PA8 - GeMM Convolution
======================

Introduction
------------
You will be implementing convolution via matrix multiplication. This PA has the most challenging indexing of all the PAs. We highly recommend that you draft your code in a separate file and test it on small test cases. Some test cases are provided at the bottom of this writeup.

Your Tasks
-----------
- Implement and call the im2col kernel
- Call `clblast::GemmBatched` to compute the product of the mask and unrolled input feature maps.

im2col
^^^^^^

Copy the elements of the input :math:`x` with shape :math:`(B, C, W, H)` to :math:`x_{\text{unroll}}` which has shape :math:`(B, C \times K \times K, (H - K + 1) \times (W - K + 1))`. Here, :math:`x_{\text{unroll}}` is a list of matrices with one matrix for each batch element. For a given matrix :math:`M` in :math:`x_{\text{unroll}}`:

- each column of :math:`M` corresponds to one (row_o, col_o) pair in the **output of the convolution** (NOT the output of im2col)
  
  - output rows and columns are flattened in row-major order
- the rows of :math:`M` correspond to the receptive field of each (row_o, col_o)
  
  - this is flattened in channel major order
  - each channel is then flattened in row-major order

.. image:: /image/unroll_diagram.excalidraw.png

Partial pseudocode is given below:
::

  for b in 0..<B:
      for c_in in 0..<C:
          for row_i in 0..<H:
              for col_i in 0..<W:
                  for mask_offset_row in 0..<K:
                      for mask_offset_col in 0..<K:
                          # indices in the output of the convolution whose receptive fields include (row_i, col_i)
                          row_o = ??
                          col_o = ??
                          row_o_in_bounds = 0 <= row_o and row_o < H - K + 1
                          col_o_in_bounds = 0 <= col_o and col_o < W - K + 1
                          if row_o_in_bounds and col_o_in_bounds:
                              # indices in x_unroll to write to
                              col_u = ??
                              row_u = ??
                              
                              x_unroll[b, col_u, row_u] = x[b, c_in, row_i, col_i]

Guiding Questions
"""""""""""""""""
- Given a (row_i, col_i), what receptive fields overlap with it?
- What (row_o, col_o) does each receptive field influence?
- What part of the receptive field is it in?

Batched GeMM
^^^^^^^^^^^^

Call `clblast::GemmBatched` to compute the product of :math:`k` and :math:`x_{\text{unroll}}`. The documentation for it is `here <https://github.com/CNugteren/CLBlast/blob/master/doc/api.md#xgemmbatched-batched-version-of-gemm>`_. For additional context:

- The formula for batched GeMM is :math:`C_i <- \alpha_i A_i B_i + \beta_i C_i` where
  
  - :math:`i` is the batch index
  - :math:`A_i` is :math:`m \times k`
  - :math:`B_i` is :math:`k \times n`
  - :math:`C_i` is :math:`m \times n` and modified in place
  - :math:`\alpha_i, \beta_i \in \mathbb{R}`
  
- `a_offsets[i]` should be the (1 dimensional) index of the first element of matrix :math:`i` in :math:`A`
  
  - same applies to `b_offsets` and `c_offsets`
  - it may be useful to use C++ vectors for this
- the leading dimension of a row-major matrix is the number of columns it has

Note that while the mask :math:`k` can be seen as a :math:`(M, C, K, K)` tensor, it can also be interpreted as an :math:`(M, C \times K \times K)` matrix, which is what we do here. If you are familiar with `numpy`, this is like doing `k.reshape((M, C * K * K))`. Similarly, :math:`y` is a :math:`(B, M, H-K+1, W-K+1)` tensor, but is interpreted as a :math:`(B, M, (H-K+1) \times (W-K+1))` tensor.

Alternatively, you can write your own batched matrix multiplication kernel. This may also be good for testing your `im2col` kernel if you cannot get `clblast` to work yet.

Implementation Suggestions
--------------------------

- Do the algorithm by hand on a small test case (such as those provided at the bottom of this writeup)
- **Draft your code in a separate file and test on small test cases**
  
  - This can be done locally, reducing dependence on the DSMLP
  - Tutors and TAs in office hours can better help with debugging this code as well
- For each variable that represents an index, keep track of
  
  - What that index represents
  - The range of possible values
  - Whether it is indexing an element in the input, convolution output, or im2col output
  - What 0 in its coordinate system represents

Im2Col Test Cases
----------------
All of the following test cases have a batch dimension of 1.

With :math:`C = 1, H = 4, W = 4, K=3`

.. code-block::

  x:
  [[[ 0 1 2 3]
    [ 4 5 6 7]
    [ 8 9 10 11]
    [12 13 14 15]]]
   
  x_unroll:
  [[ 0  1  4  5]
   [ 1  2  5  6]
   [ 2  3  6  7]
   [ 4  5  8  9]
   [ 5  6  9 10]
   [ 6  7 10 11]
   [ 8  9 12 13]
   [ 9 10 13 14]
   [10 11 14 15]]

With :math:`C=2, H=4, W=4, K=3`

.. code-block::

  x:
  [[[ 0  1  2  3]
    [ 4  5  6  7]
    [ 8  9 10 11]
    [12 13 14 15]]

   [[16 17 18 19]
    [20 21 22 23]
    [24 25 26 27]
    [28 29 30 31]]]

  x_unroll:
  [[ 0  1  4  5]
   [ 1  2  5  6]
   [ 2  3  6  7]
   [ 4  5  8  9]
   [ 5  6  9 10]
   [ 6  7 10 11]
   [ 8  9 12 13]
   [ 9 10 13 14]
   [10 11 14 15]
   [16 17 20 21]
   [17 18 21 22]
   [18 19 22 23]
   [20 21 24 25]
   [21 22 25 26]
   [22 23 26 27]
   [24 25 28 29]
   [25 26 29 30]
   [26 27 30 31]]

The following Python script can be used to make additional test data if you wish to draft your code in Python.

.. code-block:: python

  import numpy as np
  C = 2
  H = 4 
  W = 4 
  K = 3
  x = np.arange(H * W * C)
  x = x.reshape((1, C, H, W)) 
  x_unroll = np.zeros((1, C * K * K,  (H - K + 1) *  (W - K + 1)), dtype=np.int32)
