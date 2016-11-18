#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ma.h"
#include "md.h"
#include "mb.h"
#include "bt.h"
#include "lex.h"
#include "br.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionMatriz_de_Aprendizaje_triggered();

    void on_actionMatriz_de_Diferencias_triggered();

    void on_actionMatriz_B_sica_triggered();

    void on_actionAlgoritmo_BT_triggered();

    void on_actionAlgoritmo_LEX_triggered();

    void on_actionAlgoritmo_BR_triggered();

private:
    Ui::MainWindow *ui;
    ma v_ma;
    md v_md;
    mb v_mb;
    BT v_bt;
    lex v_lex;
    br v_br;
};

#endif // MAINWINDOW_H
