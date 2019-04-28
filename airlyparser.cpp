#include "airlyparser.h"


airlyParser::airlyParser()
{

    connect(&this->networkManagerObject, &NetworkManager::replyReaded,
            this, &airlyParser::parseReplyFromNetworkManagerObject);

}

airlyParser::~airlyParser()
{

}

void airlyParser::requestForMeasurements(int stationID)
{
    QString requestString = "http://airapi.airly.eu/v2/measurements/installation?indexType=AIRLY_CAQI&installationId=";
    requestString.append(QString::number(stationID));
    this->networkManagerObject.request(requestString);
}

void airlyParser::requestForInstallationData(int stationID)
{
    QString requestString = "https://airapi.airly.eu/v2/installations/";
    requestString.append(QString::number(stationID));
    this->networkManagerObject.request(requestString);
}
void airlyParser::parseReplyFromNetworkManagerObject()
{
    if (this->parser.openJsonQString(networkManagerObject.reply))
    {
        this->parser.parseMeasurements();
        emit(dataParsed(&this->parser.danePomiarowe));
        //this->parser.parseInstallation();
        //emit(dataParsed(&this->parser.daneStacji));
    }
}





