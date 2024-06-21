#include"ChunkHandler.h"
#include"Ground.h"
#include"Skybox.h"
#include"Atmosphere.h"
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

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Meadow", NULL, NULL);
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
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



    // Generates Shader objects
    Shader defaultShader("default.vert", "default.frag", "default.geom");
    Shader grassShader("grass.vert", "grass.frag", "grass.geom");
    Shader groundShader("ground.vert", "ground.frag");
    Shader skyboxShader("skybox.vert", "skybox.frag");

    // Take care of all the light related things
    Atmosphere atmosphere;
    atmosphere.bindShader(&defaultShader);
    atmosphere.bindShader(&grassShader);
    atmosphere.bindShader(&groundShader);

    atmosphere.set(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.8f, 0.9f, 1.0f, 1.0f));
    

    unsigned int density = 50;

    grassShader.Activate();
    glUniform1f(glGetUniformLocation(grassShader.ID, "instanceDistance"), (1.0f / density));
    glUniform1i(glGetUniformLocation(grassShader.ID, "chunkSize"), (unsigned int)(density * CHUNK_SIZE));


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
    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, glm::vec3(0.0f, 0.2f, 0.0f));



    std::string parentDir = (fs::current_path().fs::path::parent_path()).string();

    // For some weird reason it is extremely important that the skybox is created before any other texture is loaded, because otherwise the right side of it will be turned upside down
    // Create skybox
    Skybox skybox((parentDir + "/Resources/skybox").c_str());

    // Load in models
    GLTFModel model((parentDir + "/Resources/models/grassblade/scene.gltf").c_str());
    GLTFModel lowDetailModel((parentDir + "/Resources/models/grassblade_low_detail/scene.gltf").c_str());

    ChunkHandler grass((parentDir + "/Resources/ground").c_str(), 1000, 1000, density);



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
        }

        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Handles camera inputs
        camera.Inputs(window);
        // Updates and exports the camera matrix to the Vertex Shader
        camera.updateMatrix(VIEW_ANGLE, MIN_VIEW_DISTANCE, MAX_VIEW_DISTANCE);


        // Draw the normal model
        grass.Render(grassShader, groundShader, &camera, &model, &lowDetailModel);
        
        skybox.Draw(skyboxShader, camera);



        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }



    // Delete all the objects we've created
    defaultShader.Delete();
    grassShader.Delete();
    groundShader.Delete();
    skyboxShader.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}