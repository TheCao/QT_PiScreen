#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "airlyparser.h"
#include "jsonparser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_pobierzDane_clicked();
    void updateAirlyScreenData(jsonParser::DanePomiarowe *dane);


private:
    Ui::MainWindow *ui;
    airlyParser *airly;
};

#endif // MAINWINDOW_H
