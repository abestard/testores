#ifndef MA_H
#define MA_H
#include <QFileDialog>
#include <Qfile.h>
#include <QTextStream>
#include <QMainWindow>
#include <string>
#include "fichero.h"
#include "md.h"
#include <ma_md.h>
#include "matrix.h"

namespace Ui {
    class ma;
}

class ma : public QMainWindow {
    Q_OBJECT
public:
    ma(QWidget *parent = 0);
    ~ma();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ma *m_ui;
    fichero fich;
    md v_md;
    ma_md v_ma_md;
    QTimer *timer;
    matrix MA;

    private slots:
    void on_actionGenerar_triggered();
    void end_ma_md( );
    void on_actionConvertir_a_MD_triggered();
    void on_actionCargar_triggered();
    void on_actionSalvar_triggered();
    void on_crear_tabla_clicked();
};

#endif // MA_H
