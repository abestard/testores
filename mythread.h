#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QtCore>
#include "teoria_de_testores.h"

class MyThread : public QThread
{
public:
    MyThread();
    ~MyThread();
    void run();
    QString Nombre;
    matrix mat;
    Teoria_de_Testores *Algoritmos;
};

#endif // MYTHREAD_H
