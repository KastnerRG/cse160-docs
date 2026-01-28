PA4 - Tiled Matrix Multiplication
=================================

Objective
^^^^^^^^^
Implement a tiled dense matrix multiplication routine using shared memory. Note: you will not need to transpose any matrix for PA4. 


Instructions
^^^^^^^^^^^^^
Edit the code in the code tab to perform the following:

* Allocate device memory
* Copy host memory to device
* Initialize work group dimensions
* Invoke OpenCL kernel
* Copy results from device to host
* Deallocate device memory
* Implement the matrix-matrix multiplication routine using shared memory and tiling

Files and Directories
---------------------

- **Makefile**: Automates the compilation and execution process for the project.
- **main.c**: Source code for the tiled matrix multiplication using OpenCL.
- **Dataset/dataset_generator.py**: Source code for generating random matrices.
- **kernel.cl**: OpenCL kernel file for performing tiled matrix multiplication.

How to Compile
^^^^^^^^^^^^^^
The :code:`main.c, kernel.cl` files contains the code for the programming assignment. It can be run by typing :code:`make` from the PA4 folder. It generates a :code:`solution` output file.

How to Test
^^^^^^^^^^^
Use the :code:`make run` command to test your program. here are a total of 11 tests on which your program will be evaluated for (functional) correctness. We will use the last test case (testcase 10) to verify if your programs meet the speedup requirements that you should get using shared memory. The timing requirements will only be strict enough to ensure students cannot submit PA3's solution in PA4 and get credit.
Use the :code:`make time` command to see timing details for your kernel.  Your kernel must produce a time less than 43ms. 

Dataset Generation (Optional)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The dataset required to test the program is already generated. If you are interested in how the dataset is generated please refer to the :code:`dataset_generator.py` file in the Dataset folder. To recreate the dataset, run the dataset_generator.py file.

Submission
^^^^^^^^^^
Submit the :code:`main.c` and :code:`kernel.cl` files on Gradescope. Preserve the file name and kernel file name as the kernel name is used to identify and time the kernel code. Gradescope will only accept 1 submission per hour.  Please do not use Gradescope to time your code.

Grading
^^^^^^^
You will be graded on correctness (85pts) and on your best time on a 1080ti. 
- kernel runtime :math:`\leq 43`ms :math:`+0` pts
- :math:`15`ms :math:`\leq`` kernel runtime :math:`< 43`ms :math:`+5`pts 
- kernel runtime :math:`< 15`ms :math:`+10`pts

These times will be on the leaderboard

Optional
^^^^^^^^
Like last PA, we have a optional section on the PA for bragging rights. A major point behind using OpenCL is applying the same kernel to many devices so also on the leaderboard are three other devices:
- Device: Qalcomm RubicPi
- Device: Pixel Folds
- Device: DSMLP CPU 

Good implementations may optimize for one device, great implementations will optimize for many devices that you are targeting for. 

Hint 0: if you looked for "//@@ Hint", you will find how to identify the platform and device name, in case that is useful for optimizing per device.
Hint 1: You will not have access to the RubricPis and phones and the rate limit still applies on gradescope. What kind of optimizations can you do just without device access but with publically available information about the device? How do you reduce trial and error here?



.. Further Documentation
.. ^^^^^^^^^^^^^^^^^^^^^

..     **float** allocateMatrix(int rows, int cols):
..         Allocates memory for a 2D matrix with the given number of rows and columns.
..         Returns a pointer to the allocated matrix.

..     **void generateRandomMatrix(float** matrix, int rows, int cols):
..         Fills a given matrix with random float values.
..         Each element in the matrix is assigned a random float value between 0 and 1.

..     **float** multiplyMatrices(float** A, int A_rows, int A_cols, float** B, int B_cols):
..         Multiplies two matrices A and B.
..         A has dimensions A_rows x A_cols and B has dimensions A_cols x B_cols.
..         Returns a new matrix C that is the product of A and B with dimensions A_rows x B_cols.

..     **void saveMatrixToFile(const char* filename, float** matrix, int rows, int cols):
..         Saves a given matrix to a file specified by filename.
..         The matrix is written to the file with each element separated by a space and each row on a new line.

..     **int main(int argc, char* argv[]):
..         The entry point of the program.
..         Expects three command-line arguments representing the dimensions of the matrices: A (rows of matrix1), B (columns of matrix1 and rows of matrix2), and C (columns of matrix2).
..         Allocates and generates two random matrices of sizes A x B and B x C.
..         Multiplies these matrices and saves the result in three files: A.txt, B.txt, and C.txt.
..         Frees the allocated memory for all matrices before exiting.