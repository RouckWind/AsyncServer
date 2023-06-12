#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:

    void onpushButton_clicked();

public:
    ~MainWindow() override;
};
