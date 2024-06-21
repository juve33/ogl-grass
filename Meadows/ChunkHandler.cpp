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
}

void ChunkHandler::Render(Shader& shader, Shader& groundShader, Camera* camera, GLTFModel* LOD1, GLTFModel* LOD2)
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