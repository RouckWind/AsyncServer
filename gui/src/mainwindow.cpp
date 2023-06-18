#include "../inc/mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    setWindowTitle("MainWindow");
    layout1 = new QVBoxLayout(this);
    setLayout(layout1);

    listWidget = new QListWidget(this);
    pushButton = new QPushButton("Выход", this);

    int widght = 450;
    int height = 350;

    setFixedSize(widght, height);
    listWidget->setFixedSize(widght, 300);

    layout1->insertWidget(0, listWidget, Qt::AlignCenter);

    layout1->insertWidget(1, pushButton, Qt::AlignBottom);

    pushButton->setGeometry(175, 305, 80, 40);


    connect(pushButton, &QPushButton::clicked, this, &MainWindow::onpushButton_clicked);
}

void MainWindow::onpushButton_clicked() {
    //close();
    clientsCount();
}

void MainWindow::clientsCount() {
    auto clients = server.getClients();
    listWidget->insertItem(0, QString("Клиентов подключено: " + QString::number(clients)));
}

void MainWindow::clientJoined() {
}

void MainWindow::clientLeft() {
}

void MainWindow::sendData() {
}

void MainWindow::receiveData() {
}

void MainWindow::clientConnected() {
}

MainWindow::~MainWindow() {
}
