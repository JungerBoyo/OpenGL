#include "headers/Model.hpp"

ModelData::ModelData(const std::string& _dataPath)
{
    //ParseData(_dataPath);

    //Temporary, for debugging purposes
    vertices =
    {
        -1.0f, -1.0f, 1.0f, 1.0f, // Triangle 1
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 1.0f, 1.0f, // Triangle 2
        -1.0f, -1.0f,-1.0f, 1.0f,
         1.0f,  1.0f,-1.0f, 1.0f,
        -1.0f,  1.0f,-1.0f, 1.0f,
         1.0f, -1.0f,-1.0f, 1.0f
    };

    colors =
    {
        0.1f, 0.1f, 0.1f, 1.0f,
        0.2f, 0.2f, 0.2f, 1.0f,
        0.3f, 0.3f, 0.3f, 1.0f,
        0.3f, 0.4f, 0.4f, 1.0f,
        0.1f, 0.8f, 0.5f, 1.0f,
        0.9f, 0.8f, 0.6f, 1.0f,
        0.4f, 0.4f, 0.7f, 1.0f,
        0.0f, 0.8f, 0.8f, 1.0f
    };

    indices = 
    {
        0, 1, 2,
        0, 3, 1, // front
        3, 5, 1,
        3, 7, 5, // right
        2, 5, 6,
        2, 1, 5, // top
        4, 2, 6,
        4, 0, 2, // left
        4, 3, 0,
        4, 7, 3, // bottom
        7, 6, 5,
        7, 4, 6
    };

}

void ModelData::ParseData(const std::string& _dataPath)
{
    // TODO
}
