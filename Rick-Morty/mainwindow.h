#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include "moon.h"
#include "cloud.h"
#include "ground.h"
#include "cactus.h"
#include "dinosaur.h"

class MainWindow : public QGraphicsView {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent * event);
    void gameOver();
public slots:
    void add_cloud_or_moon();
    void add_ground();
    void add_cactus();
    void printSpeeds();
    Cactus* getCactusInstance();
    void checkCollision();

private:
    QGraphicsScene *display;
    QTimer* check_cloud_count;
    QTimer* check_moon_count;
    QTimer* check_ground_count;
    QTimer* check_cactus_count;
    QTimer* collisionTimer;

    bool isNightMode;
    Ground* currentGround;
    Cactus* currentCactus;
    Dinosaur* dinosaur;

    QGraphicsTextItem* groundSpeedTextItem;
    QGraphicsTextItem* cactusSpeedTextItem;
    QGraphicsTextItem* gameOverTextItem;
};

#endif // MAINWINDOW_H
