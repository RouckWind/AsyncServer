#include <iostream>
#include <QWidget>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    window.resize(500, 500);
    window.show();
    window.setWindowTitle("test");
    return app.exec();
}
