//
// Created by rouckwind on 04.06.23.
//

#ifndef ASYNCSERVER_MAINWINDOW_H
#define ASYNCSERVER_MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui{};
};


#endif //ASYNCSERVER_MAINWINDOW_H
