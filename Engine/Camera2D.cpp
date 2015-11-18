#include "Camera2D.h"

#include "Input.h"

#include <SDL\SDL.h>
#include <iostream>

Camera2D::Camera2D()
{
	viewMatrix_ = glm::lookAt(position_, position_ + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

Camera2D::~Camera2D()
{
}

void Camera2D::SetPosition(glm::vec3 pos)
{
	position_ = pos;
	Update();
}

void Camera2D::Update()
{
	viewMatrix_ = glm::lookAt(position_, position_ + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}