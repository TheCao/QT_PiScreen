#ifndef AIRLYPARSER_H
#define AIRLYPARSER_H

#include "jsonparser.h"
#include "networkmanager.h"

// dodanie QObject
#include <QObject>

class airlyParser : public QObject
{
    Q_OBJECT
public:
    explicit airlyParser();
    ~airlyParser();
    void requestForMeasurements(int stationID);
    void requestForInstallationData(int stationID);
signals:
    void dataParsed(jsonParser::DanePomiarowe *dane);
    //void dataParsed(jsonParser::DaneStacji *dane);

private:
    jsonParser parser;
    NetworkManager networkManagerObject;
private slots:
    void parseReplyFromNetworkManagerObject();




};

#endif // AIRLYPARSER_H
