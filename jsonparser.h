#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QDateTime>



class jsonParser
{
public:
    explicit jsonParser();
    ~jsonParser();
    bool openJsonFile(QString filePath);
    bool openJsonQString(QString &string);
    bool parseMeasurements();
    bool parseInstallation();
    void parsingDebug();
    struct DanePomiarowe
    {
        QDateTime dateValue;
        double pm1Value;
        double pm25Value;
        double pm10Value;
        double pressureValue;
        double humidityValue;
        double temperatureValue;
        QString indexName;
        double indexValue;
        QString indexLevel;
        QString indexColor;
        QString indexDescription;
        QString indexAdvice;
        double standardsPm25Limit;
        double standardsPm25Percent;
        double standardsPm10Limit;
        double standardsPm10Percent;
    }danePomiarowe;

    struct DaneStacji
    {
        uint ID;
        float latitute;
        float longitude;
        QString country;
        QString city;
        QString street;
        QString number;
        QString displayAddress1;
        QString displayAddress2;
    }daneStacji;

private:
    QJsonDocument *jsonDocument;

};

#endif // JSONPARSER_H
