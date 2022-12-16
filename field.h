#ifndef FIELD_H
#define FIELD_H
#include <QLabel>
#include <QPainter>

class Field : public QLabel {
    Q_OBJECT
    //ushort coord[257];
    uchar* buffer0;
    uchar* buffer1;
    QPixmap pix;
    QPoint mouse;
    char new_value;

    void mouse_move(int x, int y);
public:
    explicit Field(QWidget *parent = nullptr);
    ~Field();
    void resizeEvent(QResizeEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
public slots:
    void iteration();
    void clear();
};

#endif // FIELD_H
