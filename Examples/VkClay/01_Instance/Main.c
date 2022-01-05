/**
 * Example VkClay_01_Instance covers how to make a vulkan instance through VkClay
 */
#include "VkClay/VkClay.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    // Open the Vulkan Library
    vkc_LoadVulkan();

    // Now that the function pointers neccacary for creating a Vulkan instance are ready, lets create a Vulkan
    // instance

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

    VkInstance instance;
    if (vkCreateInstance(&instanceInfo, NULL, &instance) != VK_SUCCESS) {
        printf("Failed to create instance\n");
    } else {
        printf("Created Vulkan Instance!\n");
    }
}
