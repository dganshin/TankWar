#include "Game.h"
#include <QTimer>
#include <QDebug>
#include <QIcon>
#include <QPainter>
#include "sprite.h"


Sprite *player;
Game::Game(QWidget *parent) : QWidget{parent} {
    QTimer * timer = new QTimer(this);
    timer->callOnTimeout(this, [=](){ // lamda表达式
        // 更新数据
        updateGame();
        // 绘图
        update();
    });
    timer->start(1000/60); // 60帧
}

void Game::initGame(int w, int h, const QString &title, const QIcon &icon) {
    setFixedSize(w, h);
    setWindowTitle(title);
    if (!icon.isNull()){
        setWindowIcon(icon);
    }
}

void Game::run() { this->show(); }

void Game::updateGame()
{
    qInfo()<<__FUNCTION__;
}

void Game::drawGame()
{
    qInfo()<<__FUNCTION__;
}

void Game::paintEvent(QPaintEvent *ev)
{
    qInfo()<<__FUNCTION__;
}


