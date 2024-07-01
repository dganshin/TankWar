#include "Game.h"

Game::Game(QWidget *parent) : QWidget{parent} {}

void Game::run() { this->show(); }

void Game::initGame(int w, int h, const QString &title, const QIcon &icon) {
  setFixedSize(w, h);
  setWindowTitle(title);
  if (!icon.isNull()){
      setWindowIcon(icon);
  }
}
