#include "pyramid.h"

Pyramid::Pyramid() : Shape()
{
    // Triangolo frontale
    fTexCoords.append(QVector2D(0.0, 0.0));
    fColors.append(QVector3D(0.0, 1.0, 0.0));
    fVertices.append(QVector3D(0.0f, 1.0f, 0.0f));

    fTexCoords.append(QVector2D(0.0, 1.0));
    fColors.append(QVector3D(0.0, 1.0, 0.0));
    fColors.append(QVector3D(0.0, 1.0, 0.0));
    fVertices.append(QVector3D(-1.0f,-1.0f, 1.0f));

    fTexCoords.append(QVector2D(1.0, 1.0));
    fColors.append(QVector3D(0.0, 1.0, 0.0));
    fColors.append(QVector3D(0.0, 1.0, 0.0));
    fVertices.append(QVector3D(1.0f,-1.0f, 1.0f));

    // Triangolo sinistro
    /*glColor3f(1.0, 0.0, 0.0);
    glTexCoord2f (0.0, 0.0);
    glVertex3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f (0.0, 1.0);
        glVertex3f(-1.0f,-1.0f, -1.0f);
        glTexCoord2f (1.0, 1.0);
        glVertex3f(-1.0f,-1.0f, 1.0f);

        // Triangolo destro
        glColor3f(0.0, 0.0, 1.0);
        glTexCoord2f (0.0, 0.0);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f (0.0, 1.0);
        glVertex3f(1.0f,-1.0f, -1.0f);
        glTexCoord2f (1.0, 1.0);
        glVertex3f(1.0f,-1.0f, 1.0f);

        // Triangolo retro
        glColor3f(0.0, 1.0, 1.0);
        glTexCoord2f (0.0, 0.0);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f (0.0, 1.0);
        glVertex3f(-1.0f,-1.0f, -1.0f);
        glTexCoord2f (1.0, 1.0);
        glVertex3f(1.0f,-1.0f, -1.0f);
    glEnd();


    //TODO: da rifare con triangoli
    glBegin(GL_QUADS);
        // Quadrato sul fondo
        glColor3f(1.0, 0.0, 1.0);
        glTexCoord2f (0.0, 0.0);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f (0.0, 1.0);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glTexCoord2f (1.0, 0.0);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glTexCoord2f (1.0, 1.0);
        glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();*/
}
