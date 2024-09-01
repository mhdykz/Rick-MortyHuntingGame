#include "cloud.h"
#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <stdlib.h>
#include <QRandomGenerator>
#include <QDebug>
int Cloud::cloud_count=0;
int RandomGenerator(int min,int max){
    return QRandomGenerator::global()->bounded(min,max+1);
}
Cloud::Cloud(QGraphicsItem* parent):QObject(), QGraphicsPixmapItem (parent){
    qDebug()<< "cloud added!!\n";

    QPixmap image_cloud(":/images/images/cloud.png");

    QPixmap Scaled_image_cloud = image_cloud.scaled(100,50,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    setPixmap(Scaled_image_cloud);

    setPos(900,RandomGenerator(1,15));
    speed = RandomGenerator(3,10);

    Cloud_thread_movement = new QTimer();
    connect(Cloud_thread_movement,&QTimer::timeout,this,&Cloud::move_this_cloud);
    Cloud_thread_movement->start(40);

    cloud_count++;
}
void Cloud::move_this_cloud(){
    QPointF cloudPos = this->pos();
    if (cloudPos.x()<-80){
        qDebug()<< "cloud deleted!!\n";
        scene()->removeItem(this);
        delete(this);
        return;
    }
    setPos(x()-speed,y());
}

Cloud::~Cloud(){
    cloud_count--;
}
