Rubik Pi 3 Board Setup Guide: Ubuntu Installation and OpenCL Configuration
==========================================================================
.. note::
    Start by flashing the board according to this documentation, do not use the start guide provided in the box.
    Expect setup, including download, to take around an hour.

.. note::
    This guide is compiled using the official Thundercomm documentation.
    If you need further guidance, please refer to: `Thundercomm Documentation <https://www.thundercomm.com/rubik-pi-3/en/docs/rubik-pi-3/en/docs/1.0.0-u>`_.

.. note::
    This guide is for Linux, Windows, and macOS systems; however, Qualcomm Launcher is currently only avaliable for Windows on X86 or ARM64, macOS on ARM64, and Linux with a Debian-based distribution.

.. important::
    A Type-C 12V 3A power adapter compliant with PD 3.0 is required for input power.
    The power indicator LED near the power port will turn on if the power adapter meets requirements and power negotiation succeeds.
    If the adapter does not meet requirements, the LED will remain off and the device will not boot.

Prerequisites
^^^^^^^^^^^^^
Before you begin, you will need:

* A host computer with an OS supported by Qualcomm Launcher
* A Thundercomm Rubik Pi 3 development board
* USB Type-C PD 3.0 compilant power supply
* USB Type-C PD 3.0 compilant cable for power supply
* USB 3.1 compatible Type-C cable to the host computer for flashing
* USB 2.0 to Micro-B cable for UART connection
* Accessible LAN via WiFi or Ethernet

.. important::
    Please make sure to discharge static electricity by touching a metal object first before touching the Rubik Pi every time to prevent damage.

.. note::
    The Rubik Pi does not support IEEE 802.11ax (WiFi 6) or 802.11be (WiFi 7).

Ubuntu Installation
^^^^^^^^^^^^^^^^^^^

Download Required Files
-----------------------
Download Qualcomm Launcher from `Qualcomm Software Center web portal <https://softwarecenter.qualcomm.com/catalog/item/Qualcomm_Launcher>`_ and install the launcher on your host machine.

.. note::
    On Linux hosts, Qualcomm Launcher v1.2.2 or later is required.

Open Qualcomm Launcher and select **Rubik Pi** as the development kit, and **Ubuntu** as the target OS.

.. figure:: https://www.thundercomm.com/rubik-pi-3/en/assets/images/Flashing_OS_NoDeviceConnected-0bb76bdccf3d91b71344a8910de03be9.png
    :align: center
    :alt: Qualcomm launcher home config

*Credits: Thundercomm*

Do not connect the board to your host computer yet.

Enter EDL Mode
--------------
EDL Mode is required to flash firmware and OS images to RubikPi 3 using Qualcomm's QDL tool. To Enter EDL mode, please disconnect everything from the board.

Press and hold the [EDL] button:

.. figure:: /image/RubikPi/RubikPiEDL.png
    :scale: 30%
    :alt: EDL button location

While continuing to hold the [EDL] button, connect the power supply into the [PWR] USB port:

.. figure:: /image/RubikPi/RubikPiPWR.png
    :scale: 30%
    :alt: PWR port location

While continuing to hold the [EDL] button, insert the Type-C cable into the [USB 3.1] port and connect to your host computer:

.. figure:: /image/RubikPi/RubikPiUSB.png
    :scale: 30%
    :alt: USB 3.1 port location

Wait three seconds to enter 9008 mode, then release the [EDL] button.

Flashing the board
------------------

The RUBIK Pi will be automatically detected by Qualcomm Launcher. Select the device and click Flash button to begin updating the Renesas USB firmware.

After successful USB firmware flashing, a dialog box will appear. Once the Launcher is waiting for user action to put the device into EDL mode again,
the dialog box will display exactly: *Waiting for EDL device*, as seen in the following screen:

.. figure:: https://www.thundercomm.com/rubik-pi-3/en/assets/images/Renesas_USB_firmware_flashing_completed_R-9c4eee492f90429747c3460a84d717cf.png
    :align: center
    :alt: Qualcomm launcher awaiting EDL

*Credits: Thundercomm*

Without closing Qualcomm Launcher, disconnect the device and place it into EDL mode again.
As soon as the device is placed into EDL mode, the flashing operation begins automatically. You will see the following screen:

.. figure:: https://www.thundercomm.com/rubik-pi-3/en/assets/images/OS_image_flashing_Progress-5544bef5da0e1e364be431eac5ecaf5d.png
    :align: center
    :alt: Qualcomm launcher flash OS image

*Credits: Thundercomm*

After the OS image is successfully flashed, the following confirmation screen will appear, and the LED on the board will flash bright green for around 2 seconds.

.. figure:: https://www.thundercomm.com/rubik-pi-3/en/assets/images/OS_image_flashing_completed-ff45bd2899b7b3e02bdb63f28a862f42.png
    :align: center
    :alt: Qualcomm launcher flash OS successful

*Credits: Thundercomm*

Configure the device
--------------------

Click Configure Login, the launcher will then prompt to setup UART connection.

.. note::
    If the MicroUSB COM port on the host system is currently in use by another tool (e.g., PuTTY, Tera Term), please close it before proceeding.

Without disconnecting any cable from the device, connect your host computer to the device with a USB Micro-B cable at the [DEBUG] port.

.. figure:: /image/RubikPi/RubikPiUART.png
    :scale: 30%
    :alt: DEBUG port location

Once the USB Micro-B cable is connected, a serial terminal will open.

.. note::
    This will take some time as the device boots up.

When asked, type in the default username and password:

* Username: ubuntu
* Password: ubuntu

.. important::
    The serial terminal does not support copy and pasting, please type in the username and password manually.

The terminal will ask you to reset the password immediately, type in the default password again when prompted, then set your password. **Save this password, you will not be able to retrieve it**.

The launcher will prompt you to configure the Wi-Fi once finished. Configure the Wi-Fi by entering the SSID and password, or connect the device to Ethernet.
Please make sure the network you are using allows you to access LAN devices.

Once connected, the launcher will display the device IP address and the ``ssh`` command to connect to the device. **Save this information**.


.. figure:: https://www.thundercomm.com/rubik-pi-3/en/assets/images/wi-fi_completed-6c17fb871952826a717480f620f4c29f.png
    :align: center
    :alt: Qualcomm launcher WiFi connect successful

*Credits: Thundercomm*

.. important::
    Please make sure to save the password and the IP address of the device, you will need these information to access it.
    They will not be avaliable again after this screen.

Click Finish Setup and verify that the setup process is complete.

OpenCL Installation
^^^^^^^^^^^^^^^^^^^
Now you can set up OpenCL on the Rubik Pi board.

Connect to Rubik Pi
-------------------

Open a terminal window on your host computer. Please use the ``ssh`` command displayed by the qualcomm launcher to connect to the Rubik Pi.

.. code-block:: bash

    ssh ubuntu@RP3_IP_ADDRESS

.. note::
    When connecting for the first time, the terminal may prompt:
    
        The authenticity of host '192.168.0.*' can't be established.
        ED25519 key fingerprint is SHA256:FINGERPRINT.
        This key is not known by any other names. Are you sure you want to continue connecting (yes/no/[fingerprint])?

    This is normal when conncting for the first time. However, if you see a big **WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!**,
    and you have not caused the board's fingerprint to change, you may be a victim of a man-in-the-middle attack. (This should be *very* unlikely, but it’s good to be aware of them.)

OpenCL Runtime Installation
---------------------------
OpenCL runtime should be pre-installed on the device, verify this by running:

.. code-block:: bash

    dpkg -L qcom-adreno1 | grep "libOpenCL"

Verify that ``libOpenCL.so.1`` and ``libOpenCL_adreno.so.1`` are present.

If it is missing, install the Qualcomm Adreno user space libraries from the package manager (``apt``).

.. code-block:: bash

    sudo apt-get update
    sudo apt-get install qcom-adreno1

.. note::
    Your account has root privileges by default, please practice caution with ``sudo`` commands.

Development Package Installation
--------------------------------
Install the following:

* Qualcomm Adreno GPU developer libraries in the ``qcom-adreno-dev`` package
* The ``clinfo`` utility to display information about available OpenCL platforms
* The ``build-essential`` and ``gdb`` packages for C development

They can be installed with:

.. code-block:: bash

    sudo apt-get update
    sudo apt-get upgrade
    sudo apt-get install qcom-adreno-dev clinfo build-essential gdb

Testing OpenCL
--------------
Run ``clinfo`` to verify that OpenCL is working correctly:

.. code-block:: bash

    clinfo

This should display information about the OpenCL platforms and devices available on the Rubik Pi, you should see the following to use the Adreno GPU on the SoC:

.. code-block:: bash

    Number of platforms                    1
    Platform Name                          QUALCOMM Snapdragon(TM)
    Platform Vendor                        QUALCOMM
    Platform Version                       OpenCL 3.0 QUALCOMM build: 0808.11
    Platform Profile                       FULL_PROFILE
    Platform Extensions                    cl_khr_icd
    Platform Extensions with Version       cl_khr_icd        0xc00000 (3.0.0)
    Platform Numeric Version               0xc00000 (3.0.0)
    Platform Extensions function suffix    QCOM
    Platform Host timer resolution     
    Platform Name                          QUALCOMM Snapdragon(TM)
    Number of devices                      1
    Device Name                            QUALCOMM Adreno(TM) 643
    ...

Vulkan Installation
^^^^^^^^^^^^^^^^^^^
Install the ``vulkan-tools`` package:

.. code-block:: bash
    sudo apt-get install vulkan-tools

Because Vulkan ICD loader interface version 5 is required for this version, but Qualcomm's divers only support interface version 3 at the moment,
you must downgrade the Vulkan library manually and exclude it from auto-updates as the packages are only avaliable in Ubuntu Jammy:

.. code-block:: bash
    wget http://ports.ubuntu.com/ubuntu-ports/pool/main/v/vulkan-loader/libvulkan1_1.3.204.1-2_arm64.deb
    sudo dpkg -i libvulkan1_1.3.204.1-2_arm64.deb
    sudo apt --fix-broken install
    sudo apt-mark hold libvulkan1

Also install Vulkan development library of the same version:

.. code-block:: bash
    wget http://ports.ubuntu.com/ubuntu-ports/pool/main/v/vulkan-loader/libvulkan-dev_1.3.204.1-2_arm64.deb
    sudo dpkg -i libvulkan-dev_1.3.204.1-2_arm64.deb
    sudo apt --fix-broken install
    sudo apt-mark hold libvulkan-dev

Add yourself to the ``renderer`` group

.. code-block:: bash
    sudo usermod -aG render $USER
    newgrp render

Testing Vulkan
--------------
Run ``vulkaninfo`` to verify that Vulkan is working correctly:

.. code-block:: bash
    vulkaninfo

Similar to ``clinfo``, this should display information about the Vulkan platforms, and you should see the following:

.. code-block:: bash

    ===== BEGIN DUMP OF OVERRIDDEN SETTINGS =====
    ===== END DUMP OF OVERRIDDEN SETTINGS =====
    QUALCOMM build          : cf15361b28, Iece42f3fbd
    Build Date              : 09/10/25
    Shader Compiler Version : E031.49.02.00
    Local Branch            :
    Remote Branch           :
    Remote Branch           :
    Reconstruct Branch      :

    Build Config            : G QGL_C_COMPILER_OPT 2.2.0 AArch64
    Driver Path             : /usr/lib/aarch64-linux-gnu/libvulkan_adreno.so.1
    Driver Version          : 0808.11
    PFP                     : 0x016dc112
    ME                      : 0x00000000
    Application Name    : vulkaninfo
    Application Version : 0x00000001
    Engine Name         : (null)
    Engine Version      : 0x00000000
    Api Version         : 0x004030cc
    ...

Transferring Files to Rubik Pi
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
To copy files from your host computer to the RB3 board:

.. code-block:: bash

    # On your host computer
    scp /path/to/file ubuntu@RP3_IP_ADDRESS:/home/ubuntu/

Replace ``RP3_IP_ADDRESS`` with the actual IP address of the Rubik Pi board.
