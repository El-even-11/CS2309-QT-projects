#ifndef LOADTHREAD_H
#define LOADTHREAD_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include "poi.h"

class LoadThread : public QThread
{
     Q_OBJECT
public:
    explicit LoadThread(QObject *parent = nullptr);
    void setFile(QFile* file){
        this->file = file;
    }

protected:
    void run() override{
        QTextStream in(file);
        data = new QList<POI*>;

        int readBytes = 0;
        int factor = 0;
        int interval = file->size() / 100;
        while (!in.atEnd()){
            QString line = in.readLine();
            readBytes+=line.length()+2;
            QStringList list=line.split(",");

            POI* poi=new POI(list[0].toInt(),list[1].toInt(),list[2],list[3].toDouble(),list[4].toDouble());
            (*data) << poi;

            if (readBytes > interval*factor){
                emit sendNum(readBytes);
                factor++;
            }
        }
        emit sendNum(file->size());
        emit sendData(data);
    }

signals:
    void sendNum(int a);
    void sendData(QList<POI*>* data);

private:
    QFile* file;
    bool running;
    QList<POI*>* data;
};

#endif // LOADTHREAD_H
