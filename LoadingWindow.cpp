#include "LoadingWindow.h"

LoadingWindow::LoadingWindow(int diameter, int diamBalls, int numBalls, bool useShadow, bool dragEnabled, bool centered)
{
    t = 0;
    this->dragEnabled = dragEnabled;

    //setup content
    QWidget *cw = new QWidget;
    cw->setLayout(new QGridLayout);
    cw->layout()->setSpacing(0);
    cw->layout()->setMargin(0);
    this->setCentralWidget(cw);

    //setup translucent window
    this->setStyleSheet("background-color:transparent");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);

    //setup loading widget
    lw = new LoadingWidget(diameter, diamBalls, numBalls, useShadow);
    cw->layout()->addWidget(lw);
    this->setGeometry(lw->geometry());

    //setup timer
    timer = new QTimer;

    //connect drag and timer
    connect(lw, SIGNAL(dragged(QPoint)), this, SLOT(dragged(QPoint)));
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));

    if (centered)
        center();
}

LoadingWindow::~LoadingWindow() {
    timer->stop();
    timer->deleteLater();
}

void LoadingWindow::center()
{
    QRect p = this->geometry();
    p.moveCenter(QApplication::desktop()->availableGeometry().center());
    this->move(p.topLeft());
}

void LoadingWindow::start()
{
    timer->start(1000 / 60); //start timer with ~60 fps
}

void LoadingWindow::stop()
{
    timer->stop();
}

void LoadingWindow::close()
{
    timer->stop();
    this->hide();
    this->deleteLater();
}

void LoadingWindow::setDrag(bool enabled)
{
    dragEnabled = enabled;
}

void LoadingWindow::dragged(QPoint delta)
{
    if (dragEnabled)
        this->move(this->pos() + delta);
}

void LoadingWindow::tick()
{
    lw->redraw(t++);
}
