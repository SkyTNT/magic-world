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
            mchunk->setBlock(chunkpos+glm::ivec3(j,getheight(i,j),i),1,0);
            #undef getheight
        }
    }
/*    srand(seed+(int)chunkpos.x+(int)chunkpos.z);
    Ground *mGround=new Ground();
    mGround->init();

    int wcount=33,hcount=33;

    for(int i=0; i<hcount; i++)
    {
        for(int j=0; j<wcount; j++)
        {
            #define getheight(a,b) heightMapGenerator->getHeight(b+chunkpos.x*2+INT_MAX/2,a+chunkpos.z*2+INT_MAX/2)-100
            BasePiece* mpiece1=new BasePiece();
            mpiece1->mSubstanceInfos[0]=new SubstanceInfo{glm::vec3(j*0.5f,getheight(i,j),i*0.5f)+chunkpos,1,0};
            mpiece1->mSubstanceInfos[1]=new SubstanceInfo{glm::vec3(j*0.5f,getheight(i+1,j),i*0.5f)+chunkpos,1,0};
            mpiece1->mSubstanceInfos[3]=new SubstanceInfo{glm::vec3(j*0.5f,getheight(i,j+1),i*0.5f)+chunkpos,1,0};
            mpiece1->update();
            BasePiece* mpiece2=new BasePiece();
            mpiece2->mSubstanceInfos[0]=new SubstanceInfo{glm::vec3(j*0.5f,getheight(i+1,j+1),i*0.5f)+chunkpos,1,0};
            mpiece2->mSubstanceInfos[3]=new SubstanceInfo{glm::vec3(j*0.5f,getheight(i+1,j),i*0.5f)+chunkpos,1,0};
            mpiece2->mSubstanceInfos[1]=new SubstanceInfo{glm::vec3(j*0.5f,getheight(i,j+1),i*0.5f)+chunkpos,1,0};
            mpiece2->update();
            mGround->addPiece(mpiece1);
            mGround->addPiece(mpiece2);
        }
    }
    //BasePiece*mpiece=new BasePiece();
    //mpiece->mSubstances[0]=new SubstanceInfo{glm::vec3(0,0,0)};
    mchunk->mObjects.push_back(mGround);*/
}
