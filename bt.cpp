#include "bt.h"
#include "ui_bt.h"

BT::BT(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::BT)
{
    Algoritmos_de_TT = 0;
    m_ui->setupUi(this);
}

BT::~BT()
{
    delete m_ui;
}

void BT::changeEvent(QEvent *e)
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

void BT::on_iniciar_clicked( )
{
    ult = 0;
    m_ui->tableWidget_2->setRowCount(0);

    Algoritmos_de_TT = new MyThread();
    Algoritmos_de_TT->Algoritmos = new Teoria_de_Testores();
    Algoritmos_de_TT->mat = fich.cargar_matrix( );

    if( Algoritmos_de_TT->mat.tip != 2 ){
        QMessageBox *error;
        error = new QMessageBox();
        error->setText( "Matriz no valida" );
        error->show();
        return;
    }

    m_ui->iniciar->setDisabled( true );

    Algoritmos_de_TT->Nombre = "BT";
    ruta1 = &Algoritmos_de_TT->mat;
    ruta = Algoritmos_de_TT->Algoritmos;
    ruta->detener = false;
    ruta->iniciado = false;

    if( ruta1->getfil() <= 0 || ruta1->getcol() <= 0 ) return;

    char cad[100];
    sprintf(cad, "Cantidad de Testores Tipicos: %d", 0);
    m_ui->label_4->setText( cad );

    timer = new QTimer(this);
    reloj = new QTime(0,0,0);
    m_ui->reloj->setText( reloj->toString(Qt::TextDate) );

    timer->start( 1000 );
    connect( timer, SIGNAL(timeout()),this, SLOT( actualizar( ) ) );
    Algoritmos_de_TT->start();
}

void BT::on_detener_clicked( )
{
   if( Algoritmos_de_TT != 0 )
     ruta->detener = true;
}

void BT::actualizar( ){
  if( ruta->iniciado == false )return;

  *reloj = reloj->addSecs( 1 );
   m_ui->reloj->setText( reloj->toString(Qt::TextDate) );

   int n = ruta->num_TT;
   int cant_rasg = ruta->mask_TT->cant_bits();

  //Actrualizar la detencion
   if( m_ui->check1->isChecked() && n >= m_ui->numTT->value()  )
       ruta->detener = true;

   if( m_ui->check2->isChecked() && cant_rasg >= m_ui->porciento->value()*ruta1->getcol()  )
       ruta->detener = true;

  ///-END---
   if( ruta->detener == true || isActiveWindow() == false ){
       timer->stop();
       Algoritmos_de_TT->terminate();
       m_ui->iniciar->setDisabled( false );
       //delete Algoritmos_de_TT;
   }

   m_ui->tableWidget_2->setRowCount( n );
   char cad[100];
   sprintf(cad, "Cantidad de Testores Tipicos: %d", n);
   m_ui->label_4->setText( cad );

   QString nomb, test;
   QTableWidgetItem *valor;
   for( ; ult < n; ult ++ ){
       sprintf(cad, "TT%d", ult+1);
       test = cad;
       nomb = "";
       for( int i = 0; i < ruta1->getcol(); i ++ )
           if( ruta->testt[ult].getbit( i ) == true ){
               if( nomb != "" )
                  nomb += ", ";
               nomb += ruta1->rasg[i];
           }

       nomb = test + " = {" + nomb + "}";
       valor = new QTableWidgetItem(nomb);
       m_ui->tableWidget_2->setItem( ult, 0, valor );
   }



   // Actualizar variables
   if( m_ui->intervalo->value() == 0 || reloj->second()%m_ui->intervalo->value() != 0 ) return;

   sprintf(cad, "%d", n );
   valor = new QTableWidgetItem(cad);
   m_ui->tableWidget->setItem( 0, 1, valor );
}
