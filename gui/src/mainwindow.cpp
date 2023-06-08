#include "../inc/mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    auto* layout1 = new QVBoxLayout(this);
    setLayout(layout1);

    auto* listWidget = new QListWidget(this);
    auto* pushButton = new QPushButton("Выход", this);

    int widght = 450;
    int height = 350;

    setFixedSize(widght, height);
    listWidget->setFixedSize(widght, 300);
    setWindowTitle("MainWindow");

    layout1->insertWidget(0, listWidget, Qt::AlignCenter);

    layout1->insertWidget(1, pushButton, Qt::AlignBottom);

    pushButton->setGeometry(175, 305, 80, 40);

    connect(pushButton, &QPushButton::clicked, this, &MainWindow::onpushButton_clicked);
}

MainWindow::~MainWindow() {
}

void MainWindow::onpushButton_clicked() {
    close();
}