#include "br.h"
#include "ui_br.h"

br::br(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::br)
{
    ui->setupUi(this);
}

br::~br()
{
    delete ui;
}

void br::on_iniciar_clicked()
{
    ult = 0;
    ui->tableWidget_2->setRowCount(0);

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

    ui->iniciar->setDisabled( true );

    Algoritmos_de_TT->Nombre = "BR";
    ruta1 = &Algoritmos_de_TT->mat;
    ruta = Algoritmos_de_TT->Algoritmos;
    ruta->detener = false;
    ruta->iniciado = false;

    if( ruta1->getfil() <= 0 || ruta1->getcol() <= 0 ) return;

    char cad[100];
    sprintf(cad, "Cantidad de Testores Tipicos: %d", 0);
    ui->label_4->setText( cad );

    timer = new QTimer(this);
    reloj = new QTime(0,0,0);
    ui->reloj->setText( reloj->toString(Qt::TextDate) );

    timer->start( 1000 );
    connect( timer, SIGNAL(timeout()),this, SLOT( actualizar( ) ) );
    Algoritmos_de_TT->start();
}

void br::on_detener_clicked()
{
    if( Algoritmos_de_TT != 0 )
      ruta->detener = true;
}

void br::actualizar( )
{
    if( ruta->iniciado == false )return;

    *reloj = reloj->addSecs( 1 );
    ui->reloj->setText( reloj->toString(Qt::TextDate) );

    int n = ruta->num_TT;
    int cant_rasg = ruta->mask_TT->cant_bits();

    //Actrualizar la detencion
    if( ui->check1->isChecked() && n >= ui->numTT->value()  )
        ruta->detener = true;

    if( ui->check2->isChecked() && cant_rasg >= ui->porciento->value()*ruta1->getcol()  )
        ruta->detener = true;

    ///-END---
    if( ruta->detener == true || isActiveWindow() == false ){
        timer->stop();
        Algoritmos_de_TT->terminate();
        ui->iniciar->setDisabled( false );
        //delete Algoritmos_de_TT;
    }

    ui->tableWidget_2->setRowCount( n );
    char cad[100];
    sprintf(cad, "Cantidad de Testores Tipicos: %d", n);
    ui->label_4->setText( cad );

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
                nomb += ruta->Trasg[i];
            }
        nomb = test + " = {" + nomb + "}";
        valor = new QTableWidgetItem(nomb);
        ui->tableWidget_2->setItem( ult, 0, valor );
    }

    // Actualizar variables
    if( ui->intervalo->value() == 0 || reloj->second()%ui->intervalo->value() != 0 ) return;

    sprintf(cad, "%d", n );
    valor = new QTableWidgetItem(cad);
    ui->tableWidget->setItem( 0, 1, valor );
}
