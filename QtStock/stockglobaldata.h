#ifndef STOCKGLOBALDATA_H
#define STOCKGLOBALDATA_H
//#include "global.h"
#include <QMutex>
#include "structstock.h"
#include <QVector>
#include <QtAlgorithms>
#include <QDebug>

extern QVector<structStock> *stock_vector;//全局变量 所有股票
extern QVector<structStock> *stock_vector_limit_up;//全局变量 涨停股票

class stockGlobalData
{
public:
    stockGlobalData();
//    bool append(structStock stock_data);
//    bool replace(int i, structStock stock_data);
//    bool sort(QVector<structStock> stock_vector_global);
//    bool update(structStock stock_data);
//    bool qdebug(QVector<structStock> stock_vector_global);
//    QMutex mutex;
private:
//    bool compare(const structStock &stock_data1, const structStock &stock_data2);

};

#endif // STOCKGLOBALDATA_H
