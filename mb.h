#ifndef MB_H
#define MB_H
#include "fichero.h"
#include "generar_md.h"
#include <QMainWindow>

namespace Ui {
    class mb;
}

class mb : public QMainWindow {
    Q_OBJECT
public:
    mb(QWidget *parent = 0);
    ~mb();
    void mostrar_matrix( matrix );


protected:
    void changeEvent(QEvent *e);

private:
    Ui::mb *m_ui;
    fichero fich;
    QTimer *timer;
    generar_md *v_generar_md;

private slots:

private slots:
    void on_actionGenerar_triggered();
    void on_actionSalvar_triggered();
    void on_actionCargar_triggered();
    void on_crear_tabla_clicked();
    void end_generar_mb( );
};

#endif // MB_H
