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
#include <QtWidgets/QHBoxLayout>
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
    QPushButton *pushButton_3;
    QPushButton *pushButton_9;
    QLabel *label;
    QPlainTextEdit *outputArea;
    QPlainTextEdit *inputArea;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *minifyButton;
    QPushButton *pushButton_4;
    QPushButton *checkValidationButton;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *decompressButton;
    QPushButton *compressButton;
    QPushButton *convertToJSONButton;
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
        pushButton->setGeometry(QRect(170, 10, 83, 29));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(530, 440, 83, 29));
        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(530, 490, 83, 29));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 151, 20));
        outputArea = new QPlainTextEdit(centralwidget);
        outputArea->setObjectName("outputArea");
        outputArea->setGeometry(QRect(340, 60, 291, 311));
        inputArea = new QPlainTextEdit(centralwidget);
        inputArea->setObjectName("inputArea");
        inputArea->setGeometry(QRect(10, 60, 311, 311));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 40, 181, 20));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(450, 40, 181, 20));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 430, 307, 31));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        minifyButton = new QPushButton(widget);
        minifyButton->setObjectName("minifyButton");

        horizontalLayout->addWidget(minifyButton);

        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName("pushButton_4");

        horizontalLayout->addWidget(pushButton_4);

        checkValidationButton = new QPushButton(widget);
        checkValidationButton->setObjectName("checkValidationButton");

        horizontalLayout->addWidget(checkValidationButton);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(20, 490, 304, 31));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        decompressButton = new QPushButton(widget1);
        decompressButton->setObjectName("decompressButton");

        horizontalLayout_2->addWidget(decompressButton);

        compressButton = new QPushButton(widget1);
        compressButton->setObjectName("compressButton");

        horizontalLayout_2->addWidget(compressButton);

        convertToJSONButton = new QPushButton(widget1);
        convertToJSONButton->setObjectName("convertToJSONButton");

        horizontalLayout_2->addWidget(convertToJSONButton);

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
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Solve Error", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Type your XML file or ", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Input", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Output", nullptr));
        minifyButton->setText(QCoreApplication::translate("MainWindow", "Minify XML", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Prettify XML", nullptr));
        checkValidationButton->setText(QCoreApplication::translate("MainWindow", "Check Validation", nullptr));
        decompressButton->setText(QCoreApplication::translate("MainWindow", "Decompress", nullptr));
        compressButton->setText(QCoreApplication::translate("MainWindow", "Compress", nullptr));
        convertToJSONButton->setText(QCoreApplication::translate("MainWindow", "Convert to JSON", nullptr));
        menuxml->setTitle(QCoreApplication::translate("MainWindow", "xml", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
