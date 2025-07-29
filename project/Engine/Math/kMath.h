﻿#pragma once
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "AABB.h"
#include <cmath>
#include <cassert>
#define _USE_MATH_DEFINES
#include <math.h>
#include <numbers>
#include "Transform.h"

const Vector3 operator*(const Vector3& v, const float f);

Vector3& operator+=(Vector3& v1, const Vector3& v2);

Vector3& operator-=(Vector3& v1, const Vector3& v2);

Vector3& operator*=(Vector3& v1, const Vector3& v2);

Vector3& operator/=(Vector3& v1, const Vector3& v2);

const Vector3 operator+(const Vector3& v1, const Vector3 v2);

//const Vector3 operator-(const Vector3& v1, const Vector3 v2);

const Vector3 operator*(const Vector3& v1, const Vector3& v2);

const Vector3 operator/(const Vector3& v1, const Vector3 v2);

const Vector3 operator+(const Vector3& v1, const float f);

const Vector3 operator-(const Vector3& v1, const float f);

const Vector3 operator/(const Vector3& v1, const float f);

//const Vector3 operator-(const Vector3& v1);

//単位行列の作成
Matrix4x4 MakeIdentity4x4();

// 1, x軸回転行列
Matrix3x3 MakeRotateMatrix3x3(float radian);

//  行列の積
Matrix3x3 Multiply3x3(const Matrix3x3& m1, const Matrix3x3& m2);

//1次元アフィン変換行列
Matrix3x3 MakeAffineMatrix3x3(const Vector2& scale, const Vector2& rotate, const Vector2& translate);

// 1, x軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);

// 2, y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);

// 3, z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

//座標変換
Vector3 MatrixTransform(const Vector3& vector, const Matrix4x4& matrix);

// Scale計算
Matrix4x4 MakeScaleMatrix(Vector3 scale);

// Translate計算
Matrix4x4 MakeTranslateMatrix(Vector3 translate);

//  行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

//３次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Quaternion& rotate, const Vector3& translate);

Matrix4x4 MakeAffineMatrix(Transform transform);

Matrix4x4 MakeAffineMatrix(QuaternionTransform quaternionTransform);



//3次元アフィン変換行列Quaternion版
Matrix4x4 MakeAffineMatrixInQuaternion(const Vector3& scale, const Matrix4x4& axisAngle, const Vector3& translate);

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle);

//逆行列
Matrix4x4 Inverse(const Matrix4x4& m);

// 正規化
Vector3 Normalize(const Vector3& v);

// クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);

float Dot(const Vector3& v1, const Vector3& v2);

// 共役Quaternionを返す
Quaternion Conjugate(const Quaternion& quaternion);

// Quaternionの積
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);

// 任意軸回転を表すQuaternionの生成
Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);

Quaternion QuaternionNormalize(const Quaternion q);

// ベクトルをQuaternionで回転させた結果のベクトルを求める
Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);

// Quaternionから回転行列を求める
Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);


// 1, 透視投影行列
Matrix4x4 MakePrespectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

// 2, 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

// 3, ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

// 球体描画
//void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

Vector3 SwapDegree(Vector3 radian);

Vector3 SwapRadian(Vector3 degree);

Vector2 SwapDegree(Vector2 radian);

Vector2 SwapRadian(Vector2 degree);

float SwapDegree(float radian);

float SwapRadian(float degree);

float Length(const Vector3& v);

float Distance(const Vector3& v1, const Vector3& v2);

// AABBから中心座標を計算
const Vector3 CenterAABB(const AABB& aabb);

// ベクトル変換
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

// ease In-Out x1 : 開始点  x2 : 目標点
float easeInOut(float time, float x1, float x2);

// ease In-Out x1 : 開始点  x2 : 目標点
int easeInOut(float t, unsigned int x1, unsigned int x2);

// easeOutQuint
float easeOutQuint(float t, float x1, float x2);

// easeInBack
float easeInBack(float t, float x1, float x2);

// ease In-Out x1 : 開始点  x2 : 目標点
Vector3 easeInOut(float time, Vector3 x1, Vector3 x2);

// easeOutQuint
Vector3 easeOutQuint(float t, Vector3 x1, Vector3 x2);

// easeInBack
Vector3 easeInBack(float t, Vector3 x1, Vector3 x2);

Quaternion Slerp(const Quaternion& befor, const Quaternion& after, float t);

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

float Lerp(const float& v1, const float& v2, float t);

float Dot(const Quaternion& v1, const Quaternion& v2);

// 逆Quaternionを返す
Quaternion Inverse(const Quaternion& quaternion);

// Quaternionのnormを返す
float Norm(const Quaternion& quaternion);