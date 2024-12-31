#include "mainwindow.h"
//#include "mainwindow2.h"
#include "grapwindow.h"  // Include the new GraphWindow class


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
#include "minifying.h"
#include "mutual_followers.h"
#include "SuggestUsers_H.h"


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
#include <QInputDialog>



using namespace std;
QString inputQstring  ;
string inputString ;
string prcessingString ;

map<string, vector<string>> users;
vector<string> parsedXML ;





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)  // Initialize the ui pointer
{


    ui->setupUi(this);  // Setup the UI
    setWallpaper(); // Call the function to set the wallpaper

    // Now you can access the UI elements
    inputQstring = ui->inputArea->toPlainText();  // Get the text from inputArea
    inputString = inputQstring.toStdString();     // Convert it to std::string
}

MainWindow::~MainWindow()
{
    delete ui;  // Clean up the ui pointer
}







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

void highlightLinesDEBUG(QPlainTextEdit *editor, vector<int> &lines) {
    // Ensure the editor and lines vector are valid
    if (!editor || lines.empty()) {
        qDebug() << "Editor or lines are invalid!";
        return;
    }

    QTextDocument *doc = editor->document();
    int totalBlocks = doc->blockCount();
    qDebug() << "Total blocks in document: " << totalBlocks;

    for (int line : lines) {
        int blockNumber = line - 1;  // Convert to 0-based index
        qDebug() << "Highlighting line: " << line;

        // Ensure the line number is valid
        if (blockNumber < 0 || blockNumber >= totalBlocks) {
            qDebug() << "Invalid line number: " << line;
            continue;
        }

        QTextBlock block = doc->findBlockByNumber(blockNumber);
        if (block.isValid()) {
            QTextCursor cursor(block);

            // Set up the text format
            QTextCharFormat format;
            format.setBackground(Qt::red);  // Highlight in red

            // Select the block and apply the format
            cursor.select(QTextCursor::LineUnderCursor);
            cursor.mergeCharFormat(format);
        } else {
            qDebug() << "Invalid block for line: " << line;
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



void MainWindow::setWallpaper() {
    // Set the background image using QPalette
    QPalette palette;
    QPixmap pixmap("icons/ii.jpg"); // Provide the path to your image
    palette.setBrush(QPalette::Window, QBrush(pixmap));  // Use QPalette::Window instead of Background
    setPalette(palette); // Apply the palette to the window
}


void MainWindow::on_pushButton_4_clicked()
{
ui->outputArea->setPlainText(QString::fromStdString(format(prcessingString)));
}


void MainWindow::on_checkValidationButton_clicked()
{

    dehighlightAll(ui->inputArea);
    bool isValid =ValidateXML(inputString);
    if (isValid) {
        QMessageBox::information(this, "Validation", "The code is VALIDAT!");
    } else {
        QMessageBox::warning(this, "Validation", "There are errors in the code.");
    }

    highlightLinesDEBUG(ui->inputArea, errors_locations);
}


void MainWindow::on_minifyButton_clicked()
{
    ui->outputArea->setPlainText(QString::fromStdString(minifyXML(prcessingString)));

}


void MainWindow::on_compressButton_clicked()
{
    string fileName = "compressCodeFile";
    string a3redElCompression = "";
    encodeAndSave(inputString, fileName ,a3redElCompression ) ;
    ui->outputArea->setPlainText(QString::fromStdString(a3redElCompression));
}


void MainWindow::on_convertToJSONButton_clicked()
{
ui->outputArea->setPlainText(QString::fromStdString(convertXMLToJSON(prcessingString)));
}


void MainWindow::on_pushButton_clicked()
{
    browseAndLoadFile(ui->inputArea) ;
}


void MainWindow::on_inputArea_textChanged()
{
    inputQstring = ui->inputArea->toPlainText() ;
    inputString = inputQstring.toStdString();
    prcessingString= inputString ;

    ui->outputArea->clear() ;
}





void MainWindow::on_pushButton_3_clicked()
{
    //fix_missing_close_tag(inputString) ;
    ui->outputArea->setPlainText(QString::fromStdString(fix_missing_close_tag(inputString)));
    ui->outputArea->setPlainText(QString::fromStdString(fix_missing_open_tag(inputString)));

}


void MainWindow::on_outputArea_textChanged()
{

    prcessingString=  ui->outputArea->toPlainText().toStdString() ;
}


void MainWindow::on_decompressButton_clicked()
{


    string a3redElDecompression = "";
    decodeFromFile(inputString, a3redElDecompression  ) ;
    ui->outputArea->setPlainText(QString::fromStdString(a3redElDecompression));

}


void MainWindow::on_searchButton_clicked()
{

    struct TextPosition {
        int linepos;
        int lineIndex;
    };

        ui->inputArea->setPlainText(ui->inputArea->toPlainText());
    string text =   inputString ;      //ui->widget->toPlainText().toStdString();
        string targetText = ui->searchKeyword->toPlainText().toStdString(); //searchKeyword
        vector<string>lines;
        stringstream ss(text);
        string line;
        vector<TextPosition> lineIndex;

        if (text.compare("") != 0)
        {
            while(std::getline(ss,line,'\n')){
                lines.push_back(line);
            }
        }
        else
            return;

        if(targetText.compare("") == 0)
        {
            QMessageBox::warning(this, "title", "Enter text to search for");
            return;
        }

        for(int i = 0;i < (int) lines.size(); i++)
        {
            size_t found = lines[i].find(targetText);
            if(found != string::npos)
            {
                lineIndex.push_back({(int)found, i});
            }
        }

        QTextCharFormat  fmt;
        fmt.setProperty(QTextFormat::FullWidthSelection, true);
        fmt.setBackground(Qt::green);
        ui->inputArea->setLineWrapMode(QPlainTextEdit::NoWrap);

        for(int i = 0; i < (int) lineIndex.size();i++)
        {

            QTextCursor cursor = ui->inputArea->textCursor();
            cursor.movePosition(QTextCursor::Start);
            cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, lineIndex[i].lineIndex);
            cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, lineIndex[i].linepos);
            cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, (int)targetText.size());
            cursor.select(QTextCursor::LineUnderCursor);
            cursor.setCharFormat(fmt);

            //ui->widget->setTextCursor(cursor);

        }


}


void MainWindow::on_sartVisualizationButton_clicked()
{


    // Pass the data to the GraphWindow
    std::map<std::string, std::vector<std::string>> users;
    parsedXML = parseXML(inputString);
    NetworkAnalysis(users, parsedXML);
    // Populate 'users' with your actual data
    GrapWindow* graphWindow = new GrapWindow(users, this);
    graphWindow->exec();  // Show the graph in a modal window


    /*
    std::vector<std::string> tokens = parseXML(xmlData);
    std::map<std::string, std::vector<std::string>> users;
    NetworkAnalysis(users, tokens);
*/
   /* MainWindow2 mainWindow2;
    mainWindow2.drawGraph(users);
    mainWindow2.show();
    */
    /*
    MainWindow2* mainWindow2 = new MainWindow2;  // Pass users to the constructor
    mainWindow2->show();  // Now show the window after it's ready
    */

}


void MainWindow::on_mostActiveUserButton_clicked()
{
    parsedXML = parseXML(inputString);
    NetworkAnalysis(users, parsedXML);
    vector<string> result = mostActiveUser(users);

    QString message = "The most active user(s) is/are:\n";
    for (const auto& user : result) {
        message += "user " + QString::fromStdString(user) + "\n"; // Add each user and a newline
    }

    // Display the message in a message box
    QMessageBox::information(this, "Most Active Users", message);


}


void MainWindow::on_mostActiveUserButton_2_clicked()
{
    parsedXML = parseXML(inputString);
    NetworkAnalysis(users, parsedXML);
    vector<string> result = mostFollowers(users);

    QString message = "the most user(s) that got followers is/are:\n";
    for (const auto& user : result) {
        message += "user " + QString::fromStdString(user) + "\n"; // Add each user and a newline
    }

    // Display the message in a message box
    QMessageBox::information(this, "Most Active Users", message);
}


void MainWindow::on_SaveButton_clicked()
{
    // Open a file dialog to choose where to save the file
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt);;All Files (*)");

    // If the user cancels the dialog, do nothing
    if (fileName.isEmpty()) {
        return;
    }

    // Open the file for writing
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot save file: " + file.errorString());
        return;
    }

    // Retrieve text from QPlainTextEdit (assuming it's named `outputArea`)
    QString content = ui->outputArea->toPlainText();

    // Write the text to the file
    QTextStream out(&file);
    out << content;

    // Close the file
    file.close();

    // Optional: Show a confirmation message
    QMessageBox::information(this, "Success", "File saved successfully!");
}


void MainWindow::on_pushButton_9_clicked()
{
    dehighlightAll(ui->inputArea);

}


void MainWindow::on_mutualFriendsButton_clicked()
{
    map<string, vector<string>> users;
    vector<string> parsedXML = parseXML(inputString);
    NetworkAnalysis(users, parsedXML);
    string firstUser = "2";
    string secondUser = "3";
    vector<string> userIds = {"1", "2", "3"};
    QString message = "users has user(s) \n" + QString::fromStdString(mutualFollowersBetween_n_Users(users, userIds)) + "\n as a mutual friend(s)";
    // Display the message in a message box
    QMessageBox::information(this, "mutual Friends", message);
}


void MainWindow::on_mutualFriendsButton_2_clicked()
{
    string userId ;
    bool ok;
    int userNumber = QInputDialog::getInt(this, tr("User Input"),
                                          tr("Enter the user ID to Suggest Friends:"), 0, 0, 100, 1, &ok);


    userId = to_string(userNumber);

    map<string, vector<string>> users;
    vector<string> parsedXML = parseXML(inputString);
    NetworkAnalysis(users, parsedXML);

    vector<string> suggested = suggestUsersToFollow(users, userId);
    QString message = "Suggested users for user " + QString::fromStdString(userId) + " is/are :\n" ;
    for (const auto& user : suggested) {
        message += "user " + QString::fromStdString(user) + "\n"; // Add each user and a newline
    }

    // Display the message in a message box
    QMessageBox::information(this, "Suggested Users", message);

}

