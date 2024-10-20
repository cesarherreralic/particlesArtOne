#pragma once

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>


class Particle
{
public:
    glm::vec4 position;
    glm::vec4 velocity;
    glm::vec4 extra; // for radius and mass

    Particle()
    {
        this->position = glm::vec4(0.f);
        this->velocity = glm::vec4(0.f);
        this->extra = glm::vec4(1.f);
    }

    Particle(glm::vec4 position, glm::vec4 velocity, glm::vec4 extra)
    {
        this->position = position;
        this->velocity = velocity;
        this->extra = extra;
    }

    ~Particle() {}

    void setPosition(glm::vec4 position)
    {
        this->position = position;
    }

    void setVelocity(glm::vec4 velocity)
    {
        this->velocity = velocity;
    }

    void setExtra(glm::vec4 extra)
    {
        this->extra = extra;
    }

    void setRadius(GLfloat radius)
    {
        this->extra = glm::vec4(radius, this->extra[1], this->extra[2], this->extra[3]);
    }

    void setMass(GLfloat mass)
    {
        this->extra = glm::vec4(this->extra[0], mass, this->extra[2], this->extra[3]);
    }

    void setDensity(GLfloat density)
    {
        this->extra = glm::vec4(this->extra[0], this->extra[1], this->extra[2], density);
    }

    void setProperty(GLfloat prop)
    {
        this->extra = glm::vec4(this->extra[0], this->extra[0], prop, this->extra[3]);
    }
};
