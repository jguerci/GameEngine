#include "Transform.h"

#include <glm\gtc\matrix_transform.hpp>
#include <iostream>

Transform::Transform()
{
}


Transform::~Transform()
{
}

glm::mat4 Transform::GetTransformation()
{
	glm::mat4 T   = glm::translate(glm::mat4(1.0f), translation_);
	glm::mat4 TR  = glm::rotate(T, glm::radians(angle_), rotation_);
	glm::mat4 TRS = glm::scale(TR, scale_);
	
	return TRS;
}

void Transform::PrintMatrix(glm::mat4 const & Mat0)
{
	printf("mat4(\n");
	printf("\tvec4(%2.3f, %2.3f, %2.3f, %2.3f)\n",		Mat0[0][0], Mat0[0][1], Mat0[0][2], Mat0[0][3]);
	printf("\tvec4(%2.3f, %2.3f, %2.3f, %2.3f)\n",		Mat0[1][0], Mat0[1][1], Mat0[1][2], Mat0[1][3]);
	printf("\tvec4(%2.3f, %2.3f, %2.3f, %2.3f)\n",		Mat0[2][0], Mat0[2][1], Mat0[2][2], Mat0[2][3]);
	printf("\tvec4(%2.3f, %2.3f, %2.3f, %2.3f))\n\n",	Mat0[3][0], Mat0[3][1], Mat0[3][2], Mat0[3][3]);
}