#pragma once
#include <DirectXMath.h>
#include<vector>
using namespace DirectX;

namespace ButiEngine {

	struct Vector2;
	struct Vector3;
	struct Vector4;
	struct Quat;
	struct Matrix4x4;

	struct UInt2 :public DirectX::XMUINT2 {
		inline UInt2(int arg_x, int arg_y) {
			x = arg_x;
			y = arg_y;
		}
		inline UInt2() {
			x = 0;
			y = 0;
		}

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(x, y);
		}
	};

	struct Matrix4x4 :public DirectX::XMFLOAT4X4
	{
	public:
		inline Matrix4x4() {
			_11 = 1.0f;
			_12 = 0.0f;
			_13 = 0.0f;
			_14 = 0.0f;

			_21 = 0.0f;
			_22 = 1.0f;
			_23 = 0.0f;
			_24 = 0.0f;

			_31 = 0.0f;
			_32 = 0.0f;
			_33 = 1.0f;
			_34 = 0.0f;

			_41 = 0.0f;
			_42 = 0.0f;
			_43 = 0.0f;
			_44 = 1.0f;
		}
		inline Matrix4x4(const DirectX::XMMATRIX other)
		{
			DirectX::XMMATRIX tmp = other;
			DirectX::XMStoreFloat4x4(this, tmp);
		}
		explicit inline Matrix4x4(const Quat& quat);
		inline Matrix4x4& operator=(const DirectX::XMMATRIX& other)
		{
			auto tmp = other;
			DirectX::XMStoreFloat4x4(this, tmp);
			return *this;
		}
		bool ShowUI() { return false; }
		inline Vector4 operator*(const Vector4& vec4);

		inline Matrix4x4 operator*(const Matrix4x4& arg_matrix)const {
			return (XMMATRIX)(*this) * (XMMATRIX)arg_matrix;
		}
		inline Matrix4x4 operator*=(const Matrix4x4& arg_matrix) {
			*this= (XMMATRIX)(*this) * (XMMATRIX)arg_matrix;
			return *this;
		}

		inline operator DirectX::XMMATRIX() const
		{
			auto tmp = *this;
			auto output = DirectX::XMLoadFloat4x4(&tmp);
			return output;
		}
		inline Matrix4x4& Identity()
		{
			*this = (Matrix4x4)DirectX::XMMatrixIdentity();
			return *this;
		}
		inline Matrix4x4& Transpose() {

			*this = (Matrix4x4)XMMatrixTranspose(*this);
			return *this;
		}
		inline Matrix4x4 GetTranspose() const {
			return  (Matrix4x4)XMMatrixTranspose(*this);
		}
		inline Matrix4x4& Inverse() {
			*this = (Matrix4x4)XMMatrixInverse(nullptr, *this);
			return *this;
		}
		inline Matrix4x4 GetInverse()const {
			return (Matrix4x4)XMMatrixInverse(nullptr, *this);
		}
		inline Matrix4x4 GetInValidYZ()const {
			Matrix4x4 output = *this;
			output._11 = 1.0f;
			output._21 = 0.0f;
			output._31 = 0.0f;
			return output;
		}
		inline Matrix4x4 GetInValidXZ()const {
			Matrix4x4 output = *this;
			output._12 = 0.0f;
			output._22 = 1.0f;
			output._32 = 0.0f;
			return output;
		}
		inline Matrix4x4 GetInValidXY()const {
			Matrix4x4 output = *this;
			output._13 = 0.0f;
			output._23 = 0.0f;
			output._33 = 1.0f;
			return output;
		}
		inline Matrix4x4& InValidYZ() {
			this->_11 = 1.0f;
			this->_21 = 0.0f;
			this->_31 = 0.0f;
			return *this;
		}
		inline Matrix4x4& InValidXZ() {
			this->_12 = 0.0f;
			this->_22 = 1.0f;
			this->_32 = 0.0f;
			return *this;
		}
		inline Matrix4x4& InValidXY() {

			this->_13 = 0.0f;
			this->_23 = 0.0f;
			this->_33 = 1.0f;
			return *this;
		}
		inline Quat ToQuat()const;

		inline void Decompose(Vector3& rScaling, Quat& rQt, Vector3& rTranslation)const;

		inline Vector3 GetEulerOneValue()const;
		inline Vector3 GetEulerOneValue_local()const;


		inline Matrix4x4& CreateFromEuler(const Vector3& arg_euler);
		inline Matrix4x4& CreateFromEuler_local(const Vector3& arg_euler);
		inline bool Same(const Matrix4x4& other, const float epsilon = 0.001f) const {

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (abs(this->m[i][j] - other.m[i][j]) > epsilon) {
						return false;
					}
				}
			}

			return true;
		}

		static inline Matrix4x4 Scale(const Vector3& arg_scale);

		static inline Matrix4x4 RollX(const float Angle) {
			float    fSinAngle;
			float    fCosAngle;
			DirectX::XMScalarSinCos(&fSinAngle, &fCosAngle, Angle);

			Matrix4x4 M;
			M._11 = 1.0f;
			M._12 = 0.0f;
			M._13 = 0.0f;
			M._14= 0.0f;

			M._21 = 0.0f;
			M._22 = fCosAngle;
			M._23 = fSinAngle;
			M._24 = 0.0f;

			M._31 = 0.0f;
			M._32 = -fSinAngle;
			M._33 = fCosAngle;
			M._34 = 0.0f;

			M._41 = 0.0f;
			M._42 = 0.0f;
			M._43 = 0.0f;
			M._44 = 1.0f;
			return M;
		}
		static inline Matrix4x4 RollY(const float Angle) {
			float    fSinAngle;
			float    fCosAngle;
			XMScalarSinCos(&fSinAngle, &fCosAngle, Angle);

			Matrix4x4 M;
			M._11 = fCosAngle;
			M._12 = 0.0f;
			M._13 = -fSinAngle;
			M._14 =  0.0f;

			M._21 = 0.0f;
			M._22 = 1.0f;
			M._23 = 0.0f;
			M._24 = 0.0f;

			M._31 = fSinAngle;
			M._32 = 0.0f;
			M._33 = fCosAngle;
			M._34 = 0.0f;

			M._41 = 0.0f;
			M._42 = 0.0f;
			M._43 = 0.0f;
			M._44 = 1.0f;
			return M;
		}
		static inline Matrix4x4 RollZ(const float Angle) {
			float    fSinAngle;
			float    fCosAngle;
			XMScalarSinCos(&fSinAngle, &fCosAngle, Angle);

			Matrix4x4 M;
			M._11 = fCosAngle;
			M._12 = fSinAngle;
			M._13 = 0.0f;
			M._14 = 0.0f;

			M._21 = -fSinAngle;
			M._22 = fCosAngle;
			M._23 = 0.0f;
			M._24 = 0.0f;

			M._31 = 0.0f;
			M._32 = 0.0f;
			M._33 = 1.0f;
			M._34 = 0.0f;

			M._41 = 0.0f;
			M._42 = 0.0f;
			M._43 = 0.0f;
			M._44 = 1.0f;
			return M;
		}
		~Matrix4x4() {}


		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(this->_11, this->_12, this->_13, this->_14);
			archive(this->_21, this->_22, this->_23, this->_24);
			archive(this->_31, this->_32, this->_33, this->_34);
			archive(this->_41, this->_42, this->_43, this->_44);
		}
	};
	struct Vector2 :public DirectX::XMFLOAT2
	{
		inline Vector2(const DirectX::XMVECTOR other)
		{

			DirectX::XMVECTOR temp = other;
			DirectX::XMStoreFloat2(this, temp);
		};

		inline Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		inline Vector2() {
			this->x = 0;
			this->y = 0;
		}

		inline ~Vector2() {}


		inline  float* GetData()
		{
			float output[2] = { x,y };
			return output;
		}
		inline  void GetData(float* out)
		{
			auto data = GetData();
			for (int i = 0; i < 2; i++) {
				out[i] = data[i];
			}
		}

		inline Vector2& operator=(const DirectX::XMVECTOR other)
		{
			DirectX::XMVECTOR temp = other;
			DirectX::XMStoreFloat2(this, temp);
			return *this;
		}

		inline Vector2& operator +=(const Vector2& vec)
		{
			*this = *this + vec;
			return *this;
		}

		inline Vector2& operator +=(float value)
		{
			*this = *this + value;
			return *this;
		}

		inline Vector2 operator +(float value)
		{
			Vector2 temp(value, value);
			return (Vector2)XMVectorAdd(*this, temp);
		}

		inline Vector2& operator -=(const Vector2& vec)
		{
			*this = *this - vec;
			return *this;
		}

		inline Vector2& operator -=(float value)
		{
			*this = *this - value;
			return *this;
		}


		inline Vector2 operator -(float value)
		{
			Vector2 temp(value, value);
			return (Vector2)XMVectorSubtract(*this, temp);
		}

		inline Vector2& operator *=(float value)
		{
			*this = *this * value;
			return *this;
		}

		inline Vector2& operator /=(float value)
		{
			*this = *this / value;
			return *this;
		}

		inline const Vector2 operator -() const
		{
			return -1*(*this);
		}

		inline Vector2& Floor(int len=1)
		{
			if (len <= 0) {
				return *this;
			}
			*this *= std::pow(10, len - 1);
			x = std::floor(x);
			y = std::floor(y);
			*this /= std::pow(10, len - 1);
			return *this;
		}

		inline Vector2& Round(int len=1)
		{
			if (len <= 0) {
				return *this;
			}
			*this *= std::pow(10, len - 1);
			x = std::round(x);
			y = std::round(y);
			*this /= std::pow(10, len - 1);
			return *this;
		}

		inline Vector2& Ceil(int len=1)
		{
			if (len <= 0) {
				return *this;
			}
			*this *= std::pow(10, len - 1);
			x = std::ceil(x);
			y = std::ceil(y);
			*this /= std::pow(10, len - 1);
			return *this;
		}


		inline Vector2 GetRound(int len = 1)const
		{
			if (len <= 0) {
				return *this;
			}
			Vector2 output;
			output *= std::pow(10, len - 1);
			output.x = std::round(x);
			output.y = std::round(y);
			output /= std::pow(10, len - 1);
			return output;
		}
		inline Vector2 GetFloor(int len = 1)const
		{
			if (len <= 0) {
				return *this;
			}
			Vector2 output;
			output *= std::pow(10, len - 1);
			output.x = std::floor(x);
			output.y = std::floor(y);
			output /= std::pow(10, len - 1);
			return output;
		}
		inline Vector2 GetCeil(int len = 1)const
		{
			if (len <= 0) {
				return *this;
			}
			Vector2 output;
			output *= std::pow(10, len - 1);
			output.x = std::ceil(x);
			output.y = std::ceil(y);
			output /= std::pow(10, len - 1);
			return output;
		}

		inline float Dot(const Vector2& vec1) const
		{
			return ((Vector2)DirectX::XMVector2Dot(DirectX::XMVECTOR(*this), vec1)).x;
		}

		inline bool isNaN() const
		{
			return XMVector2IsNaN(*this);
		}

		inline bool isInfinite() const
		{
			return XMVector2IsInfinite(*this);
		}

		inline float GetLengthSqr() const
		{
			return ((Vector2)DirectX::XMVector2LengthSq(DirectX::XMVECTOR(*this))).x;
		}

		inline operator DirectX::XMVECTOR() const
		{
			DirectX::XMFLOAT2 temp = *this;
			DirectX::XMVECTOR output = DirectX::XMLoadFloat2(&temp);
			return output;
		}

		inline float GetLength() const {
			return ((Vector2)DirectX::XMVector2Length(DirectX::XMVECTOR(*this))).x;
		}

		inline float GetDistance(Vector2& other) const {
			auto i = sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y));
			return i;
		}

		inline void Normalize()
		{
			*this = DirectX::XMVector2Normalize(DirectX::XMVECTOR(*this));
		}
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(x, y);
		}
	};

	struct  Vector3 :public DirectX::XMFLOAT3
	{
		static Vector3 XAxis;
		static Vector3 YAxis;
		static Vector3 ZAxis;
		static Vector3 Zero;

		inline Vector3(const DirectX::XMVECTOR other)
		{
			DirectX::XMVECTOR temp = other;
			DirectX::XMStoreFloat3(this, temp);
		}
		inline Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		inline Vector3(float v)
		{
			this->x = v;
			this->y = v;
			this->z = v;
		}
		inline Vector3()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		inline Vector2 GetVector2() {
			return Vector2(x, y);
		}

		inline ~Vector3()
		{
		}

		inline  void GetData(float out[3])
		{
			out[0] = x;
			out[1] = y;
			out[2] = z;
		}
		inline const float* GetData_const()const
		{
			return &x;
		}
		inline float* GetData()
		{
			return &x;
		}
		inline Vector3& operator=(const DirectX::XMVECTOR other)
		{
			DirectX::XMVECTOR temp = other;
			DirectX::XMStoreFloat3(this, temp);
			return *this;

		}

		inline Vector3 operator=(const Vector3& other)
		{
			if (this != &other) {
				x = other.x;
				y = other.y;
				z = other.z;
			}
			return *this;
		}

		inline Vector3& operator=(const DirectX::XMFLOAT3& other)
		{
			DirectX::XMVECTOR temp = DirectX::XMLoadFloat3(&other);
			DirectX::XMStoreFloat3(this, temp);
			return *this;
		}

		inline Vector3& operator +=(const Vector3& vec)
		{
			*this = *this + vec;
			return *this;
		}

		inline Vector3& operator +=(float value)
		{
			*this = *this + value;
			return *this;
		}


		inline Vector3 operator +(float value)
		{
			Vector3 temp(value, value, value);
			return (Vector3)XMVectorAdd(*this, temp);
		}

		inline Vector3& operator -=(const Vector3& vec)
		{
			*this = *this - vec;
			return *this;
		}
		inline Vector3 operator -(const Vector3& vec)const
		{
			return Vector3(x - vec.x, y - vec.y, z - vec.z);
			
		}

		inline Vector3& operator -=(float value)
		{
			*this = *this - value;
			return *this;
		}

		inline Vector3 operator -(float value)
		{
			Vector3 temp(value, value, value);
			return (Vector3)XMVectorSubtract(*this, temp);
		}

		inline Vector3& operator *=(float value)
		{
			*this = *this * value;
			return *this;
		}
		inline Vector3 operator *(float value)const
		{
			Vector3 out = *this;
			out.x *= value;
			out.y *= value;
			out.z *= value;
			return out;
		}

		inline Vector3& operator *=(Matrix4x4 value)
		{
			*this = *this * value;
			return *this;
		}

		inline Vector3 operator *(Matrix4x4 value) const
		{
			auto tmp = (Vector3)XMVector3Transform(*this, value);
			return tmp;
		}

		inline Vector3 operator *(const Vector3& other)const {

			return Vector3(other.x * x, other.y * y, other.z * z);
		}

		inline Vector3& operator *=(const Vector3& other) {
			*this = Vector3(other.x * x, other.y * y, other.z * z);
			return  *this;
		}

		inline Vector3& operator /=(float value)
		{
			*this = *this / value;
			return *this;
		}

		inline const Vector3 operator -() const
		{
			return  -1 * (*this);
		}

		inline Vector3 operator*(const Quat& other);

		inline const bool operator==(const Vector3& other)const {
			if (other.x != this->x || other.y != this->y || other.z != this->z) {
				return false;
			}
			return true;
		}

		inline const bool operator!=(const Vector3& other)const {

			return !(*this == other);
		}

		inline const float Get(const UINT index)const {
			return *((&x) + index);
		}


		inline Vector3& Floor(int len=1)
		{
			if (len <= 0) {
				return *this;
			}
			*this *= std::pow(10, len - 1);
			x = std::floor(x);
			y = std::floor(y);
			z = std::floor(z);
			*this /= std::pow(10, len - 1);
			return *this;
		}

		inline Vector3& Round(int len=1)
		{
			if (len <= 0) {
				return *this;
			}
			*this *= std::pow( 10,len-1);
			x = std::round(x);
			y = std::round(y);
			z = std::round(z);
			*this /= std::pow(10, len - 1);
			return *this;
		}

		inline Vector3& Ceil(int len=1)
		{
			if (len <= 0) {
				return *this;
			}
			*this *= std::pow(10, len - 1);
			x= std::ceil(x);
			y=std::ceil(y);
			z=std::ceil(z);
			*this /= std::pow(10, len - 1);
			return *this;
		}


		inline Vector3 GetRound(int len = 1)const
		{
			if (len <= 0) {
				return *this;
			}
			Vector3 output;
			output *= std::pow(10, len - 1);
			output.x = std::round(x);
			output.y = std::round(y);
			output.z = std::round(z);
			output /= std::pow(10, len - 1);
			return output;
		}
		inline Vector3 GetFloor(int len = 1)const
		{
			if (len <= 0) {
				return *this;
			}
			Vector3 output;
			output *= std::pow(10, len - 1);
			output.x = std::floor(x);
			output.y = std::floor(y);
			output.z = std::floor(z);
			output /= std::pow(10, len - 1);
			return output;
		}
		inline Vector3 GetCeil(int len = 1)const
		{
			if (len <= 0) {
				return *this;
			}
			Vector3 output;
			output *= std::pow(10, len - 1);
			output.x = std::ceil(x);
			output.y = std::ceil(y);
			output.z = std::ceil(z);
			output /= std::pow(10, len - 1);
			return output;
		}

		inline float Distance(const Vector3& arg_point) {

			return sqrt((this->x - arg_point.x) * (this->x - arg_point.x) + (this->y - arg_point.y) * (this->y - arg_point.y) + (this->z - arg_point.z) * (this->z - arg_point.z));
			
		}

		inline float Dot(const Vector3& vec1) const
		{
			return ((Vector3)XMVector3Dot(*this, vec1)).x;
		}
		inline Vector2 ToVector2()const {
			return Vector2(x,y);
		}
		inline Vector3& Cross(const Vector3& vec1)
		{
			*this = (Vector3)XMVector3Cross(*this, vec1);
			return *this;
		}

		inline Vector3 GetCross(const Vector3& vec1)const
		{
			return (Vector3)XMVector3Cross(*this, vec1);
		}

		inline bool isNaN() const
		{
			return XMVector3IsNaN(*this);
		}

		inline bool isInfinite() const
		{
			return XMVector3IsInfinite(*this);
		}
		inline bool isZero() const
		{
			return (abs(x) <= FLT_MIN*10) && (abs(y) <= FLT_MIN * 10) && (abs(z) <= FLT_MIN * 10);
		}
		inline void RemoveEps() {
			if ((abs(x) <= 0.000000025)) {
				x = 0;
			}
			if ((abs(y) <= 0.000000025)) {
				y = 0;
			}
			if ((abs(z) <= 0.000000025)) {
				z = 0;
			}
		}
		inline const Vector3& ToDegrees() {
			x = XMConvertToDegrees(x);
			y = XMConvertToDegrees(y);
			z = XMConvertToDegrees(z);

			return *this;
		}
		inline  Vector3 GetDegrees() {
			Vector3 output = Vector3(XMConvertToDegrees(x), XMConvertToDegrees(y), XMConvertToDegrees(z));


			return output;
		}
		inline Vector3 GetRemoveNan() {
			if (XMVector3IsNaN(*this)) {
				auto output = *this;

				if (output.x == nanf("")) {
					output.x = 0;
				}
				if (output.y == nanf("")) {
					output.y = 0;
				}
				if (output.z == nanf("")) {
					output.z = 0;
				}
			}
			return *this;
		}
		inline const Vector3& ToRadian() {
			x = XMConvertToRadians(x);
			y = XMConvertToRadians(y);
			z = XMConvertToRadians(z);

			return *this;
		}

		inline const Vector3& SetLimit(const Vector3& arg_max, const Vector3& arg_min) {
			x = max(arg_min.x, x);
			y = max(arg_min.y, y);
			z = max(arg_min.z, z);

			x = min(arg_max.x, x);
			y = min(arg_max.y, y);
			z = min(arg_max.z, z);
			return *this;
		}
		inline Vector3 GetFreeze(bool arg_freezeX, bool arg_freezeY, bool arg_freezeZ) {
			auto output = *this;
			if (arg_freezeX)
				output.x = 0;
			if (arg_freezeY)
				output.y = 0;
			if (arg_freezeZ)
				output.z = 0;

			return output;
		}

		inline float GetLengthSqr() const
		{
			return ((Vector3)XMVector3LengthSq(*this)).x;
		}

		inline operator DirectX::XMVECTOR() const
		{
			DirectX::XMFLOAT3 temp = *this;
			DirectX::XMVECTOR output = DirectX::XMLoadFloat3(&temp);
			return output;
		};

		inline float GetLength() const
		{
			return ((Vector3)DirectX::XMVector3Length(DirectX::XMVECTOR(*this))).x;
		}

		inline Vector3& Abs() {

			x = abs(x);
			y = abs(y);
			z = abs(z);

			return *this;
		}
		inline Vector3 GetAbs()const {
			Vector3 output;
			output.x = abs(x);
			output.y = abs(y);
			output.z = abs(z);

			return output;
		}

		inline Vector3& Normalize()
		{
			*this = DirectX::XMVector3Normalize(DirectX::XMVECTOR(*this));
			return *this;
		}
		inline Vector3& Scroll()
		{
			auto temp = *this;

			x = temp.z;
			y = temp.x;
			z = temp.y;
			return *this;
		}

		inline Vector3& Scroll_Reverse() {

			auto temp = *this;

			x = temp.y;
			y = temp.z;
			z = temp.x;
			return *this;
		}

		inline Vector3 GetNormalize() const
		{
			return DirectX::XMVector3Normalize(DirectX::XMVECTOR(*this));
		}

		inline Vector3& Max(const Vector3& arg_other) {
			this->x = max(x, arg_other.x);
			this->y = max(y, arg_other.y);
			this->z = max(z, arg_other.z);
			return *this;
		}
		inline Vector3& Min(const Vector3& arg_other) {
			this->x = min(x, arg_other.x);
			this->y = min(y, arg_other.y);
			this->z = min(z, arg_other.z);
			return *this;
		}
		inline Vector3 GetMax(const Vector3& arg_other)const {
			Vector3 output;
			output.x = max(x, arg_other.x);
			output.y = max(y, arg_other.y);
			output.z = max(z, arg_other.z);

			return output;
		}
		inline Vector3 GetMin(const Vector3& arg_other)const {

			Vector3 output;
			output.x = min(x, arg_other.x);
			output.y = min(y, arg_other.y);
			output.z = min(z, arg_other.z);

			return output;
		}


		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(x, y, z);
		}

	};

	struct Vector4 :public DirectX::XMFLOAT4
	{
		inline Vector4(const DirectX::XMVECTOR other)
		{
			DirectX::XMVECTOR temp = other;
			DirectX::XMStoreFloat4(this, temp);
		}
		inline Vector4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		inline Vector4(const Vector3& xyz, float w)
		{
			this->x = xyz.x;
			this->y = xyz.y;
			this->z = xyz.z;
			this->w = w;
		}

		explicit inline Vector4(const XMFLOAT4& v) :
			DirectX::XMFLOAT4(v)
		{
		}
		inline Vector4()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}

		inline  float* GetData() 
		{
			
			return &(this->x);
		}
		inline  void GetData(float* out) 
		{
			auto data = GetData();
			for (int i = 0; i < 4; i++) {
				out[i] = data[i];
			}
		}
		inline Vector4& operator=(const DirectX::XMVECTOR& other)
		{
			DirectX::XMVECTOR temp = other;
			DirectX::XMStoreFloat4(this, temp);
			return *this;
		};
		inline ~Vector4() {};
		inline Vector4& operator +=(const Vector4& vec) {
			*this = *this + vec;
			return *this;
		};


		inline Vector4& operator +=(float value) {
			*this = *this + value;
			return *this;
		};

		inline Vector4 operator +(float value) {
			Vector4 temp(value, value, value, value);
			return (Vector4)XMVectorAdd(*this, temp);
		}


		inline Vector4& operator -=(const Vector4& vec)
		{
			*this = *this - vec;
			return *this;
		}

		inline Vector4& operator -=(float value)
		{
			*this = *this - value;
			return *this;
		};

		inline Vector4 operator -(float value)
		{
			Vector4 temp(value, value, value, value);
			return (Vector4)XMVectorSubtract(*this, temp);
		};

		inline Vector4& operator *=(float value)
		{
			*this = *this * value;
			return *this;
		}

		inline Vector4& operator /=(float value)
		{
			*this = *this / value;
			return *this;
		}

		inline const Vector4 operator -() const
		{
			
			return -1*(*this);
		}


		inline Vector4& Floor(int len) {}

		inline Vector4& Round(int len) {}

		inline Vector4& Ceil(int len) {}

		inline Vector3 GetVec3()const {
			return Vector3(x, y, z);
		}

		inline float Dot(const Vector4& vec1) const
		{
			return ((Vector3)XMVector4Dot(*this, vec1)).x;
		}

		inline bool isNaN() const
		{
			return XMVector4IsNaN(*this);
		}

		inline bool isInfinite() const
		{
			return XMVector4IsInfinite(*this);
		}

		inline float GetLengthSqr() const
		{
			return ((Vector3)DirectX::XMVector4LengthSq(DirectX::XMVECTOR(*this))).x;
		}
		inline Vector4& RemoveNan() {
			if (XMVector4IsNaN(*this)) {

				if (isnan((*this).x)) {
					(*this).x = 0;
				}
				if (isnan((*this).y)) {
					(*this).y = 0;
				}
				if (isnan((*this).z)) {
					(*this).z = 0;
				}
				if (isnan((*this).w)) {
					(*this).w = 0;
				}
			}
			return *this;
		}
		inline operator DirectX::XMVECTOR() const
		{
			DirectX::XMFLOAT4 temp = *this;
			DirectX::XMVECTOR output = DirectX::XMLoadFloat4(&temp);
			return output;
		}

		inline float GetLength() const
		{
			return ((Vector4)DirectX::XMVector4Length(DirectX::XMVECTOR(*this))).x;
		}

		inline void Normalize()
		{
			*this = DirectX::XMVector4Normalize(DirectX::XMVECTOR(*this));
		}


		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(x, y, z, w);
		}
	};

	class MathHelper
	{
	public:
		inline static double Ceil(double dSrc, int iLen)
		{
			double	dRet;

			dRet = dSrc * pow(10.0, iLen);
			dRet = (double)(int)(dRet + 0.9);

			return dRet * pow(10.0, -iLen);
		}
		inline static double Floor(double dSrc, int iLen)
		{
			double dRet;

			dRet = dSrc * pow(10.0, iLen);
			dRet = (double)(int)(dRet);

			return dRet * pow(10.0, -iLen);
		}
		inline static double Round(double dSrc, int iLen)
		{
			double	dRet;

			dRet = dSrc * pow(10.0, iLen);
			dRet = (double)(int)(dRet + 0.5);

			return dRet * pow(10.0, -iLen);
		}
		template<typename T>
		inline static T GetMaximum(const T& v1, const T& v2) {
			return v1 > v2 ? v1 : v2;
		}
		template<typename T>
		inline static T GetMinimum(const T& v1, const T& v2) {
			return v1 < v2 ? v1 : v2;
		}

		inline static float Dot(const Vector2& vec0, const Vector2& vec1)
		{
			return ((Vector2)XMVector2Dot(vec0, vec1)).x;
		}

		inline static float LengthSqr(const Vector2& vec)
		{
			return ((Vector2)XMVector2LengthSq(vec)).x;
		}

		inline static float Length(const Vector2& vec)
		{
			return ((Vector2)XMVector2Length(vec)).x;
		}

		inline static const Vector2 Normalize(const Vector2& vec)
		{
			return (Vector2)XMVector2Normalize(vec);
		}
		inline static float Dot(const Vector3& vec0, const Vector3& vec1)
		{
			return ((Vector3)XMVector3Dot(vec0, vec1)).x;
		}

		inline static float LengthSqr(const Vector3& vec)
		{
			return ((Vector3)XMVector3LengthSq(vec)).x;
		}

		inline static float Length(const Vector3& vec)
		{
			return ((Vector3)XMVector3Length(vec)).x;
		}

		inline static Vector3 Normalize(const Vector3& vec)
		{
			return (Vector3)XMVector3Normalize(vec);
		}

		static  Matrix4x4 GetLookAtRotation(const Vector3& arg_lookPos,const Vector3& arg_targetPos, const Vector3& arg_upAxis) {
			Vector3 z = ((Vector3)(arg_targetPos - arg_lookPos)).GetNormalize();
			Vector3 x = arg_upAxis.GetCross(z).GetNormalize();
			Vector3 y = z.GetCross(x).GetNormalize();

			auto out = Matrix4x4();
			out._11 = x.x; out._12 = x.y; out._13 = x.z;
			out._21 = y.x; out._22 = y.y; out._23 = y.z;
			out._31 = z.x; out._32 = z.y; out._33 = z.z;


			return out;
		}

		inline static  Vector3 Cross(const Vector3& vec0, const Vector3& vec1)
		{
			return (Vector3)XMVector3Cross(vec0, vec1);
		}

		inline static Vector3 Reflect(const Vector3& vec, const Vector3& normal)
		{
			return (Vector3)XMVector3Reflect(vec, normal);
		}

		inline static Vector3 Slide(const Vector3& vec, const Vector3& normal)
		{
			//vec�Ɩ@�����璼�s���̒����i���ςŋ��߂�j
			float Len = Dot(vec, normal);
			//���̒����ɐL�΂�
			Vector3 Contact = normal * Len;
			//�X���C�h��������͌��݂̃x�N�g����������Z
			return (vec - Contact);
		}
		inline static Matrix4x4 inverse(const Matrix4x4& mat)
		{
			XMVECTOR Vec;
			return (Matrix4x4)XMMatrixInverse(&Vec, mat);
		}

		static float ToRadian(float deg) {

			return deg * XM_PI / 180.0f;
		}
		static float ToDegree(float rad) {

			return rad * 180.0f / XM_PI;
		}


		static inline Quat LearpQuat(const Quat& arg_firstQuat, const Quat& arg_secondQuat, const float pase);
		static inline Vector3 LarpPosition(const Vector3& arg_startPoint, const Vector3& arg_endPoint, const float t) {
			return arg_startPoint + (arg_endPoint - arg_startPoint) * t;

		}

		static inline Vector3 LarpPosition(const Vector3& arg_startPoint, const Vector3& arg_endPoint, const float xt, const float yt, const float zt) {
			return Vector3(arg_startPoint.x + (arg_endPoint.x - arg_startPoint.x) * xt, arg_startPoint.y + (arg_endPoint.y - arg_startPoint.y) * yt, arg_startPoint.z + (arg_endPoint.z - arg_startPoint.z) * zt);

		}

		static const int IntMax = 2147483647;
		static const char CharMax = 127;
		static const short ShortMax = 32767;

		static char GetByteSize(const int arg_check);
		static char GetUnsignedByteSize(const UINT arg_check);
	private:
		MathHelper() {};
	};



	struct Quat : public Vector4
	{

		inline Quat() :Vector4()
		{
			Identity();
		}
		inline Quat(const Quat& quat) :
			Vector4(quat.x, quat.y, quat.z, quat.w)
		{
		}
		explicit inline Quat(const XMFLOAT4& v) :
			Vector4(v)
		{
		}
		inline Quat(float x, float y, float z, float w) :
			Vector4(x, y, z, w)
		{
		}

		inline Quat(const Vector3& vec, float r) :
			Vector4()
		{
			*this = (Quat)XMQuaternionRotationAxis(vec, r);
		}

		explicit inline Quat(float val) :
			Vector4()
		{
			x = val;
			y = val;
			z = val;
			w = val;
		}
		explicit inline Quat(const XMVECTOR& other) :
			Vector4()
		{
			XMVECTOR temp = other;
			XMStoreFloat4((XMFLOAT4*)this, temp);
		}

		explicit inline Quat(const Matrix4x4& m) {
			*this = m.ToQuat();
		}

		inline operator XMVECTOR() const {
			XMFLOAT4 temp = *this;
			XMVECTOR Vec = XMLoadFloat4(&temp);
			return Vec;
		}
		inline Quat& operator =(const Quat& quat)
		{
			if (this != &quat) {
				x = quat.x;
				y = quat.y;
				z = quat.z;
				w = quat.w;
			}
			return *this;
		}

		inline Quat& operator=(const XMFLOAT4& other) {
			(XMFLOAT4)*this = other;
			return *this;
		}

		inline Quat& operator=(const XMVECTOR& other) {
			XMVECTOR temp = other;
			XMStoreFloat4((XMFLOAT4*)this, temp);
			return *this;
		}

		inline bool operator==(const Quat& other)const {
			return XMQuaternionEqual(*this, other);
		}

		inline bool operator!=(const Quat& other)const {
			return !XMQuaternionEqual(*this, other);
		}

		inline Quat operator/(const Quat& other) {
			return (Quat)(((XMVECTOR)*this )/ (XMVECTOR)other);
		}

		inline Quat& setXYZ(const Vector3& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			return *this;
		}

		inline const Vector3 getXYZ() const
		{
			return Vector3(x, y, z);
		}

		inline Quat& setX(float arg_x)
		{
			x = arg_x;
			return *this;
		}

		inline Quat& setY(float arg_y)
		{
			y = arg_y;
			return *this;
		}

		inline Quat& setZ(float arg_z)
		{
			z = arg_z;
			return *this;
		}

		inline Quat& setW(float arg_w)
		{
			w = arg_w;
			return *this;
		}

		inline float getX()const {
			return x;
		}

		inline float getY()const {
			return y;
		}

		inline float getZ()const {
			return z;
		}

		inline float getW()const {
			return w;
		}

		inline Quat& SetElem(int idx, float value) {

			*(&x + idx) = value;
			return *this;

		}

		inline float GetElem(int idx) const {
			return *(&x + idx);
		}

		inline float& operator [](int idx)
		{
			return *(&x + idx);
		}


		inline float operator [](int idx) const
		{
			return *(&x + idx);
		}


		inline Quat operator +(const Quat& quat) const
		{
			return (Quat)XMVectorAdd(*this, quat);
		}


		inline Quat operator -(const Quat& quat) const
		{
			return (Quat)XMVectorSubtract(*this, quat);
		}


		inline Quat operator *(const Quat& quat) const
		{
			return (Quat)XMQuaternionMultiply(*this, quat);
		}

		inline Quat operator *(float val) const
		{
			Quat temp(val, val, val, val);
			return (Quat)XMVectorMultiply(*this, temp);
		}
		inline const Quat& operator *=(float val) 
		{
			Quat temp(val, val, val, val);
			return *this=(Quat)XMVectorMultiply(*this, temp);
		}

		inline const Quat& CreateFromAxisRotate(const Vector3& arg_axis, const  float angle) {
			*this = XMQuaternionRotationAxis(arg_axis, angle);
			return *this;
		}

		inline Matrix4x4 ToMatrix()const {
			return Matrix4x4(*this);
		}
		inline Quat& CreateFromEular(const Vector3& arg_eular) {

			Matrix4x4 rotationMatrix = DirectX::XMMatrixRotationZ(
				arg_eular.z
			) *
				DirectX::XMMatrixRotationY(
					arg_eular.y
				) *
				DirectX::XMMatrixRotationX(
					arg_eular.x
				);
			*this = rotationMatrix.ToQuat();
			return *this;
		}
		inline Quat& CreateFromEular_deg(const Vector3& arg_eular) {

			Matrix4x4 rotationMatrix = DirectX::XMMatrixRotationZ(
				XMConvertToRadians( arg_eular.z)
			) *
				DirectX::XMMatrixRotationY(
					XMConvertToRadians(arg_eular.y)
				) *
				DirectX::XMMatrixRotationX(
					XMConvertToRadians(arg_eular.x)
				);
			*this = rotationMatrix.ToQuat();
			return *this;
		}

		inline Quat& operator *=(const Quat& quat) {
			*this = *this * quat;
			return *this;
		}

		inline Quat& Normalize() {
			*this = (Quat)XMQuaternionNormalize(*this);
			return *this;
		}

		inline float Dot(const Quat& quat)const {
			return ((Quat)XMQuaternionDot(*this, quat)).x;
		}

		inline Quat& Conj(const Quat& quat) {
			*this = (Quat)XMQuaternionConjugate(quat);
			return *this;
		}
		inline Quat& Conj() {
			this->x = -this->x;
			this->y = -this->y;
			this->z = -this->z;
			return *this;
		}
		inline  Quat& Identity() {
			*this = (Quat)XMQuaternionIdentity();
			return *this;
		}
		
		inline Quat& Rotation(float radians, const Vector3& unitVec) {
			*this = (Quat)XMQuaternionRotationAxis(unitVec, radians);
			return *this;
		}

		inline Quat& Rotation(const Vector3& unitVec, float radians) {
			*this = (Quat)XMQuaternionRotationAxis(unitVec, radians);
			return *this;
		}
		inline Quat& rotationRollPitchYawFromVector(const Vector3& rotVec) {
			*this = (Quat)XMQuaternionRotationRollPitchYawFromVector(rotVec);
			return *this;
		}

		inline  Vector3 ToRotVec() const {
			Quat Temp = *this;
			Temp.Normalize();
			Matrix4x4 mt(Temp);
			Vector3 Rot;
			if (mt._32 == 1.0f) {
				Rot.x = XM_PI / 2.0f;
				Rot.y = 0;
				Rot.z = -atan2(mt._21, mt._11);
			}
			else if (mt._32 == -1.0f) {
				Rot.x = -XM_PI / 2.0f;
				Rot.y = 0;
				Rot.z = -atan2(mt._21, mt._11);
			}
			else {
				Rot.x = -asin(mt._32);
				Rot.y = -atan2(-mt._31, mt._33);
				Rot.z = atan2(mt._12, mt._11);
			}
			return Rot;
		}

		inline Quat& Inverse() {
			*this = (Quat)XMQuaternionInverse(*this);
			return *this;
		}
		inline Quat GetInverse()const {
			return (Quat)XMQuaternionInverse(*this);
			
		}
		inline Quat& Facing(const Vector3& norm) {
			Vector3 DefUp(0, 1.0f, 0);
			Vector3 Temp = norm;
			Vector2 TempVec2(Temp.x, Temp.z);
			if (MathHelper::Length(TempVec2) < 0.1f) {
				DefUp = Vector3(0, 0, 1.0f);
			}
			Temp.Normalize();
			Matrix4x4 RotMatrix;
			RotMatrix = XMMatrixLookAtLH(Vector3(0, 0, 0), Temp, DefUp);
			RotMatrix = MathHelper::inverse(RotMatrix);
			*this = RotMatrix.ToQuat();
			(*this).Normalize();
			return *this;
		}

		inline Quat& facingY(const Vector3& norm) {
			Vector3 Temp = norm;
			Temp.Normalize();
			*this = XMQuaternionRotationRollPitchYaw(0, atan2(Temp.x, Temp.z), 0);
			(*this).Normalize();
			return *this;
		}

		inline bool IsNaN() const {
			return XMQuaternionIsNaN(*this);
		}
		inline bool IsInfinite() const {
			return XMQuaternionIsInfinite(*this);
		}
	};
	inline Vector3 ButiEngine::Vector3::operator*(const Quat& other)
	{
		return (Vector3)(*this)*(other.ToMatrix());
	}

	inline Quat MathHelper::LearpQuat(const Quat& arg_firstQuat, const Quat& arg_secondQuat, const float pase)
	{
		Quat secQ = arg_secondQuat;
		if (arg_firstQuat.Dot(secQ) <= 0) {
			secQ = -secQ;
		}
		Quat out = Quat();
		const float len1 = arg_firstQuat.GetLength();
		const float len2 = arg_firstQuat.GetLength();

		if (len1 == 0.0f || len2 == 0.0f)
			return out;

		const float cos_val = (arg_firstQuat[0] * secQ[0] + arg_firstQuat[1] * secQ[1] + arg_firstQuat[2] * secQ[2] + arg_firstQuat[3] * secQ[3]) / (len1 * len2);
		const float w = acosf(cos_val);


		const float sin_w = sinf(w);
		const float sin_t_w = sinf(pase * w);
		const float sin_inv_t_w = sinf((1.0f - pase) * w);
		const float mult_q1 = sin_inv_t_w / sin_w;
		const float mult_q2 = sin_t_w / sin_w;

		for (int i = 0; i < 4; i++)
			out[i] = mult_q1 * arg_firstQuat[i] + mult_q2 * secQ[i];

		return out;
	}

	struct Line {
		Vector3 point;
		Vector3 velocity;
		Line() {}
		Line(const Vector3& p, const Vector3& v) :point(p), velocity(v) {}

		// ����̍��W���擾
		//  t: �x�N�g���Ɋ|���Z����W��
		inline virtual Vector3 GetPoint(float t) const {
			return point + velocity * t;
		}

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(point);
			archive(velocity);

		}
	};

	struct Segment : public Line {
		Segment() {}
		Segment(const Vector3& startPoint, const Vector3& endPoint) :Line(startPoint,((Vector3)( endPoint - startPoint)).GetNormalize()), endPos(endPoint) {}

		// �I�_���擾
		inline Vector3 GetEndPoint() const {
			return endPos;
		}
		inline Vector3 GetPoint(float t) const override {
			return point + (endPos - point) * t;
		}
		float Length()const {
			return ((Vector3)(endPos - point)).GetLength();
		}
		float LengthSqr()const {
			return ((Vector3)(endPos - point)).GetLengthSqr();
		}
		Vector3 endPos;
	};

	struct QuadraticBezierCurve {
	public:
		QuadraticBezierCurve(const Vector3& pointA, const Vector3& pointB, const Vector3& pointC) :lineAB(pointA, pointB), lineBC(pointB, pointC) {}
		inline Vector3 GetPoint(float t) {
			quadratic.point = lineAB.GetPoint(t);
			quadratic.endPos = lineBC.GetPoint(t);

			return quadratic.GetPoint(t);
		}
	private:
		Segment lineAB;
		Segment lineBC;
		Segment quadratic;
	};
	struct CubicBezierCurve {
	public:
		CubicBezierCurve(const Vector3& pointA, const Vector3& pointB, const Vector3& pointC, const Vector3& pointD) :curveABC(pointA, pointB, pointC), curveBCD(pointB, pointC, pointD) {}

		inline Vector3 GetPoint(float t) {
			cubic.point = curveABC.GetPoint(t);
			cubic.endPos = curveBCD.GetPoint(t);

			return cubic.GetPoint(t);
		}
	private:
		QuadraticBezierCurve curveABC;
		QuadraticBezierCurve curveBCD;
		Segment cubic;
	};

	struct Line2D {
		Vector2 point;
		Vector2 velocity;
		Line2D() {}
		Line2D(const Vector2& p, const Vector2& v) :point(p), velocity(v) {}

		// ����̍��W���擾
		//  t: �x�N�g���Ɋ|���Z����W��
		inline virtual Vector2 GetPoint(float t) const {
			return point + velocity * t;
		}
	};

	struct Segment2D : public Line2D {
		Segment2D() {}
		Segment2D(const Vector2& startPoint, const Vector2& endPoint) :Line2D(startPoint, endPoint - startPoint), endPos(endPoint) {}

		// �I�_���擾
		inline Vector2 GetEndPoint() const {
			return endPos;
		}
		inline Vector2 GetPoint(float t) const override {
			return point + (endPos - point) * t;
		}
		Vector2 endPos;
	};

	struct QuadraticBezierCurve2D {
	public:
		QuadraticBezierCurve2D() {}
		QuadraticBezierCurve2D(const Vector2& pointA, const Vector2& pointB, const Vector2& pointC) :lineAB(pointA, pointB), lineBC(pointB, pointC) {}
		inline Vector2 GetPoint(float t) {
			quadratic.point = lineAB.GetPoint(t);
			quadratic.endPos = lineBC.GetPoint(t);

			return quadratic.GetPoint(t);
		}
		Segment2D lineAB;
		Segment2D lineBC;
	private:
		Segment2D quadratic;
	};
	struct CubicBezierCurve2D {
	public:
		CubicBezierCurve2D(const Vector2& pointA, const Vector2& pointB, const Vector2& pointC, const Vector2& pointD)
		{
			curveABC = QuadraticBezierCurve2D(pointA, pointB, pointC);
			curveBCD = QuadraticBezierCurve2D(pointB, pointC, pointD);
		}

		inline Vector2 GetPoint(float t) {
			cubic.point = curveABC.GetPoint(t);
			cubic.endPos = curveBCD.GetPoint(t);

			return cubic.GetPoint(t);
		}

		inline float GetDerivative(float t) {
			return (3.0f * curveABC.lineAB.point.x * t + 2.0f * curveABC.lineAB.endPos.x) * t + curveABC.lineBC.endPos.x;
		}

		inline float GetYFromNuton(float x) {
			float epsilon = 1e-5f; // 臒l
			float x2, t0, t1, t2, d2, i;
			for (t2 = x, i = 0; i < 16; i++) {
				x2 = GetPoint(t2).x - x;
				if (abs(x2) < epsilon) {
					return GetPoint(t2).y;
				}
				d2 = GetDerivative(t2);
				if (abs(d2) < 1e-6f) {
					break;
				}
				t2 = t2 - x2 / d2;
			}
			t0 = 0.0f;
			t1 = 1.0f;
			t2 = x;
			if (t2 < t0) {
				return GetPoint(t0).y;
			}
			if (t2 > t1) {
				return GetPoint(t1).y;
			}
			while (t0 < t1) {
				x2 = GetPoint(t2).x;
				if (abs(x2 - x) < epsilon) {
					return GetPoint(t2).y;
				}
				if (x > x2) {
					t0 = t2;
				}
				else {
					t1 = t2;
				}
				t2 = (t1 - t0) * 0.5f + t0;
			}


			return  GetPoint(t2).y;
		}

		inline float GetYFromHalf(const float x, const char testCount = 12) {

			Vector2 a = curveABC.lineBC.endPos;
			Vector2 b = curveABC.lineAB.endPos;
			if (a.x == a.y && b.x == b.y) {
				return x;
			}
			float t = x;

			const float k0 = 1 + 3 * a.x - 3 * b.x;
			const float k1 = 3 * b.x - 6 * a.x;
			const float k2 = 3 * a.x;

			float epsilon = 0.0005f; // 臒l

			for (int i = 0; i < testCount; i++) {
				auto ft = k0 * t * t * t + k1 * t * t + k2 * t - x;

				if (ft <= epsilon && ft >= -epsilon) {
					break;
				}
				t -= t / 2;
			}
			auto r = 1 - t;

			return t * t * t + 3 * t * t * r * b.y + 3 * t * r * r * a.y;
		}
	private:
		QuadraticBezierCurve2D curveABC;
		QuadraticBezierCurve2D curveBCD;
		Segment2D cubic;
	};


	struct SplineCurve {
	public:
		SplineCurve() {
			for (int i = 0; i < 6; i++)
				vec_points.push_back(Vector3(0, 0, 0));
			Initialize();
		}
		SplineCurve(const std::vector<Vector3>& arg_vec_points) {
			vec_points = arg_vec_points;
			Initialize();
		}
		SplineCurve(Vector3 start, Vector3 end, const std::vector<Vector3>& arg_vec_points) {
			vec_points.push_back(start);
			vec_points.push_back(start);

			std::copy(arg_vec_points.begin(), arg_vec_points.end(), std::back_inserter(vec_points));

			vec_points.push_back(end);
			vec_points.push_back(end);
			Initialize();
		}
		SplineCurve(Vector3 startAndEnd, std::vector<Vector3> arg_vec_points) {
			vec_points.push_back(startAndEnd);
			vec_points.push_back(startAndEnd);

			std::copy(arg_vec_points.begin(), arg_vec_points.end(), std::back_inserter(vec_points));

			vec_points.push_back(startAndEnd);
			vec_points.push_back(startAndEnd);
			Initialize();
		}
		bool IsLoop()const {
			return vec_points.at(0) == vec_points.at(vec_points.size()-1);
		}

		Vector3 GetPoint(float t) {
			{
				UINT itr = (t / unit);

				if (itr >= vec_points.size() - 3) {
					itr = vec_points.size() - 4;
				}


				return CatmullRom((t - itr * unit) / unit, vec_points[itr], vec_points[itr + 1], vec_points[itr + 2], vec_points[itr + 3]);

			}
			t += 0.01f;

			if (t > 1.0f) {
				t = 0;
			}

		}

		bool ShowUI();

		void Initialize() {
			unit = 1.0f / (vec_points.size() - 3);
		}


		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(vec_points);
			archive(unit);
		}

	private:
		static Vector3 CatmullRom(float t, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3) {
			Vector3 a = -p0 + 3.0f * p1 - 3.0f * p2 + p3;
			Vector3 b = 2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3;
			Vector3 c = -p0 + p2;
			Vector3 d = 2.0f * p1;

			return 0.5f * ((a * t * t * t) + (b * t * t) + (c * t) + d);
		}

		std::vector<Vector3> vec_points;
		float unit = 0.0f;
	};

	////////////////////////////////////////////////////

	inline Vector4 ButiEngine::Matrix4x4::operator*(const Vector4& vec4)
	{
		return XMVector4Transform(vec4, *this);
	}

	inline ButiEngine::Matrix4x4::Matrix4x4(const Quat& quat)
	{
		if (!quat.isNaN())
			*this = (Matrix4x4)XMMatrixRotationQuaternion(XMVECTOR(quat));
		else {
			_11 = 1.0f;
			_12 = 0.0f;
			_13 = 0.0f;
			_14 = 0.0f;

			_21 = 0.0f;
			_22 = 1.0f;
			_23 = 0.0f;
			_24 = 0.0f;

			_31 = 0.0f;
			_32 = 0.0f;
			_33 = 1.0f;
			_34 = 0.0f;

			_41 = 0.0f;
			_42 = 0.0f;
			_43 = 0.0f;
			_44 = 1.0f;
		}
	}
	inline Matrix4x4 ButiEngine::Matrix4x4::Scale(const Vector3& arg_scale)
	{
		Matrix4x4 output;
		output._11 = arg_scale.x;
		output._22 = arg_scale.y;
		output._33 = arg_scale.z;
		return output;
	}
	inline Quat ButiEngine::Matrix4x4::ToQuat() const
	{
		Vector3 scale, pos;
		Quat qt;
		Decompose(scale, qt, pos);
		return qt;
	}
	inline void ButiEngine::Matrix4x4::Decompose(Vector3& rScaling, Quat& rQt, Vector3& rTranslation) const
	{
		XMVECTOR Scale;
		XMVECTOR Qt;
		XMVECTOR Translation;
		if (XMMatrixDecompose(&Scale, &Qt, &Translation, *this)) {
			rScaling = Scale;
			rQt = Qt;
			rTranslation = Translation;
		}
		else {
			//�X�P�[�����O�}�C�i�X�̏ꍇ�̏���
			auto XLen = MathHelper::Length(Vector3(_11, _12, _13));
			auto YLen = MathHelper::Length(Vector3(_21, _22, _23));
			auto ZLen = MathHelper::Length(Vector3(_31, _32, _33));
			//�X�P�[�����O��0�̗v�f������
			if (XLen == 0.0f) {
				XLen = 0.0001f;
			}
			if (YLen == 0.0f) {
				YLen = 0.0001f;
			}
			if (ZLen == 0.0f) {
				ZLen = 0.0001f;
			}
			rScaling = Vector3(XLen, YLen, ZLen);
			rTranslation = Vector3(_41, _42, _43);

			Vector3 vX = Vector3(_11, _12, _13) / XLen;
			Vector3 vY = Vector3(_21, _22, _23) / XLen;
			Vector3 vZ = Vector3(_31, _32, _33) / XLen;

			Matrix4x4 retM;
			retM.Identity();
			retM._11 = vX.x;
			retM._12 = vX.y;
			retM._13 = vX.z;

			retM._21 = vY.x;
			retM._22 = vY.y;
			retM._23 = vY.z;

			retM._31 = vZ.x;
			retM._32 = vZ.y;
			retM._33 = vZ.z;

			rQt = (Quat)XMQuaternionRotationMatrix(retM);

		}
	}

	inline Matrix4x4& Matrix4x4::CreateFromEuler(const Vector3& arg_euler)
	{
		*this = DirectX::XMMatrixRotationX(
			arg_euler.x
		) *
			DirectX::XMMatrixRotationY(
				arg_euler.y
			) *
			DirectX::XMMatrixRotationZ(
				arg_euler.z
			);
		return *this;
	}
	inline Matrix4x4& Matrix4x4::CreateFromEuler_local(const Vector3& arg_euler)
	{
		*this = DirectX::XMMatrixRotationZ(
			arg_euler.z
		) *
			DirectX::XMMatrixRotationY(
				arg_euler.y
			) *
			DirectX::XMMatrixRotationX(
				arg_euler.x
			);
		return *this;
	}

	static const float EulerXLimit = 90.0f / 180.0f * XM_PI;
	inline Vector3 Matrix4x4::GetEulerOneValue_local() const
	{

		Vector3 Rot;
		if (this->_31 == 1.0f) {
			Rot.x = atan2(-this->_32,this->_33);
			Rot.y = XM_PI / 2.0f;
			Rot.z = 0;
		}
		else if (this->_31 == -1.0f) {
			Rot.x = atan2(-this->_32,this->_33);
			Rot.y = -XM_PI / 2.0f;
			Rot.z = 0;
		}
		else {


			Rot.x = atan2(-this->_32, this->_33);
			Rot.y = asin(this->_31);
			Rot.z = -atan2(this->_21, this->_11);///-90~90
		}

		return Rot;


	}
	inline Vector3 Matrix4x4::GetEulerOneValue() const
	{
		Vector3 Rot;
		if (this->_13 == 1.0f) {
			Rot.x = atan2(this->_23 , this->_33);
			Rot.y = XM_PI / 2.0f;
			Rot.z = 0;
		}
		else if (this->_13 == -1.0f) {
			Rot.x = atan2(this->_23 , this->_33 );
			Rot.y = -XM_PI / 2.0f;
			Rot.z = 0;
		}
		else {


			Rot.x = atan2(this->_23 , this->_33);
			Rot.y = -asin(this->_13);
			Rot.z = atan2(this->_12 , this->_11 );///-90~90
		} 

		return Rot;
	}


	typedef Vector4 Color;
	typedef Vector2 Point2D;

	class Rectangle {
	public:
		float width;
		float height;
		float outerCircleRadius;
		Vector2 position;
		inline Rectangle() :width(0), height(0), position(Vector2()), outerCircleRadius(0) {};
		inline Rectangle(float arg_width, float  arg_height, Vector2 arg_position) :width(arg_width), height(arg_height), position(arg_position), outerCircleRadius(GetRectangleOuterCircleRadius((int)width, (int)height)) {};
		inline Rectangle(float arg_width, float  arg_height, Vector2 arg_position, float arg_outerCircleRadius) :width(arg_width), height(arg_height), position(arg_position), outerCircleRadius(arg_outerCircleRadius) {};
		inline Rectangle(float arg_width, float  arg_height, float x, float y) :width(arg_width), height(arg_height), position(Vector2(x, y)), outerCircleRadius(GetRectangleOuterCircleRadius((int)width, (int)height)) {};
		inline std::vector< Point2D> GetVertecies()
		{
			std::vector<Point2D> out{
				   Point2D(position.x - width / 2, position.y - height / 2),
				   Point2D(position.x + width / 2, position.y - height / 2),
				   Point2D(position.x + width / 2, position.y + height / 2),
				   Point2D(position.x - width / 2, position.y + height / 2)
			};

			return out;
		}

		inline void GetVertecies(Point2D* out) {
			out = GetVertecies().data();
		}

		inline bool IsContain(Point2D arg_point2D) {
			if (arg_point2D.x >= position.x - width / 2 && arg_point2D.x <= position.x + width / 2
				&& arg_point2D.y >= position.y - height / 2 && arg_point2D.y <= position.y + height / 2) {
				return true;
			}
			return false;
		}
		inline bool IsIntersects(std::shared_ptr< Rectangle> other) {

			/*auto d = other->position.GetDistance(position);
			if (other->position.GetDistance(position) > other->outerCircleRadius + outerCircleRadius) {
				return false;
			}*/
			auto otherVertecies = other->GetVertecies();
			for (auto i = 0; i < 4; i++)
			{
				if (IsContain(otherVertecies.at(i))) {
					return true;
				}
			}
			return false;
		}
		inline float GetTop() {

			return position.y - height / 2;
		}
		inline float GetBottom() {

			return position.y + height / 2;
		}
		inline float GetLeft() {
			return position.x - width / 2;
		}
		inline float GetRight() {

			return position.x + width / 2;
		}
		inline static float GetRectangleOuterCircleRadius(const int width, const int height) {
			auto aW = width; auto aH = height;
			auto s = (aW + aH);
			auto t = (s - aW) * (s - aH) * (s - aW) * (s - aH);
			auto u = (aW * aH * 2) * (aW * aH * 2) * (aW * aW + aH * aH);


			auto output = std::sqrt(u / t) / 4;
			return output;
		}
		inline static float GetRectangleOuterCircleRadius(const Rectangle& ref_rect) {
			auto s = (ref_rect.width + ref_rect.height);
			auto t = (s - ref_rect.width) * (s - ref_rect.height) * (s - ref_rect.width) * (s - ref_rect.height);
			auto u = (ref_rect.width * ref_rect.height * 2) * (ref_rect.width * ref_rect.height * 2) * (ref_rect.width * ref_rect.width + ref_rect.height * ref_rect.height);
			auto output = std::sqrt(u / t) / 4;
			return output;
		}
	};


	void OutputCereal(const Vector2& v, const std::string& path);

	void InputCereal(Vector2& v, const std::string& path);

	void OutputCereal(const Vector3& v, const std::string& path);

	void InputCereal(Vector3& v, const std::string& path);

	void OutputCereal(const Vector4& v, const std::string& path);

	void InputCereal(Vector4& v, const std::string& path);

	void OutputCereal(const Matrix4x4& v, const std::string& path);

	void InputCereal(Matrix4x4& v, const std::string& path);

	void OutputCereal(const Line& v, const std::string& path);

	void InputCereal(Line& v, const std::string& path);



}