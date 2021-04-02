#ifndef TRANSFORMATIONS_HPP
#define TRANSFORMATIONS_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <functional>
#include <memory>
#include <vector>

class ModelMatrices;
class Camera;
class ModelTFMS;

enum {CAM_FORWARD, CAM_BACKWARD, CAM_RIGHT, CAM_LEFT};

class Camera 
{
    public:
        inline Camera() {};

        glm::mat4 LookAt();
        void UpdateDirVec(float anglePitch, float angleHead);
        void UpdatePos(int movType);

        inline glm::vec4 GetCamPosition() const { return camPos; }
        inline glm::mat4 GetActLookAtMat() const { return actLookAt; }

        inline float* CamMatData() { return &actLookAt[0][0]; }
        inline float* CamPosData() { return &camPos[0]; }

    private:     
        glm::mat4 actLookAt;
        glm::vec4 camPos = {0.0f, 0.0f, 0.0f, 1.0f};

        glm::vec4 dirVec = {0.0f, 0.0f, 1.0f, 0.0f};
        const glm::vec3 worldUp = {0.0f, 1.0f, 0.0f};

        float pitch = 0.0f;
        float head = 0.0f;

};

class ModelMatrices
{
    typedef float(*scaleOscillationFunction)(float);

    public:
        ModelMatrices(int count);

        void AddAngle(float rotRate, glm::vec3 axisisRot, unsigned int matIdx);
        void AddAngles(std::vector<float> _rotRates, std::vector<glm::vec3> _axisisRots, unsigned int matIdx);
        void ReplaceAngle(float rotRate, glm::vec3 axisisRot, unsigned int matIdx, unsigned int matDataIdx);

        void AddTranslation(float translationRate, glm::vec3 translationDir, unsigned int matIdx);
        void AddTranslations(std::vector<float> translationRates, std::vector<glm::vec3> translationDirs,  unsigned int matIdx);
        void ReplaceTranslation(float rotRate, glm::vec3 axisisRot, unsigned int matIdx, unsigned int matDataIdx);

        void UpdateAll();
        void UpdateOne(unsigned int matIdx);

        void ScaleOne(glm::vec3 scale, unsigned int matIdx);
        void ScaleAll(glm::vec3 scale);

        inline float* data()
        {
            return glm::value_ptr(transformationMatrices.front());
        }

    private:
        void UpdateModel(unsigned int ID);

        struct OneMatrixData
        {
            OneMatrixData()
            {
                angleRotRates = {};
                axisRots = {};
                translateRates = {};
                translateDirs = {};
            }

            std::vector<float> angleRotRates;
            std::vector<glm::vec3> axisRots;

            std::vector<float> translateRates;
            std::vector<glm::vec3> translateDirs;
        };

        std::vector<OneMatrixData> transformData;
        std::vector<glm::mat4> transformationMatrices;
};

#endif