#ifndef SPHEREMATRIX_H
#define SPHEREMATRIX_H

#include <shape.h>

class SphereMatrix : public Shape
{
public:
    SphereMatrix(float radius, unsigned subdv);
};

#endif // SPHEREMATRIX_H
