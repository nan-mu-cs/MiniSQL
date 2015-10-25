//
//  IndexManager.cpp
//  
//
//  Created by 杨凯 on 15/10/23.
//
//

#include "IndexManager.h"
#include "BplusTree.h"
#include <vector>
#include <sstream>
using std::stringstream;
using std::string;
using std::vector;
using namespace bpt;
void IndexManager::InsertKey(off_t pos,int key,off_t value){
    Integer ikey = key;
    bpt::BplusTree<Integer> tree(pos);
    tree.insert(ikey, value);
}

void IndexManager::InsertKey(off_t pos, float key, off_t value){
    Float fkey = key;
    bpt::BplusTree<Float> tree(pos);
    tree.insert(fkey, value);
}
void IndexManager::InsertKey(off_t pos, char * key, off_t value){
    bpt::BplusTree<String> tree(pos);
    size_t size = tree.meta.keySize - sizeof(size_t);
    String skey(key,size);
    tree.insert(skey, value);
}
/*
void InsertKey(off_t pos,sqlstruct::insertitem item,off_t value){
    if(item.data_type == sqlstruct::INTNUM)
    {
        Integer key = stoi(item.value);
        bpt::BplusTree<Integer> tree(pos);
        tree.insert(key,value);
    }
    else if(item.data_type == sqlstruct::FLOATNUM){
        Float key = stof(item.value);
        bpt::BplusTree<Float> tree(pos);
        tree.insert(key, value);
    }
    else {
        int size = item.data_type - sqlstruct::CHAR;
        if(size<=0)
            return ;
        String key(item.value.c_str(),size);
        bpt::BplusTree<String> key;
        
    }
}
 */
void IndexManager::DeleteKey(off_t pos, int key){
    Integer ikey = key;
    bpt::BplusTree<Integer> tree(pos);
    tree.remove(ikey);
}

void IndexManager::DeleteKey(off_t pos, float key){
    Float fkey = key;
    bpt::BplusTree<Float> tree(pos);
    tree.remove(fkey);
}

void IndexManager::DeleteKey(off_t pos, char *key){
    bpt::BplusTree<String> tree(pos);
    size_t size = tree.meta.keySize - sizeof(size_t);
    String skey(key,size);
    tree.remove(skey);
}

off_t IndexManager::SearchKey(off_t pos, int key){
    Integer ikey = key;
    bpt::BplusTree<Integer> tree(pos);
    off_t keypos;
    if(tree.search(ikey, keypos))
        return keypos;
    else return -1;
}

off_t IndexManager::SearchKey(off_t pos, float key){
    Float fkey = key;
    bpt::BplusTree<Float> tree(pos);
    off_t keypos;
    if(tree.search(fkey, keypos))
        return keypos;
    else return -1;
}

off_t IndexManager::SearchKey(off_t pos, char *key){
    bpt::BplusTree<String> tree(pos);
    size_t size = tree.meta.keySize - sizeof(size_t);
    String skey(key,size);
    off_t keypos;
    if(tree.search(skey, keypos))
        return keypos;
    else return -1;
}

void IndexManager::DeleteIndex(off_t pos){

}
void IndexManager::InitFromEmpty(){
    mem.freeblock = -1;
    mem.meta_nowblock = mem.meta_endblock = -1;
    mem.record_nowblock = mem.record_endblock = -1;
    fp = fopen(filepath,"wb+");
    //fseek(fp, sizeof(b), SEEK_SET);
    fwrite(&mem, sizeof(mem), 1, fp);
}
void IndexManager::InitFromFile(){
    fp = fopen(filepath, "rb+");
    fread(&mem, sizeof(mem), 1, fp);
}
off_t IndexManager::newIndex(int dataType){
    if(dataType == sqlstruct::INTNUM){
        bpt::BplusTree<Integer> tree;
        off_t pos = AllocMeta();
        tree.BuildNewTree(pos, sizeof(Integer));
        return pos;
    }
    else if(dataType == sqlstruct::FLOATNUM){
        bpt::BplusTree<Float> tree;
        off_t pos = AllocMeta();
        tree.BuildNewTree(pos, sizeof(Float));
        return pos;
    }
    else {
        int size = dataType - sqlstruct::CHAR;
        bpt::BplusTree<String> tree;
        off_t pos = AllocMeta();
        tree.BuildNewTree(pos, sizeof(size_t) + size);
        return pos;
    }
}

