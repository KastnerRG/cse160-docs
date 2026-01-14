=======================================================================
Developing on your hardware using Visual Studio Code with DevContainers
=======================================================================

Introduction
------------
This guide will show you how to set up a development environment for CSE 160 on your own computer using Visual Studio Code and DevContainers.
DevContainers is a feature of Visual Studio Code that allows you to develop in a containerized environment.
This means that you can develop on your own computer without having to install all the necessary dependencies required for this class.
In general, expect that you will not be able to access the accelerators of your computer (e.g. GPU) from within the container. NVIDIA is an exception to this rule.

This configuration is not officially supported by the course staff, but we hope that it will be helpful to you.

Prerequisites
-------------
0. WINDOWS ONLY: Set up WSL before you set up Docker Desktop: https://learn.microsoft.com/en-us/windows/wsl/install
1. Install Docker Desktop: https://www.docker.com/products/docker-desktop
2. Install Visual Studio Code: https://code.visualstudio.com/

Setting up DevContainers
------------------------
1. Download the source code locally to your device.
2. Open the source code in Visual Studio Code.
3. Visual Studio Code will detect the extensions json file and prompt you to install the recommended extensions.
4. Visual Studio Code will detect the presence of the `.devcontainer` folder and prompt you to reopen the project in a container.
5. Click on the "Reopen in Container" button.
6. Visual Studio Code will prompt you to choose a container configuration. Choose the one the one that matches your available accelerators.
7. Visual Studio Code will build the container and open the project in the container.

Confirm that your development environment is set up correctly by running :code:`clinfo` in the terminal. If you see the OpenCL information, then your development environment is set up correctly.

Common Pitfalls
----------------
- For Windows users, if you are seeing the error `Error response from daemon: accessing specified distro mount service` or
    `distro-services/ubuntu.sock: no such file or directory`, open Docker Desktop and go to Resources>WSL Integration and check the box that says
    `Enable integration with my default WSL distro`. Then restart docker. This should spin docker up in your WSL distro.