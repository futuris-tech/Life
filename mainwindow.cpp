#include "mainwindow.h"
#include <QResizeEvent>
#include <random>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timer(this),
    field(this),
    button(this)
{
    timer.setInterval(100);
    connect(&button, &Button::pause, &timer, &QTimer::stop);
    connect(&button, &Button::play, &timer, (void (QTimer::*)())&QTimer::start);
    connect(&timer, &QTimer::timeout, &field, &Field::iteration);
    /*std::default_random_engine dre;
    field.data = new uchar[256*256];
    for (int i = 0; i < 256*256; i++)
        field.data[i] = dre() % 2;*/
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    auto size = event->size();
    size.setWidth(size.width() - 120);
    int l = std::min(size.width(), size.height());
    field.resize(l, l);
    int x = (size.width() - l) / 2;
    int y = (size.height() - l) / 2;
    field.move(x, y);
    button.move(x + l + 20, (size.height() - 100) / 2);
}

