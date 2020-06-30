#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotChoose();
    void slotEncryption();

private:
    Ui::MainWindow *ui;

    QString fileFull = "";
    QString fileName = "";
    QString filePath = "";
    QString md5 = "";
    QString result = "";

    QString getMd5(QString path);
};
#endif // MAINWINDOW_H
