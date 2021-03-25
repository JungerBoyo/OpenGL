#ifndef TRANSFORMATIONS_HPP
#define TRANSFORMATIONS_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>

enum {CAM_FORWARD, CAM_BACKWARD, CAM_RIGHT, CAM_LEFT};

class Camera 
{
    public:
        inline Camera() {};

        glm::mat4 LookAt();
        void UpdateDirVec(float anglePitch, float angleHead);
        void UpdatePos(int movType);

        inline glm::vec4 GetCamPosition() const { return camPos; }
        inline glm::mat4 GetActLookAtMat() const {return actLookAt; }

    private:     
        glm::mat4 actLookAt;
        glm::vec4 camPos = {0.0f, 0.0f, 0.0f, 1.0f};

        glm::vec4 dirVec = {0.0f, 0.0f, 1.0f, 0.0f};
        const glm::vec3 worldUp = {0.0f, 1.0f, 0.0f};

        float pitch = 0.0f;
        float head = 0.0f;

};

class ModelTFMS
{
    public:
      public:
        ModelTFMS(glm::vec3 translation, 
               std::vector<float> rotAngles, 
               std::vector<glm::vec3> rotAxises,
               glm::vec3 _scale = {1.0f, 1.0f, 1.0f});

        void UpdateModel(glm::vec3 translation, 
                         std::vector<float> rotAngles = std::vector<float>(0), 
                         std::vector<glm::vec3> rotAxises = std::vector<glm::vec3>(0),
                         glm::vec3 scale = {1.0f, 1.0f, 1.0f});

        inline glm::mat4 GetActualModelMat() const { return actualModelMat; } 
        inline glm::vec3 GetActualModelWorldCoords() const { return actualModelWorldCoords; }

    private:
        glm::mat4 actualModelMat = glm::mat4(1.0f);
        glm::vec3 actualModelWorldCoords = glm::vec3(0.0f);
};

#endif