# RB3 Board Docker Setup Guide:

Install Docker
^^^^^^^^^^^^^^

1. **Update the package list and install required packages**

.. code-block:: bash

```
sudo apt update
sudo apt install apt-transport-https ca-certificates curl software-properties-common -y
```

2\. **Add the Docker GPG key**

.. code-block:: bash

```
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
```

3\. **Add the Docker repository**

.. code-block:: bash

```
echo "deb [arch=arm64 signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
```

4\. **Install Docker**

.. code-block:: bash

```
sudo apt update
sudo apt install docker-ce docker-ce-cli containerd.io -y
```

Verify Docker Installation
^^^^^^^^^^^^^^^^^^^^^^^^^
Verify that Docker is installed correctly by checking the version:

.. code-block:: bash

```
docker --version
```

You should see an output similar to::

```
Docker version xx.xx.xx, build 1234567
```

Fixing Docker Permission Issue
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
By default, Docker requires root privileges, which can lead to permission issues. To allow non-root users to run Docker commands, follow these steps:

1. **Add the current user to the Docker group**

.. code-block:: bash

```
sudo usermod -aG docker $USER
```

2\. **Apply the group changes** (This step is critical to avoid permission issues):

.. code-block:: bash

```
newgrp docker
```

3\. **Test the configuration**

.. code-block:: bash

```
docker run hello-world
```

If you see the "Hello from Docker!" message, your setup is complete.

Enabling Docker at Startup
^^^^^^^^^^^^^^^^^^^^^^^^^^
Ensure Docker starts automatically on boot:

.. code-block:: bash

```
sudo systemctl enable docker
sudo systemctl start docker
```
