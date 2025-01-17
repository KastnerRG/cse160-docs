====================
Developing on Ubuntu
====================

Introduction
^^^^^^^^^^^^
This guide is focused on running OpenCL on Ubuntu 24.04.
These instructions may be different for other distributions.

Hardware Specific Considerations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
There are multiple different OpenCL drivers that allow you to run OpenCL on your hardware.
We will look at Nvidia and x86_64. You may have other drivers on your machine.

To check, make sure you have the necessary packages installed.

.. code-block:: bash

    sudo apt-get update
    sudo apt-get install -y ocl-icd-libopencl1 clinfo

With these packages installed, run `clinfo`.
If you have results, you already have an OpenCL compatible driver installed.

x86_64
++++++
If you do not have any other hardware available, you can still execute OpenCL directly on your CPU.
To do so, you can install the Intel OneAPI.  This will run on both AMD and Intel CPUs.

.. code-block:: bash

    # download the key to system keyring
    wget -O- https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB \
    | gpg --dearmor | sudo tee /usr/share/keyrings/oneapi-archive-keyring.gpg > /dev/null
    # add signed entry to apt sources and configure the APT client to use Intel repository:
    echo "deb [signed-by=/usr/share/keyrings/oneapi-archive-keyring.gpg] https://apt.repos.intel.com/oneapi all main" | sudo tee /etc/apt/sources.list.d/oneAPI.list
    # install the packages for Intel OpenCL
    sudo apt-get update
    sudo apt-get -y install intel-oneapi-runtime-libs opencl-headers

Once you have these installed, try `clinfo` again and confirm you have devices.

Other Dependencies
^^^^^^^^^^^^^^^^^^
You also need a few development libraries installed to be able to develop for OpenCL.
You can installed them with the following CommandLineTools

.. code-block:: bash

    sudo apt-get update
    sudo apt-get install -y build-essential ocl-icd-opencl-dev ocl-icd-dev

Nvidia OpenCL on WSL
^^^^^^^^^^^^^^^^^^^^
Nvidia's OpenCL driver does not work correctly on WSL.
You can use POCL as a work around to get a Cuda-based OpenCL driver in WSL.
