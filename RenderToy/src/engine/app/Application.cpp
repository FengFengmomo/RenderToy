#include "Application.h"

Application::Application()
{
    width = 0;
    height = 0;
    window = nullptr;
}

Application::~Application()
{
    gui::Destroy();
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Application::Init(int setWidth, int setHeight, const char* programName)
{
    //Initialize GLFW
    if (!glfwInit())
    {
        return false;
    }
    //Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(setWidth, setHeight, programName, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return false;
    }
    //Make the window's context current
    glfwMakeContextCurrent(window);

    //Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        return false;
    }
    //Initialize Dear ImGui
    gui::Init(window, "#version 330");
    //Get current OpenGL version
    std::cout << "Checking current OpenGLVersion......" << std::endl;
    std::cout << "OpenGL Verison: " << glGetString(GL_VERSION) << std::endl;
    //Bind Callback
    //glfwSetCursorPosCallback(window, MouseMove);

    width = setWidth;
    height = setHeight;
    renderer.Init();
    return true;
}

void Application::Run()
{
    Model cube;
    cube.Init();

    //Shader
    Shader shader("res/shader/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);
    //Shader

    //Texture
    Texture texture("res/texture/grass.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);
    //Texture

    //Math
    float fov = 80.0f;
    float near = 10.0f;
    float far = -300.0f;
    int modelX = 0;
    int modelY = 0;
    int modelZ = 50;
    float radians = 0.0f;
    bool if_rotx = false;
    bool if_roty = true;
    bool if_rotz = false;
    float rotX = 0.0f;
    float rotY = 1.0f;
    float rotZ = 0.0f;
    glm::mat4 model, mvp, rot;
    int cubeWidth = 5;
    int cubeHeight = 5;
    int cubeColumn = 5;
    //Math

    //Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        //Render here
        renderer.Clear();

        //Handle Input
        KeyboardInput(window);

        //Camera
        renderer.GetCamera().SetPers(fov, width, height, near, far);
        //Camera

        //Math
        rot = glm::rotate(glm::mat4(1.0f), glm::radians(radians), glm::vec3(rotX, rotY, rotZ));
        model = glm::translate(glm::mat4(1.0f), glm::vec3(modelX, modelY, modelZ));
        model *= rot;
        //Math

        for (int i = 1; i <= cubeColumn; i++)
        {
            model = glm::translate(glm::mat4(1.0f), glm::vec3(0, i * 10, 0)) * model;
            mvp = renderer.GetCamera().GetCameraMat() * model;
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(cube, shader);
            model = glm::translate(glm::mat4(1.0f), glm::vec3(modelX, modelY, modelZ));
            model *= rot;
        }

        for (int i = 0; i < cubeHeight; i++)
        {
            for (int j = 0; j < cubeWidth; j++)
            {
                model = glm::translate(glm::mat4(1.0f), glm::vec3(i * 10, 0, j * 10)) * model;
                mvp = renderer.GetCamera().GetCameraMat() * model;
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(cube, shader);
                model = glm::translate(glm::mat4(1.0f), glm::vec3(modelX, modelY, modelZ));
                model *= rot;
            }
        }

        //imgui
        gui::NewFrame();
        {
            gui::Begin("Hello World!");
            gui::SliderFloat("fov", &fov, -150.0f, 150.0f);
            gui::SliderFloat("near", &near, -500.0f, 500.0f);
            gui::SliderFloat("far", &far, -500.0f, 500.0f);
            gui::SliderInt("model x", &modelX, -1000, 1000);
            gui::SliderInt("model y", &modelY, -1000, 1000);
            gui::SliderInt("model z", &modelZ, -1000, 1000);
            gui::SliderFloat("radians", &radians, -180.0f, 180.0f);
            gui::SliderInt("cube width", &cubeWidth, 1, 20);
            gui::SliderInt("cube height", &cubeHeight, 1, 20);
            gui::SliderInt("cube column", &cubeColumn, 1, 20);
            if (gui::Button("reset"))
            {
                fov = 80.0f;
                near = 10.0f;
                far = -300.0f;
                modelX = 0;
                modelY = 0;
                modelZ = 50;
                radians = 0.0f;
                if_rotx = false;
                if_roty = true;
                if_rotz = false;
                rotX = 0.0f;
                rotY = 1.0f;
                rotZ = 0.0f;
                cubeHeight = 5;
                cubeWidth = 5;
                cubeColumn = 5;
                renderer.GetCamera().SetPos(0.0f, 0.0f, 0.0f);
                renderer.GetCamera().SetRot(0.0f, 0.0f, 0.0f);
            }
            //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            gui::End();
        }
        gui::EndFrame();
        gui::Draw();
        //imgui

        //Swap front and back buffers
        glfwSwapBuffers(window);

        //Poll for and process events
        glfwPollEvents();
    }
}

void Application::Update()
{

}

void Application::KeyboardInput(GLFWwindow* window)
{
    float moveSpeed = 0.5f;
    float rotateSpeed = 1.0f;
    glm::vec4 move = glm::vec4(0.0f);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    //Camera Movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        move = renderer.GetCamera().GetRotMat() * glm::vec4(0.0f, 0.0f, moveSpeed, 0.0f);
        renderer.GetCamera().SetPos(renderer.GetCamera().GetPosX() - move[0], renderer.GetCamera().GetPosY(), renderer.GetCamera().GetPosZ() + move[2]);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        move = renderer.GetCamera().GetRotMat() * glm::vec4(moveSpeed, 0.0f, 0.0f, 0.0f);
        renderer.GetCamera().SetPos(renderer.GetCamera().GetPosX() + move[0], renderer.GetCamera().GetPosY(), renderer.GetCamera().GetPosZ() - move[2]);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        move = renderer.GetCamera().GetRotMat() * glm::vec4(0.0f, 0.0f, moveSpeed, 0.0f);
        renderer.GetCamera().SetPos(renderer.GetCamera().GetPosX() + move[0], renderer.GetCamera().GetPosY(), renderer.GetCamera().GetPosZ() - move[2]);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        move = renderer.GetCamera().GetRotMat() * glm::vec4(moveSpeed, 0.0f, 0.0f, 0.0f);
        renderer.GetCamera().SetPos(renderer.GetCamera().GetPosX() - move[0], renderer.GetCamera().GetPosY(), renderer.GetCamera().GetPosZ() + move[2]);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        renderer.GetCamera().SetPosY(renderer.GetCamera().GetPosY() - moveSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        renderer.GetCamera().SetPosY(renderer.GetCamera().GetPosY() + moveSpeed);
    }
    //Camera Movement

    //Camera Rotation
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if (abs(renderer.GetCamera().GetYaw()) < 360.0f)
        {
            renderer.GetCamera().SetYaw(renderer.GetCamera().GetYaw() - rotateSpeed);
        }
        else
        {
            renderer.GetCamera().SetYaw(0.0f);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if (abs(renderer.GetCamera().GetYaw()) < 360.0f)
        {
            renderer.GetCamera().SetYaw(renderer.GetCamera().GetYaw() + rotateSpeed);
        }
        else
        {
            renderer.GetCamera().SetYaw(0.0f);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if (renderer.GetCamera().GetPitch() > -90.0f)
        {
            renderer.GetCamera().SetPitch(renderer.GetCamera().GetPitch() - rotateSpeed);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (renderer.GetCamera().GetPitch() < 90.0f)
        {
            renderer.GetCamera().SetPitch(renderer.GetCamera().GetPitch() + rotateSpeed);
        }
    }
    //Camera Rotation
}