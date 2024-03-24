#include "Camera.h"

// USED LEARNOPENGL AS REF FOR THIS CLASS

Camera::Camera(glm::vec3 camPos, glm::vec3 worldUp, float pitch, float yaw, float cameraSpeed, float cameraSensitivity)
{
	m_CameraPos = camPos;
	m_WorldUp = worldUp;
	m_Pitch = pitch;
	m_Yaw = yaw;
	m_CameraSpeed = cameraSpeed;
	m_CameraSensitivity = cameraSensitivity;

	updateCameraVectors();
}

void Camera::moveCamera(CameraMoveDirection direction, float deltaTime)
{

	if (direction == RIGHT)
	{
		m_CameraPos += m_CameraRight * deltaTime * m_CameraSpeed;
	}

	if (direction == LEFT)
	{
		m_CameraPos -= m_CameraRight * deltaTime * m_CameraSpeed;

	}

	if (direction == FORWARD)
	{
		m_CameraPos += m_CameraFront * deltaTime * m_CameraSpeed;

	}

	if (direction == BACKWARD)
	{
		m_CameraPos -= m_CameraFront * deltaTime * m_CameraSpeed;
	}
}

void Camera::updateCameraRotation(float xOffset, float yOffset)
{
	xOffset *= m_CameraSensitivity;
	yOffset *= m_CameraSensitivity;

	m_Yaw += xOffset;
	m_Pitch += yOffset;

	if (m_Pitch > 90.0f)
	{
		m_Pitch = 90.0f;
	}
	else if (m_Pitch < -90.0f) {
		m_Pitch = -90.0f;
	}


	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	glm::mat4 view;
	view = glm::lookAt(m_CameraPos,
		m_CameraPos + m_CameraFront,
		m_CameraUp);

	return view;
}

glm::vec3 Camera::getCameraPos()
{
	return m_CameraPos;
}

void Camera::updateCameraVectors()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	direction.y = sin(glm::radians(m_Pitch));
	direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_CameraFront = glm::normalize(direction);

	m_CameraRight = glm::normalize(glm::cross(m_CameraFront, m_WorldUp));
	m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));
}
