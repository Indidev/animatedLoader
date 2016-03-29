#include "LoadingWidget.h"

#define STEP M_PI / 400.0

LoadingWidget::LoadingWidget(int diameter, int diamBalls, int numBalls, bool useShadow)
{
    setStyleSheet("background-color:transparent;");
    mouseDown = false;
    diam = diameter;
    innerDiam = diamBalls;
    num = numBalls;
    shadow = useShadow;
    color = Qt::transparent;
    this->setGeometry(0, 0, diam * 2 + innerDiam, diam * 2 + innerDiam);

    //initial draw
    redraw(0);
}

void LoadingWidget::redraw(int t)
{
    //prepare image
    QPixmap pix(diam * 2 + innerDiam, diam * 2 + innerDiam);
    pix.fill(Qt::transparent);
    QPainter p(&pix);

    color = calcColor(t);

    //calc outer circle
    float outerAngle = -(float) t * 2.f * M_PI / (float) 200;
    int deltaX = diam + (int) (sin(outerAngle) * (float) diam / 2);
    int deltaY = diam + (int) (cos(outerAngle) * (float) diam / 2);

    //draw circles
    for (int i = 0; i < num; i++) {
        //calc base angle
        float angle = (float) i * 2.f * M_PI / (float) num;

        //rotate inner circle
        angle += fmod((float) t * M_PI / 100.f, 2.f * M_PI);

        int x = deltaX + (int) (sin(angle) * (float) diam / 2);
        int y = deltaY + (int) (cos(angle) * (float) diam / 2);

        //set outline transparent
        p.setPen(Qt::transparent);
        p.setRenderHint(QPainter::HighQualityAntialiasing);

        //draw shadow if enabled
        if (shadow) {
            int sX = x + 3;
            int sY = y + 3;

            p.setBrush(QBrush(QColor::fromRgba(qRgba(0, 0, 0, color.alphaF() * 100.f))));
            p.drawEllipse(sX, sY, innerDiam, innerDiam);
        }

        p.setBrush(QBrush(color));

        //draw point
        p.drawEllipse(x, y, innerDiam, innerDiam);

    }

    this->setPixmap(pix);
}

void LoadingWidget::mouseMoveEvent(QMouseEvent *ev)
{
    if (mouseDown) {
        QPoint delta = ev->screenPos().toPoint() - lastPos;
        lastPos = ev->screenPos().toPoint();
        emit dragged(delta);
    }
}

void LoadingWidget::mousePressEvent(QMouseEvent *ev)
{
    mouseDown = true;
    lastPos = ev->screenPos().toPoint();
}

void LoadingWidget::mouseReleaseEvent(QMouseEvent *)
{
    mouseDown = false;
}

QColor LoadingWidget::calcColor(int t)
{
    static int a = 0;

    if (a < 250)
        a = (int) (255.f * (float)t / 100.f);
    else
        a = 255;

    int h = 360.f * (float) (t % 800) / 800.f;//(int) (255.f * (1 + cos((float) t * STEP)) / 2);

    return QColor::fromHsv(h, 255, 255, a);
}
