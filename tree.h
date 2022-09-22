#include <stdint.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <QMainWindow>
#include <QStandardItemModel>

class Tree: public QStandardItem{
 private:
    QString _name;
  public:
    Tree(QString s);
    virtual ~Tree();

    Tree* AddSub(QString s);
    uint32_t GetSubCount();
    uint32_t GetAllSubCount();
    //void Del(int dep);
    //void print(int indentation, bool numbers = false, int level = 0);
    //void print2(int indentation, bool numbers = false, std::string index = "");
  private:
    //void setIndex(std::string i);

};
