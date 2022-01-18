/**
 * Handles the instance creation and the selection of the instance level extensions to be used
 */

#include "VkObjects.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

VkInstance instance;

// Are we using validation layers or not
#ifndef NDEBUG
#define TRY_VALIDATION_LAYERS (1)
#endif  // !NDEBUG

void createInstance()
{
    // Start by selecting the instance extensions that we want to use
    char* requestedInstanceExtensionNames[] = {"VK_KHR_surface", "VK_EXT_debug_utils"};
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

    // Validate that all of the requested instance extensions are supported
    char** validatedInstanceExtensions = malloc(requestedIECount * sizeof(char*));
    uint32_t validatedInstanceExtensionCount = 0;

    if (validatedInstanceExtensions) {
        // Loop through each of the requested instance extension to see if they are found
        for (uint32_t i = 0; i < requestedIECount; i++) {
            char* extName = requestedInstanceExtensionNames[i];

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
                if (!strcmp(extName, "VK_KHR_surface")) {
                    "Could not find support for the surface extension, meaning this demo won't work here\n";
                    exit(-1);
                }
            } else {
                // Extension has been found so save it
                validatedInstanceExtensions[validatedInstanceExtensionCount] = malloc(strlen(extName) + 1);
                if (!validatedInstanceExtensions[validatedInstanceExtensionCount]) continue;
                memcpy(validatedInstanceExtensions[validatedInstanceExtensionCount], extName,
                       strlen(extName) + 1);
                validatedInstanceExtensionCount++;
            }
        }
    } else {
        printf(
          "Could not allocate space for the validated instance extensions\n"
          "And we need at least surface extension support");
        exit(-1);
    }

    // Now let's check for validation layers
    bool validationLayersSupported = false;

#ifdef TRY_VALIDATION_LAYERS  // Dont need to search on release mode
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, NULL);
    VkLayerProperties* layerProps = malloc(layerCount * sizeof(VkLayerProperties));
    if (layerProps) {
        vkEnumerateInstanceLayerProperties(&layerCount, layerProps);

        // Now we need to search through all of the layers for validation layers
        for (uint32_t i = 0; i < layerCount; i++) {
            if (!strcmp("VK_LAYER_KHRONOS_validation", layerProps[i].layerName)) {
                validationLayersSupported = true;
            }
        }

    } else {
        printf(
          "Could not allocate space for the instance layer properties\n"
          "We will be acting as if there are no layers supported\n");
    }

    // Did the user request the validation layers and not get them
    if (!validationLayersSupported) {
        printf("Warning : Requested validation layers, but could not find them\n");
    }
#endif

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
    instanceinfo.enabledExtensionCount = validatedInstanceExtensionCount;
    instanceinfo.ppEnabledExtensionNames = validatedInstanceExtensions;

    // Does the user still have the validation layers enabled, if so let's add it to the instance
    const char* validationLayerName = "VK_LAYER_KHRONOS_validation";
    if (validationLayersSupported) {
        instanceinfo.ppEnabledLayerNames = &validationLayerName;
        instanceinfo.enabledLayerCount = 1;
    }

    if (vkCreateInstance(&instanceinfo, NULL, &instance) != VK_SUCCESS) {
        printf("Could not create Vulkan instance, exiting\n");
        exit(-1);
    } else {
        printf("Created Vulkan Instance\n");
    }

    // Create a debug messenger if layers are supported and the debug utils extension as well
    // There is only 2 instance extensions, and surface is required. If we have two validated
    // then we know debug utils is supported
    if (validationLayersSupported && validatedInstanceExtensionCount >= 2) createDebugMessenger();
}

// A variable to tell if we're using a debug messenger for creation and destruction
bool _usingDebugMessenger = false;
VkDebugUtilsMessengerEXT _messenger;

static VKAPI_ATTR VkBool32 VKAPI_CALL callbackMessenger(
  VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
    // Only report this when the message serverity is high enough
    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        printf("Debug messenger warning : \n\t%s\n", pCallbackData->pMessage);
    }
}

void createDebugMessenger()
{
    // This has been called, so store that the debug messenger will be destroyed
    _usingDebugMessenger = true;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    memset(&createInfo, 0, sizeof(VkDebugUtilsMessengerCreateInfoEXT));
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

    createInfo.pfnUserCallback = callbackMessenger;

    // Notice how we didn't have to load the function pointers!
    if (vkCreateDebugUtilsMessengerEXT(instance, &createInfo, NULL, &_messenger) != VK_SUCCESS) {
        printf("Failed to create Debug Messenger\n");
    } else {
        printf("Created Debug Messenger\n");

        _usingDebugMessenger = false;
    }
}
