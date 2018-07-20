#include "ChunkManager.h"
#include "../generation/WorldGenerator.h"
#include "Chunk.h"
#include "../World.h"
#include "../../utils/Utils.h"
#include <math.h>

ChunkManager::ChunkManager(World *_mWorld)
{
    mWorld=_mWorld;
}

ChunkManager::~ChunkManager()
{
    for(auto it=mChunks.begin();it!=mChunks.end();it++)
    {
        Chunk*chunk=it->second;
        delete chunk;
    }
    mChunks.clear();
}

void ChunkManager::loadChunk(glm::ivec2 key)
{
    Chunk* chunk=getChunk(key);
    if(chunk!=NULL)
    {
        return;
    }

    chunk=new Chunk(mWorld);
    chunk->setPos(glm::ivec3(key.x*CHUNK_SIZE,0,key.y*CHUNK_SIZE));
    mWorld->worldgenerator->genChunk(chunk);
    mChunks[key]=chunk;
}

void ChunkManager::loadChunk(glm::ivec3 bpos)
{
    loadChunk(pos2key(bpos));
}

void ChunkManager::loadChunk(glm::vec3 pos)
{
    loadChunk(pos2key(pos));
}

void ChunkManager::deleteChunk(glm::ivec2 key)
{
    auto it=mChunks.find(key);
    if(it==mChunks.end())
        return;
    mChunks.erase(it);
    delete it->second;
}
void ChunkManager::deleteChunk(glm::ivec3 bpos)
{
    deleteChunk(pos2key(bpos));
}
void ChunkManager::deleteChunk(glm::vec3 pos)
{
    deleteChunk(pos2key(pos));
}

void ChunkManager::updateChunk(glm::ivec3 bpos)
{
    updateChunk(pos2key(bpos));
}

void ChunkManager::updateChunk(glm::vec3 pos)
{
    updateChunk(pos2key(pos));
}
void ChunkManager::updateChunk(glm::ivec2 key)
{
    Chunk* chunk=getChunk(key);
    if(chunk==NULL)
    {
        LOG_I("chunk update err: can not find the chunk to update");
        return;
    }
    chunk->updateChunk();
}

void ChunkManager::updateAll()
{
    for(auto it=mChunks.begin();it!=mChunks.end();it++)
    {
        it->second->updateChunk();
    }
}

Chunk* ChunkManager::getChunk(glm::ivec2 key)
{
    auto it=mChunks.find(key);
    if(it==mChunks.end())
    {
        return NULL;
    }
    return it->second;
}

Chunk* ChunkManager::getChunk(glm::ivec3 bpos)
{
    return getChunk(pos2key(bpos));
}

Chunk* ChunkManager::getChunk(glm::vec3 pos)
{
    return getChunk(pos2key(pos));
}

glm::ivec2 ChunkManager::pos2key(glm::ivec3 bpos)
{
    return glm::ivec2(floor((float)bpos.x/CHUNK_SIZE),floor((float)bpos.z/CHUNK_SIZE));
}

glm::ivec2 ChunkManager::pos2key(glm::vec3 pos)
{
    return glm::ivec2(floor(pos.x/CHUNK_SIZE),floor(pos.z/CHUNK_SIZE));
}

