#include "Vector.hpp"

namespace Math
{


    template<typename T, typename>
    Vector3::Vector3(T X, T Y, T Z) {
        x(X), y(Y), z(Z);
    }

    Vector3::~Vector3() {}

    // Definition of the Zero vector
    template<typename T, typename>
    const Vector3& Vector3::Zero() {
        static const Vector3 zero(0, 0, 0);
        return zero;
    }

    // Definition of the One vector
    template<typename T, typename>
    const Vector3& Vector3::One() {
        static const Vector3 one(1, 1, 1);
        return one;
    }

    // Definition of the Up vector
    template<typename T, typename>
    const Vector3& Vector3::Up() {
        static const Vector3 up(0, 1, 0);
        return up;
    }

    // Definition of the Down vector
    template<typename T, typename>
    const Vector3& Vector3::Down() {
        static const Vector3 down(0, -1, 0);
        return down;
    }

    // Definition of the Right vector
    template<typename T, typename>
    const Vector3& Vector3::Right() {
        static const Vector3 right(1, 0, 0);
        return right;
    }

    // Definition of the Forward vector
    template<typename T, typename>
    const Vector3& Vector3::Forward() {
        static const Vector3 forward(0, 0, 1);
        return forward;
    }

    // Definition of the Back vector
    template<typename T, typename>
    const Vector3& Vector3::Back() {
        static const Vector3 back(0, 0, -1);
        return back;
    }
}