// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
	vec3& axis_norm = glm::normalize(axis);

	mat3* identity = new mat3(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);
	mat3* K = new mat3(0.0f, -axis_norm.z, axis_norm.y,
		axis_norm.z, 0.0f, -axis_norm.x,
		-axis_norm.y, axis_norm.x, 0.0f);

	return *identity + sin(degrees*(pi / 180.0f)) * *K + (1 - cos(degrees*(pi / 180.0f)))*(*K**K);
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
	eye = eye * rotate(degrees, up);
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
	glm::vec3 axis = glm::normalize(glm::cross(eye, up));
	eye = eye * rotate(degrees, axis);
	up = up * rotate(degrees, axis);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
	glm::vec3 vecW = glm::normalize(eye);
	glm::vec3 normalUp = glm::normalize(up);
	glm::vec3 vecU = glm::cross(up, vecW);
	glm::vec3 vecV = glm::normalize(glm::cross(vecW, vecU));

	glm::mat4 rotation = glm::transpose(glm::mat4(
		vecU.x, vecU.y, vecU.z, 0.0f,
		vecV.x, vecV.y, vecV.z, 0.0f,
		vecW.x, vecW.y, vecW.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	));

	glm::mat4 translation = glm::transpose(glm::mat4(
		1.0f, 0.0f, 0.0f, -eye.x,
		0.0f, 1.0f, 0.0f, -eye.y,
		0.0f, 0.0f, 1.0f, -eye.z,
		0.0f, 0.0f, 0.0f, 1.0f
	));

	return rotation * translation;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	const float ar_x_hfov = 1.0f / aspect * tanf(fovy / 2);
	const float row3col3 = (-zNear - zFar) / (zNear - zFar);
	const float row3col4 = 2 * (zFar + zNear) / (zNear - zFar);
	mat4 perspectiveMatrix = mat4(ar_x_hfov, 0.0f, 0.0f, 0.0f,
		0.0f, ar_x_hfov*aspect, 0.0f, 0.0f,
		0.0f, 0.0f, row3col3, row3col4,
		0.0f, 0.0f, 1.0f, 0.0f);
	// YOUR CODE FOR HW2 HERE
	// New, to implement the perspective transform as well.  
	return perspectiveMatrix;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
	mat4 scaleMatrix = mat4(sx, 0.0f, 0.0f, 0.0f,
							0.0f, sy, 0.0f, 0.0f,
							0.0f, 0.0f, sz, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f);
	// YOUR CODE FOR HW2 HERE
	// Implement scaling 
	return scaleMatrix;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
	mat4 translationMatrix =	mat4(1.0f, 0.0f, 1.0f, tx,
									0.0f, 1.0f, 0.0f, ty,
									0.0f, 0.0f, 1.0f, tz,
									0.0f, 0.0f, 0.0f, 1.0f);
	// YOUR CODE FOR HW2 HERE
	// Implement translation 
	return translationMatrix;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
