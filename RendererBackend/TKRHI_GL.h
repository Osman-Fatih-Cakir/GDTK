/*
 * Copyright (c) 2019-2025 OtSoftware
 * This code is licensed under the GNU Lesser General Public License v3.0 (LGPL-3.0).
 * For more information, including options for a more permissive commercial license,
 * please visit [otyazilim.com] or contact us at [info@otyazilim.com].
 */

#pragma once

#include "TKRHI.h"

namespace ToolKit
{
  namespace TKRHI
  {

    class RHIOpenGL : public RHIBackend
    {
     public:
      void GenBuffer(uint* bufferId) override;
      void DeleteBuffers(int count, const uint* bufferIds) override;
      void BindUniformBuffer(uint bufferId) override;
      void BufferDataUniform(uint64 size, const void* data) override;
      void BufferSubDataUniform(uint64 offset, uint64 size, const void* data) override;
    };

    /** Populates TKRHI::g_rhi with OpenGL backend. Must be called after GL context creation. */
    void RegisterOpenGLBackend(void* glGetProcAddress);

  } // namespace TKRHI
} // namespace ToolKit
