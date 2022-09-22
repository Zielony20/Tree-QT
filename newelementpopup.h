#ifndef NEWELEMENTPOPUP_H
#define NEWELEMENTPOPUP_H

#include <QWidget>
#include <QDialog>
#include <QTextEdit>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class NewElementPopUp; }
QT_END_NAMESPACE


class NewElementPopUp : public QDialog
{
    Q_OBJECT
public:
    //explicit
    NewElementPopUp(QWidget *parent = nullptr);
    NewElementPopUp(QWidget *parent, MainWindow *mainwindow);
    ~NewElementPopUp();

    void setEditText(QTextEdit* te){
        _text = te;
    }
    QTextEdit* text() const{
        return _text;
    }

private slots:
    void on_newElementButton_clicked();


private:
    Ui::NewElementPopUp* ui;
    QTextEdit* _text;
    MainWindow* mainwindow;
};


#endif // NEWELEMENTPOPUP_H
