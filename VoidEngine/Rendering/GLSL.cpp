#include <VoidEngine/Rendering/Shader.hpp>

namespace VOID_NS {
    const std::string Shader::DefaultGLSLInclude() {
        return R"(
            /**
             *  In/out attributes
             */

            layout(location = 0) in vec3 i_Position;
            layout(location = 1) in vec3 i_Normal;
            layout(location = 2) in vec2 i_TexCoords;

            layout(location = 0) out vec3 o_Position;
            layout(location = 1) out vec3 o_Normal;
            layout(location = 2) out vec2 o_TexCoords;

            /**
             *  Generic struct definitions
             */

            struct PointLight {
                vec4 Color;
                vec3 Position;
                float Intensity;
            };

            /**
             *  Uniform block definitions
             */

            struct vd_ub_Material {
                vec4  Albedo;
                float Metallic;
                float Roughness;
                float Occlusion;
            };

            struct vd_ub_MVP {
                mat4 Model;
                mat4 View;
                mat4 Projection;
            };

            struct vd_ub_Light {
                float      Gamma;
                vec3       CameraPosition;
                uint       LightCount;
                PointLight LightingData[32];
            };


            /**
             *  Constants
             */

            const float PI = 3.14159265359;

            /**
             *  Common functions
             */

            vec3 Fresnel(float theta, vec3 F) {
                return F + (1.0 - F) * pow(1.0 - theta, 5.0);
            }

            vec4 Fresnel(float theta, vec4 F) {
                return F + (1.0 - F) * pow(1.0 - theta, 5.0);
            }

            /**
             *  Uniforms.
             */

            uniform vd_ub_Material ub_Material;
            uniform vd_ub_MVP      ub_MVP;
            uniform vd_ub_Light    ub_Light;
        )";
    }

    const std::map<ShaderStage, std::string> Shader::DefaultStageInclude() {
        std::map<ShaderStage, std::string> maps = {
            { ShaderStage::Vertex,          R"()" },
            { ShaderStage::Fragment,        R"(
                out vec4 o_Color;
            )" },
            { ShaderStage::Compute,         R"()" },
            { ShaderStage::Geometry,        R"()" },
            { ShaderStage::TessControl,     R"()" },
            { ShaderStage::TessEvaluation,  R"()" },
        };
        return maps;
    }

    const ShaderLayout Shader::DefaultShaderLayout() {
        return ShaderLayout(sizeof(Vertex), {
                { ShaderLayout::Type::Float, ShaderLayout::Dimension::L3D, false, offsetof(Vertex, position)  },
                { ShaderLayout::Type::Float, ShaderLayout::Dimension::L3D, false, offsetof(Vertex, normal)    },
                { ShaderLayout::Type::Float, ShaderLayout::Dimension::L2D, false, offsetof(Vertex, texCoords) }
            }
        );
    }
};