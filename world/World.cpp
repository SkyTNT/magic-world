#include "World.h"
#include "../client/GameClient.h"
#include "../entity/player/Player.h"
#include "../utils/Utils.h"
#include "chunk/Chunk.h"
#include "generation/WorldGenerator.h"
#include "../block/BlockIdAndData.h"
#include "../thread/ThreadPool.h"
#include "chunk/ChunkManager.h"

#include <math.h>

World::World(GameClient* _client)
{
    client=_client;
    worldgenerator=NULL;
    worldThreadPool=new ThreadPool(2);
    chunkmanager=new ChunkManager(this);
}

World::~World()
{
    if(worldgenerator!=NULL)
        delete worldgenerator;
    delete worldThreadPool;
    delete chunkmanager;
}

void World::init(int _seed)
{
    worldgenerator=new WorldGenerator(_seed,this);
    worldThreadPool->init();
}

void World::tick(float dtime)
{
    glm::vec3 playerpos=mainPlayer->getPos();
    glm::ivec2 mainKey=glm::ivec2(playerpos.x/CHUNK_SIZE,playerpos.z/CHUNK_SIZE);
    for(int i=0; i<MAX_CHUNK-5; i++)
        for(int j=0; j<MAX_CHUNK-5; j++)
        {
            chunkmanager->loadChunk(mainKey+glm::ivec2(j-(MAX_CHUNK-5)/2,i-(MAX_CHUNK-5)/2));
        }

    {
        std::lock_guard<std::mutex> lock(chunkmanager->mMutex);
        for(auto it=chunkmanager->mChunks.begin(); it!=chunkmanager->mChunks.end();)
        {
            Chunk* mchunk=it->second;
            glm::ivec2 key=it->first;
            if(abs(key.x-mainKey.x)>MAX_CHUNK/2||abs(key.y-mainKey.y)>MAX_CHUNK/2)
            {
                it=chunkmanager->mChunks.erase(it);
                delete mchunk;
            }
            else
            {
                it++;
            }
        }
    }
    worldThreadPool->commit([this,mainKey]
    {
        chunkmanager->updateAll();
    });
}

Chunk* World::getChunk(glm::vec3 pos)
{
    return chunkmanager->getChunk(pos);
}

Chunk* World::getChunk(glm::ivec3 pos)
{
    return chunkmanager->getChunk(pos);
}

BlockIdAndData World::getBlock(glm::ivec3 pos)
{
    Chunk*mchunk=getChunk(pos);

    if(mchunk==NULL)
        return {0,0};
    return mchunk->getBlock(pos);
}

void World::setBlock(glm::ivec3 pos,BlockIdAndData idanddata)
{
    Chunk*mchunk=getChunk(pos);
    if(mchunk!=NULL)
        mchunk->setBlock(pos,idanddata.id,idanddata.data);
}
