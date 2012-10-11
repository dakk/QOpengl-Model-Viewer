#include "sphererecursion.h"

SphereRecursion::SphereRecursion(float radius, int sub) : Shape()
{
    fVertices.append(QVector3D(1, 0, 0));
    fVertices.append(QVector3D(-1, 0, 0));
    fVertices.append(QVector3D(0, 1, 0));
    fVertices.append(QVector3D(0, -1, 0));
    fVertices.append(QVector3D(0, 0, 1));
    fVertices.append(QVector3D(0, 0, -1));


    GLushort indices[]  = {      0, 4, 2,
                                 2, 4, 1,
                                 1, 4, 3,
                                 3, 4, 0,
                                 0, 2, 5,
                                 2, 1, 5,
                                 1, 3, 5,
                                 3, 0, 5  };

    for(int i = 0; i < 24; i++)
        fIndices.append(indices[i]);

    for(int i = 0; i < sub; i++)
        subdivide();
}


void SphereRecursion::subdivide()
{
    QVector<GLuint>     indices;
    QVector<QVector3D>  vertices;
    QVector<QVector3D>  normals;
    unsigned triangles = getFacesCount() * 4;
    unsigned k = 0;

    /*
        https://sites.google.com/site/dlampetest/python/triangulating-a-sphere-recursively
        #            Make new points
        #                 a = (0+2)/2
        #                 b = (0+1)/2
        #                 c = (1+2)/2
        #        1
        #       /\        Normalize a, b, c
        #      /  \
        #    b/____\ c    Construct new triangles
        #    /\    /\       t1 [0,b,a]
        #   /  \  /  \      t2 [b,1,c]
        #  /____\/____\     t3 [a,b,c]
        # 0      a     2    t4 [a,c,2]
    */

    for(int i = 0; i < fIndices.size(); i += 3)
    {
        QVector3D v0 = fVertices[fIndices[i]];
        QVector3D v1 = fVertices[fIndices[i+1]];
        QVector3D v2 = fVertices[fIndices[i+2]];

        QVector3D a = (v0 + v2) * 0.5;
        QVector3D b = (v0 + v1) * 0.5;
        QVector3D c = (v1 + v2) * 0.5;

        a.normalize();
        b.normalize();
        c.normalize();

        vertices.append(a);     //0
        vertices.append(b);     //1
        vertices.append(c);     //2
        vertices.append(v0);    //3
        vertices.append(v1);    //4
        vertices.append(v2);    //5

        normals.append(calculateFaceNormal(v1, c, b));
        indices.append(k + 4);
        indices.append(k + 2);
        indices.append(k + 1);

        normals.append(calculateFaceNormal(c, v2, a));
        indices.append(k + 2);
        indices.append(k + 5);
        indices.append(k + 0);

        normals.append(calculateFaceNormal(b, c, a));
        indices.append(k + 1);
        indices.append(k + 2);
        indices.append(k + 0);

        normals.append(calculateFaceNormal(v0, b, a));
        indices.append(k + 3);
        indices.append(k + 1);
        indices.append(k + 0);

        k += 6;
    }

    fIndices = indices;
    fVertices = vertices;
    fNormals = normals;
}
