#include "tree.h"

Tree::Tree(QString s):QStandardItem(s),_name(s){
}

Tree::~Tree(){
}

Tree* Tree::AddSub(QString s){

    Tree* subTree = new Tree(s);
    appendRow(subTree);

    return subTree;
}

uint32_t Tree::GetSubCount(){
    return rowCount();
}

uint32_t Tree::GetAllSubCount(){

    uint32_t result = 0;

    for (uint8_t i=0;i<GetSubCount();i++){
        result += child(i)->rowCount();
    }
    result += GetSubCount();

    return result;
}



