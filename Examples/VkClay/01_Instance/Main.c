/**
 * Example VkClay_01_Instance covers how to make a vulkan instance through VkClay
 */
#include "VkClay/VkClay.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    // Open the Vulkan Library and the global function pointer

    // This provides us with the bare minimum functions for creating an instance
    // vkEnumerateInstanceVersion - If loader version on the device > 1.0 else null
    // vkEnumerateInstanceExtensionProperties
    // vkEnumerateInstanceLayerProperties
    // vkGetInstanceProcAddr
    // vkCreateInstance
    if (vkc_LoadVulkan() != vkc_success) {
        printf("Failed to open the Vulkan library");
        exit(-1);
    }

    // Create very basic instance create info
    VkInstanceCreateInfo instanceInfo;
    memset(&instanceInfo, 0, sizeof(VkInstanceCreateInfo));
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

    VkApplicationInfo appInfo;
    memset(&appInfo, 0, sizeof(VkApplicationInfo));
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

    appInfo.apiVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
    appInfo.pApplicationName = "VkClayTester";
    appInfo.pEngineName = "VkClay";
    instanceInfo.pApplicationInfo = &appInfo;

    // Use the instance info to create a Vulkan instance
    VkInstance instance;
    if (vkCreateInstance(&instanceInfo, NULL, &instance) != VK_SUCCESS) {
        printf("Failed to create instance\n");
        return -1;
    } else {
        printf("Created Vulkan Instance!\n");
    }

    // Let's prove that we've loaded the instance functions by using one
    uint32_t physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, NULL);
    VkPhysicalDevice* physicalDevices;

    if (physicalDeviceCount) {
        physicalDevices = malloc(physicalDeviceCount * sizeof(VkPhysicalDevice));
        if (physicalDevices) {
            vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices);

            for (uint32_t i = 0; i < physicalDeviceCount; i++) {
                VkPhysicalDeviceProperties props;
                vkGetPhysicalDeviceProperties(physicalDevices[i], &props);

                printf(" * Physical device %i:\n\t%s", i, props.deviceName);
            }

        } else {
            printf("Whoops, couldn't allocate space for the list of physical devices\n");
        }
    }
}
