#include "shape.h"
#include <malloc.h>

Shape::Shape()
{
}


Shape::Shape(char *plyFile)
{
    FILE *f = fopen(plyFile, "r");

    /*if(f == NULL)
        raise file not found exception*/

    char line[512];

    while(fgets(line, sizeof(line), f) != NULL)
    {
        /* Se inizia con 3, stiamo leggendo un triangolo 3 i j k */
        if(line[0] == '3' && line[1] == ' ')
        {
            int i, j, k, verts;

            sscanf(line, "%d %d %d %d", &verts, &i, &j, &k);
            fIndices.append((unsigned) i);
            fIndices.append((unsigned) j);
            fIndices.append((unsigned) k);

            /* Calcolo la normale della faccia */
            fNormals.append(calculateFaceNormal(fVertices[i], fVertices[j], fVertices[k]));
        }
        /* Altrimenti stiamo leggendo un vertice x y z u v  */
        else
        {
            float x, y, z, u, v;

            sscanf(line, "%f %f %f %f %f", &x, &y, &z, &u, &v);
            fVertices.append(QVector3D(x, y, z));

            fTexCoords.append(QVector2D(u, v));
        }
    }

    printf("Loaded %s: %d vertices and %d faces\n", plyFile, fVertices.size(), getFacesCount());
    fclose(f);
}




QVector3D Shape::calculateFaceNormal(QVector3D v1, QVector3D v2, QVector3D v3)
{
    QVector3D a = v2 - v1; //QVector3D(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
    QVector3D b = v3 - v1; //QVector3D(v2.x() - v3.x(), v2.y() - v3.y(), v2.z() - v3.z());

    QVector3D normal = /*QVector3D::crossProduct(a, b); /**/QVector3D((a.y() * b.z()) - (a.z() * b.y()),
                                 (a.z() * b.x()) - (a.x() * b.z()),
                                 (a.x() * b.y()) - (a.y() * b.x()));/**/
    normal.normalize();
    return normal;
}


unsigned Shape::getFacesCount()
{
    return fIndices.size() / 3;
}


Shape::~Shape()
{
}


void Shape::randomizeColors()
{
    qsrand(time(NULL));
    for(int i = 0; i < fVertices.size(); i++)
        fColors.append(QVector3D(qrand() / (float) RAND_MAX, qrand() / (float) RAND_MAX, qrand() / (float) RAND_MAX));
}

void Shape::paint()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, fVertices.constData());

    if(fTexCoords.size() == fVertices.size())
    {
        glTexCoordPointer(2, GL_FLOAT, 0, fTexCoords.constData());
    }

    if(fColors.size() == fVertices.size())
    {
        //glColorPointer(3, GL_FLOAT, 0, fColors.constData());
    }
    if((unsigned) fNormals.size() == getFacesCount())
    {
        glNormalPointer(GL_FLOAT, 0, fNormals.constData());
    }

    glDrawElements(GL_TRIANGLES, fIndices.size(), GL_UNSIGNED_INT, fIndices.constData());
    //glDrawArrays(GL_POINTS, 0, fVertices.size());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    //glDisableClientState(GL_COLOR_ARRAY);
}


void Shape::addVertices(QVector<QVector3D> vect)
{
    for(int i = 0; i < vect.size(); i++)
        fVertices.append(vect.at(i));
}
