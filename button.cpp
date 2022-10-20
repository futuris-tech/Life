#include "button.h"

#include <QMouseEvent>

Button::Button(QWidget* parent) :
    QLabel(parent),
    playing(false)
{
    resize(40, 40);
    setPixmap(QIcon(":/play.svg").pixmap(40, 40));
}

void Button::mouseReleaseEvent(QMouseEvent *event) {
    playing = !playing;
    const char* name;
    if (playing) {
        name = ":/pause.svg";
        emit play();
    }
    else {
        name = ":/play.svg";
        emit pause();
    }
    setPixmap(QIcon(name).pixmap(40, 40));
}
