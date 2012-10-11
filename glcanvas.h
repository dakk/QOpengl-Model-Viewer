#ifndef GLCANVAS_H
#define GLCANVAS_H

#include <QGLWidget>
#include <shape.h>

typedef enum
{
    OT_CUBE = 1,
    OT_PYRAMID,
    OT_TEAPOT,
    OT_TORUS,
    OT_SPHERE,
    OT_SPHEREMATRIX,
    OT_SPHERERECURSION,
    OT_BUNNY
} ObjectType;

class GlCanvas : public QGLWidget
{
    Q_OBJECT
public:
    explicit GlCanvas(QWidget *parent = 0);
            ~GlCanvas();
    void setWireframe(bool state);
    void setLighting(bool state);
    void setTexture(bool state);
    void setObjectType(ObjectType type);
    void resetView();
    void paintSphere(float radius, float step);
    void paintSphereRecursion(float radius, float subdivision);
    void paintSphereWithMatrix(float radius, float step);
    static unsigned loadTexture(char *path);
    
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:
    
public slots:
    void update();

private:
    float       fRotX;
    float       fRotY;
    float       fTransX;
    float       fTransY;
    float       fScale;
    ObjectType  fObjectType;
    bool        fClicked;
    bool        fMoveClicked;

    /* Posizione precedente del mouse */
    int         fOldMousePosX;
    int         fOldMousePosY;

    /* Posizione iniziale del mouse, nella quale e' stato premuto il tasto */
    int         fStartMousePosX;
    int         fStartMousePosY;

    unsigned    fDefaultTexture;
    bool        fTextureMapping;

    Shape       *fSphereMatrix;
    Shape       *fSphereRecursion;
    Shape       *fSphere;
    Shape       *fBunny;
    
};

#endif // GLCANVAS_H
