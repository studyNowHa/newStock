#ifndef A_H
#define A_H
#include <QStandardItemModel>
#include <QVector>
#include <QMutex>
#include "structstock.h"
#include <QDebug>

extern int a;
extern QStandardItemModel* model;
extern QVector<structStock> *stock_vector;//全局变量 所有股票
extern QVector<structStock> *stock_vector_limit_up;//全局变量 涨停股票
extern bool append(structStock stock_data);
extern bool update(structStock stock_data);
extern bool qdebug(QVector<structStock> stock_vector_global);
extern bool sort(QVector<structStock> stock_vector_global);
//QMutex mutex;
#endif // A_H
