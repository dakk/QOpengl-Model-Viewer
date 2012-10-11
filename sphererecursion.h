#ifndef SPHERERECURSION_H
#define SPHERERECURSION_H

#include <shape.h>


class SphereRecursion : public Shape
{
public:
            SphereRecursion(float radius, int sub);
    void    subdivide();
};

#endif // SPHERERECURSION_H
