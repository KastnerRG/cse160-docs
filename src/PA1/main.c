#include <stdio.h>
#include <CL/cl.h>

#define MAX_INFO_STRING_SIZE 256

/*! \verbatim embed:rst:leading-asterisk
 * Query all platforms and all the devices on those platforms and display information
 * about the platform.
 * \endverbatim
*/
int main(int argc, char **argv) {
    cl_platform_id platforms[10];
    cl_device_id device;
    cl_uint num_platforms, num_devices; 
    cl_int err;

    // Get platform count
    err = clGetPlatformIDs(10, platforms, &num_platforms);
    if (err != CL_SUCCESS || num_platforms == 0) {
        printf("Error getting platform IDs\n");
        return 1;
    }

    printf("INITIAL: Number of Platforms Discovered -> %u\n\n", num_platforms);

    // Iterate through all platforms 
    for (int i = 0; i < num_platforms; i++) {
        cl_platform_id platform = platforms[i];
        // Get devices and number of devices
        err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, &num_devices);
        if (err != CL_SUCCESS || num_devices == 0) {
            printf("Error getting GPU device IDs\n");   
            return 1;
        }

        //iterate through devices in the platform
        for (int dev = 0; dev < num_devices; dev++) {
            cl_device_id current_device = device;
            char device_name[MAX_INFO_STRING_SIZE];
            cl_device_type device_type;
            cl_uint compute_units;
            cl_ulong global_mem_size;
            cl_ulong constant_mem_size;
            cl_ulong local_mem_size;
            size_t max_work_item_sizes[3];
            size_t max_work_group_size;
            size_t max_work_item_dimensions;
            size_t preferred_work_group_size_multiple;

            clGetDeviceInfo(current_device, CL_DEVICE_NAME, sizeof(device_name), device_name, NULL); // Name of device
            clGetDeviceInfo(current_device, CL_DEVICE_TYPE, sizeof(device_type), &device_type, NULL); // Type of device; CL_DEVICE_TYPE enumerates device type
            clGetDeviceInfo(current_device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(compute_units), &compute_units, NULL);  // # of streaming multiprocessors
            clGetDeviceInfo(current_device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(global_mem_size), &global_mem_size, NULL); // Global memory size
            clGetDeviceInfo(current_device, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(constant_mem_size), &constant_mem_size, NULL); // Constant memory size
            clGetDeviceInfo(current_device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(local_mem_size), &local_mem_size, NULL); // Size of local memory (analagously shared mem in cuda)
            clGetDeviceInfo(current_device, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(max_work_item_sizes), max_work_item_sizes, NULL); 
            clGetDeviceInfo(current_device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(max_work_group_size), &max_work_group_size, NULL);
            clGetDeviceInfo(current_device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(max_work_item_dimensions), &max_work_item_dimensions, NULL); // max # of dimensions for a work group 

            printf("Device %d name: %s\n", dev, device_name);
            
            printf("Device Type: ");
            
            // Print out type of device
            if (device_type & CL_DEVICE_TYPE_DEFAULT) {
                printf("Default\n");
            } else if (device_type & CL_DEVICE_TYPE_CPU) {
                printf("CPU\n");
            } else if (device_type & CL_DEVICE_TYPE_GPU) {
                printf("GPU\n");
            } else if (device_type & CL_DEVICE_TYPE_ACCELERATOR) {
                printf("Accelerator\n");
            } else {
                printf("\n");
            }

            // Display device properties
            printf("Computational Capabilities: %d\n", compute_units);
            printf("Maximum global memory size: %lu bytes\n", global_mem_size);
            printf("Maximum constant memory size: %lu bytes\n", constant_mem_size);
            printf("Maximum shared memory size per Compute Unit: %lu bytes\n", local_mem_size);
            printf("Maximum Work Item size: %zu x %zu x %zu\n", max_work_item_sizes[0], max_work_item_sizes[1], max_work_item_sizes[2]);
            printf("Maximum Work Item dimensions: %zu\n", max_work_item_dimensions);
            printf("Maximum Group Size: %zu\n", max_work_group_size);
            printf("\n");
        }
            
    }
    return 0;
}
