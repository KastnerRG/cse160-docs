=======================================
Programming Assignment 1 - Device Query
=======================================

======
Part 1
======

Objective
^^^^^^^^^
The purpose of this programming assignment is to familiarize the student with the underlying hardware and how it relates to the OpenCL hardware model.  By extension, the program will familiarize the student with the processing resources at hand along with their capabilities.  By the end of this assignment, one should understand the process of compiling and running code that will be used in subsequent modules.



Instructions
^^^^^^^^^^^^
The file :code:`main.c` queries for devices across all platforms, and displays information about each device.

Some properties to pay attention to:

* Computational Capabilities
* Global Memory Size
* Shared Memory Size
* Work Item Size
* Work Item Dimensions
* Work Group Size
* Preferred Work Group Size Multiple

The student is encouraged to relate the device-specific information to the OpenCL memory model, provided below.

.. image:: /image/memory_model.jpg
  :width: 400
  :alt: OpenCL Memory model

*Credits: Khronos Group*


How to Run
^^^^^^^^^^
The :code:`main.c` file contains the host code for the programming assignment; there is no associated device kernel code for this assignment. There is a Makefile included which compiles it. It can be run by typing :code:`make` from the DeviceQuery folder. It generates a :code:`device_query` output file.  Simply run this with :code:`./device_query`, which will print device information to the console.

Submission
^^^^^^^^^^
You do not need to submit any code for this assignment. You must answer the questions in Gradescope.

======
Part 2
======

Objective
^^^^^^^^^

The second part of this assignment aims to contextualize parallelization and demonstrate
the benefits of heterogenous programming.  With access to multiple processing cores, 
multiple threads can be assigned to operate on independent tasks of a program, 
allowing parallelized programs to have massive benefits over their sequential counterparts.

The goal of this part of the assignment is to demonstrate the visible speedup that 
arises from a program running on one thread, to a program running in parallel on slightly more 
threads, and finally to a program that runs in parallel on many threads.

Context 
^^^^^^^

For a visually appealing example, the program chosen to desmonstrate parallelization
is that of a **raytracer**.  We first explore the high level overview of raytracer functionality
to understand why parallelization is a natural application for this program.

The high level concept of raytracing is derived from the idea of shooting "rays" into 
a virtual world and seeing what these rays hit.  One can imagine an eye shooting out 
into the world and being able to see whatever the ray hits.  In the case of ray tracing,
we have a "camera" (i.e. the eye) that produces rays starting from the eye position and 
going through pixels in a 2D screen.

.. image:: /image/lightingnoshadow.gif
  :width: 400
  :alt: Raytracing Diagram

*Credits: scratchapixel.com*

In the diagram above, the computer screen can be represented as a 2D grid of squares,
where each square represents a pixel on the screen.  A ray (labelled as primary ray) 
is shot from the position of the camera towards the center of the pixel. 

Such a ray is created for every pixel in the screen.  As such, the direction a ray goes
is determined by where the origin of the ray is (that is, where the eye is positioned) and
the coordinates of the pixel on the screen that the ray is shot through.  In other words,
*every primary ray is unique to the pixel it is sent through*.

On the other side of the screen is the virtual scene, composed of objects and lights.  
In the diagram above, we observe a singular object of a green sphere and a singular 
point light above it.

After the ray is created, it is sent into the virtual scene.  The purpose of the ray is
to probe the virtual scene.  The first object in the virtual scene that the ray 
hits, referred to as an *intersection*, determines what object is closest to the 
screen.  For simplicity, we first assume that the ray will simply track the first
object intersected.  As stated before, *every primary ray is unique to the pixel it is sent through*;
as such, we may draw the color of the object that was first intersected to the screen,
as an intersection of the object with the primary ray indicates that we can see the object.

In the diagram below, we can see that an intersection of a primary ray with the 
blue sphere in the scene results in blue being drawn to the pixel that the primary
ray goes through.

.. image:: /image/raytracerimage2.gif
  :width: 400
  :alt: Raytracing Diagram

*Credits: Graphic Speak*
