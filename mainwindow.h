#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tree.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtXml>

class NewElementPopUp;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    NewElementPopUp* newElementPopUpForm;
    QStandardItemModel* model;
    QMenu* contextMenu;
    QStandardItem* tree;
    Ui::MainWindow *ui;
    QString currentFile = "";

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStandardItem* AddItem(QString name, QStandardItem* t);

private slots:
    void on_actionNew_triggered();
    void on_actionSave_triggered();
    void on_actionLoad_triggered();
    void onCustomContextMenu(const QPoint &);
    void AddItem_triggered();
    void DeleteItem_triggered();

    //void on_treeView_expanded(const QModelIndex &index);
    //void on_actionAdd_triggered();

    void on_indentationBox_valueChanged(int arg1);

private:

    QDomElement treeToXml(QDomDocument &document, QDomElement &root, QStandardItem* t);
    void traverse (const QDomNode & node, QStandardItem* t );
    void answerFunc_add();

friend NewElementPopUp;
};
#endif // MAINWINDOW_H

