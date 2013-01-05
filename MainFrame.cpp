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
#include <QVBoxLayout>
#include <QHeaderView>
#include <QProgressDialog>
#include <QAbstractNetworkCache>
#include <QSplashScreen>

#include "MainFrame.h"
#include "JIGSNetworkReply.h"
#include "JIGSProgressDialog.h"
#include "qftp.h"

FtpApp::FtpApp()
{
    manager = new QNetworkAccessManager(this);    
    setWindowTitle("JIGS File Sharing");
    setGeometry(430,300,555,400);

    QMovie *movie = new QMovie(":/images/waiting.gif");
    processLabel = new QLabel(this);
    processLabel->setMovie(movie);
    movie->start();

    splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/FtpSplash.png"));
    splash->show();

    createStatusBar();
    createActions();
    createMenus();

    fileList = new QTreeWidget;
    fileList->setEnabled(false);
    fileList->setRootIsDecorated(false);
    fileList->setHeaderLabels(QStringList() << tr("Name") << tr("Size") << tr("Owner") << tr("Group") << tr("Time"));
    fileList->setColumnWidth(0,150);

    connect(fileList,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(downloadFile(QTreeWidgetItem*)));

    getFiles();
}

void FtpApp::getFiles()
{
    Qt::Alignment leftBottom = Qt::AlignLeft | Qt::AlignBottom;

    splash->showMessage("Looking up host...",leftBottom,Qt::white);
    statusLabel->setText("Looking up host...");
    ftp = new QFtp(this);
    fileList->clear();

    connect(ftp, SIGNAL(listInfo(QUrlInfo)),
                this, SLOT(addToList(QUrlInfo)));
    connect(ftp,SIGNAL(stateChanged(int)),this,SLOT(changeOfState(int)));

    QUrl url("ftp://ftp.ftpjigs.comze.com/public_html/");
    url.setPort(21);
    url.setUserName("a1996228");
    url.setPassword("11107jigs");
    std::cout<<qPrintable(url.path())<<"\n";
    ftp->connectToHost(url.host(),url.port(21));
    ftp->login(url.userName(),url.password());
}

void FtpApp::changeOfState(int state)
{
    Qt::Alignment leftBottom = Qt::AlignLeft | Qt::AlignBottom;

    if(state==2){
        splash->showMessage("Connecting...",leftBottom,Qt::white);
        statusLabel->setText("Connecting...");
    }
    else if(state==3){
        splash->showMessage("Connected...Loging In...",leftBottom,Qt::white);
        statusLabel->setText("Connected...Loging In...");
    }
    else if(state==4){
        splash->showMessage("Logged In...Getting file list...",leftBottom,Qt::white);
        statusLabel->setText("Logged In...Getting file list...");
        fileList->setEnabled(true);
        ftp->cd("public_html");        
        ftp->list();
    }
}

void FtpApp::addToList(const QUrlInfo &urlInfo)
{
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, urlInfo.name());
    item->setText(1, QString::number(float(urlInfo.size())/1000)+"KB");
    item->setText(2, urlInfo.owner());
    item->setText(3, urlInfo.group());
    item->setText(4, urlInfo.lastModified().toString("MMM dd yyyy"));    

    fileSize[urlInfo.name()]=urlInfo.size();

    QPixmap pixmap(urlInfo.isDir() ? ":/images/dir.png" : ":/images/file.png");
    item->setIcon(0, pixmap);

    fileList->addTopLevelItem(item);
    if (!fileList->currentItem()) {
        fileList->setCurrentItem(fileList->topLevelItem(0));
        fileList->setEnabled(true);
    }
    statusLabel->setText("Status");
    this->setContentsMargins(0,0,0,0);
    this->setCentralWidget(fileList);
    //if(processLabel!=0) {delete processLabel;std::cout<<"Success";}
    splash->close();
    this->show();
}

void FtpApp::createMenus()
{
    file = menuBar()->addMenu(tr("&File"));
    file->addAction(refresh);
    file->addSeparator();
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
    refresh = new QAction("&Refresh",this);
    refresh->setStatusTip("Refresh the list of files");
    refresh->setShortcut(Qt::Key_F5);
    connect(refresh,SIGNAL(triggered()),this,SLOT(refreshList()));

    quitAction = new QAction(tr("&Quit"),this);
    quitAction->setStatusTip("Quit the JIGS File Sharing");
    quitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

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

void FtpApp::refreshList()
{
    fileList->clear();
    fileSize.clear();         

    //this->setContentsMargins(250,0,0,0);
    //this->setCentralWidget(processLabel);

    getFiles();
}

void FtpApp::quit()
{
    close();
    QCoreApplication::exit();
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
    url.setUrl(address);
    url.setPort(21);
    url.setUserName("a1996228");
    url.setPassword("11107jigs");

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
    if(fileName!=0){
        QHash<QString, qint64>::const_iterator i = fileSize.find(fileName);
        if(i==fileSize.end()) QMessageBox::information(this,"File Not Found","No such file is present on server");
    else
        {
            QString file=QFileDialog::getSaveFileName(this,tr("Save Downloaded File"),"/home/gaurav/Downloads/"+fileName);

            if(file!=0){
                url.setUrl("ftp://ftp.ftpjigs.comze.com/public_html/"+fileName);
                url.setPort(21);
                url.setUserName("a1996228");
                url.setPassword("11107jigs");

                QNetworkRequest download(url);
                statusLabel->setText("Downloading file...wait!");

                JIGSProgressDialog *progressDialog=new JIGSProgressDialog();

                progressDialog->show();
                progressDialog->setTotal(fileSize[fileName]);
                progressDialog->setFixedWidth(300);

                JIGSNetworkReply *qreply=new JIGSNetworkReply(manager->get(download));
                JIGSNetworkReply *reply=qreply->getJIGSNetworkReply();

                reply->setFileName(file);

                connect(reply->reply,SIGNAL(downloadProgress(qint64,qint64)),progressDialog,SLOT(setProgress(qint64)));
                connect(reply->reply,SIGNAL(finished()),progressDialog,SLOT(setProgress()));
                connect(reply,SIGNAL(downloadedData(QByteArray,QString)),this,SLOT(writeDownloadedFile(QByteArray,QString)));
                connect(reply->reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(checkError(QNetworkReply::NetworkError)));
            }
        }
    }
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

void FtpApp::downloadFile(QTreeWidgetItem* item)
{
    QString fileName=item->text(0);
    QString file=QFileDialog::getSaveFileName(this,tr("Save Downloaded File"),"/home/gaurav/Downloads/"+fileName);

    if(file!=0){
    url.setUrl("ftp://ftp.ftpjigs.comze.com/public_html/"+fileName);
    url.setPort(21);
    url.setUserName("a1996228");
    url.setPassword("11107jigs");

    QNetworkRequest download(url);
    statusLabel->setText("Downloading file...wait!");

    JIGSProgressDialog *progressDialog=new JIGSProgressDialog();

    progressDialog->show();
    progressDialog->setTotal(fileSize[fileName]);
    progressDialog->setFixedWidth(300);

    JIGSNetworkReply *qreply=new JIGSNetworkReply(manager->get(download));
    JIGSNetworkReply *reply=qreply->getJIGSNetworkReply();    

    reply->setFileName(file);    

    connect(reply->reply,SIGNAL(downloadProgress(qint64,qint64)),progressDialog,SLOT(setProgress(qint64)));
    connect(reply->reply,SIGNAL(finished()),progressDialog,SLOT(setProgress()));
    connect(reply,SIGNAL(downloadedData(QByteArray,QString)),this,SLOT(writeDownloadedFile(QByteArray,QString)));
    connect(reply->reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(checkError(QNetworkReply::NetworkError)));
    }
}
