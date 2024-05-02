PA2 - Vector Addition
=====================

Objective
^^^^^^^^^
The purpose of this lab is to introduce the student to the CUDA API by implementing vector addition. The student will implement vector addition by writing the GPU kernel code as well as the associated host code.

Instructions
^^^^^^^^^^^^^
Edit the code in the code tab to perform the following:

* Allocate device memory
* Copy host memory to device
* Initialize thread block and kernel grid dimensions
* Invoke CUDA kernel
* Copy results from device to host
* Free device memory
* Write the CUDA kernel

Instructions about where to place each part of the code is demarcated by the :code:`//@@` comment lines.

How to Compile
^^^^^^^^^^^^^^
The :code:`template.cu` file contains the code for the programming assignment. There is a Makefile included which compiles it and links it with the libgputk CUDA library automatically. It can be run by typing :code:`make` from the PA2 folder. It generates a :code:`solution` output file. During development, make sure to run the :code:`make clean` command before running :code:`make`.

How to Test
^^^^^^^^^^^
Use the :code:`make run` command to test your program. There are a total of 10 tests on which your program will be evaluated.

Dataset Generation (Optional)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The dataset required to test the program is already generated. If you are interested in how the dataset is generated please refer to the :code:`dataset_generator.cpp` file. You may compile this file using the :code:`make dataset_generator` command and run the executeable using the command :code:`./dataset_generator`.

Submission
^^^^^^^^^^
Submit the :code:`template.cu` file on gradescope. Preserve the file name while uploading to gradescope.