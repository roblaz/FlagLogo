#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>

#include <QPainterPath>

#include <QTimer>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_radioButton_Orig_clicked();
    void on_radioButton_Night_clicked();

    void updatePos();

private:

    void createScene();

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *rec1, *rec2, *rec3, *rec4;
    QTimer *timer;
    QPen outlinePen;
    QList<QGraphicsItem *> itemsList;
    QGraphicsItemGroup *group;
    QPolygon polygon;

    int iX = 0,
        iY = 0; // Current pos for moving

    int speedX = 2,
        speedY = 1; // Moving direction

    int startX = 300.0, // Start pos for draw Logo
        startY = 200.0;

    int iOri = 1; // Flag Light/Night mode (1 = Light
};

#endif // MAINWINDOW_H
