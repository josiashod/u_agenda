/****************************************************************************
** Meta object code from reading C++ file 'rdvitem.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../app/rdvitem.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rdvitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_RdvItem_t {
    uint offsetsAndSizes[22];
    char stringdata0[8];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[4];
    char stringdata4[7];
    char stringdata5[8];
    char stringdata6[8];
    char stringdata7[12];
    char stringdata8[4];
    char stringdata9[11];
    char stringdata10[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_RdvItem_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_RdvItem_t qt_meta_stringdata_RdvItem = {
    {
        QT_MOC_LITERAL(0, 7),  // "RdvItem"
        QT_MOC_LITERAL(8, 7),  // "updated"
        QT_MOC_LITERAL(16, 0),  // ""
        QT_MOC_LITERAL(17, 3),  // "rdv"
        QT_MOC_LITERAL(21, 6),  // "ancien"
        QT_MOC_LITERAL(28, 7),  // "nouveau"
        QT_MOC_LITERAL(36, 7),  // "deleted"
        QT_MOC_LITERAL(44, 11),  // "std::string"
        QT_MOC_LITERAL(56, 3),  // "nom"
        QT_MOC_LITERAL(60, 10),  // "onAfficher"
        QT_MOC_LITERAL(71, 11)   // "onSupprimer"
    },
    "RdvItem",
    "updated",
    "",
    "rdv",
    "ancien",
    "nouveau",
    "deleted",
    "std::string",
    "nom",
    "onAfficher",
    "onSupprimer"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_RdvItem[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   38,    2, 0x06,    1 /* Public */,
       6,    1,   43,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   46,    2, 0x08,    6 /* Private */,
      10,    0,   47,    2, 0x08,    7 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject RdvItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_RdvItem.offsetsAndSizes,
    qt_meta_data_RdvItem,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_RdvItem_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<RdvItem, std::true_type>,
        // method 'updated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<rdv, std::false_type>,
        QtPrivate::TypeAndForceComplete<rdv, std::false_type>,
        // method 'deleted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::string, std::false_type>,
        // method 'onAfficher'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSupprimer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void RdvItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RdvItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updated((*reinterpret_cast< std::add_pointer_t<rdv>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<rdv>>(_a[2]))); break;
        case 1: _t->deleted((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 2: _t->onAfficher(); break;
        case 3: _t->onSupprimer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RdvItem::*)(rdv , rdv );
            if (_t _q_method = &RdvItem::updated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RdvItem::*)(std::string );
            if (_t _q_method = &RdvItem::deleted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *RdvItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RdvItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RdvItem.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RdvItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void RdvItem::updated(rdv _t1, rdv _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RdvItem::deleted(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
