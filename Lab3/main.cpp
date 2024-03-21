#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>
#include <QInputDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QGraphicsScene scene;
    scene.setBackgroundBrush(Qt::white);
    QGraphicsView view(&scene);
    a.setApplicationName("Лабораторная №3");

    view.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view.setFixedSize(800, 600);
    view.show();

    scene.addLine(-400, 0, 400, 0, QPen(Qt::black));
    scene.addLine(0, -300, 0, 300, QPen(Qt::black));

    QPolygonF trapazoid;
    trapazoid << QPointF(-30, -50) << QPointF(30, -50) << QPointF(50, 50) << QPointF(-50, 50);
    QGraphicsPolygonItem trapazoidItem(trapazoid);
    scene.addItem(&trapazoidItem);

    QLineEdit xInput;
    xInput.setPlaceholderText("Введите x");

    QLineEdit yInput;
    yInput.setPlaceholderText("Введите y");

    QLineEdit scaleInput;
    scaleInput.setPlaceholderText("Введите коэффициент масштабирования");

    QLineEdit angleInput;
    angleInput.setPlaceholderText("Введите угол поворота");

    QPushButton applyButton("Apply");

    QWidget widget;

    QVBoxLayout layout(&widget);
    layout.addWidget(&xInput);
    layout.addWidget(&yInput);
    layout.addWidget(&scaleInput);
    layout.addWidget(&angleInput);
    layout.addWidget(&applyButton);
    widget.setLayout(&layout);
    widget.show();

    QObject::connect(&applyButton, &QPushButton::clicked, [&]() {
        qint64 x = xInput.text().toLong();
        qint64 y = yInput.text().toLong();
        qreal scale = scaleInput.text().toDouble();
        qreal angle = angleInput.text().toDouble();

        trapazoidItem.setScale(scale);
        trapazoidItem.setRotation(angle);
        trapazoidItem.setX(x);
        trapazoidItem.setY(-y);
    });

    return a.exec();
}
