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

/**
 * @breif Searches an array of strings for a specific string
 * @param stringList Is the array being searched
 * @param string Is the string being searched for
 * @returns True if the array contains a copy of that string
 */
bool searchArrayForString(const char** stringList, const char* string)
{
    // Start by getting the array length
    uint32_t arrayLength = sizeof(stringList) / sizeof(char*);
    bool found = false;

    for (uint32_t i = 0; i < arrayLength; i++) {
        if (!strcmp(stringList[i], string)) {
            // Found the key we're looking for
            found = true;
            break;
        }
    }

    return found;
}

void createInstance()
{
    // Start by selecting the instance extensions that we want to use
    char* instanceExtensionNames[] = {"VK_KHR_surface"};

    // Obtain a list of supported instance extensions
    uint32_t instanceExtensionCount = 0;
    vkEnumerateInstanceExtensionProperties(NULL, &instanceExtensionCount, NULL);
    VkExtensionProperties* extProps = malloc(instanceExtensionCount * sizeof(VkExtensionProperties));

    if (extProps) {
        vkEnumerateInstanceExtensionProperties(NULL, &instanceExtensionCount, extProps);
    } else {
        printf("Could not allocate space for the instance extensions\n");
        exit(-1);
    }

    // Validate that all of the requested instance extensions are supported
    uint32_t extCount = sizeof(instanceExtensionNames) / sizeof(char*);
    char** validatedInstanceExtensions = malloc(extCount * sizeof(char*));
    uint32_t validatedInstanceExtensionCount = 0;

    for (uint32_t i = 0; i < extCount; i++) {
        char* extName = instanceExtensionNames[i];

        // Search through the list of instance extensions for this extension
        if (!searchArrayForString(instanceExtensionNames, extName)) {
            // Report any not found extensions
            printf("Unable to find support for the following instance extension : %s\n", extName);
            if (!strcmp(extName, "VK_KHR_surface")) {
                "Could not find support for the surface extension, meaning this demo won't work here\n";
                exit(-1);
            }
        } else {
            // Extension has been found so save it
            validatedInstanceExtensions[validatedInstanceExtensionCount] = malloc(strlen(extName) + 1);
            memcpy(validatedInstanceExtensions[validatedInstanceExtensionCount], extName,
                   strlen(extName) + 1);
            validatedInstanceExtensionCount++;
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
    instanceinfo.enabledExtensionCount = validatedInstanceExtensionCount;
    instanceinfo.ppEnabledExtensionNames = validatedInstanceExtensions;

    if (vkCreateInstance(&instanceinfo, NULL, &instance) != VK_SUCCESS) {
        printf("Could not create Vulkan instance, exiting\n");
        exit(-1);
    } else {
        printf("Created Vulkan Instance\n");
    }
}
