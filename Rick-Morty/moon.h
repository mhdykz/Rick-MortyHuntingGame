#ifndef MOON_H
#define MOON_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class Moon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    static int moon_count;

    Moon(QGraphicsItem* parent=nullptr);
    ~Moon();

public slots:
    void move_this_moon();

private:
    int speed;
    QTimer* Moon_thread_movement;
};

#endif // MOON_H
