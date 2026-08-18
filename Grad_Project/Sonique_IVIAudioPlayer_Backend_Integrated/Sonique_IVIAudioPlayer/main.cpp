#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "soniqueplaybackengine.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QGuiApplication::setApplicationName(QStringLiteral("Sonique IVI Audio"));
    QGuiApplication::setOrganizationName(QStringLiteral("Sonique"));

    QQmlApplicationEngine engine;
    SoniquePlaybackEngine playbackEngine;
    engine.rootContext()->setContextProperty(
            QStringLiteral("soniquePlaybackEngine"), &playbackEngine);
    engine.loadFromModule("IVIAudioPlayer", "Main");

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
