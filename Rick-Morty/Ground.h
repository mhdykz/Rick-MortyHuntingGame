#ifndef GROUND_H
#define GROUND_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class Ground : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Ground(QGraphicsItem* parent=nullptr);
    static float gspeed;

    ~Ground();
    static int ground_count;
public slots:
    void move_this_ground();

private:
    QTimer* Ground_thread_movement;
};

#endif // GROUND_H
