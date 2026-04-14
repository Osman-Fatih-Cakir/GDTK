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

    // Buffer
    //////////////////////////////////////////

    /** Creates a GPU buffer and returns its handle. */
    using FnGenBuffer = void (*)(uint* bufferId);

    /** Deletes GPU buffers. */
    using FnDeleteBuffers = void (*)(int count, const uint* bufferIds);

    /** Binds a buffer to the uniform buffer target. */
    using FnBindUniformBuffer = void (*)(uint bufferId);

    /** Allocates storage for the currently bound uniform buffer. */
    using FnBufferDataUniform = void (*)(uint64 size, const void* data);

    /** Updates a sub-region of the currently bound uniform buffer. */
    using FnBufferSubDataUniform = void (*)(uint64 offset, uint64 size, const void* data);

    // Function pointer table.
    //////////////////////////////////////////

    struct RHIFunctions
    {
      FnGenBuffer GenBuffer                     = nullptr;
      FnDeleteBuffers DeleteBuffers             = nullptr;
      FnBindUniformBuffer BindUniformBuffer     = nullptr;
      FnBufferDataUniform BufferDataUniform     = nullptr;
      FnBufferSubDataUniform BufferSubDataUniform = nullptr;
    };

    /** Global RHI function table, populated by the active backend module. */
    TK_API extern RHIFunctions g_rhi;

    // Convenience inline wrappers.
    //////////////////////////////////////////

    inline void GenBuffer(uint* bufferId) { g_rhi.GenBuffer(bufferId); }

    inline void DeleteBuffers(int count, const uint* bufferIds) { g_rhi.DeleteBuffers(count, bufferIds); }

    inline void BindUniformBuffer(uint bufferId) { g_rhi.BindUniformBuffer(bufferId); }

    inline void BufferDataUniform(uint64 size, const void* data) { g_rhi.BufferDataUniform(size, data); }

    inline void BufferSubDataUniform(uint64 offset, uint64 size, const void* data)
    {
      g_rhi.BufferSubDataUniform(offset, size, data);
    }

  } // namespace TKRHI

} // namespace ToolKit
