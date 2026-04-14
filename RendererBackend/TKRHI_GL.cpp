/*
 * Copyright (c) 2019-2025 OtSoftware
 * This code is licensed under the GNU Lesser General Public License v3.0 (LGPL-3.0).
 * For more information, including options for a more permissive commercial license,
 * please visit [otyazilim.com] or contact us at [info@otyazilim.com].
 */

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#include "TKRHI_GL.h"

namespace ToolKit
{

  namespace TKRHI
  {

    void RHIOpenGL::GenBuffer(uint* bufferId) { glGenBuffers(1, bufferId); }

    void RHIOpenGL::DeleteBuffers(int count, const uint* bufferIds) { glDeleteBuffers(count, bufferIds); }

    void RHIOpenGL::BindUniformBuffer(uint bufferId) { glBindBuffer(GL_UNIFORM_BUFFER, bufferId); }

    void RHIOpenGL::BufferDataUniform(uint64 size, const void* data)
    {
      glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
    }

    void RHIOpenGL::BufferSubDataUniform(uint64 offset, uint64 size, const void* data)
    {
      glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    }

    uint RHIOpenGL::CreateShader(uint type) { return glCreateShader(type); }

    void RHIOpenGL::DeleteShader(uint shaderHandle) { glDeleteShader(shaderHandle); }

    void RHIOpenGL::ShaderSource(uint shaderHandle, const char* source)
    {
      glShaderSource(shaderHandle, 1, &source, nullptr);
    }

    void RHIOpenGL::CompileShader(uint shaderHandle) { glCompileShader(shaderHandle); }

    bool RHIOpenGL::GetShaderCompileStatus(uint shaderHandle)
    {
      GLint compiled = 0;
      glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compiled);
      return compiled != 0;
    }

    int RHIOpenGL::GetShaderInfoLogLength(uint shaderHandle)
    {
      GLint length = 0;
      glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &length);
      return length;
    }

    void RHIOpenGL::GetShaderInfoLog(uint shaderHandle, int bufSize, char* infoLog)
    {
      glGetShaderInfoLog(shaderHandle, bufSize, nullptr, infoLog);
    }

    // Program

    uint RHIOpenGL::CreateProgram() { return glCreateProgram(); }

    void RHIOpenGL::DeleteProgram(uint programHandle) { glDeleteProgram(programHandle); }

    void RHIOpenGL::AttachShader(uint programHandle, uint shaderHandle)
    {
      glAttachShader(programHandle, shaderHandle);
    }

    void RHIOpenGL::LinkProgram(uint programHandle) { glLinkProgram(programHandle); }

    bool RHIOpenGL::GetProgramLinkStatus(uint programHandle)
    {
      GLint linked = 0;
      glGetProgramiv(programHandle, GL_LINK_STATUS, &linked);
      return linked != 0;
    }

    int RHIOpenGL::GetProgramInfoLogLength(uint programHandle)
    {
      GLint length = 0;
      glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &length);
      return length;
    }

    void RHIOpenGL::GetProgramInfoLog(uint programHandle, int bufSize, char* infoLog)
    {
      glGetProgramInfoLog(programHandle, bufSize, nullptr, infoLog);
    }

    void RHIOpenGL::UseProgram(uint programHandle) { glUseProgram(programHandle); }

    uint RHIOpenGL::GetCurrentProgram()
    {
      GLint current = 0;
      glGetIntegerv(GL_CURRENT_PROGRAM, &current);
      return (uint) current;
    }

    int RHIOpenGL::GetUniformLocation(uint programHandle, const char* name)
    {
      return glGetUniformLocation(programHandle, name);
    }

    void RHIOpenGL::Uniform1i(int location, int value) { glUniform1i(location, value); }

    uint RHIOpenGL::GetUniformBlockIndex(uint programHandle, const char* name)
    {
      return glGetUniformBlockIndex(programHandle, name);
    }

    void RHIOpenGL::UniformBlockBinding(uint programHandle, uint blockIndex, uint bindingPoint)
    {
      glUniformBlockBinding(programHandle, blockIndex, bindingPoint);
    }

    void RHIOpenGL::BindUniformBufferBase(uint bindingPoint, uint bufferId)
    {
      glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, bufferId);
    }

    static RHIOpenGL s_glBackend;

    void RegisterOpenGLBackend(void* glGetProcAddress)
    {
      gladLoadGL((GLADloadfunc) glGetProcAddress);
      g_rhi = &s_glBackend;
    }

  } // namespace TKRHI

} // namespace ToolKit
