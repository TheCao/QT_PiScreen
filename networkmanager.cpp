#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
    connect(manager, &QNetworkAccessManager::finished, this,&NetworkManager::replyFinished);
}

void NetworkManager::request(QString webpage)
{
    QNetworkRequest request;
    request.setUrl((QUrl(webpage)));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("accept-Language", "pl");
    request.setRawHeader("apikey", "pO3iwCvyDDaM3AQM0xV3u7P2zEgIUi1w");
    manager->get(request);
}



void NetworkManager::replyFinished(QNetworkReply *reply)
{

    QString fullreply = reply->readAll();
    if(!fullreply.isEmpty())
    {
        this->reply = fullreply;
   }
   else {
       this->reply = "Got Error. Sorry";
       qDebug() << "Error";
   }
   emit(replyReaded());


}

