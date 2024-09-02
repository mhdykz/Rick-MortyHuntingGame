#ifndef DINOSAUR_H
#define DINOSAUR_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>

class Dinosaur : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Dinosaur(QGraphicsItem* parent = nullptr);
    ~Dinosaur();
    void keyPressEvent(QKeyEvent *event);
    bool isJumping;
public slots:
    void jump();
    void stayInAir();
    void fall();

private:
    QTimer* jump_timer;
    QTimer* fall_timer;
    QTimer* air_timer;

    int jump_height;
    int initialY;

    QPixmap image_dinosaur;
    QPixmap image_dinosaur_jump;
};

#endif // DINOSAUR_H
