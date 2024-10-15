Qualcomm Innovators Development Kit (QIDK)
==========================================
In this guide, "your system" or "your computer" refers to your development machine.
We often refer to the QIDK as "the/your device".

Android Debug Bridge (ADB)
^^^^^^^^^^^^^^^^^^^^^^^^^^
Installation:
    1. Install Android Studio `here <https://developer.android.com/studio>`_
    2. Follow these `instructions <https://developer.android.com/tools/adb>`_ to install ADB using Android Studio's SDK Manager
    3. Add the path to :code:`android_sdk/platform-tools/` to your system's PATH variable or navigate to the directory and run the commands from there
Alternative Installation:
    1. Install `Android SDK Platform Tools <https://developer.android.com/tools/releases/platform-tools>`_
        a. If you have Homebrew `brew install --cask android-platform-tools`
Usage:
    - Connect your device to your computer via USB-C to USB-A cable
    - Enable USB debugging on your device
    - Run the following command to verify that your device is connected: :code:`adb devices`
    - Run the following command to start an interactive shell on your device: :code:`adb shell`
Alternatively, you can get shell access by:
    1. Enable development mode on your device by going to `Settings -> About phone` and tapping the "Build number" tag 7 times
    2. Go to `Developer Settings` and enable Wireless debugging
    3. Search for the button called `Pair device with pairing code` and press it
    4. On your computer's terminal, type `adb pair ip:port` where `ip:port` is the ip address and port of your QIDK.
    5. Once paired, you can type `adb shell` to access a read only shell of your device

Termux
^^^^^^
Installation:
    1. Download the Termux APK from this `repository <https://github.com/termux/termux-app>`_ 
    2. Install the APK on your device using: :code:`adb install path/to/termux.apk`
    3. Check your Android device; Termux should now be installed and available

Usage:
    - Termux now acts as a linux terminal on your Android device
    - Connect to a network and run the following command to install a package: :code:`pkg install package_name`


Access QIDK using SSH
^^^^^^^^^^^^^^^^^^^^^
Installation:
    1. Open Termux on your Android device
    2. Run the following command to install the OpenSSH package: :code:`pkg install openssh`
    3. Run the following command to set your password: :code:`passwd`
    4. Run the following command to start the SSH server: :code:`sshd`
    5. Run the following command to get the IP address of your device: :code:`ifconfig`

Usage:
    - Connect to the same network as the Android device and run the following command on your computer to connect to your device: :code:`ssh ip_address -p 8022`
    - Enter the password you set in step 3 to access the device
    - You should now have access to the device's linux terminal under your personal user account

Access QIDK using VSCode (code-server)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Installation:
    1. Open Termux on your Android device or SSH into your device
    2. Run the following command to install the OpenSSH package: :code:`pkg install tur-repo`
    3. Run the following command to install the OpenSSH package: :code:`pkg install code-server`

Usage:
    - Run the following command to start the code-server: 
        - With authentication: :code:`code-server --bind-addr 0.0.0.0:8080`, find the password in :code:`/code-server/config.yaml`
        - Without authentication: :code:`code-server --auth none --bind-addr 0.0.0.0:8080`
    - Access VSCode from your local machine by entering the QIDK's IP address and port number (8080) in your browser

OpenCL Setup For QIDK
^^^^^^^^^^^^^^^^^^^^^
Installation:
    1. Open Termux on your Android device or SSH into your device
    2. Run the following command to install the OpenCL package: :code:`pkg install ocl-icd`
    3. Run the following command to install the OpenCL headers: :code:`pkg install opencl-headers`
    4. Run the following command to add the device OpenCL drivers to the dynamic linker path: :code:`export LD_LIBRARY_PATH=/system/vendor/lib64:$LD_LIBRARY_PATH`

Debugging
^^^^^^^^^
Make/GCC/LD Errors:
    1. This is probably due to the fact that build tools are not installed in the device.
    2. Run the following command to install the build tools: :code:`pkg install build-essential`

Usage:
    - You can now compile and run OpenCL programs on your Android device like you would on DSMLP