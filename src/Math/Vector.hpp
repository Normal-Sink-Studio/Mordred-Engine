#pragma once

namespace Math {
	class Vector3
	{
	public:
		Vector3(double x, double y, double z);
		Vector3();
		~Vector3();
		Vector3 Zero(0,0,0);
		Vector3 One(1,1,1);		
		Vector3 Up(0,1,0);
		Vector3 Down(0, -1, 0);
		Vector3 Left(1, 0, 0);
		Vector3 Forward(0, 0, 1);
		Vector3 Back(0, 0, -1);
		Vector3 Normalize();
		double Length();
		double x = 0;
		double y = 0;
		double z = 0;
		Vector3 operator+(const int &a)
		{
			return(Vector3(this->x + a, this->y + a, this->z + a));
		}
	private:

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
}