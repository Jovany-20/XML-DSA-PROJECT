/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *checkValidationButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *convertToJSONButton;
    QPushButton *minifyButton;
    QPushButton *compressButton;
    QPushButton *decompressButton;
    QPushButton *pushButton_9;
    QLabel *label;
    QPlainTextEdit *outputArea;
    QMenuBar *menubar;
    QMenu *menuxml;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(649, 582);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(180, 40, 83, 29));
        checkValidationButton = new QPushButton(centralwidget);
        checkValidationButton->setObjectName("checkValidationButton");
        checkValidationButton->setGeometry(QRect(20, 110, 121, 29));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(150, 110, 83, 29));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(20, 180, 101, 29));
        convertToJSONButton = new QPushButton(centralwidget);
        convertToJSONButton->setObjectName("convertToJSONButton");
        convertToJSONButton->setGeometry(QRect(10, 320, 121, 29));
        minifyButton = new QPushButton(centralwidget);
        minifyButton->setObjectName("minifyButton");
        minifyButton->setGeometry(QRect(20, 250, 91, 29));
        compressButton = new QPushButton(centralwidget);
        compressButton->setObjectName("compressButton");
        compressButton->setGeometry(QRect(10, 390, 91, 29));
        decompressButton = new QPushButton(centralwidget);
        decompressButton->setObjectName("decompressButton");
        decompressButton->setGeometry(QRect(110, 390, 91, 29));
        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(240, 110, 83, 29));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 40, 181, 20));
        outputArea = new QPlainTextEdit(centralwidget);
        outputArea->setObjectName("outputArea");
        outputArea->setGeometry(QRect(340, 10, 291, 531));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 649, 25));
        menuxml = new QMenu(menubar);
        menuxml->setObjectName("menuxml");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuxml->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        checkValidationButton->setText(QCoreApplication::translate("MainWindow", "Check Validation", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Solve Error", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Prettify XML", nullptr));
        convertToJSONButton->setText(QCoreApplication::translate("MainWindow", "Convert to JSON", nullptr));
        minifyButton->setText(QCoreApplication::translate("MainWindow", "Minify XML", nullptr));
        compressButton->setText(QCoreApplication::translate("MainWindow", "Compress", nullptr));
        decompressButton->setText(QCoreApplication::translate("MainWindow", "Decompress", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "type your XML file or ", nullptr));
        menuxml->setTitle(QCoreApplication::translate("MainWindow", "xml", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
