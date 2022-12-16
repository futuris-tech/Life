#include "clearbutton.h"

ClearButton::ClearButton(QWidget *parent)
    : QLabel(parent)
{
    setText("Clear");
}

void ClearButton::mouseReleaseEvent(QMouseEvent *event) {
    emit clear();
}
