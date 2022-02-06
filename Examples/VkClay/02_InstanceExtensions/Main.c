/**
 * Example VkClay_01_Instance covers how to make a vulkan instance through VkClay
 */
#include "VkClay/VkClay.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    // Open the Vulkan Library and the global function pointers
    if (vkc_LoadVulkan() != vkc_success) {
        printf("Failed to open the Vulkan library");
        exit(-1);
    }

    // Now, using the global level functions check if the device we're looking for supports the extension
    uint32_t instanceExtCount = 0;
    vkEnumerateInstanceExtensionProperties(NULL, &instanceExtCount, NULL);

    // Allocate space for the instance extension props
    VkExtensionProperties* extprops;
    if (instanceExtCount) {
        extprops = malloc(instanceExtCount * sizeof(VkExtensionProperties));
        if (!extprops) return -1;
    } else {
        printf("Could not load the number of instance extensions\n");
        return -1;
    }

    // Actually fill in the instance extension properties
    vkEnumerateInstanceExtensionProperties(NULL, &instanceExtCount, extprops);

    // Loop through each of the extensions looking for
    const char* extensionName = "VK_KHR_get_physical_device_properties2";
    bool foundExt = false;
    for (uint32_t i = 0; i < instanceExtCount; i++) {
        if (!strcmp(extensionName, extprops[i].extensionName)) {
            foundExt = true;
            break;
        }
    }

    // Was the instance extension found?
    if (!foundExt) {
        printf("We've not been able to find the following instance extension : %s\n", extensionName);
        return -1;
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

    // Since we got this far we can assume the instance extension was found
    // So add it into the list of extensions to load
    instanceInfo.enabledExtensionCount = 1;
    instanceInfo.ppEnabledExtensionNames = &extensionName;

    // Use the instance info to create a Vulkan instance
    VkInstance instance;
    if (vkCreateInstance(&instanceInfo, NULL, &instance) != VK_SUCCESS) {
        printf("Failed to create instance\n");
        return -1;
    } else {
        printf("Created Vulkan Instance!\n");
    }

    // Let's prove that we've loaded the extension function pointers by using one
    // Note that since our instance version is 1.0.0, VkPhysicalDeviceProperties2KHR is not in Core
    // So the instance extension has to be enabled to avoid getting a nullptr from this function
    uint32_t physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, NULL);
    VkPhysicalDevice* physicalDevices;

    if (physicalDeviceCount) {
        physicalDevices = malloc(physicalDeviceCount * sizeof(VkPhysicalDevice));
        if (physicalDevices) {
            vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices);

            for (uint32_t i = 0; i < physicalDeviceCount; i++) {
                VkPhysicalDeviceProperties2KHR props;
                memset(&props, 0, sizeof(VkPhysicalDeviceProperties2KHR));
                props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2_KHR;

                vkGetPhysicalDeviceProperties2KHR(physicalDevices[i], &props);

                printf(" * Physical device %i:\n\t%s\n", i, props.properties.deviceName);
            }

        } else {
            printf("Whoops, couldn't allocate space for the list of physical devices\n");
        }
    }
}
