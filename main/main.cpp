#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Mordred Engine/Servers/VulkanServer.h>
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#pragma warning( push )
#pragma warning( disable : 4996 )
#include <vulkan/vulkan.hpp>
#pragma warning( push )
#include <iostream>
class Mordred
{
private:
    GLFWwindow* window;
    
    void initVulkan()
    {
        createInstance();

    }
    void createInstance() {
        
    }
    void initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        window = glfwCreateWindow(800, 600, "Mordred Engine", nullptr, nullptr);
    }
    void update()
    {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }
    void clean()
    {
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);

        glfwTerminate();
    }
public:
    void run() 
    {
        //init vulkan for now but add openGL support later
        initVulkan();
        initWindow();
        update();
        clean();

    }
};

int main() 
{
    Mordred mordred;
    char String[] = "Hello World \0";
    std::printf(String);
   try {
        mordred.run();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
  }

    return EXIT_SUCCESS;
}
