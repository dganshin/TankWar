// 可移动的实体, 玩家, 敌人
#ifndef SPRITE_H
#define SPRITE_H
#include "Entity.h"
#include <QWidget>

class Sprite : public Entity
{
public:
    Sprite();
    Sprite(int x, int y, cosnt Qstring&filename );
};

#endif // SPRITE_H
