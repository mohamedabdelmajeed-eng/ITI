/****************************************************************************
** Meta object code from reading C++ file 'soniqueplaybackengine.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../soniqueplaybackengine.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'soniqueplaybackengine.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN21SoniquePlaybackEngineE_t {};
} // unnamed namespace

template <> constexpr inline auto SoniquePlaybackEngine::qt_create_metaobjectdata<qt_meta_tag_ZN21SoniquePlaybackEngineE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SoniquePlaybackEngine",
        "playbackActiveChanged",
        "",
        "playheadChanged",
        "mediaLengthChanged",
        "silenceEnabledChanged",
        "outputLevelChanged",
        "localTracksChanged",
        "selectedTrackIndexChanged",
        "trackDetailsChanged",
        "playbackErrorChanged",
        "radioActiveChanged",
        "stationCatalogChanged",
        "tunedStationChanged",
        "streamBufferingChanged",
        "togglePlayback",
        "stopPlayback",
        "playNext",
        "playPrevious",
        "seekTo",
        "milliseconds",
        "loadLocalFolder",
        "QUrl",
        "folderUrl",
        "useLocalLibrary",
        "formatClock",
        "tuneStation",
        "stationIndex",
        "saveStation",
        "name",
        "country",
        "streamUrl",
        "playbackActive",
        "playheadMs",
        "mediaLengthMs",
        "silenceEnabled",
        "outputLevel",
        "localTracks",
        "selectedTrackIndex",
        "trackTitle",
        "trackArtist",
        "trackAlbum",
        "trackGenre",
        "lastPlaybackError",
        "radioActive",
        "stationCatalog",
        "QVariantList",
        "tunedStationName",
        "tunedStationCountry",
        "streamBuffering"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'playbackActiveChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'playheadChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'mediaLengthChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'silenceEnabledChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'outputLevelChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'localTracksChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'selectedTrackIndexChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'trackDetailsChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'playbackErrorChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'radioActiveChanged'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'stationCatalogChanged'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'tunedStationChanged'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'streamBufferingChanged'
        QtMocHelpers::SignalData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'togglePlayback'
        QtMocHelpers::MethodData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'stopPlayback'
        QtMocHelpers::MethodData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'playNext'
        QtMocHelpers::MethodData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'playPrevious'
        QtMocHelpers::MethodData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'seekTo'
        QtMocHelpers::MethodData<void(qint64)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::LongLong, 20 },
        }}),
        // Method 'loadLocalFolder'
        QtMocHelpers::MethodData<void(const QUrl &)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 22, 23 },
        }}),
        // Method 'useLocalLibrary'
        QtMocHelpers::MethodData<void()>(24, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'formatClock'
        QtMocHelpers::MethodData<QString(qint64) const>(25, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::LongLong, 20 },
        }}),
        // Method 'tuneStation'
        QtMocHelpers::MethodData<void(int)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 27 },
        }}),
        // Method 'saveStation'
        QtMocHelpers::MethodData<void(const QString &, const QString &, const QUrl &)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 29 }, { QMetaType::QString, 30 }, { 0x80000000 | 22, 31 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'playbackActive'
        QtMocHelpers::PropertyData<bool>(32, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 0),
        // property 'playheadMs'
        QtMocHelpers::PropertyData<qint64>(33, QMetaType::LongLong, QMC::DefaultPropertyFlags | QMC::Final, 1),
        // property 'mediaLengthMs'
        QtMocHelpers::PropertyData<qint64>(34, QMetaType::LongLong, QMC::DefaultPropertyFlags | QMC::Final, 2),
        // property 'silenceEnabled'
        QtMocHelpers::PropertyData<bool>(35, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::Final, 3),
        // property 'outputLevel'
        QtMocHelpers::PropertyData<float>(36, QMetaType::Float, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 4),
        // property 'localTracks'
        QtMocHelpers::PropertyData<QStringList>(37, QMetaType::QStringList, QMC::DefaultPropertyFlags | QMC::Final, 5),
        // property 'selectedTrackIndex'
        QtMocHelpers::PropertyData<int>(38, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Final, 6),
        // property 'trackTitle'
        QtMocHelpers::PropertyData<QString>(39, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 7),
        // property 'trackArtist'
        QtMocHelpers::PropertyData<QString>(40, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 7),
        // property 'trackAlbum'
        QtMocHelpers::PropertyData<QString>(41, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 7),
        // property 'trackGenre'
        QtMocHelpers::PropertyData<QString>(42, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 7),
        // property 'lastPlaybackError'
        QtMocHelpers::PropertyData<QString>(43, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 8),
        // property 'radioActive'
        QtMocHelpers::PropertyData<bool>(44, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 9),
        // property 'stationCatalog'
        QtMocHelpers::PropertyData<QVariantList>(45, 0x80000000 | 46, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Final, 10),
        // property 'tunedStationName'
        QtMocHelpers::PropertyData<QString>(47, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 11),
        // property 'tunedStationCountry'
        QtMocHelpers::PropertyData<QString>(48, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Final, 11),
        // property 'streamBuffering'
        QtMocHelpers::PropertyData<bool>(49, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 12),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SoniquePlaybackEngine, qt_meta_tag_ZN21SoniquePlaybackEngineE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SoniquePlaybackEngine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21SoniquePlaybackEngineE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21SoniquePlaybackEngineE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN21SoniquePlaybackEngineE_t>.metaTypes,
    nullptr
} };

void SoniquePlaybackEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SoniquePlaybackEngine *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->playbackActiveChanged(); break;
        case 1: _t->playheadChanged(); break;
        case 2: _t->mediaLengthChanged(); break;
        case 3: _t->silenceEnabledChanged(); break;
        case 4: _t->outputLevelChanged(); break;
        case 5: _t->localTracksChanged(); break;
        case 6: _t->selectedTrackIndexChanged(); break;
        case 7: _t->trackDetailsChanged(); break;
        case 8: _t->playbackErrorChanged(); break;
        case 9: _t->radioActiveChanged(); break;
        case 10: _t->stationCatalogChanged(); break;
        case 11: _t->tunedStationChanged(); break;
        case 12: _t->streamBufferingChanged(); break;
        case 13: _t->togglePlayback(); break;
        case 14: _t->stopPlayback(); break;
        case 15: _t->playNext(); break;
        case 16: _t->playPrevious(); break;
        case 17: _t->seekTo((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1]))); break;
        case 18: _t->loadLocalFolder((*reinterpret_cast<std::add_pointer_t<QUrl>>(_a[1]))); break;
        case 19: _t->useLocalLibrary(); break;
        case 20: { QString _r = _t->formatClock((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 21: _t->tuneStation((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 22: _t->saveStation((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QUrl>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (SoniquePlaybackEngine::*)()>(_a, &SoniquePlaybackEngine::playbackActiveChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (SoniquePlaybackEngine::*)()>(_a, &SoniquePlaybackEngine::playheadChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (SoniquePlaybackEngine::*)()>(_a, &SoniquePlaybackEngine::mediaLengthChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (SoniquePlaybackEngine::*)()>(_a, &SoniquePlaybackEngine::silenceEnabledChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (SoniquePlaybackEngine::*)()>(_a, &SoniquePlaybackEngine::outputLevelChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (SoniquePlaybackEngine::*)()>(_a, &SoniquePlaybackEngine::localTracksChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (SoniquePlaybackEngine::*)()>(_a, &SoniquePlaybackEngine::selectedTrackIndexChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (SoniquePlaybackEngine::*)()>(_a, &SoniquePlaybackEngine::trackDetailsChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (SoniquePlaybackEngine::*)()>(_a, &SoniquePlaybackEngine::playbackErrorChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (SoniquePlaybackEngine::*)()>(_a, &SoniquePlaybackEngine::radioActiveChanged, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (SoniquePlaybackEngine::*)()>(_a, &SoniquePlaybackEngine::stationCatalogChanged, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (SoniquePlaybackEngine::*)()>(_a, &SoniquePlaybackEngine::tunedStationChanged, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (SoniquePlaybackEngine::*)()>(_a, &SoniquePlaybackEngine::streamBufferingChanged, 12))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->isPlaybackActive(); break;
        case 1: *reinterpret_cast<qint64*>(_v) = _t->playhead(); break;
        case 2: *reinterpret_cast<qint64*>(_v) = _t->mediaLength(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->isSilenced(); break;
        case 4: *reinterpret_cast<float*>(_v) = _t->outputLevel(); break;
        case 5: *reinterpret_cast<QStringList*>(_v) = _t->localTracks(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->selectedTrackIndex(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->trackTitle(); break;
        case 8: *reinterpret_cast<QString*>(_v) = _t->trackArtist(); break;
        case 9: *reinterpret_cast<QString*>(_v) = _t->trackAlbum(); break;
        case 10: *reinterpret_cast<QString*>(_v) = _t->trackGenre(); break;
        case 11: *reinterpret_cast<QString*>(_v) = _t->lastPlaybackError(); break;
        case 12: *reinterpret_cast<bool*>(_v) = _t->isRadioActive(); break;
        case 13: *reinterpret_cast<QVariantList*>(_v) = _t->stationCatalog(); break;
        case 14: *reinterpret_cast<QString*>(_v) = _t->tunedStationName(); break;
        case 15: *reinterpret_cast<QString*>(_v) = _t->tunedStationCountry(); break;
        case 16: *reinterpret_cast<bool*>(_v) = _t->isStreamBuffering(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 3: _t->setSilenced(*reinterpret_cast<bool*>(_v)); break;
        case 4: _t->setOutputLevel(*reinterpret_cast<float*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *SoniquePlaybackEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SoniquePlaybackEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21SoniquePlaybackEngineE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SoniquePlaybackEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 23;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void SoniquePlaybackEngine::playbackActiveChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SoniquePlaybackEngine::playheadChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SoniquePlaybackEngine::mediaLengthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SoniquePlaybackEngine::silenceEnabledChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SoniquePlaybackEngine::outputLevelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void SoniquePlaybackEngine::localTracksChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void SoniquePlaybackEngine::selectedTrackIndexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void SoniquePlaybackEngine::trackDetailsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void SoniquePlaybackEngine::playbackErrorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void SoniquePlaybackEngine::radioActiveChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void SoniquePlaybackEngine::stationCatalogChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void SoniquePlaybackEngine::tunedStationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void SoniquePlaybackEngine::streamBufferingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}
QT_WARNING_POP
