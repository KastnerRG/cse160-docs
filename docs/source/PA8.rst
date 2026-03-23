PA8 - Softmaxing the (PyTorch) Wheel
Objective ^^^^^^^^^^^^^^^^^^^^^^
In the last PA, you implemented a batched, strided, dilated, tiled convolution to replace PyTorch's conv2d function for convolutional neural networks. Those convolutional layers produce raw output scores called logits. Before a model can make a prediction, those logits need to be converted into a valid probability distribution. That is where Softmax comes in.
In this project, you will be using OpenCL to build a numerically stable, parallelized Softmax kernel. The input is of shape (Batch_size, N) and you must implement softmax independently over each vector of length N. Since this is the last PA, you can implement this however you wish as long as you are using OpenCL kernels.


Remember to start early and start often.


Instructions ^^^^^^^^^^^^^^^^^^^^^^
Part 0: What is Softmax and Why Do We Care?


Softmax is a **normalized exponential function** and one of the most important activation functions in modern machine learning. It appears at the output layer of nearly every classification network, and inside the attention mechanism of every transformer model. Given a vector of K real numbers, it produces a valid probability distribution over K outcomes:


.. math::


   \sigma(\mathbf{z})_i = \frac{e^{z_i}}{\sum_{j=1}^{K} e^{z_j}}


The output values all lie in ``(0, 1)`` and sum to exactly 1, which is what makes it suitable as a probability distribution. The largest logit gets the highest probability, and the function is differentiable everywhere, which is essential for training via backpropagation.


**The Numerical Stability Problem**


The naive formula above has a serious flaw in practice: when any ``z_i`` is large, ``exp(z_i)`` overflows floating point representation entirely:


* When ``z_i = 64``, that exponentiation is 6.2x10^27
* When ``z_i = 128``, that exponentiation is 3.9x10^55
* When ``z_i = 256``, that exponentiation is 1.5x10^111
* When ``z_i = 512``, that exponentiation is 2.3x10^222…


The standard fix is the **max-shift trick**: subtract the row maximum from every element before exponentiating:


.. math::


   \sigma(\mathbf{z})_i = \frac{e^{z_i - \max(\mathbf{z})}}{\sum_{j=1}^{n} e^{z_j - \max(\mathbf{z})}}


This is mathematically identical to the original formula (the ``max(z)`` terms cancel in the ratio), but the largest exponentiated value is now always ``exp(0) = 1``, and all other values sit in ``(0, 1]``. Values much smaller than the max underflow gracefully to 0, which is fine since they represent negligible probabilities.


You should consider numerical stability carefully when designing your kernel. Any implementation that does not address this will fail on the test cases.


The three key computations are:


* **Find max**: scan the input vector to find ``max(z)``
* **Calculate norm**: sum ``exp(z_j - max(z))`` across all elements
* **Compute softmax**: divide each ``exp(z_i - max(z))`` by the norm


Part 1: Implement the Naive Softmax
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Before parallelizing anything, you will implement a naive version where **each work-item processes one entire row** of the input matrix. This gives you a correct baseline before you start optimizing.


The naive approach requires three sequential passes over each row:


* **Pass 1: Find max**: Traverse the vector from index 0 to N-1 to find ``max(z)``
* **Pass 2: Calculate norm**: Traverse again, accumulating the sum of ``exp(z_j - max(z))``
* **Pass 3: Compute softmax**: Traverse a third time, writing each output as ``exp(z_i - max(z)) / norm``


**Go to PA8/opencl_functions/softmax.cl**
Implement your naive kernel here. Each work-item should use its global ID to index into the correct row of the input matrix:


**Go to PA8/opencl_functions/opencl-functions.cpp**
Implement the host-side code to set kernel arguments, allocate device buffers, and enqueue the kernel. Once you have a passing naive implementation, you have a correct baseline. Now make it fast.


Part 2: Implement a Parallel Softmax
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


The naive implementation leaves nearly all the hardware idle. For a batch of 32 rows, you launch 32 work-items total regardless of how wide each row is, with the GPU's remaining compute units sitting unused.


The solution is to assign **multiple work-items per row** and use **parallel reductions** to compute the max and norm. This is the same reduction pattern from lecture, now applied to softmax.


You will implement everything in :code:`PA8/opencl_functions/opencl-functions.cpp` and :code:`PA8/opencl_functions/softmax.cl`.


**Brief Explanation of Parallel Reduction**


Reduction is a fundamental parallel primitive: given N inputs, produce 1 output (a max, a sum, etc.) in O(log N) steps rather than O(N). The pattern is:


1. Load all values into **local (shared) memory**
2. Each step, active work-items compare or combine values at a fixed stride, writing results back to local memory
3. Halve the stride and repeat until one value remains


For N=16 with 8 work-items, finding the max proceeds like this:


.. code-block:: none


   Input:  [-5, 2, -7, 1, -3, -2, 7, 6, -4, 0, 3, 5, -6, 4, -8, -1]


   Step 1, Stride 8:  8 work-items compare [i] vs [i+8]
   Result: [-4, 2, 3, 5, -3, -2, 7, 6, ...]


   Step 2, Stride 4:  4 work-items compare [i] vs [i+4]
   Result: [-3, -2, 7, 6, ...]


   Step 3, Stride 2:  2 work-items compare [i] vs [i+2]
   Result: [7, 6, ...]


   Step 4, Stride 1:  1 work-item compares [0] vs [1]
   Result: [7]  <- max of entire row


The exact same pattern applies for the norm reduction, just replace ``max`` with ``+``.


**Online Softmax (Optional 2-Pass Optimization)**


Before jumping to full parallelism, note that the naive 3-pass approach can be reduced to 2 passes using the **online softmax** technique. Instead of a separate max pass and norm pass, you can merge them into a single traversal by maintaining a running correction.


As you scan left to right, keep a running max ``m`` and running norm ``d``. When a new element updates the max from ``m_old`` to ``m_new``, correct the existing norm using the exponential multiplication property:


.. math::


   e^a \cdot e^b = e^{a+b}


Specifically: ``d_new = d_old * exp(m_old - m_new) + exp(z_i - m_new)``


This gives you the correct norm in one pass without revisiting elements. It is a great sequential optimization and extends naturally into the parallel setting when combining partial results across work-items.
**Pseudocode for the Full Parallel Softmax**


Below is the pseudocode for this implementation:


// Step 1: each work-item loads its element(s), coarsening if N > wg_size
   local_mem[local_id] = max of assigned elements
   barrier()


   // Step 2: parallel reduction for max
   for stride = wg_size/2 ... 1:
       local_mem[local_id] = max(local_mem[local_id], local_mem[local_id + stride])
       barrier()
   max_val = local_mem[0]


   // Step 3: each work-item computes its partial norm
   local_mem[local_id] = sum of exp(input[row][i] - max_val) for assigned elements
   barrier()


   // Step 4: parallel reduction for norm
   for stride = wg_size/2 ... 1:
       local_mem[local_id] += local_mem[local_id + stride]
       barrier()
   norm = local_mem[0]


   // Step 5: each work-item writes its output element(s)
   output[row][i] = exp(input[row][i] - max_val) / norm


**Softmax Optimizations**


There is significant design space here, and this is where leaderboard points are won or lost. Consider the following when designing your kernel:


* What to parallelize? Max, norm, softmax, some, all?
* How to best combine reductions? Merge passes, online, ...?
* How to create work-items and work-groups? Number of work-items per row, number of rows per work-group, ...
* How to use local memory? Sharing reduction data; doing both max and norm simultaneously requires more local memory. Is the tradeoff worth it?
* Coalescing! Always an important factor, regardless of application


You are free to use any tools from `CLBlast <https://urldefense.com/v3/__https://github.com/CNugteren/CLBlast/blob/master/doc/api.md__;!!Mih3wA!BbbeGZ9w0lPUmYfVLI0XlbTAPOv8nqHfOT40OyuXuBP-r9yWIbVfkZDd7a3buNc_Dalz1pHkFIQdR2J_FWs$ >`__ that you wish.


Note that some devices (including the Qualcomm Adreno 643) impose limits on the maximum size of a single work dimension. There may be cases where it makes sense to split your NDRange across an extra dimension. Keep this in mind when configuring your kernel launch.


How to Compile
^^^^^^^^^^^^^^^^^^^^^^


The :code:`PA8/opencl_functions/opencl-functions.cpp` and :code:`PA8/opencl_functions/softmax.cl` files contain the code for the programming assignment. It can be run by typing :code:`make run` from the PA8 folder.


How to Test
^^^^^^^^^^^^^^^^^^^^^^


Use the :code:`make run` command to test your program, which will run :code:`python3 test.py`. This checks your softmax output against PyTorch's ``torch.nn.functional.softmax`` across a variety of batch sizes and vector lengths. All tests must pass. If any test fails on the Qualcomm Adreno 643, you will not be placed on the leaderboard.


Grading
^^^^^^^^^^^^^^^^^^^^^^


You will get up to 90 points if your algorithm is correct on CPU. If you score more than 75 points, you will get additional points for your Qualcomm Adreno 643 execution time based on leaderboard placement. Note the leaderboard is considered frozen at 11:59pm on the deadline date. Submissions afterwards will be removed from the leaderboard:


* +5 points (Top 50)
* +4 points (51 - 100)
* +3 points (101 - 150)
* +2 points (151 - 200)
* +1 point (201 - 250)


Leaderboard positions above 250 will receive no additional points. Note all tests must be correct. If one test fails on the Qualcomm Adreno 643, you will not be placed on the leaderboard.


Submission
^^^^^^^^^^^^^^^^^^^^^^


Submit the :code:`PA8/opencl_functions/opencl-functions.cpp` and :code:`PA8/opencl_functions/softmax.cl` files on gradescope.