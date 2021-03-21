#include "../headers/transformations.hpp"

void Camera::UpdatePos(int _movType)
{
    switch(_movType)
    {
        case CAM_FORWARD: camPos += -0.1f * dirVec; LookAt(); break;
        case CAM_BACKWARD: camPos +=  0.1f * dirVec; LookAt(); break; 
        case CAM_LEFT: camPos +=  0.1f * glm::vec4(glm::normalize(glm::cross(glm::vec3(dirVec), worldUp)), 0.0f); LookAt(); break;
        case CAM_RIGHT: camPos += -0.1f * glm::vec4(glm::normalize(glm::cross(glm::vec3(dirVec), worldUp)), 0.0f); LookAt(); break;
    }
}

void Camera::UpdateDirVec(float _anglePitch, float _angleHead)
{
    pitch += _anglePitch;
    head += _angleHead;

    if(pitch > 2*M_PI || pitch < -2*M_PI)
        pitch = 0.0f;
    if(head > 2*M_PI || head < -2*M_PI)
        head = 0.0f;

    dirVec.x = -sinf32(head)*cosf32(pitch);
    dirVec.y = sinf32(pitch);
    dirVec.z = cosf32(head)*cosf32(pitch);

    dirVec = glm::normalize(dirVec);

    LookAt();
}

glm::mat4 Camera::LookAt()
{
    glm::vec3 dirVecCast = glm::normalize((glm::vec3((camPos+dirVec)) - glm::vec3(camPos)));
    glm::vec3 rightDir = glm::normalize(glm::cross(worldUp, dirVecCast));
    glm::vec3 upDir = glm::cross(dirVecCast, rightDir);

    glm::mat4 lookAtMat = 
    {
        rightDir.x,upDir.x,dirVecCast.x ,  0,
        rightDir.y,upDir.y,dirVecCast.y ,  0,
        rightDir.z,upDir.z,dirVecCast.z ,  0,

        -glm::dot(glm::vec3(camPos), rightDir),
        -glm::dot(glm::vec3(camPos), upDir), 
        -glm::dot(glm::vec3(camPos), dirVecCast),
        1
    };
  
    return actLookAt = lookAtMat;
}

ModelTFMS::ModelTFMS(glm::vec3 _translation, 
             std::vector<float> _rotAngles, 
             std::vector<glm::vec3> _rotAxises,
             glm::vec3 _scale)
{
    UpdateModel(_translation, _rotAngles, _rotAxises, _scale);
}

void ModelTFMS::UpdateModel(glm::vec3 _translation, 
                        std::vector<float> _rotAngles, 
                        std::vector<glm::vec3> _rotAxises,
                        glm::vec3 _scale)
{
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), _scale);
    
    glm::mat4 rotMat = glm::mat4(1.0f);
    for(int i=0; i<_rotAngles.size() && i<3; i++)
        rotMat *= glm::rotate(glm::mat4(1.0f), _rotAngles[i], _rotAxises[i]);
    
    glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), _translation);

    actualModelMat *= translateMat * rotMat * scaleMat;
    actualModelWorldCoords += _translation;
}