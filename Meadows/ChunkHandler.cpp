#include "ChunkHandler.h"

ChunkHandler::ChunkHandler(std::string groundTexDir, unsigned int x, unsigned int y, unsigned int density, glm::vec2 startPosition)
{
    ground = Ground(groundTexDir);
    for (unsigned int i = 0; i < x; i++)
    {
        for (unsigned int j = 0; j < y; j++)
        {
            chunks.push_back(Chunk(density, &ground, glm::vec2((float)i * CHUNK_SIZE, (float)j * CHUNK_SIZE) + startPosition));
        }
    }
    ChunkHandler::x = x;
    ChunkHandler::y = y;
    ChunkHandler::startPosition = startPosition;



    // Set seed
    std::srand(std::time(nullptr));

    std::vector<glm::vec2> grassDisplacement;
    std::vector<glm::vec2> grassRotation;
    std::vector<float> grassCurveValue;
    std::vector<float> grassHeight;
    float rotation;

    for (int i = 0; i < (int)(density * density * CHUNK_SIZE * CHUNK_SIZE); i++)
    {
        grassDisplacement.push_back(glm::vec2((float)(std::rand() % 50) / 50.0f, (float)(std::rand() % 50) / 50.0f));
        rotation = (float)(std::rand() % 360) * 3.14159f / 180.0f;
        grassRotation.push_back(glm::vec2(sin(rotation), cos(rotation)));
        grassCurveValue.push_back((float)(std::rand() % 100) / 150.0f);
        grassHeight.push_back((float)(std::rand() % 50) / 100.0f + 0.75f);
    }

    Buffer<glm::vec2> SSBO_displacement(GL_SHADER_STORAGE_BUFFER, grassDisplacement);
    Buffer<glm::vec2> SSBO_rotation(GL_SHADER_STORAGE_BUFFER, grassRotation);
    Buffer<float> SSBO_curve(GL_SHADER_STORAGE_BUFFER, grassCurveValue);
    Buffer<float> SSBO_height(GL_SHADER_STORAGE_BUFFER, grassHeight);

    SSBO_displacement.SetBinding(0);
    SSBO_rotation.SetBinding(1);
    SSBO_curve.SetBinding(2);
    SSBO_height.SetBinding(3);

    SSBO_displacement.Unbind();
    SSBO_rotation.Unbind();
    SSBO_curve.Unbind();
    SSBO_height.Unbind();
}

void ChunkHandler::Render(Shader& shader, Shader& groundShader, Camera* camera, AbstractModel* LOD1, AbstractModel* LOD2)
{
    int m = (int)floor((camera->Position.x - startPosition.x) / CHUNK_SIZE);
    int n = (int)floor((camera->Position.z - startPosition.y) / CHUNK_SIZE);

    int _m, _n, _index;
    float _distance;

    if ((m < x + RENDER_DISTANCE) && (n < y + RENDER_DISTANCE) && (m >= -RENDER_DISTANCE) && (n >= -RENDER_DISTANCE))
    {
        for (int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++)
        {
            _m = m + i;
            if ((_m >= 0) && (_m < x))
            {
                for (int j = -RENDER_DISTANCE; j <= RENDER_DISTANCE; j++)
                {
                    _n = n + j;
                    if ((_n >= 0) && (_n < y))
                    {
                        _index = _m * y + _n;
                        _distance = glm::distance(camera->Position.xz(), chunks[_index].GetCenter());

                        if (_distance <= 1.5f * CHUNK_SIZE)
                        {
                            chunks[_index].ForceRender(shader, groundShader, camera, LOD1);
                        }
                        else if (_distance < LOD_DISTANCE)
                        {
                            chunks[_index].Render(shader, groundShader, camera, LOD1);
                        }
                        else
                        {
                            chunks[_index].Render(shader, groundShader, camera, LOD2);
                        }
                    }
                }
            }
        }
    }
}