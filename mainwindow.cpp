#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>
#include <QSignalMapper>
#include <QVBoxLayout>

/**
 * Costruttore della finestra principale
 *
 * \note A seconda del tipo di implementazione opengl che stiamo usando (opengl / opengles),
 *       rendo disponibili nell'interfaccia solo le funzioni compatibili.
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Inizializzo le variabili */
    fWireframe = false;
    fLighting = false;
    fTexture = false;

    /* Crea il canvas e lo inserisce nel layout apposito */
    fCanvas = new GlCanvas;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fCanvas);

    ui->centralWidget->setLayout(mainLayout);


    /* Riempio il menu' e la toolbar */
    QMenu *menu;
    QAction *action;

    // Menu' file
    menu = new QMenu("File");
    menu->addSeparator();

    action = new QAction(this->style()->standardIcon(QStyle::SP_DialogCloseButton), ("&Exit"), this);
    connect(action, SIGNAL(triggered()), this, SLOT(exitAction()));
    menu->addAction(action);

    ui->menuBar->addMenu(menu);


    // Menu' vista
    menu = new QMenu("View");


    action = new QAction(("&Reset view"), this);
    //action->setEnabled(false);
    connect(action, SIGNAL(triggered()), this, SLOT(resetViewAction()));
    menu->addAction(action);

    menu->addSeparator();

    action = new QAction(("&Wireframe"), this);
    connect(action, SIGNAL(triggered()), this, SLOT(wireframeAction()));
    menu->addAction(action);
    ui->mainToolBar->addAction(action);
    action->setCheckable(true);
    action->setChecked(false);


    action = new QAction(("&Skybox"), this);
    action->setEnabled(false);
    action->setCheckable(true);
    action->setChecked(false);
    //connect(action, SIGNAL(triggered()), this, SLOT(resetViewAction()));
    menu->addAction(action);


    action = new QAction(("&Texture"), this);
    action->setCheckable(true);
    action->setChecked(false);
    connect(action, SIGNAL(triggered()), this, SLOT(textureAction()));
    menu->addAction(action);
    ui->mainToolBar->addAction(action);


    action = new QAction(("&Lighting"), this);
    connect(action, SIGNAL(triggered()), this, SLOT(lightingAction()));
    menu->addAction(action);
    ui->mainToolBar->addAction(action);
    action->setCheckable(true);
    action->setChecked(false);

    menu->addSeparator();

    action = new QAction(("Set Texture"), this);
    action->setEnabled(false);
    //connect(action, SIGNAL(triggered()), this, SLOT(textureAction()));
    menu->addAction(action);

    action = new QAction(("Set Skybox"), this);
    action->setEnabled(false);
    //connect(action, SIGNAL(triggered()), this, SLOT(resetViewAction()));
    menu->addAction(action);

    ui->menuBar->addMenu(menu);


    // Menu' oggetti
    menu = new QMenu("Object");

    QAction *cubeAction = new QAction(("Cube"), this);
    QAction *pyramidAction = new QAction(("Pyramid"), this);
    QAction *teapotAction = new QAction(("Teapot"), this);
    QAction *torusAction = new QAction(("Torus"), this);
    QAction *sphereAction = new QAction(("Sphere"), this);
    QAction *sphereMatrixAction = new QAction(("Sphere with matrix"), this);
    QAction *sphereRecursionAction = new QAction(("Sphere with recursion"), this);
    QAction *bunnyAction = new QAction(("Stanford bunny"), this);

    QSignalMapper *signalMapper = new QSignalMapper(this);
    signalMapper->setMapping(pyramidAction, OT_PYRAMID);

    /* Non compilo le funzioni che usano glut per problemi di compilazione con opengles */
#ifndef QT_OPENGL_ES
    signalMapper->setMapping(cubeAction, OT_CUBE);
    signalMapper->setMapping(teapotAction, OT_TEAPOT);
    signalMapper->setMapping(torusAction, OT_TORUS);
    signalMapper->setMapping(sphereAction, OT_SPHERE);
    signalMapper->setMapping(sphereMatrixAction, OT_SPHEREMATRIX);
    signalMapper->setMapping(sphereRecursionAction, OT_SPHERERECURSION);
    signalMapper->setMapping(bunnyAction, OT_BUNNY);
#endif


    connect(pyramidAction, SIGNAL(triggered()), signalMapper, SLOT (map()));
#ifndef QT_OPENGL_ES
    connect(cubeAction, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(teapotAction, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(torusAction, SIGNAL(triggered()), signalMapper, SLOT (map()));
#endif
    connect(sphereAction, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(bunnyAction, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(sphereMatrixAction, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(sphereRecursionAction, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(setObjectAction(int)));

    menu->addAction(pyramidAction);
#ifndef QT_OPENGL_ES
    menu->addAction(cubeAction);
    menu->addAction(teapotAction);
    menu->addAction(torusAction);
    menu->addAction(sphereAction);
    menu->addAction(bunnyAction);
    menu->addAction(sphereMatrixAction);
    menu->addAction(sphereRecursionAction);
#endif

    ui->menuBar->addMenu(menu);
}


MainWindow::~MainWindow()
{
    delete ui;
}




/** Chiude l'applicazione */
void MainWindow::exitAction()
{
    this->close();
}


/** Resetta la vista, ristabilendo la visione frontale */
void MainWindow::resetViewAction()
{
    fCanvas->resetView();
}


/** Abilita/Disabilita le texture */
void MainWindow::textureAction()
{
    fTexture = !fTexture;
    fCanvas->setTexture(fTexture);
}




/** Abilita/Disabilita l'illuminazione */
void MainWindow::lightingAction()
{
    fLighting = !fLighting;
    fCanvas->setLighting(fLighting);
}


/** Abilita/Disabilita il wireframe */
void MainWindow::wireframeAction()
{
    fWireframe = !fWireframe;
    fCanvas->setWireframe(fWireframe);
}


/** Imposta l'oggeto da visualizzare */
void MainWindow::setObjectAction(int type)
{
    fCanvas->setObjectType((ObjectType) type);
}
