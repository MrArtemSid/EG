#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QBrush>
#include <QColor>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QVector>
#include <QKeyEvent>

class KeyEventHandler : public QObject {
public:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Space) {
                if (timer->interval() == 50) {
                    timer->setInterval(100);
                }
                else if (timer->interval() == 100) {
                    timer->setInterval(10);
                }
                else {
                    timer->setInterval(50);
                }
                return true;
            }
            if (keyEvent->key() == Qt::Key_S) {
                if (timer->isActive()) {
                    timer->stop();
                } else {
                    timer->start();
                }
                return true;
            }
        }
        return QObject::eventFilter(obj, event);
    }

    QTimer* timer;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QTimer timer;
    KeyEventHandler keyEventHandler;
    keyEventHandler.timer = &timer;
    app.installEventFilter(&keyEventHandler);
    timer.setInterval(50);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 800, 600);
    QGraphicsView view(&scene);

    QGraphicsEllipseItem sun(0, 300, 50, 50);
    sun.setBrush(QBrush(Qt::yellow));
    scene.addItem(&sun);

    QVector<QGraphicsEllipseItem*>waves;
    QVector<QGraphicsPolygonItem*>clouds;

    QPolygonF cloudShape;

    cloudShape << QPointF(50, 50)
               << QPointF(70, 40)
               << QPointF(80, 30)
               << QPointF(90, 40)
               << QPointF(100, 45)
               << QPointF(110, 50)
               << QPointF(105, 60)
               << QPointF(100, 70)
               << QPointF(85, 80)
               << QPointF(75, 80)
               << QPointF(65, 77)
               << QPointF(55, 70)
               << QPointF(50, 60);

    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 15; ++j) {
            QGraphicsEllipseItem* ellipse = scene.addEllipse(50 * j + 2 * i, 400 + 10 * i, 80, 80, QPen(Qt::black), QBrush(Qt::darkBlue));
            waves.push_back(ellipse);


            QGraphicsPolygonItem *cloudItem = new QGraphicsPolygonItem(cloudShape);
            cloudItem->setBrush(Qt::white);
            cloudItem->setPen(Qt::NoPen);

            cloudItem->setPos(-40 + 50 * j, 10);

            clouds.push_back(cloudItem);
            scene.addItem(cloudItem);
        }
    }

    // Лодка
    QPolygonF boatShape;
    boatShape << QPointF(100, 450)
              << QPointF(200, 450)
              << QPointF(220, 420)
              << QPointF(80, 420);
    QGraphicsPolygonItem boat(boatShape);
    boat.setBrush(QBrush(Qt::green));
    scene.addItem(&boat);
    // Парус
    QPolygonF sailShape;
    sailShape << QPointF(150, 425)
              << QPointF(150, 325)
              << QPointF(180, 355);
    QGraphicsPolygonItem sail(sailShape);
    sail.setBrush(QBrush(Qt::white));
    sail.setPen(QPen(Qt::black));
    scene.addItem(&sail);

    int step = 0;
    int direction_x = 1;
    int direction_y = 1;
    bool isNight = false;

    QObject::connect(&timer, &QTimer::timeout, [&](){
        int x = step % 800;
        int y = -(x-350)*(x-350)/800 + 300; // Параболический путь солнца/луны


        for (int i = 0; i < waves.size(); ++i) {
            int delta = 0;
            if (i % 2 == isNight)
                delta = -1;
            else
                delta = 1;
            waves[i]->setPos(waves[i]->pos().x() + 2 * delta, waves[i]->pos().y());
            clouds[i]->setPos((int)(clouds[i]->pos().x() + 1), clouds[i]->pos().y());
        }

        if (!isNight) {
            sun.setBrush(QBrush(Qt::yellow));
        } else {
            sun.setBrush(QBrush(Qt::white));
        }
        sun.setPos(x, -y);

        if (boat.pos().x() > 600 || boat.pos().x() < 0)
            direction_x *= -1;
        boat.setPos(boat.pos().x() + 3 * direction_x, boat.pos().y());
        sail.setPos(sail.pos().x() + 3 * direction_x, sail.pos().y());

        int green = qBound((255 - step % 1601 / 5) % 256, 0, 255);
        scene.setBackgroundBrush(QBrush(QColor(0, green, 255)));

        step += 5;

        isNight = (step % 1601) > 800;
    });

    timer.start();

    view.show();

    return app.exec();
}
