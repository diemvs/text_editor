#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#include <QMainWindow>
#include <QRegExp>
#include <QtQuick/QQuickTextDocument>
#include <QTextEdit>
#include "highlighter.h"


namespace Ui {
class Text_edit;
}

class Text_edit : public QMainWindow
{
    Q_OBJECT

public:
    explicit Text_edit(QWidget *parent = nullptr);

    ~Text_edit();


private slots:
    void OpenFile();
    void SaveAsFile();
    void SaveFile();
    void Font();
    void FontColour();
    void NewFile();
    void BackgroundColour();
    void Undo();
    void Redo();
    void Paste();
    void Cut();
    void About();
    void Copy();
    void codec1251();

private:
    Ui::Text_edit *ui;
    QString file_name;

    QString openedFileName;
    QColor Pal;
    QPalette Bcolour;
    QShortcut *HotKeySave, *HotKeyOpen, *HotKeyUndo;

    Highlighter *highlighter;
    QTextEdit *editor;
    QColor fontColour;
    QTextCodec *codec;

};

#endif // TEXT_EDIT_H
