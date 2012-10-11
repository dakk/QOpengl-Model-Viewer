#include "spherematrix.h"
#include <math.h>
#include <QMatrix4x4>

SphereMatrix::SphereMatrix(float radius, unsigned subdv) : Shape()
{
    QVector<QVector3D>  section;
    int k = 0;
    float step = M_PI / (float) subdv;

    /* Creo una semicirconferenza che utilizzeremo per creare la sfera */
    qsrand(time(NULL));
    float rr, gg, bb;

    rr = qrand() / (float) RAND_MAX;
    gg = qrand() / (float) RAND_MAX;
    bb = qrand() / (float) RAND_MAX;

    for(float a = 0; a <= M_PI; a += step)
    {
        float x1 = radius * sin(a) * cos(0);
        float z1 = radius * sin(a) * sin(0);
        float y1 = radius * cos(a);

        section.append(QVector3D(x1, y1, z1));
        fColors.append(QVector3D(rr, gg, bb));
    }
    addVertices(section);
    k += section.size();


    /* Matrice di rotazione */
    QMatrix4x4 m;
    m.rotate((step * 180) / M_PI, 0.0, 1.0f, 0.0);

    /* Ruoto ad ogni iterazione i vertici della semicirconferenza, salvandoli
     * nell'array dei vertici */
    for(float b = step; b <= (2 * M_PI); b += step)
    {
        QVector<QVector3D>  section2;

        rr = qrand() / (float) RAND_MAX;
        gg = qrand() / (float) RAND_MAX;
        bb = qrand() / (float) RAND_MAX;

        /* Ruota ciascun vertice della sezione precedente */
        for(int i = 0; i < section.size(); i++)
        {
            /* Ruota ciascun vertice della sezione */
            section2.append(section[i] * m);
            fColors.append(QVector3D(rr, gg, bb));
        }

        addVertices(section2);
        k += section2.size();
        section.clear();
        section = section2;
    }



    /* Crea le facce */
    subdv++;

    for(int j = 0; j < fVertices.size() / subdv - 1; j++)
    {
        for(int i = 0; i < subdv; i++)
        {
            fIndices.append(j * subdv + i + 0);
            fIndices.append(j * subdv + i + 1);
            fIndices.append(j * subdv + i + subdv + 1);
            fNormals.append(Shape::calculateFaceNormal(fVertices[j * subdv + i], fVertices[j * subdv + i + 1], fVertices[j * subdv + i + subdv + 1]));

            fIndices.append(j * subdv + i + subdv + 1);
            fIndices.append(j * subdv + i + 1);
            fIndices.append(j * subdv + i + subdv + 2);
            fNormals.append(Shape::calculateFaceNormal(fVertices[j * subdv + i + subdv + 1], fVertices[j * subdv + i + 1], fVertices[j * subdv + i + subdv + 2]));

        }
    }

    for(int i = 0; i < subdv; i++)
    {
        int j = fVertices.size() / subdv - 1;

        fIndices.append(j * subdv + i - 1);
        fIndices.append(j * subdv + i + 0);
        fIndices.append(i + 0);
        fNormals.append(Shape::calculateFaceNormal(fVertices[j * subdv + i - 1], fVertices[j * subdv + i], fVertices[i]));

        fIndices.append(i + 0);
        fIndices.append(j * subdv + i + 0);
        fIndices.append(i + 1);
        fNormals.append(Shape::calculateFaceNormal(fVertices[i], fVertices[j * subdv + i], fVertices[i+1]));
    }
}
