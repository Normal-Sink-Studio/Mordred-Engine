#pragma once
#include <type_traits>
#include <iostream>
namespace Math {
	
	class Vector3
	{

	private:

	public:
		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		Vector3(T X, T Y, T Z);
		Vector3();
		~Vector3();
		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		static const Vector3& Zero();
		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		static const Vector3& One();
		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		static const Vector3& Up();
		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		static const Vector3& Down();
		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		static const Vector3& Left();
		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		static const Vector3& Right();
		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		static const Vector3& Forward();
		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		static const Vector3& Back();
		Vector3 Normalize();
		double Length();

		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		T x;
		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		T y;
		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		T z;
		template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		Vector3 operator+(const int& a)
		{
			return(Vector3(this->x + a, this->y + a, this->z + a));
		};
		class Vector2
		{
		public:
			Vector2();
			~Vector2();

		private:

		};

		Vector2::Vector2()
		{
		}

		Vector2::~Vector2()
		{
		}
	};