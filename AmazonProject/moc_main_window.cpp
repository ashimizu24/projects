/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "main_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      21,   11,   11,   11, 0x08,
      37,   11,   11,   11, 0x08,
      52,   11,   11,   11, 0x08,
      79,   66,   11,   11, 0x08,
      98,   66,   11,   11, 0x08,
     117,   11,   11,   11, 0x08,
     137,  129,   11,   11, 0x08,
     151,   11,   11,   11, 0x08,
     171,   11,   11,   11, 0x08,
     182,   11,   11,   11, 0x08,
     192,   11,   11,   11, 0x08,
     206,   11,   11,   11, 0x08,
     227,  222,   11,   11, 0x08,
     251,   11,   11,   11, 0x08,
     264,   11,   11,   11, 0x08,
     274,   11,   11,   11, 0x08,
     289,   11,   11,   11, 0x08,
     316,   11,   11,   11, 0x08,
     326,   11,   11,   11, 0x08,
     339,   11,   11,   11, 0x08,
     352,   11,   11,   11, 0x08,
     365,   11,   11,   11, 0x08,
     378,   11,   11,   11, 0x08,
     391,   11,   11,   11, 0x08,
     404,   11,   11,   11, 0x08,
     416,   11,   11,   11, 0x08,
     433,   11,   11,   11, 0x08,
     458,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0logout()\0displaySearch()\0"
    "setSearchAND()\0setSearchOR()\0productIndex\0"
    "reviewDisplay(int)\0selectProduct(int)\0"
    "addToCart()\0sortNum\0prodSort(int)\0"
    "showProductSearch()\0saveFile()\0quitApp()\0"
    "setupWindow()\0closeViewcart()\0item\0"
    "selectItemViewCart(int)\0removeItem()\0"
    "buycart()\0openViewcart()\0"
    "writeReviewButtonClicked()\0setDate()\0"
    "setRating1()\0setRating2()\0setRating3()\0"
    "setRating4()\0setRating5()\0readReview()\0"
    "addReview()\0closeAddReview()\0"
    "displayRecommendations()\0closeSuggestions()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->logout(); break;
        case 1: _t->displaySearch(); break;
        case 2: _t->setSearchAND(); break;
        case 3: _t->setSearchOR(); break;
        case 4: _t->reviewDisplay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->selectProduct((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->addToCart(); break;
        case 7: _t->prodSort((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->showProductSearch(); break;
        case 9: _t->saveFile(); break;
        case 10: _t->quitApp(); break;
        case 11: _t->setupWindow(); break;
        case 12: _t->closeViewcart(); break;
        case 13: _t->selectItemViewCart((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->removeItem(); break;
        case 15: _t->buycart(); break;
        case 16: _t->openViewcart(); break;
        case 17: _t->writeReviewButtonClicked(); break;
        case 18: _t->setDate(); break;
        case 19: _t->setRating1(); break;
        case 20: _t->setRating2(); break;
        case 21: _t->setRating3(); break;
        case 22: _t->setRating4(); break;
        case 23: _t->setRating5(); break;
        case 24: _t->readReview(); break;
        case 25: _t->addReview(); break;
        case 26: _t->closeAddReview(); break;
        case 27: _t->displayRecommendations(); break;
        case 28: _t->closeSuggestions(); break;
        default: ;
        }
    }
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
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
