#include "mb.h"
#include "ui_mb.h"
#include "matrix.h"

mb::mb(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::mb)
{
    m_ui->setupUi(this);

    ///
    m_ui->fila->setValue( 10 );
    m_ui->columna->setValue(10);

    int tam = 0;
    matrix mat( 10, 10 ), tmp;

    while( tam != 10 ){

        mat.generar_MD( 0 );
        tmp = mat.conv_MD_MB(true);
        tam = tmp.getfil();
    }

        tmp.conv_a_Tabla( m_ui->tableWidget, false );
    ///
}

mb::~mb()
{
    delete m_ui;
}

void mb::changeEvent(QEvent *e)
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

void mb::on_crear_tabla_clicked()
{
  int fil = m_ui->fila->value();
  int col = m_ui->columna->value();

  if( fil <= 0 || col <= 0 ) return;

  m_ui->tableWidget->setRowCount( fil + 1 );
  m_ui->tableWidget->setColumnCount( col + 1 );

  QTableWidgetItem *valor;
  for( int i = 1; i <= fil; i ++ )
      for( int j = 1; j <= col; j ++ ){
         valor = new QTableWidgetItem();
         valor->setBackground( Qt::lightGray );
         m_ui->tableWidget->setItem( i, j, valor );
      }

  for( int j = 1; j < col+1; j ++ ){
      valor = new QTableWidgetItem();
      valor->setBackground( Qt::darkGray );
      m_ui->tableWidget->setItem( 0, j, valor );
  }

  for( int i = 0; i < fil+1; i ++ ){
       valor = new QTableWidgetItem();
       valor->setBackground( Qt::darkGray );
       m_ui->tableWidget->setItem( i, 0, valor );
   }

  //bloquer item
  valor = new QTableWidgetItem("Objts/Descipciones");
  valor->setFlags(Qt::NoItemFlags);
  valor->setFlags(Qt::ItemIsEnabled);
  valor->setBackground( Qt::darkGray );
  m_ui->tableWidget->setItem( 0, 0, valor );
}

void mb::on_actionGenerar_triggered()
{
    int fil = m_ui->tableWidget->rowCount()-1;
    int col = m_ui->tableWidget->columnCount()-1;

    if( fil <= 0 || col <= 0 ) return;

    timer = new QTimer(  );
    v_generar_md = new generar_md();
    timer->start( 300 );
    connect( timer, SIGNAL( timeout()), this, SLOT( end_generar_mb( ) ) );
    v_generar_md->show();
}

void mb::end_generar_mb( ){
    if( v_generar_md->isActiveWindow() ) return;

    timer->stop();

    if( !v_generar_md->terminado ) return;

    int fil = m_ui->fila->value();
    int col = m_ui->columna->value();

    int tam = 0;
    matrix mat( fil, col ), tmp;

    while( tam != fil ){
        if( v_generar_md->tip == 1/*"aleatorio"*/ )
            mat.generar_MD( 0 );
        else
            mat.generar_MD( 1, v_generar_md->porciento );
        tmp = mat.conv_MD_MB(true);
        tam = tmp.getfil();
    }


    tmp.conv_a_Tabla( m_ui->tableWidget, false );
}

void mb::on_actionCargar_triggered()
{
    matrix mat = fich.cargar_matrix(  );

    if( mat.tip != 2 ){
        QMessageBox *error;
        error = new QMessageBox();
        error->setText( "Matriz no valida" );
        error->show();
        return;
    }

    m_ui->fila->setValue( mat.getfil() );
    m_ui->columna->setValue( mat.getcol() );
    mat.conv_a_Tabla( m_ui->tableWidget, false );
}

void mb::on_actionSalvar_triggered()
{
    fich.salvar_tabla( m_ui->tableWidget, 2 );
}

void mb::mostrar_matrix( matrix mat ){
    mat.conv_a_Tabla( m_ui->tableWidget, false );
    m_ui->fila->setValue( mat.getfil() );
    m_ui->columna->setValue( mat.getcol() );
}
