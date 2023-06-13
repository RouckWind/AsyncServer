#include <server.h>

#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:

    void clientsCount();
    void clientJoined();
    void clientLeft();
    void sendData();
    void receiveData();
    void clientConnected();

    void onpushButton_clicked();

private:
    TCPServer::Server server;
    QListWidget* listWidget;
    QVBoxLayout* layout1;
    QPushButton* pushButton;
};
