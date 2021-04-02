#include "headers/transformations.hpp"
#include <iostream>
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

ModelMatrices::ModelMatrices(int _count)
{
    transformationMatrices.reserve(_count);
    transformData.reserve(_count);
    for(unsigned int i=0; i<_count; i++)
    {
        transformationMatrices.emplace_back(glm::mat4(1.0f));
        transformData.emplace_back(OneMatrixData());
    }
}

void ModelMatrices::UpdateModel(unsigned int _ID)
{
    for(unsigned int i=0; i < transformData[_ID].angleRotRates.size(); i++)
        transformationMatrices[_ID] = glm::rotate(transformationMatrices[_ID], transformData[_ID].angleRotRates[i] * M_PIf32, transformData[_ID].axisRots[i]);

    for(unsigned int i=0; i < transformData[_ID].translateRates.size(); i++)
        transformationMatrices[_ID] = glm::translate(transformationMatrices[_ID], transformData[_ID].translateRates[i] * transformData[_ID].translateDirs[i]);
}
void ModelMatrices::AddAngle(float _rotRate, glm::vec3 _axisisRot, unsigned int _matIdx)
{
    transformData[_matIdx].axisRots.push_back(glm::normalize(_axisisRot));
    transformData[_matIdx].angleRotRates.push_back(_rotRate);
}
void ModelMatrices::AddAngles(std::vector<float> _rotRates, std::vector<glm::vec3> _axisisRots, unsigned int _matIdx)
{
    for(unsigned int i=0; i<_axisisRots.size(); i++)
        _axisisRots[i] = glm::normalize(_axisisRots[i]);

    transformData[_matIdx].axisRots.insert(transformData[_matIdx].axisRots.end(), _axisisRots.begin(), _axisisRots.end());
    transformData[_matIdx].angleRotRates.insert(transformData[_matIdx].angleRotRates.end(), _rotRates.begin(), _rotRates.end());
}

void ModelMatrices::AddTranslation(float _translationRate, glm::vec3 _translationDir, unsigned int _matIdx)
{
    transformData[_matIdx].translateDirs.push_back(glm::normalize(_translationDir));
    transformData[_matIdx].translateRates.push_back(_translationRate);
}
void ModelMatrices::AddTranslations(std::vector<float> _translationRates, std::vector<glm::vec3> _translationDirs,  unsigned int _matIdx)
{
    for(unsigned int i=0; i<_translationDirs.size(); i++)
        _translationDirs[i] = glm::normalize(_translationDirs[i]);

    transformData[_matIdx].translateDirs.insert(transformData[_matIdx].translateDirs.end(), _translationDirs.begin(), _translationDirs.end());
    transformData[_matIdx].translateRates.insert(transformData[_matIdx].translateRates.end(), _translationRates.begin(), _translationRates.end());
}

void ModelMatrices::ReplaceAngle(float _rotRate, glm::vec3 _axisisRot, unsigned int _matIdx, unsigned int _matDataIdx)
{
    transformData[_matIdx].axisRots[_matDataIdx] = glm::normalize(_axisisRot);
    transformData[_matIdx].angleRotRates[_matDataIdx] = _rotRate;
}

void ModelMatrices::ReplaceTranslation(float rotRate, glm::vec3 axisisRot, unsigned int matIdx, unsigned int matDataIdx)
{
    transformData[matIdx].translateDirs[matDataIdx] = glm::normalize(axisisRot);
    transformData[matIdx].translateRates[matDataIdx] = rotRate;
}

void ModelMatrices::ScaleOne(glm::vec3 _scale, unsigned int _matIdx)
{
    transformationMatrices[_matIdx] = glm::scale(transformationMatrices[_matIdx], _scale);
}

void ModelMatrices::ScaleAll(glm::vec3 _scale)
{
    for(int i=0; i<transformationMatrices.size(); i++)
        transformationMatrices[i] = glm::scale(transformationMatrices[i], _scale);
}

void ModelMatrices::UpdateOne(unsigned int _matIdx)
{
    this->UpdateModel(_matIdx);
}

void ModelMatrices::UpdateAll()
{
    for(unsigned int i=0; i<transformationMatrices.size(); i++)
        this->UpdateModel(i);
}