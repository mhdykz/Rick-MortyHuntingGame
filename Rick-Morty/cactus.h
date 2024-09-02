#ifndef CACTUS_H
#define CACTUS_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include "ground.h"

class Cactus : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    static int cactus_count;
    bool isAlive;
    Cactus(Ground* ground, QGraphicsItem* parent=nullptr);
    ~Cactus();
    static float cspeed;

public slots:
    void move_this_cactus();

private:
    QTimer* Cactus_thread_movement;
    Ground* ground;
};

#endif // CACTUS_H
