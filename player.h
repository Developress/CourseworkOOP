#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Player:public QObject, public QGraphicsPixmapItem
{
public:
    Player();
    void keyPressEvent(QKeyEvent *event);
};

#endif // PLAYER_H
