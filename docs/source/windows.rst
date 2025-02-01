=====================
Developing on Windows
=====================
Introduction
^^^^^^^^^^^^
This document is a work in progress and is not yet complete.

This guide is focused on running OpenCL on Windows 11 x64.
These instructions may be different for other versions.

Installing the SDK
^^^^^^^^^^^^^^^^^^
TODO

Hardware Specific Considerations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
There are multiple different OpenCL drivers that allow you to run OpenCL on your hardware.
We will look at Nvidia and x86_64. You may have other drivers on your machine.

You can run it with `clinfo.exe`.  If you have results, you already have an OpenCL compatible driver installed.

x86_64
++++++
If you do not have any other hardware available, you can still execute OpenCL directly on your CPU.
To do so, you can install the Intel OneAPI.  This will run on both AMD and Intel CPUs.

You can obtain it from here: `Intel OneAPI OpenCL Drivers <https://www.intel.com/content/www/us/en/developer/articles/tool/opencl-drivers.html>`.

Once you have these installed, try `clinfo` again and confirm you have devices.

WSL
^^^
On Windows, you can also enable WSL. In order to setup WSL, review the Ubuntu documentation on the left-hand side.