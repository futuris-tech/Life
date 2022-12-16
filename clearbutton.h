#ifndef CLEARBUTTON_H
#define CLEARBUTTON_H

#include <QLabel>

class ClearButton : public QLabel {
    Q_OBJECT
public:
    ClearButton(QWidget *parent = nullptr);
    void mouseReleaseEvent(QMouseEvent* event) override;
signals:
    void clear();
};

#endif // CLEARBUTTON_H
