#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QMenu;


class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow();
private:
    QAction *upload;
    QAction *download;
    QMenu *fileMenu;
private slots:
    void uploadFile();
    void downloadFile();
};

#endif // MAINWINDOW_H
