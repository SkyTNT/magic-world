#include "GameWorld.h"
#include "../client/GameClient.h"
#include "../entity/player/Player.h"
#include "../utils/Utils.h"
#include "chunk/BaseChunk.h"
#include "generation/WorldGenerator.h"
#include "../block/BlockIdAndData.h"

GameWorld::GameWorld(GameClient* _client)
{
    client=_client;
    memset(mChunks,0,sizeof(mChunks));
    worldgenerator=NULL;
}

GameWorld::~GameWorld()
{
    for(BaseChunk*mchunk:mChunks)
    {
        if(mchunk!=NULL)
            delete mchunk;
    }
    if(worldgenerator!=NULL)
        delete worldgenerator;
}

void GameWorld::init(int _seed)
{
    worldgenerator=new WorldGenerator(_seed,this);
    for(unsigned int i=0; i<MAX_CHUNK; i++)
        for(unsigned int j=0; j<MAX_CHUNK; j++)
        {
            BaseChunk*mchunk=new BaseChunk(this);
            mchunk->setPos(glm::ivec3(j*CHUNK_SIZE,0,i*CHUNK_SIZE)+glm::ivec3(0,0,0));
            mChunks[i*MAX_CHUNK+j]=mchunk;
            worldgenerator->genChunk(mchunk);

        }
    centerChunk=MAX_CHUNK*MAX_CHUNK/2+MAX_CHUNK/2;
}
int offs=0;
void GameWorld::tick(float dtime)
{
    for(BaseChunk*mchunk:mChunks)
    {
        if(mchunk!=NULL)
            mchunk->tick(dtime);
    }

    glm::vec3 playerpos=mainPlayer->getPos(),centerpos=mChunks[centerChunk]->pos;
    if(playerpos.x>centerpos.x+CHUNK_SIZE)
    {
        for(unsigned int i=0; i<MAX_CHUNK; i++)
            for(unsigned int j=0; j<MAX_CHUNK; j++)
            {

                if(j==0)
                {
                    delete mChunks[i*MAX_CHUNK+j];
                    mChunks[i*MAX_CHUNK+j]=NULL;
                }

                if(j==MAX_CHUNK-1)
                {
                    BaseChunk*newchunk=new BaseChunk(this);
                    newchunk->setPos(mChunks[i*MAX_CHUNK+j]->pos+glm::ivec3(CHUNK_SIZE,0,0));
                    mChunks[i*MAX_CHUNK+j]=newchunk;
                    worldgenerator->genChunk(newchunk);

                    continue;
                }

                mChunks[i*MAX_CHUNK+j]=mChunks[i*MAX_CHUNK+j+1];
            }

    }
    if(playerpos.x<centerpos.x)
    {
        for(unsigned int i=0; i<MAX_CHUNK; i++)
            for(int j=MAX_CHUNK-1; j>=0; j--)
            {

                if(j==MAX_CHUNK-1)
                {
                    delete mChunks[i*MAX_CHUNK+j];
                    mChunks[i*MAX_CHUNK+j]=NULL;
                }

                if(j==0)
                {
                    BaseChunk*newchunk=new BaseChunk(this);
                    newchunk->setPos(mChunks[i*MAX_CHUNK+j]->pos+glm::ivec3(-CHUNK_SIZE,0,0));
                    mChunks[i*MAX_CHUNK+j]=newchunk;
                    worldgenerator->genChunk(newchunk);

                    continue;
                }

                mChunks[i*MAX_CHUNK+j]=mChunks[i*MAX_CHUNK+j-1];
            }

    }
    if(playerpos.z>centerpos.z+CHUNK_SIZE)
    {
        for(unsigned int i=0; i<MAX_CHUNK; i++)
            for(unsigned int j=0; j<MAX_CHUNK; j++)
            {

                if(i==0)
                {
                    delete mChunks[i*MAX_CHUNK+j];
                    mChunks[i*MAX_CHUNK+j]=NULL;
                }

                if(i==MAX_CHUNK-1)
                {
                    BaseChunk*newchunk=new BaseChunk(this);
                    newchunk->setPos(mChunks[i*MAX_CHUNK+j]->pos+glm::ivec3(0,0,CHUNK_SIZE));
                    mChunks[i*MAX_CHUNK+j]=newchunk;
                    worldgenerator->genChunk(newchunk);

                    continue;
                }

                mChunks[i*MAX_CHUNK+j]=mChunks[(i+1)*MAX_CHUNK+j];
            }

    }
    if(playerpos.z<centerpos.z)
    {
        for(int i=MAX_CHUNK-1; i>=0; i--)
            for(unsigned int j=0; j<MAX_CHUNK; j++)
            {

                if(i==MAX_CHUNK-1)
                {
                    delete mChunks[i*MAX_CHUNK+j];
                    mChunks[i*MAX_CHUNK+j]=NULL;
                }

                if(i==0)
                {
                    BaseChunk*newchunk=new BaseChunk(this);
                    newchunk->setPos(mChunks[i*MAX_CHUNK+j]->pos+glm::ivec3(0,0,-CHUNK_SIZE));
                    mChunks[i*MAX_CHUNK+j]=newchunk;
                    worldgenerator->genChunk(newchunk);

                    continue;
                }

                mChunks[i*MAX_CHUNK+j]=mChunks[(i-1)*MAX_CHUNK+j];
            }

    }
}

BaseChunk* GameWorld::getChunk(glm::vec3 pos)
{
    for(BaseChunk*mchunk:mChunks)
    {
        if(mchunk!=NULL)
        {
            glm::ivec3 chunkpos=mchunk->pos;
            if(pos.x>=chunkpos.x&&pos.x<chunkpos.x+CHUNK_SIZE&&pos.z>=chunkpos.z&&pos.z<chunkpos.z+CHUNK_SIZE)
                return mchunk;
        }
    }
    return NULL;
}

BaseChunk* GameWorld::getChunk(glm::ivec3 pos)
{
    for(BaseChunk*mchunk:mChunks)
    {
        if(mchunk!=NULL)
        {
            glm::ivec3 chunkpos=mchunk->pos;
            if(pos.x>=chunkpos.x&&pos.x<chunkpos.x+CHUNK_SIZE&&pos.z>=chunkpos.z&&pos.z<chunkpos.z+CHUNK_SIZE)
                return mchunk;
        }
    }
    return NULL;
}

BlockIdAndData GameWorld::getBlock(glm::ivec3 pos)
{
    BaseChunk*mchunk=getChunk(pos);
    if(mchunk==NULL)return {0,0};
    return mchunk->getBlock(pos);
}

