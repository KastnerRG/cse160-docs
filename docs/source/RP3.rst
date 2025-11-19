RB3 Board Setup Guide: Ubuntu Installation and OpenCL Configuration
==========================================

.. note::
    This guide is compiled using the official Thundercomm documentation. If you need 
    further guidance, please refer to: `Thundercomm Documentation <https://www.thundercomm.com/rubik-pi-3/en/docs/rubik-pi-3/en/docs/1.0.0-u>`_.

.. note::
    This guide is for Linux, Windows, and macOS systems; however, Qualcomm Launcher is currently only avaliable for Windows on X86 or ARM64, macOS on ARM64, and Linux with a Debian-based distribution

.. important::
    A Type-C 12V 3A power adapter compliant with PD 3.0 is required for input power.
    The power indicator LED near the power port will turn on if the power adapter meets requirements and power negotiation succeeds.
    If the adapter does not meet requirements, the LED will remain off and the device will not boot.

Prerequisites
^^^^^^^^^^^^
Before you begin, you will need:

* A computer with an OS supported by Qualcomm Launcher
* A Thundercomm Rubik Pi 3 development board
* USB Type-C PD 3.0 compilant power supply
* USB Type-C PD 3.0 compilant cable for power supply
* USB 3.1 compatible Type-C cable to the computer for flashing
* USB 2.0 to Micro-B cable for UART connection
* Accessible LAN via WiFi or Ethernet


.. note::
    The Rubik Pi does not support IEEE 802.11ax (Wifi 6) or 802.11be (WiFi 7)

Ubuntu Installation
^^^^^^^^^^^^^^^^^^

Download Required Files
----------------------
Download Qualcomm Launcher from `Qualcomm Software Center web portal <https://softwarecenter.qualcomm.com/catalog/item/Qualcomm_Launcher>`_ and install the launcher on your host machine.

.. note::
    On Linux hosts, Qualcomm Launcher v1.2.2 or later is required.

Open Qualcomm Launcher and select **Rubik Pi** as the development kit, and **Ubuntu** as the target OS

.. figure:: https://www.thundercomm.com/rubik-pi-3/en/assets/images/Flashing_OS_NoDeviceConnected-0bb76bdccf3d91b71344a8910de03be9.png
    :align: center
    :alt: Qualcomm launcher home config

*Credits: Thundercomm*

Do not connect the board to your computer yet

Enter EDL Mode
-------------
EDL Mode is required to flash firmware and OS images to RubikPi 3 using Qualcomm's QDL tool. To Enter EDL mode, please disconnect everything from the board.

Press and hold the [EDL] button

.. figure:: /image/RubikPi/RubikPiEDL.png
    :scale: 30%
    :alt: EDL button location

While continuing to hold the [EDL] button, connect the power supply into [PWR] USB port

.. figure:: /image/RubikPi/RubikPiPWR.png
    :scale: 30%
    :alt: PWR port location

While continuing to hold the [EDL] button, insert the Type-C cable into [USB 3.1] port and connect to your computer.

.. figure:: /image/RubikPi/RubikPiUSB.png
    :scale: 30%
    :alt: USB 3.1 port location

Wait three seconds to enter 9008 mode, then release [EDL] button

Flashing the board
-----------------

The RUBIK Pi will be automatically detected by Qualcomm Launcher. Select the device and click Flash button to begin updating the Renesas USB firmware.

After successful USB firmware flashing, a dialog box will appear. Once the Launcher is waiting for user action to put the device into EDL mode again, you will see the following screen:

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

After the OS image is successfully flashed, the following confirmation screen will appear.

.. figure:: https://www.thundercomm.com/rubik-pi-3/en/assets/images/OS_image_flashing_completed-ff45bd2899b7b3e02bdb63f28a862f42.png
    :align: center
    :alt: Qualcomm launcher flash OS successful
*Credits: Thundercomm*

Configure the device
-----------------

Click Configure Login, the launcher will then prompt to setup UART connection.

.. note::
    If the MicroUSB COM port on the host system is currently in use by another tool (e.g., PuTTY, Tera Term), please close it before proceeding.

Without disconnecting any cable from the device, connect your computer to the device with a USB Micro-B cable at the [DEBUG] port

.. figure:: /image/RubikPi/RubikPiUART.png
    :scale: 30%
    :alt: DEBUG port location

Once the USB Micro-B cable is connected, a serial terminal will open. When asked, type in the default username and password:

* Username: ubuntu
* Password: ubuntu

The terminal will ask you to reset the password immediately, type in the default password again when prompted, then set your password.

The launcher will prompt you to configure the Wi-Fi once finished. Configure the Wi-Fi by entering the SSID and password, or connect the device to Ethernet.
Once connected, the launcher will display the device IP address and the `ssh` command to connect to the device. Save this information.

.. figure:: https://www.thundercomm.com/rubik-pi-3/en/assets/images/wi-fi_completed-6c17fb871952826a717480f620f4c29f.png
    :align: center
    :alt: Qualcomm launcher WiFi connect successful
*Credits: Thundercomm*

Click Finish Setup and verify that the setup process is complete.
