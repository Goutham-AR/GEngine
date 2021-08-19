#include "VertexArray.hh"

#include "../GL/GLVertexArray.hh"

namespace GE
{

Sptr<VertexArray> VertexArray::create()
{
    return Sptr<VertexArray>{new GLVertexArray{}};
}

}