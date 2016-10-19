#ifndef LEX_H
#define LEX_H

#include <QMainWindow>
#include "mythread.h"
#include "fichero.h"

namespace Ui {
    class lex;
}

class lex : public QMainWindow {
    Q_OBJECT
public:
    lex(QWidget *parent = 0);
    ~lex();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::lex *m_ui;
    QTimer *timer;
    QTime *reloj;
    fichero fich;
    MyThread *Algoritmos_de_TT;
    Teoria_de_Testores *ruta;
    matrix *ruta1;
    int ult;

private slots:
    void on_detener_clicked();
    void on_iniciar_clicked();
    void actualizar();
};

#endif // LEX_H
