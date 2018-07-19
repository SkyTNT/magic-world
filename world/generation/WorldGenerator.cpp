#include "WorldGenerator.h"
#include "../World.h"
#include "../chunk/Chunk.h"
#include "../../utils/NoiseGenerator.h"

WorldGenerator::WorldGenerator(int _seed,World* _mWorld):seed(_seed),mWorld(_mWorld)
{
    heightMapGenerator=new NoiseGenerator(_seed);
    heightMapGenerator->setParameters(NoiseParameters{5,30,555,10,0.5});

}

WorldGenerator::~WorldGenerator()
{

}

void WorldGenerator::genChunk(Chunk*mchunk)
{
    glm::ivec3 chunkpos=mchunk->pos;
    for(int i=0; i<CHUNK_SIZE; i++)
    {
        for(int j=0; j<CHUNK_SIZE; j++)
        {
            #define getheight(a,b) heightMapGenerator->getHeight(b+chunkpos.x+INT_MAX/2,a+chunkpos.z+INT_MAX/2)
            int height=getheight(i,j);
            for(int h=0; h<height; h++)
            mchunk->setBlock(chunkpos+glm::ivec3(j,h,i),1,0);
            #undef getheight
        }
    }
}
