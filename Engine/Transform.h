#pragma once

#include <glm\glm.hpp>

class Transform
{
public:
	Transform();
	~Transform();

	glm::mat4 GetTransformation();

	inline glm::vec3& GetTranslation() { return translation_; }
	inline glm::vec3& GetRotation()    { return rotation_; }
	inline glm::vec3& GetScale()       { return scale_; }
	inline glm::vec3& GetPosition()    { return position_; }

	inline void SetTranslation(const glm::vec3& trans) { translation_ = trans; }
	inline void SetRotation(const glm::vec3& rot, float angle) { rotation_ = rot; angle_ = angle; }
	inline void SetScale(const glm::vec3& scale) { scale_ = scale; }
	inline void SetPosition(const glm::vec3& pos) { position_ = pos; }
private:
	void Transform::PrintMatrix(glm::mat4 const & Mat0);

	float angle_ = 1.0f;
	glm::vec3 translation_ = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation_    = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale_       = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 position_    = glm::vec3(0.0f, 0.0f, 0.0f);
};

