/*  Fichero canvas.cc
    Visualizador de tareas 

*/

#include "tipos.h"
#include "input.tab.h"   
#include "canvas.hh"
#include <qpopmenu.h>
#include <qkeycode.h>
#include <qapp.h>
#include <qmsgbox.h>
#include <qpixmap.h>
#include <qframe.h>
#include <qscrbar.h>
#include <qfiledlg.h>  
#include <qpoint.h>
#include <qpntarry.h>
#include <qwmatrix.h>
#include <qcolor.h>
#include <qpen.h>
#include <math.h>
#include <qtooltip.h> 


//------------------------------ AND old crono functions -------------

Canvas::Canvas( QWidget *parent, const char *name )
  : QWidget( parent, name ){
  setBackgroundColor(white);
  grid = 1;
  scroll= 0;
  zoom = 20;
  final_simulacion=0;
  
  //  setGeometry(0,y(),width(),height());

  area_de_nombres =  new Pizarra_Cls (this);
  area_de_nombres->setFrameStyle( QFrame::Box | QFrame::Raised );
  area_de_nombres->setGeometry(0,0,100,height());
  area_de_nombres->setBackgroundColor(lightGray);
  area_de_nombres->setMidLineWidth(2);

  area_de_cronograma =  new Pizarra_Cls (this);
  area_de_cronograma->setGeometry(0,0,100,height()-16);
  area_de_cronograma->setBackgroundColor(white);
  area_de_cronograma->setMidLineWidth(2);




  hscroll =new QScrollBar(0,0,10,500,0,QScrollBar::Horizontal, area_de_cronograma);
  CHECK_PTR( hscroll );

  //  hscroll->setStyle(WindowsStyle);  

  connect ( hscroll, SIGNAL(valueChanged(int)), SLOT(setScroll(int)));

  connect (area_de_cronograma, SIGNAL(hayQueRedibujar()), this, SLOT(reenvia()));
  connect (area_de_nombres, SIGNAL(hayQueRedibujar()), this, SLOT(reenvia()));
}


//------------------------------------------------------------------------------
void Canvas::resizeEvent( QResizeEvent * ){
  area_de_nombres->setGeometry(0,0,100,height());
  area_de_cronograma->setGeometry(100,0,width()-100,height());
  hscroll->setGeometry(0, height()-16, width()-100, 16);
  Limpia();
  emit hayQueRedibujar(true);

}



//------------------------------------------------------------------------------
void Canvas::setZoom(int z){
  zoom=z; 
  Limpia();
  emit hayQueRedibujar(true);
};
void Canvas::setScroll(int s){
  scroll=-(float)s;
  //  printf("scroll:%d\n",scroll);
  Limpia();
  emit hayQueRedibujar(true);
};
void Canvas::setGrid(int g){
  grid = g; 
  Limpia();
  emit hayQueRedibujar(true);
};

//------------------------------------------------------------------------------
void Canvas::Limpia(){
  QPainter p;
  
  p.begin(area_de_nombres);
  p.eraseRect(4,4,area_de_nombres->width()-8, area_de_nombres->height()-8);
  p.end();
  
  p.begin(area_de_cronograma);
  p.eraseRect(0,0,width(),height());
  p.end();
  
  QToolTip::remove(area_de_nombres,QRect(0,0,
					 area_de_nombres->width(),
					 area_de_nombres->height()));
  QToolTip::remove(area_de_cronograma,QRect(0,0,
					    area_de_cronograma->width(),
					    area_de_cronograma->height()));


  final_simulacion=0;
 
}
//------------------------------------------------------------------------------
void Canvas::Dibuja(int pos, const char *nombre, const char *tip){
  QPainter p;
  QRect r;

  
  r.setRect(4,ESPACIO_REGLA+pos*40+10, 
	    area_de_nombres->width(),
	    15);


  p.begin(area_de_nombres);
  p.drawText(4,ESPACIO_REGLA+20+40*pos,nombre,14);
  //  printf("%d->%s\n", pos, nombre);
  p.end();
  
  
  
  QToolTip::add(area_de_nombres,r,tip);


} // Canvas::Dibuja (int, cost char *)



//------------------------------------------------------------------------------
void Canvas::finalizado_dibujo(){
  QPainter p;
  int X=0;
  QPoint Linea;
  char cade[100];


  mat_escalado.reset();
  mat_escalado.translate(scroll,ESPACIO_REGLA);
  mat_escalado.scale(zoom,1.0);



  p.begin(area_de_cronograma);
  p.setPen( QPen(DotLine));
  if (grid > 0 ){    
    for (int x=0; (x<10000) &&   (X <=  area_de_cronograma->width()) ; x += grid) {
      Linea = mat_escalado.map(QPoint(x,(x%5) == 0 ? -20:-10));
      X=Linea.rx();
      
      
      if ((x%5) == 0){
	// Poner los números de la regla. y marcarlos más cada 5 unidades.
	sprintf(cade,"%d",x);
	p.drawText(X,15,cade,strlen(cade));
	p.setPen(QPen(DashDotLine));
	p.drawLine(Linea, QPoint(Linea.rx(),area_de_cronograma->height()));
	p.setPen( QPen(DotLine));
      } else {
	p.drawLine(Linea, QPoint(Linea.rx(),area_de_cronograma->height()));
      }
    }
  }
  p.setPen( QPen(SolidLine));
  for (int y=0; y< num_tareas; y++){
    X=y*40+24+ESPACIO_REGLA;
    p.drawLine(0, X, area_de_cronograma->width(), X);
  }
  p.end();


  

  //  printf("%d,%d\n",area_de_cronograma->width(), final_simulacion);

  int r_max =  ((final_simulacion+1)* zoom )- area_de_cronograma->width();

  r_max = r_max> 0 ? r_max: 0;


  hscroll->setRange(0, r_max);
  hscroll->setSteps(zoom,zoom*10);

}


//------------------------------------------------------------------------------
void Canvas::Dibuja(const evento_c &evento){

  QPainter p;

  QRect r;

  static QColor gama_col[]={ cyan, darkRed, darkGreen, darkBlue,
			     darkCyan, darkMagenta, darkYellow,
			     lightGray, green, blue, red, magenta,
			     yellow, black, white,
			     darkGray, gray};   

  QBrush c(gama_col[evento.Recurso() % 17]);
  static struct {
    int x, y;
  } puntos[]={{0,0} ,{0,20}, {0,0}, {0,-10}, {-1,5}, {1,-5}, {1,5}};
  
  
  


  mat_escalado.reset();
  mat_escalado.translate(scroll,ESPACIO_REGLA);
  mat_escalado.scale(zoom,1.0);




  int ultimo_punto=evento.Inicio();

  if (ultimo_punto>final_simulacion)
    final_simulacion= ultimo_punto;


    

  
  QPoint point(evento.Inicio(), (evento.Identificador())*40);
  point = mat_escalado.map(point);

  if (point.x()> area_de_cronograma->width()) 
    return;

  p.begin(area_de_cronograma);    
  p.setPen( QPen(SolidLine));
  p.setBrush( c );   

  switch(evento.Tipo()){
  case E_llegada:{ // ----------- Llegada


    r.setRect(point.x()-7,point.y()+20,15,15);

    p.drawPie(r,3840,960);
    if (evento.Recurso() != 0 ){
      p.setPen((QColor)black);
      p.setFont( QFont( "helvetica", 8 ));
      p.drawText(point.x(),point.y()+9, Recursos[evento.Recurso()].nombre);
    }

    break;
  }
  case E_activacion: {  //--------------- Activación
    QRect r_esca;
    
    r.setRect(evento.Inicio(), 
	      (evento.Identificador())*40+10, 
	      (evento.Fin() - evento.Inicio()+1) , 
	      15);
    r_esca = mat_escalado.map(r);
    p.drawRect( r_esca);
    break;
  }
  case E_final: {  // ----------------- Final
    
    r.setRect(point.x()-7,point.y(),15,15);
    p.drawPie(r,960,960);
    break;
  }
  } /* switch */
  p.end();


}

//------------------------------------------------------------------------------
void Canvas::Dibuja(){

}


void Canvas::reenvia( ){
  emit hayQueRedibujar(false);
  //printf("LLamado reenvia\n");
}



void Canvas::paintEvent( QPaintEvent * ){
  emit hayQueRedibujar(false);
  //printf("LLamado\n");
}
