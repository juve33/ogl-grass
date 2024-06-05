#include"Skybox.h"

Skybox::Skybox(std::string texturesDirectory)
{
    std::vector<glm::vec3> skyboxVertices =
    {
        //   Coordinates
        glm::vec3(-1.0f, -1.0f,  1.0f),//        7--------6
        glm::vec3( 1.0f, -1.0f,  1.0f),//       /|       /|
        glm::vec3( 1.0f, -1.0f, -1.0f),//      4--------5 |
        glm::vec3(-1.0f, -1.0f, -1.0f),//      | |      | |
        glm::vec3(-1.0f,  1.0f,  1.0f),//      | 3------|-2
        glm::vec3( 1.0f,  1.0f,  1.0f),//      |/       |/
        glm::vec3( 1.0f,  1.0f, -1.0f),//      0--------1
        glm::vec3(-1.0f,  1.0f, -1.0f)
    };

    std::vector<unsigned int> skyboxIndices =
    {
        // Right
        1, 2, 6,
        6, 5, 1,
        // Left
        0, 4, 7,
        7, 3, 0,
        // Top
        4, 5, 6,
        6, 7, 4,
        // Bottom
        0, 3, 2,
        2, 1, 0,
        // Back
        0, 1, 5,
        5, 4, 0,
        // Front
        3, 7, 6,
        6, 2, 3
    };



    VAO.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    Buffer<glm::vec3> VBO(GL_ARRAY_BUFFER, skyboxVertices);
    // Generates Element Buffer Object and links it to indices
    Buffer<unsigned int> EBO(GL_ELEMENT_ARRAY_BUFFER, skyboxIndices);
    // Links VBO attributes such as coordinates and colors to VAO
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();


    // All the faces of the cubemap (make sure they are in this exact order)
    std::string facesCubemap[6] =
    {
        texturesDirectory + "/right.jpg",
        texturesDirectory + "/left.jpg",
        texturesDirectory + "/top.jpg",
        texturesDirectory + "/bottom.jpg",
        texturesDirectory + "/front.jpg",
        texturesDirectory + "/back.jpg"
    };

    // Creates the cubemap texture object
    glGenTextures(1, &cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // These are very important to prevent seams
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // This might help with seams on some systems
    //glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    // Cycles through all the textures and attaches them to the cubemap object
    for (unsigned int i = 0; i < 6; i++)
    {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D
            (
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                width,
                height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
            stbi_image_free(data);
        }
    }
}

void Skybox::Draw(Shader& shader, Camera& camera, int width, int height)
{
    // Since the cubemap will always have a depth of 1.0, we need that equal sign so it doesn't get discarded
    glDepthFunc(GL_LEQUAL);

    shader.Activate();
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    // We make the mat4 into a mat3 and then a mat4 again in order to get rid of the last row and column
    // The last row and column affect the translation of the skybox (which we don't want to affect)
    view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
    projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    VAO.Bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    VAO.Unbind();

    // Switch back to the normal depth function
    glDepthFunc(GL_LESS);
}