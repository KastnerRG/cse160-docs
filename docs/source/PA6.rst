PA6 - Convolutional Neural Network Forward Layer GPU Implementation
===================================================================

Objective
---------
This project implements the forward pass of a convolution layer using OpenCL. Convolutional layers are the primary building blocks of convolutional neural networks (CNNs), which are used for tasks like image classification, object detection, natural language processing, and recommendation systems.

You will be working with a modified version of the LeNet5 architecture shown below:

.. figure:: /image/lenet.png
    :align: center
    :alt: LeNet-5 Architecture

You can read about the original network:

Source: http://yann.lecun.com/exdb/publis/pdf/lecun-01a.pdf

Your optimized OpenCL implementation of the convolutional layer will be used to perform inference for layers C1 and C3 (shown in red) in the figure above. This leverages the `mini-dnn-cpp <http://yann.lecun.com/exdb/publis/pdf/lecun-01a.pdf>`_ (Mini-DNN) framework for implementing the modified LeNet-5.

Input Data
----------
The network will be tested on the `Fashion MNIST dataset <https://github.com/zalandoresearch/fashion-mnist>`_, which contains 10,000 single channel images, each of dimension 86x86. We will process these in a batch of 1000 images. The output layer consists of 10 nodes representing the likelihood of the input belonging to one of the 10 classes (t-shirt, dress, sneaker, boot, etc).


Instructions
-------------
This assignment requires you to write a GPU implementation of the convolutional layer. The files you need to update to implement the forward convolution is:
:code:`PA6/src/layer/custom/new-forward-kernel.cl` and :code:`new-forward.cc`.

To understand which functions within :code:`new-forward-kernel.cl` are being called and when you can refer to :code:`cnn/src/layer/custom/gpu.cc`.

Make sure that you use :code:`opecnl->context`, :code:`opencl->queue`, and :code:`opencl->program` from the :code:`opencl.cc` file for the context, command queue, and program.  These are initialized for you.


The pseudocode for a convolutional layer is:

.. code-block:: none

    for b = 0 .. B                     // for each image in the batch 
        for m = 0 .. M                 // for each output feature maps
            for h = 0 .. H_out         // for each output element
                for w = 0 .. W_out
                {
                    y[b][m][h][w] = 0;
                    for c = 0 .. C     // sum over all input feature maps
                        for p = 0 .. K // KxK filter
                            for q = 0 .. K
                                y[b][m][h][w] += x[b][c][h + p][w + q] * k[m][c][p][q]
                }

This animation helps visualize this process:

.. figure:: /image/convolution.png
    :align: center
    :alt: Convolution Animation

Source: https://stanford.edu/~shervine/teaching/cs-230/cheatsheet-convolutional-neural-networks#layer

File Descriptions
-----------------
- **m1.cc**: The main file that contains the main function to run the forward pass of the convolutional layer on CPU.
- **m2.cc**: The main file that contains the main function to run the forward pass of the convolutional layer on GPU.
- **ece408net.cc**: The file that constructs the network.
- **Eigen**: The Eigen library is used for matrix operations.
- **src/network.cc**: Implementation of the network.
- **src/mnist.cc**: For managing the MNIST dataset.
- **src/optimizer/sgd.cc**: Implementation of the stochastic gradient descent optimizer.
- **src/loss/cross_entropy_loss.cc**: Implementation of the cross entropy loss function.
- **src/loss/mse_loss.cc**: Implementation of the mean squared error loss function.
- **src/layer/ave_pooling.cc**: Implementation of the average pooling layer on CPU.
- **src/layer/conv_cust.cc**: Implementation of the convolutional layer in OpenCL.
- **src/layer/conv.cc**: Implementation of the convolutional layer on CPU.
- **src/layer/fully_connected.cc**: Implementation of the fully connected layer on CPU.
- **src/layer/max_pooling.cc**: Implementation of the max pooling layer on CPU.
- **src/layer/relu.cc**: Implementation of the ReLU activation function on CPU.
- **src/layer/sigmoid.cc**: Implementation of the sigmoid activation function on CPU.
- **src/layer/softmax.cc**: Implementation of the softmax activation function on CPU.
- **src/layer/custom/new-forward-kernel.cl**: The OpenCL kernel file that contains the implementation of the forward pass of the convolutional layer.
- **src/layer/custom/new-forward.cc**: The file that contains the implementation of the forward pass of the convolutional layer on OpenCL.
- **src/layer/custom/opencl.cc**: The file that contains the OpenCL helper functions. **It is important that you use this file to initialize OpenCL and create the context, command queue, and program.**

How to Compile & Test
--------------
The :code:`PA6/src/layer/custom/new-forward-kernel.cl` and :code:`new-forward.cc` files contain the code for the programming assignment. It can be run by typing :code:`make gpu` from the PA6 folder. It generates a :code:`m1` output executable.

How to Test
-----------
Use the :code:`make gpu` command to test your program, which will run the program on a batch size of 1000 images on GPU. The command will print out the run time and accuracy. To test your program on CPU, use the command :code:`make cpu`.

Test Output
-----------

.. You will need to checkout a GPU for this assignment, but please avoid editing while accessing a device. You can accomplish this with:
.. :code:`launch.sh -g 1 -s -i ghcr.io/ucsd-ets/cse160-notebook:main -W CSE160_WI25_A00 -P Always`

The accuracy of your implementation should meet the 0.886 that our implementation does. 90% of this assignment will be graded on correctness. To gain full credits, your implementation on 1080ti GPU should run correctly within 60ms.  


Submission
----------
Submit the :code:`PA6/src/layer/custom/new-forward-kernel.cl` and :code:`new-forward.cc` files on gradescope.

Credit
------
This project is originally from UIUC ECE408 and builds off several open-source projects including the Fashion MNIST dataset, mini-dnn-cpp, and the Eigen project.


