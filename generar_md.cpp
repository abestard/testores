#include "generar_md.h"
#include "ui_generar_md.h"

generar_md::generar_md(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::generar_md)
{
    terminado = false;
    m_ui->setupUi(this);
}

generar_md::~generar_md()
{
    terminado = false;
    delete m_ui;
}

void generar_md::changeEvent(QEvent *e)
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

void generar_md::on_pushButton_clicked()
{
  terminado = true;
  tip = m_ui->comboBox->currentIndex();
  if( tip != 1/*"aleatorio"*/ )
      porciento = m_ui->doubleSpinBox->value();

  close();
}

void generar_md::on_comboBox_currentIndexChanged( QString tip )
{
    if( tip == "aleatorio" )
      m_ui->doubleSpinBox->setDisabled( true );
    else
      m_ui->doubleSpinBox->setDisabled( false );
}
