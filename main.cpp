#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include "jerry.h"
#include "cheese.h"
#include "pellets.h"
#include <QApplication>
#include "tom.h"
#include <QTimer>
#include <QDebug>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QGraphicsView view;
  QGraphicsScene scene;



  view.setWindowTitle("Tom and Jerry Game");
  view.setFixedSize(1000,1000);
  QPalette pb;
  //pb.setBrush(QPalette::Background, q1);
  view.setPalette(pb);
  view.setBackgroundBrush(QBrush(Qt::cyan));
  //view.setMinimumSize(600,600);

  int board[24][24];
  QFile bfile("gameboard.txt");
  bfile.open(QIODevice::ReadOnly);
  QTextStream stream(&bfile);

  QString tempStr;
      for (int i = 0; i < 24; i++)
         { for (int j = 0; j < 24; j++)
          {stream >> tempStr;
              board[i][j] = tempStr.toInt();
  }
      }


  QPixmap q1("bricks.jpeg");
  q1=q1.scaledToHeight(40);
  q1=q1.scaledToWidth(40);
  QPixmap q2("line.png");
  q2=q2.scaledToHeight(40);
  q2=q2.scaledToWidth(40);

  QGraphicsPixmapItem boardimages[24][24];
  for (int i=0; i<24; i++){
      for (int j=0; j<24; j++){

          if (board[i][j]==-1)
              boardimages[i][j].setPixmap(q2);
          else
              boardimages[i][j].setPixmap(q1);

          boardimages[i][j].setPos(20+(40*j), 80+(35*i));
          scene.addItem(&boardimages[i][j]);

      }
  }



     cheese c1(2,22), c2(2, 2), c3(22, 2), c4(22,22);
     scene.addItem(&c1);
     scene.addItem(&c2);
     scene.addItem(&c3);
     scene.addItem(&c4);

     pellets p1(13, 1), p2(12, 21);
     scene.addItem(&p1);
     scene.addItem(&p2);

     tom t1(21, 10, board);
     scene.addItem(&t1);
     jerry j1(12, 11, board);
        scene.addItem(&j1);
        j1.setFlag(QGraphicsPixmapItem::ItemIsFocusable);
        j1.setFocus();


        j1.text= scene.addText("state: normal");
        QFont serifFont("Times", 15, QFont::Bold);
        j1.text->setDefaultTextColor(qBlue(64));
        j1.text->setFont(serifFont);
        j1.text->setPos(800,0);

        QPixmap jerry("jerry.png");
        jerry = jerry.scaledToWidth(40);
        jerry = jerry.scaledToHeight(40);
        j1.jerryimage.setPixmap(jerry);
        j1.jerryimage.setPos(800,35);
        scene.addItem(&j1.jerryimage);

        j1.ji1.setPixmap(jerry);
        j1.ji1.setPos(840,35);
        scene.addItem(&j1.ji1);

        j1.ji2.setPixmap(jerry);
        j1.ji2.setPos(880,35);
        scene.addItem(&j1.ji2);

        QVector<int>samplevec;
        //samplevec=t1.Dijkstra( t1.matrix,  0);
       // qDebug()<<samplevec[0]<<samplevec[1];

     QTimer timer;
    timer.connect(&timer,SIGNAL(timeout()),&t1, SLOT(advancee()) );
    timer.start(300);
    // timer.connect(&timer, SIGNAL(timeout()),scene, SLOT(advance()));




  view.setScene(&scene);
  view.show();
   return a.exec();
}
