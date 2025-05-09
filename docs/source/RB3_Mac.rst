RB3 Board Setup Guide: Ubuntu Installation and OpenCL Configuration
=====================================================================

.. note::
    This guide is compiled using the official Qualcomm documentation. If you need 
    further guidance, please refer to: `Qualcomm Documentation <https://docs.qualcomm.com/bundle/publicresource/topics/80-82645-1/Integrate_and_flash_software_2.html?product=1601111740057201>`_

.. important::
    This guide is specifically for macOS. For other users, please follow the instructions on the RB3 Board Setup Guide:

Prerequisites
^^^^^^^^^^^^^^
Before you begin, you will need:

* A personal computer running macOS
* A Qualcomm RB3 development board
* 12V power supply for the RB3 board
* USB Type-C cable
* USB to USB-C Adpater (if needed)

.. note::
    The RB3 board, power supply, and USB cable should all be included in the RB3 box.

   
Setting Up Virtual Machine on macOS
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Install UTM on macOS
---------------------

Visit the official `UTM website <https://mac.getutm.app/>`_: 

Click  **Download** to download and install the latest version of UTM.

Open the downloaded UTM file and follow the installation instructions.

Once installed, open UTM and follow the steps below to create a Linux virtual machine.

Create a Linux Virtual Machine
------------------------------

Visit the `UTM gallery <https://mac.getutm.app/gallery/ubuntu-20-04>`_:  

Download the **Ubuntu 22.04** UTM VM

In the UTM app, click "+" > "Virtualize" > "Linux".
Select the downloaded Ubuntu ISO and your downloaded UTM Virtual Machine should be shown on the left side of the UTM app.

In UTM, select the VM > "Settings" > "Input".
Set "USB Support" to `USB 3.0 (XHCI)`.
Enable "Share USB device from host".
Click "Save".

Start the VM by clicking the play button in UTM

.. note::
      The display might take a little bit to show up, so please be patient.


Oncw the VM is started, you ahould see the Ubuntu login screen.

The default username is "ubuntu" and the password is also "ubuntu".

Open the terminal 

**The following steps will be done in the UTM VM Terminal**

Ubuntu Installation 
^^^^^^^^^^^^^^^^^^^^^^

Workspace Setup
----------------
Start by creating a workspace directory to organize your files:

.. code-block:: bash

    mkdir rb3
    cd rb3

Download Required Files
------------------------
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
---------------------------
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
---------------------
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
------------------
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
-----------------
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
-----------------
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

Logging in to Ubuntu
^^^^^^^^^^^^^^^^^^^^^^
After flashing, the RB3 board will boot into Ubuntu.

**Switch to using the terimal on you host machine - the macOS device**

There are two ways to access the system:

1. **Serial Console**: Connect to the board using a serial console on your host machine. The default baud rate is 115200.
2. **SSH**: Connect to the board over SSH using the IP address assigned by your network.

To connect via Serial Console follow these steps:

Plug the micro USB cable into the debug port on the RB3 board and USB end to your host machine.

.. note:: 
   If you cannot find the debug port please use this documentation: `Minicom Serial Console <https://docs.qualcomm.com/bundle/publicresource/topics/80-70015-253/ubuntu_host.html#set-up-debug-uart>`_

Open a terminal and run the following command to make sure the device is recognized:

.. code-block:: bash

    ls /dev/tty.* /dev/cu.*

You should see a device like `/dev/cu.usbserial-DP06OGHE`. If you don't see it, make sure the cable is connected properly.

.. code-block:: bash

    screen /dev/cu.usbserial-DP06OGHE 115200

A blank screen should appear. Wait one minute, then press Enter to get the login prompt.

If you see the login prompt, you are successfully connected to the RB3 board.


To connect via SSH, you can use the following command:

.. code-block:: bash

    ssh ubuntu@RB3_IP_ADDRESS

Replace ``RB3_IP_ADDRESS`` with the actual IP address of your RB3 board.

If you are using the serial console, please hit enter to get the login prompt. The default username and password are:

.. code-block:: bash

    Username: ubuntu
    Password: ubuntu

If you are using SSH, the default username and password are the same. You will be prompted to change the password on first login.


Network Setup
^^^^^^^^^^^^^^
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
^^^^^^^^^^^^^^^^^^^^^^
Now you can set up OpenCL on your RB3 board.

Building clinfo
-----------------
The ``clinfo`` utility displays information about available OpenCL platforms:

.. code-block:: bash

    # Install required packages
    sudo add-apt-repository ppa:ubuntu-qcom-iot/qcom-ppa
    sudo apt update
    sudo apt install gstreamer1.0-qcom-sample-apps weston-qcom

    # Try running the find command to see if you find the OpenCL library
    sudo find / -name libOpenCL.so

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
----------------
Run ``clinfo`` to verify that OpenCL is working correctly:

.. code-block:: bash

    clinfo

This should display information about the OpenCL platforms and devices available on your RB3 board.

Running OpenCL Examples
^^^^^^^^^^^^^^^^^^^^^^^^^

Transferring Files to RB3
-----------------------------
To copy files from your host computer to the RB3 board:

.. code-block:: bash

    # On your host computer
    scp /path/to/OpenCL_SDK.zip ubuntu@RB3_IP_ADDRESS:/home/ubuntu/

Replace ``RB3_IP_ADDRESS`` with the actual IP address of your RB3 board.

You can download the Adreno OpenCL SDK from:
`Qualcomm Adreno OpenCL SDK <https://qpm.qualcomm.com/#/main/tools/details/Adreno_OpenCL_SDK>`_

Assignment Notes
^^^^^^^^^^^^^^^^^^
When working on assignments, make sure the Makefile paths are correctly set:

.. code-block:: makefile

    else ifeq ($(shell uname -o), GNU/Linux)
        LDFLAGS  += -L/usr/lib -lOpenCL
        INCFLAGS += -I$(HOME)/OpenCL-Headers

This makes sure your OpenCL applications can find the necessary libraries and header files.