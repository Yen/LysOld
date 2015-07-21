#include "matrix4.hpp"

#include <string>

#include "mathsfunctions.hpp"

namespace lys
{

	Matrix4::Matrix4()
	{
		memset(&elements, 0, sizeof(float) * 16);
	}

	Matrix4::Matrix4(const float &diagonal)
		: Matrix4()
	{
		blocks[0].x = diagonal;
		blocks[1].y = diagonal;
		blocks[2].z = diagonal;
		blocks[3].w = diagonal;
	}

	Matrix4 &Matrix4::multiply(const Matrix4 &other)
	{
		float data[16];
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += elements[x + e * 4] * other.elements[e + y * 4];
				}
				data[x + y * 4] = sum;
			}
		}
		memcpy(elements, data, sizeof(float) * 16);

		return *this;
	}

	Matrix4 operator *(Matrix4 left, const Matrix4 &right)
	{
		return left.multiply(right);
	}

	Matrix4 &Matrix4::operator *=(const Matrix4 &other)
	{
		return multiply(other);
	}

	Vector3 Matrix4::multiply(const Vector3 &other) const
	{
		return Vector3(
			blocks[0].x * other.x + blocks[1].x * other.y + blocks[2].x * other.z + blocks[3].x,
			blocks[0].y * other.x + blocks[1].y * other.y + blocks[2].y * other.z + blocks[3].y,
			blocks[0].z * other.x + blocks[1].z * other.y + blocks[2].z * other.z + blocks[3].z
			);
	}

	Vector3 operator *(const Matrix4 &left, const Vector3 &right)
	{
		return left.multiply(right);
	}

	Vector4 Matrix4::multiply(const Vector4 &other) const
	{
		return Vector4(
			blocks[0].x * other.x + blocks[1].x * other.y + blocks[2].x * other.z + blocks[3].x * other.w,
			blocks[0].y * other.x + blocks[1].y * other.y + blocks[2].y * other.z + blocks[3].y * other.w,
			blocks[0].z * other.x + blocks[1].z * other.y + blocks[2].z * other.z + blocks[3].z * other.w,
			blocks[0].w * other.x + blocks[1].w * other.y + blocks[2].w * other.z + blocks[3].w * other.w
			);
	}

	Vector4 operator *(const Matrix4 &left, const Vector4 &right)
	{
		return left.multiply(right);
	}

	Matrix4 &Matrix4::invert()
	{
		float temp[16];

		temp[0] = elements[5] * elements[10] * elements[15] -
			elements[5] * elements[11] * elements[14] -
			elements[9] * elements[6] * elements[15] +
			elements[9] * elements[7] * elements[14] +
			elements[13] * elements[6] * elements[11] -
			elements[13] * elements[7] * elements[10];

		temp[4] = -elements[4] * elements[10] * elements[15] +
			elements[4] * elements[11] * elements[14] +
			elements[8] * elements[6] * elements[15] -
			elements[8] * elements[7] * elements[14] -
			elements[12] * elements[6] * elements[11] +
			elements[12] * elements[7] * elements[10];

		temp[8] = elements[4] * elements[9] * elements[15] -
			elements[4] * elements[11] * elements[13] -
			elements[8] * elements[5] * elements[15] +
			elements[8] * elements[7] * elements[13] +
			elements[12] * elements[5] * elements[11] -
			elements[12] * elements[7] * elements[9];

		temp[12] = -elements[4] * elements[9] * elements[14] +
			elements[4] * elements[10] * elements[13] +
			elements[8] * elements[5] * elements[14] -
			elements[8] * elements[6] * elements[13] -
			elements[12] * elements[5] * elements[10] +
			elements[12] * elements[6] * elements[9];

		temp[1] = -elements[1] * elements[10] * elements[15] +
			elements[1] * elements[11] * elements[14] +
			elements[9] * elements[2] * elements[15] -
			elements[9] * elements[3] * elements[14] -
			elements[13] * elements[2] * elements[11] +
			elements[13] * elements[3] * elements[10];

		temp[5] = elements[0] * elements[10] * elements[15] -
			elements[0] * elements[11] * elements[14] -
			elements[8] * elements[2] * elements[15] +
			elements[8] * elements[3] * elements[14] +
			elements[12] * elements[2] * elements[11] -
			elements[12] * elements[3] * elements[10];

		temp[9] = -elements[0] * elements[9] * elements[15] +
			elements[0] * elements[11] * elements[13] +
			elements[8] * elements[1] * elements[15] -
			elements[8] * elements[3] * elements[13] -
			elements[12] * elements[1] * elements[11] +
			elements[12] * elements[3] * elements[9];

		temp[13] = elements[0] * elements[9] * elements[14] -
			elements[0] * elements[10] * elements[13] -
			elements[8] * elements[1] * elements[14] +
			elements[8] * elements[2] * elements[13] +
			elements[12] * elements[1] * elements[10] -
			elements[12] * elements[2] * elements[9];

		temp[2] = elements[1] * elements[6] * elements[15] -
			elements[1] * elements[7] * elements[14] -
			elements[5] * elements[2] * elements[15] +
			elements[5] * elements[3] * elements[14] +
			elements[13] * elements[2] * elements[7] -
			elements[13] * elements[3] * elements[6];

		temp[6] = -elements[0] * elements[6] * elements[15] +
			elements[0] * elements[7] * elements[14] +
			elements[4] * elements[2] * elements[15] -
			elements[4] * elements[3] * elements[14] -
			elements[12] * elements[2] * elements[7] +
			elements[12] * elements[3] * elements[6];

		temp[10] = elements[0] * elements[5] * elements[15] -
			elements[0] * elements[7] * elements[13] -
			elements[4] * elements[1] * elements[15] +
			elements[4] * elements[3] * elements[13] +
			elements[12] * elements[1] * elements[7] -
			elements[12] * elements[3] * elements[5];

		temp[14] = -elements[0] * elements[5] * elements[14] +
			elements[0] * elements[6] * elements[13] +
			elements[4] * elements[1] * elements[14] -
			elements[4] * elements[2] * elements[13] -
			elements[12] * elements[1] * elements[6] +
			elements[12] * elements[2] * elements[5];

		temp[3] = -elements[1] * elements[6] * elements[11] +
			elements[1] * elements[7] * elements[10] +
			elements[5] * elements[2] * elements[11] -
			elements[5] * elements[3] * elements[10] -
			elements[9] * elements[2] * elements[7] +
			elements[9] * elements[3] * elements[6];

		temp[7] = elements[0] * elements[6] * elements[11] -
			elements[0] * elements[7] * elements[10] -
			elements[4] * elements[2] * elements[11] +
			elements[4] * elements[3] * elements[10] +
			elements[8] * elements[2] * elements[7] -
			elements[8] * elements[3] * elements[6];

		temp[11] = -elements[0] * elements[5] * elements[11] +
			elements[0] * elements[7] * elements[9] +
			elements[4] * elements[1] * elements[11] -
			elements[4] * elements[3] * elements[9] -
			elements[8] * elements[1] * elements[7] +
			elements[8] * elements[3] * elements[5];

		temp[15] = elements[0] * elements[5] * elements[10] -
			elements[0] * elements[6] * elements[9] -
			elements[4] * elements[1] * elements[10] +
			elements[4] * elements[2] * elements[9] +
			elements[8] * elements[1] * elements[6] -
			elements[8] * elements[2] * elements[5];

		float determinant = elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12];
		determinant = 1.0f / determinant;

		for (int i = 0; i < 4 * 4; i++) elements[i] = temp[i] * determinant;

		return *this;
	}

	Matrix4 Matrix4::invert(const Matrix4 &matrix)
	{
		Matrix4 result = matrix;
		return result.invert();
	}

	Matrix4 &Matrix4::transpose()
	{
		Matrix4 result = *this;
		result.blocks[0] = Vector4(blocks[0].x, blocks[1].x, blocks[2].x, blocks[3].x);
		result.blocks[1] = Vector4(blocks[0].y, blocks[1].y, blocks[2].y, blocks[3].y);
		result.blocks[2] = Vector4(blocks[0].z, blocks[1].z, blocks[2].z, blocks[3].z);
		result.blocks[3] = Vector4(blocks[0].w, blocks[1].w, blocks[2].w, blocks[3].w);
		*this = result;
		return *this;
	}

	Matrix4 Matrix4::transpose(const Matrix4 &matrix)
	{
		Matrix4 result = matrix;
		return result.transpose();
	}

	Matrix4 Matrix4::orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		Matrix4 result(1.0f);

		result.blocks[0].x = 2.0f / (right - left);
		result.blocks[1].y = 2.0f / (top - bottom);
		result.blocks[2].z = 2.0f / (near - far);

		result.blocks[3].x = (left + right) / (left - right);
		result.blocks[3].y = (bottom + top) / (bottom - top);
		result.blocks[3].z = (far + near) / (far - near);

		return result;
	}

	Matrix4 Matrix4::perspectivefov(float fov, float aspect, float near, float far)
	{
		float ymax = near * tan(maths::toRadians(0.5f * fov));
		float ymin = -ymax;
		float xmin = ymin * aspect;
		float xmax = ymax * aspect;

		return perspectiveoffcenter(xmin, xmax, ymin, ymax, near, far);
	}

	Matrix4 Matrix4::perspectiveoffcenter(float left, float right, float bottom, float top, float near, float far)
	{
		Matrix4 result(1.0f);

		float x = (2.0f * near) / (right - left);
		float y = (2.0f * near) / (top - bottom);

		float a = (right + left) / (right - left);
		float b = (top + bottom) / (top - bottom);
		float c = -(far + near) / (far - near);
		float d = -(2.0f * far * near) / (far - near);

		result.blocks[0].x = x;
		result.blocks[1].y = y;
		result.blocks[2].x = a;
		result.blocks[2].y = b;
		result.blocks[2].z = c;
		result.blocks[2].w = -1.0f;
		result.blocks[3].z = d;
		result.blocks[3].w = 0.0f;

		return result;
	}

	Matrix4 Matrix4::lookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up)
	{
		Vector3 z = Vector3::normalize(eye - target);
		Vector3 x = Vector3::normalize(Vector3::cross(up, z));
		Vector3 y = Vector3::normalize(Vector3::cross(z, x));

		Matrix4 result(1.0f);

		result.blocks[0].x = x.x;
		result.blocks[0].y = y.x;
		result.blocks[0].z = z.x;

		result.blocks[1].x = x.y;
		result.blocks[1].y = y.y;
		result.blocks[1].z = z.y;

		result.blocks[2].x = x.z;
		result.blocks[2].y = y.z;
		result.blocks[2].z = z.z;

		result.blocks[3].x = -((x.x * eye.x) + (x.y * eye.y) + (x.z * eye.z));
		result.blocks[3].y = -((y.x * eye.x) + (y.y * eye.y) + (y.z * eye.z));
		result.blocks[3].z = -((z.x * eye.x) + (z.y * eye.y) + (z.z * eye.z));

		return result;
	}

	Matrix4 Matrix4::translation(const Vector3 &translation)
	{
		Matrix4 result(1.0f);

		result.blocks[3].x = translation.x;
		result.blocks[3].y = translation.y;
		result.blocks[3].z = translation.z;

		return result;
	}

	Matrix4 Matrix4::rotation(float angle, const Vector3 &axis)
	{
		Matrix4 result(1.0f);

		float r = maths::toRadians(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		result.blocks[0].x = axis.x * omc + c;
		result.blocks[0].y = axis.y * axis.x * omc + axis.z * s;
		result.blocks[0].z = axis.x * axis.z * omc - axis.y * s;

		result.blocks[1].x = axis.x * axis.y * omc - axis.z * s;
		result.blocks[1].y = axis.y * omc + c;
		result.blocks[1].z = axis.y * axis.z * omc + axis.x * s;

		result.blocks[2].x = axis.x * axis.z * omc + axis.y * s;
		result.blocks[2].y = axis.y * axis.z * omc - axis.x * s;
		result.blocks[2].z = axis.z * omc + c;

		return result;
	}

	Matrix4 Matrix4::scale(const Vector3 &scale)
	{
		Matrix4 result(1.0f);

		result.blocks[0].x = scale.x;
		result.blocks[1].y = scale.y;
		result.blocks[2].z = scale.z;

		return result;
	}

	bool Matrix4::operator ==(const Matrix4 &other) const
	{
		for (char i = 0; i < 16; i++)
		{
			if (elements[i] != other.elements[i]) return false;
		}
		return true;
	}

	bool Matrix4::operator !=(const Matrix4 &other) const
	{
		return !(*this == other);
	}

}