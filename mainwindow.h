#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "glcanvas.h"


namespace Ui
{
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public Q_SLOTS:
    void exitAction();
    void setObjectAction(int type);
    void wireframeAction();
    void resetViewAction();
    void lightingAction();
    void textureAction();
    
private:
    Ui::MainWindow  *ui;
    GlCanvas        *fCanvas;
    bool             fWireframe;
    bool             fLighting;
    bool             fTexture;
};

#endif // MAINWINDOW_H
