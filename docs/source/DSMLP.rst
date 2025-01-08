DSMLP
=====

Access DSMLP Using SSH
^^^^^^^^^^^^^^^^^^^^^^

You will use the `UCSD Data Science / Machine Learning Platform (DSMLP) <https://support.ucsd.edu/its?id=kb_article_view&sys_kb_id=fda9846287908954947a0fa8cebb352b>`_ to get access to a GPU.

You can login to DSMLP using by :code:`ssh USERNAME@dsmlp-login.ucsd.edu`. Your username and password are the same as your UCSD account. You can set up an `ssh key <https://support.ucsd.edu/services?id=kb_article_view&sys_kb_id=711d8e9e1b7b34d473462fc4604bcb47>`_ that allows you to more easily login.

Follow the steps in this `link <https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent?platform=mac#about-ssh-key-passphrases>`_ to generate a key pair (Follow the guide till step 3 under 'Adding your SSH key to the ssh-agent').

DSMLP uses containers to set up its software environment. You must create a container that provides access to a GPU with CUDA installed using the command :code:`launch.sh -g 1 -s -i ghcr.io/ucsd-ets/cse160-notebook:main -W CSE160_WI25_A00 -P Always`

Once you have the container, try to running the command :code:`nvidia-smi` and :code:`clinfo` to see if you have access to a GPU.

.. code-block:: bash
    # First, let's see if we have access to cuda
    nvidia-smi

    # Next let's make sure OpenCL is found.  This should return multiple.
    # Note that this includes both CPU and GPU OpenCL implementations
    clinfo

    # Request just the cuda OpenCL driver
    export POCL_DEVICES=cuda
    
Now you can compile and run the Makefiles in the PA directories.

Please be considerate on your use of the GPUs. The GPUs in DSMLP are shared within this class and across campus. If you are not actively using the GPU, you should shut down the container to allow others to access it.

Access DSMLP Using VSCode
^^^^^^^^^^^^^^^^^^^^^^^^^

To be determined.

Notes
^^^^^
When you close VSCode, the kubernetes pod is not released automatically. You have to manually delete the pod using :code:`kubectl delete pod <pod_name>`. To find your pod's name, you can run :code:`kubectl get pods` and find all the pods open. Once you do this, you will be able to use the terminal for launching a new container if you want.
