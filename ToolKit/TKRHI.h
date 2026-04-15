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

    enum class TextureParam : uint
    {
      MagFilter          = 0x2800, // GL_TEXTURE_MAG_FILTER
      MinFilter          = 0x2801, // GL_TEXTURE_MIN_FILTER
      WrapS              = 0x2802, // GL_TEXTURE_WRAP_S
      WrapT              = 0x2803, // GL_TEXTURE_WRAP_T
      MaxLevel           = 0x813D, // GL_TEXTURE_MAX_LEVEL
      WrapR              = 0x8072, // GL_TEXTURE_WRAP_R
      MaxAnisotropyExt   = 0x84FE, // GL_TEXTURE_MAX_ANISOTROPY_EXT
      MaxAnisotropyQuery = 0x84FF  // GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
    };

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

      // Shader
      //////////////////////////////////////////

      virtual uint CreateShader(uint type)                                            = 0;
      virtual void DeleteShader(uint shaderHandle)                                    = 0;
      virtual void ShaderSource(uint shaderHandle, const char* source)                = 0;
      virtual void CompileShader(uint shaderHandle)                                   = 0;
      virtual bool GetShaderCompileStatus(uint shaderHandle)                          = 0;
      virtual int GetShaderInfoLogLength(uint shaderHandle)                           = 0;
      virtual void GetShaderInfoLog(uint shaderHandle, int bufSize, char* infoLog)    = 0;

      // Program
      //////////////////////////////////////////

      virtual uint CreateProgram()                                                                = 0;
      virtual void DeleteProgram(uint programHandle)                                              = 0;
      virtual void AttachShader(uint programHandle, uint shaderHandle)                            = 0;
      virtual void LinkProgram(uint programHandle)                                                = 0;
      virtual bool GetProgramLinkStatus(uint programHandle)                                       = 0;
      virtual int GetProgramInfoLogLength(uint programHandle)                                     = 0;
      virtual void GetProgramInfoLog(uint programHandle, int bufSize, char* infoLog)              = 0;
      virtual void UseProgram(uint programHandle)                                                 = 0;
      virtual uint GetCurrentProgram()                                                            = 0;
      virtual int GetUniformLocation(uint programHandle, const char* name)                        = 0;
      virtual void Uniform1i(int location, int value)                                             = 0;
      virtual uint GetUniformBlockIndex(uint programHandle, const char* name)                     = 0;
      virtual void UniformBlockBinding(uint programHandle, uint blockIndex, uint bindingPoint)    = 0;
      virtual void BindUniformBufferBase(uint bindingPoint, uint bufferId)                        = 0;

      // Texture
      //////////////////////////////////////////

      virtual void CreateTextures(int count, uint* textureIds)                                     = 0;
      virtual void DestroyTextures(int count, const uint* textureIds)                              = 0;
      virtual void SetTextureBinding(uint target, uint textureId, uint textureSlot = 0)            = 0;
      virtual void SetTextureData2D(uint target,
                                    int level,
                                    int internalFormat,
                                    int width,
                                    int height,
                                    uint format,
                                    uint type,
                                    const void* data)                                             = 0;
      virtual void SetCubeTextureFaceData(int faceIndex,
                                          int level,
                                          int internalFormat,
                                          int width,
                                          int height,
                                          uint format,
                                          uint type,
                                          const void* data)                                       = 0;
      virtual void UpdateTextureData2D(uint target,
                                       int level,
                                       int xoffset,
                                       int yoffset,
                                       int width,
                                       int height,
                                       uint format,
                                       uint type,
                                       const void* data)                                          = 0;
      virtual void SetTextureData3D(uint target,
                                    int level,
                                    int internalFormat,
                                    int width,
                                    int height,
                                    int depth,
                                    uint format,
                                    uint type,
                                    const void* data)                                             = 0;
      virtual void SetTextureParamInt(uint target, uint paramName, int value)                      = 0;
      virtual void SetTextureParamFloat(uint target, uint paramName, float value)                 = 0;
      virtual void GenerateTextureMipmaps(uint target)                                             = 0;
      virtual bool IsAnisotropicFilteringSupported()                                               = 0;
      virtual float GetMaxAnisotropyLevel()                                                        = 0;

      // Renderbuffer
      //////////////////////////////////////////

      virtual void CreateRenderbuffers(int count, uint* renderbufferIds)                           = 0;
      virtual void SetRenderbufferBinding(uint renderbufferId)                                     = 0;
      virtual void DestroyRenderbuffers(int count, const uint* renderbufferIds)                    = 0;
      virtual void AllocateRenderbufferStorage(uint internalformat, int width, int height)         = 0;
      virtual void AllocateRenderbufferStorageMSAA(int samples,
                                                   uint internalformat,
                                                   int width,
                                                   int height)                                    = 0;
      virtual bool IsMSAARenderbufferSupported()                                                    = 0;
    };

    /** Global RHI backend instance, set by the active backend module. */
    TK_API extern RHIBackend* g_rhi;

    static constexpr uint InvalidIndex = 0xFFFFFFFFu;

    // Convenience inline wrappers.
    //////////////////////////////////////////

    // Buffer

    inline void GenBuffer(uint* bufferId) { g_rhi->GenBuffer(bufferId); }

    inline void DeleteBuffers(int count, const uint* bufferIds) { g_rhi->DeleteBuffers(count, bufferIds); }

    inline void BindUniformBuffer(uint bufferId) { g_rhi->BindUniformBuffer(bufferId); }

    inline void BufferDataUniform(uint64 size, const void* data) { g_rhi->BufferDataUniform(size, data); }

    inline void BufferSubDataUniform(uint64 offset, uint64 size, const void* data)
    {
      g_rhi->BufferSubDataUniform(offset, size, data);
    }

    // Shader

    inline uint CreateShader(uint type) { return g_rhi->CreateShader(type); }

    inline void DeleteShader(uint shaderHandle) { g_rhi->DeleteShader(shaderHandle); }

    inline void ShaderSource(uint shaderHandle, const char* source) { g_rhi->ShaderSource(shaderHandle, source); }

    inline void CompileShader(uint shaderHandle) { g_rhi->CompileShader(shaderHandle); }

    inline bool GetShaderCompileStatus(uint shaderHandle) { return g_rhi->GetShaderCompileStatus(shaderHandle); }

    inline int GetShaderInfoLogLength(uint shaderHandle) { return g_rhi->GetShaderInfoLogLength(shaderHandle); }

    inline void GetShaderInfoLog(uint shaderHandle, int bufSize, char* infoLog)
    {
      g_rhi->GetShaderInfoLog(shaderHandle, bufSize, infoLog);
    }

    // Program

    inline uint CreateProgram() { return g_rhi->CreateProgram(); }

    inline void DeleteProgram(uint programHandle) { g_rhi->DeleteProgram(programHandle); }

    inline void AttachShader(uint programHandle, uint shaderHandle)
    {
      g_rhi->AttachShader(programHandle, shaderHandle);
    }

    inline void LinkProgram(uint programHandle) { g_rhi->LinkProgram(programHandle); }

    inline bool GetProgramLinkStatus(uint programHandle) { return g_rhi->GetProgramLinkStatus(programHandle); }

    inline int GetProgramInfoLogLength(uint programHandle) { return g_rhi->GetProgramInfoLogLength(programHandle); }

    inline void GetProgramInfoLog(uint programHandle, int bufSize, char* infoLog)
    {
      g_rhi->GetProgramInfoLog(programHandle, bufSize, infoLog);
    }

    inline void UseProgram(uint programHandle) { g_rhi->UseProgram(programHandle); }

    inline uint GetCurrentProgram() { return g_rhi->GetCurrentProgram(); }

    inline int GetUniformLocation(uint programHandle, const char* name)
    {
      return g_rhi->GetUniformLocation(programHandle, name);
    }

    inline void Uniform1i(int location, int value) { g_rhi->Uniform1i(location, value); }

    inline uint GetUniformBlockIndex(uint programHandle, const char* name)
    {
      return g_rhi->GetUniformBlockIndex(programHandle, name);
    }

    inline void UniformBlockBinding(uint programHandle, uint blockIndex, uint bindingPoint)
    {
      g_rhi->UniformBlockBinding(programHandle, blockIndex, bindingPoint);
    }

    inline void BindUniformBufferBase(uint bindingPoint, uint bufferId)
    {
      g_rhi->BindUniformBufferBase(bindingPoint, bufferId);
    }

    // Texture

    inline void CreateTextures(int count, uint* textureIds) { g_rhi->CreateTextures(count, textureIds); }

    inline void DestroyTextures(int count, const uint* textureIds)
    {
      g_rhi->DestroyTextures(count, textureIds);
    }

    inline void DestroyTexture(uint textureId) { g_rhi->DestroyTextures(1, &textureId); }

    inline void SetTextureBinding(uint target, uint textureId, uint textureSlot = 0)
    {
      g_rhi->SetTextureBinding(target, textureId, textureSlot);
    }

    inline void SetTextureData2D(uint target,
                                 int level,
                                 int internalFormat,
                                 int width,
                                 int height,
                                 uint format,
                                 uint type,
                                 const void* data)
    {
      g_rhi->SetTextureData2D(target, level, internalFormat, width, height, format, type, data);
    }

    inline void SetCubeTextureFaceData(int faceIndex,
                                       int level,
                                       int internalFormat,
                                       int width,
                                       int height,
                                       uint format,
                                       uint type,
                                       const void* data)
    {
      g_rhi->SetCubeTextureFaceData(faceIndex, level, internalFormat, width, height, format, type, data);
    }

    inline void UpdateTextureData2D(uint target,
                                    int level,
                                    int xoffset,
                                    int yoffset,
                                    int width,
                                    int height,
                                    uint format,
                                    uint type,
                                    const void* data)
    {
      g_rhi->UpdateTextureData2D(target, level, xoffset, yoffset, width, height, format, type, data);
    }

    inline void SetTextureData3D(uint target,
                                 int level,
                                 int internalFormat,
                                 int width,
                                 int height,
                                 int depth,
                                 uint format,
                                 uint type,
                                 const void* data)
    {
      g_rhi->SetTextureData3D(target, level, internalFormat, width, height, depth, format, type, data);
    }

    inline void SetTextureParamInt(uint target, uint paramName, int value)
    {
      g_rhi->SetTextureParamInt(target, paramName, value);
    }

    inline void SetTextureParamFloat(uint target, uint paramName, float value)
    {
      g_rhi->SetTextureParamFloat(target, paramName, value);
    }

    inline void GenerateTextureMipmaps(uint target) { g_rhi->GenerateTextureMipmaps(target); }

    inline bool IsAnisotropicFilteringSupported() { return g_rhi->IsAnisotropicFilteringSupported(); }

    inline float GetMaxAnisotropyLevel() { return g_rhi->GetMaxAnisotropyLevel(); }

    // Renderbuffer

    inline void CreateRenderbuffers(int count, uint* renderbufferIds)
    {
      g_rhi->CreateRenderbuffers(count, renderbufferIds);
    }

    inline void SetRenderbufferBinding(uint renderbufferId) { g_rhi->SetRenderbufferBinding(renderbufferId); }

    inline void DestroyRenderbuffers(int count, const uint* renderbufferIds)
    {
      g_rhi->DestroyRenderbuffers(count, renderbufferIds);
    }

    inline void DestroyRenderbuffer(uint renderbufferId) { g_rhi->DestroyRenderbuffers(1, &renderbufferId); }

    inline void AllocateRenderbufferStorage(uint internalformat, int width, int height)
    {
      g_rhi->AllocateRenderbufferStorage(internalformat, width, height);
    }

    inline void AllocateRenderbufferStorageMSAA(int samples, uint internalformat, int width, int height)
    {
      g_rhi->AllocateRenderbufferStorageMSAA(samples, internalformat, width, height);
    }

    inline bool IsMSAARenderbufferSupported()
    {
      return g_rhi->IsMSAARenderbufferSupported();
    }

  } // namespace TKRHI

} // namespace ToolKit
