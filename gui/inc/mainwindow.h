//
// Created by rouckwind on 04.06.23.
//

#ifndef ASYNCSERVER_MAINWINDOW_H
#define ASYNCSERVER_MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QListView>
#include <QPushButton>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onpushButton_clicked();

public:
    ~MainWindow() override;
};


#endif //ASYNCSERVER_MAINWINDOW_H
