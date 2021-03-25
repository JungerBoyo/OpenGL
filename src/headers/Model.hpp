#ifndef MODEL_HPP
#define MODEL_HPP

#include "Buffers.hpp"
#include "transformations.hpp"

class ModelData
{
    protected:
        ModelData(const std::string& dataPath = "");
        void ParseData(const std::string& dataPath);

    protected:
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> colors;
        std::vector<GLuint> indices;
};

#endif