#include <QtGui>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QNetworkReply>
#include <QProgressBar>
#include <QAuthenticator>
#include <iostream>
#include <QFileDialog>
#include <QInputDialog>

#include "MainFrame.h"
#include "JIGSNetworkReply.h"

FtpApp::FtpApp()
{
    manager = new QNetworkAccessManager(this);
    url.setPort(21);
    url.setUserName("a1996228");
    url.setPassword("11107jigs");

    setWindowTitle("JIGS File Sharing");
    setGeometry(250,150,700,500);
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
    download->addAction(downloadFileAction);

    help=menuBar()->addMenu(tr("&Help"));
    help->addAction(aboutAction);

}

void FtpApp::createActions()
{
    quitAction = new QAction(tr("&Quit"),this);
    quitAction->setStatusTip("Quit the JIGS File Sharing");
    quitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutAction=new QAction(tr("&About"),this);
    aboutAction->setStatusTip("About JIGS File Sharing");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutPopup()));

    uploadFileAction=new QAction("&Upload Single File",this);
    uploadFileAction->setShortcut(Qt::CTRL + Qt::Key_U);
    uploadFileAction->setStatusTip("Upload a single File to the FTP Server");
    connect(uploadFileAction,SIGNAL(triggered()),this,SLOT(uploadFile()));

    downloadFileAction = new QAction("&Download Single File",this);
    downloadFileAction->setShortcut(Qt::CTRL + Qt::Key_D);
    downloadFileAction->setStatusTip("Download a single file from FTP sever");
    connect(downloadFileAction,SIGNAL(triggered()),this,SLOT(downloadFile()));
}

void FtpApp::createStatusBar()
{
    statusLabel = new QLabel("Status");
    statusBar()->addWidget(statusLabel);
}

void FtpApp::uploadFile(){
    progressBar = new QProgressBar();
    progressBar->setAlignment(Qt::AlignCenter);
   // progressBar->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowTransparentForInput);
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    progressBar->setFixedWidth(300);

    manager = new QNetworkAccessManager(this);

    QString fileName = QFileDialog::getOpenFileName(this,"Select File to Upload","","*");
    if(fileName.isNull())return;

    QFile *file = new QFile(fileName);
    QFileInfo fileInfo(*file);
    file->open(QIODevice::ReadOnly);
    progressBar->setWindowTitle(fileInfo.fileName());
   // progressBar->setFixedSize(sizeHint());

    QString address("ftp://ftp.ftpjigs.comze.com/public_html/");
    address.append(fileInfo.fileName());
   // std::cout<<file->fileName().toStdString();
    url.setUrl(address);

    QNetworkRequest upload(url);
    progressBar->show();

    QNetworkReply* reply =manager->put(upload,file);
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(checkError(QNetworkReply::NetworkError)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(uploadSuccess(QNetworkReply*)));
    connect(reply,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(setMyValue(qint64,qint64)));

}

void FtpApp::setMyValue(qint64 a,qint64 b)
{
    progressBar->setValue((int)a*100/b);
}

void FtpApp::aboutPopup()
{
    QMessageBox msgBox(this);
    msgBox.setText("The document has been modified.");
    msgBox.exec();
}

void FtpApp::checkError(QNetworkReply::NetworkError e)
{
    QMessageBox msgBox(this);
    msgBox.setText("QNetworkReply::NetworkError "+e);
    msgBox.exec();
    progressBar->close();
}

void FtpApp::uploadSuccess(QNetworkReply *reply)
{
    QMessageBox msgBox(this);
    msgBox.setText("Upload Successfull : Congo!");
    msgBox.exec();
    progressBar->close();
    reply->deleteLater();
}

void FtpApp::downloadFile()
{
    QInputDialog qid(this);
    qid.setLabelText("Enter file name:");
    qid.exec();
    QString fileName = qid.textValue();

    QString file=QFileDialog::getSaveFileName(this,tr("Save Downloaded File"),"/home/gaurav/Downloads/"+fileName);

    url.setUrl("ftp://ftp.ftpjigs.comze.com/public_html/"+fileName);

    QNetworkRequest download(url);
    statusLabel->setText("Downloading file...wait!");

    JIGSNetworkReply *qreply=new JIGSNetworkReply(manager->get(download));
    JIGSNetworkReply *reply=qreply->getJIGSNetworkReply();

    reply->setFileName(file);

    connect(reply,SIGNAL(downloadedData(QByteArray,QString)),this,SLOT(writeDownloadedFile(QByteArray,QString)));
    connect(reply->reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(checkError(QNetworkReply::NetworkError)));
}

void FtpApp::writeDownloadedFile(QByteArray data,QString fileName)
{
    if(data.size()!=0){               
        if(fileName!=0){
            QFile file(fileName.toStdString().data());
            if(!file.open(QIODevice::WriteOnly))
                std::cout<<"Cannot be done now";
            file.write(data);
        }
    }
    statusLabel->setText("Status");
}
