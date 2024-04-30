#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>

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
	void initWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		mWindow = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	}

	void initVulkan()
	{
		createInstance();
	}

	void mainLoop()
	{
		while (!glfwWindowShouldClose(mWindow))
		{
			glfwPollEvents();
		}
	}

	void cleanup()
	{
		vkDestroyInstance(mInstance, nullptr);

		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

private:
	std::vector<VkExtensionProperties> getAvaliableExtensions()
	{
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> avaliableExtensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, avaliableExtensions.data());

		return avaliableExtensions;
	}

	std::vector<const char*> getRequiredExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		std::vector<const char*> requiredExtensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		return requiredExtensions;
	}

	bool checkExtensionSupport(const std::vector<VkExtensionProperties>& avaliableExtensions, const std::vector<const char*>& requiredExtensions)
	{
		std::set<std::string> requiredExtensionsSet(requiredExtensions.begin(), requiredExtensions.end());
		for (const auto& extension : avaliableExtensions)
		{
			requiredExtensionsSet.erase(extension.extensionName);
		}

		return requiredExtensionsSet.empty();
	}

	void createInstance()
	{
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine"; 
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		std::vector<VkExtensionProperties> avaliableExtensions = getAvaliableExtensions();
		std::vector<const char*> requiredExtensions = getRequiredExtensions();
		if (!checkExtensionSupport(avaliableExtensions, requiredExtensions))
		{
			throw std::runtime_error("Extensions requested, but are not supported!");
		}
		uint32_t requiredExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
		const char** requiredExtensionNames = requiredExtensions.data();

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = requiredExtensionCount;
		createInfo.ppEnabledExtensionNames = requiredExtensionNames;
		createInfo.enabledLayerCount = 0;

		if (vkCreateInstance(&createInfo, nullptr, &mInstance) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create instance!");
		}
	}

private:
	GLFWwindow* mWindow;
	VkInstance mInstance;
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