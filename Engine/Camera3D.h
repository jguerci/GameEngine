#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Window.h"

using namespace glm;

enum class Direction
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	NONE
};

class Camera3D
{
public:
	Camera3D(const vec3& pos = vec3(0, 0, 0), const vec3& forward = vec3(0, 0, 1), const vec3& up = vec3(0, 1, 0));

	void ProcessInput(float dt);
	void Update(float dt);

	inline vec3& GetPosition() { return position_; }
protected:
private:
	float yaw_ = 0.0;
	float pitch_ = 0.0;

	glm::vec3 up_       = vec3(0.0, 1.0, 0.0);
	glm::vec3 right_    = vec3(0.0, 0.0, 0.0);
	glm::vec3 forward_  = vec3(0.0, 0.0, 1.0);
	glm::vec3 position_ = vec3(0.0, 0.0, 0.0);

	Direction direction_ = Direction::NONE;
};

