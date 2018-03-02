/****************************************************************************
** confedit meta object code from reading C++ file 'confedit.h'
**
** Created: Fri Oct 7 20:33:38 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "confedit.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *confedit::className() const
{
    return "confedit";
}

QMetaObject *confedit::metaObj = 0;
static QMetaObjectCleanUp cleanUp_confedit( "confedit", &confedit::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString confedit::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "confedit", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString confedit::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "confedit", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* confedit::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"closec", 0, 0 };
    static const QUMethod slot_1 = {"helpc", 0, 0 };
    static const QUMethod slot_2 = {"openc", 0, 0 };
    static const QUMethod slot_3 = {"makecurrc", 0, 0 };
    static const QUMethod slot_4 = {"savec", 0, 0 };
    static const QUMethod slot_5 = {"defaultc", 0, 0 };
    static const QUParameter param_slot_6[] = {
	{ "tempname", &static_QUType_QString, 0, QUParameter::InOut }
    };
    static const QUMethod slot_6 = {"openfile", 1, param_slot_6 };
    static const QMetaData slot_tbl[] = {
	{ "closec()", &slot_0, QMetaData::Private },
	{ "helpc()", &slot_1, QMetaData::Private },
	{ "openc()", &slot_2, QMetaData::Private },
	{ "makecurrc()", &slot_3, QMetaData::Private },
	{ "savec()", &slot_4, QMetaData::Private },
	{ "defaultc()", &slot_5, QMetaData::Private },
	{ "openfile(QString&)", &slot_6, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"confedit", parentObject,
	slot_tbl, 7,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_confedit.setMetaObject( metaObj );
    return metaObj;
}

void* confedit::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "confedit" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool confedit::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: closec(); break;
    case 1: helpc(); break;
    case 2: openc(); break;
    case 3: makecurrc(); break;
    case 4: savec(); break;
    case 5: defaultc(); break;
    case 6: openfile((QString&)static_QUType_QString.get(_o+1)); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool confedit::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool confedit::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool confedit::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
