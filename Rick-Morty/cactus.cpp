#include "cactus.h"
#include "Ground.h"
#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QDebug>
int Cactus::cactus_count=0;
float Cactus::cspeed=10.0;

Cactus::Cactus(Ground* ground, QGraphicsItem* parent):QObject(), QGraphicsPixmapItem (parent),
    ground(ground),isAlive(true){
    qDebug()<< "cactus added!!\n";
    QPixmap image_cactus(":/images/images/cactus.png");

    QPixmap Scaled_image_cactus = image_cactus.scaled(100,300,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    setPixmap(Scaled_image_cactus);

    setPos(900,300);
    //cspeed = ground->gspeed;

    Cactus_thread_movement = new QTimer();
    connect(Cactus_thread_movement,&QTimer::timeout,this,&Cactus::move_this_cactus);
    Cactus_thread_movement->start(40);
}

void Cactus::move_this_cactus(){
    if (!isAlive) return;
    cspeed += 0.012;
    setPos(x()-(Cactus::cspeed), y());
    if (x() < -100) {
        scene()->removeItem(this);
        delete this;
    }
}

Cactus::~Cactus(){
    cactus_count--;
}
