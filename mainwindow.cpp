#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QCryptographicHash>
#include <QString>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QObject::connect(ui->btn_Choose,&QPushButton::clicked,this->slotChoose());
    connect(ui->btn_Choose, SIGNAL(clicked()), this, SLOT(slotChoose()));
    connect(ui->btn_Encryption, SIGNAL(clicked()), this, SLOT(slotEncryption()));
    ui->label_Status->setText("");
}

void MainWindow::slotChoose()
{
    QFileInfo fileInfo;
    fileFull = QFileDialog::getOpenFileName(this,"Open File","","Text File(*.csv)");
    ui->lineEdit_Path->setText(fileFull);
    fileInfo = QFileInfo(fileFull);
    fileName = fileInfo.fileName();
    filePath = fileInfo.absolutePath();
    qDebug() << fileFull;
    qDebug() << fileName;
    qDebug() << filePath;
    if(fileFull == "")
        ui->label_Status->setText("No file was selected!");
}

void MainWindow::slotEncryption()
{
    QString tmp = "";
    if(fileFull != "")
    {
        md5 = getMd5(fileFull);
        qDebug() << md5;

        QDateTime currentDate = QDateTime::currentDateTime();
        QString currentTime = currentDate.toString("yyyyMMdd_HHmmss");

        qDebug() << currentTime;
        if (fileName.contains(".csv"))
            tmp = fileName.replace(".csv","");
        else {
            tmp = fileName.replace(".plist","");
        }
        qDebug() << tmp;
        result = (md5 + "&" + tmp + "&" + currentTime).toUpper();
        qDebug() << result;

        QByteArray byteArray;
        byteArray = result.toUtf8();
        qDebug() << byteArray;

        QFile file(filePath + "/" + tmp + ".Key");
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.write(result.toUtf8());
        file.close();
        ui->label_Status->setText("Create encryption file successfully in" + filePath + "/" + tmp + ".Key");
    }
}

QString MainWindow::getMd5(QString path)
{
    QFile theFile(path);
    theFile.open(QIODevice::ReadOnly);
    QByteArray ba = QCryptographicHash::hash(theFile.readAll(), QCryptographicHash::Md5);
    theFile.close();
    return  ba.toHex().constData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

