#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    polygon << QPoint(startX, startY)
            << QPoint(startX, 480)
            << QPoint(240, 480)
            << QPoint(240, 230);

    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL( timeout() ), this, SLOT(updatePos() ));

    createScene();

    timer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createScene() {
    QPen outlinePen;
    QBrush blueBrush(Qt::blue);
    QBrush blackBrush(Qt::black);
    QBrush whiteBrush(Qt::white);
    QBrush brownBrush(QColor(128,0,0));
    QBrush logoBrush(QColor(23,145,255));

    QBrush brushLogo;

    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 800, 600);
    ui->graphicsView->setScene(scene);

    if (iOri == 1) { // Day
        outlinePen.setStyle(Qt::SolidLine);
        outlinePen.setColor(Qt::black);
        ui->graphicsView->setBackgroundBrush(whiteBrush);
        brushLogo = logoBrush;
    } else {  // Night
        outlinePen.setStyle(Qt::DotLine);
        outlinePen.setColor(Qt::white);
        ui->graphicsView->setBackgroundBrush(blackBrush);
        brushLogo = whiteBrush;
    }

    // Draw Logo
    QGraphicsTextItem *text = scene->addText("ESTONIA");
    //text->adjustSize();
    text->setDefaultTextColor(QColor(23,145,255)); //Qt::black); //
    text->setRotation(-90);
    text->setPos(210, 485);
    scene->addPolygon(polygon, outlinePen, brushLogo);
    scene->addEllipse(startX + 20,startY, 130, 130, outlinePen, brushLogo);
    scene->addEllipse(startX + 20,startY + 150, 130, 130, outlinePen, brushLogo);

    // Draw flag
    rec1 = scene->addRect(iX, iY, 80, 20, outlinePen, blueBrush);
    rec2 = scene->addRect(iX, iY+20, 80, 20, outlinePen, blackBrush);
    rec3 = scene->addRect(iX, iY+40, 80, 20, outlinePen, whiteBrush);
    rec4 = scene->addRect(iX, iY, 7, 130, outlinePen, brownBrush);

    // Create moving group (flag)
    group = scene->createItemGroup(itemsList);
    group->addToGroup(rec1);
    group->addToGroup(rec2);
    group->addToGroup(rec3);
    group->addToGroup(rec4);
}

void MainWindow::on_radioButton_Orig_clicked() // Day
{
    timer->stop();

    qreal x, y;
    x = group->x();
    y = group->y();

    iOri = 1;

    delete scene;
    createScene();

    group->setX(x);
    group->setY(y);

    timer->start(20);
}

void MainWindow::on_radioButton_Night_clicked()
{
    timer->stop();

    qreal x, y;
    x = group->x();
    y = group->y();

    iOri = 0;

    delete scene;
    createScene();

    group->setX(x);
    group->setY(y);

    timer->start(20);
}

void MainWindow::updatePos()
{
    qreal x, y;

    x = group->x();
    y = group->y();
    //qDebug() << "Ellips old pos: " << x << y;

    QRectF boundRec = group->boundingRect(); //get borders of flag
    qreal wid = boundRec.width();
    qreal heg = boundRec.height();

    if (x + wid >= 1000)
        speedX = -2; // Check rigth border

    if (x < -180)
        speedX = +2;       // Check left border

    x += speedX;

    if (y + heg >= 650)
        speedY=-1;
    if (y <= -50)
        speedY = +1;

    y += speedY;

    group->setX(x);
    group->setY(y);

}
