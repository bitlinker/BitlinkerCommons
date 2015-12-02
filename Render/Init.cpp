#include <Render/RenderCommon.h>
#include <Render/Init.h>
#include <Exception/Exception.h>

namespace Commons
{
	namespace Render
	{
    Init::Init()
    {
        if (GL_TRUE != glfwInit()) // TODO: init in window class? GLFW singleton initializer?
            throw Commons::UnknownException("Can't init GLFW");       
    }


    Init::~Init()
    {
        glfwTerminate();
    }
}
}