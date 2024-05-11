#pragma warning( push )
#pragma warning( disable : 4996 )
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#pragma warning( push )
#pragma once
#ifdef VULKAN_SERVER
#define VULKAN_SERVER
class VulkanServer
{
private:
	void initVulkan();
	void createInstance();
};
public:
	VkInstance instance;

#endif