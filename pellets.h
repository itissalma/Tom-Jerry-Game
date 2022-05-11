#ifndef PELLETS_H
#define PELLETS_H

#include <QGraphicsPixmapItem>

class pellets : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    pellets(int initialRow, int initialColumn);
};

#endif // PELLETS_H
