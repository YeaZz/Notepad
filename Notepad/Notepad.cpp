#include "Notepad.h"
#include "ui_notepad.h"
#include <QFileDialog>
#include <QMessageBox>

Notepad::Notepad(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
}

Notepad::~Notepad() {
}

void Notepad::on_actionNew_triggered() {
    currentFile.clear();
    ui.textEdit->setText(QString());
}

void Notepad::on_actionOpen_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " +
            file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui.textEdit->setText(text);
    file.close();
}

void Notepad::on_actionSave_triggered() {
    QFile* file;
    if (currentFile.isEmpty()) {
        QString fileName = QFileDialog::getSaveFileName(this, "Save the file");
        if (fileName.isEmpty())
            return;
        file = new QFile(fileName);
        currentFile = fileName;
        setWindowTitle(fileName);
    } else
        file = new QFile(currentFile);
    if ((*file).open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(file);
        out << ui.textEdit->toPlainText();
    }
    delete file;
}

void Notepad::on_actionSave_as_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save the file");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    currentFile = fileName;
    setWindowTitle(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << ui.textEdit->toPlainText();
    }
    setWindowTitle(fileName);
}

void Notepad::on_actionExit_triggered() {
    close();
}