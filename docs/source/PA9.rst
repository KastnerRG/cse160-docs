PA9 - Implicit GEMM Convolution
===============================

Introduction
------------
In this assignment, you'll implement an implicit GEMM-based convolution from scratch. Unlike explicit methods (like im2col), implicit GEMM avoids materializing large intermediate matrices, reducing memory usage while maintaining high computational efficiency. This technique is fundamental to how modern deep learning frameworks accelerate convolutions behind the scenes.

By the end of this assignment, you'll have hands-on experience with:

    * Mapping convolution operations to implicit GEMM formulations
    * Optimizing memory access patterns for speed and efficiency
    * Appreciating the magic of matrix multiplications without blowing up your memory footprint

Implementation Suggestions
------------
- Never give up
- Don't let the PA let you down
- There might be a bit of run around but don't desert it

Here's a `video <https://www.youtube.com/watch?v=dQw4w9WgXcQ>`_ that will explain how to do the PA. Good luck and you're welcome.

Now that we've got that out of the way, let's get to work and make some fast convolutions happen!
