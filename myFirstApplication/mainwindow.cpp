#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->outputArea->setPlainText(" pretifiy output here");

}


void MainWindow::on_checkValidationButton_clicked()
{
    ui->outputArea->setPlainText(" check validation output here");
}


void MainWindow::on_minifyButton_clicked()
{
    ui->outputArea->setPlainText(" minify  output ");

}


void MainWindow::on_compressButton_clicked()
{
    ui->outputArea->setPlainText(" compress  output ");

}


void MainWindow::on_convertToJSONButton_clicked()
{

}

