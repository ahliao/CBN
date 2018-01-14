/****************************************************************************
** Meta object code from reading C++ file 'lomdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../lomdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lomdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PSCDP__LOMDialog_t {
    QByteArrayData data[6];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PSCDP__LOMDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PSCDP__LOMDialog_t qt_meta_stringdata_PSCDP__LOMDialog = {
    {
QT_MOC_LITERAL(0, 0, 16), // "PSCDP::LOMDialog"
QT_MOC_LITERAL(1, 17, 19), // "handleTreeSelection"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 7), // "current"
QT_MOC_LITERAL(4, 46, 8), // "previous"
QT_MOC_LITERAL(5, 55, 12) // "handeDoneBtn"

    },
    "PSCDP::LOMDialog\0handleTreeSelection\0"
    "\0current\0previous\0handeDoneBtn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PSCDP__LOMDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x0a /* Public */,
       5,    0,   29,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::QModelIndex,    3,    4,
    QMetaType::Void,

       0        // eod
};

void PSCDP::LOMDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LOMDialog *_t = static_cast<LOMDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handleTreeSelection((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 1: _t->handeDoneBtn(); break;
        default: ;
        }
    }
}

const QMetaObject PSCDP::LOMDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PSCDP__LOMDialog.data,
      qt_meta_data_PSCDP__LOMDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PSCDP::LOMDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PSCDP::LOMDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PSCDP__LOMDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int PSCDP::LOMDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
