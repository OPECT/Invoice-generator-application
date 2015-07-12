#include <QApplication>
#include <QTranslator>
#include "baengine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load("InvoiceGenerator_ua");
    app.installTranslator(&translator);

    BAEngine engine;

    engine.run();
    return app.exec();
}
