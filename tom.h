#ifndef TOM_H
#define TOM_H

#include <QGraphicsPixmapItem>
#include "cheese.h"
#include "jerry.h"
#include <QTimer>
#include <QVector>
const int COUNT = 365;
const int INFINITE = 999;

class tom : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QTimer *timer;
    qreal speed;
    static int row, column;
    int data[24][24];
    static int ogRow, ogCol;
public slots:
    void advancee();
public:
    int matrix[COUNT][COUNT];
    tom(int initialRow, int initialColumn,int d[24][24]);
    QVector<int> Dijkstra(int Graph[COUNT][COUNT], int startVertex);
    void move(QVector<int>paths);
    bool isathome(int roww, int columnn);
    static void goHome();
};

#endif // TOM_H
