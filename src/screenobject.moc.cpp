/****************************************************************************
** screenobject meta object code from reading C++ file 'screenobject.h'
**
** Created: Fri Oct 7 20:34:00 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "screenobject.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *screenobject::className() const
{
    return "screenobject";
}

QMetaObject *screenobject::metaObj = 0;
static QMetaObjectCleanUp cleanUp_screenobject( "screenobject", &screenobject::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString screenobject::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "screenobject", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString screenobject::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "screenobject", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* screenobject::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "x", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"setextragfx", 1, param_slot_0 };
    static const QMetaData slot_tbl[] = {
	{ "setextragfx(bool)", &slot_0, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ "x", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"armorchanged", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ "x", &static_QUType_int, 0, QUParameter::In },
	{ "y", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_1 = {"fuelchanged", 2, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ "msg", &static_QUType_charstar, 0, QUParameter::In }
    };
    static const QUMethod signal_2 = {"messagechanged", 1, param_signal_2 };
    static const QMetaData signal_tbl[] = {
	{ "armorchanged(int)", &signal_0, QMetaData::Private },
	{ "fuelchanged(int,int)", &signal_1, QMetaData::Private },
	{ "messagechanged(char*)", &signal_2, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"screenobject", parentObject,
	slot_tbl, 1,
	signal_tbl, 3,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_screenobject.setMetaObject( metaObj );
    return metaObj;
}

void* screenobject::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "screenobject" ) )
	return this;
    return QObject::qt_cast( clname );
}

// SIGNAL armorchanged
void screenobject::armorchanged( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL fuelchanged
void screenobject::fuelchanged( int t0, int t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_int.set(o+1,t0);
    static_QUType_int.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL messagechanged
void screenobject::messagechanged( char* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 2 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_charstar.set(o+1,t0);
    activate_signal( clist, o );
}

bool screenobject::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: setextragfx((bool)static_QUType_bool.get(_o+1)); break;
    default:
	return QObject::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool screenobject::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: armorchanged((int)static_QUType_int.get(_o+1)); break;
    case 1: fuelchanged((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 2: messagechanged((char*)static_QUType_charstar.get(_o+1)); break;
    default:
	return QObject::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool screenobject::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool screenobject::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
