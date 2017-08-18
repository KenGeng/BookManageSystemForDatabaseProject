#include "bms.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));//solve the encoding problem of ºº×Ö
    Widget w;

    w.show();

    return a.exec();
}
