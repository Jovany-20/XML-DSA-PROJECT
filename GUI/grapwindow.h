#ifndef GRAPWINDOW_H
#define GRAPWINDOW_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <map>
#include <vector>
#include <string>


namespace Ui {
class GrapWindow;
}

class GrapWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GrapWindow(const std::map<std::string, std::vector<std::string>>& users, QWidget *parent = nullptr);

    ~GrapWindow(); //not sure

private:
    Ui::GrapWindow *ui; //not sure
    QGraphicsView* view;
    QGraphicsScene* scene;
    void drawGraph(const std::map<std::string, std::vector<std::string>>& users);
};

#endif // GRAPWINDOW_H
