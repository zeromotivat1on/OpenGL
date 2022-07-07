#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "tests/TestMenu.h"
#include "tests/TestClearColor.h" 
#include "tests/TestTexture2D.h" 

int main(void)
{
    const char* glslVersion = "#version 130";

    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cout << "Glfw Initialization Error" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // if we use core profile, then we should mannualy create vertex array
    // compatibility profile has its own default vertex array
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);*/
    const float windowWidth = 1080;
    const float windowHeight = 720;

    window = glfwCreateWindow(windowWidth, windowHeight, "Procedural Generation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); // enable v-sync

    if (glewInit() != GLEW_OK) 
    {
        std::cout << "Glew Initialization Error" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VENDOR) << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;

    // creating a scope, so while we close the app window, it will force to stop the whole program
    {
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Renderer renderer;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glslVersion);

        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");

        while (!glfwWindowShouldClose(window))
        {
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("Go back"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }

                currentTest->OnImGuiRender();
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        delete currentTest;
        if (currentTest != testMenu)
        {
            delete testMenu;
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}