#ifndef TRANFORM_H
#define TRANFORM_H

#include <string>
#include "Vector2D.h"

class Tranform
{
    public:
        float X, Y;

    public:
        Tranform(float x = 0, float y = 0) :X(x), Y(y) {}
        ~Tranform() {}

        void Log(std::string msg = "")
        {
            std::cerr << msg << "(X, Y) = (" << X << ", " << Y << ")" << std::endl;
        }

    private:
        inline void TranslateX(float x) { this->X += x; }
        inline void TranslateY(float y) { this->Y += y; }
        inline void Translate(Vector2D v) { this->X += v.X; this->Y += v.Y; }
};

#endif // TRANFORM_H
