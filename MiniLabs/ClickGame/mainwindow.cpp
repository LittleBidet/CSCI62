#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->myButton, &QPushButton::clicked, this, &MainWindow::MyButtonClick);
    ui->winLabel->hide();
    std::ifstream inputFile("instructions.txt");
    std::string instructions;
    std::getline(inputFile, instructions);
    ui->instructionLabel->setText(QString::fromStdString(instructions));

}
void MainWindow::MyButtonClick(){
    c.add();
    std::string text = "Number of Clicks: " + std::to_string(c.getCount());
    ui->numberOfClicks->setText(QString::fromStdString(text));
    if(c.getCount() >= 10){
        ui->numberOfClicks->hide();
        ui->myButton->hide();
        ui->winLabel->show();
        return;
    }

}
MainWindow::~MainWindow()
{
    delete ui;
}
