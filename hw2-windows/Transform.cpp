// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
	const float radians = glm::radians(degrees);
	vec3& a = glm::normalize(axis);

	mat3* identity = new mat3(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);
	mat3* aaT = new mat3(a.x * a.x, a.x * a.y, a.x * a.z,
		a.x * a.y, a.y * a.y, a.y * a.z,
		a.x * a.z, a.y * a.z, a.z * a.z);
	mat3* K = new mat3(0.0f, a.z, -a.y,
		-a.z, 0.0f, a.x,
		a.y, -a.x, 0.0f);

	return mat3(cos(radians) * *identity + (1.0f - cos(radians)) * *aaT
		+ sin(radians) * *K);
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
	eye = rotate(degrees, up) * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
	glm::vec3 axis = glm::cross(eye, up);
	eye = rotate(degrees, axis) * eye;
	up = glm::normalize(rotate(degrees, axis) * up);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
	glm::vec3 vecW = glm::normalize(eye - center);
	glm::vec3 normalUp = glm::normalize(up);
	glm::vec3 vecU = glm::normalize(glm::cross(normalUp, vecW));
	glm::vec3 vecV = glm::cross(vecW, vecU);

	glm::mat4 lookAtMat = glm::mat4(
		vecU.x, vecV.x, vecW.x, 0.0f,
		vecU.y, vecV.y, vecW.y, 0.0f,
		vecU.z, vecV.z, vecW.z, 0.0f,
		-glm::dot(vecU, eye), -glm::dot(vecV, eye), -glm::dot(vecW, eye), 1.0f
	);

	return lookAtMat;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	const float ar_x_hfov = 1.0f / glm::tan(glm::radians(fovy / 2.0f));
	const float row3col3 = (-zNear - zFar) / (zFar - zNear);
	const float row3col4 = -2.0f * zFar * zNear / (zFar - zNear);
	mat4 perspectiveMatrix = mat4(ar_x_hfov / aspect, 0.0f, 0.0f, 0.0f,
									0.0f, ar_x_hfov, 0.0f, 0.0f,
									0.0f, 0.0f, row3col3, -1.0f,
									0.0f, 0.0f, row3col4, 0.0f);
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
	mat4 translationMatrix =	mat4(1.0f, 0.0f, 0.0f, 0.0f,
									0.0f, 1.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 1.0f, 0.0f,
									tx, ty, tz, 1.0f);
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
