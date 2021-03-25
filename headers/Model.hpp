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

class Model : ModelData
{
    using ModelData::ModelData;

    public: 
        inline GLuint* GetIndices() { return &indices[0]; };

        void SetModel(const std::string& vShaderPath, const std::string& fShaderPath, const std::string& gShaderPath = "");

    private:
        ModelTFMS* modelTFMS;
        VBO* vertexBuffer;
        IBO* indexBuffer;
        GLuint program;
        std::map<const std::string, int> uniforms;
};


#endif