#ifndef MA_MD_H
#define MA_MD_H


#include <QMainWindow>
//#include "md.h"
namespace Ui {
    class ma_md;
}

class ma_md : public QMainWindow{
    Q_OBJECT
public:
    ma_md(QWidget *parent = 0);
    ~ma_md();
    void vaule_umbral( QString*, int );
    double *umbral;
    bool terminado;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ma_md *m_ui;

private slots:
    void on_comboBox_currentIndexChanged(QString );
    void on_tableWidget_cellChanged(int row, int column);
    void on_pushButton_clicked();
    void on_ma_md_destroyed();
    void on_OK_clicked();
    void combobox( int );
};

#endif // MA_MD_H
