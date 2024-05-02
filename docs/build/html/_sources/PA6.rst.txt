PA6 - Convolutional Neural Network Forward Layer GPU Implementation
===================================================================

Objective
^^^^^^^^^
This is the second part of a three part project implementing and optimizing the forward pass of a convolution layer using CUDA. Convolutional layers are the primary building blocks of convolutional neural networks (CNNs), which are used for tasks like image classification, object detection, natural language processing and recommendation systems.

You will be working with a modified version of the LeNet5 architceture shown bellow:

.. figure:: /image/lenet.png
    :align: center
    :alt: LeNet-5 Architecture

You can read about the original network:

Source: http://yann.lecun.com/exdb/publis/pdf/lecun-01a.pdf

Your optimized CUDA implementation of the convolutional layer will be used to perform inference for layers C1 and C3 (shown in red) in the figure above. This leverages the `mini-dnn-cpp <http://yann.lecun.com/exdb/publis/pdf/lecun-01a.pdf>`_ (Mini-DNN) framework for implementing the modified LeNet-5.

Input Data
^^^^^^^^^^
The network will be tested on the `Fashion MNIST dataset <https://github.com/zalandoresearch/fashion-mnist>`_ which contains 10,000 single channel images each of dimensions 86x86 but we will only use 1000 of these at a time. The output layer consists of 10 nodes, where each node represents the likelihood of the input belonging to one of the 10 classes (T-shirt, dress, sneaker, boot, etc).


Instructions
^^^^^^^^^^^^^
This assignment requires you to complete a GPU implementation of the convolutional layer. Performance of the GPU implementation is not important as this assignment is intended to build functionality before optimizing. The only file you need to update to implement the forward convolution is: :code:`src/layer/custom/new-forward.cu`. To understand which functions within :code:`new-forward.cu` are being called and when, it may be helpful ot refer to :code:`src/layer/conv_cust.cc`.

Again, you are performing the following operation:

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

This animation can help visualize this process better:

.. figure:: /image/convolution.png
    :align: center
    :alt: Convolution Animation

Source: https://stanford.edu/~shervine/teaching/cs-230/cheatsheet-convolutional-neural-networks#layer

How to Compile
^^^^^^^^^^^^^^
The :code:`src/layer/custom/new-forward.cu` file contains the code for the programming assignment. There is a Makefile included which compiles it and links it with the libgputk CUDA library automatically. It can be run by typing :code:`make m2` from the PA7 folder. It generates a :code:`m2` output executable.

How to Test
^^^^^^^^^^^
Use the :code:`make run` command to test your program which will run your program on a batch size of 1000 images. This will automatically compile your source (equivilent to executing :code:`make m2` and then running :code:`./m2 1000`).

Test Output
^^^^^^^^^^^

You will need to checkout a GPU for this assignment, but please avoid editing while accessing a device. You can accomplish this with: :code:`launch.sh -g 1 -s -i ghcr.io/ucsd-ets/nvcr-cuda:main`

The accuracy of your implementation should meet the 0.886 that our implementation does.

Submission
^^^^^^^^^^
Submit the :code:`src/layer/custom/new-forward.cu` file on gradescope.

Credit
^^^^^^
This project is originally from UIUC ECE408 and builds off a number of open source projects including the Fashion MNIST dataset, mini-dnn-cpp, and the Eigen project.