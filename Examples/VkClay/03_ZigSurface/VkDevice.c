#include "VkObjects.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

VkDevice device;

VkPhysicalDevice selectPhysicalDevice()
{
    // Now we're going to select the most appropriate physical device
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);
    if (deviceCount == 0) {
        printf("Could not find any physical devices compatible with Vulkan\n");
        exit(-1);
    }

    VkPhysicalDevice *devices = malloc(deviceCount * sizeof(VkPhysicalDevice));
    if (!devices) {
        printf("Could not allocate space for all the physical devices\n");
        exit(-1);
    }

    vkEnumeratePhysicalDevices(instance, &deviceCount, devices);

    // for now just return the first one
    return devices[0];
}

// Creates the graphics and presentation queues globally
void createDeviceQueues(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
{
    // We now need to find all of the necessary queues, which is one for compute and one for presentation
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, NULL);
    VkQueueFamilyProperties *queueFamilyProps = malloc(queueFamilyCount * sizeof(VkQueueFamilyProperties));

    if (!queueFamilyProps) {
        printf("Could not allocate space for queue family properties\n");
        exit(-1);
    }

    bool graphicsQueueFound = false;
    bool presentQueueFound = false;
    uint32_t graphicsQueueIndex;
    uint32_t presentQueueIndex;

    for (uint32_t i = 0; i < queueFamilyCount; i++) {
        // once both queues are found stop searching
        if (graphicsQueueFound && presentQueueFound) break;

        if (!graphicsQueueFound && (queueFamilyProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
            graphicsQueueFound = true;
            graphicsQueueIndex = i;
        }

        // Need to make a call to
        // vkGetPhysicalDeviceSurfaceSupportKHR
    }

    if (!(graphicsQueueFound && presentQueueFound)) {
        printf("Could not find the required queues\n");
        exit(-1);
    }
}

// The external function that is actually called
void createDevice()
{
    // First select the physical device, as this is minimal we'll likely pick the first one
    VkPhysicalDevice physicalDevice = selectPhysicalDevice();

    // Now we need to create the surface, this is a whole extra section
    const char *surfaceDeviceExtensionName = createSurface(physicalDevice);
}
