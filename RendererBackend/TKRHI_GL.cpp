/*
 * Copyright (c) 2019-2025 OtSoftware
 * This code is licensed under the GNU Lesser General Public License v3.0 (LGPL-3.0).
 * For more information, including options for a more permissive commercial license,
 * please visit [otyazilim.com] or contact us at [info@otyazilim.com].
 */

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#include "TKRHI_GL.h"
#include "TKRHI.h"

namespace ToolKit
{

  namespace TKRHI
  {

    static void GL_GenBuffer(uint* bufferId) { glGenBuffers(1, bufferId); }

    static void GL_DeleteBuffers(int count, const uint* bufferIds) { glDeleteBuffers(count, bufferIds); }

    static void GL_BindUniformBuffer(uint bufferId) { glBindBuffer(GL_UNIFORM_BUFFER, bufferId); }

    static void GL_BufferDataUniform(uint64 size, const void* data)
    {
      glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
    }

    static void GL_BufferSubDataUniform(uint64 offset, uint64 size, const void* data)
    {
      glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    }

    void RegisterOpenGLBackend(void* glGetProcAddress)
    {
      gladLoadGL((GLADloadfunc) glGetProcAddress);

      g_rhi.GenBuffer            = GL_GenBuffer;
      g_rhi.DeleteBuffers        = GL_DeleteBuffers;
      g_rhi.BindUniformBuffer    = GL_BindUniformBuffer;
      g_rhi.BufferDataUniform    = GL_BufferDataUniform;
      g_rhi.BufferSubDataUniform = GL_BufferSubDataUniform;
    }

  } // namespace TKRHI

} // namespace ToolKit
