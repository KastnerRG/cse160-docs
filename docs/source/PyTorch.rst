OpenCL and PyTorch
==================

Author: Sean Perry

Note: These Docs are a work in progress as they intend to be documentation on how PyTorch_OCL works. 


PyTorch's Python library is a wrapper around C support for diffrent Backends. These backends take the parralizable part of machine learning (basic operations, matrix mutliplication etc), and send operations to various accerlators.
PyTorch currently supports a backends for parralization, as shown in `https://docs.pytorch.org/docs/stable/backends.html`. Unforunately, PyTorch, as of time of writing, does not currently have an OpenCL Backend.

However, custom backends can be implemented via `Autoloading <https://docs.pytorch.org/tutorials/unstable/python_extension_autoload.html>`. 

This is where the work of Artyom Beilis comes into play. Around July of 2021, they started work on building out an OpenCL backend for Pytorch <https://dev-discuss.pytorch.org/t/implementing-opencl-backend-for-pytorch/283>. 
They already had a library implemented in OpenCL call `dlprimitives <https://github.com/artyom-beilis/dlprimitives>` (Deep Learning Primitives) that could handle operations like Linear Layers and Convolutions. 

The progress of this work can be tracked over various PyTorch forums `such as this <https://dev-discuss.pytorch.org/t/opencl-backend-dev-questions-support/2407>` ending up with `pytorch_dlprim <https://github.com/artyom-beilis/pytorch_dlprim>`

This PyTorch wrapper takes the OpenCL implementations in dlprimitives and connects to an out of tree backend that can be autoloaded into pytorch. 
So that means if you wanted to implement a Pytorch operation, you would need the OpenCL function for calling it to exist in dlprimitives and the function call in pytorch_dlprim to be able to use pytorch with that OpenCL function.

Currently these libraries are built in our docker containers (on this `PR <https://github.com/KastnerRG/cse160-opencl-docker/pull/6>`) and installed into the base python path to be used in PyTorch. 
The libraries are forked into the KastnerRG github in case people want to build off this work.

These libraries are fully capable of end to end training in OpenCL including autograd.


Current limitations
-------------------
Many Attention operations are not implemented by pytorch_dlprim (`see the issues on pytorch_dlprim <https://github.com/artyom-beilis/pytorch_dlprim/issues/110>`). This posses an issue for running LLMs in OpenCL or even modern effientnets.
There maybe some possible work arounds, namely according to the issue linked above, LlamaCPP could be used here. This should be considered future work.

If anyone is interested in addressing this issue. Please let me know. 