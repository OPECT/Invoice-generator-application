#include <QApplication>
#include "baengine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BAEngine engine;

    engine.run();
    return a.exec();
}
