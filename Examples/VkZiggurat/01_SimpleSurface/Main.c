/**
 * This example covers how you can use Zig and VkClay together inorder to create a Vulkan surface
 * From here you can dgo about completing full Vulkan projects (Hopefully)
 *
 * Ziggurat includes VkClay for you, it also demands that you have defined a windowing system
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ziggurat/Ziggurat.h"

// Vulkan Objects
VkInstance instance;
VkSurfaceKHR surface;

// Forward declared functions for creating the instance
void createInstance();

int main(int argc, char* argv[])
{
    // Open the Vulkan Library and the global function pointers
    vkc_LoadVulkan();

    // Create the Vulkan instance
    createInstance();

    // Now lets start ziggurat and use it to create a surface
    zig_ShowWindow(640, 480);
    zigenum res = zig_CreateVulkanSurface(&surface, instance);
    if (res != zig_success) {
        printf("Zig failed to create a surface!!\n");
    } else {
        printf("Ziggurat surface created\n");
    }

    // Enter the windowing loop
    while (zig_WindowLoopContinues()) {
        // Check the zigurrat events
        zig_ProcessEvents();
    }

    // Windowing loop has finished, so let's cleanup
}

void createInstance()
{
    // First check that Ziggurat was built with a windowing system in mind
    if (zig_GetVulkanSurfaceEXTName() == NULL) {
        printf("Ziggurat was not build with a surface defined!\n");
        exit(-1);
    }

    // Start by selecting the instance extensions that we want to use
    const char* requestedInstanceExtensionNames[] = {"VK_KHR_surface", zig_GetVulkanSurfaceEXTName()};
    uint32_t requestedIECount = 2;

    // Obtain a list of supported instance extensions
    uint32_t supportedIECount = 0;
    vkEnumerateInstanceExtensionProperties(NULL, &supportedIECount, NULL);
    VkExtensionProperties* extProps = malloc(supportedIECount * sizeof(VkExtensionProperties));

    if (extProps) {
        vkEnumerateInstanceExtensionProperties(NULL, &supportedIECount, extProps);
    } else {
        printf(
          "Could not allocate space for the supported instance extensions\n"
          "And we need at least surface support\n");
        exit(-1);
    }

    // Loop through each of the requested instance extension to see if they are found
    for (uint32_t i = 0; i < requestedIECount; i++) {
        const char* extName = requestedInstanceExtensionNames[i];

        // Search through the list of instance extensions for this extension
        bool extFound = false;
        for (uint32_t j = 0; j < supportedIECount; j++) {
            if (!strcmp(extName, extProps[j].extensionName)) {
                // We've found the extension name
                extFound = true;
                break;
            }
        }

        // Have we found this instance extension?
        if (!extFound) {
            // Report any not found extensions
            printf("Unable to find support for the following instance extension : %s\n", extName);
            exit(-1);
        }
    }

    // Now create an application info structure
    VkApplicationInfo appinfo;
    memset(&appinfo, 0, sizeof(VkApplicationInfo));
    appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appinfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);
    appinfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appinfo.pEngineName = "VkClay";
    appinfo.pApplicationName = "VkClayZigExample";

    // Create the Vulkan instance create info
    VkInstanceCreateInfo instanceinfo;
    memset(&instanceinfo, 0, sizeof(VkInstanceCreateInfo));
    instanceinfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceinfo.pApplicationInfo = &appinfo;
    instanceinfo.enabledExtensionCount = requestedIECount;
    instanceinfo.ppEnabledExtensionNames = requestedInstanceExtensionNames;

    if (vkCreateInstance(&instanceinfo, NULL, &instance) != VK_SUCCESS) {
        printf("Could not create Vulkan instance, exiting\n");
        exit(-1);
    } else {
        printf("Created Vulkan Instance\n");

        printf("Using the following instance extensions :\n");
        for (uint32_t i = 0; i < instanceinfo.enabledExtensionCount; i++) {
            printf("\t* %s\n", instanceinfo.ppEnabledExtensionNames[i]);
        }
    }
}
