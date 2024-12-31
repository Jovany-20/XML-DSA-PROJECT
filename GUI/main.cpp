#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Set the main window title
    w.setWindowTitle("XML Geeks");


    QDir::setCurrent(QCoreApplication::applicationDirPath());

    // Use the relative path to load the icon
    QIcon appIcon("icons/app.ico");


    // Set the icon for the application (taskbar, etc.)
    a.setWindowIcon(appIcon);

    // Create a main window (if applicable)
    QMainWindow window;
    window.setWindowIcon(appIcon);  // Set the icon for the window

    w.show();

    return a.exec();
}
