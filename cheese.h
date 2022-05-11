#ifndef CHEESE_H
#define CHEESE_H

#include <QGraphicsPixmapItem>

class cheese : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    static int row;
    static int column;
public:
    cheese(int initialRow, int initialColumn);
    cheese();
    void setcheeserow(int rowvalue);
    void setcheesecolumn(int columnvalue);
    void setbacktoriginal(int columnvalue, int rowvalue);

    static int getrow(){
        return row;
    }
    static int getcolumn(){
        return column;
    }
};

#endif // CHEESE_H
