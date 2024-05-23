Qualcomm Innovators Development Kit (QIDK)
==========================================

Android Debug Bridge (ADB)
^^^^^^^^^^^^^^^^^^^^^^^^^^
Installation:
    1. Install Android Studio `here <https://developer.android.com/studio>`_
    2. Follow instructions `here <https://developer.android.com/tools/adb>`_ to install ADB using Android Studio's SDK Manager
    3. Add the path to :code:`android_sdk/platform-tools/` to your system's PATH variable or navigate to the directory and run the commands from there

Usage:
    - Connect your device to your computer via USB-C to USB-A cable
    - Enable USB debugging on your device
    - Run the following command to verify that your device is connected: :code:`adb devices`
    - Run the following command to start an interactive shell on your device: :code:`adb shell`

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


OpenCL Setup For QIDK
^^^^^^^^^^^^^^^^^^^^^
Installation:
    1. Open Termux on your Android device or SSH into your device
    2. Run the following command to install the OpenCL package: :code:`pkg install ocl-icd`
    3. Run the following command to install the OpenCL development package: :code:`pkg install ocl-icd-dev`
    4. Run the following command to install the OpenCL headers: :code:`pkg install opencl-headers`

Usage:
    - You can now compile and run OpenCL programs on your Android device like you would on DSMLP