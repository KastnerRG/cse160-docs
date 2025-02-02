===============================
Debugging Gradescope Autograder
===============================

This document is aimed at students who want to better understand how the Gradescope Autograder works and how they can debug they debug their code.

Introduction
------------
The Gradescope Autograder has access to an Intel x86_64 CPU. As such, we are the Intel OpenAPI Runtime to run your OpenCL code.  This is likely different then the platform you have used to develop it. DSMLP also has this driver available, but it is not the default.

Accessing Intel OpenAPI Runtime on DSMLP
----------------------------------------
The starter code in the :code:`helper_lib` supports overriding the platform and device index. If you know the platform and device index, you can override these at runtime with by executing :code:`PLATFORM_INDEX=p DEVICE_INDEX=d make run`.

To get :code:`p` and :code:`d`, you can execute :code:`clinfo`.  Here is an example output.

.. code-block:: bash

    59960@ccrutchf-1340126:~$ clinfo
    Number of platforms                               2
    Platform Name                                   Portable Computing Language
    Platform Vendor                                 The pocl project
    Platform Version                                OpenCL 3.0 PoCL 6.0  Linux, Release, RELOC, LLVM 14.0.0, SLEEF, CUDA, POCL_DEBUG
    Platform Profile                                FULL_PROFILE
    Platform Extensions                             cl_khr_icd cl_khr_priority_hints cl_khr_throttle_hints cl_pocl_content_size cl_ext_buffer_device_address
    Platform Extensions with Version                cl_khr_icd                                                       0x400000 (1.0.0)
                                                    cl_khr_priority_hints                                            0x400000 (1.0.0)
                                                    cl_khr_throttle_hints                                            0x400000 (1.0.0)
                                                    cl_pocl_content_size                                             0x400000 (1.0.0)
                                                    cl_ext_buffer_device_address                                       0x1000 (0.1.0)
    Platform Numeric Version                        0xc00000 (3.0.0)
    Platform Extensions function suffix             POCL
    Platform Host timer resolution                  1ns

    Platform Name                                   Intel(R) OpenCL
    Platform Vendor                                 Intel(R) Corporation
    Platform Version                                OpenCL 3.0 LINUX
    Platform Profile                                FULL_PROFILE
    Platform Extensions                             cl_khr_spirv_linkonce_odr cl_khr_fp64 cl_khr_fp16 cl_khr_global_int32_base_atomics cl_khr_global_int32_extended_atomics cl_khr_local_int32_base_atomics cl_khr_local_int32_extended_atomics cl_khr_3d_image_writes cl_khr_byte_addressable_store cl_khr_depth_images cl_khr_extended_bit_ops cl_khr_icd cl_khr_il_program cl_khr_suggested_local_work_size cl_intel_unified_shared_memory cl_intel_devicelib_assert cl_khr_subgroup_ballot cl_khr_subgroup_shuffle cl_khr_subgroup_shuffle_relative cl_khr_subgroup_extended_types cl_khr_subgroup_non_uniform_arithmetic cl_khr_subgroup_non_uniform_vote cl_khr_subgroup_clustered_reduce cl_intel_subgroups cl_intel_subgroups_char cl_intel_subgroups_short cl_intel_subgroups_long cl_intel_required_subgroup_size cl_intel_spirv_subgroups cl_khr_int64_base_atomics cl_khr_int64_extended_atomics cl_intel_device_attribute_query cl_intel_exec_by_local_thread cl_intel_vec_len_hint cl_intel_device_partition_by_names cl_khr_spir cl_khr_image2d_from_buffer cl_intel_concurrent_dispatch
    Platform Extensions with Version                cl_khr_spirv_linkonce_odr                                        0x400000 (1.0.0)
                                                    cl_khr_fp64                                                      0x400000 (1.0.0)
                                                    cl_khr_fp16                                                      0x400000 (1.0.0)
                                                    cl_khr_global_int32_base_atomics                                 0x400000 (1.0.0)
                                                    cl_khr_global_int32_extended_atomics                             0x400000 (1.0.0)
                                                    cl_khr_local_int32_base_atomics                                  0x400000 (1.0.0)
                                                    cl_khr_local_int32_extended_atomics                              0x400000 (1.0.0)
                                                    cl_khr_3d_image_writes                                           0x400000 (1.0.0)
                                                    cl_khr_byte_addressable_store                                    0x400000 (1.0.0)
                                                    cl_khr_depth_images                                              0x400000 (1.0.0)
                                                    cl_khr_extended_bit_ops                                          0x400000 (1.0.0)
                                                    cl_khr_icd                                                       0x400000 (1.0.0)
                                                    cl_khr_il_program                                                0x400000 (1.0.0)
                                                    cl_khr_suggested_local_work_size                                 0x400000 (1.0.0)
                                                    cl_intel_unified_shared_memory                                   0x400000 (1.0.0)
                                                    cl_intel_devicelib_assert                                        0x400000 (1.0.0)
                                                    cl_khr_subgroup_ballot                                           0x400000 (1.0.0)
                                                    cl_khr_subgroup_shuffle                                          0x400000 (1.0.0)
                                                    cl_khr_subgroup_shuffle_relative                                 0x400000 (1.0.0)
                                                    cl_khr_subgroup_extended_types                                   0x400000 (1.0.0)
                                                    cl_khr_subgroup_non_uniform_arithmetic                           0x400000 (1.0.0)
                                                    cl_khr_subgroup_non_uniform_vote                                 0x400000 (1.0.0)
                                                    cl_khr_subgroup_clustered_reduce                                 0x400000 (1.0.0)
                                                    cl_intel_subgroups                                               0x400000 (1.0.0)
                                                    cl_intel_subgroups_char                                          0x400000 (1.0.0)
                                                    cl_intel_subgroups_short                                         0x400000 (1.0.0)
                                                    cl_intel_subgroups_long                                          0x400000 (1.0.0)
                                                    cl_intel_required_subgroup_size                                  0x400000 (1.0.0)
                                                    cl_intel_spirv_subgroups                                         0x400000 (1.0.0)
                                                    cl_khr_int64_base_atomics                                        0x400000 (1.0.0)
                                                    cl_khr_int64_extended_atomics                                    0x400000 (1.0.0)
                                                    cl_intel_device_attribute_query                                  0x400000 (1.0.0)
                                                    cl_intel_exec_by_local_thread                                    0x400000 (1.0.0)
                                                    cl_intel_vec_len_hint                                            0x400000 (1.0.0)
                                                    cl_intel_device_partition_by_names                               0x400000 (1.0.0)
                                                    cl_khr_spir                                                      0x400000 (1.0.0)
                                                    cl_khr_image2d_from_buffer                                       0x400000 (1.0.0)
                                                    cl_intel_concurrent_dispatch                                     0x400000 (1.0.0)
    Platform Numeric Version                        0xc00000 (3.0.0)
    Platform Extensions function suffix             INTEL
    Platform Host timer resolution                  1ns

    Platform Name                                   Portable Computing Language
    Number of devices                                 2
    Device Name                                     cpu-cascadelake-Intel(R) Xeon(R) Gold 5218 CPU @ 2.30GHz
    Device Vendor                                   GenuineIntel
    Device Vendor ID                                0x10006
    Device Version                                  OpenCL 3.0 PoCL HSTR: cpu-x86_64-pc-linux-gnu-cascadelake
    Device Numeric Version                          0xc00000 (3.0.0)
    Driver Version                                  6.0
    Device OpenCL C Version                         OpenCL C 1.2 PoCL
    Device OpenCL C all versions                    OpenCL C                                                         0x400000 (1.0.0)
                                                    OpenCL C                                                         0x401000 (1.1.0)
                                                    OpenCL C                                                         0x402000 (1.2.0)
                                                    OpenCL C                                                         0xc00000 (3.0.0)
    Device OpenCL C features                        __opencl_c_3d_image_writes                                       0xc00000 (3.0.0)
                                                    __opencl_c_images                                                0xc00000 (3.0.0)
                                                    __opencl_c_atomic_order_acq_rel                                  0xc00000 (3.0.0)
                                                    __opencl_c_atomic_order_seq_cst                                  0xc00000 (3.0.0)
                                                    __opencl_c_atomic_scope_device                                   0xc00000 (3.0.0)
                                                    __opencl_c_program_scope_global_variables                        0xc00000 (3.0.0)
                                                    __opencl_c_atomic_scope_all_devices                              0xc00000 (3.0.0)
                                                    __opencl_c_generic_address_space                                 0xc00000 (3.0.0)
                                                    __opencl_c_work_group_collective_functions                       0xc00000 (3.0.0)
                                                    __opencl_c_read_write_images                                     0xc00000 (3.0.0)
                                                    __opencl_c_subgroups                                             0xc00000 (3.0.0)
                                                    __opencl_c_fp64                                                  0xc00000 (3.0.0)
                                                    __opencl_c_ext_fp32_global_atomic_add                            0xc00000 (3.0.0)
                                                    __opencl_c_ext_fp32_local_atomic_add                             0xc00000 (3.0.0)
                                                    __opencl_c_ext_fp32_global_atomic_min_max                        0xc00000 (3.0.0)
                                                    __opencl_c_ext_fp32_local_atomic_min_max                         0xc00000 (3.0.0)
                                                    __opencl_c_ext_fp64_global_atomic_add                            0xc00000 (3.0.0)
                                                    __opencl_c_ext_fp64_local_atomic_add                             0xc00000 (3.0.0)
                                                    __opencl_c_ext_fp64_global_atomic_min_max                        0xc00000 (3.0.0)
                                                    __opencl_c_ext_fp64_local_atomic_min_max                         0xc00000 (3.0.0)
                                                    __opencl_c_int64                                                 0xc00000 (3.0.0)
    Latest comfornace test passed                   v2022-04-19-01
    Device Type                                     CPU
    Device Profile                                  FULL_PROFILE
    Device Available                                Yes
    Compiler Available                              Yes
    Linker Available                                Yes
    Max compute units                               64
    Max clock frequency                             3900MHz
    Device Partition                                (core)
        Max number of sub-devices                     64
        Supported partition types                     equally, by counts
        Supported affinity domains                    (n/a)
    Max work item dimensions                        3
    Max work item sizes                             4096x4096x4096
    Max work group size                             4096
    Preferred work group size multiple (device)     8
    Preferred work group size multiple (kernel)     8
    Max sub-groups per work group                   128
    Sub-group sizes (Intel)                         1, 2, 4, 8, 16, 32, 64, 128, 256, 512
    Preferred / native vector sizes                 
        char                                                16 / 16      
        short                                               16 / 16      
        int                                                 16 / 16      
        long                                                 8 / 8       
        half                                                 0 / 0        (n/a)
        float                                               16 / 16      
        double                                               8 / 8        (cl_khr_fp64)
    Half-precision Floating-point support           (n/a)
    Single-precision Floating-point support         (core)
        Denormals                                     Yes
        Infinity and NANs                             Yes
        Round to nearest                              Yes
        Round to zero                                 Yes
        Round to infinity                             Yes
        IEEE754-2008 fused multiply-add               Yes
        Support is emulated in software               No
        Correctly-rounded divide and sqrt operations  Yes
    Double-precision Floating-point support         (cl_khr_fp64)
        Denormals                                     Yes
        Infinity and NANs                             Yes
        Round to nearest                              Yes
        Round to zero                                 Yes
        Round to infinity                             Yes
        IEEE754-2008 fused multiply-add               Yes
        Support is emulated in software               No
    Address bits                                    64, Little-Endian
    Global memory size                              402161725440 (374.5GiB)
    Error Correction support                        No
    Max memory allocation                           137438953472 (128GiB)
    Unified memory for Host and Device              Yes
    Shared Virtual Memory (SVM) capabilities        (core)
        Coarse-grained buffer sharing                 Yes
        Fine-grained buffer sharing                   Yes
        Fine-grained system sharing                   Yes
        Atomics                                       Yes
    Minimum alignment for any data type             128 bytes
    Alignment of base address                       1024 bits (128 bytes)
    Preferred alignment for atomics                 
        SVM                                           64 bytes
        Global                                        64 bytes
        Local                                         64 bytes
    Atomic memory capabilities                      relaxed, acquire/release, sequentially-consistent, work-group scope, device scope, all-devices scope
    Atomic fence capabilities                       relaxed, acquire/release, sequentially-consistent, work-item scope, work-group scope, device scope
    Max size for global variable                    64000 (62.5KiB)
    Preferred total size of global vars             1048576 (1024KiB)
    Global Memory cache type                        Read/Write
    Global Memory cache size                        23068672 (22MiB)
    Global Memory cache line size                   64 bytes
    Image support                                   Yes
        Max number of samplers per kernel             16
        Max size for 1D images from buffer            8589934592 pixels
        Max 1D or 2D image array size                 2048 images
        Max 2D image size                             65536x65536 pixels
        Max 3D image size                             2048x2048x2048 pixels
        Max number of read image args                 128
        Max number of write image args                128
        Max number of read/write image args           128
    Pipe support                                    No
    Max number of pipe args                         0
    Max active pipe reservations                    0
    Max pipe packet size                            0
    Local memory type                               Global
    Local memory size                               1048576 (1024KiB)
    Max number of constant args                     8
    Max constant buffer size                        1048576 (1024KiB)
    Generic address space support                   Yes
    Max size of kernel argument                     1024
    Queue properties (on host)                      
        Out-of-order execution                        Yes
        Profiling                                     Yes
    Device enqueue capabilities                     (n/a)
    Queue properties (on device)                    
        Out-of-order execution                        No
        Profiling                                     No
        Preferred size                                0
        Max size                                      0
    Max queues on device                            0
    Max events on device                            0
    Prefer user sync for interop                    Yes
    Profiling timer resolution                      1ns
    Execution capabilities                          
        Run OpenCL kernels                            Yes
        Run native kernels                            Yes
        Non-uniform work-groups                       No
        Work-group collective functions               Yes
        Sub-group independent forward progress        Yes
        IL version                                    (n/a)
        ILs with version                              (n/a)
    printf() buffer size                            16777216 (16MiB)
    Built-in kernels                                pocl.add.i8;org.khronos.openvx.scale_image.nn.u8;org.khronos.openvx.scale_image.bl.u8;org.khronos.openvx.tensor_convert_depth.wrap.u8.f32
    Built-in kernels with version                   pocl.add.i8                                                      0x402000 (1.2.0)
                                                    org.khronos.openvx.scale_image.nn.u8                             0x402000 (1.2.0)
                                                    org.khronos.openvx.scale_image.bl.u8                             0x402000 (1.2.0)
                                                    org.khronos.openvx.tensor_convert_depth.wrap.u8.f32              0x402000 (1.2.0)
    Device Extensions                               cl_khr_byte_addressable_store cl_khr_global_int32_base_atomics cl_khr_global_int32_extended_atomics cl_khr_local_int32_base_atomics cl_khr_local_int32_extended_atomics cl_khr_3d_image_writes cl_khr_command_buffer cl_khr_command_buffer_multi_device cl_khr_subgroups cl_intel_unified_shared_memory cl_ext_buffer_device_address       cl_pocl_svm_rect cl_pocl_command_buffer_svm       cl_pocl_command_buffer_host_buffer cl_khr_subgroup_ballot cl_khr_subgroup_shuffle cl_intel_subgroups cl_intel_subgroups_short cl_ext_float_atomics cl_intel_required_subgroup_size cl_khr_fp64 cl_khr_int64_base_atomics cl_khr_int64_extended_atomics
    Device Extensions with Version                  cl_khr_byte_addressable_store                                    0x400000 (1.0.0)
                                                    cl_khr_global_int32_base_atomics                                 0x400000 (1.0.0)
                                                    cl_khr_global_int32_extended_atomics                             0x400000 (1.0.0)
                                                    cl_khr_local_int32_base_atomics                                  0x400000 (1.0.0)
                                                    cl_khr_local_int32_extended_atomics                              0x400000 (1.0.0)
                                                    cl_khr_3d_image_writes                                           0x400000 (1.0.0)
                                                    cl_khr_command_buffer                                              0x9004 (0.9.4)
                                                    cl_khr_command_buffer_multi_device                                 0x9001 (0.9.1)
                                                    cl_khr_subgroups                                                 0x400000 (1.0.0)
                                                    cl_intel_unified_shared_memory                                   0x400000 (1.0.0)
                                                    cl_ext_buffer_device_address                                       0x1000 (0.1.0)
                                                    cl_pocl_svm_rect                                                   0x9000 (0.9.0)
                                                    cl_pocl_command_buffer_svm                                         0x9000 (0.9.0)
                                                    cl_pocl_command_buffer_host_buffer                                 0x9000 (0.9.0)
                                                    cl_khr_subgroup_ballot                                           0x400000 (1.0.0)
                                                    cl_khr_subgroup_shuffle                                          0x400000 (1.0.0)
                                                    cl_intel_subgroups                                               0x400000 (1.0.0)
                                                    cl_intel_subgroups_short                                         0x400000 (1.0.0)
                                                    cl_ext_float_atomics                                             0x400000 (1.0.0)
                                                    cl_intel_required_subgroup_size                                  0x400000 (1.0.0)
                                                    cl_khr_fp64                                                      0x400000 (1.0.0)
                                                    cl_khr_int64_base_atomics                                        0x400000 (1.0.0)
                                                    cl_khr_int64_extended_atomics                                    0x400000 (1.0.0)

    Device Name                                     NVIDIA GeForce RTX 2080 Ti
    Device Vendor                                   NVIDIA Corporation
    Device Vendor ID                                0x10de
    Device Version                                  OpenCL 3.0 PoCL HSTR: CUDA-sm_75
    Device Numeric Version                          0xc00000 (3.0.0)
    Driver Version                                  6.0
    Device OpenCL C Version                         OpenCL C 1.2 PoCL
    Device OpenCL C all versions                    OpenCL C                                                         0x400000 (1.0.0)
                                                    OpenCL C                                                         0x401000 (1.1.0)
                                                    OpenCL C                                                         0x402000 (1.2.0)
                                                    OpenCL C                                                         0xc00000 (3.0.0)
    Device OpenCL C features                        __opencl_c_images                                                0xc00000 (3.0.0)
                                                    __opencl_c_atomic_order_acq_rel                                  0xc00000 (3.0.0)
                                                    __opencl_c_atomic_order_seq_cst                                  0xc00000 (3.0.0)
                                                    __opencl_c_atomic_scope_device                                   0xc00000 (3.0.0)
                                                    __opencl_c_program_scope_global_variables                        0xc00000 (3.0.0)
                                                    __opencl_c_generic_address_space                                 0xc00000 (3.0.0)
                                                    __opencl_c_fp16                                                  0xc00000 (3.0.0)
                                                    __opencl_c_fp64                                                  0xc00000 (3.0.0)
    Latest comfornace test passed                   (n/a)
    Device Type                                     GPU
    Device Topology (NV)                            PCI-E, 0000:da:00.0
    Device Profile                                  FULL_PROFILE
    Device Available                                Yes
    Compiler Available                              Yes
    Linker Available                                Yes
    Max compute units                               68
    Max clock frequency                             1620MHz
    Compute Capability (NV)                         7.5
    Device Partition                                (core)
        Max number of sub-devices                     1
        Supported partition types                     None
        Supported affinity domains                    (n/a)
    Max work item dimensions                        3
    Max work item sizes                             1024x1024x64
    Max work group size                             1024
    Preferred work group size multiple (device)     32
    Preferred work group size multiple (kernel)     32
    Warp size (NV)                                  32
    Max sub-groups per work group                   32
    Preferred / native vector sizes                 
        char                                                 1 / 1       
        short                                                1 / 1       
        int                                                  1 / 1       
        long                                                 1 / 1       
        half                                                 0 / 0        (cl_khr_fp16)
        float                                                1 / 1       
        double                                               1 / 1        (cl_khr_fp64)
    Half-precision Floating-point support           (cl_khr_fp16)
        Denormals                                     No
        Infinity and NANs                             Yes
        Round to nearest                              Yes
        Round to zero                                 No
        Round to infinity                             No
        IEEE754-2008 fused multiply-add               No
        Support is emulated in software               No
    Single-precision Floating-point support         (core)
        Denormals                                     Yes
        Infinity and NANs                             Yes
        Round to nearest                              Yes
        Round to zero                                 Yes
        Round to infinity                             Yes
        IEEE754-2008 fused multiply-add               Yes
        Support is emulated in software               No
        Correctly-rounded divide and sqrt operations  No
    Double-precision Floating-point support         (cl_khr_fp64)
        Denormals                                     Yes
        Infinity and NANs                             Yes
        Round to nearest                              Yes
        Round to zero                                 Yes
        Round to infinity                             Yes
        IEEE754-2008 fused multiply-add               Yes
        Support is emulated in software               No
    Address bits                                    64, Little-Endian
    Global memory size                              11546394624 (10.75GiB)
    Error Correction support                        No
    Max memory allocation                           11381768192 (10.6GiB)
    Unified memory for Host and Device              No
    Integrated memory (NV)                          No
    Shared Virtual Memory (SVM) capabilities        (core)
        Coarse-grained buffer sharing                 Yes
        Fine-grained buffer sharing                   Yes
        Fine-grained system sharing                   No
        Atomics                                       No
    Minimum alignment for any data type             128 bytes
    Alignment of base address                       4096 bits (512 bytes)
    Preferred alignment for atomics                 
        SVM                                           64 bytes
        Global                                        64 bytes
        Local                                         64 bytes
    Atomic memory capabilities                      relaxed, work-group scope
    Atomic fence capabilities                       relaxed, acquire/release, work-group scope
    Max size for global variable                    0
    Preferred total size of global vars             0
    Global Memory cache type                        None
    Image support                                   No
    Pipe support                                    No
    Max number of pipe args                         0
    Max active pipe reservations                    0
    Max pipe packet size                            0
    Local memory type                               Local
    Local memory size                               49152 (48KiB)
    Registers per block (NV)                        65536
    Max number of constant args                     8
    Max constant buffer size                        65536 (64KiB)
    Generic address space support                   Yes
    Max size of kernel argument                     4352 (4.25KiB)
    Queue properties (on host)                      
        Out-of-order execution                        No
        Profiling                                     Yes
    Device enqueue capabilities                     (n/a)
    Queue properties (on device)                    
        Out-of-order execution                        No
        Profiling                                     No
        Preferred size                                0
        Max size                                      0
    Max queues on device                            0
    Max events on device                            0
    Prefer user sync for interop                    Yes
    Profiling timer resolution                      1ns
    Execution capabilities                          
        Run OpenCL kernels                            Yes
        Run native kernels                            No
        Non-uniform work-groups                       No
        Work-group collective functions               No
        Sub-group independent forward progress        Yes
        Kernel execution timeout (NV)                 No
    Concurrent copy and kernel execution (NV)       Yes
        Number of async copy engines                  3
        IL version                                    (n/a)
        ILs with version                              (n/a)
    printf() buffer size                            16777216 (16MiB)
    Built-in kernels                                pocl.mul.i32;pocl.add.i32;pocl.dnn.conv2d_int8_relu;pocl.sgemm.local.f32;pocl.sgemm.tensor.f16f16f32;pocl.sgemm_ab.tensor.f16f16f32;pocl.abs.f32;pocl.add.i8;org.khronos.openvx.scale_image.nn.u8;org.khronos.openvx.scale_image.bl.u8;org.khronos.openvx.tensor_convert_depth.wrap.u8.f32
    Built-in kernels with version                   pocl.mul.i32                                                     0x402000 (1.2.0)
                                                    pocl.add.i32                                                     0x402000 (1.2.0)
                                                    pocl.dnn.conv2d_int8_relu                                        0x402000 (1.2.0)
                                                    pocl.sgemm.local.f32                                             0x402000 (1.2.0)
                                                    pocl.sgemm.tensor.f16f16f32                                      0x402000 (1.2.0)
                                                    pocl.sgemm_ab.tensor.f16f16f32                                   0x402000 (1.2.0)
                                                    pocl.abs.f32                                                     0x402000 (1.2.0)
                                                    pocl.add.i8                                                      0x402000 (1.2.0)
                                                    org.khronos.openvx.scale_image.nn.u8                             0x402000 (1.2.0)
                                                    org.khronos.openvx.scale_image.bl.u8                             0x402000 (1.2.0)
                                                    org.khronos.openvx.tensor_convert_depth.wrap.u8.f32              0x402000 (1.2.0)
    Device Extensions                               cl_khr_byte_addressable_store cl_khr_global_int32_base_atomics     cl_khr_global_int32_extended_atomics cl_khr_local_int32_base_atomics     cl_khr_local_int32_extended_atomics cl_khr_int64_base_atomics     cl_khr_int64_extended_atomics cl_nv_device_attribute_query cl_khr_fp16 cl_khr_fp64 cl_ext_buffer_device_address cl_khr_subgroup_ballot cl_khr_subgroup_shuffle
    Device Extensions with Version                  cl_khr_byte_addressable_store                                    0x400000 (1.0.0)
                                                    cl_khr_global_int32_base_atomics                                 0x400000 (1.0.0)
                                                    cl_khr_global_int32_extended_atomics                             0x400000 (1.0.0)
                                                    cl_khr_local_int32_base_atomics                                  0x400000 (1.0.0)
                                                    cl_khr_local_int32_extended_atomics                              0x400000 (1.0.0)
                                                    cl_khr_int64_base_atomics                                        0x400000 (1.0.0)
                                                    cl_khr_int64_extended_atomics                                    0x400000 (1.0.0)
                                                    cl_nv_device_attribute_query                                     0x400000 (1.0.0)
                                                    cl_khr_fp16                                                      0x400000 (1.0.0)
                                                    cl_khr_fp64                                                      0x400000 (1.0.0)
                                                    cl_ext_buffer_device_address                                       0x1000 (0.1.0)
                                                    cl_khr_subgroup_ballot                                           0x400000 (1.0.0)
                                                    cl_khr_subgroup_shuffle                                          0x400000 (1.0.0)

    Platform Name                                   Intel(R) OpenCL
    Number of devices                                 1
    Device Name                                     Intel(R) Xeon(R) Gold 5218 CPU @ 2.30GHz
    Device Vendor                                   Intel(R) Corporation
    Device Vendor ID                                0x8086
    Device Version                                  OpenCL 3.0 (Build 0)
    Device Numeric Version                          0xc00000 (3.0.0)
    Driver Version                                  2024.18.12.0.05_160000
    Device OpenCL C Version                         OpenCL C 3.0 
    Device OpenCL C all versions                    OpenCL C                                                         0xc00000 (3.0.0)
                                                    OpenCL C                                                         0x800000 (2.0.0)
                                                    OpenCL C                                                         0x402000 (1.2.0)
                                                    OpenCL C                                                         0x401000 (1.1.0)
                                                    OpenCL C                                                         0x400000 (1.0.0)
    Device OpenCL C features                        __opencl_c_3d_image_writes                                       0xc00000 (3.0.0)
                                                    __opencl_c_atomic_order_acq_rel                                  0xc00000 (3.0.0)
                                                    __opencl_c_atomic_order_seq_cst                                  0xc00000 (3.0.0)
                                                    __opencl_c_atomic_scope_device                                   0xc00000 (3.0.0)
                                                    __opencl_c_atomic_scope_all_devices                              0xc00000 (3.0.0)
                                                    __opencl_c_device_enqueue                                        0xc00000 (3.0.0)
                                                    __opencl_c_generic_address_space                                 0xc00000 (3.0.0)
                                                    __opencl_c_fp64                                                  0xc00000 (3.0.0)
                                                    __opencl_c_images                                                0xc00000 (3.0.0)
                                                    __opencl_c_int64                                                 0xc00000 (3.0.0)
                                                    __opencl_c_pipes                                                 0xc00000 (3.0.0)
                                                    __opencl_c_program_scope_global_variables                        0xc00000 (3.0.0)
                                                    __opencl_c_read_write_images                                     0xc00000 (3.0.0)
                                                    __opencl_c_subgroups                                             0xc00000 (3.0.0)
                                                    __opencl_c_work_group_collective_functions                       0xc00000 (3.0.0)
    Latest comfornace test passed                   v2023-10-10-00
    Device Type                                     CPU
    Device Profile                                  FULL_PROFILE
    Device Available                                Yes
    Compiler Available                              Yes
    Linker Available                                Yes
    Max compute units                               64
    Max clock frequency                             2300MHz
    Device Partition                                (core)
        Max number of sub-devices                     64
        Supported partition types                     by counts, equally, by names (Intel), by affinity domain
        Supported affinity domains                    NUMA, next partitionable
    Max work item dimensions                        3
    Max work item sizes                             8192x8192x8192
    Max work group size                             8192
    Preferred work group size multiple (device)     128
    Preferred work group size multiple (kernel)     128
    Max sub-groups per work group                   2048
    Sub-group sizes (Intel)                         4, 8, 16, 32, 64
    Preferred / native vector sizes                 
        char                                                 1 / 64      
        short                                                1 / 32      
        int                                                  1 / 16      
        long                                                 1 / 8       
        half                                                 1 / 32       (cl_khr_fp16)
        float                                                1 / 16      
        double                                               1 / 8        (cl_khr_fp64)
    Half-precision Floating-point support           (cl_khr_fp16)
        Denormals                                     No
        Infinity and NANs                             Yes
        Round to nearest                              Yes
        Round to zero                                 No
        Round to infinity                             No
        IEEE754-2008 fused multiply-add               No
        Support is emulated in software               No
    Single-precision Floating-point support         (core)
        Denormals                                     Yes
        Infinity and NANs                             Yes
        Round to nearest                              Yes
        Round to zero                                 No
        Round to infinity                             No
        IEEE754-2008 fused multiply-add               No
        Support is emulated in software               No
        Correctly-rounded divide and sqrt operations  No
    Double-precision Floating-point support         (cl_khr_fp64)
        Denormals                                     Yes
        Infinity and NANs                             Yes
        Round to nearest                              Yes
        Round to zero                                 Yes
        Round to infinity                             Yes
        IEEE754-2008 fused multiply-add               Yes
        Support is emulated in software               No
    Address bits                                    64, Little-Endian
    Global memory size                              404309209088 (376.5GiB)
    Error Correction support                        No
    Max memory allocation                           202154604544 (188.3GiB)
    Unified memory for Host and Device              Yes
    Shared Virtual Memory (SVM) capabilities        (core)
        Coarse-grained buffer sharing                 Yes
        Fine-grained buffer sharing                   Yes
        Fine-grained system sharing                   Yes
        Atomics                                       Yes
    Minimum alignment for any data type             128 bytes
    Alignment of base address                       1024 bits (128 bytes)
    Preferred alignment for atomics                 
        SVM                                           64 bytes
        Global                                        64 bytes
        Local                                         0 bytes
    Atomic memory capabilities                      relaxed, acquire/release, sequentially-consistent, work-group scope, device scope, all-devices scope
    Atomic fence capabilities                       relaxed, acquire/release, sequentially-consistent, work-item scope, work-group scope, device scope, all-devices scope
    Max size for global variable                    65536 (64KiB)
    Preferred total size of global vars             65536 (64KiB)
    Global Memory cache type                        Read/Write
    Global Memory cache size                        262144 (256KiB)
    Global Memory cache line size                   64 bytes
    Image support                                   Yes
        Max number of samplers per kernel             480
        Max size for 1D images from buffer            12634662784 pixels
        Max 1D or 2D image array size                 2048 images
        Base address alignment for 2D image buffers   64 bytes
        Pitch alignment for 2D image buffers          64 pixels
        Max 2D image size                             16384x16384 pixels
        Max 3D image size                             2048x2048x2048 pixels
        Max number of read image args                 480
        Max number of write image args                480
        Max number of read/write image args           480
    Pipe support                                    Yes
    Max number of pipe args                         16
    Max active pipe reservations                    4095
    Max pipe packet size                            1024
    Local memory type                               Global
    Local memory size                               262144 (256KiB)
    Max number of constant args                     480
    Max constant buffer size                        131072 (128KiB)
    Generic address space support                   Yes
    Max size of kernel argument                     3840 (3.75KiB)
    Queue properties (on host)                      
        Out-of-order execution                        Yes
        Profiling                                     Yes
        Local thread execution (Intel)                Yes
    Device enqueue capabilities                     supported, replaceable default queue
    Queue properties (on device)                    
        Out-of-order execution                        Yes
        Profiling                                     Yes
        Preferred size                                4294967295 (4GiB)
        Max size                                      4294967295 (4GiB)
    Max queues on device                            4294967295
    Max events on device                            4294967295
    Prefer user sync for interop                    No
    Profiling timer resolution                      1ns
    Execution capabilities                          
        Run OpenCL kernels                            Yes
        Run native kernels                            Yes
        Non-uniform work-groups                       Yes
        Work-group collective functions               Yes
        Sub-group independent forward progress        No
        IL version                                    SPIR-V_1.0 SPIR-V_1.1 SPIR-V_1.2 SPIR-V_1.3 SPIR-V_1.4
        ILs with version                              SPIR-V                                                           0x400000 (1.0.0)
                                                    SPIR-V                                                           0x401000 (1.1.0)
                                                    SPIR-V                                                           0x402000 (1.2.0)
                                                    SPIR-V                                                           0x403000 (1.3.0)
                                                    SPIR-V                                                           0x404000 (1.4.0)
        SPIR versions                                 1.2
    printf() buffer size                            1048576 (1024KiB)
    Built-in kernels                                (n/a)
    Built-in kernels with version                   (n/a)
    Device Extensions                               cl_khr_spirv_linkonce_odr cl_khr_fp64 cl_khr_fp16 cl_khr_global_int32_base_atomics cl_khr_global_int32_extended_atomics cl_khr_local_int32_base_atomics cl_khr_local_int32_extended_atomics cl_khr_3d_image_writes cl_khr_byte_addressable_store cl_khr_depth_images cl_khr_extended_bit_ops cl_khr_icd cl_khr_il_program cl_khr_suggested_local_work_size cl_intel_unified_shared_memory cl_intel_devicelib_assert cl_khr_subgroup_ballot cl_khr_subgroup_shuffle cl_khr_subgroup_shuffle_relative cl_khr_subgroup_extended_types cl_khr_subgroup_non_uniform_arithmetic cl_khr_subgroup_non_uniform_vote cl_khr_subgroup_clustered_reduce cl_intel_subgroups cl_intel_subgroups_char cl_intel_subgroups_short cl_intel_subgroups_long cl_intel_required_subgroup_size cl_intel_spirv_subgroups cl_khr_int64_base_atomics cl_khr_int64_extended_atomics cl_intel_device_attribute_query cl_intel_exec_by_local_thread cl_intel_vec_len_hint cl_intel_device_partition_by_names cl_khr_spir cl_khr_image2d_from_buffer cl_intel_concurrent_dispatch
    Device Extensions with Version                  cl_khr_spirv_linkonce_odr                                        0x400000 (1.0.0)
                                                    cl_khr_fp64                                                      0x400000 (1.0.0)
                                                    cl_khr_fp16                                                      0x400000 (1.0.0)
                                                    cl_khr_global_int32_base_atomics                                 0x400000 (1.0.0)
                                                    cl_khr_global_int32_extended_atomics                             0x400000 (1.0.0)
                                                    cl_khr_local_int32_base_atomics                                  0x400000 (1.0.0)
                                                    cl_khr_local_int32_extended_atomics                              0x400000 (1.0.0)
                                                    cl_khr_3d_image_writes                                           0x400000 (1.0.0)
                                                    cl_khr_byte_addressable_store                                    0x400000 (1.0.0)
                                                    cl_khr_depth_images                                              0x400000 (1.0.0)
                                                    cl_khr_extended_bit_ops                                          0x400000 (1.0.0)
                                                    cl_khr_icd                                                       0x400000 (1.0.0)
                                                    cl_khr_il_program                                                0x400000 (1.0.0)
                                                    cl_khr_suggested_local_work_size                                 0x400000 (1.0.0)
                                                    cl_intel_unified_shared_memory                                   0x400000 (1.0.0)
                                                    cl_intel_devicelib_assert                                        0x400000 (1.0.0)
                                                    cl_khr_subgroup_ballot                                           0x400000 (1.0.0)
                                                    cl_khr_subgroup_shuffle                                          0x400000 (1.0.0)
                                                    cl_khr_subgroup_shuffle_relative                                 0x400000 (1.0.0)
                                                    cl_khr_subgroup_extended_types                                   0x400000 (1.0.0)
                                                    cl_khr_subgroup_non_uniform_arithmetic                           0x400000 (1.0.0)
                                                    cl_khr_subgroup_non_uniform_vote                                 0x400000 (1.0.0)
                                                    cl_khr_subgroup_clustered_reduce                                 0x400000 (1.0.0)
                                                    cl_intel_subgroups                                               0x400000 (1.0.0)
                                                    cl_intel_subgroups_char                                          0x400000 (1.0.0)
                                                    cl_intel_subgroups_short                                         0x400000 (1.0.0)
                                                    cl_intel_subgroups_long                                          0x400000 (1.0.0)
                                                    cl_intel_required_subgroup_size                                  0x400000 (1.0.0)
                                                    cl_intel_spirv_subgroups                                         0x400000 (1.0.0)
                                                    cl_khr_int64_base_atomics                                        0x400000 (1.0.0)
                                                    cl_khr_int64_extended_atomics                                    0x400000 (1.0.0)
                                                    cl_intel_device_attribute_query                                  0x400000 (1.0.0)
                                                    cl_intel_exec_by_local_thread                                    0x400000 (1.0.0)
                                                    cl_intel_vec_len_hint                                            0x400000 (1.0.0)
                                                    cl_intel_device_partition_by_names                               0x400000 (1.0.0)
                                                    cl_khr_spir                                                      0x400000 (1.0.0)
                                                    cl_khr_image2d_from_buffer                                       0x400000 (1.0.0)
                                                    cl_intel_concurrent_dispatch                                     0x400000 (1.0.0)


    NULL platform behavior
    clGetPlatformInfo(NULL, CL_PLATFORM_NAME, ...)  Portable Computing Language
    clGetDeviceIDs(NULL, CL_DEVICE_TYPE_ALL, ...)   Success [POCL]
    clCreateContext(NULL, ...) [default]            Success [POCL]
    clCreateContext(NULL, ...) [other]              Success [INTEL]
    clCreateContextFromType(NULL, CL_DEVICE_TYPE_DEFAULT)  Success (1)
        Platform Name                                 Portable Computing Language
        Device Name                                   cpu-cascadelake-Intel(R) Xeon(R) Gold 5218 CPU @ 2.30GHz
    clCreateContextFromType(NULL, CL_DEVICE_TYPE_CPU)  Success (1)
        Platform Name                                 Portable Computing Language
        Device Name                                   cpu-cascadelake-Intel(R) Xeon(R) Gold 5218 CPU @ 2.30GHz
    clCreateContextFromType(NULL, CL_DEVICE_TYPE_GPU)  Success (1)
        Platform Name                                 Portable Computing Language
        Device Name                                   NVIDIA GeForce RTX 2080 Ti
    clCreateContextFromType(NULL, CL_DEVICE_TYPE_ACCELERATOR)  No devices found in platform
    clCreateContextFromType(NULL, CL_DEVICE_TYPE_CUSTOM)  No devices found in platform
    clCreateContextFromType(NULL, CL_DEVICE_TYPE_ALL)  Success (2)
        Platform Name                                 Portable Computing Language
        Device Name                                   cpu-cascadelake-Intel(R) Xeon(R) Gold 5218 CPU @ 2.30GHz
        Device Name                                   NVIDIA GeForce RTX 2080 Ti

    ICD loader properties
    ICD loader Name                                 OpenCL ICD Loader
    ICD loader Vendor                               OCL Icd free software
    ICD loader Version                              2.2.14
    ICD loader Profile                              OpenCL 3.0

While this result is quite verbose, we can see that Platform 1 is :code:`Intel(R) OpenCL` and Device 0 is :code:`Intel(R) Xeon(R) Gold 5218 CPU @ 2.30GHz`.  This is the platform and device index we are interested in to best match Gradescope.

Therefore, to reproduce the results that Gradescope has, we can execute :code:`PLATFORM_INDEX=1 DEVICE_INDEX=0 make run`.
