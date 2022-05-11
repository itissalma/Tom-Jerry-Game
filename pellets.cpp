#include "pellets.h"

pellets::pellets(int initialRow, int initialColumn)
{
    // Set Image
    QPixmap image("pellet.png");
    image =image.scaledToWidth(40);
    image = image.scaledToHeight(40);
    setPixmap(image);
    // Set Position
    setPos(20 + 40 * initialColumn, 80 + 35 * initialRow);
}
