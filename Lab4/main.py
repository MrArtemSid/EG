import sys
from PyQt6 import QtGui, QtWidgets
image_b = None

def get_image_size():
    header = image_b.read(54)
    width = header[18] + header[19] * 256
    height = header[22] + header[23] * 256
    return width, height


def draw_image(canvas, width, height):
    painter = QtGui.QPainter(canvas)
    for i in range(height - 1, -1, -1):
        for j in range(width):
            b, g, r = image_b.read(3)
            painter.setPen(QtGui.QColor(r, g, b))
            painter.drawPoint(j, i)
    painter.end()


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.label = QtWidgets.QLabel()
        self.setCentralWidget(self.label)

        self.setWindowTitle('Лабораторная работа #4')
        self.setGeometry(100, 100, 400, 200)

        self.button = QtWidgets.QPushButton('Открыть', self)
        self.button.setGeometry(0, 0, 100, 50)
        self.button.move(self.frameGeometry().width() // 2 - self.button.frameGeometry().width() // 2,
                    self.frameGeometry().height() // 2 - self.button.frameGeometry().height() // 2)
        self.button.clicked.connect(self.mousePressEvent)

    def mousePressEvent(self, event):
        try:
            global image_b
            image_b = open(QtWidgets.QFileDialog.getOpenFileName()[0], "rb")
            width, height = get_image_size()
            canvas = QtGui.QPixmap(width, height)
            draw_image(canvas, width, height)
            self.label.setPixmap(canvas)
            self.setFixedWidth(width)
            self.setFixedHeight(height)
            self.button.hide()
        except:
            print("Ошибка при открытии файла\n")

def main():
    app = QtWidgets.QApplication(sys.argv)

    window = MainWindow()
    window.show()

    app.exec()
main()
