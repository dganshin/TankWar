#include "sprite.h"

Sprite::Sprite()
{}

Sprite::Sprite(int x, int y, const QString &filename)
    :position(x, y)
{
    pixmap.load(filename);
}

void Sprite::update()
{

}

void Sprite::draw(QPainter *painter)
{
    painter->drawPixmap(position.toPoint(), pixmap);
}
