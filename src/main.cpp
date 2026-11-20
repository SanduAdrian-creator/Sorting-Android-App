#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "cuvinte/WordListModel.h"

#ifdef Q_OS_ANDROID
#include <QJniObject>

// Ascunde bara de navigare a sistemului (modul "immersive"). Bara reapare
// temporar când utilizatorul trage de la marginea de jos a ecranului.
static void hideSystemNavigationBar()
{
    QNativeInterface::QAndroidApplication::runOnAndroidMainThread([] {
        QJniObject activity = QNativeInterface::QAndroidApplication::context();
        if (!activity.isValid())
            return;

        QJniObject window = activity.callObjectMethod("getWindow", "()Landroid/view/Window;");
        QJniObject decorView = window.callObjectMethod("getDecorView", "()Landroid/view/View;");

        // HIDE_NAVIGATION | LAYOUT_STABLE | LAYOUT_HIDE_NAVIGATION | IMMERSIVE_STICKY
        constexpr int flags = 0x2 | 0x100 | 0x200 | 0x1000;
        decorView.callMethod<void>("setSystemUiVisibility", "(I)V", flags);
    });
}
#endif

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

#ifdef Q_OS_ANDROID
    hideSystemNavigationBar();
    // Sistemul readuce bara după ce aplicația pierde și recapătă focusul.
    QObject::connect(&app, &QGuiApplication::applicationStateChanged, &app,
                     [](Qt::ApplicationState state) {
                         if (state == Qt::ApplicationActive)
                             hideSystemNavigationBar();
                     });
#endif

    return app.exec();
}