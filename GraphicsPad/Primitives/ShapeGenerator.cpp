#include "ShapeGenerator.h"
#include "glm.hpp"
#include <Primitives/Vertex.h>

#define NUM_ARRAY_ELEMENTS(a) (sizeof(a) / sizeof(*a))

ShapeGenerator::ShapeGenerator()
{
}

ShapeGenerator::~ShapeGenerator()
{
}

ShapeData ShapeGenerator::makeTriangle()
{
    ShapeData ret;

    Vertex verts[] = {
        glm::vec3(0, 1, 0),
        glm::vec3(1, 0, 0),

        glm::vec3(-1, -1, 0),
        glm::vec3(0, 1, 0),

        glm::vec3(1, -1, 0),
        glm::vec3(0, 0, 1)
    };

    GLushort indices[] = { 0,1,2 };

    ret.numVertices = NUM_ARRAY_ELEMENTS(verts);
    ret.vertices = new Vertex[ret.numVertices];
    memcpy(ret.vertices, verts, sizeof(verts));

    ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
    ret.indices = new GLushort[ret.numIndices];
    memcpy(ret.indices, indices, sizeof(indices));

    return ret;
}

ShapeData ShapeGenerator::makeCube()
{
    ShapeData ret;

    Vertex verts[] =
    {
        glm::vec3(-1, 1, 1), // 0
        glm::vec3(1, 0, 0), // Color
        glm::vec3(1, 1, 1), // 1
        glm::vec3(0, 1, 0), // Color
        glm::vec3(1, 1, -1), // 2
        glm::vec3(0, 0, 1), // Color
        glm::vec3(-1, 1, -1), // 3
        glm::vec3(1, 1, 1), // Color

        glm::vec3(-1, 1, -1), // 4
        glm::vec3(1, 0, 1), // Color
        glm::vec3(1, 1, -1), // 5
        glm::vec3(0, .5, .2), // Color
        glm::vec3(1, -1, -1), // 6
        glm::vec3(.6, .8, .4), // Color
        glm::vec3(-1, -1, -1), // 7
        glm::vec3(.3, 1, .5), // Color

        glm::vec3(1, 1, -1), // 8
        glm::vec3(.2, .5, .2), // Color
        glm::vec3(1, 1, 1), // 9
        glm::vec3(.9, .3, .7), // Color
        glm::vec3(1, -1, 1), // 10
        glm::vec3(.3, .7, .5), // Color
        glm::vec3(1, -1, -1), // 11
        glm::vec3(.5, .7, .5), // Color

        glm::vec3(-1, 1, 1), // 12
        glm::vec3(.7, .8, .2), // Color
        glm::vec3(-1, 1, -1), // 13
        glm::vec3(.5, .7, .3), // Color
        glm::vec3(-1, -1, -1), // 14
        glm::vec3(.4, .7, .7), // Color
        glm::vec3(-1, -1, 1), // 15
        glm::vec3(.2, .5, 1), // Color

        glm::vec3(1, 1, 1), // 16
        glm::vec3(.6, 1, .7), // Color
        glm::vec3(-1, 1, 1), // 17
        glm::vec3(.6, .4, .8), // Color
        glm::vec3(-1, -1, 1), // 18
        glm::vec3(.2, .8, .7), // Color
        glm::vec3(1, -1, 1), // 19
        glm::vec3(.2, .7, 1), // Color

        glm::vec3(1, -1, -1), // 20
        glm::vec3(.8, .3, .7), // Color
        glm::vec3(-1, -1, -1), // 21
        glm::vec3(.8, .9, .5), // Color
        glm::vec3(-1, -1, 1), // 22
        glm::vec3(.5, .8, .5), // Color
        glm::vec3(1, -1, 1), // 23
        glm::vec3(.9, 1, .2), // Color
    };

    ret.numVertices = NUM_ARRAY_ELEMENTS(verts);
    ret.vertices = new Vertex[ret.numVertices];
    memcpy(ret.vertices, verts, sizeof(verts));

    unsigned short indices[] = {
        0,   1,  2,  0,  2,  3, // Top
        4,   5,  6,  4,  6,  7, // Front
        8,   9, 10,  8, 10, 11, // Right
        12, 13, 14, 12, 14, 15, // Left
        16, 17, 18, 16, 18, 19, // Back
        20, 22, 21, 20, 23, 22 // Bottom
    };

    ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
    ret.indices = new GLushort[ret.numIndices];
    memcpy(ret.indices, indices, sizeof(indices));

    return ret;
}

ShapeData ShapeGenerator::makeArrow()
{
	ShapeData ret;

	// Vert + Color
	Vertex verts[] =
	{
		// Top side of arrow head
		glm::vec3(+0.00f, +0.25f, -0.25f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 0		 
		glm::vec3(+0.50f, +0.25f, -0.25f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 1	  
		glm::vec3(+0.00f, +0.25f, -1.00f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 2	  
		glm::vec3(-0.50f, +0.25f, -0.25f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 3

		// Bottom side of arrow head
		glm::vec3(+0.00f, -0.25f, -0.25f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 4	  
		glm::vec3(+0.50f, -0.25f, -0.25f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 5	 
		glm::vec3(+0.00f, -0.25f, -1.00f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 6	  
		glm::vec3(-0.50f, -0.25f, -0.25f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 7

		// Right side of arrow tip
		glm::vec3(+0.50f, +0.25f, -0.25f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 8	  
		glm::vec3(+0.00f, +0.25f, -1.00f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 9	  
		glm::vec3(+0.00f, -0.25f, -1.00f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 10  
		glm::vec3(+0.50f, -0.25f, -0.25f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 11

		// Left side of arrow tip
		glm::vec3(+0.00f, +0.25f, -1.00f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 12	  
		glm::vec3(-0.50f, +0.25f, -0.25f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 13  
		glm::vec3(+0.00f, -0.25f, -1.00f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 14  
		glm::vec3(-0.50f, -0.25f, -0.25f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 15

		// Back side of arrow tip
		glm::vec3(-0.50f, +0.25f, -0.25f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 16 		  
		glm::vec3(+0.50f, +0.25f, -0.25f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 17  
		glm::vec3(-0.50f, -0.25f, -0.25f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 18  
		glm::vec3(+0.50f, -0.25f, -0.25f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 19

		// Top side of back of arrow
		glm::vec3(+0.25f, +0.25f, -0.25f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 20	  
		glm::vec3(+0.25f, +0.25f, +1.00f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 21  
		glm::vec3(-0.25f, +0.25f, +1.00f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 22  
		glm::vec3(-0.25f, +0.25f, -0.25f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 23 

		// Bottom side of back of arrow
		glm::vec3(+0.25f, -0.25f, -0.25f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 24	  
		glm::vec3(+0.25f, -0.25f, +1.00f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 25 
		glm::vec3(-0.25f, -0.25f, +1.00f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 26 
		glm::vec3(-0.25f, -0.25f, -0.25f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 27

		// Right side of back of arrow
		glm::vec3(+0.25f, +0.25f, -0.25f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 28	  
		glm::vec3(+0.25f, -0.25f, -0.25f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 29  
		glm::vec3(+0.25f, -0.25f, +1.00f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 30  
		glm::vec3(+0.25f, +0.25f, +1.00f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 31

		// Left side of back of arrow
		glm::vec3(-0.25f, +0.25f, -0.25f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 32		  
		glm::vec3(-0.25f, -0.25f, -0.25f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 33	 
		glm::vec3(-0.25f, -0.25f, +1.00f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 34  
		glm::vec3(-0.25f, +0.25f, +1.00f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 35  
	
		// Back side of back of arrow
		glm::vec3(-0.25f, +0.25f, +1.00f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 36  
		glm::vec3(+0.25f, +0.25f, +1.00f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 37  
		glm::vec3(-0.25f, -0.25f, +1.00f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 38 
		glm::vec3(+0.25f, -0.25f, +1.00f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 39  
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(verts);
    ret.vertices = new Vertex[ret.numVertices];
    memcpy(ret.vertices, verts, sizeof(verts));

	GLushort indices[] = {
		0, 1, 2, // Top
		0, 2, 3,
		4, 6, 5, // Bottom
		4, 7, 6,
		8, 10, 9, // Right side of arrow tip
		8, 11, 10,
		12, 15, 13, // Left side of arrow tip
		12, 14, 15,
		16, 19, 17, // Back side of arrow tip
		16, 18, 19,
		20, 22, 21, // Top side of back of arrow
		20, 23, 22,
		24, 25, 26, // Bottom side of back of arrow
		24, 26, 27,
		28, 30, 29, // Right side of back of arrow
		28, 31, 30,
		32, 33, 34, // Left side of back of arrow
		32, 34, 35,
		36, 39, 37, // Back side of back of arrow
		36, 38, 39,
	};

    ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
    ret.indices = new GLushort[ret.numIndices];
    memcpy(ret.indices, indices, sizeof(indices));

    return ret;

}