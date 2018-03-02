/****************************************************************************
** battlearea meta object code from reading C++ file 'battlearea.h'
**
** Created: Fri Oct 7 20:33:35 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "battlearea.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *battlearea::className() const
{
    return "battlearea";
}

QMetaObject *battlearea::metaObj = 0;
static QMetaObjectCleanUp cleanUp_battlearea( "battlearea", &battlearea::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString battlearea::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "battlearea", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString battlearea::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "battlearea", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* battlearea::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"execute", 0, 0 };
    static const QUMethod slot_1 = {"play", 0, 0 };
    static const QUMethod slot_2 = {"pause", 0, 0 };
    static const QUMethod slot_3 = {"singlestep", 0, 0 };
    static const QUMethod slot_4 = {"dmem", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "execute()", &slot_0, QMetaData::Private },
	{ "play()", &slot_1, QMetaData::Private },
	{ "pause()", &slot_2, QMetaData::Private },
	{ "singlestep()", &slot_3, QMetaData::Private },
	{ "dmem()", &slot_4, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"battledone", 2, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "battledone(int,int)", &signal_0, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"battlearea", parentObject,
	slot_tbl, 5,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_battlearea.setMetaObject( metaObj );
    return metaObj;
}

void* battlearea::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "battlearea" ) )
	return this;
    if ( !qstrcmp( clname, "textmodeBattleArea" ) )
	return (textmodeBattleArea*)this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL battledone
void battlearea::battledone( int t0, int t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_int.set(o+1,t0);
    static_QUType_int.set(o+2,t1);
    activate_signal( clist, o );
}

bool battlearea::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: execute(); break;
    case 1: play(); break;
    case 2: pause(); break;
    case 3: singlestep(); break;
    case 4: dmem(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool battlearea::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: battledone((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool battlearea::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool battlearea::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
