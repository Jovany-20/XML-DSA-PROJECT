#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Set the main window title
    w.setWindowTitle("XML Geeks");

    /*// Set the main window icon using the relative path to the 'icons' folder
    QString iconPath = QDir::current().filePath("icons/app.png");


    w.setWindowIcon(QIcon("D:/college/3. senior 1/2. Data strc & Alg/project/gui/my working area/myFirstApplicationicons/app.ico"));
*/
    QIcon appIcon("D:/college/3. senior 1/2. Data strc & Alg/project/gui/my working area/myFirstApplication/icons/app.ico");
    if (appIcon.isNull()) {
        qDebug() << "Icon load failed!";
    } else {
        w.setWindowIcon(appIcon);
    }
    w.show();

    return a.exec();
}
