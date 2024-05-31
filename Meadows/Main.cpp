// do NOT include anything above Model.h bc it'll cause a linking error (if it uses any buffer objects)
#include"Model.h"
#include<filesystem>
namespace fs = std::filesystem;


const unsigned int width = 800;
const unsigned int height = 800;


int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Meadow", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    //Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    glViewport(0, 0, width, height);



    // Generates Shader objects
    Shader shaderProgram("default.vert", "default.frag", "default.geom");
    Shader skyboxShader("skybox.vert", "skybox.frag", "default.geom");

    // Take care of all the light related things
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightDir"), glm::normalize(lightPos).x, glm::normalize(lightPos).y, glm::normalize(lightPos).z);



    // Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);
    // Enables Cull Facing
    glEnable(GL_CULL_FACE);
    // Keeps front faces
    glCullFace(GL_FRONT);
    // Uses counter clock-wise standard
    glFrontFace(GL_CCW);



    // Creates camera object
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));



    std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
    std::string modelPath = "/Resources/models/statue/scene.gltf";

    // Load in models
    Model model((parentDir + modelPath).c_str());


    std::string skyboxPath = "/Resources/models/skybox/scene.gltf";

    // Load in models
    Model skybox((parentDir + skyboxPath).c_str());



    // Variables to create periodic event for FPS displaying
    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff;
    // Keeps track of the amount of frames in timeDiff
    unsigned int counter = 0;

    // Use this to disable VSync (not advised)
    //glfwSwapInterval(0);



    // Main while loop
    while ((!glfwWindowShouldClose(window)) && (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS))
    {
        // Updates counter and times
        crntTime = glfwGetTime();
        timeDiff = crntTime - prevTime;
        counter++;

        if (timeDiff >= 1.0 / 30.0)
        {
            // Creates new title
            std::string FPS = std::to_string((1.0 / timeDiff) * counter);
            std::string ms = std::to_string((timeDiff / counter) * 1000);
            std::string newTitle = "Meadow - " + FPS + "FPS / " + ms + "ms";
            glfwSetWindowTitle(window, newTitle.c_str());

            // Resets times and counter
            prevTime = crntTime;
            counter = 0;

            // Use this if you have disabled VSync
            //camera.Inputs(window);
        }

        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Handles camera inputs (delete this if you have disabled VSync)
        camera.Inputs(window);
        // Updates and exports the camera matrix to the Vertex Shader
        camera.updateMatrix(45.0f, 0.1f, 100.0f);


        // Draw the normal model
        model.Draw(shaderProgram, camera);
        // Draw the skybox model
        skybox.Draw(skyboxShader, camera);

        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }



    // Delete all the objects we've created
    shaderProgram.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}