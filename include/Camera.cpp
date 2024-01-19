#include "Camera.hpp"

Camera::Camera() {}
Camera::~Camera() {}
void Camera::Move(int dir, float deltaTime)
{
    switch (dir)
    {
    case CAMERA_FORWARD:
        cameraPos += cameraSpeed * deltaTime * cameraFront;
        break;
    case CAMERA_BACKWARD:
        cameraPos -= cameraSpeed * deltaTime * cameraFront;
        break;
    case CAMERA_LEFT:
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
        break;
    case CAMERA_RIGHT:
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
        break;
    }
}
void Camera::Look(int dir, float deltaTime)
{
    switch (dir)
    {
    case CAMERA_LOOK_UP:
    {
        pitch += 1 * lookSensitivity * deltaTime;
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
        break;
    }
    case CAMERA_LOOK_DOWN:
    {
        pitch -= 1 * lookSensitivity * deltaTime;
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
        break;
    }
    case CAMERA_LOOK_LEFT:
    {
        yaw -= 1 * lookSensitivity * deltaTime;
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
        break;
    }
    case CAMERA_LOOK_RIGHT:
    {
        yaw += 1 * lookSensitivity * deltaTime;
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
        break;
    }
    }
}
/// @brief returns view matrix as currently configured by camera parameters cameraPos, cameraFront and cameraUp
/// @return glm::mat4 view matrix
glm::mat4 Camera::GetViewMatrix()
{
    glm::mat4 viewMatrix;
    viewMatrix = glm::lookAt(cameraPos,               // cameraPos(position)
                             cameraPos + cameraFront, // cameraPos + cameraFront(direction)
                             cameraUp);               // cameraUp(up vector)
    return viewMatrix;
}