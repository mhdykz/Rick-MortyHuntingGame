#include "dinosaur.h"
#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QDebug>

Dinosaur::Dinosaur(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem(parent), jump_height(0), isJumping(false), initialY(280) {
    qDebug() << "dinosaur added!!\n";

    image_dinosaur = QPixmap(":/images/images/dino1.png").scaled(100, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    image_dinosaur_jump = QPixmap(":/images/images/dino2.png").scaled(100, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setPixmap(image_dinosaur);
    setPos(100, initialY);

    jump_timer = new QTimer();
    connect(jump_timer, &QTimer::timeout, this, &Dinosaur::jump);

    fall_timer = new QTimer();
    connect(fall_timer, &QTimer::timeout, this, &Dinosaur::fall);

    air_timer = new QTimer();
    connect(air_timer, &QTimer::timeout, this, &Dinosaur::stayInAir);
}

void Dinosaur::jump() {
    if (jump_height < 140) {
        setPos(x(), y() - 10);
        jump_height += 10;
        setPixmap(image_dinosaur_jump);
    } else {
        jump_timer->stop();
        air_timer->start(500); // Stay in air for a moment
    }
}

void Dinosaur::stayInAir() {
    air_timer->stop();
    fall_timer->start(20);
}

void Dinosaur::fall() {
    if (y() < initialY) {
        setPos(x(), y() + 10);
        setPixmap(image_dinosaur_jump);
    } else {
        fall_timer->stop();
        isJumping = false;
        jump_height = 0;
        setPixmap(image_dinosaur);
    }
}

void Dinosaur::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space && !isJumping) {
        isJumping = true;
        jump_timer->start(20);
    }
}

Dinosaur::~Dinosaur() {
    delete jump_timer;
    delete fall_timer;
    delete air_timer;
}
