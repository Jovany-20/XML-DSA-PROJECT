#include "grapwindow.h"
#include "ui_grapwindow.h"

/*
GrapWindow::GrapWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GrapWindow)
{
    ui->setupUi(this);
}
*/
GrapWindow::~GrapWindow()
{
    delete ui;
}

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QFont>
#include <cmath>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <cmath>


GrapWindow::GrapWindow(const std::map<std::string, std::vector<std::string>>& users, QWidget *parent)
    : QDialog(parent), view(new QGraphicsView(this)), scene(new QGraphicsScene(this)) {
    setWindowTitle("Network Analysis Graph");
    setGeometry(100, 100, 800, 600);

    view->setScene(scene);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(view);
    setLayout(layout);

    drawGraph(users);
}

void GrapWindow::drawGraph(const std::map<std::string, std::vector<std::string>>& users) {
    std::map<std::string, QGraphicsEllipseItem*> nodeItems;
    const int nodeRadius = 60;
    const int centerX = 400; // Center of the scene
    const int centerY = 300;
    const int circleRadius = 200; // Radius of the circle where nodes will be placed

    int n = users.size();
    int index = 0;

    // Arrange nodes in a circle
    for (const auto& pair : users) {
        double angle = (2 * M_PI * index) / n; // Angle for each node
        int x = centerX + circleRadius * std::cos(angle) - nodeRadius / 2;
        int y = centerY + circleRadius * std::sin(angle) - nodeRadius / 2;

        // Create the node (circle)
        QGraphicsEllipseItem* node = scene->addEllipse(x, y, nodeRadius, nodeRadius, QPen(Qt::black), QBrush(Qt::green));

        // Add the label centered inside the node
        QGraphicsTextItem* label = scene->addText(QString::fromStdString(pair.first));
        label->setDefaultTextColor(Qt::black);


        // Set the font if needed
        QFont font("Arial", 15); // Adjust font and size as needed
        label->setFont(font);

        // Get the bounding rectangle of the text
        QRectF textRect = label->boundingRect();

        // Calculate the position to center the text in the node
        qreal labelX = x + (nodeRadius - textRect.width()) / 2 - textRect.left();
        qreal labelY = y + (nodeRadius - textRect.height()) / 2 - textRect.top();

        // Set the label position
        label->setPos(labelX, labelY);

        nodeItems[pair.first] = node;
        ++index;
    }

    // Create directed edges with arrows
    for (const auto& pair : users) {
        const std::string& userId = pair.first;
        const std::vector<std::string>& followers = pair.second;

        QGraphicsEllipseItem* startNode = nodeItems[userId];
        QPointF startPos = startNode->rect().center() + startNode->scenePos();

        for (const std::string& followerId : followers) {
            if (nodeItems.find(followerId) != nodeItems.end()) {
                QGraphicsEllipseItem* endNode = nodeItems[followerId];
                QPointF endPos = endNode->rect().center() + endNode->scenePos();

                // Calculate vector from start to end
                QLineF line(startPos, endPos);

                // Adjust start and end points so lines start and end at the edge of the nodes
                qreal angle = std::atan2(-line.dy(), line.dx());

                qreal startX = startPos.x() + nodeRadius / 2 * std::cos(angle);
                qreal startY = startPos.y() - nodeRadius / 2 * std::sin(angle);

                qreal endX = endPos.x() - nodeRadius / 2 * std::cos(angle);
                qreal endY = endPos.y() + nodeRadius / 2 * std::sin(angle);

                QPointF adjustedStart(startX, startY);
                QPointF adjustedEnd(endX, endY);

                // Draw the line for the edge
                QGraphicsLineItem* edgeLine = scene->addLine(QLineF(adjustedStart, adjustedEnd), QPen(Qt::blue));

                // Draw the arrowhead
                const double arrowSize = 10;
                QLineF arrowLine(adjustedEnd, adjustedStart);
                double arrowAngle = std::atan2(-arrowLine.dy(), arrowLine.dx());

                QPointF arrowP1 = adjustedEnd + QPointF(std::cos(arrowAngle + M_PI / 6) * arrowSize,
                                                        -std::sin(arrowAngle + M_PI / 6) * arrowSize);
                QPointF arrowP2 = adjustedEnd + QPointF(std::cos(arrowAngle - M_PI / 6) * arrowSize,
                                                        -std::sin(arrowAngle - M_PI / 6) * arrowSize);

                QPolygonF arrowHead;
                arrowHead << adjustedEnd << arrowP1 << arrowP2;
                scene->addPolygon(arrowHead, QPen(Qt::blue), QBrush(Qt::blue));
            }
        }
    }
}


