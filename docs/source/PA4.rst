PA4 - Tiled Matrix Multiplication
=================================

Objective
^^^^^^^^^
Implement a tiled dense matrix multiplication routine using shared memory.


Instructions
^^^^^^^^^^^^^
Edit the code in the code tab to perform the following:

* Allocate device memory
* Copy host memory to device
* Initialize thread block and kernel grid dimensions
* Invoke CUDA kernel
* Copy results from device to host
* Deallocate device memory
* Implement the matrix-matrix multiplication routine using shared memory and tiling

Instructions about where to place each part of the code is demarcated by the :code:`//@@` comment lines. Recommended Block dimensions are 16 x 16.

How to Compile
^^^^^^^^^^^^^^
The :code:`template.cu` file contains the code for the programming assignment. There is a Makefile included which compiles it and links it with the libgputk CUDA library automatically. It can be run by typing :code:`make` from the PA3 folder. It generates a :code:`solution` output file. During development, make sure to run the :code:`make clean` command before running :code:`make`.

To compile the program for debugging, use the :code:`make debug` command.

How to Test
^^^^^^^^^^^
Use the :code:`make run` command to test your program. here are a total of 9 tests on which your program will be evaluated for (functional) correctness. Use the :code:`make run_big command` to test your program on a big matrix size. Since PA3 and PA4 are functionally the same, we will use the last test case (:code:`make run_big`) to verify if your programs meet the speedup requirements that you should get using shared memory. The timing requirements will only be strict enough to ensure students cannot submit PA3's solution in PA4 and get credit.

Dataset Generation (Optional)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The dataset required to test the program is already generated. If you are interested in how the dataset is generated please refer to the :code:`dataset_generator.cpp` file. You may compile this file using the :code:`make dataset_generator` command and run the executeable using the command :code:`./dataset_generator`.

Submission
^^^^^^^^^^
Submit the :code:`template.cu` file on gradescope. Preserve the file name and kernel function name as the kernel name is used to identify and time the kernel code.