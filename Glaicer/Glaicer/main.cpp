/*
 * Vulkan Windowed Program
 *
 * Copyright (C) 2016 Valve Corporation
 * Copyright (C) 2016 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
Vulkan Windowed Project Template
Create and destroy a Vulkan surface on an SDL window.
*/

// Enable the WSI extensions
#if defined(__ANDROID__)
#define VK_USE_PLATFORM_ANDROID_KHR
#elif defined(__linux__)
#define VK_USE_PLATFORM_XLIB_KHR
#elif defined(_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#endif

// Tell SDL not to mess with main()
#define SDL_MAIN_HANDLED

#include "VulkanSurface.h"

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <vulkan/vulkan.h>
#include "logger.h"

#include <iostream>
#include <vector>

std::vector<const char*> getAvailableWSIExtensions();


using namespace std;
int main()
{
	Logger log;
	FILE *logfile = fopen("log.txt", "a+");
	log.addFileStream(stdout);
	log.addFileStream(logfile);

	VkResult result;

    // Use validation layers if this is a debug build, and use WSI extensions regardless
    std::vector<const char*> extensions = getAvailableWSIExtensions();
    std::vector<const char*> layers;
#if defined(_DEBUG)
    layers.push_back("VK_LAYER_LUNARG_standard_validation");
#endif
	
    // VkApplicationInfo allows the programmer to specifiy some basic information about the
    // program, which can be useful for layers and tools to provide more debug information.
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = NULL;
    appInfo.pApplicationName = "Vulkan Program Template";
    appInfo.applicationVersion = 1;
    appInfo.pEngineName = "LunarG SDK";
    appInfo.engineVersion = 1;
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // VkInstanceCreateInfo is where the programmer specifies the layers and/or extensions that
    // are needed.
    VkInstanceCreateInfo instInfo = {};
    instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instInfo.pNext = NULL;
    instInfo.flags = 0;
    instInfo.pApplicationInfo = &appInfo;
    instInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    instInfo.ppEnabledExtensionNames = extensions.data();
    instInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
    instInfo.ppEnabledLayerNames = layers.data();

    // Create the Vulkan instance.
    VkInstance instance;
    result = vkCreateInstance(&instInfo, NULL, &instance);
    if(result == VK_ERROR_INCOMPATIBLE_DRIVER) {
        log.fatal("Unable to find a compatible Vulkan Driver.");
        return 1;
    } else if(result) {
		log.fatal("Could not create a Vulkan instance (for unknown reasons).");
        return 1;
    }

    // Create an SDL window that supports Vulkan and OpenGL rendering.
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		log.fatal("Could not initialize SDL.");
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Vulkan Window", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    if(window == NULL) {
		log.fatal("Could not create SDL window.");
        return 1;
    }

    // Create a Vulkan surface for rendering
    VkSurfaceKHR surface;
    //createVulkanSurface(instance, window, &surface);
	VulkanSurface::create(instance, window, &surface, log);

    // This is where most initializtion for a program should be performed

	uint32_t deviceCount = 0;
	result = vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);
	if (result != VK_SUCCESS) {
		log.fatalf("Failed to enumerate physical devices present: %d", result);
		abort();
	}

	if (deviceCount == 0) {
		log.fatalf("Couldn't detect any devices present with Vulkan support: %d", result);
		abort();
	}

	vector<VkPhysicalDevice> physicalDevices(deviceCount);
	result = vkEnumeratePhysicalDevices(instance, &deviceCount, &physicalDevices[0]);
	if (result != VK_SUCCESS) {
		log.fatalf("Failed to enumerate physical devices present: %d", result);
		abort();
	}

	VkPhysicalDeviceProperties deviceProperties;
	for (uint32_t i = 0; i < deviceCount; i++) {
		memset(&deviceProperties, 0, sizeof deviceProperties);
		vkGetPhysicalDeviceProperties(physicalDevices[i], &deviceProperties);
		log.infof("Driver Version: %d\n", deviceProperties.driverVersion);
		log.infof("Device Name: %s\n", deviceProperties.deviceName);
		log.infof("Device Type: %d\n", deviceProperties.deviceType);
		log.infof("API Version: %d.%d.%d\n",(deviceProperties.apiVersion>>22)&0xFF, (deviceProperties.apiVersion>>12)&0x3FF, (deviceProperties.apiVersion&0x3FF));

		
		/*
		The Vulkan API encodes its versions as a 32 bit int, with major and minor versions being 31-22, and 21-12.  10 bits each.
		The final 12 bits are the patch version number. Implement these.

		#define VK_VER_MAJOR(X) (((X)>>22)&0x3FF)
		#define VK_VER_MINOR(X) (((X)>>12)&0x3FF)
		#define VK_VER_PATCH(X) ((X) & 0x3FF)
		*/

	}



    // Poll for user input.
    bool stillRunning = true;
    while(stillRunning) {

        SDL_Event event;
        while(SDL_PollEvent(&event)) {

            switch(event.type) {

            case SDL_QUIT:
                stillRunning = false;
                break;

            default:
                // Do nothing.
                break;
            }
        }

        SDL_Delay(10);
    }


    // Clean up.
    vkDestroySurfaceKHR(instance, surface, NULL);
    SDL_DestroyWindow(window);
    SDL_Quit();
    vkDestroyInstance(instance, NULL);

	fclose(logfile);
    return 0;
}

std::vector<const char*> getAvailableWSIExtensions()
{
    std::vector<const char*> extensions;
    extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    extensions.push_back(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_MIR_KHR)
    extensions.push_back(VK_KHR_MIR_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
    extensions.push_back(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_WIN32_KHR)
    extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_XLIB_KHR)
    extensions.push_back(VK_KHR_XLIB_SURFACE_EXTENSION_NAME);
#endif

    return extensions;
}
