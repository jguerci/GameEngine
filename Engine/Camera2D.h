#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D
{
public:
	Camera2D();
	~Camera2D();
	
	inline glm::vec3& GetPosition()   { return position_; }
	inline glm::mat4& GetViewMatrix() { return viewMatrix_; }

	void SetPosition(glm::vec3 pos);
private:
	glm::vec3 position_;
	glm::mat4 viewMatrix_;

	void Update();
};