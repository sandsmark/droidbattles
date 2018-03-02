/****************************************************************************
** startsbatt meta object code from reading C++ file 'startsbatt.h'
**
** Created: Fri Oct 7 20:33:54 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "startsbatt.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *startsbatt::className() const
{
    return "startsbatt";
}

QMetaObject *startsbatt::metaObj = 0;
static QMetaObjectCleanUp cleanUp_startsbatt( "startsbatt", &startsbatt::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString startsbatt::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "startsbatt", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString startsbatt::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "startsbatt", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* startsbatt::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"choosefile", 0, 0 };
    static const QUMethod slot_1 = {"dechoosefile", 0, 0 };
    static const QUMethod slot_2 = {"ocl", 0, 0 };
    static const QUMethod slot_3 = {"ccl", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "choosefile()", &slot_0, QMetaData::Private },
	{ "dechoosefile()", &slot_1, QMetaData::Private },
	{ "ocl()", &slot_2, QMetaData::Private },
	{ "ccl()", &slot_3, QMetaData::Private }
    };
    static const QUMethod signal_0 = {"okclicked", 0, 0 };
    static const QUMethod signal_1 = {"cancelclicked", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "okclicked()", &signal_0, QMetaData::Private },
	{ "cancelclicked()", &signal_1, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"startsbatt", parentObject,
	slot_tbl, 4,
	signal_tbl, 2,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_startsbatt.setMetaObject( metaObj );
    return metaObj;
}

void* startsbatt::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "startsbatt" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL okclicked
void startsbatt::okclicked()
{
    activate_signal( staticMetaObject()->signalOffset() + 0 );
}

// SIGNAL cancelclicked
void startsbatt::cancelclicked()
{
    activate_signal( staticMetaObject()->signalOffset() + 1 );
}

bool startsbatt::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: choosefile(); break;
    case 1: dechoosefile(); break;
    case 2: ocl(); break;
    case 3: ccl(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool startsbatt::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: okclicked(); break;
    case 1: cancelclicked(); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool startsbatt::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool startsbatt::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
