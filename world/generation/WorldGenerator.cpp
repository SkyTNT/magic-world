#include "WorldGenerator.h"
#include "../GameWorld.h"
#include "../chunk/BaseChunk.h"
#include "../../utils/NoiseGenerator.h"

WorldGenerator::WorldGenerator(int _seed,GameWorld* _mWorld):seed(_seed),mWorld(_mWorld)
{
    heightMapGenerator=new NoiseGenerator(_seed);
}

WorldGenerator::~WorldGenerator()
{

}

void WorldGenerator::genChunk(BaseChunk*mchunk)
{

    glm::ivec3 chunkpos=mchunk->pos;
    for(int i=0; i<CHUNK_SIZE; i++)
    {
        for(int j=0; j<CHUNK_SIZE; j++)
        {
            #define getheight(a,b) heightMapGenerator->getHeight(b+chunkpos.x+INT_MAX/2,a+chunkpos.z+INT_MAX/2)-100
            int height=getheight(i,j);
            for(int h=0; h<3; h++)
            mchunk->setBlock(chunkpos+glm::ivec3(j,h,i),1,0);
            #undef getheight
        }
    }
}
