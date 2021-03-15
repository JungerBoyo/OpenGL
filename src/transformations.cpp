#include "../headers/transformations.hpp"

TransformManager::TransformManager()
{
    
}

glm::mat4 TransformManager::GetModelTransform(glm::vec3 _translation, 
                                              std::vector<float> _rotAngles, 
                                              std::vector<glm::vec3> _rotAxises, 
                                              glm::vec3 _scale)
{
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), _scale);
    
    glm::mat4 rotMat = glm::mat4(1.0f);
    for(int i=0; i<_rotAngles.size() && i<3; i++)
        rotMat *= glm::rotate(glm::mat4(1.0f), _rotAngles[i], _rotAxises[i]);
    
    glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), _translation);

    return translateMat * rotMat * scaleMat;
}

glm::mat4 TransformManager::GetViewTransform(glm::vec3 _translation, 
                           std::vector<float> _rotAngles, 
                           std::vector<glm::vec3> _rotAxises)
{
    glm::mat4 rotMat = glm::mat4(1.0f);
  
    for(int i=0; i<_rotAngles.size() && i<3; i++)
        rotMat *= glm::rotate(glm::mat4(1.0f), _rotAngles[i], _rotAxises[i]);

    glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), _translation);

    return translateMat * rotMat;    
}


Camera::Camera(glm::vec3 _translation, 
               std::vector<float> _rotAngles, 
               std::vector<glm::vec3> _rotAxises)
{
    actualCameraViewMat *= GetViewTransform(_translation, _rotAngles, _rotAxises);
    actualCameraWorldCoords += _translation;
}

void Camera::UpdateCamera(glm::vec3 _translation, 
                          std::vector<float> _rotAngles, 
                          std::vector<glm::vec3> _rotAxises)
{
    actualCameraViewMat *= GetViewTransform(_translation, _rotAngles, _rotAxises);
    actualCameraWorldCoords += _translation;
}

Model::Model(glm::vec3 _translation, 
             std::vector<float> _rotAngles, 
             std::vector<glm::vec3> _rotAxises,
             glm::vec3 _scale)
{
    actualModelMat = GetModelTransform(_translation, _rotAngles, _rotAxises, _scale);
    actualModelWorldCoords = _translation;
}

void Model::UpdateModel(glm::vec3 _translation, 
                        std::vector<float> _rotAngles, 
                        std::vector<glm::vec3> _rotAxises,
                        glm::vec3 _scale)
{
    actualModelMat = GetModelTransform(_translation, _rotAngles, _rotAxises, _scale);
    actualModelWorldCoords = _translation;
}