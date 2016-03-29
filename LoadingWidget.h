#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
#include <QColor>

#include <math.h>

class LoadingWidget : public QLabel
{
    Q_OBJECT
public:
    explicit LoadingWidget(int diameter = 100, int diamBalls = 10, int numBalls = 12, bool useShadow = true);

    /**
     * @brief redraw redraws the screen
     * @param time passed (200 = one roundabout)
     */
    void redraw(int t);

signals:
    /**
     * @brief dragged returns delta movement of drag events
     * @param delta delta of mouse movement
     */
    void dragged(QPoint delta);

public slots:

protected:
    //parameters
    int diam;
    int innerDiam;
    int num;
    bool shadow;
    QColor color;

    //drag event stuff
    bool mouseDown;
    QPoint lastPos;

    virtual void mouseMoveEvent(QMouseEvent * ev);
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void mouseReleaseEvent(QMouseEvent *);

    QColor calcColor(int t);

};

#endif // LOADINGWIDGET_H
