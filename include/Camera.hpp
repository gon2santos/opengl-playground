#ifndef CAMERA_H
#define CAMERA_H

#define CAMERA_FORWARD 0
#define CAMERA_BACKWARD 1
#define CAMERA_LEFT 2
#define CAMERA_RIGHT 3
#define CAMERA_LOOK_UP 4
#define CAMERA_LOOK_DOWN 5
#define CAMERA_LOOK_LEFT 6
#define CAMERA_LOOK_RIGHT 7

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera
{
public:
    glm::vec3 cameraPos = glm::vec3(-0.584592f, 1.51415f, 3.3521f);
    glm::vec3 cameraFront = glm::vec3(0.439877f, -0.372988f, -0.816938f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    float cameraZoom = 45.0f;
    const float cameraSpeed = .02f;
    float pitch = -21.9f;
    float yaw = -61.7f;
    float lookSensitivity = 0.1f;
    Camera();
    ~Camera();
    void Move(int dir, float deltaTime);
    void Look(int dir, float deltaTime);
    glm::mat4 GetViewMatrix();

private:
};

#endif