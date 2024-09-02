#include "ground.h"
#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QDebug>
int Ground::ground_count=0;
float Ground:: gspeed =10.0;
Ground::Ground(QGraphicsItem* parent):QObject(), QGraphicsPixmapItem (parent){
    qDebug()<< "ground added!!\n";
    QPixmap image_ground(":/images/images/g.png");
    QPixmap Scaled_image_ground = image_ground.scaled(2000,100,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    setPixmap(Scaled_image_ground);

    // setPos(900,335);
    setPos(-100,350);
    //speed = 15.0;

    Ground_thread_movement = new QTimer();
    connect(Ground_thread_movement,&QTimer::timeout,this,&Ground::move_this_ground);
    Ground_thread_movement->start(40);

    setZValue(-1);
}



void Ground::move_this_ground(){
    int newX = x() - gspeed;
    if(newX < -900){
        newX = -100;
    }
    setPos(newX, y());
    gspeed += 0.004;
}

Ground::~Ground(){
}
