PA7 - Softmaxing the (Pytorch) Wheel [Draft]
===================================================================

Objective
---------
For the last(?) PA, we will be implementing softmax, a very common operation in ML applications (for example in attention!)

Since this is the last PA, you can implement this PA however you wish as long as you are using OpenCL kernels. 

The input is in the size (Batch_size, vector) and you must only implement softmax over each vector. 

Hints
-----
Since softmaxs include exponents, you may encounter numerical instablity issues. Consider how to address this when designing the PA. 

You are free to use any tools from clblast that you wish.

Some devices have limits to the max size you can make a single dimension. There maybe some cases it makes sense to use an extra dimension...

Grading
-------
You will be graded on your GPU execution time: 

\< TBD: 85 points

\< TBD: 90 points (Beat the TA solution)

You will get additional points for your Leaderboard placement. Note the Leaderboard is considered frozen at 11:59 on the deadline date. Submissions afterwards will be removed from the leaderboard:

* +5 points (Top 50)
* +4 points (50 - 100)
* +3 points (100 - 150)
* +2 points (150 - 200)
* +1 points (200 - 250)

Leaderboard positions above 250 will recieve no additional points.

Note all tests must be correct. If a single test case fails, either on GPU and on CPU, you will get an 0 for the assignment. 


Submission
^^^^^^^^^^^^^^^^^^^^^^

Submit the :code:`PA6/opencl_functions/opencl-functions.cpp` and :code:`PA6/opencl_functions/conv2d.cl` files on gradescope.