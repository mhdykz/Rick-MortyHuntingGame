// press space for jump & c for chang conition
#include "mainwindow.h"
#include "cloud.h"
#include "moon.h"
#include "ground.h"
#include "cactus.h"
#include "dinosaur.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QGraphicsView(parent), isNightMode(false), currentGround(nullptr),
    currentCactus(nullptr), dinosaur(nullptr)
{
    display = new QGraphicsScene(this);
    setScene(display);
    setFixedSize(900, 500);
    setSceneRect(0, 0, 800, 400);
    display->setBackgroundBrush(QBrush(Qt::red));

    dinosaur = new Dinosaur();
    display->addItem(dinosaur);

    check_ground_count = new QTimer();
    connect(check_ground_count, &QTimer::timeout, this, &MainWindow::add_ground);
    check_ground_count->start(40);

    check_cloud_count = new QTimer();
    connect(check_cloud_count, &QTimer::timeout, this, &MainWindow::add_cloud_or_moon);
    check_cloud_count->start(40);

    check_cactus_count = new QTimer();
    connect(check_cactus_count, &QTimer::timeout, this, &MainWindow::add_cactus);
    check_cactus_count->start(2000);

    groundSpeedTextItem = new QGraphicsTextItem();
    groundSpeedTextItem->setDefaultTextColor(Qt::blue);
    groundSpeedTextItem->setFont(QFont("Arial", 14));
    groundSpeedTextItem->setPos(-10, 200);
    display->addItem(groundSpeedTextItem);

    cactusSpeedTextItem = new QGraphicsTextItem();
    cactusSpeedTextItem->setDefaultTextColor(Qt::blue);
    cactusSpeedTextItem->setFont(QFont("Arial", 14));
    cactusSpeedTextItem->setPos(-10, 220);
    display->addItem(cactusSpeedTextItem);

    collisionTimer = new QTimer(this);
    connect(collisionTimer, &QTimer::timeout, this, &MainWindow::checkCollision);
    collisionTimer->start(50);

    QTimer* speedUpdateTimer = new QTimer(this);
    connect(speedUpdateTimer, &QTimer::timeout, this, &MainWindow::printSpeeds);
    speedUpdateTimer->start(1000);
}

void MainWindow::printSpeeds() {
    if (currentGround != nullptr) {
        QString groundSpeed = "Ground speed: " + QString::number(currentGround->gspeed);
        groundSpeedTextItem->setPlainText(groundSpeed);
    }
    if (Cactus::cactus_count > 0 && currentCactus != nullptr) {
        QString cactusSpeed = "Score: " + QString::number(currentCactus->cspeed);
        cactusSpeedTextItem->setPlainText(cactusSpeed);
    }
}

void MainWindow::add_cloud_or_moon() {
    if (isNightMode) {
        if (Moon::moon_count < 1) {
            Moon* newMoon = new Moon();
            display->addItem(newMoon);
        }
    } else {
        if (Cloud::cloud_count < 10) {
            Cloud* newCloud = new Cloud();
            display->addItem(newCloud);
        }
    }
}

void MainWindow::add_ground() {
    if (currentGround == nullptr) {
        currentGround = new Ground();
        display->addItem(currentGround);
        connect(check_ground_count, &QTimer::timeout, currentGround, &Ground::move_this_ground);
    }
}

void MainWindow::add_cactus() {
    if (Cactus::cactus_count < 1) {
        currentCactus = new Cactus(currentGround);
        display->addItem(currentCactus);
        Cactus::cactus_count++;
    }
}

Cactus* MainWindow::getCactusInstance() {
    return currentCactus;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_C) {
        isNightMode = !isNightMode;
        if (isNightMode) {
            if (check_cloud_count != nullptr) {
                check_cloud_count->stop();
                delete check_cloud_count;
                check_cloud_count = nullptr;
            }
            check_moon_count = new QTimer();
            connect(check_moon_count, &QTimer::timeout, this, &MainWindow::add_cloud_or_moon);
            check_moon_count->start(40);
            display->setBackgroundBrush(QBrush(Qt::black));
        } else {
            if (check_moon_count != nullptr) {
                check_moon_count->stop();
                delete check_moon_count;
                check_moon_count = nullptr;
            }
            check_cloud_count = new QTimer();
            connect(check_cloud_count, &QTimer::timeout, this, &MainWindow::add_cloud_or_moon);
            check_cloud_count->start(40);
            display->setBackgroundBrush(QBrush(Qt::red));
        }
    } else {
        dinosaur->keyPressEvent(event);
    }
}

void MainWindow::checkCollision() {
    QList<QGraphicsItem*> collidingItems = dinosaur->collidingItems();
    for (QGraphicsItem* item : collidingItems) {
        if (typeid(*item) == typeid(Cactus)) {
            gameOver();
            return;
        }
    }
}

void MainWindow::gameOver() {
    // Stop all timers
    if (check_cloud_count != nullptr) check_cloud_count->stop();
    if (check_moon_count != nullptr) check_moon_count->stop();
    if (check_ground_count != nullptr) check_ground_count->stop();
    if (check_cactus_count != nullptr) check_cactus_count->stop();
    collisionTimer->stop();

    // Display Game Over text
    gameOverTextItem = new QGraphicsTextItem("Game Over");
    gameOverTextItem->setDefaultTextColor(Qt::white);
    gameOverTextItem->setFont(QFont("Arial", 48));
    gameOverTextItem->setPos(300, 150);
    display->addItem(gameOverTextItem);
}

MainWindow::~MainWindow() {
    if (check_cloud_count != nullptr) {
        delete check_cloud_count;
    }
    if (check_moon_count != nullptr) {
        delete check_moon_count;
    }
    if (check_ground_count != nullptr) {
        delete check_ground_count;
    }
    if (check_cactus_count != nullptr) {
        delete check_cactus_count;
    }
}
