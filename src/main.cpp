#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

// GLOBALS
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication
{
public:
	void run()
	{
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

private:
	// Initialization, mainloop, and cleanup:
	
	void initWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	}

	void initVulkan()
	{
		createInstance();
	}

	void mainLoop()
	{
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}
	}

	void cleanup()
	{
		vkDestroyInstance(instance, nullptr);

		glfwDestroyWindow(window);
		glfwTerminate();
	}

private:
	void createInstance()
	{
		/*
			The Vulkan instance is the entrypoint for interacting with the graphics and compute system. Creating the instance initializes the Vulkan
			API and allows for the querying of physical devices such as GPUs. It also enables the application to configure global settings and parameters
			such as validation layers and extensions that affect the way Vulkan behaves at runtime. 

			struct VkApplicationInfo
			{
				VkStructureType    sType;
				const void*        pNext;
				const char*        pApplicationName;
				uint32_t           applicationVersion;
				const char*        pEngineName;
				uint32_t           engineVersion;
				uint32_t           apiVersion;
			};

			The Vulkan struct VkApplicationInfo specifies information about the application to the Vulkan implementation. This contains information such as
			the application's name, version, and engine. This is neccassary to help Vulkan understand how the application needs to behave.
		*/

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine"; 
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		/*
			struct VkInstanceCreateInfo 
			{
				VkStructureType             sType;
				const void*                 pNext;
				VkInstanceCreateFlags       flags;
				const VkApplicationInfo*    pApplicationInfo;
				uint32_t                    enabledLayerCount;
				const char* const*          ppEnabledLayerNames;
				uint32_t                    enabledExtensionCount;
				const char* const*          ppEnabledExtensionNames;
			};

			The Vulkan struct VkInstanceCreateInfo specifies the create information for the instnace. It tells the Vulkan driver which global extensions
			and validation layers we want to use. Global here means that they apply to the entire program and not a specific device. 
		*/

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;

		/*
			VKAPI_ATTR VkResult VKAPI_CALL vkCreateInstance
			(
				const VkInstanceCreateInfo*                 pCreateInfo,
				const VkAllocationCallbacks*                pAllocator,
				VkInstance*                                 pInstance
			);

			The Vulkan function vkCreateInstance takes in a reference to the instance's create info, optional allocator, and a reference to the instance
			handle.	If the function is successful, it returns VK_SUCCESS of type VkResult and a handle to the instance. 
		*/

		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create instance!");
		}
	}

private:	
	// GLFW and Vulkan handle objects:
	GLFWwindow* window;
	VkInstance instance;
};

int main()
{
	HelloTriangleApplication app;

	try
	{
		app.run();
	}
	
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}