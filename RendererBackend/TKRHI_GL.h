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
      // Buffer
      void GenBuffer(uint* bufferId) override;
      void DeleteBuffers(int count, const uint* bufferIds) override;
      void BindUniformBuffer(uint bufferId) override;
      void BufferDataUniform(uint64 size, const void* data) override;
      void BufferSubDataUniform(uint64 offset, uint64 size, const void* data) override;

      // Shader
      uint CreateShader(uint type) override;
      void DeleteShader(uint shaderHandle) override;
      void ShaderSource(uint shaderHandle, const char* source) override;
      void CompileShader(uint shaderHandle) override;
      bool GetShaderCompileStatus(uint shaderHandle) override;
      int GetShaderInfoLogLength(uint shaderHandle) override;
      void GetShaderInfoLog(uint shaderHandle, int bufSize, char* infoLog) override;

      // Program
      uint CreateProgram() override;
      void DeleteProgram(uint programHandle) override;
      void AttachShader(uint programHandle, uint shaderHandle) override;
      void LinkProgram(uint programHandle) override;
      bool GetProgramLinkStatus(uint programHandle) override;
      int GetProgramInfoLogLength(uint programHandle) override;
      void GetProgramInfoLog(uint programHandle, int bufSize, char* infoLog) override;
      void UseProgram(uint programHandle) override;
      uint GetCurrentProgram() override;
      int GetUniformLocation(uint programHandle, const char* name) override;
      void Uniform1i(int location, int value) override;
      uint GetUniformBlockIndex(uint programHandle, const char* name) override;
      void UniformBlockBinding(uint programHandle, uint blockIndex, uint bindingPoint) override;
      void BindUniformBufferBase(uint bindingPoint, uint bufferId) override;

      // Texture
      void CreateTextures(int count, uint* textureIds) override;
      void DestroyTextures(int count, const uint* textureIds) override;
      void SetTextureBinding(uint target, uint textureId, uint textureSlot = 0) override;
      void SetTextureData2D(uint target,
                            int level,
                            int internalFormat,
                            int width,
                            int height,
                            uint format,
                            uint type,
                            const void* data) override;
      void SetCubeTextureFaceData(int faceIndex,
                                  int level,
                                  int internalFormat,
                                  int width,
                                  int height,
                                  uint format,
                                  uint type,
                                  const void* data) override;
      void UpdateTextureData2D(uint target,
                               int level,
                               int xoffset,
                               int yoffset,
                               int width,
                               int height,
                               uint format,
                               uint type,
                               const void* data) override;
      void SetTextureData3D(uint target,
                            int level,
                            int internalFormat,
                            int width,
                            int height,
                            int depth,
                            uint format,
                            uint type,
                            const void* data) override;
      void SetTextureParamInt(uint target, uint paramName, int value) override;
      void SetTextureParamFloat(uint target, uint paramName, float value) override;
      void GenerateTextureMipmaps(uint target) override;
      bool IsAnisotropicFilteringSupported() override;
      float GetMaxAnisotropyLevel() override;

      // Renderbuffer
      void CreateRenderbuffers(int count, uint* renderbufferIds) override;
      void SetRenderbufferBinding(uint renderbufferId) override;
      void DestroyRenderbuffers(int count, const uint* renderbufferIds) override;
      void AllocateRenderbufferStorage(uint internalformat, int width, int height) override;
      void AllocateRenderbufferStorageMSAA(int samples, uint internalformat, int width, int height) override;
      bool IsMSAARenderbufferSupported() override;
    };

    /** Populates TKRHI::g_rhi with OpenGL backend. Must be called after GL context creation. */
    void RegisterOpenGLBackend(void* glGetProcAddress);

  } // namespace TKRHI
} // namespace ToolKit
