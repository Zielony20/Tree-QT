#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileSystemModel>
#include <QDebug>
#include "newelementpopup.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    tree = model->invisibleRootItem();
    ui->treeView->setModel(model);
    contextMenu = new QMenu(ui->treeView);
    contextMenu->addAction("Add", this, SLOT(AddItem_triggered()));
    contextMenu->addAction("Delete", this, SLOT(DeleteItem_triggered()));
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->treeView,
            SIGNAL(customContextMenuRequested(const QPoint &)),
            this,
            SLOT(onCustomContextMenu(const QPoint &)));

    //connect(pushButton, SIGNAL(clicked()), popupWindow, SLOT(exec()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onCustomContextMenu(const QPoint &point)
{
    QModelIndex index = ui->treeView->indexAt(point);
    if (index.isValid() ) {
        contextMenu->exec(ui->treeView->viewport()->mapToGlobal(point));
    }
}

QStandardItem* MainWindow::AddItem(QString name, QStandardItem* t)
{
    QStandardItem *app = new QStandardItem(name);
    t->appendRow(app);
    QList<QStandardItem*> l;

    return app;
}

void MainWindow::AddItem_triggered(){

    newElementPopUpForm = new NewElementPopUp(this,this);
    newElementPopUpForm->show();

}

void MainWindow::answerFunc_add(){

    newElementPopUpForm->hide();
    QString t = newElementPopUpForm->text()->toPlainText();


    QModelIndex index = ui->treeView->currentIndex();

    //if new part of tree
    if(index.row()!=-1){
        QStandardItem * item {model->itemFromIndex(index)};
        AddItem(t, item);
    }
    //if new tree
    else{
        AddItem(t, tree);
    }
    ui->treeView->setExpanded(index,true);
    delete newElementPopUpForm;
}

void MainWindow::DeleteItem_triggered(){    
    QModelIndex index = ui->treeView->currentIndex();
    QStandardItem * item {model->itemFromIndex(index)};
    int row = index.row();

    //contition because item->parent()->removeRow(row) crush if parent is root of treeview
    if(index.parent().row()== -1){
        tree->removeRow(row);
    }
    else{
        item->parent()->removeRow(row);
    }
}

void MainWindow::on_actionNew_triggered(){
    currentFile.clear();

    while(tree->hasChildren()){
        tree->removeRow(0);
    }

    newElementPopUpForm = new NewElementPopUp(this,this);
    newElementPopUpForm->show();


}

QDomElement MainWindow::treeToXml(QDomDocument &document, QDomElement &root, QStandardItem* t){
    QDomElement tr = document.createElement("tree");
    QDomText text = document.createTextNode(t->text());
    QDomElement name = document.createElement("name");

    tr.appendChild(name);
    root.appendChild(tr);
    name.appendChild(text);

    for(int i=0;i<t->rowCount();i++){
        //qDebug()<<t->rowCount();
        QDomElement subtr = treeToXml(document, tr, t->child(i));
    }
    return root;
}

void MainWindow::traverse ( const QDomNode & node, QStandardItem* t ) {
        QDomNode domNode = node.firstChild();

        while (!domNode.isNull()){
            if (domNode.isElement()) {
                QDomElement domElement = domNode.toElement();
                if (!domElement.isNull()){
                    if(domElement.tagName() == "name")
                    {
                        //qDebug()<<"\t"<<domElement.tagName()<<": "<<domElement.text();
                        t = AddItem(domElement.text(),t);

                    }
                }
            }
            traverse(domNode, t);
            domNode = domNode.nextSibling();
        }
    }

void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot save file: "+file.errorString());
        return;
    }

    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QDomDocument document;
    QDomElement root = document.createElement("tree");
    document.appendChild(root);
    document.appendChild(treeToXml(document, root, tree->child(0)));
    out << document.toString();
    file.close();
}

void MainWindow::on_actionLoad_triggered()
{

    QString filename = QFileDialog::getOpenFileName((this));
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot open file: "+file.errorString());
        return;
    }

    QDomDocument doc;
    if (doc.setContent(&file)) // if successfull then proceed
    {
        qDebug()<<"test";

        QDomElement elem = doc.documentElement();

        tree->clearData();
        tree->removeRows(0,tree->rowCount());

        traverse(elem,tree);
    }
    file.close();
}

void MainWindow::on_indentationBox_valueChanged(int arg1)
{
    ui->treeView->setIndentation(arg1);
}

