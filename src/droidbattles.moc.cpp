/****************************************************************************
** DroidBattles meta object code from reading C++ file 'droidbattles.h'
**
** Created: Fri Oct 7 20:33:45 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "droidbattles.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *DroidBattles::className() const
{
    return "DroidBattles";
}

QMetaObject *DroidBattles::metaObj = 0;
static QMetaObjectCleanUp cleanUp_DroidBattles( "DroidBattles", &DroidBattles::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString DroidBattles::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "DroidBattles", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString DroidBattles::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "DroidBattles", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* DroidBattles::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"createb", 0, 0 };
    static const QUMethod slot_1 = {"about", 0, 0 };
    static const QUMethod slot_2 = {"showb", 0, 0 };
    static const QUMethod slot_3 = {"quit", 0, 0 };
    static const QUMethod slot_4 = {"editconf", 0, 0 };
    static const QUMethod slot_5 = {"skirmish", 0, 0 };
    static const QUMethod slot_6 = {"startskirmish", 0, 0 };
    static const QUMethod slot_7 = {"stopskirmish", 0, 0 };
    static const QUMethod slot_8 = {"survival", 0, 0 };
    static const QUMethod slot_9 = {"startsurvival", 0, 0 };
    static const QUMethod slot_10 = {"stopsurvival", 0, 0 };
    static const QUMethod slot_11 = {"death", 0, 0 };
    static const QUMethod slot_12 = {"startdeath", 0, 0 };
    static const QUMethod slot_13 = {"stopdeath", 0, 0 };
    static const QUMethod slot_14 = {"tournament", 0, 0 };
    static const QUMethod slot_15 = {"starttourney", 0, 0 };
    static const QUMethod slot_16 = {"stoptourney", 0, 0 };
    static const QUParameter param_slot_17[] = {
	{ "wins1", &static_QUType_int, 0, QUParameter::In },
	{ "wins2", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_17 = {"managetourney", 2, param_slot_17 };
    static const QUMethod slot_18 = {"koth", 0, 0 };
    static const QUMethod slot_19 = {"startkoth", 0, 0 };
    static const QUMethod slot_20 = {"stopkoth", 0, 0 };
    static const QUParameter param_slot_21[] = {
	{ "wins1", &static_QUType_int, 0, QUParameter::In },
	{ "wins2", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_21 = {"mankothtourney", 2, param_slot_21 };
    static const QUMethod slot_22 = {"cup", 0, 0 };
    static const QUMethod slot_23 = {"startcupt", 0, 0 };
    static const QUMethod slot_24 = {"stopcup", 0, 0 };
    static const QUParameter param_slot_25[] = {
	{ "wins1", &static_QUType_int, 0, QUParameter::In },
	{ "wins2", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_25 = {"mancuptourney", 2, param_slot_25 };
    static const QUMethod slot_26 = {"showdoc", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "createb()", &slot_0, QMetaData::Private },
	{ "about()", &slot_1, QMetaData::Private },
	{ "showb()", &slot_2, QMetaData::Private },
	{ "quit()", &slot_3, QMetaData::Private },
	{ "editconf()", &slot_4, QMetaData::Private },
	{ "skirmish()", &slot_5, QMetaData::Private },
	{ "startskirmish()", &slot_6, QMetaData::Private },
	{ "stopskirmish()", &slot_7, QMetaData::Private },
	{ "survival()", &slot_8, QMetaData::Private },
	{ "startsurvival()", &slot_9, QMetaData::Private },
	{ "stopsurvival()", &slot_10, QMetaData::Private },
	{ "death()", &slot_11, QMetaData::Private },
	{ "startdeath()", &slot_12, QMetaData::Private },
	{ "stopdeath()", &slot_13, QMetaData::Private },
	{ "tournament()", &slot_14, QMetaData::Private },
	{ "starttourney()", &slot_15, QMetaData::Private },
	{ "stoptourney()", &slot_16, QMetaData::Private },
	{ "managetourney(int,int)", &slot_17, QMetaData::Private },
	{ "koth()", &slot_18, QMetaData::Private },
	{ "startkoth()", &slot_19, QMetaData::Private },
	{ "stopkoth()", &slot_20, QMetaData::Private },
	{ "mankothtourney(int,int)", &slot_21, QMetaData::Private },
	{ "cup()", &slot_22, QMetaData::Private },
	{ "startcupt()", &slot_23, QMetaData::Private },
	{ "stopcup()", &slot_24, QMetaData::Private },
	{ "mancuptourney(int,int)", &slot_25, QMetaData::Private },
	{ "showdoc()", &slot_26, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"DroidBattles", parentObject,
	slot_tbl, 27,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_DroidBattles.setMetaObject( metaObj );
    return metaObj;
}

void* DroidBattles::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "DroidBattles" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool DroidBattles::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: createb(); break;
    case 1: about(); break;
    case 2: showb(); break;
    case 3: quit(); break;
    case 4: editconf(); break;
    case 5: skirmish(); break;
    case 6: startskirmish(); break;
    case 7: stopskirmish(); break;
    case 8: survival(); break;
    case 9: startsurvival(); break;
    case 10: stopsurvival(); break;
    case 11: death(); break;
    case 12: startdeath(); break;
    case 13: stopdeath(); break;
    case 14: tournament(); break;
    case 15: starttourney(); break;
    case 16: stoptourney(); break;
    case 17: managetourney((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 18: koth(); break;
    case 19: startkoth(); break;
    case 20: stopkoth(); break;
    case 21: mankothtourney((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 22: cup(); break;
    case 23: startcupt(); break;
    case 24: stopcup(); break;
    case 25: mancuptourney((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 26: showdoc(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool DroidBattles::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool DroidBattles::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool DroidBattles::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
