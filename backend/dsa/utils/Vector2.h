#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <iostream>
#include <string>

class Vector2 {
public:
    float x, y;

    // Constructors
    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float x, float y) : x(x), y(y) {}
    Vector2(const Vector2& other) : x(other.x), y(other.y) {}

    // Assignment operator
    Vector2& operator=(const Vector2& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    // Addition
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // Subtraction
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // Scalar multiplication
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // Scalar division
    Vector2 operator/(float scalar) const {
        if (scalar == 0.0f)
            throw std::runtime_error("Division by zero");
        return Vector2(x / scalar, y / scalar);
    }

    Vector2& operator/=(float scalar) {
        if (scalar == 0.0f)
            throw std::runtime_error("Division by zero");
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Unary minus (negation)
    Vector2 operator-() const {
        return Vector2(-x, -y);
    }


    bool operator==(const Vector2& other) const {
        return (std::abs(x - other.x) < 1e-6f) && (std::abs(y - other.y) < 1e-6f);
    }

    bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }
    // Dot product
    float dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }

    // Cross product (returns scalar in 2D)
    float cross(const Vector2& other) const {
        return x * other.y - y * other.x;
    }

    // Magnitude (length) of the vector
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    // Squared magnitude (faster, avoids sqrt)
    float magnitudeSquared() const {
        return x * x + y * y;
    }

    // Normalize (make unit vector)
    Vector2 normalized() const {
        float mag = magnitude();
        if (mag == 0.0f)
            return Vector2(0.0f, 0.0f);
        return Vector2(x / mag, y / mag);
    }

    // Normalize in place
    void normalize() {
        float mag = magnitude();
        if (mag != 0.0f) {
            x /= mag;
            y /= mag;
        }
    }

    // Distance to another vector
    float distance(const Vector2& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    // Squared distance (faster)
    float distanceSquared(const Vector2& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        return dx * dx + dy * dy;
    }

    // Angle in radians
    float angle() const {
        return std::atan2(y, x);
    }

    // Angle between two vectors (in radians)
    float angleTo(const Vector2& other) const {
        float dot_prod = dot(other);
        float mags = magnitude() * other.magnitude();
        if (mags == 0.0f)
            return 0.0f;
        return std::acos(dot_prod / mags);
    }

    // Rotate by angle (in radians)
    Vector2 rotated(float angle) const {
        float cos_a = std::cos(angle);
        float sin_a = std::sin(angle);
        return Vector2(x * cos_a - y * sin_a, x * sin_a + y * cos_a);
    }

    // Rotate in place
    void rotate(float angle) {
        float cos_a = std::cos(angle);
        float sin_a = std::sin(angle);
        float new_x = x * cos_a - y * sin_a;
        float new_y = x * sin_a + y * cos_a;
        x = new_x;
        y = new_y;
    }

    // Perpendicular vector (90° rotation)
    Vector2 perpendicular() const {
        return Vector2(-y, x);
    }

    // Linear interpolation
    Vector2 lerp(const Vector2& other, float t) const {
        return Vector2(x + (other.x - x) * t, y + (other.y - y) * t);
    }

    // Clamp magnitude
    Vector2 clampMagnitude(float maxLength) const {
        float mag = magnitude();
        if (mag > maxLength && mag > 0.0f) {
            return (*this) * (maxLength / mag);
        }
        return *this;
    }

    // Reflect vector across a normal
    Vector2 reflect(const Vector2& normal) const {
        return *this - normal * (2.0f * dot(normal));
    }

    // Project this vector onto another
    Vector2 project(const Vector2& other) const {
        float mag_sq = other.magnitudeSquared();
        if (mag_sq == 0.0f)
            return Vector2(0.0f, 0.0f);
        float dot_prod = dot(other);
        return other * (dot_prod / mag_sq);
    }

    // ========== Static Methods ==========

    static float Dot(const Vector2& a, const Vector2& b) {
        return a.dot(b);
    }

    static float Cross(const Vector2& a, const Vector2& b) {
        return a.cross(b);
    }

    static float Distance(const Vector2& a, const Vector2& b) {
        return a.distance(b);
    }

    static Vector2 Lerp(const Vector2& a, const Vector2& b, float t) {
        return a.lerp(b, t);
    }

    static const Vector2 Zero() { return Vector2(0.0f, 0.0f); }
    static const Vector2 One() { return Vector2(1.0f, 1.0f); }
    static const Vector2 Up() { return Vector2(0.0f, 1.0f); }
    static const Vector2 Down() { return Vector2(0.0f, -1.0f); }
    static const Vector2 Left() { return Vector2(-1.0f, 0.0f); }
    static const Vector2 Right() { return Vector2(1.0f, 0.0f); }

    // ========== Utility ==========

    // Set components
    void set(float x, float y) {
        this->x = x;
        this->y = y;
    }

    // Check if vector is zero
    bool isZero() const {
        return std::abs(x) < 1e-6f && std::abs(y) < 1e-6f;
    }

    // Print vector
    void print() const {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }

    // String representation
    std::string toString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};


// Scalar * Vector (left multiplication)
inline Vector2 operator*(float scalar, const Vector2& vec) {
    return vec * scalar;
}

// Stream output
inline std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

#endif 