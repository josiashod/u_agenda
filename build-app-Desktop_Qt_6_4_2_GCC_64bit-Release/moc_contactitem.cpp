/****************************************************************************
** Meta object code from reading C++ file 'contactitem.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../app/contactitem.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'contactitem.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_ContactItem_t {
    uint offsetsAndSizes[26];
    char stringdata0[12];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[12];
    char stringdata5[12];
    char stringdata6[8];
    char stringdata7[12];
    char stringdata8[11];
    char stringdata9[27];
    char stringdata10[11];
    char stringdata11[11];
    char stringdata12[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ContactItem_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_ContactItem_t qt_meta_stringdata_ContactItem = {
    {
        QT_MOC_LITERAL(0, 11),  // "ContactItem"
        QT_MOC_LITERAL(12, 7),  // "updated"
        QT_MOC_LITERAL(20, 0),  // ""
        QT_MOC_LITERAL(21, 8),  // "personne"
        QT_MOC_LITERAL(30, 11),  // "oldPersonne"
        QT_MOC_LITERAL(42, 11),  // "newPersonne"
        QT_MOC_LITERAL(54, 7),  // "deleted"
        QT_MOC_LITERAL(62, 11),  // "std::string"
        QT_MOC_LITERAL(74, 10),  // "nomComplet"
        QT_MOC_LITERAL(85, 26),  // "onAfficherFormModification"
        QT_MOC_LITERAL(112, 10),  // "onAfficher"
        QT_MOC_LITERAL(123, 10),  // "onModifier"
        QT_MOC_LITERAL(134, 11)   // "onSupprimer"
    },
    "ContactItem",
    "updated",
    "",
    "personne",
    "oldPersonne",
    "newPersonne",
    "deleted",
    "std::string",
    "nomComplet",
    "onAfficherFormModification",
    "onAfficher",
    "onModifier",
    "onSupprimer"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_ContactItem[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   50,    2, 0x06,    1 /* Public */,
       6,    1,   55,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   58,    2, 0x08,    6 /* Private */,
      10,    0,   59,    2, 0x08,    7 /* Private */,
      11,    2,   60,    2, 0x08,    8 /* Private */,
      12,    0,   65,    2, 0x08,   11 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ContactItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ContactItem.offsetsAndSizes,
    qt_meta_data_ContactItem,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_ContactItem_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ContactItem, std::true_type>,
        // method 'updated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<personne, std::false_type>,
        QtPrivate::TypeAndForceComplete<personne, std::false_type>,
        // method 'deleted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::string, std::false_type>,
        // method 'onAfficherFormModification'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAfficher'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onModifier'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<personne, std::false_type>,
        QtPrivate::TypeAndForceComplete<personne, std::false_type>,
        // method 'onSupprimer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ContactItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ContactItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updated((*reinterpret_cast< std::add_pointer_t<personne>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<personne>>(_a[2]))); break;
        case 1: _t->deleted((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 2: _t->onAfficherFormModification(); break;
        case 3: _t->onAfficher(); break;
        case 4: _t->onModifier((*reinterpret_cast< std::add_pointer_t<personne>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<personne>>(_a[2]))); break;
        case 5: _t->onSupprimer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ContactItem::*)(personne , personne );
            if (_t _q_method = &ContactItem::updated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ContactItem::*)(std::string );
            if (_t _q_method = &ContactItem::deleted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *ContactItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ContactItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ContactItem.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ContactItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ContactItem::updated(personne _t1, personne _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ContactItem::deleted(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
