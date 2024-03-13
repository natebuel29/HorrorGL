#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

// USED LEARNOPENGL AS REF FOR THIS CLASS

enum CameraMoveDirection
{
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
	UP,
	DOWN
};

class Camera
{
public:
	Camera(glm::vec3 camPos, glm::vec3 worldUp, float pitch, float yaw, float cameraSpeed, float cameraSensitivity);

	void moveCamera(CameraMoveDirection direction, float deltaTime);
	void updateCameraRotation(float xOffset, float yOffset);
	glm::mat4 getViewMatrix();

private:
	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraFront;
	glm::vec3 m_CameraUp;
	glm::vec3 m_CameraRight;
	glm::vec3 m_WorldUp;


	float m_CameraSpeed;
	float m_CameraSensitivity;
	float m_Pitch;
	float m_Yaw;

	void updateCameraVectors();
};

