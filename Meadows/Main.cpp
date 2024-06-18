#include"ChunkHandler.h"
#include"Skybox.h"
#include<filesystem>
namespace fs = std::filesystem;

const unsigned int width = 800;
const unsigned int height = 800;
// Fullscreen
//const unsigned int width = 1920;
//const unsigned int height = 1017;



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
    Shader shaderProgram("grass.vert", "grass.frag", "grass.geom");
    Shader skyboxShader("skybox.vert", "skybox.frag");

    // Take care of all the light related things
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec4 fogColor = glm::vec4(0.8f, 0.9f, 1.0f, 1.0f);

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "fogColor"), fogColor.x, fogColor.y, fogColor.z, fogColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightDir"), glm::normalize(lightPos).x, glm::normalize(lightPos).y, glm::normalize(lightPos).z);


    unsigned int density = 50;

    glUniform1f(glGetUniformLocation(shaderProgram.ID, "instanceDistance"), (1.0f / density));
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "chunkSize"), (unsigned int)(density * CHUNK_SIZE));

    skyboxShader.Activate();
    glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);



    // Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);
    // Enables Cull Facing
    //glEnable(GL_CULL_FACE);
    // Keeps front faces
    //glCullFace(GL_FRONT);
    // Uses counter clock-wise standard
    glFrontFace(GL_CCW);



    // Creates camera object
    Camera camera(width, height, glm::vec3(0.0f, 0.2f, 0.0f));



    std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
    std::string modelPath = "/Resources/models/grassblade/scene.gltf";

    // Load in models
    GLTFModel model((parentDir + modelPath).c_str());

    std::string lowDetailModelPath = "/Resources/models/grassblade_low_detail/scene.gltf";

    // Load in models
    GLTFModel lowDetailModel((parentDir + lowDetailModelPath).c_str());

    ChunkHandler grass(1000, 1000, density);
    grass.BindCamera(&camera);

    std::string skyboxPath = "/Resources/skybox";

    // Create skybox
    Skybox skybox((parentDir + skyboxPath).c_str());



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
        /*
        if (std::trunc(prevTime) != std::trunc(crntTime))
        {
            std::cout << (camera.Position.x / 20.0f) << " " << (camera.Position.z / 20.0f) << "\n";
        }*/

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
        camera.updateMatrix(45.0f, 0.1f, 4.75f);


        // Draw the normal model
        grass.Render(shaderProgram, camera, &model, &lowDetailModel);
        
        skybox.Draw(skyboxShader, camera, width, height);



        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }



    // Delete all the objects we've created
    shaderProgram.Delete();
    skyboxShader.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}