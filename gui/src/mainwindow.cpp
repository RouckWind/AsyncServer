#include "../inc/mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent){
    QGridLayout *layout1 = new QGridLayout(this);
    QListView *listView = new QListView(this);
    QPushButton *pushButton = new QPushButton("Выход", this);

    layout1->addWidget(listView, 0, 0, Qt::AlignCenter);
    layout1->addWidget(pushButton,1,0, Qt::AlignCenter);

    this->setLayout(layout1);


    int widght = 450;
    int height = 350;

    this->resize(widght,height);
    this->setWindowTitle("MainWindow");

    pushButton->resize(80, 40);

    listView->resize(widght, 300);

    layout1->setRowMinimumHeight(0, 300);


    this->show();
}

MainWindow::~MainWindow() {
}
