#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "XML_Validor.h"
#include <QFileDialog> // for browse button
#include <QString>
#include <string>
#include <QFile> // to open file in the Qplain texet
#include <QTextStream>
#include <QPlainTextEdit>
#include <QMessageBox> // for massge box // msh m7taga 7aga y3ny (bsot 3adel emam)
#include <QTextCursor> //for highlight errors lines
#include <QTextCharFormat>
#include <QVector>
#include <QTextDocument>
#include <QTextBlock>
#include <QPixmap>   // For setting custom icon



using namespace std;
QString inputQstring  ;
string inputString ;


void browseAndLoadFile(QPlainTextEdit* plainTextEdit) {
    /*
     -function usage:  to open the explorer when BROWSE button is clicked
     -paramenters : only pass to it the textfield(GUI area) it will display file in
    */

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

void display_errorMessage(){
    // QMessageBox::information(editor, "successfully  ","Valid XML file, zero errors found.", QMessageBox::Ok, QMessageBox::Information);
    /*
          QMessageBox msgBox(editor);
         msgBox.setWindowTitle("No Errors");
         msgBox.setText("No errors found.");
         msgBox.setIconPixmap(QPixmap(":/icons/green_checkmark.png"));
         msgBox.exec();
        */
}


void highlightLines(QPlainTextEdit *editor, vector<int> &lines) {
    /*
     -function usage: to higlight the lines that was found having errors in red
     -paramenters : 1.where it will highline (where are the lines)
                    2. vector having all the lines that have errors
    */

    // Ensure the editor and lines vector are valid
    if (!editor || lines.empty())

        return;

    QTextDocument *doc = editor->document();


    for (int line : lines) { // Convert from 1-based index (passed vector) to 0-based index
        int blockNumber = line - 1;

        // Ensure the line number is valid (0-based check)
        if (blockNumber < 0 || blockNumber >= doc->blockCount())
            continue;

        QTextBlock block = doc->findBlockByNumber(blockNumber);
        if (block.isValid()) {
            QTextCursor cursor(block);

            // Set up the text format
            QTextCharFormat format;
            format.setBackground(Qt::red);  // Highlight in red

            // Select the block and apply the format
            cursor.select(QTextCursor::LineUnderCursor);
            cursor.mergeCharFormat(format);
        }
    }

}

void dehighlightAll(QPlainTextEdit *editor) {
    /*
     -function usage: dehiglight all the lines
     -paramenters : where it will highline (where are the lines)

    */
    if (!editor)
        return;

    QTextDocument *doc = editor->document();
    QTextCursor cursor(doc);

    // set up the text format to remove any background color
    QTextCharFormat format;
    format.setBackground(Qt::transparent);  // remove background color

    cursor.select(QTextCursor::Document);
    cursor.mergeCharFormat(format);
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     inputQstring = ui->inputArea->toPlainText() ;
     inputString = inputQstring.toStdString();
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
    bool value = ValidateXML(inputString) ;
    QString text1 = value ? "true" : "false";

    ui->outputArea->setPlainText( text1  );

    dehighlightAll(ui->inputArea);
    highlightLines(ui->inputArea, errors_locations);
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


void MainWindow::on_inputArea_textChanged()
{
    inputQstring = ui->inputArea->toPlainText() ;
    inputString = inputQstring.toStdString();
}

