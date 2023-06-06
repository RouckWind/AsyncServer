#include "../inc/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent){
    QVBoxLayout *layout1 = new QVBoxLayout(this);
    QListView *listView = new QListView(this);
    QPushButton *pushButton = new QPushButton("Выход", this);

    int widght = 450;
    int height = 350;

    this->resize(widght,height);
    this->setWindowTitle("MainWindow");


    layout1->addWidget(listView, 0, Qt::AlignCenter);
    layout1->addWidget(pushButton,1, Qt::AlignCenter);


    pushButton->setGeometry(175, 305, 80, 40);

    listView->resize(widght, 300);

    this->show();

    connect(pushButton, &QPushButton::clicked, this, &MainWindow::onpushButton_clicked);
}

MainWindow::~MainWindow() { }

void MainWindow::onpushButton_clicked() {
    this->close();
}