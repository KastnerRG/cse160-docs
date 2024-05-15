PA3 - Matrix Multiplication
===========================

Objective
^^^^^^^^^
The purpose of this lab is to get you familiar with mapping computations onto the GPU 
and multi-dimensional local and global work sizes. You will implement matrix multiplication 
by writing the GPU kernel code as well as the associated host code.

Instructions
^^^^^^^^^^^^^
Edit the code in the code tab to perform the following:

* Set the dimensions of the result matrix
* Create device buffers for the matrices 
* Copy host memory to device buffers
* Create the kernel
* Build the kernel program?
* Set up arguments for the kernel
* Define local and global work sizes
* Invoke OpenCL kernel
* Copy result matrix from device to host
* Release memory on device 
* Write the OpenCL kernel to perform matrix multiplication

Instructions about where to place each part of the code is demarcated by the :code:`//@@` comment lines.

How to Compile
^^^^^^^^^^^^^^
The :code:`template.c` file contains the host code for the programming assignment. 
THe :code:`kernel.cl` file contains the device code.
There is a Makefile included which compiles it and links it with library helper functions.
It can be run by typing :code:`make` from the PA3 folder. It generates a :code:`solution` output file. 
During development, make sure to run the :code:`make clean` command before running :code:`make`.

How to Test
^^^^^^^^^^^
Use the :code:`make run` command to test your program. There are a total of 9 tests on which your program will be evaluated.

Dataset Generation (Optional)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
TODO

Submission
^^^^^^^^^^
TODO