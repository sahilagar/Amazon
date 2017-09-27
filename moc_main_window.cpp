/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "main_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      31,   11,   11,   11, 0x08,
      49,   11,   11,   11, 0x08,
      61,   11,   11,   11, 0x08,
      73,   11,   11,   11, 0x08,
      81,   11,   11,   11, 0x08,
      91,   11,   11,   11, 0x08,
     112,   11,   11,   11, 0x08,
     129,   11,   11,   11, 0x08,
     149,   11,   11,   11, 0x08,
     156,   11,   11,   11, 0x08,
     173,   11,   11,   11, 0x08,
     185,   11,   11,   11, 0x08,
     203,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0andButtonClicked()\0"
    "orButtonClicked()\0addToCart()\0showPopup()\0"
    "close()\0buyCart()\0removeItemFromCart()\0"
    "displayReviews()\0closeReviewLayout()\0"
    "exit()\0saveToDatabase()\0addReview()\0"
    "populateReviews()\0closeAddWindow()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->andButtonClicked(); break;
        case 1: _t->orButtonClicked(); break;
        case 2: _t->addToCart(); break;
        case 3: _t->showPopup(); break;
        case 4: _t->close(); break;
        case 5: _t->buyCart(); break;
        case 6: _t->removeItemFromCart(); break;
        case 7: _t->displayReviews(); break;
        case 8: _t->closeReviewLayout(); break;
        case 9: _t->exit(); break;
        case 10: _t->saveToDatabase(); break;
        case 11: _t->addReview(); break;
        case 12: _t->populateReviews(); break;
        case 13: _t->closeAddWindow(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
