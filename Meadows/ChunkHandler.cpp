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
    int m = (int)floor((position->x - startPosition.x) / (20.0f * CHUNK_SIZE));
    int n = (int)floor((position->z - startPosition.y) / (20.0f * CHUNK_SIZE)) % y;

    int _m;
    int _n;
    int _index;

    std::cout << "x: " << m << " y: " << n << " id: " << m * y + n << "\n";
    if ((m < x + RENDER_DISTANCE) && (n < y + RENDER_DISTANCE))
    {
        for (int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++)
        {
            for (int j = -RENDER_DISTANCE; j <= RENDER_DISTANCE; j++)
            {
                _m = m + i;
                _n = n + j;
                if ((_m >= 0) && (_n >= 0) && (_m < x) && (n < y))
                {
                    _index = _m * y + _n;
                    if (glm::distance((position->xz() / 20.0f), chunks[_index].GetCenter()) < LOD_DISTANCE)
                    {
                        //chunks[_index].Render(shader, camera, LOD1);
                    }
                    else
                    {
                        chunks[_index].Render(shader, camera, LOD2);
                    }
                }
            }
        }
    }
    
    /*
    for (Chunk chunk : chunks)
    {
        if (glm::distance((position->xz() / 20.0f), chunk.GetCenter()) < LOD_DISTANCE)
        {
            //chunk.Render(shader, camera, LOD1);
        }
        else
        {
            chunk.Render(shader, camera, LOD2);
        }
    }
    */
}