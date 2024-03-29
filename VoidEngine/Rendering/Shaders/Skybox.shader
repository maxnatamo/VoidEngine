#ifndef VOID_SHADER_SKYBOX_H__
#define VOID_SHADER_SKYBOX_H__

#include <VoidEngine/Rendering/Shaders/_Shader.hpp>

std::string k_ShaderSkybox_vert = R"(#version 450 core

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec4 i_Color;
layout(location = 2) in vec3 i_Normal;
layout(location = 3) in vec2 i_TexCoords;

layout(location = 0) out vec3 v_TexCoords;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main() {
    gl_Position = vec4(u_Projection * u_View * vec4(i_Position, 1.0)).xyww;
    v_TexCoords = i_Position;
}
)";

std::string k_ShaderSkybox_frag = R"(#version 450 core

layout(location = 0) in vec3 v_TexCoords;

layout(location = 0) out vec4 o_Color;

uniform samplerCube u_Skybox;

void main() {
    o_Color = vec4(texture(u_Skybox, v_TexCoords).rgb, 1.0);
}
)";

ShaderCreationInfo k_ShaderSkybox = {
    "Skybox", {
        { ShaderStage::StageVertex,     k_ShaderSkybox_vert },
        { ShaderStage::StageFragment,   k_ShaderSkybox_frag },
    }, {
        sizeof(Vertex), {
            { ShaderLayout::Type::Float, ShaderLayout::Dimension::L3D, false, offsetof(Vertex, position)  },
            { ShaderLayout::Type::Float, ShaderLayout::Dimension::L4D, false, offsetof(Vertex, color)     },
            { ShaderLayout::Type::Float, ShaderLayout::Dimension::L3D, false, offsetof(Vertex, normal)    },
            { ShaderLayout::Type::Float, ShaderLayout::Dimension::L2D, false, offsetof(Vertex, texCoords) },
        }
    }
};

#endif /* VOID_SHADER_FRAMEBUFFER_H__ */
