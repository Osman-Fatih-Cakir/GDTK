/*
 * Copyright (c) 2019-2025 OtSoftware
 * This code is licensed under the GNU Lesser General Public License v3.0 (LGPL-3.0).
 * For more information, including options for a more permissive commercial license,
 * please visit [otyazilim.com] or contact us at [info@otyazilim.com].
 */

#pragma once

namespace ToolKit
{
  namespace TKRHI
  {
    /** Populates TKRHI::g_rhi with OpenGL implementations. Must be called after GL context creation. */
    void RegisterOpenGLBackend(void* glGetProcAddress);
  }
} // namespace ToolKit
