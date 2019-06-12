#pragma once
#include <Primitives/ShapeData.h>

class ShapeGenerator
{
public:
    ShapeGenerator();
    virtual ~ShapeGenerator();

    static ShapeData makeTriangle();
    static ShapeData makeCube();
};

