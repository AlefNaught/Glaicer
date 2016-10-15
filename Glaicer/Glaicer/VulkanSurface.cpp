#include "VulkanSurface.h"

#include <iostream>

int VulkanSurface::create(VkInstance instance, SDL_Window *window, VkSurfaceKHR *surface) {
	SDL_SysWMinfo windowInfo;
	SDL_VERSION(&windowInfo.version);
	if (!SDL_GetWindowWMInfo(window, &windowInfo)) {
		std::cout << "SDK window manager info is not available." << std::endl;
		return 1;
	}

	switch (windowInfo.subsystem) {

#if defined(SDL_VIDEO_DRIVER_ANDROID) && defined(VK_USE_PLATFORM_ANDROID_KHR)
	case SDL_SYSWM_ANDROID: {
		VkAndroidSurfaceCreateInfoKHR surfaceInfo = {};
		surfaceInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
		surfaceInfo.window = windowInfo.info.android.window;

		VkResult result = vkCreateAndroidSurfaceKHR(instance, &surfaceInfo, NULL, surface);
		if (result != VK_SUCCESS) {
			std::cout << "Failed to create Android surface." << std::endl;
			return 1;
		}
		break;
	}
#endif

#if defined(SDL_VIDEO_DRIVER_MIR) && defined(VK_USE_PLATFORM_MIR_KHR)
	case SDL_SYSWM_MIR: {
		VkMirSurfaceCreateInfoKHR surfaceInfo = {};
		surfaceInfo.sType = VK_STRUCTURE_TYPE_MIR_SURFACE_CREATE_INFO_KHR;
		surfaceInfo.connection = windowInfo.info.mir.connection;
		surfaceInfo.mirSurface = windowInfo.info.mir.surface;

		VkResult result = vkCreateMirSurfaceKHR(instance, &surfaceInfo, NULL, surface);
		if (result != VK_SUCCESS) {
			std::cout << "Failed to create Mir surface." << std::endl;
			return 1;
		}
		break;
	}
#endif

#if defined(SDL_VIDEO_DRIVER_WAYLAND) && defined(VK_USE_PLATFORM_WAYLAND_KHR)
	case SDL_SYSWM_WAYLAND: {
		VkWaylandSurfaceCreateInfoKHR surfaceInfo = {};
		surfaceInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
		surfaceInfo.display = windowInfo.info.wl.display;
		surfaceInfo.surface = windowInfo.info.wl.surface;

		VkResult result = vkCreateWaylandSurfaceKHR(instance, &surfaceInfo, NULL, surface);
		if (result != VK_SUCCESS) {
			std::cout << "Failed to create Wayland surface." << std::endl;
			return 1;
		}
		break;
	}
#endif

#if defined(SDL_VIDEO_DRIVER_WINDOWS) && defined(VK_USE_PLATFORM_WIN32_KHR)
	case SDL_SYSWM_WINDOWS: {
		VkWin32SurfaceCreateInfoKHR surfaceInfo = {};
		surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		surfaceInfo.hinstance = GetModuleHandle(NULL);
		surfaceInfo.hwnd = windowInfo.info.win.window;

		VkResult result = vkCreateWin32SurfaceKHR(instance, &surfaceInfo, NULL, surface);
		if (result != VK_SUCCESS) {
			std::cout << "Failed to create Win32 surface." << std::endl;
			return 1;
		}
		break;
	}
#endif

#if defined(SDL_VIDEO_DRIVER_X11) && defined(VK_USE_PLATFORM_XLIB_KHR)
	case SDL_SYSWM_X11: {
		VkXlibSurfaceCreateInfoKHR surfaceInfo = {};
		surfaceInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
		surfaceInfo.dpy = windowInfo.info.x11.display;
		surfaceInfo.window = windowInfo.info.x11.window;

		VkResult result = vkCreateXlibSurfaceKHR(instance, &surfaceInfo, NULL, surface);
		if (result != VK_SUCCESS) {
			std::cout << "Failed to create X11 surface." << std::endl;
			return 1;
		}
		break;
	}
#endif

	default:
		std::cout << "Unsupported window manager is in use." << std::endl;
		return 1;
	}

	return 0;
}