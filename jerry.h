#ifndef JERRY_H
#define JERRY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QList>
#include "cheese.h"
#include "pellets.h"
#include <QGraphicsScene>
#include <QString>
#include "tom.h"
#include <QTimer>
#include <QMediaPlayer>

class jerry : public QObject, public QGraphicsPixmapItem
{
   Q_OBJECT

private:
   char direction;
   static int row, column;
   int data[24][24];
   QString state;
   QChar state2;
   bool gotcheese[4];
   static int cheesecount;
   int lives;
   cheese* heldCheese;
   QTimer timerstate;
   QMediaPlayer *collisionsound;
   QMediaPlayer *winningsound;
   QMediaPlayer *losingsound;
   //tom *tomObj;
public:
   jerry(int initialRow, int initialColumn, int d[24][24]/*, tom* t*/);
   bool isathome();
   static int getrow(){
       return row;
   }
   static int getcolumn(){
       return column;
   }
   void adjuststate();
   void movecheese();
   static int getcheesecount();
   QGraphicsTextItem *text;
   QGraphicsPixmapItem jerryimage, ji1, ji2;

public slots:
   void keyPressEvent(QKeyEvent* event);
   void setState();


};

#endif // JERRY_H
