===================
Developing on macOS
===================

Introduction
------------
This guide is based off of the instructional team's experience running OpenCL on an Apple Silicon Mac.
**OpenCL is deprecated on macOS**, meaning Apple no longer officially supports it.
However, macOS still ships with working OpenCL drivers and headers.
As a result, it is currently possible to run OpenCL on a Mac GPU.
This document contains a series of modifications that may be made to PAs to run on macOS.
**You should still know how to build OpenCL programs on an officially supported platform, such as the DSMLP**
as Apple may remove support at an time.
Some of these modifications may show up in released PAs, but they are not garuanteed to be present.

Platform Specific Compilation
-----------------------------

To ensure your code works on multiple platforms, you should use C preprocessor if statements
to compile different code depending on the platform::

    #ifdef __APPLE__ 
    // code that works macOS
    // ..
    #else 
    // code that works elsewhere
    // ..
    #endif

The OpenCL Header File
----------------------

If you have installed xcode command line tools, you probably already have the header, ``cl.h``.
It will likely be somewhere in::

    ./Library/Developer/CommandLineTools/SDKs
    ./System/Volumes/Data/Library/Developer/CommandLineTools/SDKs

For each of these paths, try searching the header::

    find <root_path> -name cl.h

If the header is missing, you can get the OpenCL framework through the xcode command line tools: ``xcode-select --install``.

The ``cl.h`` header file is in a different location on macOS.
For any files that require the header, use the following conditional compilation clause::

    #ifdef __APPLE__ 
    #include <OpenCL/cl.h>
    #else 
    #include <CL/cl.h>
    #endif


Makefiles
---------

Instead of linking the OpenCL library, you want to use link the framework::

    # this if statement is true on macOS
    ifeq ($(shell uname -s),Darwin)
        LDFLAGS = -framework OpenCL
    else
        LDFLAGS = -L/usr/local/cuda/lib64 -lOpenCL
    endif

Additionally, the helper library uses the ``ar`` command line tool.
This tool is used to generate a the shared ``helper_lib.a`` static library.
It should come with macOS, but its usage is slightly different than on Linux.
You should remove the `-o` flag to get it to work on macOS.::

    # Linux
    ar rcs -o $@ $(OBJECTS)
    # macOS
    ar rcs $@ $(OBJECTS)

Older OpenCL
------------

macOS supports OpenCL 1.2
Programming assignments are written with a higher version in mind.
In particular, the ``clCreateCommandQueueWithProperties`` requires OpenCL 2.0
On macOS, you must use the deprecated ``clCreateCommandQueue`` function::

    // Create a command queue
    # if __APPLE__
        queue = clCreateCommandQueue( /* args here */ );
    # else
        queue = clCreateCommandQueueWithProperties( /* args here */ );
    # endif