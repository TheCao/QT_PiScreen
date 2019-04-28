#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    QString reply;
    explicit NetworkManager(QObject *parent = nullptr);
    void request(QString webpage);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);




signals:
    void sendReply(QString reply);
    void replyReaded();


public slots:
void replyFinished(QNetworkReply *reply);
private:


};

#endif // NETWORKMANAGER_H
