/****************************************************************************
** devchoice meta object code from reading C++ file 'devchoice.h'
**
** Created: Fri Oct 7 20:33:43 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "devchoice.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *devchoice::className() const
{
    return "devchoice";
}

QMetaObject *devchoice::metaObj = 0;
static QMetaObjectCleanUp cleanUp_devchoice( "devchoice", &devchoice::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString devchoice::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "devchoice", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString devchoice::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "devchoice", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* devchoice::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"levelchosen", 1, param_slot_0 };
    static const QUMethod slot_1 = {"costchanged", 0, 0 };
    static const QUMethod slot_2 = {"showinfo", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "levelchosen(int)", &slot_0, QMetaData::Public },
	{ "costchanged()", &slot_1, QMetaData::Public },
	{ "showinfo()", &slot_2, QMetaData::Public }
    };
    static const QUMethod signal_0 = {"change", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "change()", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"devchoice", parentObject,
	slot_tbl, 3,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_devchoice.setMetaObject( metaObj );
    return metaObj;
}

void* devchoice::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "devchoice" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL change
void devchoice::change()
{
    activate_signal( staticMetaObject()->signalOffset() + 0 );
}

bool devchoice::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: levelchosen((int)static_QUType_int.get(_o+1)); break;
    case 1: costchanged(); break;
    case 2: showinfo(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool devchoice::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: change(); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool devchoice::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool devchoice::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
