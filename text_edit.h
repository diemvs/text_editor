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
    enum codecType {
        UTF8 = 0,
        WINDOWS1251 = 1,
        IBM866 = 2,
        CP1251 = 3
    };

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
    void codecCP1251();
    void codecIBM866();
    void codecUTF8();
    void codecWindows1251();
    void codecButton(codecType type);
    void turnOnHl();
    void turnOffHl();

private:
    Ui::Text_edit *ui;
    QString _fileName, _openedFileName, _str;
    QByteArray _strUTF8;

    QColor _pal, _fontColour;
    QPalette _bColour;
    QShortcut *_hotKeySave, *_hotKeyOpen, *_hotKeyUndo;

    Highlighter *_highlighter = nullptr;
    QTextEdit *editor;
    QTextCodec *codec;
};

#endif // TEXT_EDIT_H
