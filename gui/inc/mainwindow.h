//
// Created by rouckwind on 04.06.23.
//

#ifndef ASYNCSERVER_MAINWINDOW_H
#define ASYNCSERVER_MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QListView>
#include <QPushButton>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;
};


#endif //ASYNCSERVER_MAINWINDOW_H
