#include "stockglobaldata.h"
//全局函数
//bool compare(const structStock &stock_data1, const structStock &stock_data2)
//{
//    if(stock_data1.stock_uplift_percent.toFloat() > stock_data2.stock_uplift_percent.toFloat()){
//        return true;
//    }else {
//        return false;
//    }
//}

stockGlobalData::stockGlobalData()
{

}

//bool stockGlobalData::append(structStock stock_data)
//{
//    mutex.lock();
//    stock_vector->append(stock_data);
//    mutex.unlock();
//    return true;
//}

//bool stockGlobalData::replace(int i, structStock stock_data)
//{
//    mutex.lock();
//    stock_vector->replace(i,stock_data);
//    mutex.unlock();
//    return true;
//}

//bool stockGlobalData::sort(QVector<structStock> stock_vector_global)
//{
//    mutex.lock();
//    qSort(stock_vector_global.begin(),stock_vector_global.end(),compare);
//    mutex.unlock();
//    return true;
//}

//bool stockGlobalData::update(structStock stock_data)
//{
//    mutex.lock();
//    for(int i =0; i<stock_vector->size(); i++){
//        if(stock_vector->at(i).stock_name == stock_data.stock_name){
//            stock_vector->replace(i,stock_data);
//            break;
//        }
//    }
//    mutex.unlock();
//    return true;
//}

//bool stockGlobalData::qdebug(QVector<structStock> stock_vector_global)
//{
//    mutex.lock();
//    qDebug()<<stock_vector_global.size();
//    for(int i =0; i<stock_vector_global.size(); i++){
//       qDebug()<<stock_vector_global.at(i).stock_num<<stock_vector_global.at(i).stock_uplift_percent;
//    }
//    qDebug()<<endl;
//    mutex.unlock();
//    return true;
//}


