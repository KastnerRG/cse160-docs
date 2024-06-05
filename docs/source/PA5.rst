PA5 - Convolution
=================

.. figure:: /image/2D_Convolution_Animation.gif
    :align: center
    :alt: 2D Convolution GIF
*Credit: Wikipedia*

Objective
^^^^^^^^^
The lab's objective is to implement a tiled image convolution using both shared and constant memory. We will have a constant 5x5 convolution mask, but will have arbitrarily sized image (assume the image dimensions are greater than 5x5 for this Lab).

To use the constant memory for the convolution mask, you can first transfer the mask data to the device. Consider the case where the pointer to the device array for the mask is named M. You can use :code:`__constant float * M` as one of the parameters during your kernel launch. This informs the compiler that the contents of the mask array are constants and will only be accessed through pointer variable :code:`M`. This will enable the compiler to place the data into constant memory and allow the SM hardware to aggressively cache the mask data at runtime.

Convolution is used in many fields, such as image processing for image filtering. A standard image convolution formula for a 5x5 convolution filter :code:`M` with an Image :code:`I` is:

.. figure:: /image/convolution_formula.png
    :align: center
    :alt: Convolution Formula


where :math:`P_{i,j,c}` is the output pixel at position :code:`i,j` in channel :code:`c`, :math:`I_{i,j,c}` is the input pixel at :code:`i,j` in channel :code:`c` (the number of channels will always be 3 for this PA corresponding to the RGB values), and :math:`M_{x,y}` is the mask at position :code:`x,y`.

Input Data
^^^^^^^^^^
The input is an interleaved image of :code:`height x width x channels`. By interleaved, we mean that the the element :code:`I[y][x]` contains three values representing the RGB channels. This means that to index a particular element's value, you will have to do something like:

.. code-block:: c

    index = (yIndex*width + xIndex)*channels + channelIndex;

For this assignment, the channel index is 0 for R, 1 for G, and 2 for B. So, to access the G value of :code:`I[y][x]`, you should use the linearized expression :code:`I[(yIndex*width+xIndex)*channels + 1]`.

For simplicity, you can assume that :code:`channels` is always set to :code:`3`.


Instructions
^^^^^^^^^^^^^
Edit the code in the code tab to perform the following:

* Allocate device memory
* Copy host memory to device
* Initialize thread block and kernel grid dimensions
* Invoke OpenCL kernel
* Copy results from device to host
* Deallocate device memory
* Implement the tiled 2D convolution kernel with adjustments for channels
* Use shared memory to reduce the number of global accesses, handle the boundary conditions in when loading input list elements into the shared memory

Instructions about where to place each part of the code is demarcated by the :code:`//@@` comment lines.

Psuedo Code
^^^^^^^^^^^
A sequential pseudo code would look something like this:

.. code-block:: none

    maskWidth := 5
    maskRadius := maskWidth/2 # this is integer division, so the result is 2
    for i from 0 to height do
        for j from 0 to width do
            for k from 0 to channels
                accum := 0
                for y from -maskRadius to maskRadius do
                    for x from -maskRadius to maskRadius do
                        xOffset := j + x
                        yOffset := i + y
                        if xOffset >= 0 && xOffset < width &&
                            yOffset >= 0 && yOffset < height then
                            imagePixel := I[(yOffset * width + xOffset) * channels + k]
                            maskValue := K[(y+maskRadius)*maskWidth+x+maskRadius]
                            accum += imagePixel * maskValue
                        end
                    end
                end
                # pixels are in the range of 0 to 1
                P[(i * width + j)*channels + k] = clamp(accum, 0, 1)
            end
        end
    end

where :code:`clamp` is defined as

.. code-block:: c

    def clamp(x, lower, upper)
        return min(max(x, lower), upper)
    end

How to Compile
^^^^^^^^^^^^^^
The :code:`main.c` and :code:`kernel.cl` file contains the code for the programming assignment. There is a Makefile included which compiles it. It can be run by typing :code:`make` from the PA5 folder. It generates a :code:`solution` output file. During development, make sure to run the :code:`make clean` command before running :code:`make`.

How to Test
^^^^^^^^^^^
Use the :code:`make run` command to test your program. There are a total of 9 tests on which your program will be evaluated for (functional) correctness.

Dataset Generation (Optional)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
This will need to be updated

The dataset required to test the program is already generated. If you are interested in how the dataset is generated please refer to the :code:`dataset_generator.cpp` file. You may compile this file using the :code:`make dataset_generator` command and run the executeable using the command :code:`./dataset_generator`.

Extra Credit (Optional)
^^^^^^^^^^^^^^^^^^^^^^^
We have provided you an additional :code:`make run_big` you can execute for larger images and larger kernel sizes. If you successfully implement both cases, we will consider your execution time for the leaderboard. You can test your execution time locally by running :code:`make time`.

Submission
^^^^^^^^^^
Submit the :code:`main.c` and :code:`kernel.cl` file on gradescope. Preserve the file name before uploading to gradescope.

Tips and Tricks
^^^^^^^^^^^^^^^
After you understand how convolution works, I would recommend starting by implementing the embarrassingly parallel portion of convolution. Make sure the naive implementation works before going forward and attempting to incoporate shared memory. It will be extremely difficult to debug your shared memory portion if your basic convolution does not work. In terms of complexity, strategy 3 is the easiest and strategy 1 is the hardest.

.. figure:: /image/TilingStrategies.png
    :align: center
    :alt: Tiling Strategies