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
* Initialize work group dimensions
* Invoke OpenCL kernel
* Copy results from device to host
* Deallocate device memory
* Implement the matrix-matrix multiplication routine using shared memory and tiling

Recommended Block dimensions are 16 x 16.

Files and Directories
---------------------

- **Makefile**: Automates the compilation and execution process for the project.
- **tmm.c**: Source code for the tiled matrix multiplication using OpenCL.
- **datagen.c**: Source code for generating random matrices.
- **kernel.cl**: OpenCL kernel file for performing tiled matrix multiplication.
- **test.sh**: Script to run the matrix multiplication on all generated matrix sets.
- **datagen.sh**: Script to generate multiple sets of matrices.
- **matrices/**: Directory to store the generated matrix sets.
- **timing_log.txt**: File to log the execution time for each matrix multiplication run.

How to Compile
^^^^^^^^^^^^^^
The :code:`tmm.c, kernel.cl` files contains the code for the programming assignment. There is a Makefile included which compiles it and links it with the libgputk CUDA library automatically. It can be run by typing :code:`make` from the PA3 folder. It generates a :code:`tmm` output file.

How to Test
^^^^^^^^^^^
Use the :code:`make run` command to test your program. here are a total of 9 tests on which your program will be evaluated for (functional) correctness. Since PA3 and PA4 are functionally the same, we will use the last test case to verify if your programs meet the speedup requirements that you should get using shared memory. The timing requirements will only be strict enough to ensure students cannot submit PA3's solution in PA4 and get credit.
Timing details will be saved in 

Dataset Generation (Optional)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The dataset required to test the program is already generated. If you are interested in how the dataset is generated please refer to the :code:`datagen.c` file. To recreate the dataset, run the datagen.sh script.

Submission
^^^^^^^^^^
Submit the :code:`tmm.c` and :code:`kernel.cl` files on Gradescope. Preserve the file name and kernel file name as the kernel name is used to identify and time the kernel code.

Further Documentation
^^^^^^^^^^^^^^^^^^^^^

    **float** allocateMatrix(int rows, int cols):
        Allocates memory for a 2D matrix with the given number of rows and columns.
        Returns a pointer to the allocated matrix.

    **void generateRandomMatrix(float** matrix, int rows, int cols):
        Fills a given matrix with random float values.
        Each element in the matrix is assigned a random float value between 0 and 1.

    **float** multiplyMatrices(float** A, int A_rows, int A_cols, float** B, int B_cols):
        Multiplies two matrices A and B.
        A has dimensions A_rows x A_cols and B has dimensions A_cols x B_cols.
        Returns a new matrix C that is the product of A and B with dimensions A_rows x B_cols.

    **void saveMatrixToFile(const char* filename, float** matrix, int rows, int cols):
        Saves a given matrix to a file specified by filename.
        The matrix is written to the file with each element separated by a space and each row on a new line.

    **int main(int argc, char* argv[]):
        The entry point of the program.
        Expects three command-line arguments representing the dimensions of the matrices: A (rows of matrix1), B (columns of matrix1 and rows of matrix2), and C (columns of matrix2).
        Allocates and generates two random matrices of sizes A x B and B x C.
        Multiplies these matrices and saves the result in three files: A.txt, B.txt, and C.txt.
        Frees the allocated memory for all matrices before exiting.