#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLContext>
#include <QTimer>
#include "field.h"
#include "button.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTimer timer;
    Field field;
    Button button;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resizeEvent(QResizeEvent *event) override;

};
#endif // MAINWINDOW_H
