/*
 * Copyright (c) 2019-2025 OtSoftware
 * This code is licensed under the GNU Lesser General Public License v3.0 (LGPL-3.0).
 * For more information, including options for a more permissive commercial license,
 * please visit [otyazilim.com] or contact us at [info@otyazilim.com].
 */

#pragma once

#include "Types.h"

namespace ToolKit
{

  namespace TKRHI
  {

    class TK_API RHIBackend
    {
     public:
      virtual ~RHIBackend() = default;

      // Buffer
      //////////////////////////////////////////

      virtual void GenBuffer(uint* bufferId)                                        = 0;
      virtual void DeleteBuffers(int count, const uint* bufferIds)                  = 0;
      virtual void BindUniformBuffer(uint bufferId)                                 = 0;
      virtual void BufferDataUniform(uint64 size, const void* data)                 = 0;
      virtual void BufferSubDataUniform(uint64 offset, uint64 size, const void* data) = 0;
    };

    /** Global RHI backend instance, set by the active backend module. */
    TK_API extern RHIBackend* g_rhi;

    // Convenience inline wrappers.
    //////////////////////////////////////////

    inline void GenBuffer(uint* bufferId) { g_rhi->GenBuffer(bufferId); }

    inline void DeleteBuffers(int count, const uint* bufferIds) { g_rhi->DeleteBuffers(count, bufferIds); }

    inline void BindUniformBuffer(uint bufferId) { g_rhi->BindUniformBuffer(bufferId); }

    inline void BufferDataUniform(uint64 size, const void* data) { g_rhi->BufferDataUniform(size, data); }

    inline void BufferSubDataUniform(uint64 offset, uint64 size, const void* data)
    {
      g_rhi->BufferSubDataUniform(offset, size, data);
    }

  } // namespace TKRHI

} // namespace ToolKit
