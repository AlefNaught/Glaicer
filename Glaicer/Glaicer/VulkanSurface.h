#pragma once

// Enable the WSI extensions
#if defined(__ANDROID__)
#define VK_USE_PLATFORM_ANDROID_KHR
#elif defined(__linux__)
#define VK_USE_PLATFORM_XLIB_KHR
#elif defined(_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <vulkan/vulkan.h>

#include "logger.h"

class VulkanSurface {
public:
	static int create(VkInstance instance, SDL_Window *window, VkSurfaceKHR *surface, Logger log);
};