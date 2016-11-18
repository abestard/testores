#ifndef BR_H
#define BR_H

#include <QMainWindow>
#include "mythread.h"
#include "fichero.h"

namespace Ui {
class br;
}

class br : public QMainWindow
{
    Q_OBJECT

public:
    explicit br(QWidget *parent = 0);
    ~br();

private slots:
    void on_iniciar_clicked();
    void on_detener_clicked();
    void actualizar( );

private:
    Ui::br *ui;
    QTimer *timer;
    QTime *reloj;
    fichero fich;
    MyThread *Algoritmos_de_TT;
    Teoria_de_Testores *ruta;
    matrix *ruta1;
    int ult;
};

#endif // BR_H
