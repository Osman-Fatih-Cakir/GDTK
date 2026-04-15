/*
 * Copyright (c) 2019-2025 OtSoftware
 * This code is licensed under the GNU Lesser General Public License v3.0 (LGPL-3.0).
 * For more information, including options for a more permissive commercial license,
 * please visit [otyazilim.com] or contact us at [info@otyazilim.com].
 */

#pragma once

#include "RHIConstants.h"
#include "Stats.h"
#include "TKOpenGL.h"
#include "Types.h"

namespace ToolKit
{
  class TK_API RHI
  {
    friend class Renderer;
    friend class Framebuffer;
    friend class RenderSystem;
    friend class Mesh;
    friend class Main;

   public:
    struct TextureSlotState
    {
      GLuint textureID = 0;
      GLenum target    = 0;
    };

    using TextureIdSlotMap = std::unordered_map<GLenum, TextureSlotState>;

    // Framebuffer helpers
    static void SetFramebuffer(GLenum target, GLuint framebufferID);
    static void DeleteFramebuffers(GLsizei n, const GLuint* framebuffers);

    static void StoreFramebufferBindings();
    static void RestoreFramebufferBindings();

    // Texture helpers
    static void SetTexture(GLenum target, GLuint textureID, GLenum textureSlot = 0);
    static void DeleteTexture(GLuint textureID);

    // Vertex array helpers
    static void BindVertexArray(GLuint VAO);

   private:
    static GLuint m_currentReadFramebufferID;
    static GLuint m_currentDrawFramebufferID;
    static GLuint m_currentVAO;

    // Stacks to support nested Store/Restore calls
    static IntArray m_storedReadFramebufferStack;
    static IntArray m_storedDrawFramebufferStack;

    static TextureIdSlotMap m_textureIdSlotMap;
  };

} // namespace ToolKit
