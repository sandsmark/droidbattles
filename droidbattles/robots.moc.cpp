/****************************************************************************
** robots meta object code from reading C++ file 'robots.h'
**
** Created: Fri Oct 7 20:34:01 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "robots.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *robots::className() const
{
    return "robots";
}

QMetaObject *robots::metaObj = 0;
static QMetaObjectCleanUp cleanUp_robots( "robots", &robots::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString robots::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "robots", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString robots::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "robots", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* robots::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = screenobject::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"robots", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_robots.setMetaObject( metaObj );
    return metaObj;
}

void* robots::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "robots" ) )
	return this;
    return screenobject::qt_cast( clname );
}

bool robots::qt_invoke( int _id, QUObject* _o )
{
    return screenobject::qt_invoke(_id,_o);
}

bool robots::qt_emit( int _id, QUObject* _o )
{
    return screenobject::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool robots::qt_property( int id, int f, QVariant* v)
{
    return screenobject::qt_property( id, f, v);
}

bool robots::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
