#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "cuvinte/WordListModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QCoreApplication::setOrganizationName("CuvinteApp");
    QCoreApplication::setApplicationName("CuvinteApp");

    WordListModel wordModel;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("wordModel", &wordModel);

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, [] { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("CuvinteApp", "Main");

    return app.exec();
}