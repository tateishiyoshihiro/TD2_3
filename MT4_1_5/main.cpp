#include <Novice.h>
#include"Matrix4x4.h"
#include"Vector3.h"
#include"Vector2.h"
#include<cmath>
#include <cassert>
#include <stdio.h>
#define _USE_MATH_DEFINES
static const int kRowHeight = 20;
static const int kColumnWidth = 60;
static const int kWindowWidth = 1280;
static const int kWindowHeght = 720;

const char kWindowTitle[] = "LE2C_14_タテイシ_ヨシヒロ";
struct Quaternion {
	float x;
	float y;
	float z;
	float w;
};

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] +
		1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] +
		1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] +
		1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] +
		1.0f * matrix.m[3][3];

	assert(w != 0.0f);

	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {

	Matrix4x4 result;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] = m1.m[y][x] + m2.m[y][x];
		}
	}
	return result;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Quaternion QuaternionSubtract(const Quaternion& q1, const Quaternion& q2) {
	Quaternion result;
	result.x = q1.x - q2.x;
	result.y = q1.y - q2.y;
	result.z = q1.z - q2.z;
	result.w = q1.w - q2.w;
	return result;
}

float Dot(const Vector3& v1, const Vector3& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

float Length(const Vector3& v) { return sqrtf(Dot(v, v)); }

Vector3 Normalize(const Vector3& v) {
	float length = Length(v);
	if (length != 0) {
		return { v.x / length, v.y / length, v.z / length };
	}
	return v;
}

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 v = { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };

	return v;
};

Vector3 VectorMultiply(float sclar, const Vector3& v) {
	return { sclar * v.x, sclar * v.y, sclar * v.z };
}

Matrix4x4 MakeRotateXMatrix(float radian) {
	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);
	return { 1.0f, 0.0f,      0.0f,     0.0f, 0.0f, cosTheta, sinTheta, 0.0f,
			0.0f, -sinTheta, cosTheta, 0.0f, 0.0f, 0.0f,     0.0f,     1.0f };
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);
	return { cosTheta, 0.0f, -sinTheta, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			sinTheta, 0.0f, cosTheta,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);
	return { cosTheta, sinTheta, 0.0f, 0.0f, -sinTheta, cosTheta, 0.0f, 0.0f,
			0.0f,     0.0f,     1.0f, 0.0f, 0.0f,      0.0f,     0.0f, 1.0f };
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] +
		m1.m[0][3] * m2.m[3][0];
	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] +
		m1.m[0][3] * m2.m[3][1];
	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] +
		m1.m[0][3] * m2.m[3][2];
	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] +
		m1.m[0][3] * m2.m[3][3];

	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] +
		m1.m[1][3] * m2.m[3][0];
	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] +
		m1.m[1][3] * m2.m[3][1];
	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] +
		m1.m[1][3] * m2.m[3][2];
	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] +
		m1.m[1][3] * m2.m[3][3];

	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] +
		m1.m[2][3] * m2.m[3][0];
	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] +
		m1.m[2][3] * m2.m[3][1];
	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] +
		m1.m[2][3] * m2.m[3][2];
	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] +
		m1.m[2][3] * m2.m[3][3];

	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] +
		m1.m[3][3] * m2.m[3][0];
	result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] +
		m1.m[3][3] * m2.m[3][1];
	result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] +
		m1.m[3][3] * m2.m[3][2];
	result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] +
		m1.m[3][3] * m2.m[3][3];
	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result = Multiply(
		Multiply(MakeRotateXMatrix(rotate.x), MakeRotateYMatrix(rotate.y)),
		MakeRotateZMatrix(rotate.z));
	result.m[0][0] *= scale.x;
	result.m[0][1] *= scale.x;
	result.m[0][2] *= scale.x;
	result.m[0][3] = 0;

	result.m[1][0] *= scale.y;
	result.m[1][1] *= scale.y;
	result.m[1][2] *= scale.y;
	result.m[1][3] = 0;

	result.m[2][0] *= scale.z;
	result.m[2][1] *= scale.z;
	result.m[2][2] *= scale.z;
	result.m[2][3] = 0;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1;
	return result;
}

Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 mat;
	mat.m[0][0] = 1;
	mat.m[0][1] = 0;
	mat.m[0][2] = 0;
	mat.m[0][3] = 0;

	mat.m[1][0] = 0;
	mat.m[1][1] = 1;
	mat.m[1][2] = 0;
	mat.m[1][3] = 0;

	mat.m[2][0] = 0;
	mat.m[2][1] = 0;
	mat.m[2][2] = 1;
	mat.m[2][3] = 0;

	mat.m[3][0] = 0;
	mat.m[3][1] = 0;
	mat.m[3][2] = 0;
	mat.m[3][3] = 1;
	return mat;
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + row * kRowHeight + 20, "%6.02f",
				matrix.m[row][column]);
		}
	}
	Novice::ScreenPrintf(x, y, "%s", label);
}

Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 matrix = { 0, 0, 0, 0 };
	float A = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] +
		m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] +
		m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]

		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] -
		m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] -
		m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] -
		m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] -
		m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] -
		m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] +
		m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] +
		m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] +
		m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] +
		m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] -
		m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] -
		m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] -
		m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] -
		m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] -
		m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] -
		m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] +
		m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] +
		m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] +
		m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];
	float A_ = 1 / A;
	matrix.m[0][0] = A_ * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
		m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] -
		m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]);
	matrix.m[0][1] = A_ * (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] -
		m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] +
		m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]);
	matrix.m[0][2] = A_ * (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] -
		m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]);
	matrix.m[0][3] = A_ * (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] -
		m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] +
		m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]);
	matrix.m[1][0] = A_ * (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] -
		m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] +
		m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]);
	matrix.m[1][1] = A_ * (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] +
		m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] -
		m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]);
	matrix.m[1][2] = A_ * (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] -
		m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] +
		m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]);
	matrix.m[1][3] = A_ * (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] +
		m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] -
		m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]);
	matrix.m[2][0] = A_ * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] +
		m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] -
		m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]);
	matrix.m[2][1] = A_ * (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] -
		m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] +
		m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]);
	matrix.m[2][2] = A_ * (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] +
		m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] -
		m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]);
	matrix.m[2][3] = A_ * (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] -
		m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] +
		m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]);
	matrix.m[3][0] = A_ * (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] -
		m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] +
		m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]);
	matrix.m[3][1] = A_ * (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] +
		m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] -
		m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]);
	matrix.m[3][2] = A_ * (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] -
		m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] +
		m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]);
	matrix.m[3][3] = A_ * (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] -
		m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]);
	return matrix;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 Per;

	Per.m[0][0] = (1 / aspectRatio) * (1 / tan(fovY / 2));
	Per.m[0][1] = 0.0f;
	Per.m[0][2] = 0.0f;
	Per.m[0][3] = 0.0f;

	Per.m[1][0] = 0.0f;
	Per.m[1][1] = (1 / tan(fovY / 2));
	Per.m[1][2] = 0.0f;
	Per.m[1][3] = 0.0f;

	Per.m[2][0] = 0.0f;
	Per.m[2][1] = 0.0f;
	Per.m[2][2] = farClip / farClip - nearClip;
	Per.m[2][3] = 1.0f;

	Per.m[3][0] = 0.0f;
	Per.m[3][1] = 0.0f;
	Per.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	Per.m[3][3] = 0.0f;

	return Per;
}

Matrix4x4 MakeOrthographicMatrix(
	float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 Ort;
	assert(left != right);
	assert(top != bottom);
	assert(nearClip != farClip);
	Ort.m[0][0] = 2.0f / (right - left);
	Ort.m[0][1] = 0.0f;
	Ort.m[0][2] = 0.0f;
	Ort.m[0][3] = 0.0f;

	Ort.m[1][0] = 0.0f;
	Ort.m[1][1] = 2.0f / (top - bottom);
	Ort.m[1][2] = 0.0f;
	Ort.m[1][3] = 0.0f;

	Ort.m[2][0] = 0.0f;
	Ort.m[2][1] = 0.0f;
	Ort.m[2][2] = 1.0f / (farClip - nearClip);
	Ort.m[2][3] = 0.0f;

	Ort.m[3][0] = (left + right) / (left - right);
	Ort.m[3][1] = (top + bottom) / (bottom - top);
	Ort.m[3][2] = nearClip / (farClip - nearClip);
	Ort.m[3][3] = 1.0f;

	return Ort;
}

Matrix4x4 ScalarMultiply(float scalar, const Matrix4x4& m) {

	Matrix4x4 result;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] = scalar * m.m[y][x];
		}
	}
	return result;
}

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angel) {
	Matrix4x4 rS = MakeIdentity4x4();

	rS.m[0][0] = std::cosf(angel);
	rS.m[1][1] = std::cosf(angel);
	rS.m[2][2] = std::cosf(angel);

	Matrix4x4 rP = MakeIdentity4x4();

	rP.m[0][0] = axis.x * axis.x;
	rP.m[0][1] = axis.x * axis.y;
	rP.m[0][2] = axis.x * axis.z;

	rP.m[1][0] = axis.y * axis.x;
	rP.m[1][1] = axis.y * axis.y;
	rP.m[1][2] = axis.y * axis.z;

	rP.m[2][0] = axis.z * axis.x;
	rP.m[2][1] = axis.z * axis.y;
	rP.m[2][2] = axis.z * axis.z;

	rP.m[3][3] = 0.0f;

	rP = ScalarMultiply((1.0f - std::cosf(angel)), rP);

	Matrix4x4 rC = MakeIdentity4x4();

	rC.m[0][0] = 0.0f;
	rC.m[0][1] = -axis.z;
	rC.m[0][2] = axis.y;
	rC.m[1][0] = axis.z;
	rC.m[1][1] = 0.0f;
	rC.m[1][2] = -axis.x;
	rC.m[2][0] = -axis.y;
	rC.m[2][1] = axis.x;
	rC.m[2][2] = 0.0f;
	rC.m[3][3] = 0.0f;

	rC = ScalarMultiply((-std::sinf(angel)), rC);

	Matrix4x4 resultMatrix = Add(Add(rS, rP), rC);

	return resultMatrix;
}

Matrix4x4 DerectionToDerection(const Vector3& from, const Vector3& to) {
	Vector3 Normal = Normalize(Cross(from, to));
	Vector3 MathTo = VectorMultiply(-1.0f, to);
	Matrix4x4 Result = MakeIdentity4x4();

	if ((from.x == MathTo.x && from.y == MathTo.y && from.z == MathTo.z)) {
		if (from.x != 0.0f || from.y != 0.0f) {
			Normal = { from.y, -from.x, 0.0f };
		}
		else if (from.x != 0.0f || from.z != 0.0f) {
			Normal = { from.z, 0.0f, -from.x };
		}
	}
	float cos = Dot(from, to);
	float sin = Length(Cross(from, to));

	Result.m[0][0] = Normal.x * Normal.x * (1.0f - cos) + cos;
	Result.m[0][1] = Normal.x * Normal.y * (1.0f - cos) + Normal.z * sin;
	Result.m[0][2] = Normal.x * Normal.z * (1.0f - cos) - Normal.y * sin;

	Result.m[1][0] = Normal.x * Normal.y * (1.0f - cos) - Normal.z * sin;
	Result.m[1][1] = Normal.y * Normal.y * (1.0f - cos) + cos;
	Result.m[1][2] = Normal.y * Normal.z * (1.0f - cos) + Normal.x * sin;

	Result.m[2][0] = Normal.x * Normal.z * (1.0f - cos) + Normal.y * sin;
	Result.m[2][1] = Normal.y * Normal.z * (1.0f - cos) - Normal.x * sin;
	Result.m[2][2] = Normal.z * Normal.z * (1.0f - cos) + cos;

	return Result;
}

Quaternion operator*(const Quaternion& a, const float b) {
	return Quaternion{
		.x = a.x * b,
		.y = a.y * b,
		.z = a.z * b,
		.w = a.w * b,
	};
}

Quaternion operator*(const float a, const Quaternion& b) { return b * a; }

// Multiply
Quaternion operator*(const Quaternion& lns, const Quaternion& rhs) {
	Quaternion q;

	q.w = lns.w * rhs.w - lns.x * rhs.x - lns.y * rhs.y - lns.z * rhs.z;

	q.x = lns.y * rhs.z - lns.z * rhs.y + rhs.w * lns.x + lns.w * rhs.x;

	q.y = lns.z * rhs.x - lns.x * rhs.z + rhs.w * lns.y + lns.w * rhs.y;

	q.z = lns.x * rhs.y - lns.y * rhs.x + rhs.w * lns.z + lns.w * rhs.z;

	return q;
}

Quaternion QuaternionMultiply(const Quaternion& lns, const Quaternion& rhs) {
	Quaternion q;

	q.w = lns.w * rhs.w - lns.x * rhs.x - lns.y * rhs.y - lns.z * rhs.z;

	q.x = lns.y * rhs.z - lns.z * rhs.y + rhs.w * lns.x + lns.w * rhs.x;

	q.y = lns.z * rhs.x - lns.x * rhs.z + rhs.w * lns.y + lns.w * rhs.y;

	q.z = lns.x * rhs.y - lns.y * rhs.x + rhs.w * lns.z + lns.w * rhs.z;

	return q;
}
Quaternion IdentityQuaternion() {
	Quaternion identity;

	identity.w = 1.0f;
	identity.x = 0.0f;
	identity.y = 0.0f;
	identity.z = 0.0f;

	return identity;
}

Quaternion Conjugate(const Quaternion& quaternion) {
	Quaternion result = { -quaternion.x, -quaternion.y, -quaternion.z, quaternion.w };

	return result;
}

Quaternion SlerpConjugate(const Quaternion& quaternion) {
	Quaternion result = { quaternion.x, -quaternion.y, quaternion.z, -quaternion.w };

	return result;
}

float Norm(const Quaternion& quaternion) {
	return sqrt(
		quaternion.w * quaternion.w + quaternion.x * quaternion.x + quaternion.y * quaternion.y +
		quaternion.z * quaternion.z);
}

Quaternion NormalizeQuaternion(const Quaternion& quaternion) {
	Quaternion result = {};

	float norm = Norm(quaternion);

	if (quaternion.x != 0.0f) {
		result.x = quaternion.x / norm;
	}
	else {
		result.x = 0.0f;
	}

	if (quaternion.y != 0.0f) {
		result.y = quaternion.y / norm;
	}
	else {
		result.y = 0.0f;
	}

	if (quaternion.z != 0.0f) {
		result.z = quaternion.z / norm;
	}
	else {
		result.z = 0.0f;
	}

	if (quaternion.w != 0.0f) {
		result.w = quaternion.w / norm;
	}
	else {
		result.w = 0.0f;
	}

	return result;
}

void VectorScreenPrintf(int x, int y, Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%0.2f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%0.2f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%0.2f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

void QuaternionScreenPrintf(int x, int y, Quaternion& Q, const char* label) {

	Novice::ScreenPrintf(x, y, "%0.2f", Q.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%0.2f", Q.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%0.2f", Q.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%0.2f", Q.w);
	Novice::ScreenPrintf(x + kColumnWidth * 4, y, "%s", label);
}

Quaternion InverseQuaternion(const Quaternion& quaternion) {

	Quaternion result = {};
	Quaternion conjugate = Conjugate(quaternion);

	float norm = Norm(quaternion);

	if (norm != 0.0f) {
		result.x = conjugate.x / (norm * norm);
		result.y = conjugate.y / (norm * norm);
		result.z = conjugate.z / (norm * norm);
		result.w = conjugate.w / (norm * norm);
	}

	return result;
}

// 任意軸回転
Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angl) {
	Quaternion result;
	float quaternionSin = std::sinf(angl / 2.0f);

	result.w = std::cosf(angl / 2.0f);
	result.x = quaternionSin * axis.x;
	result.y = quaternionSin * axis.y;
	result.z = quaternionSin * axis.z;

	return result;
}

// ベクトルでquaternionを回転させた結果のベクトルを求める
Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion) {
	Quaternion vectorQuat = { 0, vector.x, vector.y, vector.z };

	// 回転
	Quaternion rotatedQuat =
		QuaternionMultiply(QuaternionMultiply(quaternion, vectorQuat), Conjugate(quaternion));

	// 結果をベクトルに変換
	Vector3 rotatedVector = { rotatedQuat.x, rotatedQuat.y, rotatedQuat.z };

	return rotatedVector;
}

// Quaternionから回転行列を求める
Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion) {
	Matrix4x4 result;

	result.m[0][0] = (quaternion.w * quaternion.w) + (quaternion.x * quaternion.x) -
		(quaternion.y * quaternion.y) - (quaternion.z * quaternion.z);
	result.m[0][1] = (quaternion.x * quaternion.y) + (quaternion.w * quaternion.z) * 2;
	result.m[0][2] = (quaternion.x * quaternion.z) - (quaternion.w * quaternion.y) * 2;
	result.m[0][3] = 0.0f;

	result.m[1][0] = (quaternion.x * quaternion.y) - (quaternion.w * quaternion.z) * 2;
	result.m[1][1] = (quaternion.w * quaternion.w) - (quaternion.x * quaternion.x) +
		(quaternion.y * quaternion.y) - (quaternion.z * quaternion.z);
	result.m[1][2] = (quaternion.y * quaternion.z) + (quaternion.w * quaternion.x) * 2;
	result.m[1][3] = 0.0f;

	result.m[2][0] = (quaternion.x * quaternion.z) + (quaternion.w * quaternion.y) * 2;
	result.m[2][1] = (quaternion.y * quaternion.z) - (quaternion.w * quaternion.x) * 2;
	result.m[2][2] = (quaternion.w * quaternion.w) - (quaternion.x * quaternion.x) -
		(quaternion.y * quaternion.y) + (quaternion.z * quaternion.z);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

void invertQuaternion(Quaternion* q) {
	q->w = -q->w;
	q->x = -q->x;
	q->y = -q->y;
	q->z = -q->z;
}

// 球面線形保管

Quaternion Slerp(Quaternion& q0, Quaternion& q1, float t) {
	Quaternion result{};

	float dot = (q0.w * q1.w) + (q0.x * q1.x) + (q0.y * q1.y) + (q0.z * q1.z);

	// クォータニオンが逆向きの場合、符号を反転
	if (dot < 0.0) {

		invertQuaternion(&q1);

		dot = -dot;
	}

	// 線形補間
	float theta = std::acosf(dot);
	float sinTheta = std::sinf(theta);
	float weight1 = std::sinf((1.0f - t) * theta) / sinTheta;
	float weight2 = std::sinf(t * theta) / sinTheta;

	result.w = (weight1 * q0.w) + (weight2 * q1.w);
	result.x = (weight1 * q0.x) + (weight2 * q1.x);
	result.y = (weight1 * q0.y) + (weight2 * q1.y);
	result.z = (weight1 * q0.z) + (weight2 * q1.z);

	// 補間結果の正規化
	NormalizeQuaternion(result);

	return result;
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	Quaternion rotation0 = MakeRotateAxisAngleQuaternion({ 0.71f, 0.71f, 0.0f }, 0.3f);

	Quaternion rotation1 = MakeRotateAxisAngleQuaternion({ 0.71f, 0.0f, 0.71f }, 3.141592f);

	Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.0f);

	Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);

	Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);

	Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);

	Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.0f);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		QuaternionScreenPrintf(0, 0, interpolate0, " : interpolate0, Slerp(q0, q1, 0.0f)");
		QuaternionScreenPrintf(0, 20, interpolate1, " : interpolate1, Slerp(q0, q1, 0.3f)");
		QuaternionScreenPrintf(0, 40, interpolate2, " : interpolate2, Slerp(q0, q1, 0.5f)");
		QuaternionScreenPrintf(0, 60, interpolate3, " : interpolate3, Slerp(q0, q1, 0.7f)");
		QuaternionScreenPrintf(0, 80, interpolate4, " : interpolate4, Slerp(q0, q1, 1.0f)");
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
