#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <cmath>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class ParabolaWidget : public QWidget {
public:
    int a, b, c, d, scale;
    double step, x_start, x_end;

    void drawParabola() {
        update();
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int prevX, prevY;
        bool firstPoint = true;

        painter.translate(width() / 2, height() / 2);

        painter.setPen(Qt::black);
        painter.drawLine(-width() / 2, 0, width() / 2, 0);

        painter.drawLine(0, -height() / 2, 0, height() / 2);

        painter.setPen(Qt::blue);
        for (double x = x_start; x < x_end; x += step) {
            if (x == 0)
                continue;
            double y = (d - a*x*x*x - b*x*x - c*x) / x;
            double scaledX = x * scale;
            double scaledY = -(y * scale);

            if (std::abs(x) >= 0.001) {
                if (!firstPoint) {
                    painter.drawLine(prevX, prevY, scaledX, scaledY);
                } else {
                    firstPoint = false;
                }
            }

            prevX = scaledX;
            prevY = scaledY;
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Лабораторная №5");

    QLineEdit aInput;
    QLineEdit bInput;
    QLineEdit cInput;
    QLineEdit dInput;
    QLineEdit scaleInput;
    QLineEdit stepInput;
    QLineEdit xstartInput;
    QLineEdit xendInput;

    QLabel aLabel("a");
    QLabel bLabel("b");
    QLabel cLabel("c");
    QLabel dLabel("d");
    QLabel scaleLabel("Scale");
    QLabel stepLabel("Step");
    QLabel xstartLabel("X start");
    QLabel xendLabel("X end");

    QPushButton applyButton("Apply");

    QWidget settings;

    QVBoxLayout layout(&settings);
    layout.addWidget(&aLabel);
    layout.addWidget(&aInput);
    layout.addWidget(&bLabel);
    layout.addWidget(&bInput);
    layout.addWidget(&cLabel);
    layout.addWidget(&cInput);
    layout.addWidget(&dLabel);
    layout.addWidget(&dInput);
    layout.addWidget(&scaleLabel);
    layout.addWidget(&scaleInput);
    layout.addWidget(&stepLabel);
    layout.addWidget(&stepInput);
    layout.addWidget(&xstartLabel);
    layout.addWidget(&xstartInput);
    layout.addWidget(&xendLabel);
    layout.addWidget(&xendInput);
    layout.addWidget(&applyButton);
    settings.setLayout(&layout);

    ParabolaWidget widget;
    widget.resize(800, 600);

    QObject::connect(&applyButton, &QPushButton::clicked, [&]() {
        widget.a = aInput.text().toInt();
        widget.b = bInput.text().toInt();
        widget.c = cInput.text().toInt();
        widget.d = dInput.text().toInt();
        widget.scale = scaleInput.text().toInt();
        widget.step = stepInput.text().toDouble();
        widget.x_start = xstartInput.text().toDouble();
        widget.x_end = xendInput.text().toDouble();
        widget.show();
        widget.update();
    });

    settings.show();

    return app.exec();
}
