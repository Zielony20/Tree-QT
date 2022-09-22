#include "newelementpopup.h"
#include "ui_newelementpopup.h"
#include "mainwindow.h"


NewElementPopUp::NewElementPopUp(QWidget *parent):
    QDialog(parent),
    ui(new Ui::NewElementPopUp())
{
    ui->setupUi(this);
}

NewElementPopUp::NewElementPopUp(QWidget *parent, MainWindow *mainwindow):
    QDialog(parent),
    ui(new Ui::NewElementPopUp()),
    mainwindow(mainwindow)
{
    ui->setupUi(this);
    ui->newElementEditText->setFocus();
    ui->newElementEditText->setTabChangesFocus(true);
}

NewElementPopUp::~NewElementPopUp(){
    delete ui;
}

void NewElementPopUp::on_newElementButton_clicked()
{
    setEditText(ui->newElementEditText);
    mainwindow->answerFunc_add();
}

