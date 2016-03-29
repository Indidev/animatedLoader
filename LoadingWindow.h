#ifndef LOADINGWINDOW_H
#define LOADINGWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPoint>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>

#include "LoadingWidget.h"

namespace Ui {
class MainWindow;
}

class LoadingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoadingWindow(int diameter = 100, int diamBalls = 10, int numBalls = 12, bool useShadow = true, bool dragEnabled = true, bool centered = true);
    ~LoadingWindow();
    void center();
    void start();
    void stop();
    void close();
    void setDrag(bool enabled = true);

protected slots:
    void dragged(QPoint delta);
    void tick();

protected:
    int t;
    bool dragEnabled;
    LoadingWidget *lw;
    QTimer *timer;
};

#endif // LOADINGWINDOW_H
