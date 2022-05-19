/****************************************************************************
** AyudaCls meta object code from reading C++ file 'ayuda.hh'
**
** Created: Wed Nov 25 15:03:05 1998
**      by: The Qt Meta Object Compiler ($Revision: 2.18 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 2
#elif Q_MOC_OUTPUT_REVISION != 2
#error Moc format conflict - please regenerate all moc files
#endif

#include "../include/ayuda.hh"
#include <qmetaobj.h>


const char *AyudaCls::className() const
{
    return "AyudaCls";
}

QMetaObject *AyudaCls::metaObj = 0;

void AyudaCls::initMetaObject()
{
    if ( metaObj )
	return;
    if ( strcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("AyudaCls","QWidget");
    if ( !QWidget::metaObject() )
	QWidget::initMetaObject();
    typedef void(AyudaCls::*m1_t0)();
    typedef void(AyudaCls::*m1_t1)(const char*);
    typedef void(AyudaCls::*m1_t2)();
    typedef void(AyudaCls::*m1_t3)(int);
    m1_t0 v1_0 = &AyudaCls::newDoc;
    m1_t1 v1_1 = &AyudaCls::load;
    m1_t2 v1_2 = &AyudaCls::closeDoc;
    m1_t3 v1_3 = &AyudaCls::ayuda_elegida;
    QMetaData *slot_tbl = new QMetaData[4];
    slot_tbl[0].name = "newDoc()";
    slot_tbl[1].name = "load(const char*)";
    slot_tbl[2].name = "closeDoc()";
    slot_tbl[3].name = "ayuda_elegida(int)";
    slot_tbl[0].ptr = *((QMember*)&v1_0);
    slot_tbl[1].ptr = *((QMember*)&v1_1);
    slot_tbl[2].ptr = *((QMember*)&v1_2);
    slot_tbl[3].ptr = *((QMember*)&v1_3);
    metaObj = new QMetaObject( "AyudaCls", "QWidget",
	slot_tbl, 4,
	0, 0 );
}
