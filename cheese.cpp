#include "cheese.h"

int cheese::row=0;
int cheese::column=0;
cheese::cheese(int initialRow, int initialColumn)
{
    // Set Image
    QPixmap image("cheese.png");
    image =image.scaledToWidth(40);
    image = image.scaledToHeight(40);
    setPixmap(image);
    row=initialRow;
    column=initialColumn;
    // Set Position
    setPos(20 + 40 * initialColumn, 80 + 35 * initialRow);
}
