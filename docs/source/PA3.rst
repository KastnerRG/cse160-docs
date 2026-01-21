PA3 - Matrix Multiplication
===========================

Objective
^^^^^^^^^
The purpose of this lab is to get you familiar with mapping computations onto the GPU 
and multi-dimensional local and global work sizes. You will implement transposed matrix multiplication 
by writing the GPU kernel code as well as the associated host code.

Instructions
^^^^^^^^^^^^^
Given matrices :math:`A \in \mathbb{R}^{m \times n}` 
and :math:`B \in \mathbb{R}^{m \times p}`, compute 
their product :math:`C = A^T B`. 
Recall that :math:`C` will be an :math:`n \times p` matrix that 
can be computed with the following formula:

.. math:: 
    C_{ij} = \sum_{k = 1}^m (A^T)_{ik} B_{kj}

Where :math:`M_{ij}` is the entry at the row :math:`i` and 
column :math:`j` of matrix :math:`M`.


Edit the code to perform the following:

* Set the dimensions of the result matrix
* Create device buffers for the matrices 
* Copy host memory to device buffers
* Create the kernel
* Set up arguments for the kernel
* Define local and global work sizes
* Invoke OpenCL kernel
* Copy result matrix from device to host
* Release memory on device 
* Write the OpenCL kernel to perform matrix multiplication with row wise coarsening

Instructions about where to place each part of the code is demarcated by the :code:`//@@` comment lines.

How to Compile
^^^^^^^^^^^^^^
The :code:`main.c` file contains the host code for the programming assignment. 
THe :code:`kernel.cl` file contains the device code.
There is a Makefile included which compiles it and links it with library helper functions.
It can be run by typing :code:`make` from the PA3 folder. It generates a :code:`solution` output file. 
During development, make sure to run the :code:`make clean` command before running :code:`make`.

How to Test
^^^^^^^^^^^
Use the :code:`make run` command to test your program on the 
test cases in the :code:`Dataset` foldeer. 
There are a total of 11 tests on which your program will be evaluated for correctness. 

We will use the last test case (testcase 10) to verify if your programs meet the speedup requirements that you should get using coarsening on the row. 
Use the :code:`make time` command to see timing details for your kernel.  Your kernel must produce a time less than 500ms. 

For debugging tools, you can use `oclgrind`, see https://github.com/jrprice/Oclgrind?tab=readme-ov-file#usage for usage documentation

Submission
^^^^^^^^^^
Submit the :code:`main.c` and :code:`kernel.cl` files on gradescope. Preserve the file name while uploading to gradescope. 

Gradescope submissions are heavily rate limited starting this PA. See <rate_limit> for more details. Please do not use Gradescope to time your code.