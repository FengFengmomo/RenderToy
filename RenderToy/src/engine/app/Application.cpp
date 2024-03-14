#include "Application.h"

Application::Application()
{
    window = nullptr;
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
    std::cout << glGetString(GL_VERSION) << std::endl;

    width = setWidth;
    height = setHeight;

    renderer = Renderer();

    return true;
}

void Application::Run()
{
    {
        //positions of every vertex
        float cube[] = {
           -5.0f, -5.0f, -5.0f, 0.25f, 0.33f, //0
            5.0f, -5.0f, -5.0f, 0.50f, 0.33f, //1
            5.0f,  5.0f, -5.0f, 0.50f, 0.66f, //2
           -5.0f,  5.0f, -5.0f, 0.25f, 0.66f, //3 near
           -5.0f, -5.0f,  5.0f, 0.75f, 0.33f, //4
            5.0f, -5.0f,  5.0f, 1.00f, 0.33f, //5
            5.0f,  5.0f,  5.0f, 1.00f, 0.66f, //6
           -5.0f,  5.0f,  5.0f, 0.75f, 0.66f, //7 far
           -5.0f, -5.0f,  5.0f, 0.00f, 0.33f, //8
           -5.0f, -5.0f, -5.0f, 0.25f, 0.33f, //9
           -5.0f,  5.0f, -5.0f, 0.25f, 0.66f, //10
           -5.0f,  5.0f,  5.0f, 0.00f, 0.66f, //11 left
            5.0f, -5.0f, -5.0f, 0.50f, 0.33f, //12
            5.0f, -5.0f,  5.0f, 0.75f, 0.33f, //13
            5.0f,  5.0f,  5.0f, 0.75f, 0.66f, //14
            5.0f,  5.0f, -5.0f, 0.50f, 0.66f, //15 right
           -5.0f,  5.0f, -5.0f, 0.25f, 0.66f, //16
            5.0f,  5.0f, -5.0f, 0.50f, 0.66f, //17
            5.0f,  5.0f,  5.0f, 0.50f, 1.00f, //18
           -5.0f,  5.0f,  5.0f, 0.25f, 1.00f, //19 top
           -5.0f, -5.0f,  5.0f, 0.25f, 0.00f, //20
            5.0f, -5.0f,  5.0f, 0.50f, 0.00f, //21
            5.0f, -5.0f, -5.0f, 0.50f, 0.33f, //22
           -5.0f, -5.0f, -5.0f, 0.25f, 0.33f  //23 bottom
        };

        //indicate the vertex of each triangle
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,
            4, 5, 6,
            6, 7, 4,
            8, 9, 10,
            10, 11, 8,
            12, 13, 14,
            14, 15, 12,
            16, 17, 18,
            18, 19, 16,
            20, 21, 22,
            22, 23, 20
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDepthFunc(GL_LESS));

        VertexArray va;
        VertexBufferLayout layout;
        VertexBuffer vb(cube, sizeof(cube));
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        IndexBuffer ib(indices, (unsigned int)(sizeof(indices)/sizeof(unsigned int)));

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
        int cameraX = 0;
        int cameraY = 0;
        int cameraZ = 0;
        float cameraRotX = 0.0f;
        float cameraRotY = 0.0f;
        float cameraRotZ = 0.0f;
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
        //Math

        //Loop until the user closes the window
        while (!glfwWindowShouldClose(window))
        {
            //Render here
            renderer.Clear();
            
            //Camera
            renderer.camera.SetPers(fov, width, height, near, far);
            renderer.camera.SetPos(cameraX, cameraY, cameraZ);
            renderer.camera.SetRot(cameraRotX, cameraRotY, cameraRotZ);
            //Camera

            //Math
            rot = glm::rotate(glm::mat4(1.0f), glm::radians(radians), glm::vec3(rotX, rotY, rotZ));
            model = glm::translate(glm::mat4(1.0f), glm::vec3(modelX , modelY, modelZ));
            model *= rot;
            //Math

            for (int i = 1; i <= 5; i++)
            {
                model = glm::translate(glm::mat4(1.0f), glm::vec3(0, i*10, 0)) * model;
                mvp = renderer.camera.GetCamera() * model;
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(va, ib, shader);
                model = glm::translate(glm::mat4(1.0f), glm::vec3(modelX, modelY, modelZ));
                model *= rot;
            }

            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++) 
                {
                    model = glm::translate(glm::mat4(1.0f), glm::vec3(i*10, 0, j * 10)) * model;
                    mvp = renderer.camera.GetCamera() * model;
                    shader.SetUniformMat4f("u_MVP", mvp);
                    renderer.Draw(va, ib, shader);
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
                gui::SliderInt("camera x", &cameraX, -1000, 1000);
                gui::SliderInt("camera y", &cameraY, -1000, 1000);
                gui::SliderInt("camera z", &cameraZ, -1000, 1000);
                gui::SliderFloat("camera rot x", &cameraRotX, -180.0f, 180.0f);
                gui::SliderFloat("camera rot y", &cameraRotY, -180.0f, 180.0f);
                gui::SliderFloat("camera rot z", &cameraRotZ, -180.0f, 180.0f);
                gui::SliderInt("model x", &modelX, -1000, 1000);
                gui::SliderInt("model y", &modelY, -1000, 1000);
                gui::SliderInt("model z", &modelZ, -1000, 1000);
                gui::SliderFloat("radians", &radians, -180.0f, 180.0f);
                gui::Checkbox("X", &if_rotx);
                gui::SameLine();
                gui::Checkbox("Y", &if_roty);
                gui::SameLine();
                gui::Checkbox("Z", &if_rotz);
                rotX = if_rotx ? 1.0f : 0.0f;
                rotY = if_roty ? 1.0f : 0.0f;
                rotZ = if_rotz ? 1.0f : 0.0f;
                if (gui::Button("reset"))
                {
                    fov = 80.0f;
                    near = 10.0f;
                    far = -300.0f;
                    cameraX = 0;
                    cameraY = 0;
                    cameraZ = 0;
                    cameraRotX = 0.0f;
                    cameraRotY = 0.0f;
                    cameraRotZ = 0.0f;
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
}

void Application::Update()
{

}

Application::~Application()
{
    gui::Destroy();
    glfwDestroyWindow(window);
    glfwTerminate();
}