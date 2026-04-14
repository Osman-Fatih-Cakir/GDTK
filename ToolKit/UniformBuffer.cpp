/*
 * Copyright (c) 2019-2025 OtSoftware
 * This code is licensed under the GNU Lesser General Public License v3.0 (LGPL-3.0).
 * For more information, including options for a more permissive commercial license,
 * please visit [otyazilim.com] or contact us at [info@otyazilim.com].
 */

#include "UniformBuffer.h"

#include "RHI.h"
#include "Stats.h"
#include "TKRHI.h"

#include "DebugNew.h"

namespace ToolKit
{

  UniformBuffer::UniformBuffer()
  {
    m_id   = 0;
    m_slot = -1;
  }

  UniformBuffer::~UniformBuffer() { TKRHI::DeleteBuffers(1, &m_id); }

  void UniformBuffer::Init(uint64 size)
  {
    m_size = size;
    TKRHI::GenBuffer(&m_id);
    TKRHI::BindUniformBuffer(m_id);
    TKRHI::BufferDataUniform(m_size, nullptr);
  }

  void UniformBuffer::Map(const void* data, uint64 size)
  {
    // Sanitize buffer.
    if (m_id == NullHandle || m_slot == InvalidHandle)
    {
      TK_ERR("Uniform buffer is not initialized properly.");
      return;
    }

    if (size != m_size)
    {
      TK_ERR("Uniform buffer size does not match.");
      return;
    }

    if (size == 0)
    {
      return;
    }

    Stats::IncrementStat(FrameStatType::UboUpdates);

    TKRHI::BindUniformBuffer(m_id);
    TKRHI::BufferSubDataUniform(0, size, data);
  }

} // namespace ToolKit