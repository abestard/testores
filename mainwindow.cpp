#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionMatriz_de_Aprendizaje_triggered()
{
    v_ma.show();
}

void MainWindow::on_actionMatriz_de_Diferencias_triggered()
{
    v_md.show();
}

void MainWindow::on_actionMatriz_B_sica_triggered()
{
    v_mb.show();
}

void MainWindow::on_actionAlgoritmo_BT_triggered()
{
    v_bt.show();
}

void MainWindow::on_actionAlgoritmo_LEX_triggered()
{
    v_lex.show();
}

void MainWindow::on_actionAlgoritmo_BR_triggered()
{
    v_br.show();
}
