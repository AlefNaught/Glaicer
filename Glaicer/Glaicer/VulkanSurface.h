#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <vulkan/vulkan.h>

class VulkanSurface {
public:
	static int create(VkInstance instance, SDL_Window *window, VkSurfaceKHR *surface);
};