#include "BlockShape.h"
#include "../../../client/render/RendererContext.h"
#include "CubeBlockShape.h"
#include "../../../utils/Utils.h"


BlockShape* BlockShape::mBlockShapes[1024];

BlockShape::BlockShape()
{
}
BlockShape::~BlockShape()
{
}

void BlockShape::init()
{
}

void BlockShape::addToWorld(World *world,glm::ivec3 bpos,glm::vec3 pos,BlockIdAndData idAndData)
{

}

void BlockShape::initBlockShapes()
{
    memset(mBlockShapes,0,sizeof(mBlockShapes));
    mBlockShapes[SHAPE_CUBE]=new CubeBlockShape();
    mBlockShapes[SHAPE_CUBE]->init();
}
void BlockShape::deleteBlockShapes()
{
    for(BlockShape*shape:mBlockShapes)
        if(shape!=NULL)
            delete shape;
}
