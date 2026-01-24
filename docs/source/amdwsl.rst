============================================
Developing on AMD GPUs using VSCode with WSL
============================================

Introduction
^^^^^^^^^^^^

This guide will show you how to set up a development environment for CSE 160 on your own computer with an AMD GPU using
Visual Studio Code and Windows Subsystem for Linux (WSL).
WSL is a feature of Visual Studio Code that allows you to develop in an Linux containerized environment on Windows.
This means that you can develop on your own computer without having to install a Linux distribution on your computer.
This allows the usage of AMD acclerators (including some APUs) in a containerized enviornment on Windows.

This configuration is not officially supported by the course staff, and hardware compatibility depends on the AMD
driver, but we hope that it will be helpful to you.

.. important::
    This guide is for Windows systems only. For Linux systems, please follow
    `AMD's official guide on ROCm installation <https://rocm.docs.amd.com/projects/install-on-linux/en/latest/>`_.

.. note::
    Native AMD GPU support on macOS ended with Big Sur 11.4, use Boot Camp drivers for Windows instead.

WSL Installation
^^^^^^^^^^^^^^^^

Open Windows Powershell **as administrator** by right-clicking and selecting "Run as administrator".
Enter:

.. code-block:: Powershell

    wsl --install

.. note::
    The effect of ``wsl --install`` may vary depending on your system.
    After installation, a reboot is usually required before WSL distros can be installed.
    If those WSL components are already enabled, a reboot may not be required and an installation of the default Ubuntu
    distribution will be attempted.
    Read Microsoft documentation for more information on
    `installing WSL <https://learn.microsoft.com/en-us/windows/wsl/install>`_.

Install Ubuntu Noble by entering as administrator into Powershell:

.. code-block:: Powershell

    wsl --install Ubuntu-24.04

After installation, you can open Ubuntu instances by:

- Running the ``wsl -d <Distro>`` command in PowerShell
- Opening the dropdown in Windows Terminal
- Searching for Ubuntu in the Windows search bar

.. note::
    If installed for the first time, open the instance immediately after installation to complete the user setup process

.. important::
    Remember the Ubuntu user password as it will be needed during driver installation

AMD GPU driver installation
^^^^^^^^^^^^^^^^^^^^^^^^^^^

AMD Radeon Software installation
--------------------------------

To use ROCm in WSL, AMD Software: Adrenalin Edition or AMD Software: PRO Edition for WSL2 must be installed.
If the software is already installed, update it to the latest version. If not, download and install from:

- `AMD Software: Adrenalin Edition™ Application <https://www.amd.com/en/products/software/adrenalin.html>`_
- `AMD Software: PRO Edition <https://www.amd.com/en/products/software/pro-edition.html>`_

.. note::
    Only one of these software can be installed at the same time

AMDGPU driver in WSL
--------------------

.. warning::
    ROCm driver for WSL is quite sizable, make sure to have at least 30GiB of usable disk space before installation

Open Ubuntu 24.04 in WSL. Install AMD unified driver package repositories and installer script:

.. code:: bash

    sudo apt update
    wget https://repo.radeon.com/amdgpu-install/6.4.2.1/ubuntu/noble/amdgpu-install_6.4.60402-1_all.deb
    sudo apt install ./amdgpu-install_6.4.60402-1_all.deb

.. note::
    Using sudo in WSL will prompt to enter password, use the password set during the Ubuntu user setup process

Install AMD unified kernel-mode GPU driver, ROCm, and graphics. You can see a list of usecases by entering:

.. code:: bash

    sudo amdgpu-install --list-usecase

Install the driver with the desired uscases. For this course, the following will suffice:

.. code:: bash

    amdgpu-install -y --usecase=wsl,rocm,opencl --no-dkms

.. important::
    Do not install with Dynamic Kernel Module Support (dkms) in WSL.

Wait for the installation process to finish, this step may take serval minutes depending on your internet connection and
device performance.

Post-install verification
-------------------------

After the process has finished, verify that you can use the GPU by checking if GPU is listed as a ROCm agent:

.. code:: bash

    rocminfo

Example expected result:

.. code:: bash

    [...]
    *******
    Agent 2
    *******
      Name:                    gfx1100
      Marketing Name:          AMD Radeon RX 7900 XTX
      [...]
      Device Type:             GPU
      [...]
    [...]

.. note::
    Because ``dkms`` cannot be installed in WSL, ``amd-smi`` and ``rocm-smi`` will not be avaliable

Upgrade driver and modify usecases
----------------------------------

Upgrade the driver version or modify usecases by unstallating the amdgpu driver and installing the desired version.
See `Uninstallation`_.

Course specific dependencies installation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Run:

.. code:: bash

    sudo apt-get update
    sudo apt-get install -y build-essential git llvm-20 llvm-20-dev clang-20 libclang-20-dev libclang-cpp20-dev cmake pkg-config make ninja-build libhwloc-dev clinfo dialog apt-utils libxml2-dev vim gdb valgrind oclgrind python3-numpy

Run ``clinfo`` to verify that OpenCL is working correctly:

.. code-block:: bash

    clinfo

This should display information about the OpenCL platforms and devices available, you should see similar to the following:

.. code-block:: bash

    Number of platforms                               1
      Platform Name                                   AMD Accelerated Parallel Processing
      Platform Vendor                                 Advanced Micro Devices, Inc.
      Platform Version                                OpenCL 2.1 AMD-APP (3649.0)
      Platform Profile                                FULL_PROFILE
      Platform Extensions                             cl_khr_icd cl_amd_event_callback
      Platform Extensions function suffix             AMD
      Platform Host timer resolution                  1ns

      Platform Name                                   AMD Accelerated Parallel Processing
    Number of devices                                 1
      Device Name                                     gfx1100
      Device Vendor                                   Advanced Micro Devices, Inc.
      Device Vendor ID                                0x1002
      Device Version                                  OpenCL 2.0
      Driver Version                                  3649.0 (HSA1.1,LC)
      Device OpenCL C Version                         OpenCL C 2.0
      Device Type                                     GPU
      Device Board Name (AMD)                         AMD Radeon RX 7900 XT
      Device PCI-e ID (AMD)                           0x744c
      Device Topology (AMD)                           PCI-E, 0000:67:00.0
      Device Profile                                  FULL_PROFILE
      Device Available                                Yes
      Compiler Available                              Yes
      Linker Available                                Yes
    ...


Visual Studio Code integration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Install `Visual Studio Code <https://code.visualstudio.com/>`_ on the **Windows side** (do not install in WSL).

.. important::
    Note: When prompted to Select Additional Tasks during installation, be sure to check the **Add to PATH** option to
    open a folder in WSL using the ``code`` command.

Install the `WSL extension <https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl>`_ in VSCode.

Open Ubuntu in WSL, navigate to the desired directory, then enter:

.. code:: bash

    code .

VSCode WSL server will begin installation if not already, VSCode on Windows will then open the directory within WSL

Expected output:

.. code:: bash

    Installing VS Code Server for Linux x64
    Downloading: 100%
    Unpacking: 100%
    Unpacked 2202 files and folders to /home/<user>/.vscode-server/bin/<build>.
    Looking for compatibility check script at /home/<user>/.vscode-server/bin/<build>/bin/helpers/check-requirements.sh
    Running compatibility check script
    Compatibility check successful (0)

Hardware Compatibility Matrix
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Below are devices supported by ROCm version 6.4.2 for WSL at the time of writing and is subject to update

.. note::
    Devices not on the list may work, but are not officially supported by AMD and do not have functionality guarantee

AMD Radeon Pro
--------------

================================ ============ ===========
Name                             Architecture LLVM target
================================ ============ ===========
AMD Radeon AI PRO R9700          RDNA4        gfx1201
AMD Radeon AI PRO R9600D         RDNA4        gfx1200
AMD Radeon PRO W7900             RDNA3        gfx1100
AMD Radeon PRO W7900 (Dual Slot) RDNA3        gfx1100
AMD Radeon PRO W7800             RDNA3        gfx1100
AMD Radeon PRO W7800 48GB        RDNA3        gfx1100
AMD Radeon PRO W7700             RDNA3        gfx1101
================================ ============ ===========

AMD Radeon
----------

====================== ============ ===========
Name                   Architecture LLVM target
====================== ============ ===========
AMD Radeon RX 9070 XT  RDNA4        gfx1201
AMD Radeon RX 9070     RDNA4        gfx1201
AMD Radeon RX 9070 GRE RDNA4        gfx1201
AMD Radeon RX 9060XT   RDNA4        gfx1200
AMD Radeon RX 9060     RDNA4        gfx1200
AMD Radeon RX 7900 XTX RDNA3        gfx1100
AMD Radeon RX 7900 XT  RDNA3        gfx1100
AMD Radeon RX 7900 GRE RDNA3        gfx1100
AMD Radeon RX 7800 XT  RDNA3        gfx1101
====================== ============ ===========

AMD APU (Including PRO APUs)
----------------------------

===================== ============ ===========
Name                  Architecture LLVM target
===================== ============ ===========
AMD Ryzen AI Max+ 395 RDNA3.5      gfx1151
AMD Ryzen AI Max 390  RDNA3.5      gfx1151
AMD Ryzen AI Max 385  RDNA3.5      gfx1151
AMD Ryzen AI Max 380  RDNA3.5      gfx1151
===================== ============ ===========

Uninstallation
^^^^^^^^^^^^^^

Uninstall the ``amdgpu`` driver with:

.. code:: bash

    sudo amdgpu-uninstall

Uninstall Ubuntu WSL with:

.. code:: Powershell

    wsl --unregister Ubuntu-24.04
