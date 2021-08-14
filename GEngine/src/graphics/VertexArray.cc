#include "VertexArray.hh"

#include "GL/GLVertexArray.hh"

namespace GE
{

VertexArray* VertexArray::create()
{
    return new GLVertexArray{};
}

}