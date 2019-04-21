#include "text_edit.h"
#include "highlighter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Text_edit w;
    w.show();

    return a.exec();
}
