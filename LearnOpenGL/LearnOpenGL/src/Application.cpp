#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream> // stands for file stream
#include <string>
#include <sstream>
#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"




int main(void)
{
    GLFWwindow* window;

    /* Initialize GLFW */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // what does this do ?? makes it smoother?? how?

    /* Initialize GLEW */
    /* MUST be defined after valid context... */
    if (glewInit() != GLEW_OK)
        cout << "Error!" << endl;

    /* Printing current version */
    cout << glGetString(GL_VERSION) << endl;

    /* Defining vertices as arrays */
    /* basic Triangle in this case... */
    {
        float positions[] = {
            -0.5f, -0.5f, // 0
             0.5f, -0.5f, // 1
             0.5f,  0.5f, // 2
            -0.5f,  0.5f, // 3
        };

        // an index buffer (very useful, saves you from duplicating vertices)
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };




        /* Declaring buffers */
        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float)); // bounded automatically.. see class definition
        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);


        IndexBuffer ib(indices, 6);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        // unbounding everything... what does that mean??

        va.Unbind();
        vb.UnBind();
        ib.UnBind();
        shader.UnBind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            /* Draw the triangle... */
            // glDrawArrays(GL_TRIANGLES, 0, 6); 

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            renderer.Draw(va, ib, shader); // draw call abstracted "renderer" object

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}