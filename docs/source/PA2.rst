PA2 - Vector Addition
=====================

Objective
^^^^^^^^^
The purpose of this lab is to introduce the student to the OpenCL Device Programming by implementing vector addition 
as well as the start of some optimization techniques such as coalescing. The student will implement vector addition by
writing the GPU kernel code as well as the associated host code.

Instructions
^^^^^^^^^^^^^
Edit the code in the code tab to perform the following:

- Copy host memory to device
- Initialize global size and local size
- Invoke OpenCL kernel
- Copy results from device to host
- Free device memory
- Write the OpenCL kernel
- Coalescing

Instructions about where to place each part of the code is demarcated by the `//@@` comment lines. UNLIKE in PA1, you will need to write lines of code, not just fill in arguments.  
You will need to implement three kernels.  The first will take two vector inputs and produce the sum.  The second will take 4 vector inputs and produce the sum.
The last one will be an optimized version of the 4 vector input kernel that uses coalesced memory accesses with a much smaller global size. 

How to Compile
^^^^^^^^^^^^^^
The :code:`main.c`, :code:`vector_add_2.cl`, :code:`vector_add_4.cl`, :code:`vector_add_2_coalesced.cl` files contain the code for the programming assignment. 
There is a Makefile included which compiles it. It can be run by typing :code:`make` from the PA2 folder. 
It generates a :code:`solution` output file. During development, make sure to run the :code:`make clean` command before running :code:`make`. 

How to Test
^^^^^^^^^^^
Use the :code:`make run` command to test your program. There are a total of 10 tests on which your program will be evaluated.

Dataset Generation (Optional)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The dataset required to test the program is already generated. If you are interested in how the dataset is generated please refer to the :code:`dataset_generator.py` file in the :code:`Dataset` directory. 
You may run this script using :code:`python dataset_generator.py`.

Submission
^^^^^^^^^^
Submit the :code:`main.c` and :code:`vector_add_2.cl`, :code:`vector_add_4.cl`, :code:`vector_add_2_coalesced.cl` files on gradescope. 
Preserve the file name while uploading to gradescope. Remember to do the quiz. 