#include "widget.h"
#include "Game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Widget w;
    // w.show();
    Game game;
    game.initGame(480, 640, "坦克大战");
    game.run();
    return a.exec();
}
