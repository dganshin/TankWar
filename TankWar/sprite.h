// 可移动的实体, 玩家, 敌人
#ifndef SPRITE_H
#define SPRITE_H
#include "Entity.h"
#include <QWidget>

#include <QVector2D>


class Sprite : public Entity
{
public:
    Sprite();
    Sprite(int x, int y, const QString& filename);
    void update()override;
    void draw(QPainter* painter)override;

public:
    QVector2D position; // 坐标
    QPixmap pixmap; // 精灵图片
};

#endif // SPRITE_H
