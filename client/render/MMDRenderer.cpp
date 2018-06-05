#include "MMDRenderer.h"

MMDRenderer::MMDRenderer(RendererContext*ctx):BaseRenderer(ctx)
{
    textures=NULL;
    model=NULL;
    vao=0;
}

MMDRenderer::~MMDRenderer()
{
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&vboNor);
    glDeleteBuffers(1,&vboPos);
    glDeleteBuffers(1,&vboUV);
    if(!textures)
        delete textures;
}

void MMDRenderer::setModel(std::shared_ptr<saba::MMDModel> _model)
{
    this->model=_model;
    indexElemSize = model->GetIndexElementSize();
    switch (indexElemSize)
    {
    case 1:
        m_indexType = GL_UNSIGNED_BYTE;
        break;
    case 2:
        m_indexType = GL_UNSIGNED_SHORT;
        break;
    case 4:
        m_indexType = GL_UNSIGNED_INT;
        break;
    default:
        MessageBox(NULL, "unknow index size!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        break;
    }

    size_t matc = model->GetMaterialCount();
    if(!textures)
        delete textures;
    textures=new Textures(matc);
    auto mats = model->GetMaterials();
    for (unsigned int i = 0; i < matc; i++)
    {
        textures->LoadTextureExt(i,mats[i].m_texture.c_str());
    }

    size_t vc=model->GetVertexCount();
    auto positions = model->GetPositions();
    auto normals = model->GetNormals();
    auto uvs = model->GetUVs();

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vboPos);
    glGenBuffers(1, &vboNor);
    glGenBuffers(1, &vboUV);
    glGenBuffers(1, &ebo);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glBufferData(GL_ARRAY_BUFFER, vc*3*sizeof(GLfloat), positions, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vboNor);
    glBufferData(GL_ARRAY_BUFFER, vc*3*sizeof(GLfloat), normals, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vboUV);
    glBufferData(GL_ARRAY_BUFFER, vc*2*sizeof(GLfloat), uvs, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->GetIndexCount()*indexElemSize, model->GetIndices(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0);
}

void MMDRenderer::setShader(GLuint sp)
{
    shader=sp;
}

void MMDRenderer::updateMMD(float dtime)
{
    if(!model)
        return;

    //model->SaveBaseAnimation();//1

    model->BeginAnimation();

    //model->LoadBaseAnimation();//2

    model->UpdateMorphAnimation();

    model->UpdateNodeAnimation(false);

    model->UpdatePhysicsAnimation(dtime);

    model->UpdateNodeAnimation(true);

    model->EndAnimation();

    model->Update();

    size_t vc=model->GetVertexCount();
    auto positions = model->GetUpdatePositions();
    auto normals = model->GetUpdateNormals();
    auto uvs = model->GetUpdateUVs();

    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glBufferSubData(GL_ARRAY_BUFFER, 0,vc*3*sizeof(GLfloat), positions);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vboNor);
    glBufferSubData(GL_ARRAY_BUFFER, 0,vc*3*sizeof(GLfloat), normals);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vboUV);
    glBufferSubData(GL_ARRAY_BUFFER, 0,vc*2*sizeof(GLfloat), uvs);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void MMDRenderer::setPos(glm::vec3 pos)
{
    glm::mat4 mod;
    mod = glm::translate(mod,pos);
    mod=glm::scale(mod,glm::vec3(0.1f,0.1f,0.1f));
    modelmat=mod;
}

void MMDRenderer::init()
{
}

void MMDRenderer::tick(float dtime)
{
    updateMMD(dtime);
}

void MMDRenderer::render()
{
    if(!model)
        return;

    glUseProgram(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(context->view));
    glUniformMatrix4fv(glGetUniformLocation(shader, "proj"), 1, GL_FALSE, glm::value_ptr(context->proj));
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(modelmat));
    glUniform3fv(glGetUniformLocation(shader, "lightColor"), 1,glm::value_ptr(context->light0.color));
    glUniform3fv(glGetUniformLocation(shader, "lightPos"), 1,glm::value_ptr(context->light0.pos));

    glBindVertexArray(vao);

    auto submeshes = model->GetSubMeshes();
    auto mmdmats = model->GetMaterials();
    size_t sms = model->GetSubMeshCount();
    for (unsigned int j = 0; j < sms; j++)
    {
        auto submesh = submeshes[j];
        auto mmdmat=mmdmats[submesh.m_materialID];
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,textures->textureIds[submesh.m_materialID]);
        glUniform1f(glGetUniformLocation(shader, "mAlpha"),mmdmat.m_alpha);
        glUniform1i(glGetUniformLocation(shader, "mTexture"), 0);

        glDrawElements(GL_TRIANGLES, submesh.m_vertexCount, m_indexType, (void*)(submesh.m_beginIndex*indexElemSize));
    }

    glBindVertexArray(0);

}
