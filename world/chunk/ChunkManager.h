#pragma once

#include <mutex>
#include <map>
#include "../../utils/VecUtils.h"

#define MAX_CHUNK 16

class Chunk;
class World;
class WorldGenerator;

class ChunkManager
{
public:
    std::map<glm::ivec2,Chunk*,ivec2cmp> mChunks;
    std::mutex mMutex;

    ChunkManager(World *_mWorld);
    ~ChunkManager();

    void loadChunk(glm::ivec2 key);
    void loadChunk(glm::ivec3 bpos);
    void loadChunk(glm::vec3 pos);

    void deleteChunk(glm::ivec2 key);
    void deleteChunk(glm::ivec3 bpos);
    void deleteChunk(glm::vec3 pos);

    void updateChunk(glm::ivec2 key);
    void updateChunk(glm::ivec3 bpos);
    void updateChunk(glm::vec3 pos);
    void updateAll();

    Chunk* getChunk(glm::ivec2 key);
    Chunk* getChunk(glm::ivec3 bpos);
    Chunk* getChunk(glm::vec3 pos);

    glm::ivec2 pos2key(glm::ivec3 bpos);
    glm::ivec2 pos2key(glm::vec3 pos);
private:
    World *mWorld;

};
