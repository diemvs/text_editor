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
    highlighter = new Highlighter(ui->textEdit->document());

    codec = QTextCodec::codecForName("Windows-1251");

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

    connect(ui->codecCP1251, SIGNAL(triggered()), this, SLOT(codecCP1251()));
    connect(ui->codecUTF8, SIGNAL(triggered()), this, SLOT(codecUTF8()));
    connect(ui->codecIBM866, SIGNAL(triggered()), this, SLOT(codecIBM866()));
    connect(ui->codecWindows1251, SIGNAL(triggered()), this, SLOT(codecWindows1251()));

    HotKeySave = new QShortcut(this);
    HotKeySave->setKey(Qt::CTRL+Qt::Key_S);
    connect(HotKeySave, SIGNAL(activated()), this, SLOT(SaveFile()));

    HotKeyOpen = new QShortcut(this);
    HotKeyOpen->setKey(Qt::CTRL+Qt::Key_O);
    connect(HotKeyOpen, SIGNAL(activated()), this, SLOT(OpenFile()));

    HotKeyUndo = new QShortcut(this);
    HotKeyUndo->setKey(Qt::CTRL+Qt::Key_Z);
    connect(HotKeyUndo, SIGNAL(activated()), this, SLOT(Undo()));


}

Text_edit::~Text_edit()
{
    delete ui;
}

void Text_edit::OpenFile()
{
    file_name = QFileDialog::getOpenFileName(this,"Open file");
      QFile file(file_name);
      openedFileName = file_name;
      if(!file.open(QFile::ReadOnly | QFile::Text)) {
          QMessageBox::warning(this,"..","I can't open the file!");
          return;
        }
      QTextStream in(&file);
      QString text = in.readAll();
      ui->textEdit->setText(text);
      highlighter = new Highlighter(ui->textEdit->document());
      file.close();
}

void Text_edit::SaveAsFile()
{
    openedFileName = QFileDialog::getSaveFileName();
        QFile out(openedFileName);
        if (out.open(QIODevice::WriteOnly)) {
            QTextStream stream(&out);
            QString text = ui->textEdit->toPlainText();
            stream << text;
            out.flush();
            out.close();
        }
}

void Text_edit::SaveFile()
{
    QFile file(openedFileName);
      if(!file.open(QFile::WriteOnly | QFile::Text)) {
          QMessageBox::warning(this,"..","I can't save file!");
          return;
        }
      QTextStream out(&file);
      QString text = ui->textEdit->toPlainText();
      out << text;
      file.flush();
      file.close();
}

void Text_edit::Font()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok){
        ui->textEdit->setFont(font);
    }else return;
}

void Text_edit::FontColour()
{
    fontColour = QColorDialog::getColor();
    ui->textEdit->setTextColor(fontColour);
}

void Text_edit::NewFile()
{
    openedFileName = "";
    ui->textEdit->setText("");
}

void Text_edit::BackgroundColour()
{
    Pal = QColorDialog::getColor();
    ui->textEdit->setStyleSheet("QTextEdit { background-color: "+Pal.name()+" }");
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
    codec = QTextCodec::codecForName("CP-1251");
}

void Text_edit::codecIBM866()
{
    codec = QTextCodec::codecForName("IBM 866");
}

void Text_edit::codecWindows1251()
{
    codec = QTextCodec::codecForName("Windows-1251");
}

void Text_edit::codecUTF8()
{
    codec = QTextCodec::codecForName("UTF-8");
}

