/**
 * This file handles all of the opaque Vulkan objects
 */

#include "VkClay/VkClay.h"

/**
 * Vulkan object declarations
 */

// The Vulkan instance
extern VkInstance instance;
extern VkDevice device;
extern VkSurfaceKHR surface;

/**
 * Methods for creating the Vulkan objects
 */

/**
 * @brief Creates the Vulkan instance
 */
void createInstance();

void createDebugMessenger();

void createDevice();

/**
 * @brief creates a Vulkan surface and starts Zig
 * @param physicalDevice is the physical device being used to create the surface
 * @returns The name of the device extension used to load the surface
 */
const char* createSurface(VkPhysicalDevice physicalDevice);
