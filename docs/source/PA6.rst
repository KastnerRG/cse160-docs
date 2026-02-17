PA6  - Reinventing the (Pytorch) Wheel
======================================

Objective
---------

In the last PA, you implemented a tiled image convolution to create image filters. As it turns out, we can use those filters to extract meaningful imformation from the image (lines, shape, textures, etc)
to help build some inteligent tasks. 

In this project, you will be using OpenCL to build a batched, strided, dilated, tiled convolution to replace PyTorch's conv2d function for convolutional neural networks (CNNs). Oh you will also make it fast too. 

This project has a few stages to go through so PLEASE READ THE DOCS FULLY before starting. Remember to start early and start often.


Instructions
------------

Part 0: What is PyTorch and why is it Fire?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

`PyTorch <https://pytorch.org/>` is a massive open source Machine Learning framework frequently used for building and training machine learning models. By and large, most models made currently are in PyTorch. 
Now Pytorch has a number of backends where these matrix operations can occur (think CUDA, Metal, some CPU vector library). For openCL there is some externel plugin which you can build and install in order to use 
PyTorch with OpenCL (which we have done in the docker container to get some models working with OpenCL! If you are interested in learning how this works, check out the docs on <PyTorch>

But lets say we wanted to replace some of these Nerual Network Operations with our own wonderful OpenCL kernels. This PA, will we pull PyTorch open slightly and get our kernels working. 

Note you are not expected to know or understand how to train models in pytorch, but for this assignment we are going to be gutting open this library a little bit in order to add our custom conv2d implementation. 
So we are going to dive into the antomy of PyTorch Models.

The basic building block of a PyTorch model is `nn.Module <https://docs.pytorch.org/docs/stable/generated/torch.nn.Module.html>`, the basic class describing Nerual Networks or thier subcomponents 
(which are themselves are modules). This can describe at a high level what layers a model may contain. In addition, modules also define how these submodules can apply operations onto some input data `x` in the `forward` method of a module.

One such example can be seen below

.. code-block:: python

    import torch
    import torch.nn as nn

    class NeuralNetwork(nn.Module):
        def __init__(self):
            super(NeuralNetwork, self).__init__()
            self.fc1 = nn.Linear(10, 8)
            self.fc2 = nn.Linear(8, 4) 
            self.fc3 = nn.Linear(4, 2)
            
            self.sigmoid = nn.Sigmoid()
        
        def forward(self, x):
            # Layer 1
            x = self.fc1(x)
            x = self.sigmoid(x)
            
            # Layer 2
            x = self.fc2(x)
            x = self.sigmoid(x)
            
            # Output layer
            x = self.fc3(x)
            x = self.sigmoid(x)
            
            return x
    model = NeuralNetwork()
    model(torch.randn(1, 10))

The key takeway here is that the forward function actually does the operations on some input data.
This forward function is automatically called when we call `model(torch.randn(1, 10))` (ie `model.forward(torch.randn(1, 10))`, its the same thing in this case). 

Each layer is composed of a fully connected layer, or `Linear` layer that is computing the function f(x) = w^Tx +b for weight matrix W and some bias b. This is the most basic neural block you can imagine.
So those fully connected (fc) layers when we call for example `self.fc1(x)`  also calls `self.fc1.forward(x)` that does the operation $w^Tx +b$ with a weight matrix W and some bias b saved in the model (<https://github.com/pytorch/pytorch/blob/v2.10.0/torch/nn/modules/linear.py#L53>). 

Which means, techically, one could just replace the forward function of a Linear layer with a function that calls some OpenCL scripts to compute the operation $w^Tx + b$. So lets start there.


Part 1: Implement Large Language Models
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Okay that is a joke, we are just replacing the linear layers of GPT2 with OpenCL. 

Before we start messing with convolutions, we are going to walk through how we are working with PyTorch by replacing these linear layers. That should give you an idea how the code in this PA works. So for this part, simliar in many ways to PA1, we will go through the code step by step to show you how the new build scripts work. 


LLMs like GPT2 (if you can even call GPT2 "large" nowadays), are made of transformer blocks that contain a number of feed forward and Linear blocks that rely on `torch.nn.Linear blocks` in PyTorch implementations.
As you can see in Figure 1 from `"Attention is All You Need" <https://arxiv.org/pdf/1706.03762>`

.. TODO REWRITE THE NAME OF THIS IMAGE
.. figure:: /image/image.png
    :align: center
    :alt: Transformer block from Attention is All You Need

**Start by going to PA6/inferance_gpt2.py**
On line 8, add `from opencl_functions import ocl_matmul`
On line 17 you will find a line of code that reads `output = torch.zeros(output.shape).to(input.device)`. Replace this with `output = ocl_matmul(input, self.weight.t())`

Notice all of this is going to be used in our custom_forward function. `ocl_matmul` is the name of a wrapper function in c++ that will be called in python to interface with the pytorch code. This wrapper function is part of the library `opencl_functions`. However we will need to build this library and have python install it so it knows it exists.

**Go to PA6/setup.py**
On line 13 after `os.path.join(here, '../helper_lib'),` add also `os.path.join(here, 'opencl_functions')` so you have the following code:
.. code-block:: python
    includes_dir = [
        os.path.join(here, '../helper_lib'),
        ##//@@ Add the path to the openCL function library here as stated in the docs
        os.path.join(here, 'opencl_functions')
    ]

setup.py gets called when we build the python wheel for this PA. This will link the c++ code we are writing to python, so we can do things like `from opencl_functions import ocl_matmul`

At this point you should be able to `make run` to build it, then have this horribly fail because nothing has been implemented. 

**Go to PA6/opencl_functions/ocl_wrapper_torch.cpp**
There are two methods in this file, one for ocl_matmul and ocl_conv2d. Observe here that this is trying to change the types of the varibles from PyTorch world (tensors) into things we can actually use in our normal OpenCL world (Pointers to arrays)

One line 23 add `matmul_impl(a_ptr, b_ptr, c_ptr, m, n, k);`

This is the actual method that implements the OpenCL host code. This method is implemented in PA6/opencl_functions/opencl-function.cpp

**Go to PA6/opencl-functions/ocl_wrapper_torch.cpp and PA6/opencl-functions/Linear.cl**
In matmul_impl, go add your host code implementation from PA4, clean up the variable names, and in Linear.cl paste in your matmul device code from that PA.

Now if you run `make`, you can run `python3 inferance_gpt2.py`

You should see the output as "Hello, I'm a language model, I'm a problem solver.\n\nWhen I started translating, I was trying to solve my"

At this point you should have a decent idea how everything links up and how we are implementing OpenCL for this particular PA. So Now that we have done that. Lets get back to convolutions.


Part 2: Implement PyTorch's Conv2d Layer And Listen To Screaming Pihas
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We will do the same sort of thing for Conv2d. And by we, I mean everything for calling our Convolution Kernel from PyTorch is implemented (see PA6/utils/conv2d_forward.py). We will use this forward function that mimics the behavior of the forward function in `Conv2d for pytorch <docs.pytorch.org/docs/stable/generated/torch.nn.Conv2d.html>`
(Hint of all the things linked on this PA, PLEASE READ THE PYTORCH DOCS ON Conv2d. This was ltterally what this PA was designed against).

For this Part, we can look at two python scripts to help us develop our implementation, take a look at the following things:
- PA6/simple_sanity_check.py basically mirrors PA5 with simple image filters over CSE 160's favorite Legally Distant Charater! This checks against the conv2d implementation from Pytorch if you want to check your method with Mr Legally.
- PA6/inferance_resnet.py will call Conv2d to identify some of the interesting animals that the CSE 160 students and teaching staff have submitted as pets. This Model uses a `resnet18 <https://arxiv.org/abs/1512.03385>`
- PA6/inferance_bird.py will call Conv2d mutliple times in order to classify if a spectrogram is a representation of one of 132 possible Peruvian Bird Species: The Screaming Piha (this model was actually trained with OpenCL! Check out extras/train_audio.py). This Model uses a `resnet50 <https://arxiv.org/abs/1512.03385>`.  The data from this comes from a subset of the the PER train split of `birdset <https://huggingface.co/datasets/DBD-research-group/BirdSet>` and you can listen to this bird on `xeno-canto <https://xeno-canto.org/species/lipaugus-vociferans>`

Use both of those to help you develop this method.

So by we will do the same sort of thing for Conv2d, I mean you will implement everything relating to convolution in PA6/opencl_functions/opencl-functions.cpp and PA6/opencl_functions/conv2d.cl

Brief explaination on the convolution. 

Inputs of the data will be of the shape (B, C_in, H, W) where B is the number of batches, C_in is the number of input channels, H is the height of the data and W is the input of the data. 

The convolution masks are in the shape of (C_out, C_in, K_h, K_w) where C_out is the number of output channels (convolutional layers often apply many diffrent masks over each channel of your input data), K_h and K_w are your mask input and output size 
These convolution masks in ML models when stacked in this way are refered to as feature maps (think of these as the convolutions are mapping the input to some high dimensional feature space)

You will also be implementing stride (both height and width), dilation (both height and width), and a bias term. Padding is already performed over the input by the host device. You will not implement groups for this PA. 
- stide is how far the mask moves over the image. In the previous PA, stride was set to 1 in both height and width, meaning every pixel was the center of the mask. In this PA, some of the masks will be skipped over
- dilation changes what input data points are included in each application of a mask (you can think of this as spreading out the mask over the image)
`Take a look at the animations provided here for what these parameters do to the convolution <https://github.com/vdumoulin/conv_arithmetic/blob/master/README.md>`

If you need additional reasoruces for this PA again check out the pytorch docs for `Conv2d <https://docs.pytorch.org/docs/stable/generated/torch.nn.Conv2d.html>` I cannot stress how helpful this will be. I used these docs to write this PA.
A quick note before doing so: techically and confusingly speaking convolution masks in the math world are known actually as Kernels because convolution is a type Kernel function. The PyTorch docs refer to Masks as Kernels. This is not to be confused with OpenCL kernels which are the programs that run on accerlators. 
These docs will be particuarlly useful, espically when figuring out the size of the output. 

Below is the pusedocode for this implementation for running this algorithm sequentially
 .. code-block:: none
    for b = 0 .. B                           // for each image in the batch 
        for m = 0 .. M                       // for each output feature maps
            for h = 0 .. H_out               // for each output element
                for w = 0 .. W_out
                {
                    y[b][m][h][w] = bias[m]; //bias term, done per channel
                    for c = 0 .. C           // sum over all input feature maps
                        for p = 0 .. K       // KxK filter
                            for q = 0 .. K
                                y[b][m][h][w] += x[b][c][h * stride_h + p * dilation_h][w * stride_w + q * dilation_w] * k[m][c][p][q]
                }


How to Compile
--------------
The :code:`PA6/opencl_functions/opencl-functions.cpp`, `PA6/opencl_functions/Linear.cl` and :code:`PA6/opencl_functions/conv2d.cl` files contain the code for the programming assignment. It can be run by typing :code:`make run` from the PA6 folder.

How to Test
-----------
Use the :code:`make run` command to test your program, which will run `python3 test.py`

Grading
-----------
You will graded for correctness based on the tests in PA6/tests.py witch have some simple image filter tests for each of the types of padding, strides, dilations, and number of batches as well as running againsted some of the models in this PA.

You will be graded for timing based on the performance of those models runs over each data point. 

Submission
----------
Submit the :code:`PA6/opencl_functions/opencl-functions.cpp` :code:`PA6/opencl_functions/Linear.cl`, and :code:`nPA6/opencl_functions/conv2d.cl` files on gradescope.


Optional
^^^^^^^^
Again, we have a optional section on the PA for bragging rights. We cannot stress enough, this works on mutliple machines. 
- Platform: Intel(R) OpenCL \t| Device: Intel(R) Xeon(R) Platinum 8275CL CPU @ 3.00GHz
- Platform: Portable Computing Language \t| Device: NVIDIA GeForce GTX 1080 Ti
- Platform:  ARM Platform \t| Device: Mali-G710 r0p0
- Platform:  QUALCOMM Snapdragon(TM) \t| Device: QUALCOMM Adreno(TM) 643


Super Optional
^^^^^^^^^^^^^^
The goal of this course is not to teach you Machine Learning. However some of this PA was made by training on OpenCL with PyTorch. If you are curious how extactly that works, you can 
1) Go to PA6/extras/train_audio.py and run the training script yourself (make sure to have some space on your machine, BirdSet takes up a lot of space)
2) Check out <PyTorch>


.. PA6 - Convolutional Neural Network Forward Layer GPU Implementation
.. ===================================================================

.. Objective
.. ---------
.. This project implements the forward pass of a convolution layer using OpenCL. Convolutional layers are the primary building blocks of convolutional neural networks (CNNs), which are used for tasks like image classification, object detection, natural language processing, and recommendation systems.

.. You will be working with a modified version of the LeNet5 architecture shown below:

.. .. figure:: /image/lenet.png
..     :align: center
..     :alt: LeNet-5 Architecture

.. You can read about the original network in `Gradient-based learning applied to document recognition <https://ieeexplore.ieee.org/abstract/document/726791>`_

.. Your optimized OpenCL implementation of the convolutional layer will be used to perform inference for layers C1 and C3 (shown in red) in the figure above. This leverages the `mini-dnn-cpp <https://github.com/iamhankai/mini-dnn-cpp>`_ (Mini-DNN) framework for implementing the modified LeNet-5.

.. Input Data
.. ----------
.. The network will be tested on the `Fashion MNIST dataset <https://github.com/zalandoresearch/fashion-mnist>`_, which contains 10,000 single channel images, each of dimension 86x86. We will process these in a batch of 1000 images. The output layer consists of 10 nodes representing the likelihood of the input belonging to one of the 10 classes (t-shirt, dress, sneaker, boot, etc).


.. Instructions
.. -------------
.. This assignment requires you to write a GPU implementation of the convolutional layer. The files you need to update to implement the forward convolution is:
.. :code:`PA6/src/layer/custom/new-forward-kernel.cl` and :code:`new-forward.cc`.

.. To understand which functions within :code:`new-forward-kernel.cl` are being called and when you can refer to :code:`cnn/src/layer/custom/gpu.cc`.

.. Make sure that you use :code:`opecnl->context`, :code:`opencl->queue`, and :code:`opencl->program` from the :code:`opencl.cc` file for the context, command queue, and program.  These are initialized for you.


.. The pseudocode for a convolutional layer is:

.. .. code-block:: none

..     for b = 0 .. B                     // for each image in the batch 
..         for m = 0 .. M                 // for each output feature maps
..             for h = 0 .. H_out         // for each output element
..                 for w = 0 .. W_out
..                 {
..                     y[b][m][h][w] = 0;
..                     for c = 0 .. C     // sum over all input feature maps
..                         for p = 0 .. K // KxK filter
..                             for q = 0 .. K
..                                 y[b][m][h][w] += x[b][c][h + p][w + q] * k[m][c][p][q]
..                 }

.. This animation helps visualize this process:

.. .. figure:: /image/convolution.png
..     :align: center
..     :alt: Convolution Animation

.. Source: https://stanford.edu/~shervine/teaching/cs-230/cheatsheet-convolutional-neural-networks#layer

.. File Descriptions
.. -----------------
.. - **m1.cc**: The main file that contains the main function to run the forward pass of the convolutional layer on CPU.
.. - **m2.cc**: The main file that contains the main function to run the forward pass of the convolutional layer on GPU.
.. - **ece408net.cc**: The file that constructs the network.
.. - **Eigen**: The Eigen library is used for matrix operations.
.. - **src/network.cc**: Implementation of the network.
.. - **src/mnist.cc**: For managing the MNIST dataset.
.. - **src/optimizer/sgd.cc**: Implementation of the stochastic gradient descent optimizer.
.. - **src/loss/cross_entropy_loss.cc**: Implementation of the cross entropy loss function.
.. - **src/loss/mse_loss.cc**: Implementation of the mean squared error loss function.
.. - **src/layer/ave_pooling.cc**: Implementation of the average pooling layer on CPU.
.. - **src/layer/conv_cust.cc**: Implementation of the convolutional layer in OpenCL.
.. - **src/layer/conv.cc**: Implementation of the convolutional layer on CPU.
.. - **src/layer/fully_connected.cc**: Implementation of the fully connected layer on CPU.
.. - **src/layer/max_pooling.cc**: Implementation of the max pooling layer on CPU.
.. - **src/layer/relu.cc**: Implementation of the ReLU activation function on CPU.
.. - **src/layer/sigmoid.cc**: Implementation of the sigmoid activation function on CPU.
.. - **src/layer/softmax.cc**: Implementation of the softmax activation function on CPU.
.. - **src/layer/custom/new-forward-kernel.cl**: The OpenCL kernel file that contains the implementation of the forward pass of the convolutional layer. Feel free to create additional functions for to optimize CPU and GPU independently.
.. - **src/layer/custom/new-forward.cc**: The file that contains the implementation of the forward pass of the convolutional layer on OpenCL. You can use :code:`opencl->platform` and `opencl->device` to get information about the platform and device you are running on.
.. - **src/layer/custom/opencl.cc**: The file that contains the OpenCL helper functions. It also contains information about the platform and device you are running on. **It is important that you use this file to initialize OpenCL and create the context, command queue, and program.**

.. How to Compile & Test
.. --------------
.. The :code:`PA6/src/layer/custom/new-forward-kernel.cl` and :code:`new-forward.cc` files contain the code for the programming assignment. It can be run by typing :code:`make gpu` from the PA6 folder. It generates a :code:`m1` output executable.

.. How to Test
.. -----------
.. Use the :code:`make gpu` command to test your program, which will run the program on a batch size of 1000 images on GPU. The command will print out the run time and accuracy. To test your program on CPU, use the command :code:`make cpu`.

.. Test Output
.. -----------

.. .. You will need to checkout a GPU for this assignment, but please avoid editing while accessing a device. You can accomplish this with:
.. .. :code:`launch.sh -g 1 -s -i ghcr.io/ucsd-ets/cse160-notebook:main -W CSE160_WI25_A00 -P Always`

.. The accuracy of your implementation should meet the 0.886 that our implementation does. 90% of this assignment will be graded on correctness. To gain full credits, your implementation on 1080ti GPU should run correctly within 60ms.  


.. Submission
.. ----------
.. Submit the :code:`PA6/src/layer/custom/new-forward-kernel.cl` and :code:`new-forward.cc` files on gradescope.

.. Credit
.. ------
.. This project is originally from UIUC ECE408 and builds off several open-source projects including the Fashion MNIST dataset, mini-dnn-cpp, and the Eigen project.


