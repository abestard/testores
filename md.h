#ifndef MD_H
#define MD_H
#include "matrix.h"
#include "fichero.h"
#include "mb.h"
#include "generar_md.h"
#include <QMainWindow>

namespace Ui {
    class md;
}

class md : public QMainWindow {
    Q_OBJECT
public:
    md(QWidget *parent = 0);
    ~md();
    void mostrar_matrix( matrix );

protected:
    void changeEvent(QEvent *e);

private:
    Ui::md *m_ui;
    fichero fich;
    mb v_mb;
    generar_md *v_generar_md;
    QTimer *timer;


private slots:
    void on_actionGenerar_triggered();
    void on_actionConvertir_a_MB_triggered();
    void on_actionSalvar_triggered();
    void on_actionCargar_triggered();
    void on_crear_tabla_clicked();
    void end_generar_md( );
};

#endif // MD_H
