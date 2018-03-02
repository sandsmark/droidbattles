/****************************************************************************
** startcup meta object code from reading C++ file 'startcup.h'
**
** Created: Fri Oct 7 20:33:51 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "startcup.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *startcup::className() const
{
    return "startcup";
}

QMetaObject *startcup::metaObj = 0;
static QMetaObjectCleanUp cleanUp_startcup( "startcup", &startcup::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString startcup::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "startcup", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString startcup::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "startcup", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* startcup::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = starttournament::staticMetaObject();
    static const QUMethod slot_0 = {"ocl", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "ocl()", &slot_0, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"startcup", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_startcup.setMetaObject( metaObj );
    return metaObj;
}

void* startcup::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "startcup" ) )
	return this;
    return starttournament::qt_cast( clname );
}

bool startcup::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: ocl(); break;
    default:
	return starttournament::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool startcup::qt_emit( int _id, QUObject* _o )
{
    return starttournament::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool startcup::qt_property( int id, int f, QVariant* v)
{
    return starttournament::qt_property( id, f, v);
}

bool startcup::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
