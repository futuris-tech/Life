#ifndef BUTTON_H
#define BUTTON_H

#include <QLabel>

class Button : public QLabel {
    Q_OBJECT
    bool playing;
public:
    Button(QWidget* parent = Q_NULLPTR);
    void mouseReleaseEvent(QMouseEvent* event) override;
signals:
    void pause();
    void play();
};

#endif // BUTTON_H
