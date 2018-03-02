/****************************************************************************
** createbot meta object code from reading C++ file 'createbot.h'
**
** Created: Fri Oct 7 20:33:40 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "createbot.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *createbot::className() const
{
    return "createbot";
}

QMetaObject *createbot::metaObj = 0;
static QMetaObjectCleanUp cleanUp_createbot( "createbot", &createbot::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString createbot::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "createbot", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString createbot::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "createbot", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* createbot::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"assemble", 0, 0 };
    static const QUMethod slot_1 = {"newb", 0, 0 };
    static const QUMethod slot_2 = {"open", 0, 0 };
    static const QUMethod slot_3 = {"save", 0, 0 };
    static const QUMethod slot_4 = {"saveas", 0, 0 };
    static const QUMethod slot_5 = {"closec", 0, 0 };
    static const QUMethod slot_6 = {"cut", 0, 0 };
    static const QUMethod slot_7 = {"copy", 0, 0 };
    static const QUMethod slot_8 = {"paste", 0, 0 };
    static const QUMethod slot_9 = {"choosepic", 0, 0 };
    static const QUMethod slot_10 = {"startquick", 0, 0 };
    static const QUMethod slot_11 = {"confquick", 0, 0 };
    static const QUMethod slot_12 = {"stopconf", 0, 0 };
    static const QUMethod slot_13 = {"checkconf", 0, 0 };
    static const QUMethod slot_14 = {"devchanged", 0, 0 };
    static const QUParameter param_slot_15[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_15 = {"scrollview", 1, param_slot_15 };
    static const QUParameter param_slot_16[] = {
	{ "e", &static_QUType_ptr, "QResizeEvent", QUParameter::In }
    };
    static const QUMethod slot_16 = {"resizeEvent", 1, param_slot_16 };
    static const QUParameter param_slot_17[] = {
	{ "i", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_17 = {"setEdittxtScrollValue", 1, param_slot_17 };
    static const QUParameter param_slot_18[] = {
	{ "i", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_18 = {"setShowlatencyScrollValue", 1, param_slot_18 };
    static const QMetaData slot_tbl[] = {
	{ "assemble()", &slot_0, QMetaData::Private },
	{ "newb()", &slot_1, QMetaData::Private },
	{ "open()", &slot_2, QMetaData::Private },
	{ "save()", &slot_3, QMetaData::Private },
	{ "saveas()", &slot_4, QMetaData::Private },
	{ "closec()", &slot_5, QMetaData::Private },
	{ "cut()", &slot_6, QMetaData::Private },
	{ "copy()", &slot_7, QMetaData::Private },
	{ "paste()", &slot_8, QMetaData::Private },
	{ "choosepic()", &slot_9, QMetaData::Private },
	{ "startquick()", &slot_10, QMetaData::Private },
	{ "confquick()", &slot_11, QMetaData::Private },
	{ "stopconf()", &slot_12, QMetaData::Private },
	{ "checkconf()", &slot_13, QMetaData::Private },
	{ "devchanged()", &slot_14, QMetaData::Private },
	{ "scrollview(int)", &slot_15, QMetaData::Private },
	{ "resizeEvent(QResizeEvent*)", &slot_16, QMetaData::Private },
	{ "setEdittxtScrollValue(int)", &slot_17, QMetaData::Private },
	{ "setShowlatencyScrollValue(int)", &slot_18, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"createbot", parentObject,
	slot_tbl, 19,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_createbot.setMetaObject( metaObj );
    return metaObj;
}

void* createbot::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "createbot" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool createbot::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: assemble(); break;
    case 1: newb(); break;
    case 2: open(); break;
    case 3: save(); break;
    case 4: saveas(); break;
    case 5: closec(); break;
    case 6: cut(); break;
    case 7: copy(); break;
    case 8: paste(); break;
    case 9: choosepic(); break;
    case 10: startquick(); break;
    case 11: confquick(); break;
    case 12: stopconf(); break;
    case 13: checkconf(); break;
    case 14: devchanged(); break;
    case 15: scrollview((int)static_QUType_int.get(_o+1)); break;
    case 16: resizeEvent((QResizeEvent*)static_QUType_ptr.get(_o+1)); break;
    case 17: setEdittxtScrollValue((int)static_QUType_int.get(_o+1)); break;
    case 18: setShowlatencyScrollValue((int)static_QUType_int.get(_o+1)); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool createbot::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool createbot::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool createbot::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
