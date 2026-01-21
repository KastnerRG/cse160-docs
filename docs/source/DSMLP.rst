DSMLP
=====

Access DSMLP Using SSH
^^^^^^^^^^^^^^^^^^^^^^

You will use the `UCSD Data Science / Machine Learning Platform (DSMLP) <https://support.ucsd.edu/its?id=kb_article_view&sys_kb_id=fda9846287908954947a0fa8cebb352b>`_ to get access to a GPU.

You can login to DSMLP using by :code:`ssh USERNAME@dsmlp-login.ucsd.edu`. Your username and password are the same as your UCSD account. You can set up an `ssh key <https://support.ucsd.edu/services?id=kb_article_view&sys_kb_id=711d8e9e1b7b34d473462fc4604bcb47>`_ that allows you to more easily login.

Follow the steps in this `link <https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent?platform=mac#about-ssh-key-passphrases>`_ to generate a key pair (Follow the guide till step 3 under 'Adding your SSH key to the ssh-agent').

DSMLP uses containers to set up its software environment. You must create a container that provides access to a GPU with CUDA installed using the command :code:`launch.sh -g 1 -s -i ghcr.io/kastnerrg/cse160-opencl:dsmlp -W CSE160_WI26_A00 -P Always`

.. note::
    If you run into issues while getting GPUs in DSMLP, you can use :code:`-n` #, e.g., :code:`-n 1`, to avoid that node until we can reset it.
    Check the GPU status here `DSMLP STATUS <https://datahub.ucsd.edu/hub/status>`_

.. note::
    You can request a specific GPU type by appending :code:`-v GPU_TYPE` to the command above. For example, to request an GTX 1080Ti GPU, you would use :code:`-v 1080ti`. You can see the available GPU types on the `DSMLP STATUS <https://datahub.ucsd.edu/hub/status>`_ page.

Once you have the container, try to running the command :code:`nvidia-smi` and :code:`clinfo -l` to see if you have access to a GPU.

.. code-block:: bash

    # First, let's see if we have access to cuda
    nvidia-smi
    
    # Next let's make sure OpenCL is found.  This should return multiple.
    # Note that this includes both CPU and GPU OpenCL implementations
    clinfo -l
    
Now you can compile and run the Makefiles in the PA directories.

Please be considerate on your use of the GPUs. The GPUs in DSMLP are shared within this class and across campus. If you are not actively using the GPU, you should shut down the container to allow others to access it.

Access DSMLP Using VSCode
^^^^^^^^^^^^^^^^^^^^^^^^^

**1. Create SSH Key and Add to DSMLP**

Create an SSH Key on your local machine and append the public key to DSMLP's ``~/.ssh/authorized_keys`` file. Follow the steps in this `link <https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent?platform=mac#about-ssh-key-passphrases>`_ to generate a key pair (Follow the guide till step 3 under 'Adding your SSH key to the ssh-agent').

After generating the key, append it to DSMLP using:

.. code-block:: bash

    ssh-copy-id -i ~/.ssh/id_ed25519 your-username@dsmlp-login.ucsd.edu

Make sure to replace ``your-username`` with your actual UCSD username.

**2. Install VS Code**

Install VS Code if you haven't already: `VS Code Download <https://code.visualstudio.com/download>`_

**3. Install Remote-SSH Extension**

Install Remote-SSH plugin by searching for it in the extensions view.

Extension Identifier: ``ms-vscode-remote.remote-ssh``

**4. Configure SSH Connection**

1. Login to DSMLP using the terminal as shown above.
2. While logged in, run the following command to create a script that launches the container with GPU access which we will use in VSCode:

.. code-block:: bash

    echo '#!/bin/bash' > start-vscode.sh
    echo '/opt/launch-sh/bin/launch.sh -c 2 -m 8 -H -g 1 -s -i  ghcr.io/kastnerrg/cse160-opencl:dsmlp -W CSE160_WI26_A00 -P Always -N vscode-dsmlp' >> start-vscode.sh
    chmod +x start-vscode.sh

3. While still logged in, type `pwd` to get your home directory path on DSMLP and note it down for later use.
4. Click on the indicator on the bottom left corner

    .. image:: image/vscode_indictor.png
        :alt: VS Code SSH Configuration
        :width: 600px


5. Click on ``Connect to Host...``
6. Click on ``Configure SSH Hosts...``
7. Click on the ``Users/name/.ssh/config``
8. Add the following lines (make sure to change ``<your-username>`` to your username and ``<home-directory>`` to your home directory on DSMLP, e.g., ``/home/username/``):

.. code-block:: text

    Host vscode-dsmlp
    HostName dsmlp-login.ucsd.edu
    HostKeyAlias vscode-dsmlp
    IdentitiesOnly yes
    User <your-username>
    ConnectTimeout 100
    ProxyCommand ssh -i ~/.ssh/id_ed25519 <your-username>@dsmlp-login.ucsd.edu <home-directory>/start-vscode.sh

9. Save the configuration
10. Click on the >< key at the bottom left corner and then click on ``Connect to Host...``
11. You should see a ``vscode-dsmlp`` option. Click on it to start your session.
12. You may be asked to insert the passphrase you created - do that and happy coding!

Important Notes
^^^^^^^^^^^^^^^
You already have access to GPU infrastructure on DSMLP; i.e. it starts a container with GPU access and loads it with a software image that contains CUDA and other basic packages. You must be within GPU container in order to properly compile. If you get an error about not having access to nvcc, then you are not in the container. Please only use the container when you are compiling and release it when you are completed.

**Note**
When you close VSCode, the kubernetes pod is not released automatically. You have to manually delete the pod using:

.. code-block:: bash

    kubectl delete pod <pod_name>

To find your pod's name, you can run:

.. code-block:: bash

    kubectl get pods

and find all the pods open. Once you do this, you will be able to use the terminal for launching a new container if you want.