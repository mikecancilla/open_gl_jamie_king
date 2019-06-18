#pragma once
#include <Primitives/ShapeData.h>

class ShapeGenerator
{
    static ShapeData makePlaneVerts(GLuint dimensions);
    static ShapeData makePlaneIndices(GLuint dimensions);

public:
    ShapeGenerator();
    virtual ~ShapeGenerator();

    static ShapeData makeTriangle();
    static ShapeData makeCube();
    static ShapeData makeArrow();
    static ShapeData makePlane(GLuint dimensions = 10);
};

