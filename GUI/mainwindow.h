#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./ui_mainwindow.h"
#include "XML_Validor.h"
#include "XML_Fix.h"
#include "format.h"
#include "xmltojson.h"
#include "decompression.h"
#include "compression.h"
#include "Graph.h"
#include "mostActiveUser.h"
#include "Most_followers.h"


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
#include <QMainWindow>
#include <QPalette>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_checkValidationButton_clicked();

    void on_minifyButton_clicked();

    void on_compressButton_clicked();

    void on_convertToJSONButton_clicked();

    void on_pushButton_clicked();

    void on_inputArea_textChanged();

    void on_pushButton_3_clicked();

    void on_outputArea_textChanged();

    void on_decompressButton_clicked();

    void on_searchButton_clicked();

    void on_sartVisualizationButton_clicked();

    void on_mostActiveUserButton_clicked();

    void on_mostActiveUserButton_2_clicked();

    void on_SaveButton_clicked();

    void on_pushButton_9_clicked();

    void on_searchButton_2_clicked();

    void on_mutualFriendsButton_clicked();

    void on_mutualFriendsButton_2_clicked();

private:
    Ui::MainWindow *ui;

    void setWallpaper(); // Function declaration for setting wallpape
};

#endif // MAINWINDOW_H


