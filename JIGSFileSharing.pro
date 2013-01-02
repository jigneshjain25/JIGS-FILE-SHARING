TEMPLATE += app

RESOURCES += ftp.qrc

QT += gui declarative
QT += network


HEADERS += \
    MainFrame.h \
    JIGSNetworkReply.h \
    qftp.h \
    qurlinfo.h

SOURCES += \
    MainFrame.cpp \
    Main.cpp \
    JIGSNetworkReply.cpp \
    qftp.cpp \
    qurlinfo.cpp
