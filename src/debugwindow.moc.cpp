/****************************************************************************
** debugwindow meta object code from reading C++ file 'debugwindow.h'
**
** Created: Fri Oct 7 20:33:42 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "debugwindow.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *debugwindow::className() const
{
    return "debugwindow";
}

QMetaObject *debugwindow::metaObj = 0;
static QMetaObjectCleanUp cleanUp_debugwindow( "debugwindow", &debugwindow::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString debugwindow::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "debugwindow", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString debugwindow::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "debugwindow", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* debugwindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"distsignal", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "distsignal()", &slot_0, QMetaData::Private }
    };
    static const QUMethod signal_0 = {"dumpmem", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "dumpmem()", &signal_0, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"debugwindow", parentObject,
	slot_tbl, 1,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_debugwindow.setMetaObject( metaObj );
    return metaObj;
}

void* debugwindow::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "debugwindow" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL dumpmem
void debugwindow::dumpmem()
{
    activate_signal( staticMetaObject()->signalOffset() + 0 );
}

bool debugwindow::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: distsignal(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool debugwindow::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: dumpmem(); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool debugwindow::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool debugwindow::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
