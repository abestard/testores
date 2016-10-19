#ifndef BT_H
#define BT_H
#include "fichero.h"
#include <QTimer>
#include <QMainWindow>
#include "mythread.h"

namespace Ui {
    class BT;
}

class BT : public QMainWindow {
    Q_OBJECT
public:
    BT(QWidget *parent = 0);
    ~BT();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::BT *m_ui;
    QTimer *timer;
    QTime *reloj;
    fichero fich;
    int ult;
    MyThread *Algoritmos_de_TT;
    Teoria_de_Testores *ruta;
    matrix *ruta1;


private slots:
    void on_detener_clicked();
    void on_iniciar_clicked();
    void actualizar();
};

#endif // BT_H
