#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QGuiApplication::setApplicationName(QStringLiteral("Sonique IVI Audio"));
    QGuiApplication::setOrganizationName(QStringLiteral("Sonique"));

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("IVIAudioPlayer", "Main");

    return app.exec();
}
