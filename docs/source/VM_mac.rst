Ubuntu VM Setup Guide on macOS: UTM Virtualization
==================================================

.. note::

   ⚠️ **Important**  
   This guide is specifically for Intel-based Macs (x86_64).

Prerequisites
-------------

Before you begin, you will need:

* **Host machine requirements**  
  * CPU cores: 8 or more  
  * RAM: 8 GB or more  
  * Storage: 100 GB free space  
    (`Set up an Ubuntu VM on an x86_64 Mac using UTM - Qualcomm <https://docs.qualcomm.com/bundle/publicresource/topics/80-70015-41/set-up-an-ubuntu-vm-on-an-intel-based-x86-64-mac.html?utm_source=chatgpt.com>`_)
* **Operating System**: macOS 11.0 (Big Sur) or later  
* **Software**:
  * UTM (version 4.0 or later)  
  * Ubuntu 22.04.4 LTS ISO (desktop or server)  
* **Optional**: Qualcomm Linux Development Kit for testing USB passthrough

Install UTM
-----------

Download and install the latest UTM release for macOS from the 
`UTM website <https://mac.getutm.app/>`_.

Please follow 
`this guide <https://docs.qualcomm.com/bundle/publicresource/topics/80-70017-41/set-up-an-ubuntu-vm-on-an-intel-based-x86-64-mac.html>`_ 
until the section *Access the Qualcomm Linux Development Kit from the UTM VM*.

.. note::

   ℹ️ **Note**  
   This sets up a terminal version of Ubuntu. If you want a desktop version to use features like copy-paste, run the following commands:

::

   sudo apt update
   sudo apt install ubuntu-desktop -y

This process may take several minutes and require ~2 GB of additional disk space.

Enable Clipboard Sharing in UTM
-------------------------------

1. Shut down the VM if it is currently running.
2. Open UTM, select your VM, and click **Edit**.
3. In the Display section:
   - Ensure the Display Card is set to **SPICE**.
   - Check the box for **Clipboard Sharing** (Enable clipboard sync).
4. Click **Save**, then restart the VM.

Verify Clipboard Functionality
------------------------------

Once the VM boots into the Ubuntu Desktop environment:

1. Try copying text from your macOS host and pasting it into a text editor inside Ubuntu (e.g., Gedit or Terminal with ``Ctrl+Shift+V``).
2. Copy text inside Ubuntu and paste it into a macOS app (e.g., Notes or Safari).

.. warning::

   Clipboard sharing may not work reliably in all apps or Ubuntu versions. It is limited to plain text and depends on SPICE guest tools.

USB Passthrough for Development Kit
-----------------------------------

To forward a Qualcomm Linux Development Kit (or other USB device) into the VM:

1. Power on the VM, then open its **Settings** → **USB**.  
2. Click **+** to add a new USB device filter. Select your device (e.g., Qualcomm kit).  
3. Restart the VM. Inside Ubuntu, verify the device:

::

   lsusb

You should see your device’s Vendor and Product IDs.
