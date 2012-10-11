#include "glcanvas.h"
#include <QTimer>
#include <stdio.h>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <qmath.h>
#include <iostream>

#include <pnglite.h>
#include <spherematrix.h>
#include <sphererecursion.h>
#include <sphere.h>

#ifndef QT_OPENGL_ES
#include <GL/glut.h>
#include <GL/glu.h>
#endif


GlCanvas::GlCanvas(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    fClicked = false;
    fObjectType = OT_TEAPOT;
    fOldMousePosX = -1;
    fOldMousePosY = -1;
    fStartMousePosX = 0;
    fStartMousePosY = 0;
    fRotX = 0.0;
    fRotY = 0.0;
    fScale = 0.3;
    fTransX = 0.0;
    fTransY = 0.0;
    fMoveClicked = false;
    fDefaultTexture = 0;
    fTextureMapping = false;


    fSphereMatrix = new SphereMatrix(1.0, 8);
    //fSphereMatrix->randomizeColors();
    fSphereRecursion = new SphereRecursion(1.0, 3);
    //fSphereRecursion->randomizeColors();
    fSphere = new Sphere(1.0, 16);
    //fSphere->randomizeColors();
    fBunny = new Shape("Data/bunny.ply");


    /*QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);*/

    this->setFocusPolicy(Qt::StrongFocus);

}


GlCanvas::~GlCanvas()
{
    delete fSphereMatrix;
    delete fSphereRecursion;
    delete fSphere;
}



/** Dato il path, carica la texture e restituisce l'id */
unsigned GlCanvas::loadTexture(char *path)
{
    /* Carica l'immagine png in memoria, usando la libreria pnglite */
    png_t png;
    unsigned int id;

    png_init(malloc, free);

    if(png_open_file_read(&png, path) != PNG_NO_ERROR)
        return 0;

    unsigned char *data = (unsigned char *) malloc(png.width * png.height * png.bpp);

    png_get_data(&png, (unsigned char *) data);


    /* Crea la texture in opengl */
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, png.bpp, png.width, png.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    /* Libera la risorsa png */
    png_close_file(&png);

    free(data);

    /* Restituisce l'id della texture */
    return id;
}


void GlCanvas::update()
{
    updateGL();
}

void GlCanvas::setWireframe(bool state)
{
    if(state)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    updateGL();
}


void GlCanvas::setTexture(bool state)
{
    fTextureMapping = state;


    if(fTextureMapping)
    {
        glEnable(GL_TEXTURE_2D);

        if(fDefaultTexture == 0)
            fDefaultTexture = GlCanvas::loadTexture("Data/texture.png");
        updateGL();
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
        updateGL();
    }
}

void GlCanvas::setLighting(bool state)
{
    if(state)
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);

    updateGL();
}


void GlCanvas::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);

    //glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);


    /* Impostazioni illuminazione di base */
    glEnable(GL_LIGHT0);

    // Create light components
    //GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    //GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    //GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    //GLfloat position[] = { 1.0f, -1.0f, 1.0f, 1.0f };

    // Assign created components to GL_LIGHT0
    //glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    //glLightfv(GL_LIGHT0, GL_POSITION, position);

    //glEnable(GL_COLOR_MATERIAL);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);

    /*float specReflection[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);*/
    //glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 98);

        /*GLfloat position_light0[] = { -1.0f, 0.0f, 1.0f, 0.0f };
        GLfloat diffuse_light0[]  = {  1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat specular_light0[] = {  1.0f, 1.0f, 1.0f, 1.0f };
        glLightfv( GL_LIGHT0, GL_POSITION, position_light0 );
        glLightfv( GL_LIGHT0, GL_DIFFUSE,  diffuse_light0 );
        glLightfv( GL_LIGHT0, GL_SPECULAR, specular_light0 );

        GLfloat ambient_lightModel[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient_lightModel );*/
}


void GlCanvas::setObjectType(ObjectType type)
{
    fObjectType = type;
}


/** Resetta la vista e le rotazioni */
void GlCanvas::resetView()
{    
    fRotX = 0.0;
    fRotY = 0.0;
    fScale = 0.3;
    fTransX = 0.0;
    fTransY = 0.0;
}



void GlCanvas::paintGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    //glPushMatrix();

    glTranslatef(fTransX, fTransY, -10.0);
    glScalef(fScale, fScale, fScale);

    glRotatef(fRotX, 1.0, 0.0, 0.0);
    glRotatef(fRotY, 0.0, 1.0, 0.0);


    if(fTextureMapping && fDefaultTexture != 0)
        glBindTexture(GL_TEXTURE_2D, fDefaultTexture);


    /* Renderizzo l'oggetto selezionato */
    switch(fObjectType)
    {
#ifndef QT_OPENGL_ES
    case OT_TEAPOT:
        glColor3f(1.0, 0.3, 0.0);
        glutSolidTeapot(1.0);
        break;

    case OT_TORUS:
        glColor3f(1.0, 0.0, 1.0);
        glutSolidTorus(0.4, 0.8, 100, 100);
        break;

    case OT_CUBE:
        glColor3f(1.0, 0.0, 0.0);
        glutSolidCube(1.0);
        break;
#endif
    case OT_SPHEREMATRIX:
        glColor3f(1.0, 0.5, 0.0);
        fSphereMatrix->paint();
        break;

    case OT_BUNNY:
        glColor3f(1.0, 0.5, 0.0);
        glScalef(10.0, 10.0, 10.0);
        glTranslatef(0.0, -0.1, 0.0);
        fBunny->paint();
        break;

    case OT_SPHERERECURSION:
        glColor3f(1.0, 0.5, 0.0);
        fSphereRecursion->paint();
        break;

    case OT_SPHERE:
        glColor3f(1.0, 0.5, 0.0);
        fSphere->paint();
        break;

    case OT_PYRAMID:
        glBegin(GL_TRIANGLES);
            // Triangolo frontale
            glColor3f(0.0, 1.0, 0.0);
            glTexCoord2f (0.0, 0.0);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f (0.0, 1.0);
            glVertex3f(-1.0f,-1.0f, 1.0f);
            glTexCoord2f (1.0, 1.0);
            glVertex3f(1.0f,-1.0f, 1.0f);

            // Triangolo sinistro
            glColor3f(1.0, 0.0, 0.0);
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
        glEnd();
        break;
    };

    //glPopMatrix();
}


void GlCanvas::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#else
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}


void GlCanvas::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
        fTransY += 0.03;
        break;

    case Qt::Key_Down:
        fTransY -= 0.03;
        break;

    case Qt::Key_Left:
        fTransX -= 0.03;
        break;

    case Qt::Key_Right:
        fTransX += 0.03;
        break;
    };
}


void GlCanvas::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
        fScale /= 1.08;
    else if(event->delta() < 0)
        fScale *= 1.08;

    updateGL();
}


void GlCanvas::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
    {
    case Qt::LeftButton:
        fStartMousePosX = fOldMousePosX = event->x();
        fStartMousePosY = fOldMousePosY = event->y();
        fClicked = true;
        break;
    case Qt::RightButton:
        fStartMousePosX = fOldMousePosX = event->x();
        fStartMousePosY = fOldMousePosY = event->y();
        fMoveClicked = true;
        break;
    };
}

void GlCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        fClicked = false;
}

void GlCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if(fClicked || fMoveClicked)
    {
        /* Differenze di spostamento con l'iterazione precendente */
        int dx = event->x() - fStartMousePosX;
        int dy = event->y() - fStartMousePosY;
        int ndx = event->x() - fOldMousePosX;
        int ndy = event->y() - fOldMousePosY;

        if(fClicked)
        {
            /* Se prevale lo spostamento nell'asse x */
            if(abs(dx) < abs(dy))
                fRotX += ndy;

            /* Se prevale lo spostamento nell'asse y */
            else
                fRotY += ndx;
        }
        else if(fMoveClicked)
        {
            /* Se prevale lo spostamento nell'asse x */
            if(abs(dx) < abs(dy))
                fTransY -= ndy / 200.0;

            /* Se prevale lo spostamento nell'asse y */
            else
                fTransX += ndx / 200.0;
        }

        fOldMousePosX = event->x();
        fOldMousePosY = event->y();

        updateGL();
    }
}

