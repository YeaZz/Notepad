#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Notepad.h"

class Notepad : public QMainWindow {
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private:
    Ui::NotepadClass ui;
    QString currentFile;
private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_actionExit_triggered();
};
