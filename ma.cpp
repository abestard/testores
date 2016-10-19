#include "ma.h"
#include "ui_ma.h"
#include <QtGui>
#include <string.h>
#include <stdio.h>

ma::ma(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::ma)
{
    m_ui->setupUi(this);

    //
     m_ui->fila->setValue( 10 );
     m_ui->columna->setValue( 10 );

     matrix mat(10,10,2);

     mat.generar_MA();
     mat.conv_a_Tabla( m_ui->tableWidget, true );
    //
}

ma::~ma()
{
    delete m_ui;
}

void ma::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ma::on_crear_tabla_clicked()
{
  int fil = m_ui->fila->value();
  int col = m_ui->columna->value();
  int ncl = m_ui->clases->value();

  if( fil <= 0 || col <= 0 || ncl <= 1 ) return;

  m_ui->tableWidget->setRowCount( fil + 1 );
  m_ui->tableWidget->setColumnCount( col + 1 + ncl );

  QTableWidgetItem *valor;
  for( int i = 1; i <= fil; i ++ )
      for( int j = 1; j <= col+ncl; j ++ ){
         valor = new QTableWidgetItem();

         if( j > col )
          valor->setBackground( Qt::gray );
         else
          valor->setBackground( Qt::lightGray );


         m_ui->tableWidget->setItem( i, j, valor );
      }

  for( int j = 1; j <= col+ncl; j ++ ){
      valor = new QTableWidgetItem();
      valor->setBackground( Qt::darkGray );
      m_ui->tableWidget->setItem( 0, j, valor );
  }

  for( int i = 0; i < fil+1; i ++ ){
       valor = new QTableWidgetItem();
       valor->setBackground( Qt::darkGray );
       m_ui->tableWidget->setItem( i, 0, valor );
   }

  valor = new QTableWidgetItem("Objts/Descipciones");
  valor->setFlags(Qt::NoItemFlags);
  valor->setFlags(Qt::ItemIsEnabled);
  valor->setBackground( Qt::darkGray );
  m_ui->tableWidget->setItem( 0, 0, valor );
}

void ma::on_actionGenerar_triggered()
{
   int fil = m_ui->fila->value();
   int col = m_ui->columna->value();
   int ncl = m_ui->clases->value();

   if( fil <= 0 || col <= 0 ) return;

   matrix mat( fil, col, ncl );

   mat.generar_MA();

   mat.conv_a_Tabla( m_ui->tableWidget, true );
}

void ma::on_actionSalvar_triggered()
{
     fich.salvar_tabla( m_ui->tableWidget, 0, m_ui->clases->value() );
}

void ma::on_actionCargar_triggered()
{
     matrix mat = fich.cargar_matrix(  );

     if( mat.tip != 0 ){
         QMessageBox *error;
         error = new QMessageBox();
         error->setText( "Matriz no valida" );
         error->show();
         return;
     }

     m_ui->fila->setValue( mat.getfil() );
     m_ui->columna->setValue( mat.getcol() );
     m_ui->clases->setValue( mat.nclas );

     mat.conv_a_Tabla( m_ui->tableWidget, true );
}

void ma::on_actionConvertir_a_MD_triggered()
{
   timer = new QTimer( this );
   timer->start( 500 );

   MA = fich.convertir_tabla_matrix( m_ui->tableWidget, 0, m_ui->clases->value() );

   if( MA.getcol() <= 0 || MA.getfil() <= 0 || MA.nclas <= 1 ) return;

   connect(timer, SIGNAL(timeout()), this, SLOT(end_ma_md( )));

   v_ma_md.vaule_umbral( MA.rasg, MA.getcol() );
   v_ma_md.terminado = false;
   v_ma_md.show( );
}

void ma::end_ma_md(  ){
    if( !v_ma_md.isActiveWindow() ){
        timer->stop();
    }

    if( !v_ma_md.terminado ) return;

    matrix md = MA.conv_MA_MD( v_ma_md.umbral );

    if( md.getfil() <= 0 || md.getcol() <= 0 ){
        show();
        return;
    }

    v_md.mostrar_matrix( md );
    v_md.show();
    v_ma_md.terminado = false;
}

