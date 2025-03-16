PA9 - Implicit GEMM Convolution
===============================

Introduction
------------
In this assignment, you’ll implement an implicit GEMM-based convolution from scratch. Unlike explicit methods (like im2col), implicit GEMM avoids materializing large intermediate matrices, reducing memory usage while maintaining high computational efficiency. This technique is fundamental to how modern deep learning frameworks accelerate convolutions behind the scenes.

By the end of this assignment, you’ll have hands-on experience with:

    Mapping convolution operations to implicit GEMM formulations
    Optimizing memory access patterns for speed and efficiency
    Appreciating the magic of matrix multiplications without blowing up your memory footprint

And if you ever feel overwhelmed—don’t worry. We’re never gonna give you up, never gonna let you down, never gonna run around and desert you.

(Yes, this is exactly what you think it is. Here’s your totally serious technical [resource](https://www.youtube.com/embed/dQw4w9WgXcQ). You’re welcome.)

Now that we’ve got that out of the way, let’s get to work and make some fast convolutions happen!