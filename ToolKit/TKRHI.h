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

  } // namespace TKRHI

} // namespace ToolKit
