RB3 Board Setup Guide: Ubuntu Installation and OpenCL Configuration
==========================================

.. note::
    This guide is compiled using the official Qualcomm documentation. If you need 
    further guidance, please refer to: `Qualcomm Documentation <https://docs.qualcomm.com/bundle/publicresource/topics/80-82645-1/Integrate_and_flash_software_2.html?product=1601111740057201>`_.
    `RB3 Quick Setup Guide <https://docs.qualcomm.com/bundle/publicresource/topics/80-70015-253/ubuntu_host.html#edl-mode>`_.

.. important::
    This guide is specifically for Linux machines. For Windows users, please follow 
    the Qualcomm instructions `here <https://docs.qualcomm.com/bundle/publicresource/topics/80-82645-1/Integrate_and_flash_software_2.html?product=1601111740057201#panel-0-V2luZG93cyBob3N0>`_ 
    to install QUTS/PCAT/Qualcomm USB drivers before flashing Ubuntu.

Prerequisites
^^^^^^^^^^^^
Before you begin, you will need:

* A Linux machine (Ubuntu recommended)
* A Qualcomm RB3 development board
* 12V power supply for the RB3 board
* USB Type-C cable

.. note::
    The RB3 board, power supply, and USB cable should all be included in the RB3 box.

Ubuntu Installation
^^^^^^^^^^^^^^^^^^

Workspace Setup
--------------
Start by creating a workspace directory to organize your files:

.. code-block:: bash

    mkdir rb3
    cd rb3

Download Required Files
----------------------
Download the Ubuntu Server 22.04 image and boot files:

.. code-block:: bash

    # Download boot image
    wget https://artifacts.codelinaro.org/artifactory/qli-ci/flashable-binaries/ubuntu-fw/QLI.1.2-Ver.1.1-ubuntu-nhlos-bins.tar.gz

    # Download Ubuntu Server image
    wget https://people.canonical.com/~platform/images/qualcomm-iot/rb3-22.04/rb3-server-22.04-x08/ubuntu-22.04-preinstalled-server-arm64+rb3g2-x08.img.xz

    # Download checksums and manifest files
    wget https://people.canonical.com/~platform/images/qualcomm-iot/rb3-22.04/rb3-server-22.04-x08/ubuntu-22.04-preinstalled-server-arm64+rb3g2-x08.img.xz.sha256sum
    wget https://people.canonical.com/~platform/images/qualcomm-iot/rb3-22.04/rb3-server-22.04-x08/ubuntu-22.04-preinstalled-server-arm64+rb3g2-x08.manifest
    wget https://people.canonical.com/~platform/images/qualcomm-iot/rb3-22.04/rb3-server-22.04-x08/ubuntu-22.04-preinstalled-server-arm64+rb3g2-x08.manifest.sha256sum
    wget https://people.canonical.com/~platform/images/qualcomm-iot/rb3-22.04/rb3-server-22.04-x08/rawprogram0.xml

For more information, refer to the `Qualcomm Ubuntu Host Build Guide <https://docs.qualcomm.com/bundle/publicresource/topics/80-82645-1/build-on-ubuntu-host.html>`_.

Extract and Prepare Files
------------------------
Create a directory for the image files and prepare them:

.. code-block:: bash

    # Create directory for Ubuntu images
    mkdir rb3_ubuntu_images

    # Extract boot image to the directory
    tar xvf QLI.1.2-Ver.1.1-ubuntu-nhlos-bins.tar.gz -C ./rb3_ubuntu_images

    # Copy rawprogram0.xml to the directory
    cp rawprogram0.xml ./rb3_ubuntu_images

    # Remove patch0.xml if it exists
    rm rb3_ubuntu_images/patch0.xml 2>/dev/null

    # Verify checksum
    sha256sum -c ubuntu-22.04-preinstalled-server-arm64+rb3g2-x08.img.xz.sha256sum

    # Extract the OS image
    unxz ubuntu-22.04-preinstalled-server-arm64+rb3g2-x08.img.xz

    # Copy OS image to the directory
    cp ubuntu-22.04-preinstalled-server-arm64+rb3g2-x08.img ./rb3_ubuntu_images

Compile Flash Tool
-----------------
The QDL tool is needed to flash the device:

.. code-block:: bash

    # Clone QDL repository
    git clone https://github.com/linux-msm/qdl.git

    # Install dependencies
    sudo apt-get install libxml2-dev libudev-dev

    # Build QDL
    cd qdl
    make

    # Copy QDL to image directory
    cp qdl ./../rb3_ubuntu_images
    cd ..

Setup udev Rules
---------------
Configure udev rules to recognize the device in EDL mode:

.. code-block:: bash

    # update udev rules
    cd /etc/udev/rules.d
    sudo vi 51-qcom-usb.rules
    # and add the following content to the file:
    SUBSYSTEMS=="usb", ATTRS{idVendor}=="05c6", ATTRS{idProduct}=="9008", MODE="0666", GROUP="plugdev"
    # restart udev
    sudo systemctl restart udev

For more information, refer to the `Qualcomm EDL Mode documentation <https://docs.qualcomm.com/bundle/publicresource/topics/80-70015-253/ubuntu_host.html#edl-mode>`_.

Enter EDL Mode
-------------
Follow these steps to put the RB3 board into Emergency Download (EDL) mode:

1. Press and hold the F_DL button on the RB3 board
2. Connect the 12V power supply to the board
3. Connect the board to your computer using the USB Type-C cable
4. Release the F_DL button

Verify the board is in EDL mode:

.. code-block:: bash

    lsusb

You should see output similar to::

    Bus 002 Device 003: ID 05c6:9008 Qualcomm, Inc. Gobi Wireless Modem (QDL mode)

Flash the Device
---------------
Now flash Ubuntu to the RB3 board:

.. code-block:: bash

    cd rb3_ubuntu_images
    ./qdl prog_firehose_ddr.elf rawprogram*.xml patch*.xml

A successful flash operation will show output similar to this::

    waiting for programmer...
    flashed "disk" successfully at 102240kB/s
    flashed "xbl_a" successfully
    flashed "xbl_config_a" successfully
    flashed "PrimaryGPT" successfully
    flashed "BackupGPT" successfully
    flashed "PrimaryGPT" successfully
    flashed "BackupGPT" successfully
    flashed "PrimaryGPT" successfully
    flashed "BackupGPT" successfully
    flashed "aop_a" successfully
    flashed "dtb_a" successfully at 65536kB/s
    flashed "xbl_ramdump_a" successfully
    flashed "uefi_a" successfully
    flashed "tz_a" successfully
    flashed "hyp_a" successfully
    flashed "devcfg_a" successfully
    flashed "qupfw_a" successfully
    flashed "uefisecapp_a" successfully
    flashed "imagefv_a" successfully
    flashed "shrm_a" successfully
    flashed "multiimgoem_a" successfully
    flashed "cpucp_a" successfully
    flashed "toolsfv" successfully
    flashed "PrimaryGPT" successfully
    flashed "BackupGPT" successfully
    flashed "PrimaryGPT" successfully
    flashed "BackupGPT" successfully
    65 patches applied
    partition 1 is now bootable

This indicates that all necessary partitions have been successfully flashed and the device is ready to boot Ubuntu.

Network Setup
^^^^^^^^^^^^
After Ubuntu is installed and running on your RB3 board, set up a network connection to work with your board more easily:

.. code-block:: bash

    # List available WiFi networks
    sudo nmcli device wifi list

    # Connect to a WiFi network
    sudo nmcli device wifi connect "NETWORK_NAME" password "PASSWORD"

    # For open networks like UCSD-GUEST
    sudo nmcli device wifi connect UCSD-GUEST

    # Setup SSH server for file transfer
    sudo apt install openssh-client
    sudo systemctl start ssh 
    sudo systemctl enable ssh

    # Find your board's IP address
    ip -4 addr

OpenCL Configuration
^^^^^^^^^^^^^^^^^^^
Now you can set up OpenCL on your RB3 board.

Building clinfo
--------------
The ``clinfo`` utility displays information about available OpenCL platforms:

.. code-block:: bash

    # Clone required repositories
    git clone https://github.com/Oblomov/clinfo
    git clone https://github.com/KhronosGroup/OpenCL-Headers

    # Set environment variables
    export LD_LIBRARY_PATH="/usr/lib:/usr/lib/aarch64-linux-gnu:/system/vendor/lib64:/system/lib64"
    export CFLAGS="-I$HOME/OpenCL-Headers"
    export LDFLAGS="-L/usr/lib"

    # Install build dependencies
    sudo apt install build-essential

    # Build clinfo
    cd ~/clinfo
    make

    # Test if clinfo works
    ./clinfo

    # Install clinfo to system path
    sudo cp clinfo /usr/bin/clinfo

Testing OpenCL
-------------
Run ``clinfo`` to verify that OpenCL is working correctly:

.. code-block:: bash

    clinfo

This should display information about the OpenCL platforms and devices available on your RB3 board.

Running OpenCL Examples
^^^^^^^^^^^^^^^^^^^^^

Transferring Files to RB3
------------------------
To copy files from your host computer to the RB3 board:

.. code-block:: bash

    # On your host computer
    scp /path/to/OpenCL_SDK.zip ubuntu@RB3_IP_ADDRESS:/home/ubuntu/

Replace ``RB3_IP_ADDRESS`` with the actual IP address of your RB3 board.

You can download the Adreno OpenCL SDK from:
`Qualcomm Adreno OpenCL SDK <https://qpm.qualcomm.com/#/main/tools/details/Adreno_OpenCL_SDK>`_

Assignment Notes
^^^^^^^^^^^^^^^
When working on assignments, make sure the Makefile paths are correctly set:

.. code-block:: makefile

    else ifeq ($(shell uname -o), GNU/Linux)
        LDFLAGS  += -L/usr/lib -lOpenCL
        INCFLAGS += -I$(HOME)/OpenCL-Headers

This makes sure your OpenCL applications can find the necessary libraries and header files.