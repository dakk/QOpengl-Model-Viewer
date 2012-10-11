#-------------------------------------------------
#
# Project created by QtCreator 2012-09-08T12:10:54
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenglViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glcanvas.cpp \
    shape.cpp \
    spherematrix.cpp \
    sphererecursion.cpp \
    sphere.cpp \
    pyramid.cpp

HEADERS  += mainwindow.h \
    glcanvas.h \
    shape.h \
    spherematrix.h \
    sphererecursion.h \
    sphere.h \
    pyramid.h

FORMS    += mainwindow.ui

unix|win32: LIBS += -lglut -lpnglite -lGLU

OTHER_FILES += \
    android/version.xml \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/origo/QtActivity.java \
    android/src/org/kde/necessitas/origo/QtApplication.java \
    android/res/values-nl/strings.xml \
    android/res/values/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-id/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-it/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-rs/strings.xml \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/res/drawable-mdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable/logo.png \
    android/res/drawable/icon.png \
    android/res/drawable-hdpi/icon.png \
    Data/texture.png \
    Data/texture2.png \
    Data/bunny.ply
