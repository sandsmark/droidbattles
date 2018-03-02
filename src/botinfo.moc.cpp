/****************************************************************************
** botinfo meta object code from reading C++ file 'botinfo.h'
**
** Created: Fri Oct 7 20:33:37 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "botinfo.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *botinfo::className() const
{
    return "botinfo";
}

QMetaObject *botinfo::metaObj = 0;
static QMetaObjectCleanUp cleanUp_botinfo( "botinfo", &botinfo::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString botinfo::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "botinfo", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString botinfo::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "botinfo", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* botinfo::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "x", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"armorupdated", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "x", &static_QUType_int, 0, QUParameter::In },
	{ "y", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"updatefuel", 2, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "x", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"statch", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ "msg", &static_QUType_charstar, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"newmessage", 1, param_slot_3 };
    static const QMetaData slot_tbl[] = {
	{ "armorupdated(int)", &slot_0, QMetaData::Private },
	{ "updatefuel(int,int)", &slot_1, QMetaData::Private },
	{ "statch(bool)", &slot_2, QMetaData::Private },
	{ "newmessage(char*)", &slot_3, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ "x", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"changeinset", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "changeinset(bool)", &signal_0, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"botinfo", parentObject,
	slot_tbl, 4,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_botinfo.setMetaObject( metaObj );
    return metaObj;
}

void* botinfo::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "botinfo" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL changeinset
void botinfo::changeinset( bool t0 )
{
    activate_signal_bool( staticMetaObject()->signalOffset() + 0, t0 );
}

bool botinfo::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: armorupdated((int)static_QUType_int.get(_o+1)); break;
    case 1: updatefuel((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 2: statch((bool)static_QUType_bool.get(_o+1)); break;
    case 3: newmessage((char*)static_QUType_charstar.get(_o+1)); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool botinfo::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: changeinset((bool)static_QUType_bool.get(_o+1)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool botinfo::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool botinfo::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
