#include "WorldRenderer.h"

#include "../GameClient.h"
#include "../../entity/player/Player.h"
#include "../../world/GameWorld.h"
#include "../../world/chunk/BaseChunk.h"
#include "../../utils/Utils.h"
#include "../../block/blockshape/BlockShape.h"
#include "../../block/Block.h"
#include "ObjectGroup.h"
#include <math.h>

#define M_PI  3.14159265358979323846264f

BlockShape*bs;

WorldRenderer::WorldRenderer(GameClient* _client)
{
    client=_client;
    mWorld=NULL;
    mPlayer=NULL;
    blockShader=0;
    context=new RendererContext(client);
    mTextures=new Textures(1024);
    bs=new BlockShape();
}

WorldRenderer::~WorldRenderer()
{
    glDeleteProgram(blockShader);
    delete context;
    delete mTextures;
}
void WorldRenderer::init()
{

    //mTextures->LoadTextureExt(0,"assets\\gold_ore.bmp");


    GLuint cvs,cfs;
    RendererContext::creatShader(&cfs,"assets\\resource\\shader\\block.frag",GL_FRAGMENT_SHADER);
    RendererContext::creatShader(&cvs,"assets\\resource\\shader\\block.vert",GL_VERTEX_SHADER);
    RendererContext::linkShader(&blockShader,cvs,cfs);

    context->light0.setLightColor(glm::vec3(1,1,1));
    context->light0.setPos(glm::vec3(250,180,250));

    mPlayer=client->getMainPlayer();
    bs->init();
}

void WorldRenderer::tick(float dtime)
{
    if(mWorld==NULL)
        return;
    glm::vec3 epos=mPlayer->getPos();
    glm::vec2 hr=mPlayer->getHeadRotate();
    setLookAt(epos,glm::vec3(epos.x+cos(hr.y)*sin(hr.x),epos.y+sin(hr.y),epos.z+cos(hr.y)*cos(hr.x)),glm::vec3(0,1,0));
    context->light0.setPos(epos);
}

void WorldRenderer::setWorld(GameWorld* _mWorld)
{
    mWorld=_mWorld;
}

void WorldRenderer::setwidthheight(int _width,int _height)
{
    width=_width;
    height=_height;
    context->proj = glm::perspective((float)(M_PI/4), (float)width/(float)height, 0.1f, 1000.0f);
}

void WorldRenderer::setLookAt(glm::vec3 epos,glm::vec3 cpos,glm::vec3 upos)
{
    context->view = glm::lookAt(epos,cpos,upos);
}

void WorldRenderer::render()
{
    if(mWorld==NULL)
        return;
    glUseProgram(blockShader);
    glUniformMatrix4fv(glGetUniformLocation(blockShader, "view"), 1, GL_FALSE, glm::value_ptr(context->view));
    glUniformMatrix4fv(glGetUniformLocation(blockShader, "proj"), 1, GL_FALSE, glm::value_ptr(context->proj));
    glUniform3fv(glGetUniformLocation(blockShader, "lightColor"), 1,glm::value_ptr(context->light0.color));
    glUniform3fv(glGetUniformLocation(blockShader, "lightPos"), 1,glm::value_ptr(context->light0.pos));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,Block::blockTextures->texid);
    glUniform1i(glGetUniformLocation(blockShader, "mTexture"), 0);
    for(BaseChunk*mchunk:mWorld->mChunks)
    {
        glBindVertexArray(mchunk->objGroup->vao);
        glm::mat4 model;
        model = glm::translate(model,glm::vec3(mchunk->objGroup->position));
        glUniformMatrix4fv(glGetUniformLocation(blockShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES,0,mchunk->objGroup->mVertexCount);
        glBindVertexArray(0);
    }

}
