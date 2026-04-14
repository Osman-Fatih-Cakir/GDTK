/*
 * Copyright (c) 2019-2025 OtSoftware
 * This code is licensed under the GNU Lesser General Public License v3.0 (LGPL-3.0).
 * For more information, including options for a more permissive commercial license,
 * please visit [otyazilim.com] or contact us at [info@otyazilim.com].
 */

#include "GpuProgram.h"

#include "Renderer.h"
#include "Shader.h"
#include "TKRHI.h"

#include "DebugNew.h"

namespace ToolKit
{

  // GpuProgram
  //////////////////////////////////////////

  GpuProgram::GpuProgram() {}

  GpuProgram::GpuProgram(ShaderPtr vertex, ShaderPtr fragment)
  {
    m_shaders.push_back(vertex);
    m_shaders.push_back(fragment);
  }

  GpuProgram::~GpuProgram()
  {
    TKRHI::DeleteProgram(m_handle);
    m_handle = 0;
  }

  int GpuProgram::GetDefaultUniformLocation(Uniform uniform, int index)
  {
    if (index == -1)
    {
      const auto& itr = m_defaultUniformLocation.find(uniform);
      if (itr != m_defaultUniformLocation.end())
      {
        return itr->second;
      }
    }
    else
    {
      // Uniform is an array
      const auto& itr = m_defaultArrayUniformLocations.find(uniform);
      if (itr != m_defaultArrayUniformLocations.end())
      {
        return itr->second;
      }
    }

    return -1;
  }

  int GpuProgram::GetCustomUniformLocation(ShaderUniform& shaderUniform)
  {
    if (!shaderUniform.m_thisUniformIsSearchedInGPUProgram)
    {
      shaderUniform.m_thisUniformIsSearchedInGPUProgram = true;

      int loc                                            = TKRHI::GetUniformLocation(m_handle, shaderUniform.m_name.c_str());
      if (loc == -1)
      {
        TK_WRN("Uniform: \"%s\" does not exist in program!", shaderUniform.m_name.c_str());
      }

      shaderUniform.m_locInGPUProgram = loc;
    }

    return shaderUniform.m_locInGPUProgram;
  }

  void GpuProgram::UpdateCustomUniform(const String& uniformName, const UniformValue& val)
  {
    auto paramItr = m_customUniforms.find(uniformName);
    if (paramItr == m_customUniforms.end())
    {
      m_customUniforms[uniformName] = ShaderUniform(uniformName, val);
    }
    else
    {
      paramItr->second = val;
    }
  }

  void GpuProgram::UpdateCustomUniform(const ShaderUniform& uniform)
  {
    auto paramItr = m_customUniforms.find(uniform.m_name);
    if (paramItr == m_customUniforms.end())
    {
      m_customUniforms[uniform.m_name] = uniform;
    }
    else
    {
      paramItr->second = uniform.m_value;
    }
  }

  // GpuProgramManager
  //////////////////////////////////////////

  GpuProgramManager::~GpuProgramManager() { FlushPrograms(); }

  void GpuProgramManager::LinkProgram(uint program, const ShaderPtr vertexShader, const ShaderPtr fragmentShader)
  {
    TKRHI::AttachShader(program, vertexShader->m_shaderHandle);
    TKRHI::AttachShader(program, fragmentShader->m_shaderHandle);

    TKRHI::LinkProgram(program);

    if (!TKRHI::GetProgramLinkStatus(program))
    {
      int infoLen = TKRHI::GetProgramInfoLogLength(program);
      if (infoLen > 1)
      {
        char* log = new char[infoLen];
        TKRHI::GetProgramInfoLog(program, infoLen, log);
        TK_ERR("Linking failed. \nVertex shader: %s\nFragment shader: %s\n%s",
               vertexShader->GetFile().c_str(),
               fragmentShader->GetFile().c_str(),
               log);

        assert(false);
        SafeDelArray(log);
      }

      TKRHI::DeleteProgram(program);
    }
  }

  const GpuProgramPtr& GpuProgramManager::CreateProgram(const ShaderPtr vertexShader, const ShaderPtr fragmentShader)
  {
    assert(vertexShader);
    assert(fragmentShader);
    assert(m_globalGpuBuffers != nullptr);

    vertexShader->Init();
    fragmentShader->Init();

    const auto& progIter = m_programs.find({vertexShader->m_shaderHandle, fragmentShader->m_shaderHandle});
    if (progIter == m_programs.end())
    {
      GpuProgramPtr program = MakeNewPtr<GpuProgram>(vertexShader, fragmentShader);
      program->m_handle     = TKRHI::CreateProgram();

      LinkProgram(program->m_handle, vertexShader, fragmentShader);

      uint currentProgram = TKRHI::GetCurrentProgram();

      TKRHI::UseProgram(program->m_handle);
      for (ubyte slotIndx = 0; slotIndx < RHIConstants::TextureSlotCount; slotIndx++)
      {
        int loc = TKRHI::GetUniformLocation(program->m_handle, ("s_texture" + std::to_string(slotIndx)).c_str());
        if (loc != -1)
        {
          TKRHI::Uniform1i(loc, slotIndx);
        }
      }

      uint blockIdx = TKRHI::GetUniformBlockIndex(program->m_handle, "CameraData");
      if (blockIdx != TKRHI::InvalidIndex)
      {
        TKRHI::UniformBlockBinding(program->m_handle, blockIdx, CameraGpuBuffer::Binding());
        TKRHI::BindUniformBufferBase(CameraGpuBuffer::Binding(), m_globalGpuBuffers->cameraBufferId);
      }

      blockIdx = TKRHI::GetUniformBlockIndex(program->m_handle, "GraphicConstatsData");
      if (blockIdx != TKRHI::InvalidIndex)
      {
        TKRHI::UniformBlockBinding(program->m_handle, blockIdx, GraphicConstantsGpuBuffer::Binding());
        TKRHI::BindUniformBufferBase(GraphicConstantsGpuBuffer::Binding(),
                                     m_globalGpuBuffers->graphicConstantBufferId);
      }

      blockIdx = TKRHI::GetUniformBlockIndex(program->m_handle, "DirectionalLightBuffer");
      if (blockIdx != TKRHI::InvalidIndex)
      {
        TKRHI::UniformBlockBinding(program->m_handle, blockIdx, DirectionalLightBuffer::BindingSlotForLight);
        TKRHI::BindUniformBufferBase(DirectionalLightBuffer::BindingSlotForLight,
                                     m_globalGpuBuffers->directionalLightBufferId);
      }

      blockIdx = TKRHI::GetUniformBlockIndex(program->m_handle, "DirectionalLightPVMBuffer");
      if (blockIdx != TKRHI::InvalidIndex)
      {
        TKRHI::UniformBlockBinding(program->m_handle, blockIdx, DirectionalLightBuffer::BindingSlotForPVM);
        TKRHI::BindUniformBufferBase(DirectionalLightBuffer::BindingSlotForPVM,
                                     m_globalGpuBuffers->directionalLightPVMBufferId);
      }

      blockIdx = TKRHI::GetUniformBlockIndex(program->m_handle, "PointLightCache");
      if (blockIdx != TKRHI::InvalidIndex)
      {
        TKRHI::UniformBlockBinding(program->m_handle, blockIdx, PointLightCache::BindingSlot);
        TKRHI::BindUniformBufferBase(PointLightCache::BindingSlot, m_globalGpuBuffers->pointLightBufferId);
      }

      blockIdx = TKRHI::GetUniformBlockIndex(program->m_handle, "SpotLightCache");
      if (blockIdx != TKRHI::InvalidIndex)
      {
        TKRHI::UniformBlockBinding(program->m_handle, blockIdx, SpotLightCache::BindingSlot);
        TKRHI::BindUniformBufferBase(SpotLightCache::BindingSlot, m_globalGpuBuffers->spotLightBufferId);
      }

      // Register default uniform locations
      for (ShaderPtr shader : program->m_shaders)
      {
        for (const Uniform& uniform : shader->m_uniforms)
        {
          int loc                                    = TKRHI::GetUniformLocation(program->m_handle, GetUniformName(uniform));
          program->m_defaultUniformLocation[uniform] = loc;
        }

        for (Shader::ArrayUniform arrayUniform : shader->m_arrayUniforms)
        {
          String uniformName = GetUniformName(arrayUniform.uniform);
          int loc            = TKRHI::GetUniformLocation(program->m_handle, uniformName.c_str());
          program->m_defaultArrayUniformLocations[arrayUniform.uniform] = loc;
        }
      }

      m_programs[{vertexShader->m_shaderHandle, fragmentShader->m_shaderHandle}] = program;

      TKRHI::UseProgram(currentProgram);

      return m_programs[{vertexShader->m_shaderHandle, fragmentShader->m_shaderHandle}];
    }

    return progIter->second;
  }

  void GpuProgramManager::FlushPrograms() { m_programs.clear(); }

} // namespace ToolKit