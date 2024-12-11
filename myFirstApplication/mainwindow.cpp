#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog> // for browse button
#include <QString>
#include <QFile> // to open file in the Qplain texet
#include <QTextStream>
#include <QPlainTextEdit>
#include <QMessageBox>


//function to open the explorer when BROWSE button is clicked
void browseAndLoadFile(QPlainTextEdit* plainTextEdit) {
    QString filter = "XML Files (*.xml);;Text Files (*.txt)"; // only can see XML and text files
    QString fileName = QFileDialog::getOpenFileName(
        nullptr,
        "Open File",
        QDir::homePath(),
        filter
        );

    if (fileName.isEmpty()) {
        return; // User cancelled
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "Could not open the file.");
        return;
    }

    QTextStream in(&file);
    plainTextEdit->setPlainText(in.readAll());
    file.close();
}


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


void MainWindow::on_pushButton_clicked()
{
    browseAndLoadFile(ui->inputArea) ;
}

