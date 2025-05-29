RB3 Board Setup Guide: Ubuntu Installation and OpenCL Configuration (Windows)
=============================================================================

.. note::
    This guide is compiled using the official Qualcomm documentation. If you need 
    further guidance, please refer to: `Qualcomm Documentation <https://docs.qualcomm.com/bundle/publicresource/topics/80-82645-1/Integrate_and_flash_software_2.html#panel-0-V2luZG93cyBob3N0>`_.

Prerequisites
^^^^^^^^^^^^^
Before you begin, you will need:

* A Windows machine (Ubuntu recommended)
* A Qualcomm RB3 development board
* 12V power supply for the RB3 board
* USB Type-C cable

.. note::
    The RB3 board, power supply, and USB cable should all be included in the RB3 box.

Windows Installation
^^^^^^^^^^^^^^^^^^^^

QCS and PuTTY Setup
-------------------
Start by downloading `Qualcomm Software Center <https://softwarecenter.qualcomm.com/>`_.

After installing QSC, download Qualcomm USB Driver (QUD), Qualcomm Product Configuration Assistant Tool (PCAT), and Qualcomm Unified Tools Services (UTS).

.. note::
    Each driver can be found by typing in the tool's acronym in the search bar.


.. image:: /image/Tool-Installation.png
  :width: 800
  :alt: Driver installation

Installation can be verified by running the below in Terminal / Power Shell:

.. code-block:: bash

  pcat

Download Required Files
-----------------------
Visit Canonical® `Ubuntu on Qualcomm <https://ubuntu.com/download/qualcomm-iot>`_ IoT website.

Download the following files from `Download Ubuntu Server 22.04 for QCS6490`.
* rawprogram0.xml
* ubuntu-22.04-preinstalled-server-arm64+rb3g2-x08.img.xz	

Download the following files from ``Download boot firmware``:
* QLI.1.x-Ver.1.x-ubuntu-nhlos-bins.tar.gz

.. image:: /image/Ubuntu-download.png
  :width: 800
  :alt: Ubuntu install

Create a directory for the flashable images. For example ``rb3_ubuntu_images``.

Extract the boot firmware package (for example, ``QLI.1.2-Ver.1.1-ubuntu-nhlos-bins.tar.gz``) to the ``rb3_ubuntu_images`` directory.

.. important::
  Replace the extracted ``rawprogram0.xml`` file in the ``rb3_ubuntu_images`` directory with the one provided in the Canonical release and remove ``patch0.xml`` from ``rb3_ubuntu_images`` if it exists.
.. note::
  If you are copying the code for ``rawprogram0.xml`` rather than downloading it, please add ``<?xml version="1.0" ?>`` to the first line of the ``rawprogram0.xml``.

Extract ``ubuntu-22.04-preinstalled-server-arm64+rb3g2-x08.img.xz`` and copy ``ubuntu-22.04-preinstalled-server-arm64+rb3g2-x08.img`` into the ``rb3_ubuntu_images`` directory.

Enter EDL Mode
--------------
Enter `EDL <https://docs.qualcomm.com/bundle/publicresource/topics/80-70015-253/windows_host.html#edl-mode>`_ mode in the Windows host (this step is a little bit tricky as it will require you to hold the ``F_DL`` button while inserting the power and USB Type-C connecter):

.. image:: /image/fld_and_connectors.png
  :width: 800
  :alt: EDL mode

1. Press and hold the ``F_DL`` button
2. While holding the ``F_DL`` button connect the device to a 12-V wall power supply and USB Type-C connector
3. Release the ``F_DL`` button. The RB3 should now be showing up on QCS as a connected device (in EDL mode) and should also show up using ``pcat -devices`` (which will also show the device's serial number).

.. image:: /image/pcat-devices.png
  :width: 800
  :alt: PCAT serial

.. note::
  The home page of QSC will also show the device if it is in EDL mode. This is not necessary, but is helpful for checking the status of the RB3 device.

Flashing Ubuntu onto RB3
------------------------
Flash the Ubuntu image to the RB3:

.. code-block:: bash

    PCAT -PLUGIN SD -DEVICE <SERIAL NUMBER> -BUILD "<extracted zip directory path>\\rb3_ubuntu_images" -MEMORYTYPE UFS -FLAVOR asic

An example input (without path to image directory):

.. code-block:: bash

    PCAT -PLUGIN SD -DEVICE 5BF17AD4 -BUILD "<extracted zip directory path>\\rb3_ubuntu_images" -MEMORYTYPE UFS -FLAVOR asic

.. note::
  The serial number for the device can be found using pcat -devices



Logging into RB3
----------------
Download `Putty <https://www.putty.org/>`_. Open `Device Manager`` and find the Port the RB3 is using:

.. image:: /image/com-port-pos.png
  :width: 800
  :alt: Port location

Connect Micro-USB port and 12-V power connector:

.. image:: /image/Micro-USB.png
  :width: 800
  :alt: Micro-USB location

Press and hold the power button for 2-5 seconds:

.. image:: /image/powerbutton.png
  :width: 800
  :alt: Power button location

Using Putty, put the connection type to Serial, set Serial line to the port your RB3 is using and set the Speed to ``115200``.

.. image:: /image/putty-connection.png
  :width: 800
  :alt: Putty connection

Press enter and you should be prompted to enter username and password. Both are defaulted to ``ubuntu``. Logging in the first time will prompt you to change the password for the RB3:

.. image:: /image/login.png
  :width: 800
  :alt: Ubuntu login

Network Setup
^^^^^^^^^^^^^
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
^^^^^^^^^^^^^^^^^^^^
Now you can set up OpenCL on your RB3 board.

Building clinfo
---------------
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
--------------
Run ``clinfo`` to verify that OpenCL is working correctly:

.. code-block:: bash

    clinfo

This should display information about the OpenCL platforms and devices available on your RB3 board.

Running OpenCL Examples
^^^^^^^^^^^^^^^^^^^^^^^

Transferring Files to RB3
-------------------------
To copy files from your host computer to the RB3 board:

.. code-block:: bash

    # On your host computer
    scp /path/to/OpenCL_SDK.zip ubuntu@RB3_IP_ADDRESS:/home/ubuntu/

Replace ``RB3_IP_ADDRESS`` with the actual IP address of your RB3 board.

You can download the Adreno OpenCL SDK from:
`Qualcomm Adreno OpenCL SDK <https://qpm.qualcomm.com/#/main/tools/details/Adreno_OpenCL_SDK>`_

Assignment Notes
^^^^^^^^^^^^^^^^
When working on assignments, make sure the Makefile paths are correctly set:

.. code-block:: makefile

    else ifeq ($(shell uname -o), GNU/Linux)
        LDFLAGS  += -L/usr/lib -lOpenCL
        INCFLAGS += -I$(HOME)/OpenCL-Headers

This makes sure your OpenCL applications can find the necessary libraries and header files.