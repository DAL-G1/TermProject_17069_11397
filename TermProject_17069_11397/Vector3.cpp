#include "Vector3.h"
Vector3::Vector3() {}
Vector3::Vector3(float x, float y, float z) {
	xyz[0] = x;
	xyz[1] = y;
	xyz[2] = z;
}
void Vector3::setXYZ(float x, float y, float z) {
	xyz[0] = x;
	xyz[1] = y;
	xyz[2] = z;
}
const float* Vector3::getXYZ() const {
	return xyz;
}

Vector3& Vector3::operator=(const Vector3& vec3) {
	for (int i = 0; i < 3; i++) {
		xyz[i] = vec3.getXYZ()[i];
	}
	return (*this);
}

float& Vector3::operator[](const int i) {
	return xyz[i];
}
float Vector3::operator[](const int i) const {
	return xyz[i];
}
Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.getXYZ()[0] + v2.getXYZ()[0], v1.getXYZ()[1] + v2.getXYZ()[1], v1.getXYZ()[2] + v2.getXYZ()[2]);
}
Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1.getXYZ()[0] - v2.getXYZ()[0], v1.getXYZ()[1] - v2.getXYZ()[1], v1.getXYZ()[2] - v2.getXYZ()[2]);
}
Vector3 operator-(const Vector3& v) {
	return Vector3(-v.getXYZ()[0], -v.getXYZ()[1], -v.getXYZ()[2]);
}
Vector3 operator*(const float s, const Vector3& vec3) {
	return Vector3(vec3.getXYZ()[0]*s, vec3.getXYZ()[1]*s, vec3.getXYZ()[2]*s);
}
float dotProduct(const Vector3& v1, const Vector3& v2) {
	return (v1.getXYZ()[0]* v2.getXYZ()[0])+ (v1.getXYZ()[1]*v2.getXYZ()[1])+(v1.getXYZ()[2]*v2.getXYZ()[2]);
}