#ifndef CLOUD_H
#define CLOUD_H

#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class Cloud :public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    static int cloud_count;
    Cloud(QGraphicsItem* parent=nullptr);
    ~Cloud();

public slots:
    void move_this_cloud();
private:
    int speed;
    QTimer* Cloud_thread_movement;
};

#endif // CLOUD_H
