#include "field.h"
#include <QPainter>
#include <QResizeEvent>
#include <QDateTime>
#include <random>

const bool RandomInit = true;
const int Size = 256;
const int Stride = Size + 2;

enum painter_color { Dead, Alive, DeadSel, AliveSel, TypeNum };
class painter {
    QSize size;
    QPainter p;
    QBrush brush[TypeNum];
public:
    painter(QPixmap& pix) : size(pix.size()), p(&pix) {
        p.setPen(Qt::NoPen);
        brush[Dead]     = QBrush(QColor(255,255,255));
        brush[Alive]    = QBrush(QColor(0,0,0));
        brush[DeadSel]  = QBrush(QColor(92,92,255));
        brush[AliveSel] = QBrush(QColor(0,0,164));
    }
    void draw(int x, int y, painter_color color) {
        int x0 = x * size.width() / Size;
        int y0 = y * size.height() / Size;
        int x1 = (x + 1) * size.width() / Size;
        int y1 = (y + 1) * size.height() / Size;
        int w = x1 - x0;
        int h = y1 - y0;
        p.setBrush(brush[color]);
        p.drawRect(x0, y0, w, h);
    }
};

Field::Field(QWidget *parent) :
    QLabel{parent},
    buffer0(new uchar[Stride * Stride]),
    buffer1(new uchar[Stride * Stride]),
    mouse(-1,-1),
    new_value(-1)
{
    setMouseTracking(true);
    memset(buffer0, 0, Stride * Stride);
    memset(buffer1, 0, Stride * Stride);

    if constexpr (RandomInit) {
        std::default_random_engine dre;
        for (int y = 0; y < Size; y++)
        for (int x = 0; x < Size; x++)
            buffer0[Stride + y * Stride + 1 + x] = dre() % 2;
    }
}
Field::~Field() {
    delete[] buffer0;
    delete[] buffer1;
}

void Field::clear() {
    for (uint i = 0; i < Stride*Stride; i++)
        buffer0[i] = 0;
    pix.fill();
    setPixmap(pix);
}

void Field::resizeEvent(QResizeEvent *event) {
    pix = QPixmap(event->size());
    painter p(pix);
    auto src = buffer0 + Stride + 1;
    for (int y = 0; y < Size; y++) {
        for (int x = 0; x < Size; x++)
            p.draw(x, y, *src++ ? Alive : Dead);
        src += 2;
    }
    setPixmap(pix);
}

void Field::mouse_move(int x, int y) {
    painter p(pix);
    if (mouse.x() != -1)
        p.draw(mouse.x(), mouse.y(),
            buffer0[Stride + 1 + mouse.x() + mouse.y() * Stride] ? Alive : Dead);

    if (x >= 0 && x < width() && y >= 0 && y < height()) {
        mouse = {
            x * Size / width(),
            y * Size / height() };

        uchar value;
        if (new_value == -1)
            value = buffer0[Stride + 1 + mouse.x() + mouse.y() * Stride];
        else {
            value = new_value;
            buffer0[Stride + 1 + mouse.x() + mouse.y() * Stride] = value;
        }

        p.draw(mouse.x(), mouse.y(),
            value ? AliveSel : DeadSel);
    }
    else mouse = { -1,-1 };
    setPixmap(pix);
}
void Field::leaveEvent(QEvent *event) {
    mouse_move(-1,-1);
}
void Field::mouseMoveEvent(QMouseEvent *event) {
    auto pos = event->position();
    mouse_move(pos.x(), pos.y());
}
void Field::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        new_value = 1;
    else if (event->button() == Qt::RightButton)
        new_value = 0;
    auto pos = event->position();
    mouse_move(pos.x(), pos.y());
}
void Field::mouseReleaseEvent(QMouseEvent *event) {
    new_value = -1;
}

void Field::iteration() {
    painter p(pix);
    auto src = buffer0 + Stride + 1;
    auto dst = buffer1 + Stride + 1;
    for (int y = 0; y < Size; y++) {
        for (int x = 0; x < Size; x++) {
            int neighbours = src[-1] + src[1] +
                src[-Stride- 1] + src[-Stride]+ src[-Stride+ 1] +
                src[Stride - 1] + src[Stride] + src[Stride + 1];

            uchar value = *src++;
            if (!value && neighbours == 3) {
                value = 1;
                p.draw(x, y, Alive);
            }
            else if (value && neighbours != 2 && neighbours != 3) {
                value = 0;
                p.draw(x, y, Dead);
            }
            *dst++ = value;
        }
        src += 2;
        dst += 2;
    }
    std::swap(buffer0, buffer1);
    setPixmap(pix);
}

