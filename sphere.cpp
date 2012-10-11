#include "sphere.h"
#include <math.h>

Sphere::Sphere(float radius, unsigned subdv) : Shape()
{
    int k = 0;
    float step = M_PI / (float) subdv;

    for(float a = 0; a <= (M_PI); a += step)
    {
        float z1 = radius * cos(a);
        float z2 = radius * cos(a + step);

        if(a > M_PI)
            a = M_PI;

        for(float b = -M_PI; b <= (M_PI); b += step)
        {
            if(b > M_PI)
                b = M_PI;

            float x1 = radius * sin(a) * cos(b);
            float y1 = radius * sin(a) * sin(b);
            float x2 = radius * sin(a + step) * cos(b + step);
            float y2 = radius * sin(a + step) * sin(b + step);


            /* Primo triangolo */
            fVertices.append(QVector3D(x1, y1, z1));
            fVertices.append(QVector3D(radius * sin(a + step) * cos(b), radius * sin(a + step) * sin(b), z2));
            fVertices.append(QVector3D(x2, y2, z2));

            fIndices.append(k);
            fIndices.append(k+1);
            fIndices.append(k+2);

            fNormals.append(Shape::calculateFaceNormal(fVertices[k], fVertices[k+1], fVertices[k+2]));

            fTexCoords.append(QVector2D(0, 0));
            fTexCoords.append(QVector2D(0, 1));
            fTexCoords.append(QVector2D(1, 1));


            /* Secondo triangolo */
            fVertices.append(QVector3D(radius * sin(a) * cos(b + step), radius * sin(a) * sin(b + step), z1));

            fIndices.append(k);
            fIndices.append(k+2);
            fIndices.append(k+3);


            fNormals.append(Shape::calculateFaceNormal(fVertices[k], fVertices[k+2], fVertices[k+3]));

            fTexCoords.append(QVector2D(0, 0));
            fTexCoords.append(QVector2D(1, 0));
            fTexCoords.append(QVector2D(1, 1));

            k += 4;
        }
    }


    glEnd();
}
