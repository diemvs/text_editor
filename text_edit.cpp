#include "text_edit.h"
#include "ui_text_edit.h"
#include "highlighter.h"

#include <QFileDialog>
#include <QTextStream>
#include <QFontDialog>
#include <QPalette>
#include <QColorDialog>
#include <QShortcut>
#include <QMessageBox>
#include <QSyntaxHighlighter>
#include <QTextCodec>

Text_edit::Text_edit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Text_edit)
{

    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    _highlighter = new Highlighter(ui->textEdit->document());

    _codec = QTextCodec::codecForName("Windows-1251");

    connect(ui->open, SIGNAL(triggered()), this, SLOT(OpenFile()));
    connect(ui->saveAs, SIGNAL(triggered()), this, SLOT(SaveAsFile()));
    connect(ui->save, SIGNAL(triggered()), this, SLOT(SaveFile()));
    connect(ui->font, SIGNAL(triggered()), this, SLOT(Font()));
    connect(ui->fontColour, SIGNAL(triggered()), this, SLOT(FontColour()));
    connect(ui->newFile, SIGNAL(triggered()), this, SLOT(NewFile()));
    connect(ui->bColour, SIGNAL(triggered()), this, SLOT(BackgroundColour()));
    connect(ui->undo, SIGNAL(triggered()), this, SLOT(Undo()));
    connect(ui->redo, SIGNAL(triggered()), this, SLOT(Redo()));
    connect(ui->cut, SIGNAL(triggered()), this, SLOT(Cut()));
    connect(ui->paste, SIGNAL(triggered()), this, SLOT(Paste()));
    connect(ui->about, SIGNAL(triggered()), this, SLOT(About()));
    connect(ui->copy, SIGNAL(triggered()), this, SLOT(Copy()));

    connect(ui->hlOn, SIGNAL(triggered()), this, SLOT(turnOnHl()));
    connect(ui->hlOff, SIGNAL(triggered()), this, SLOT(turnOffHl()));

    connect(ui->codecCP1251, SIGNAL(triggered()), this, SLOT(codecCP1251()));
    connect(ui->codecUTF8, SIGNAL(triggered()), this, SLOT(codecUTF8()));
    connect(ui->codecIBM866, SIGNAL(triggered()), this, SLOT(codecIBM866()));
    connect(ui->codecWindows1251, SIGNAL(triggered()), this, SLOT(codecWindows1251()));

    _hotKeySave = new QShortcut(this);
    _hotKeySave->setKey(Qt::CTRL+Qt::Key_S);
    connect(_hotKeySave, SIGNAL(activated()), this, SLOT(SaveFile()));

    _hotKeyOpen = new QShortcut(this);
    _hotKeyOpen->setKey(Qt::CTRL+Qt::Key_O);
    connect(_hotKeyOpen, SIGNAL(activated()), this, SLOT(OpenFile()));

    _hotKeyUndo = new QShortcut(this);
    _hotKeyUndo->setKey(Qt::CTRL+Qt::Key_Z);
    connect(_hotKeyUndo, SIGNAL(activated()), this, SLOT(Undo()));
}

Text_edit::~Text_edit()
{
    delete ui;
}

void Text_edit::OpenFile()
{
    _fileName = QFileDialog::getOpenFileName(this,"Open file");
     QFile file(_fileName);
      _openedFileName = _fileName;
      if(!file.open(QFile::ReadOnly | QFile::Text)) {
          QMessageBox::warning(this,"..","I can't open the file!");
          return;
        }
      QTextStream in(&file);
      _str = in.readAll();
      ui->textEdit->setText(_str);
      file.close();
}

void Text_edit::SaveAsFile()
{
    _openedFileName = QFileDialog::getSaveFileName();
        QFile out(_openedFileName);
        if (out.open(QIODevice::WriteOnly)) {
            QTextStream stream(&out);
            _str = ui->textEdit->toPlainText();
            stream << _str;
            out.flush();
            out.close();
        }
}

void Text_edit::SaveFile()
{
    QFile file(_openedFileName);
      if(!file.open(QFile::WriteOnly | QFile::Text)) {
          QMessageBox::warning(this,"..","I can't save file!");
          return;
        }
      QTextStream out(&file);
      _str = ui->textEdit->toPlainText();
      out << _str;
      file.flush();
      file.close();
}

void Text_edit::Font()
{
    bool ok;
    _font = QFontDialog::getFont(&ok, this);
    if (ok){
        ui->textEdit->setFont(_font);
    }else return;
}

void Text_edit::FontColour()
{
    _fontColour = QColorDialog::getColor();
    ui->textEdit->setTextColor(_fontColour);
}

void Text_edit::NewFile()
{
    _openedFileName = "";
    ui->textEdit->setText("");
}

void Text_edit::BackgroundColour()
{
    _pal = QColorDialog::getColor();
    ui->textEdit->setStyleSheet("QTextEdit { background-color: "+_pal.name()+" }");
    ui->textEdit->show();
}

void Text_edit::Undo()
{
    ui->textEdit->undo();
}

void Text_edit::Redo()
{
    ui->textEdit->redo();
}

void Text_edit::Paste()
{
    ui->textEdit->paste();
}

void Text_edit::Cut()
{
    ui->textEdit->cut();
}

void Text_edit::Copy()
{
    ui->textEdit->copy();
}

void Text_edit::About()
{
    QString about_text;
      about_text  = "Author : Sataev D.\n";
      about_text += "Group  : KMBO 02 18\n";
      about_text += "Date   : 09/04/2019\n";
      about_text += "(C) Text Editor  \n";
      QMessageBox::about(this,"About Notepad",about_text);
}

void Text_edit::codecCP1251()
{
    codecButton(CP1251);

    _str = ui->textEdit->toPlainText();
    _strUTF8 = _str.toUtf8();
    _codec = QTextCodec::codecForName("CP-1251");
    _str = _codec->toUnicode(_strUTF8);
    ui->textEdit->clear();
    ui->textEdit->setText(_str);
}

void Text_edit::codecIBM866()
{
    codecButton(IBM866);

    _str = ui->textEdit->toPlainText();
    _strUTF8 = _str.toUtf8();
    _codec = QTextCodec::codecForName("CP-1251");
    _str = _codec->toUnicode(_strUTF8);
    _codec = QTextCodec::codecForName("IBM 866");
    _str = _codec->toUnicode(_strUTF8);
    ui->textEdit->clear();
    ui->textEdit->setText(_str);
}

void Text_edit::codecWindows1251()
{
    codecButton(WINDOWS1251);

    _str = ui->textEdit->toPlainText();
    _strUTF8 = _str.toUtf8();
    _codec = QTextCodec::codecForName("Windows-1251");
    _str = _codec->toUnicode(_strUTF8);
    ui->textEdit->clear();
    ui->textEdit->setText(_str);
}

void Text_edit::codecUTF8()
{
    codecButton(UTF8);

    _str = ui->textEdit->toPlainText();
    _strUTF8 = _str.toUtf8();
    _codec = QTextCodec::codecForName("UTF-8");
    _str = _codec->toUnicode(_strUTF8);
    ui->textEdit->clear();
    ui->textEdit->setText(_str);
}


void Text_edit::codecButton(codecType type){
    switch (type){
    case UTF8:
        ui->codecCP1251->setEnabled(true);
        ui->codecIBM866->setEnabled(true);
        ui->codecUTF8->setDisabled(true);
        ui->codecWindows1251->setEnabled(true);
        break;
    case WINDOWS1251:
        ui->codecCP1251->setEnabled(true);
        ui->codecIBM866->setEnabled(true);
        ui->codecUTF8->setEnabled(true);
        ui->codecWindows1251->setDisabled(true);
        break;
    case IBM866:
        ui->codecCP1251->setEnabled(true);
        ui->codecIBM866->setDisabled(true);
        ui->codecUTF8->setEnabled(true);
        ui->codecWindows1251->setEnabled(true);
        break;
    case CP1251:
        ui->codecCP1251->setDisabled(true);
        ui->codecIBM866->setEnabled(true);
        ui->codecUTF8->setEnabled(true);
        ui->codecWindows1251->setEnabled(true);
        break;

    }
}


void Text_edit::turnOnHl(){
     _highlighter = new Highlighter(ui->textEdit->document());
     QMessageBox::information(this, "INFO", "Highlighter is on!");
        }


void Text_edit::turnOffHl(){
    delete _highlighter;
    _highlighter = nullptr;
    QMessageBox::information(this, "INFO", "Highlighter is off!");
}
