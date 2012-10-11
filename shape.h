#ifndef SHAPE_H
#define SHAPE_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <GL/gl.h>

class Shape
{
public:
                                Shape();
                                Shape(char *plyFile);
                                ~Shape();
            void                paint();
            void                randomizeColors();
            void                addVertices(QVector<QVector3D> vect);
            unsigned            getFacesCount();
            static QVector3D    calculateFaceNormal(QVector3D v1, QVector3D v2, QVector3D v3);



protected:
            QVector<GLuint>     fIndices;
            QVector<QVector3D>  fVertices;
            QVector<QVector3D>  fNormals;
            QVector<QVector2D>  fTexCoords;
            QVector<QVector3D>  fColors;
};

#endif // SHAPE_H
