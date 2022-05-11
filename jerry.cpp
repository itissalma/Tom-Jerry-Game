#include "jerry.h"
#include "cheese.h"
#include "tom.h"
#include <QMessageBox>
#include <QProcess>
#include <QApplication>
#include <QDebug>
#include <QMediaPlayer>
int jerry::row=12;
int jerry::column = 11;
jerry::jerry(int initialRow, int initialColumn, int d[24][24]/*, tom* t)
: tomObj(t)*/)
{
    for (int i = 0; i < 24; i++)
            for (int j = 0; j < 24; j++)
                data[i][j] = d[i][j];
        row=initialRow;
        column = initialColumn;
        // Set the Images of jerry (w/o , w/ cheese)

        QPixmap image1("jerry.png");
        image1 = image1.scaledToWidth(40);
        image1 = image1.scaledToHeight(40);
        setPixmap(image1);
        state2 = 'n';

        // Set Position
        setPos(20 + 40 * column, 80 + 35 * row);
        row = initialRow;
        column = initialColumn;
        state="normal";

        for (int i=0; i<4; i++)
        gotcheese[i]=false;

        lives=3;
        heldCheese = nullptr;

        QMediaPlayer * bgmusic=new QMediaPlayer();
        bgmusic->setMedia(QUrl("qrc:/sounds/backgroundmusic.mp3"));
        bgmusic->play();

        collisionsound= new QMediaPlayer();
        collisionsound->setMedia(QUrl("qrc:/sounds/boomboom"));
        winningsound=new QMediaPlayer();
        winningsound->setMedia(QUrl("qrc:/sounds/winning.mp3"));
        losingsound=new QMediaPlayer();
        losingsound->setMedia(QUrl("qrc:/sounds/losing"));

}
bool jerry::isathome(){
    if((row==11&&column==11)||(row==11&&column==12)||(row==12&&column==11)||(row==12&&column==12))
        return true;
    else
        return false;
}
// Row and column functions
void jerry::keyPressEvent(QKeyEvent* event)
{

    if (event->key() == Qt::Key_Up && data[row - 1][column] != -1)
    {
        row--;
    }
    else if (event->key() == Qt::Key_Down && data[row + 1][column] != -1)
    {
        row++;
    }
    else if (event->key() == Qt::Key_Right && data[row][column + 1] != -1)
    {
        column++;
    }
    else if (event->key() == Qt::Key_Left && data[row][column - 1] != -1)
    {
        column--;
    }
    setPos(20 + 40 * column, 80 + 35 * row);

    QList<QGraphicsItem*> items = collidingItems();

       for (int i = 0; i < items.size(); i++)
       {
           if (typeid(*items[i]) == typeid(pellets))
           {
               scene()->removeItem(items[i]);
               state="invincible";
               timerstate.connect(&timerstate,SIGNAL(timeout()),this, SLOT(setState()));
               timerstate.start(12000);
               scene()->removeItem(text);
               text= scene()->addText("state: invincible");
               QFont serifFont("Times", 15, QFont::Bold);
               text->setDefaultTextColor(qBlue(64));
               text->setFont(serifFont);
               text->setPos(800,0);

           }

           if (typeid(*items[i]) == typeid(cheese))
           {
               if(heldCheese == nullptr&&(!isathome()))
               {
                   scene()->removeItem(items[i]);
                   heldCheese = (cheese*)items[i];
                   cheesecount++;
                   gotcheese[cheesecount]=true;
                   QPixmap image2("jerrywithcheese.png");
                   image2 = image2.scaledToWidth(40);
                   image2 = image2.scaledToHeight(40);
                   setPixmap(image2);
                   setPos(20 + 40 * column, 80 + 35 * row);
                   adjuststate();
               }
           }

           if (typeid(*items[i]) == typeid(tom)&&state=="normal")
           {
               lives--;
               row=12;
               column=12;
               if(/*gotcheese[cheesecount]==true*/ heldCheese != nullptr){ //new part
                   scene()->addItem(heldCheese);
                   heldCheese = nullptr;
                   gotcheese[cheesecount]=false;
                   cheesecount--;
                   //move the cheese back to its original place
                   QPixmap image4("jerry.png");
                   image4 = image4.scaledToWidth(40);
                   image4 = image4.scaledToHeight(40);
                   setPixmap(image4);
                   setPos(20 + 40 * column, 80 + 35 * row);
               }
               //tom goes back to home
               tom::goHome();
               if (lives == 2)
               scene()->removeItem(&ji2);
               if (lives == 1)
               scene()->removeItem(&ji1);
               if (lives == 0)
               scene()->removeItem(&jerryimage);
               setPos(20 + 40 * column, 80 + 35 * row);

               if(collisionsound->state()==QMediaPlayer::PlayingState){
                   collisionsound->setPosition(0);
               }
               else if(collisionsound->state()==QMediaPlayer::StoppedState){
                   collisionsound->play();
               }
           }

           if (typeid(*items[i]) == typeid(tom)&&state!="normal"){
               tom::goHome();
           }
        }




    if(isathome()) // jerry's home
    {
        if(heldCheese != nullptr)
        {
            scene()->addItem(heldCheese);
            heldCheese->setPos(20 + 40 * column, 80 + 35 * row);
            heldCheese = nullptr;
            QPixmap image3("jerry.png");
            image3 = image3.scaledToWidth(40);
            image3 = image3.scaledToHeight(40);
            setPixmap(image3);
            setPos(20 + 40 * column, 80 + 35 * row);

        }
    }
    adjuststate();
}

void jerry::adjuststate(){
    if(lives==0){
        if(losingsound->state()==QMediaPlayer::PlayingState){
            losingsound->setPosition(0);
        }
        else if(losingsound->state()==QMediaPlayer::StoppedState){
            losingsound->play();
        }
        QMessageBox msgBox;
        msgBox.setText("Game Over Sucker, you Lost!");
        msgBox.setInformativeText("Do you want to play again?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        if(msgBox.exec() == QMessageBox::Yes){
            qApp->quit();
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        }

    }
    if(cheesecount==4&&(isathome()) ){
        if(winningsound->state()==QMediaPlayer::PlayingState){
            winningsound->setPosition(0);
        }
        else if(winningsound->state()==QMediaPlayer::StoppedState){
            winningsound->play();
        }
        QMessageBox msgBox;
        msgBox.setText("You won!");
        msgBox.setInformativeText("Do you want to play again?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        if(msgBox.exec() == QMessageBox::Yes){
            qApp->quit();
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        }

    }
}

int jerry::cheesecount=0;

int jerry::getcheesecount(){
    return cheesecount;
}

void jerry::setState()
{

    state = "normal";
    timerstate.stop();
    scene()->removeItem(text);
    text= scene()->addText("state: normal"); // to go from invincible back to normal
    QFont serifFont("Times", 15, QFont::Bold);
    text->setDefaultTextColor(qBlue(64));
    text->setFont(serifFont);
    text->setPos(800,0);
}
