/****************************************************************************
** Meta object code from reading C++ file 'audioplayer.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../audioplayer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audioplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN11AudioPlayerE_t {};
} // unnamed namespace

template <> constexpr inline auto AudioPlayer::qt_create_metaobjectdata<qt_meta_tag_ZN11AudioPlayerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AudioPlayer",
        "QML.Element",
        "auto",
        "playingStateChanged",
        "",
        "positionChanged",
        "durationChanged",
        "muteStateChanged",
        "volumeChanged",
        "playlistChanged",
        "CurrentPlaylistIndexChanged",
        "radioModeChanged",
        "radioStationsChanged",
        "currentRadioStationNameChanged",
        "currentRadioStationCountryChanged",
        "radioReconnectingStateChanged",
        "usbModeChanged",
        "usbConnectedChanged",
        "usbRootPathChanged",
        "usbTracksChanged",
        "currentUsbTrackIndexChanged",
        "bluetoothModeChanged",
        "bluetoothAvailableChanged",
        "bluetoothScanningChanged",
        "bluetoothConnectedChanged",
        "bluetoothDevicesChanged",
        "bluetoothDeviceChanged",
        "bluetoothPlaybackStatusChanged",
        "bluetoothMediaControlsAvailableChanged",
        "metaDataChanged",
        "errorOccurred",
        "playPause",
        "stop",
        "next",
        "previous",
        "loadFolder",
        "folder_path",
        "useLocalLibrary",
        "formatTime",
        "ms",
        "playRadioStation",
        "radio_station_index",
        "addRadioStation",
        "name",
        "url",
        "loadUsbFolder",
        "useUsbLibrary",
        "playUsbTrack",
        "usb_track_index",
        "clearUsb",
        "useBluetoothSource",
        "refreshBluetoothDevices",
        "startBluetoothDiscovery",
        "stopBluetoothDiscovery",
        "connectBluetoothDevice",
        "bluetooth_device_index",
        "disconnectBluetoothDevice",
        "playing",
        "position",
        "duration",
        "muted",
        "volume",
        "playlist",
        "currentPlaylistIndex",
        "isRadioMode",
        "radioStations",
        "QVariantList",
        "currentRadioStationName",
        "currentRadioStationCountry",
        "radioReconnecting",
        "isUsbMode",
        "usbConnected",
        "usbRootPath",
        "usbTracks",
        "currentUsbTrackIndex",
        "isBluetoothMode",
        "bluetoothAvailable",
        "bluetoothScanning",
        "bluetoothConnected",
        "bluetoothDevices",
        "bluetoothDeviceName",
        "bluetoothDeviceAddress",
        "bluetoothPlaybackStatus",
        "bluetoothMediaControlsAvailable",
        "audioTitle",
        "audioAuthor",
        "audioAlbum",
        "audioType",
        "errorString"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'playingStateChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'positionChanged'
        QtMocHelpers::SignalData<void()>(5, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'durationChanged'
        QtMocHelpers::SignalData<void()>(6, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'muteStateChanged'
        QtMocHelpers::SignalData<void()>(7, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'volumeChanged'
        QtMocHelpers::SignalData<void()>(8, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'playlistChanged'
        QtMocHelpers::SignalData<void()>(9, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'CurrentPlaylistIndexChanged'
        QtMocHelpers::SignalData<void()>(10, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'radioModeChanged'
        QtMocHelpers::SignalData<void()>(11, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'radioStationsChanged'
        QtMocHelpers::SignalData<void()>(12, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'currentRadioStationNameChanged'
        QtMocHelpers::SignalData<void()>(13, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'currentRadioStationCountryChanged'
        QtMocHelpers::SignalData<void()>(14, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'radioReconnectingStateChanged'
        QtMocHelpers::SignalData<void()>(15, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'usbModeChanged'
        QtMocHelpers::SignalData<void()>(16, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'usbConnectedChanged'
        QtMocHelpers::SignalData<void()>(17, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'usbRootPathChanged'
        QtMocHelpers::SignalData<void()>(18, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'usbTracksChanged'
        QtMocHelpers::SignalData<void()>(19, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'currentUsbTrackIndexChanged'
        QtMocHelpers::SignalData<void()>(20, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'bluetoothModeChanged'
        QtMocHelpers::SignalData<void()>(21, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'bluetoothAvailableChanged'
        QtMocHelpers::SignalData<void()>(22, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'bluetoothScanningChanged'
        QtMocHelpers::SignalData<void()>(23, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'bluetoothConnectedChanged'
        QtMocHelpers::SignalData<void()>(24, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'bluetoothDevicesChanged'
        QtMocHelpers::SignalData<void()>(25, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'bluetoothDeviceChanged'
        QtMocHelpers::SignalData<void()>(26, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'bluetoothPlaybackStatusChanged'
        QtMocHelpers::SignalData<void()>(27, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'bluetoothMediaControlsAvailableChanged'
        QtMocHelpers::SignalData<void()>(28, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'metaDataChanged'
        QtMocHelpers::SignalData<void()>(29, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void()>(30, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'playPause'
        QtMocHelpers::MethodData<void()>(31, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'stop'
        QtMocHelpers::MethodData<void()>(32, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'next'
        QtMocHelpers::MethodData<void()>(33, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'previous'
        QtMocHelpers::MethodData<void()>(34, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'loadFolder'
        QtMocHelpers::MethodData<void(const QString &)>(35, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 36 },
        }}),
        // Method 'useLocalLibrary'
        QtMocHelpers::MethodData<void()>(37, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'formatTime'
        QtMocHelpers::MethodData<QString(qint64)>(38, 4, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::LongLong, 39 },
        }}),
        // Method 'playRadioStation'
        QtMocHelpers::MethodData<void(int)>(40, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 41 },
        }}),
        // Method 'addRadioStation'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(42, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 43 }, { QMetaType::QString, 44 },
        }}),
        // Method 'loadUsbFolder'
        QtMocHelpers::MethodData<void(const QString &)>(45, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 36 },
        }}),
        // Method 'useUsbLibrary'
        QtMocHelpers::MethodData<void()>(46, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'playUsbTrack'
        QtMocHelpers::MethodData<void(int)>(47, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 48 },
        }}),
        // Method 'clearUsb'
        QtMocHelpers::MethodData<void()>(49, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'useBluetoothSource'
        QtMocHelpers::MethodData<void()>(50, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'refreshBluetoothDevices'
        QtMocHelpers::MethodData<void()>(51, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'startBluetoothDiscovery'
        QtMocHelpers::MethodData<void()>(52, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'stopBluetoothDiscovery'
        QtMocHelpers::MethodData<void()>(53, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'connectBluetoothDevice'
        QtMocHelpers::MethodData<void(int)>(54, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 55 },
        }}),
        // Method 'disconnectBluetoothDevice'
        QtMocHelpers::MethodData<void()>(56, 4, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'playing'
        QtMocHelpers::PropertyData<bool>(57, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 0),
        // property 'position'
        QtMocHelpers::PropertyData<qint64>(58, QMetaType::LongLong, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 1),
        // property 'duration'
        QtMocHelpers::PropertyData<qint64>(59, QMetaType::LongLong, QMC::DefaultPropertyFlags | QMC::Final, 2),
        // property 'muted'
        QtMocHelpers::PropertyData<bool>(60, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::Final, 3),
        // property 'volume'
        QtMocHelpers::PropertyData<float>(61, QMetaType::Float, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 4),
        // property 'playlist'
        QtMocHelpers::PropertyData<QStringList>(62, QMetaType::QStringList, QMC::DefaultPropertyFlags | QMC::Final, 5),
        // property 'currentPlaylistIndex'
        QtMocHelpers::PropertyData<int>(63, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Final, 6),
        // property 'isRadioMode'
        QtMocHelpers::PropertyData<bool>(64, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 7),
        // property 'radioStations'
        QtMocHelpers::PropertyData<QVariantList>(65, 0x80000000 | 66, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Final, 8),
        // property 'currentRadioStationName'
        QtMocHelpers::PropertyData<QString>(67, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 9),
        // property 'currentRadioStationCountry'
        QtMocHelpers::PropertyData<QString>(68, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 10),
        // property 'radioReconnecting'
        QtMocHelpers::PropertyData<bool>(69, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 11),
        // property 'isUsbMode'
        QtMocHelpers::PropertyData<bool>(70, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 12),
        // property 'usbConnected'
        QtMocHelpers::PropertyData<bool>(71, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 13),
        // property 'usbRootPath'
        QtMocHelpers::PropertyData<QString>(72, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 14),
        // property 'usbTracks'
        QtMocHelpers::PropertyData<QStringList>(73, QMetaType::QStringList, QMC::DefaultPropertyFlags | QMC::Final, 15),
        // property 'currentUsbTrackIndex'
        QtMocHelpers::PropertyData<int>(74, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Final, 16),
        // property 'isBluetoothMode'
        QtMocHelpers::PropertyData<bool>(75, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 17),
        // property 'bluetoothAvailable'
        QtMocHelpers::PropertyData<bool>(76, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 18),
        // property 'bluetoothScanning'
        QtMocHelpers::PropertyData<bool>(77, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 19),
        // property 'bluetoothConnected'
        QtMocHelpers::PropertyData<bool>(78, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 20),
        // property 'bluetoothDevices'
        QtMocHelpers::PropertyData<QVariantList>(79, 0x80000000 | 66, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Final, 21),
        // property 'bluetoothDeviceName'
        QtMocHelpers::PropertyData<QString>(80, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 22),
        // property 'bluetoothDeviceAddress'
        QtMocHelpers::PropertyData<QString>(81, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 22),
        // property 'bluetoothPlaybackStatus'
        QtMocHelpers::PropertyData<QString>(82, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 23),
        // property 'bluetoothMediaControlsAvailable'
        QtMocHelpers::PropertyData<bool>(83, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 24),
        // property 'audioTitle'
        QtMocHelpers::PropertyData<QString>(84, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 25),
        // property 'audioAuthor'
        QtMocHelpers::PropertyData<QString>(85, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 25),
        // property 'audioAlbum'
        QtMocHelpers::PropertyData<QString>(86, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 25),
        // property 'audioType'
        QtMocHelpers::PropertyData<QString>(87, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 25),
        // property 'errorString'
        QtMocHelpers::PropertyData<QString>(88, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 26),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<AudioPlayer, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject AudioPlayer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11AudioPlayerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11AudioPlayerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11AudioPlayerE_t>.metaTypes,
    nullptr
} };

void AudioPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AudioPlayer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->playingStateChanged(); break;
        case 1: _t->positionChanged(); break;
        case 2: _t->durationChanged(); break;
        case 3: _t->muteStateChanged(); break;
        case 4: _t->volumeChanged(); break;
        case 5: _t->playlistChanged(); break;
        case 6: _t->CurrentPlaylistIndexChanged(); break;
        case 7: _t->radioModeChanged(); break;
        case 8: _t->radioStationsChanged(); break;
        case 9: _t->currentRadioStationNameChanged(); break;
        case 10: _t->currentRadioStationCountryChanged(); break;
        case 11: _t->radioReconnectingStateChanged(); break;
        case 12: _t->usbModeChanged(); break;
        case 13: _t->usbConnectedChanged(); break;
        case 14: _t->usbRootPathChanged(); break;
        case 15: _t->usbTracksChanged(); break;
        case 16: _t->currentUsbTrackIndexChanged(); break;
        case 17: _t->bluetoothModeChanged(); break;
        case 18: _t->bluetoothAvailableChanged(); break;
        case 19: _t->bluetoothScanningChanged(); break;
        case 20: _t->bluetoothConnectedChanged(); break;
        case 21: _t->bluetoothDevicesChanged(); break;
        case 22: _t->bluetoothDeviceChanged(); break;
        case 23: _t->bluetoothPlaybackStatusChanged(); break;
        case 24: _t->bluetoothMediaControlsAvailableChanged(); break;
        case 25: _t->metaDataChanged(); break;
        case 26: _t->errorOccurred(); break;
        case 27: _t->playPause(); break;
        case 28: _t->stop(); break;
        case 29: _t->next(); break;
        case 30: _t->previous(); break;
        case 31: _t->loadFolder((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 32: _t->useLocalLibrary(); break;
        case 33: { QString _r = _t->formatTime((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 34: _t->playRadioStation((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 35: _t->addRadioStation((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 36: _t->loadUsbFolder((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 37: _t->useUsbLibrary(); break;
        case 38: _t->playUsbTrack((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 39: _t->clearUsb(); break;
        case 40: _t->useBluetoothSource(); break;
        case 41: _t->refreshBluetoothDevices(); break;
        case 42: _t->startBluetoothDiscovery(); break;
        case 43: _t->stopBluetoothDiscovery(); break;
        case 44: _t->connectBluetoothDevice((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 45: _t->disconnectBluetoothDevice(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::playingStateChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::positionChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::durationChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::muteStateChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::volumeChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::playlistChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::CurrentPlaylistIndexChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::radioModeChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::radioStationsChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::currentRadioStationNameChanged, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::currentRadioStationCountryChanged, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::radioReconnectingStateChanged, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::usbModeChanged, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::usbConnectedChanged, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::usbRootPathChanged, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::usbTracksChanged, 15))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::currentUsbTrackIndexChanged, 16))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::bluetoothModeChanged, 17))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::bluetoothAvailableChanged, 18))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::bluetoothScanningChanged, 19))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::bluetoothConnectedChanged, 20))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::bluetoothDevicesChanged, 21))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::bluetoothDeviceChanged, 22))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::bluetoothPlaybackStatusChanged, 23))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::bluetoothMediaControlsAvailableChanged, 24))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::metaDataChanged, 25))
            return;
        if (QtMocHelpers::indexOfMethod<void (AudioPlayer::*)()>(_a, &AudioPlayer::errorOccurred, 26))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->getPlayingState(); break;
        case 1: *reinterpret_cast<qint64*>(_v) = _t->getPosition(); break;
        case 2: *reinterpret_cast<qint64*>(_v) = _t->getDuration(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->getMuteState(); break;
        case 4: *reinterpret_cast<float*>(_v) = _t->getVolume(); break;
        case 5: *reinterpret_cast<QStringList*>(_v) = _t->getPlaylist(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->getCurrentPlaylistIndex(); break;
        case 7: *reinterpret_cast<bool*>(_v) = _t->getRadioMode(); break;
        case 8: *reinterpret_cast<QVariantList*>(_v) = _t->getRadioStations(); break;
        case 9: *reinterpret_cast<QString*>(_v) = _t->getCurrentRadioStationName(); break;
        case 10: *reinterpret_cast<QString*>(_v) = _t->getCurrentStationCountry(); break;
        case 11: *reinterpret_cast<bool*>(_v) = _t->getRadioReconnectingState(); break;
        case 12: *reinterpret_cast<bool*>(_v) = _t->getUsbMode(); break;
        case 13: *reinterpret_cast<bool*>(_v) = _t->getUsbConnected(); break;
        case 14: *reinterpret_cast<QString*>(_v) = _t->getUsbRootPath(); break;
        case 15: *reinterpret_cast<QStringList*>(_v) = _t->getUsbTracks(); break;
        case 16: *reinterpret_cast<int*>(_v) = _t->getCurrentUsbTrackIndex(); break;
        case 17: *reinterpret_cast<bool*>(_v) = _t->getBluetoothMode(); break;
        case 18: *reinterpret_cast<bool*>(_v) = _t->getBluetoothAvailable(); break;
        case 19: *reinterpret_cast<bool*>(_v) = _t->getBluetoothScanning(); break;
        case 20: *reinterpret_cast<bool*>(_v) = _t->getBluetoothConnected(); break;
        case 21: *reinterpret_cast<QVariantList*>(_v) = _t->getBluetoothDevices(); break;
        case 22: *reinterpret_cast<QString*>(_v) = _t->getBluetoothDeviceName(); break;
        case 23: *reinterpret_cast<QString*>(_v) = _t->getBluetoothDeviceAddress(); break;
        case 24: *reinterpret_cast<QString*>(_v) = _t->getBluetoothPlaybackStatus(); break;
        case 25: *reinterpret_cast<bool*>(_v) = _t->getBluetoothMediaControlsAvailable(); break;
        case 26: *reinterpret_cast<QString*>(_v) = _t->getAudioTitle(); break;
        case 27: *reinterpret_cast<QString*>(_v) = _t->getAudioAuthor(); break;
        case 28: *reinterpret_cast<QString*>(_v) = _t->getAudioAlbum(); break;
        case 29: *reinterpret_cast<QString*>(_v) = _t->getAudioType(); break;
        case 30: *reinterpret_cast<QString*>(_v) = _t->getErrorString(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setPosition(*reinterpret_cast<qint64*>(_v)); break;
        case 3: _t->setMuteState(*reinterpret_cast<bool*>(_v)); break;
        case 4: _t->setVolume(*reinterpret_cast<float*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *AudioPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AudioPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11AudioPlayerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AudioPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 46)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 46;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 46)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 46;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    }
    return _id;
}

// SIGNAL 0
void AudioPlayer::playingStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AudioPlayer::positionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AudioPlayer::durationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AudioPlayer::muteStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void AudioPlayer::volumeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void AudioPlayer::playlistChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void AudioPlayer::CurrentPlaylistIndexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void AudioPlayer::radioModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void AudioPlayer::radioStationsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void AudioPlayer::currentRadioStationNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void AudioPlayer::currentRadioStationCountryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void AudioPlayer::radioReconnectingStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void AudioPlayer::usbModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void AudioPlayer::usbConnectedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void AudioPlayer::usbRootPathChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void AudioPlayer::usbTracksChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void AudioPlayer::currentUsbTrackIndexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void AudioPlayer::bluetoothModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}

// SIGNAL 18
void AudioPlayer::bluetoothAvailableChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 18, nullptr);
}

// SIGNAL 19
void AudioPlayer::bluetoothScanningChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void AudioPlayer::bluetoothConnectedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}

// SIGNAL 21
void AudioPlayer::bluetoothDevicesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 21, nullptr);
}

// SIGNAL 22
void AudioPlayer::bluetoothDeviceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 22, nullptr);
}

// SIGNAL 23
void AudioPlayer::bluetoothPlaybackStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 23, nullptr);
}

// SIGNAL 24
void AudioPlayer::bluetoothMediaControlsAvailableChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 24, nullptr);
}

// SIGNAL 25
void AudioPlayer::metaDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 25, nullptr);
}

// SIGNAL 26
void AudioPlayer::errorOccurred()
{
    QMetaObject::activate(this, &staticMetaObject, 26, nullptr);
}
QT_WARNING_POP
