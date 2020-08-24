#ifndef VOID_ECS_ENTITIES_CUBE_H__
#define VOID_ECS_ENTITIES_CUBE_H__

#include <vector>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/ECS/Entity.hpp>
#include <VoidEngine/Math/Shapes.hpp>

namespace VOID_NS {
    class Cube : public Entity {
    private:
    protected:
    public:
        Cube() : Entity() {
            this->renderable = true;

            /* Front */
            vertices.push_back(Vertex(glm::vec3(0.0f, 0.0f, 0.0f), Color::Red()));    // 0
            vertices.push_back(Vertex(glm::vec3(1.0f, 0.0f, 0.0f), Color::Green()));  // 1
            vertices.push_back(Vertex(glm::vec3(1.0f, 1.0f, 0.0f), Color::Blue()));   // 2
            vertices.push_back(Vertex(glm::vec3(0.0f, 1.0f, 0.0f), Color::Yellow())); // 3

            /* Back */
            vertices.push_back(Vertex(glm::vec3(0.0f, 0.0f, 1.0f), Color::Black()));   // 4
            vertices.push_back(Vertex(glm::vec3(1.0f, 0.0f, 1.0f), Color::Cyan()));    // 5
            vertices.push_back(Vertex(glm::vec3(1.0f, 1.0f, 1.0f), Color::Magenta())); // 6
            vertices.push_back(Vertex(glm::vec3(0.0f, 1.0f, 1.0f), Color::White()));   // 7

            indices.insert(indices.begin(), {
                /* Front */
                0, 1, 2, 2, 3, 0,

                /* Back */
                4, 5, 6, 6, 7, 4,

                /* Left */
                1, 2, 5, 5, 6, 2,

                /* Right */
                0, 3, 4, 4, 7, 3,

                /* Bottom */
                0, 1, 4, 4, 5, 1,

                /* Top */
                2, 3, 6, 6, 7, 3
            });
        }
    };
};

#endif /* VOID_ECS_ENTITIES_CUBE_H__ */