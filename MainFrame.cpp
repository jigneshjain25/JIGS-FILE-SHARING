#include <QtGui>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QNetworkReply>
#include <QAuthenticator>
#include <iostream>
#include <QFileDialog>
#include "MainFrame.h"

FtpApp::FtpApp()
{
    setWindowTitle("JIGS File Sharing");
    setGeometry(150,150,700,500);
    QPalette palette;
    palette.setColor(backgroundRole(), Qt::cyan);
    setPalette(palette);
    createStatusBar();
    createActions();
    createMenus();
}

void FtpApp::createMenus()
{
    file = menuBar()->addMenu(tr("&File"));
    file->addAction(quitAction);

    upload = menuBar()->addMenu(tr("&Upload"));
    upload->addAction(uploadFileAction);

    download = menuBar()->addMenu(tr("&Download"));

    help=menuBar()->addMenu(tr("&Help"));
    help->addAction(aboutAction);

}

void FtpApp::createActions()
{
    quitAction = new QAction(tr("&Quit"),this);
    quitAction->setStatusTip("Quit the JIGS File Sharing");
    quitAction->setShortcut(tr("Ctrl+Q"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutAction=new QAction(tr("&About"),this);
    aboutAction->setStatusTip("About JIGS File Sharing");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutPopup()));

    uploadFileAction=new QAction("Upload Single File",this);
    uploadFileAction->setShortcut(Qt::CTRL + Qt::Key_U);
    uploadFileAction->setStatusTip("Upload a single File to the FTP Server");
    connect(uploadFileAction,SIGNAL(triggered()),this,SLOT(uploadFile()));
}

void FtpApp::createStatusBar()
{
    statusLabel = new QLabel("Status");
    statusBar()->addWidget(statusLabel);
}

void FtpApp::uploadFile(){
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    QString fileName = QFileDialog::getOpenFileName(this,"Select File to Upload","","*");
    if(fileName.isNull())return;

    QFile *file = new QFile(fileName);
    QFileInfo fileInfo(*file);
    file->open(QIODevice::ReadOnly);

    QString address("ftp://ftp.ftpjigs.comze.com/public_html/");
    address.append(fileInfo.fileName());
    std::cout<<file->fileName().toStdString();
    QUrl url(address);
    url.setPort(21);
    url.setUserName("a1996228");
    url.setPassword("11107jigs");
    QNetworkRequest upload(url);
    statusLabel->setText("Uploading..wait");
    QNetworkReply* reply =manager->put(upload,file);
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(checkError(QNetworkReply::NetworkError)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(uploadSuccess()));
}

void FtpApp::aboutPopup()
{
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();
}

void FtpApp::checkError(QNetworkReply::NetworkError e)
{
    statusLabel->setText("Upload Failed");
    QMessageBox msgBox;
    msgBox.setText("QNetworkReply::NetworkError "+e);
    msgBox.exec();
    statusLabel->setText("Status");
}

void FtpApp::uploadSuccess()
{
    statusLabel->setText("Upload Successfull");
    QMessageBox msgBox;
    msgBox.setText("Upload Successfull : Congo!");
    msgBox.exec();
    statusLabel->setText("Status");
}
