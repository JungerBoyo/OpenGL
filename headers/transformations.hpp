#ifndef TRANSFORMATIONS_HPP
#define TRANSFORMATIONS_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>

class TransformManager
{
    public:
        TransformManager();
        glm::mat4 GetModelTransform(glm::vec3 translation, 
                                    std::vector<float> rotAngles, 
                                    std::vector<glm::vec3> rotAxises, 
                                    glm::vec3 _scale = {1.0f, 1.0f, 1.0f});
        
        
        
        glm::mat4 GetViewTransform(glm::vec3 translation, 
                                   std::vector<float> rotAngles, 
                                   std::vector<glm::vec3> rotAxises);

};

class Camera : public TransformManager
{
    public:
        Camera(glm::vec3 translation, 
               std::vector<float> rotAngles, 
               std::vector<glm::vec3> rotAxises);

        void UpdateCamera(glm::vec3 translation, 
                          std::vector<float> rotAngles = std::vector<float>(0), 
                          std::vector<glm::vec3> rotAxises = std::vector<glm::vec3>(0));

        inline glm::mat4 GetActualCameraViewMat() const { return actualCameraViewMat; } 
        inline glm::vec3 GetActualCameraWorldCoords() const { return actualCameraWorldCoords; }

    private:
        glm::mat4 actualCameraViewMat = glm::mat4(1.0f);
        glm::vec3 actualCameraWorldCoords;

};

class Model : public TransformManager
{
    public:
      public:
        Model(glm::vec3 translation, 
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
        glm::vec3 actualModelWorldCoords;
};

#endif