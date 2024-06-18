#include "ChunkHandler.h"

ChunkHandler::ChunkHandler(unsigned int x, unsigned int y, unsigned int density, glm::vec2 startPosition)
{
    for (unsigned int i = 0; i < x; i++)
    {
        for (unsigned int j = 0; j < y; j++)
        {
            chunks.push_back(Chunk(density, glm::vec2((float)i * CHUNK_SIZE, (float)j * CHUNK_SIZE) + startPosition));
        }
    }
    ChunkHandler::x = x;
    ChunkHandler::y = y;
    ChunkHandler::startPosition = startPosition;
}

void ChunkHandler::BindCamera(Camera* camera)
{
	position = &camera->Position;
}

void ChunkHandler::Render(Shader& shader, Camera& camera, GLTFModel* LOD1, GLTFModel* LOD2)
{
    int m = (int)floor((position->x - startPosition.x) / CHUNK_SIZE);
    int n = (int)floor((position->z - startPosition.y) / CHUNK_SIZE);

    int _m;
    int _n;
    int _index;

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
                        if (glm::distance(position->xz(), chunks[_index].GetCenter()) < LOD_DISTANCE)
                        {
                            chunks[_index].Render(shader, camera, LOD1);
                        }
                        else
                        {
                            chunks[_index].Render(shader, camera, LOD2);
                        }
                    }
                }
            }
        }
    }
}