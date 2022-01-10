/**
 * This example covers how you can use Zig and VkClay together inorder to create a Vulkan surface
 * From here you can dgo about completing full Vulkan projects (Hopefully)
 */

#include "VkClay/VkClay.h"
#include "VkObjects.h"  // This header handles all the Vulkan object creation for us

int main(int argc, char* argv[])
{
    // Open the Vulkan Library and the global function pointers
    vkc_LoadVulkan();

    // Create the Vulkan instance
    createInstance();
}
