#include <QtGui>
#include <QAction>
#include <QMenuBar>
#include <mainwindow.h>

MainWindow :: MainWindow(){
    upload=new QAction("&Upload" , this);
    upload->setStatusTip("Upload a file to the server");
    upload->setShortcut(Qt::CTRL + Qt::Key_U);
    connect(upload,SIGNAL(triggered()),this,SLOT(uploadFile()));

    download = new QAction("&Download",this);
    download->setStatusTip("Download the selected file");
    download->setShortcut(Qt::CTRL + Qt::Key_D);
    connect(download,SIGNAL(triggered()),this,SLOT(downloadFile()));

    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(upload);
    fileMenu->addAction(download);

    setWindowTitle("JIGS File Sharing");
    setGeometry(250,200,600,300);
}
void MainWindow :: uploadFile(){

}
void MainWindow :: downloadFile(){

}
