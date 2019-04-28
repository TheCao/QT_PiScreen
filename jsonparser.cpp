#include "jsonparser.h"

jsonParser::jsonParser()
{

}

bool jsonParser::openJsonFile(QString filePath)
{
    QFile jsonFile(filePath);
    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Blad otarcia pliku" << jsonFile.fileName() << ".Err code: " << jsonFile.errorString();
        return false;
    }
    QByteArray jsonData(jsonFile.readAll());
    if (jsonFile.error() != QFile::NoError)
    {
        qDebug() << QString("Blad odczytu z plku %1, error: %2").arg(jsonFile.fileName()).arg(jsonFile.errorString());
        return false;
    }
    if(jsonData.isEmpty())
    {
        qDebug() << "Brak danych w pliku" << jsonFile.fileName();
        return false;
    }
    jsonDocument = new QJsonDocument(QJsonDocument::fromJson(jsonData));
    if(!jsonDocument->isObject())
    {
        jsonDocument = nullptr;
        qDebug() << "Error @ jsonParser::openJsonFile() Dokument nie jest obiektem"; //TODO dopracuj error messages
        return false;
    }
    if(jsonDocument->isNull())
    {
       qDebug() << "Dokument jest pusty!";
       return false;
    }
    return true;
}

bool jsonParser::openJsonQString(QString &string)
{
    QByteArray jsonData;
    jsonData.append(string);
    if(jsonData.isEmpty())
    {
        qDebug() << "Brak danych w pobranym pliku json";
        return false;
    }
    jsonDocument = new QJsonDocument(QJsonDocument::fromJson(jsonData));
    if(!jsonDocument->isObject())
    {
        jsonDocument = nullptr;
        qDebug() << "Error @ jsonParser::openJsonQString() Dokument nie jest obiektem";
        return false;
    }
    if(jsonDocument->isNull())
    {
       qDebug() << "Dokument jest pusty!";
       return false;
    }
    return true;
}

jsonParser::~jsonParser()
{
    delete jsonDocument;
}





bool jsonParser::parseMeasurements()
{
    QJsonObject jsonObject = jsonDocument->object();
    QJsonObject currentObject = jsonObject.value("current").toObject();
    //QJsonArray historyArray = jsonObject.value("history").toArray();
    //QJsonArray forecastArray = jsonObject.value("forecast").toArray(); //trzeba by wydobyc forecast na najblizsze godziny a nie wszystko

    // data pomiaru
    this->danePomiarowe.dateValue = QDateTime::fromString(currentObject.value("fromDateTime").toString(), "yyyy-MM-ddTHH:mm:ss.zzzZ");

    QJsonArray valuesTab  = currentObject.value("values").toArray();
    QJsonObject indexesTabObj = (currentObject.value("indexes").toArray())[0].toObject(); //only one object in indexesTab
    QJsonArray standardsTab = currentObject.value("standards").toArray();
    // dane z current->values - każda wartość to jednen element tablicy
    for (int i=0; i<valuesTab.size();i++)
    {
       if(!QString::compare(valuesTab[i].toObject().value("name").toString(), "PM1"))
       {
           this->danePomiarowe.pm1Value = valuesTab[i].toObject().value("value").toDouble();
       }
       if(!QString::compare(valuesTab[i].toObject().value("name").toString(), "PM10"))
       {
           this->danePomiarowe.pm10Value = valuesTab[i].toObject().value("value").toDouble();
       }
       if(!QString::compare(valuesTab[i].toObject().value("name").toString(), "PM25"))
       {
           this->danePomiarowe.pm25Value = valuesTab[i].toObject().value("value").toDouble();
       }
       if(!QString::compare(valuesTab[i].toObject().value("name").toString(), "PRESSURE"))
       {
           this->danePomiarowe.pressureValue = valuesTab[i].toObject().value("value").toDouble();
       }
       if(!QString::compare(valuesTab[i].toObject().value("name").toString(), "HUMIDITY"))
       {
           this->danePomiarowe.humidityValue = valuesTab[i].toObject().value("value").toDouble();
       }
       if(!QString::compare(valuesTab[i].toObject().value("name").toString(), "TEMPERATURE"))
       {
           this->danePomiarowe.temperatureValue = valuesTab[i].toObject().value("value").toDouble();
       }
    }

    // dane z current->indexes
    this->danePomiarowe.indexName = indexesTabObj.value("name").toString();
    this->danePomiarowe.indexColor = indexesTabObj.value("color").toString();
    this->danePomiarowe.indexLevel = indexesTabObj.value("level").toString();
    this->danePomiarowe.indexValue = indexesTabObj.value("value").toDouble();
    this->danePomiarowe.indexDescription = indexesTabObj.value("description").toString();
    this->danePomiarowe.indexAdvice = indexesTabObj.value("advice").toString();

    // dane z current->standards
    for (int i = 0; i<standardsTab.size(); i++)
    {
        if(!QString::compare(standardsTab[i].toObject().value("pollutant").toString(), "PM10"))
        {
            this->danePomiarowe.standardsPm10Limit = standardsTab[i].toObject().value("limit").toDouble();
            this->danePomiarowe.standardsPm10Percent = standardsTab[i].toObject().value("percent").toDouble();
        }
        else if(!QString::compare(standardsTab[i].toObject().value("pollutant").toString(), "PM25"))
        {
            this->danePomiarowe.standardsPm25Limit = standardsTab[i].toObject().value("limit").toDouble();
            this->danePomiarowe.standardsPm25Percent = standardsTab[i].toObject().value("percent").toDouble();
        }
    }
    //TODO Dopisz warunki dla których funkcja zwraca false
    return true;
}
bool jsonParser::parseInstallation()
{
    qDebug() << "Odpalilem parserInstallation()";
    return true;
}
void jsonParser::parsingDebug()
 {
     qDebug() << "PM1: " << this->danePomiarowe.pm1Value << endl
              << "PM10: " << this->danePomiarowe.pm10Value << endl
              << "PM25: " << this->danePomiarowe.pm25Value << endl
              << "Date: " << this->danePomiarowe.dateValue.date().toString()
                          << this->danePomiarowe.dateValue.time().toString() << endl
              << "Index name: " << this->danePomiarowe.indexName << endl
              << "Index color: " << this->danePomiarowe.indexColor << endl
              << "Index level: " << this->danePomiarowe.indexLevel << endl
              << "Index Value: " << this->danePomiarowe.indexValue << endl
              << "Humidity: " << this->danePomiarowe.humidityValue << endl
              << "Pressure: " << this->danePomiarowe.pressureValue << endl
              << "Temperature: " << this->danePomiarowe.temperatureValue << endl
              << "PM10 Limit: " << this->danePomiarowe.standardsPm10Limit << endl
              << "PM25 Limit: " << this->danePomiarowe.standardsPm25Limit << endl
              << "PM10 Percent: " << this->danePomiarowe.standardsPm10Percent << endl
              << "PM25 Percent: " << this->danePomiarowe.standardsPm25Percent << endl
              << "Opis: " << this->danePomiarowe.indexDescription << endl
              << "Porada: " << this->danePomiarowe.indexAdvice << endl;
 }




