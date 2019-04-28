#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    airly(new airlyParser)
{
    connect(airly,&airlyParser::dataParsed, this, &MainWindow::updateAirlyScreenData);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete airly;
    delete ui;
}

void MainWindow::on_button_pobierzDane_clicked()
{
    airly->requestForMeasurements(2318);
    airly->requestForInstallationData(2318);
}

void MainWindow::updateAirlyScreenData(jsonParser::DanePomiarowe *dane)
{
    ui->label_PM1->setText(QString::number(dane->pm1Value));
    ui->label_PM10->setText(QString::number(dane->pm10Value));
    ui->label_PM25->setText(QString::number(dane->pm25Value));
    ui->label_Temperatura->setText(QString::number(dane->temperatureValue, 'f', 0)+ " ℃");
    ui->label_Cisnienie->setText(QString::number(dane->pressureValue, 'f', 0)+ " hPa");
    ui->label_Wilgotnosc->setText(QString::number(dane->humidityValue, 'f', 0)+ " %");

    ui->label_PM10_Percent->setText(QString::number(dane->standardsPm10Percent, 'f', 0)+ " %"); // fixed precision to 0
    ui->label_PM25_Percent->setText(QString::number(dane->standardsPm25Percent, 'f', 0)+ " %"); // fixed precision to 0

    ui->label_Descritpion->setStyleSheet("QLabel {color : blue; }");
    ui->label_Descritpion->setText(dane->indexDescription + dane->indexAdvice);
    ui->label_CAQI->setText(QString::number(dane->indexValue));



}



