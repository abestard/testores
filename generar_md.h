#ifndef GENERAR_MD_H
#define GENERAR_MD_H

#include <QMainWindow>

namespace Ui {
    class generar_md;
}

class generar_md : public QMainWindow {
    Q_OBJECT
public:
    generar_md(QWidget *parent = 0);
    ~generar_md();
    bool terminado;
    int tip;
    double porciento;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::generar_md *m_ui;

private slots:
    void on_comboBox_currentIndexChanged(QString );
    void on_pushButton_clicked();
};

#endif // GENERAR_MD_H
