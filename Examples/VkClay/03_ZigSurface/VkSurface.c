/**
 * Vulkan surface creation in a crossplatform manner is pretty involved, and usually relies on preprocessor
 * statements selecting the right include headers, and then changing depending on which type of surface you're
 * using
 *
 * Swiftshader has XCB not X11, wayland can sometimes run X Apps, -> we'll use XCB
 * Windows -> Win32
 * Android -> Android
 * Mac or ios -> Metal
 */

#ifdef WIN32
#define VK_USE_PLATFORM_WIN32_KHR (1)
#elif defined __ANDROID__
#define VK_USE_PLATFORM_ANDROID_KHR (1)
#elif defined __linux__
#define VK_USE_PLATFORM_XCB_KHR (1)
#elif defined __apple__
#define VK_USE_PLATFORM_METAL_EXT(1)
#endif

#include "VkObjects.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Global surface handle
VkSurfaceKHR surface;

const char* createSurface(VkPhysicalDevice physicalDevice)
{
    // Now that we're creating a surface now would be a good time to fire up Zig

    // Unfortunatley we need to split this up depending on the windowing system being used
    // We have guessed at which platform is being used based on the OS

    /**
     * Windows
     */
#ifdef VK_USE_PLATFORM_WIN32_KHR
    return "win32";

    /**
     * Android Native
     */
#elif defined VK_USE_PLATFORM_ANDROID_KHR
    return "android";

    /**
     * Linux XCB
     */
#elif defined VK_USE_PLATFORM_XCB_KHR
    return "xcb";

    /**
     * ios and macos Metal
     */
#elif defined VK_USE_PLATFORM_METAL_EXT
    return "metal";

    /**
     * OOps
     */
#else
    return "None";
#endif  // VK_USE_PLATFORM_WIN32_KHR
}
