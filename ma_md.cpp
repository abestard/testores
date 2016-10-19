#include "ma_md.h"
#include "ui_ma_md.h"
#include <QtGui>
#include "md.h"

ma_md::ma_md(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::ma_md)
{
    m_ui->setupUi(this);
    terminado = false;
}

ma_md::~ma_md()
{
    delete m_ui;
}

void ma_md::changeEvent(QEvent *e)
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

void ma_md::vaule_umbral( QString *rasg, int n ){
   m_ui->tableWidget->setRowCount( n );
   QTableWidgetItem *valor;
   QStringList list;
   list << "mayor que un umbral" << "igualdad estricta";
   QComboBox *comb;
   QDoubleSpinBox *spin;
   QSignalMapper *mapa;
   mapa = new QSignalMapper (this);
   for( int i = 0; i < n; i ++ ){
       valor = new QTableWidgetItem( rasg[i] );
       valor->setFlags( Qt::NoItemFlags );
       valor->setFlags(Qt::ItemIsEnabled);
       m_ui->tableWidget->setItem( i, 0, valor );
       spin = new QDoubleSpinBox();
       spin->setMaximum( 100.00 );
       m_ui->tableWidget->setCellWidget( i, 2, spin );
       comb = new QComboBox( );
       comb->addItems( list );
       connect( comb, SIGNAL( currentIndexChanged(QString)), mapa, SLOT(map()) );
       mapa->setMapping( comb, i );
       m_ui->tableWidget->setCellWidget( i, 1, comb );
   }

   connect( mapa, SIGNAL(mapped(int)), this, SLOT( combobox(int) ) );
}

void ma_md::on_OK_clicked()
{
    int n = m_ui->tableWidget->rowCount();
    QString string;
    QComboBox *comb;
    QDoubleSpinBox *spin;
    umbral = new double[n];
    for( int i = 0; i < n ; i ++ ){
      comb = (QComboBox*)m_ui->tableWidget->cellWidget(i,1);

      spin = (QDoubleSpinBox*)m_ui->tableWidget->cellWidget(i,2);

      if( comb->currentText() == "igualdad estricta" )
        umbral[i] = 0;
      else
        umbral[i] = spin->value();
    }

    close();
    terminado = true;
}

void ma_md::on_ma_md_destroyed(){  /*nada*/   }


void ma_md::on_pushButton_clicked()
{
    QComboBox *comb;
    QDoubleSpinBox *spin;
    for( int i = 0; i < m_ui->tableWidget->rowCount(); i ++ ){
        comb = (QComboBox*)m_ui->tableWidget->cellWidget( i,1 );
        comb->setCurrentIndex( m_ui->comboBox->currentIndex() );
        spin = (QDoubleSpinBox*)m_ui->tableWidget->cellWidget( i,2 );
        spin->setValue( m_ui->doubleSpinBox->value() );
    }

    //connect(m_ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT( act() );
}

void ma_md::on_tableWidget_cellChanged(int row, int column)
{
    QString string;

    if( column == 1 ){
        string = m_ui->tableWidget->item(row, column)->text();
        if( string == "igualdad estricta" ){
           m_ui->tableWidget->item( row, 2 )->setFlags( Qt::NoItemFlags );
          // m_ui->tableWidget->item( row, 2 )->setFlags( Qt::ItemIsEnabled );
        }
        else{
           m_ui->tableWidget->item( row, 2 )->setFlags( Qt::ItemIsEditable );
           m_ui->tableWidget->item( row, 2 )->setFlags( Qt::ItemIsSelectable );
        }
    }
}

void ma_md::combobox( int row ){
    QComboBox *comb;

        comb = (QComboBox*)m_ui->tableWidget->cellWidget( row, 1 );
        if( comb->currentText() == "igualdad estricta" ){
           m_ui->tableWidget->cellWidget( row, 2 )->setDisabled( true );
          // m_ui->tableWidget->item( row, 2 )->setFlags( Qt::ItemIsEnabled );
        }
        else{
           m_ui->tableWidget->cellWidget( row, 2 )->setDisabled( false );
        }

}

void ma_md::on_comboBox_currentIndexChanged(QString tip )
{
    if( tip == "igualdad estricta" )
        m_ui->doubleSpinBox->setDisabled( true );
    else
        m_ui->doubleSpinBox->setDisabled( false );
}
