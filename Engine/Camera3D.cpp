#include "Camera3D.h"

#include <SDL\SDL.h>

#include "Input.h"

const vec3 UP(0.0f, 1.0f, 0.0f);
const float SENSITIVTY = 0.50f;
const float SPEED = 10.0f;

Camera3D::Camera3D(const vec3& pos, const vec3& forward, const vec3& up) :
	position_(pos), forward_(forward), up_(up) 
{
}

void Camera3D::ProcessInput(float dt)
{
	vec2 centerPosition = vec2((float)Window::GetWidth() / 2.0f, (float)Window::GetHeight() / 2.0f);
	vec2 offset = Input::MousePosition() - centerPosition;

	yaw_   += (offset.x * SENSITIVTY);
	pitch_ += (offset.y * SENSITIVTY);

	direction_ == Direction::NONE;
	if (Input::KeyHeld(SDLK_w))
		direction_ == Direction::FORWARD;
	if (Input::KeyHeld(SDLK_s))
		direction_ == Direction::BACKWARD;
	if (Input::KeyHeld(SDLK_a))
		direction_ == Direction::LEFT;
	if (Input::KeyHeld(SDLK_d))
		direction_ == Direction::RIGHT;
}

void Camera3D::Update(float dt)
{
	GLfloat velocity = SPEED * dt;
	switch (direction_)
	{
		case Direction::NONE:
		{
			break;
		}
		case Direction::FORWARD:
		{
			position_ += forward_ * velocity;
			break;
		}
		case Direction::BACKWARD:
		{
			position_ -= forward_ * velocity;
			break;
		}
		case Direction::LEFT:
		{
			position_ -= right_ * velocity;
			break;
		}
		case Direction::RIGHT:
		{
			position_ += right_ * velocity;
			break;
		}
	}

	glm::vec3 front;
	front.x  = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front.y  = sin(glm::radians(pitch_));
	front.z  = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	forward_ = glm::normalize(front);
	right_   = glm::normalize(glm::cross(forward_, UP));
	up_      = glm::normalize(glm::cross(right_, forward_));

	Input::SetMousePosition(vec2((float)Window::GetWidth() / 2.0f, (float)Window::GetHeight() / 2.0f));
}