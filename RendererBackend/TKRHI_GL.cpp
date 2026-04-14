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

    static RHIOpenGL s_glBackend;

    void RegisterOpenGLBackend(void* glGetProcAddress)
    {
      gladLoadGL((GLADloadfunc) glGetProcAddress);
      g_rhi = &s_glBackend;
    }

  } // namespace TKRHI

} // namespace ToolKit
