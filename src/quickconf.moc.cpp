/****************************************************************************
** quickconf meta object code from reading C++ file 'quickconf.h'
**
** Created: Fri Oct 7 20:33:49 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "quickconf.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *quickconf::className() const
{
    return "quickconf";
}

QMetaObject *quickconf::metaObj = 0;
static QMetaObjectCleanUp cleanUp_quickconf( "quickconf", &quickconf::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString quickconf::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "quickconf", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString quickconf::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "quickconf", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* quickconf::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = startsbatt::staticMetaObject();
    static const QUMethod slot_0 = {"ocl", 0, 0 };
    static const QUMethod slot_1 = {"ccl", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "ocl()", &slot_0, QMetaData::Private },
	{ "ccl()", &slot_1, QMetaData::Private }
    };
    static const QUMethod signal_0 = {"cancelclicked", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "cancelclicked()", &signal_0, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"quickconf", parentObject,
	slot_tbl, 2,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_quickconf.setMetaObject( metaObj );
    return metaObj;
}

void* quickconf::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "quickconf" ) )
	return this;
    return startsbatt::qt_cast( clname );
}

// SIGNAL cancelclicked
void quickconf::cancelclicked()
{
    activate_signal( staticMetaObject()->signalOffset() + 0 );
}

bool quickconf::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: ocl(); break;
    case 1: ccl(); break;
    default:
	return startsbatt::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool quickconf::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: cancelclicked(); break;
    default:
	return startsbatt::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool quickconf::qt_property( int id, int f, QVariant* v)
{
    return startsbatt::qt_property( id, f, v);
}

bool quickconf::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
