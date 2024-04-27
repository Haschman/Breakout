#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Game.h"
#include "ResourceManager.h"
#include "ErrorManager.h"

#include <iostream>
#include <thread>


const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            Breakout.m_keys[key] = true;
        else if (action == GLFW_RELEASE)
            Breakout.m_keys[key] = false;
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


int main(int argc, char* argv[]) {

    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "Breakout",
        nullptr,
        nullptr
    );
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glfwSwapInterval(1);

    std::cout << glGetString(GL_VERSION) << std::endl << std::endl;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    {
        GLCall(glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Breakout.Init();

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            static float red = 0.0f;
            static float green = 0.0f;
            static float blue = 0.0f;

            {
                ImGui::Begin("ImGUI window");
            
                ImGui::SliderFloat("red", &red, 0.0f, 1.0f);
                ImGui::SliderFloat("green", &green, 0.0f, 1.0f);
                ImGui::SliderFloat("blue", &blue, 0.0f, 1.0f);
            
            
                ImGui::Text(
                    "Application average %.3f ms/frame (%.1f FPS)",
                    1000.0f / io.Framerate,
                    io.Framerate
                );
                ImGui::End();
            }

            GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            float currentFrame = (float)glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            Breakout.ProcessInput(currentFrame);

            Breakout.Update(deltaTime);

            ImGui::Render();
            Breakout.Render(glm::vec3(red, green, blue));

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
        }

        ResourceManager::Clear();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
