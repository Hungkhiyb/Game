#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D
{
    public:
        float X, Y;

    public:
        Vector2D() {}
        Vector2D(float x, float y) :X(x), Y(y) {}
        ~Vector2D() {}

    public:
        inline Vector2D operator + (const Vector2D& v2) const
        {
            return Vector2D(this->X + v2.X, this->Y + v2.Y);
        }

        inline Vector2D operator - (const Vector2D& v2) const
        {
            return Vector2D(this->X - v2.X, this->Y - v2.Y);
        }

        inline Vector2D operator * (const float scalar) const
        {
            return Vector2D(this->X * scalar, this->Y * scalar);
        }

        inline Vector2D operator / (const float scalar) const
        {
            return Vector2D(this->X / scalar, this->Y / scalar);
        }

        void Log(std::string msg = "")
        {
            std::cerr << msg << "(X, Y) = (" << X << ", " << Y << ")" << std::endl;
        }
};

#endif // VECTOR2D_H
