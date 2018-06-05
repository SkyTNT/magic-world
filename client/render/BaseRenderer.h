#pragma once

#include "RendererContext.h"

class BaseRenderer
{
public:
    RendererContext*context;

    BaseRenderer(RendererContext*ctx);
    virtual ~BaseRenderer();
    virtual void init()=0;
    virtual void tick(float dtime)=0;
    virtual void render()=0;
};
