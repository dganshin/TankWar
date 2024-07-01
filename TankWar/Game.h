#ifndef GAME_H
#define GAME_H

#include <QWidget>

class Game : public QWidget {
  Q_OBJECT
public:
  explicit Game(QWidget *parent = nullptr);
  // 初始化游戏
  void initGame(int w, int h, const QString &title, const QIcon & = QIcon());

  // 运行游戏
  void run();

  // 清理游戏
  void cleanGame();
signals:
};

#endif // GAME_H
