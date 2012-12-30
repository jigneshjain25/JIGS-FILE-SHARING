#ifndef JIGSREPLY_H
#define JIGSREPLY_H

#include <QNetworkReply>

#include "JIGSNetworkReply.h"

class JIGSNetworkReply:public QObject
{
    Q_OBJECT    

public:
    JIGSNetworkReply(QNetworkReply*);
    void setFileName(QString);
    JIGSNetworkReply* getJIGSNetworkReply();

    QNetworkReply* reply;
    QString fileName;

signals:
    void downloadedData(QByteArray,QString);

public slots:
    void afterFinish();    
};

#endif // JIGSREPLY_H
