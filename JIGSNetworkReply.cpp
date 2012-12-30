#include "JIGSNetworkReply.h"

JIGSNetworkReply::JIGSNetworkReply( QNetworkReply* reply):QObject()
{
    this->reply=reply;
    QObject::connect(reply,SIGNAL(finished()),this,SLOT(afterFinish()));
}

void JIGSNetworkReply::setFileName(QString fileName)
{
    this->fileName=fileName;
}

void JIGSNetworkReply::afterFinish()
{
    emit downloadedData(reply->readAll(),fileName);
}

JIGSNetworkReply* JIGSNetworkReply::getJIGSNetworkReply()
{
    return this;
}
