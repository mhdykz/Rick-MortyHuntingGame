#include "moon.h"
#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <stdlib.h>
#include <QRandomGenerator>
#include <QDebug>
int Moon::moon_count=0;
int RandomGenerator2(int min,int max){
    return QRandomGenerator::global()->bounded(min,max+1);
}

Moon::Moon(QGraphicsItem* parent):QObject(), QGraphicsPixmapItem (parent){
    qDebug()<< "moon added!!\n";

    QPixmap image_moon(":/images/images/moon.png");

    QPixmap Scaled_image_moon = image_moon.scaled(100,50,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    setPixmap(Scaled_image_moon);

    setPos(900,RandomGenerator2(1,15));
    speed = RandomGenerator2(1,2);

    Moon_thread_movement = new QTimer();
    connect(Moon_thread_movement,&QTimer::timeout,this,&Moon::move_this_moon);
    Moon_thread_movement->start(40);
    moon_count++;

}

void Moon::move_this_moon(){
    QPointF moonPos = this->pos();
    if (moonPos.x()<-80){
        qDebug()<< "moon deleted!!\n";
        scene()->removeItem(this);
        delete(this);
        return;
    }
    setPos(x()-speed,y());
}

Moon::~Moon(){
    moon_count--;
}
