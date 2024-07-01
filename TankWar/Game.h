#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QIcon>

class QPainter;

class Game : public QWidget {
    Q_OBJECT
public:
    explicit Game(QWidget *parent = nullptr);
    // 初始化游戏
    void initGame(int w, int h, const QString &title, const QIcon & = QIcon());

    // 运行游戏
    void run();

    // 更新游戏
    void updateGame();
    // 绘制游戏

    void drawGame();

    // 清理游戏
    void cleanGame(QPainter *painter);
protected:
    void paintEvent(QPaintEvent * ev)override;
};

#endif // GAME_H
