#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    socketConnect c;
    loginDialog login(&c);
    login.show();
    return a.exec();
}
