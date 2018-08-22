#include "httpqq.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QNetworkAccessManager>
#include <QThread>
#include <QEventLoop>
#include <QStringList>
#include <QStandardItemModel>
#include <QtAlgorithms>
#include "stockglobaldata.h"
#include "global.h"

//extern QStandardItemModel* model;

bool compareStock(const structStock &stock_data1, const structStock &stock_data2)
{
    //    qDebug()<<"stock_data1.stock_uplift_percent = "<<stock_data1.stock_uplift_percent;
    if(stock_data1.stock_uplift_percent.toFloat() > stock_data2.stock_uplift_percent.toFloat()){
        return true;
    }else {
        return false;
    }
}

httpQQ::httpQQ(QString num){
    //    QMutexLocker locker(&mutex);  //使用互斥体锁住此函数，同一时刻只有一个线程可以使用此函数
    QString stock = "http://qt.gtimg.cn/q=" + num;
    //是否存在这个股票或者停牌，没有就删除
    this->getStockData(stock);
    if(stock_data.stock_state){
        //        stock_vector->append(stock_data);//增加到股票池
        //        stockGlobalData stock_global_data;
        //        stock_global_data.append(stock_data);
        append(stock_data);
        while(1){
            //更新数据
            if(stock_data.stock_get_data_state){
                //如果涨停加入涨停股票池
                if(stock_data.stock_sell_volume == "0" && stock_data.stock_price ==
                        stock_data.stock_limit_up_price && stock_data.stock_limit_up_price != "0.00")
                {//涨停判断，当前价格等于涨停价，并且卖一量为0,并且涨停价不为0。
                    //去重复判断
                    if(stock_vector_limit_up->size() == 0){
                        stock_vector_limit_up->append(stock_data);
                    }else{
                        for(int i =0; i<stock_vector_limit_up->size(); i++){
                            if(stock_vector_limit_up->at(i).stock_name != stock_data.stock_name){
                                stock_vector_limit_up->append(stock_data);
                            }
                        }
                    }
                }
                update(stock_data);
//                sort(*stock_vector);
                qdebug(*stock_vector);
            }
            QThread::sleep(1);//降低CPU使用率
        }

    }
}

httpQQ::~httpQQ()
{
    netWork->deleteLater();
    //    reply->deleteLater();
    qDebug()<< "~httpQQ" << endl;
}

bool httpQQ::compareStockData(const structStock &stock_data1, const structStock &stock_data2)
{
    if(stock_data1.stock_uplift_percent > stock_data2.stock_uplift_percent){
        return true;
    }else if(stock_data1.stock_uplift_percent < stock_data2.stock_uplift_percent){
        return false;
    }
}

void httpQQ::replyFinished(QNetworkReply *replys)
{
    QString all = QString::fromLocal8Bit(replys->readAll());
    qDebug()<< all << endl;
    replys->deleteLater();
    replyState = true;
    qDebug()<< "replyFinished" << endl;
}

void httpQQ::replyreadyRead()
{
    //    QString all = QString::fromLocal8Bit(reply->readAll());
    //    qDebug()<< all << endl;
    //    qDebug()<< "replyreadyRead" << endl;
}

structStock *httpQQ::getStockData(QString num)
{
    QNetworkReply *replys;
    QEventLoop eventLoop;
    QObject::connect(netWork, SIGNAL(finished(QNetworkReply*)),&eventLoop,SLOT(quit()));
    replys =netWork->get(QNetworkRequest(QUrl(num)));
    eventLoop.exec();
    QString all = QString::fromLocal8Bit(replys->readAll());
    //判断是否有"~"
    if(all.contains("~",Qt::CaseSensitive)){
        QStringList stock_list = all.split("~");
        //判断长度的有效性
        if(stock_list.count()>48){
            //判断数据的有效性
            stock_data.stock_name = stock_list.at(1);
            stock_data.stock_num = stock_list.at(2);
            stock_data.stock_price = stock_list.at(3);
            stock_data.stock_sell_volume = stock_list.at(20);
            stock_data.stock_limit_up_price = stock_list.at(47);
            stock_data.stock_uplift_percent = stock_list.at(32);
            if(!stock_data.stock_name.isEmpty() &&  !stock_data.stock_num.isEmpty() &&
                    !stock_data.stock_price.isEmpty() && !stock_data.stock_sell_volume.isEmpty()
                    && !stock_data.stock_limit_up_price.isEmpty() && !stock_data.stock_uplift_percent.isEmpty()){
                if(stock_data.stock_limit_up_price.toFloat() == 0){
                    stock_data.stock_state = false;
                    delete replys;
                    return &stock_data;
                }
                stock_data.stock_get_data_state = true;
            }else{
                stock_data.stock_get_data_state = false;
            }
        }else{
            stock_data.stock_get_data_state = false;
        }
        delete replys;
        return &stock_data;
    }else{
        stock_data.stock_get_data_state = false;
        delete replys;
        return &stock_data;
    }
}
