cmake_minimum_required(VERSION 2.6)
project(BitlinkerCommons)

# Sources
set(BITLINKER_COMMONS_SOURCES
        Common/Endianness.cpp
        Common/StringUtils.cpp
        Common/StringUtils.h

        #Logger
        Logger/Log.h
        Logger/Log.cpp

        #Render
        Render/Init.h
        Render/Init.cpp
        Render/BufferObject.h
        Render/Camera.h
        Render/Camera.cpp
        Render/IBindable.h
        Render/RenderCommon.h
        Render/GLContext.h
        Render/GLContext.cpp
        Render/ScopeBind.h
        Render/Shader.h
        Render/Shader.cpp
        Render/ShaderProgram.h
        Render/ShaderProgram.cpp
        Render/Texture.h
        Render/Texture.cpp
        Render/VertexArrayObject.h
        Render/RenderWindow.h
        Render/RenderWindow.cpp
        Render/RenderNode.h
        Render/RenderNode.cpp
        Render/Frustum.h
        Render/Frustum.cpp
        Render/SharedTextureMgr.h
        Render/SharedTextureMgr.cpp

        #Streams
        Streams/FileStream.h
        Streams/FileStream.cpp
        Streams/MemoryStream.h
        Streams/MemoryStream.cpp

        #Imaging
        Imaging/ImageInfo.h
        Imaging/ImageDecoder.h
        Imaging/DdsImageDecoder.h
        Imaging/DdsImageDecoder.cpp
        Imaging/TgaImageEncoder.cpp
        Imaging/TgaImageEncoder.h
        )

add_library(BitlinkerCommons ${BITLINKER_COMMONS_SOURCES})