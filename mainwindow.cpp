#include "mainwindow.h"
#include <QResizeEvent>
#include <random>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timer(this),
    field(this),
    button(this),
    c_button(this)
{
    timer.setInterval(100);
    connect(&button, &Button::pause, &timer, &QTimer::stop);
    connect(&button, &Button::play, &timer, (void (QTimer::*)())&QTimer::start);
    connect(&c_button, &ClearButton::clear, &field, &Field::clear);
    connect(&timer, &QTimer::timeout, &field, &Field::iteration);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    auto size = event->size();
    size.setWidth(size.width() - 120);
    int l = std::min(size.width(), size.height());
    field.resize(l, l);
    int x = (size.width() - l) / 2;
    int y = (size.height() - l) / 2;
    int ch = size.height() / 2;
    field.move(x, y);
    button.move(x + l + 20, ch - button.height());
    c_button.move(x + l + 20, ch);
}

