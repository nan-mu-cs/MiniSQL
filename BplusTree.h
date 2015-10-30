//
//  BplusTree.h
//  BplusTree
//
//  Created by 杨凯 on 15/9/24.
//  Copyright (c) 2015年 杨凯. All rights reserved.
//

#ifndef BplusTree_BplusTree_h
#define BplusTree_BplusTree_h

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <queue>
#include "IndexManager.h"
#include "BufferManager.hpp"
namespace bpt {
#define FILENAME 512
#define OFFSET_META 0
#define BLOCKSIZE 4096
#define value_t off_t
#define RECORD_START_BLOCK 2
#define META_START_BLOCK 1
#define BLOCK_HEAD 8
#define META_SIZE sizeof(meta_t)
#define BLOCKREMAINDER 10000
#define NODESIZE (sizeof(node_t) - 2*sizeof(struct record_t*) + (meta.order+1)*(meta.keySize + meta.valueSize) + 4
//char filepath[FILENAME] = "/Users/andyyang/Documents/MiniSQL/MiniSQL/index.txt";
std::string filepath = "./data/index.data";
struct mem_t{
    off_t freeblock;
    off_t record_endblock;
    off_t record_nowblock;
    off_t meta_nowblock;
    off_t meta_endblock;
} mem;
struct meta_t{
    size_t order;
    size_t valueSize;
    size_t keySize;
    off_t rootOffset;
    off_t leafOffset;
};
FILE *fp;
BufferManager *bm;
int fp_level;
    /*
void Openfile(const char *mode="rb+"){
    if(fp_level == 0)
        fp = fopen(filepath,mode);
    fp_level++;
}
void Closefile(){
    if(fp_level == 1)
        fclose(fp);
    fp_level--;
}*/
int NextFreeBlock(){
    return -1;
}
off_t AllocMeta(){
    size_t used = 0;
    bool flag = false;
    if(mem.meta_nowblock == -1){
        mem.meta_nowblock = META_START_BLOCK;
        mem.meta_endblock = META_START_BLOCK;
        flag = true;
    }
    else {
        //Openfile();
        //fseek(fp, mem.meta_nowblock*BLOCKSIZE, SEEK_SET);
        //fread(&used, sizeof(size_t), 1, fp);
        bm->constReadBuffer(filepath, mem.meta_nowblock, &used, 0, sizeof(size_t));
    }
    if(used + META_SIZE>BLOCKSIZE||flag){
        used = 0;
        if(!flag){
            if(mem.freeblock!=-1)
                mem.meta_nowblock = mem.freeblock;
            else{
                mem.meta_nowblock = mem.meta_endblock + 1;
                mem.meta_endblock++;
            }
        }
        //Openfile();
        //fseek(fp, mem.meta_nowblock*BLOCKSIZE, SEEK_SET);
        used = META_SIZE + BLOCK_HEAD;
        //fwrite(&used, sizeof(size_t), 1, fp);
        //Closefile();
        bm->writeBuffer(filepath, mem.meta_nowblock, &used, 0, sizeof(size_t));
        bm->save();
        return BLOCK_HEAD + mem.meta_nowblock*BLOCKREMAINDER;
    }
    else {
        off_t tmp = used;
        used += META_SIZE;
        //Openfile();
        //fseek(fp, mem.meta_nowblock*BLOCKSIZE, SEEK_SET);
        //fwrite(&used, sizeof(size_t), 1, fp);
        //Closefile();
        bm->writeBuffer(filepath, mem.meta_nowblock, &used, 0, sizeof(size_t));
        bm->save();
        return tmp + mem.meta_nowblock*BLOCKREMAINDER;
    }
}
template<typename key_t>
    class BplusTree{
    public:
        meta_t meta;
    private:
        struct record_t{
            key_t key;
            off_t value;
        };
        struct node_t{
            off_t parent;
            off_t next;
            off_t pre;
            size_t n;
            bool isleaf;
            struct record_t *children;
        };
        /*
        struct record_t{
            key_t key;
            value_t value;
        };
        struct leafNode_t{
            off_t parent;
            off_t next;
            off_t pre;
            size_t n;
            struct record_t *children;
        };*/
        void map(node_t *node,off_t pos){
            //Openfile();
            //fseek(fp,offset,SEEK_SET);
            /*
            size_t rd = fread(&(node->parent),sizeof(node->parent),1,fp);
            rd += fread(&(node->pre),sizeof(node->pre),1,fp);
            rd += fread(&(node->next),sizeof(node->next),1,fp);
            rd += fread(&(node->n),sizeof(node->n),1,fp);
            rd += fread(&(node->isleaf),sizeof(node->isleaf),1,fp);
            */
            int blockindex = pos/BLOCKREMAINDER;
            int blockoffset = pos%BLOCKREMAINDER;
            bm->constReadBuffer(filepath, blockindex, &(node->parent), blockoffset, sizeof(node->parent));
            blockoffset += sizeof(node->parent);
            bm->constReadBuffer(filepath, blockindex, &(node->pre), blockoffset, sizeof(node->pre));
            blockoffset += sizeof(node->pre);
            bm->constReadBuffer(filepath, blockindex, &(node->next), blockoffset, sizeof(node->next));
            blockoffset += sizeof(node->next);
            bm->constReadBuffer(filepath, blockindex, &(node->n), blockoffset, sizeof(node->n));
            blockoffset += sizeof(node->n);
            bm->constReadBuffer(filepath, blockindex, &(node->isleaf), blockoffset, sizeof(node->isleaf));
            blockoffset += sizeof(node->isleaf);
            //rd += fread(node->children,(meta.keySize + meta.valueSize),meta.order+1,fp);
            for(int i = 0;i<meta.order+1;i++){
                //node->children[i].key.Read(fp);
                Read(blockindex,blockoffset,node->children[i].key);
                //fread(&(node->children[i].value),sizeof(value_t),1,fp);
                bm->constReadBuffer(filepath, blockindex, &(node->children[i].value), blockoffset, sizeof(value_t));
                blockoffset += sizeof(value_t);
            }
            //bm->save();
            //Closefile();
            //for(int i = 0;i<node->n;i++)
              //  std::cout << node->children[i].key.k << std::endl;
            //if(rd == 6)
              //  return true;
            //else return false;
        }
        off_t AllocStorage(){
            //off_t slot = meta.slot;
            //meta.slot += size;
            //if(mem.nowblock == -1)
            /*
            bool flag = false;
            size_t used = 0;
            if(mem.record_nowblock == -1){
                flag = true;
                mem.record_nowblock = RECORD_START_BLOCK;
            }
            else {
                Openfile();
                fseek(fp, mem.record_nowblock*BLOCKSIZE, SEEK_SET);
                fread(&used,sizeof(size_t),1,fp);
            }
            if(flag||used + size>BLOCKSIZE){
                used = 0;
                if(!flag){
                    if(mem.freeblock !=-1)
                        mem.record_nowblock = mem.freeblock;
                    else mem.record_nowblock = ++mem.record_endblock;
                }
                used = size + BLOCK_HEAD;
                Openfile();
                fseek(fp, mem.record_nowblock*BLOCKSIZE, SEEK_SET);
                fwrite(&used, sizeof(size_t), 1, fp);
                Closefile();
                return BLOCK_HEAD + BLOCKSIZE*mem.record_nowblock;
            }
            else {
                off_t tmp = used;
                used += size;
                Openfile();
                fseek(fp, mem.record_nowblock*BLOCKSIZE, SEEK_SET);
                fwrite(&used, sizeof(size_t), 1, fp);
                Closefile();
                return tmp + mem.record_nowblock*BLOCKSIZE;
            }*/
            if(mem.freeblock!=-1){
                mem.freeblock = NextFreeBlock();
                return mem.freeblock*BLOCKREMAINDER;
            }
            else if(mem.record_endblock == -1){
                mem.record_nowblock = RECORD_START_BLOCK;
                mem.record_endblock = RECORD_START_BLOCK;
                return mem.record_endblock*BLOCKREMAINDER;
            }
            else{
                mem.record_endblock++;
                return mem.record_endblock*BLOCKREMAINDER;
            }
        }
        /*
        off_t AllocStorage(node_t &node){
            //node.n = 1;
            //meta.internalNodeNum++;
            //return AllocStorage(sizeof(node));
            off_t slot = meta.slot;
            meta.slot += NODESIZE;//needed changed
            return slot;
        }*/
        void unmap(node_t *node,off_t pos){
            //Openfile();
            //fseek(fp,offset,SEEK_SET);
            /*
            size_t wd = fwrite(&(node->parent),sizeof(node->parent),1,fp);
            wd += fwrite(&(node->pre),sizeof(node->pre),1,fp);
            wd += fwrite(&(node->next),sizeof(node->next),1,fp);
            wd += fwrite(&(node->n),sizeof(node->n),1,fp);
            wd += fwrite(&(node->isleaf),sizeof(node->isleaf),1,fp);
            //wd += fwrite(node->children,(meta.keySize + meta.valueSize),meta.order+1,fp);
            */
            int blockindex = pos/BLOCKREMAINDER;
            int blockoffset = pos % BLOCKREMAINDER;
            bm->writeBuffer(filepath, blockindex, &(node->parent), blockoffset, sizeof(node->parent));
            blockoffset += sizeof(node->parent);
            bm->writeBuffer(filepath, blockindex, &(node->pre), blockoffset, sizeof(node->pre));
            blockoffset += sizeof(node->pre);
            bm->writeBuffer(filepath, blockindex, &(node->next), blockoffset, sizeof(node->next));
            blockoffset += sizeof(node->next);
            bm->writeBuffer(filepath, blockindex, &(node->n), blockoffset, sizeof(node->n));
            blockoffset += sizeof(node->n);
            bm->writeBuffer(filepath, blockindex, &(node->isleaf), blockoffset, sizeof(node->isleaf));
            blockoffset += sizeof(node->isleaf);
            for(int i = 0;i<meta.order+1;i++){
                //node->children[i].key.Write(fp);
                Write(blockindex,blockoffset,node->children[i].key);
                //fwrite(&(node->children[i].value),sizeof(value_t),1,fp);
                bm->writeBuffer(filepath, blockindex, &(node->children[i].value), blockoffset, sizeof(value_t));
                blockoffset += sizeof(value_t);
            }
            bm->save();
            //Closefile();
            //Openfile();
            //fseek(fp,offset,SEEK_SET);
            //off_t parent;
            //fread(&parent, sizeof(off_t), 1, fp);
            //std::cout << parent << std::endl;
            //Closefile();
            //if(wd == 6)
             //   return true;
            //else return false;
        }
        void map(off_t pos){
            int blockindex = pos/BLOCKREMAINDER;
            int blockoffset = pos % BLOCKREMAINDER;
            //Openfile();
            //fseek(fp,pos,SEEK_SET);
            //size_t rd = fread(meta,sizeof(meta),1,fp);
            //Closefile();
            //if(rd!=1)
              //  return false;
            //else return true;
            bm->constReadBuffer(filepath, blockindex, &meta, blockoffset, sizeof(meta));
        }
        void unmap(off_t pos){
            //Openfile();
            //fseek(fp,offset,SEEK_SET);
            //size_t wd = fwrite(block,size,1,fp);
            //Closefile();
            //if(wd == 1)
            //return true;
            //else return false;
            int blockindex = pos /BLOCKREMAINDER;
            int blockoffset = pos % BLOCKREMAINDER;
            bm->writeBuffer(filepath, blockindex, &meta, blockoffset, sizeof(meta));
            bm->save();
        }

        off_t SearchNode(off_t rt,const key_t &key){
            node_t node;
            node.children = new record_t[meta.order+1];
            map(&node,rt);
            if(node.isleaf){
                delete [] node.children;
                return rt;
            }
            else{
                int i = 0;
                for(i = 0;i<node.n;i++)
                    if(key.cmp(key,node.children[i].key))
                        break;
                off_t next;
                next = node.children[i].value;
                //free(node.children);
                delete [] node.children;
                return SearchNode(next,key);
            }
        }
        void InsertInLeaf(const off_t pointer,const key_t &key,const value_t &value){
            node_t node;
            node.children = new record_t [meta.order+1];
            map(&node,pointer);
            int i = 0;
            for(i = 0;i<node.n;i++)
                if(key.cmp(key,node.children[i].key))
                    break;
            int j = 0;
            if(node.n)
                node.children[node.n+1].value = node.children[node.n-1].value;
            for(j = node.n;j>i;j--)
                node.children[j] = node.children[j-1];
            node.children[i].key = key;
            node.children[i].value = value;
            node.n++;
            unmap(&node,pointer);
            //free(node.children);
            delete [] node.children;
        }
        off_t SplitInternalNode(const off_t &pare,const off_t &p,const key_t &key,const off_t newp,key_t &newkey){
            node_t node;
            node.children = new record_t [meta.order+1];
            //std::cout << "splitinternal--node" << node.children << std::endl;
            record_t *tmp = new record_t [meta.order+3];
            //std::cout << "splitinternal--tmp" << tmp << std::endl;
            node_t newnode;
            newnode.children = new record_t [meta.order+1];
            //std::cout << "splitinternal--newnode" << newnode.children << std::endl;
            node_t childnode;
            childnode.children = new record_t [meta.order+1];
            //std::cout << "splitinternal--childnode" << childnode.children << std::endl;
            map(&node,pare);
            int i = 0,j = 0;
            bool flag = false;
            while(j<=meta.order){
                if(node.children[j].value == p){
                    tmp[i].value = p;
                    i++;
                    tmp[i].value = newp;
                    flag = true;
                }
                else tmp[i].value = node.children[j].value;
                i++;
                j++;
            }
          //  if(flag == false)
            //    tmp[i].value = newp;
            j = 0;
            i = 0;
            while(i<=meta.order){
                if(node.children[j].value == p){
                    tmp[j].key = key;
                }
                else {
                    tmp[j].key = node.children[i].key;
                    i++;
                }
                j++;
            }
            //if(i == j)
              //  tmp[j].key = key;
            int n = 0;
            n = (meta.order+1)/2;
            //if((meta.order+1)%2)
              //  n++;
            
            node.n = n;
            newnode.n = meta.order+1  - n - 1;
            //node_t left,right;
            //left.children = new record_t [meta.order+1];
            //right.children = new record_t [meta.order+1];
            //map(&left,p);
            //map(&right,newp);
            for(i = 0;i<n;i++){
                map(&childnode,tmp[i].value);
                childnode.parent = pare;
                unmap(&childnode,tmp[i].value);
                node.children[i].key = tmp[i].key;
                node.children[i].value = tmp[i].value;
                //if(tmp[i].value == p)
                  //  left.parent = pare;
                //if(tmp[i].value == newp)
                  //  right.parent = pare;
               // std::cout<< node.children[i].key.k << ' ' << node.children[i].value<<std::endl;
            }
            node.children[i].value = tmp[i].value;
            map(&childnode,tmp[i].value);
            childnode.parent = pare;
            unmap(&childnode,tmp[i].value);
            //if(tmp[i].value == p)
              //  left.parent = pare;
            //if(tmp[i].value == newp)
              //  right.parent = pare;
            newkey = tmp[i].key;
            i++;
            off_t newPointer = AllocStorage();
            for(j = 0;i<=meta.order;i++,j++){
                newnode.children[j].key = tmp[i].key;
                newnode.children[j].value = tmp[i].value;
                map(&childnode,tmp[i].value);
                childnode.parent = newPointer;
                unmap(&childnode,tmp[i].value);
                //if(tmp[i].value == p)
                  //  left.parent = newPointer;
                //if(tmp[i].value == newp)
                  //  right.parent = newPointer;
                //std::cout << tmp[i].key.k << ' ' << tmp[i].value << std::endl;
            }
            newnode.children[j].value = tmp[i].value;
            //if(tmp[i].value == p)
              //  left.parent = newPointer;
            //if(tmp[i].value == newp)
              //  right.parent = newPointer;
            map(&childnode,tmp[i].value);
            childnode.parent = newPointer;
            unmap(&childnode,tmp[i].value);
            //std::cout << tmp[i].value << std::endl;
            newnode.pre = pare;
            newnode.next = node.next;
            node.next = newPointer;
            newnode.isleaf = false;
            unmap(&node,pare);
            unmap(&newnode,newPointer);
           // unmap(&left,p);
           // unmap(&right,newp);
            delete [] node.children;
            delete [] tmp;
            delete [] childnode.children;
            delete [] newnode.children;
            //delete [] left.children;
            //delete [] right.children;
            return newPointer;

        }
        off_t SplitNode(const off_t pointer,const key_t key,const value_t value){
            node_t node,newNode;
            node.children = new record_t [meta.order+1];
            map(&node,pointer);
            newNode.children = new record_t [meta.order+1];
            record_t *tmp = new record_t [meta.order+3];
           // std::cout << "tmp" << tmp << std::endl;
            int i = 0,j=0;
            bool flag = false;
            while(i<meta.order){
                if(!flag&&key.cmp(key,node.children[i].key)){
                    tmp[j].key = key;
                    tmp[j].value = value;
                    j++;
                    flag = true;
                }
                else{
                    tmp[j].key = node.children[i].key;
                    tmp[j].value = node.children[i].value;
                    j++;
                    i++;
                }
            }
            if(flag == false){
                tmp[j].key = key;
                tmp[j].value = value;
            }
            int n = 0;
            n = (meta.order+1)/2;
            if((meta.order+1)%2)
                n++;
            node.n = n;
            newNode.n = meta.order + 1 - n;
            //newNode.children[n+1].value = node.children[meta.order].value;
            for(i = 0;i<n;i++){
                node.children[i].key = tmp[i].key;
                node.children[i].value = tmp[i].value;
                //std::cout << node.children[i].key.k << std::endl;
            }
            for(j = 0;i<meta.order+1;i++,j++){
                newNode.children[j].key = tmp[i].key;
                newNode.children[j].value = tmp[i].value;
                //std::cout << newNode.children[j].key.k << std::endl;
            }
            off_t newPointer = AllocStorage();
            newNode.pre = pointer;
            newNode.next = node.next;
            node.next = newPointer;
            //newNode.children[newNode.n].value = node.next;
            newNode.isleaf = true;
            newNode.parent = node.parent;
           // node.children[newNode.n].value = newPointer;
            unmap(&node,pointer);
            unmap(&newNode,newPointer);
            delete [] tmp;
            delete [] newNode.children;
            delete [] node.children;
            return newPointer;
        }
        void InsertInInternalNode(const off_t &pare,const off_t &p,const key_t &key,const off_t &newp){
            node_t parenode;
            parenode.children = new record_t [meta.order+1];
            map(&parenode,pare);
            int i;
            for(i = 0;i<=parenode.n;i++)
                if(parenode.children[i].value == p)
                    break;
            int j = 0;
            //i++;
            for(j = parenode.n;j>i;j--)
                parenode.children[j].key = parenode.children[j-1].key;
            parenode.children[j].key = key;
            i++;
            for(j = parenode.n+1;j>i;j--)
                parenode.children[j].value = parenode.children[j-1].value;
            parenode.children[j].value = newp;
            /*
            for(j = parenode.n;j>i;j--){
                parenode.children[j].value = parenode.children[j-1].value;
                parenode.children[j-1].key = parenode.children[j-2].key;
            }
            parenode.children[i].value = newp;
            parenode.children[i-1].key = key;
            */
            parenode.n++;
          //  std::cout << "Internalnode has " << parenode.n << std::endl;
            unmap(&parenode, pare);
            delete [] parenode.children;
        }
        void InsertInParent(off_t p,key_t &key,off_t newp){
            node_t pnode,newpnode;
            pnode.children = new record_t [meta.order+1];
           // std::cout << "parent1" << pnode.children << std::endl;
            newpnode.children = new record_t [meta.order+1];
           // std::cout << "parent2" << newpnode.children << std::endl;
            map(&pnode,p);
            map(&newpnode,newp);
            if(p == meta.rootOffset){
                node_t newroot;
                newroot.children = new record_t [meta.order+1];
                newroot.n = 1;
                newroot.parent = newroot.pre = newroot.next = -1;
                newroot.children[0].key = key;
                newroot.children[0].value = p;
                newroot.children[1].value = newp;
                off_t newrootpointer = AllocStorage();
                pnode.parent = newrootpointer;
                newpnode.parent = newrootpointer;
                newroot.isleaf = false;
                meta.rootOffset = newrootpointer;
                unmap(&pnode,p);
                unmap(&newpnode,newp);
                unmap(&newroot,newrootpointer);
                //unmap(&meta,pos,sizeof(meta));
                unmap(pos);
                //free(pnode.children);
                delete [] pnode.children;
                //free(newpnode.children);
                //free(newroot.children);
                delete [] newpnode.children;
                delete [] newroot.children;
                return ;
            }
            off_t pare = pnode.parent;
            node_t parenode;
            parenode.children = new record_t [meta.order+1];
         //   std::cout << "parent3" << parenode.children << std::endl;
            map(&parenode,pare);
            if(parenode.n<meta.order){
                //InsertInLeaf(pare,newpnode.children[0].key,p);
                newpnode.parent = pare;
                pnode.next = newp;
                newpnode.pre = p;
                unmap(&newpnode, newp);
                unmap(&pnode, p);
                delete [] pnode.children;
                //delete [] newpnode.children;
                delete [] parenode.children;
                InsertInInternalNode(pare,p,key,newp);
                map(&newpnode,pare);
                delete [] newpnode.children;
            }
            else {
                key_t mkey;
                key_t orignkey = newpnode.children[0].key;
                delete [] pnode.children;
                delete [] newpnode.children;
                delete [] parenode.children;
                //off_t newpare = SplitNode(pare,newpnode.children[0].key,p);
                off_t newpare = SplitInternalNode(pare,p,key,newp,mkey);
                node_t newparenode;
                newparenode.children = new record_t [meta.order+1];
                map(&newparenode,newpare);
                newparenode.isleaf = false;
                unmap(&newparenode, newpare);
                //map(&newpnode,newp);
                delete [] newparenode.children;
                InsertInParent(pare,mkey,newpare);
            }
        }
        void deleteNode(const value_t &p,const key_t &key,const value_t &target){
            node_t node;
            node.children = new record_t [meta.order+1];
            map(&node,p);
            int i;
            for(i = 0;i<node.n;i++)
                if(node.children[i].key == key)
                    break;
            while(i<node.n){
                node.children[i].key = node.children[i+1].key;
                i++;
            }
            for(i = 0;i<=node.n;i++)
                if(node.children[i].value == target)
                    break;
            while(i<= node.n){
                node.children[i].value = node.children[i+1].value;
                i++;
            }
            node.n--;
            unmap(&node, p);
            delete [] node.children;
        }
        void UnallocStorage(const value_t &p){
            ;
        }
        key_t FindCommonKey(const value_t &pare,const value_t &p){
            node_t node;
            node.children = new record_t [meta.order+1];
            map(&node,pare);
            key_t result;
            for(int i = 0;i<node.n;i++)
                if(node.children[i].value == p){
                    result = node.children[i].key;
                    break;
                }
            delete [] node.children;
            return result;
        }
        bool deleteEntry(const value_t &p,const key_t &key,const value_t &target){
            deleteNode(p,key,target);
            node_t node;
            node.children = new record_t [meta.order+1];
            map(&node,p);
            if(meta.rootOffset == p){
                if(node.isleaf){
                    delete [] node.children;
                    return true;
                }
                else if(node.n == 0){
                    meta.rootOffset = node.children[0].value;
                    UnallocStorage(p);
                    //unmap(&meta,pos,sizeof(meta));
                    unmap(pos);
                    delete [] node.children;
                    return true;
                }
                else {
                    delete []  node.children;
                    return true;
                }
            }
            int pointerSize,keySize;
            int pointerLowbound,keyLowbound;
            pointerSize = meta.order+1;
            keySize = meta.order;
            if(pointerSize%2)
                pointerLowbound = pointerSize/2 + 1;
            else pointerLowbound = pointerSize/2;
            if(keySize%2)
                keyLowbound = keySize/2 + 1;
            else keyLowbound = keySize/2;
            if((node.isleaf&&node.n<keyLowbound)||(!node.isleaf&&node.n+1<pointerLowbound)){
                bool isPre = false;
                off_t sibling = -1;
                if(node.pre!=-1){
                    isPre = true;
                    sibling = node.pre;
                }
                else if(node.next!=-1){
                    sibling = node.next;
                }
                if(sibling == -1){
                    delete [] node.children;
                    return false;
                }
                key_t nkey;
                if(isPre)
                    nkey = FindCommonKey(node.parent,sibling);
                else nkey = FindCommonKey(node.parent,p);
                node_t siblingnode;
                siblingnode.children = new record_t [meta.order+1];
                map(&siblingnode,sibling);
                if((node.isleaf&&siblingnode.n+node.n<=meta.order)
                   ||(!node.isleaf&&siblingnode.n+node.n+1<=meta.order)){
                    if(!isPre)
                        SwapNode(node,p,siblingnode,sibling);
                    if(!node.isleaf)
                        AppendInternalNode(sibling,siblingnode,nkey,node);
                    else AppendLeafNode(siblingnode,nkey,node);
                    if(isPre)
                        siblingnode.next = node.next;
                    else siblingnode.pre = node.pre;
                    unmap(&siblingnode, sibling);
                    unmap(&node,p);
                    UnallocStorage(p);
                    delete [] siblingnode.children;
                    delete [] node.children;
                    deleteEntry(node.parent, nkey, p);
                }
                else {
                    if(isPre){
                        if(!node.isleaf){
                            value_t lastvalue = siblingnode.children[siblingnode.n].value;
                            siblingnode.n--;
                            key_t pkey = siblingnode.children[siblingnode.n-1].key;
                            InsertFromHead(node,nkey,lastvalue);
                            ReplaceKey(node.parent,nkey,pkey);
                        }
                        else {
                            value_t lastvalue = siblingnode.children[siblingnode.n-1].value;
                            key_t lastkey = siblingnode.children[siblingnode.n-1].key;
                            siblingnode.n--;
                            InsertFromHead(node, lastkey, lastvalue);
                            ReplaceKey(node.parent, nkey, lastkey);
                        }
                    }
                    else {
                        if(!node.isleaf){
                            value_t firstvalue = siblingnode.children[0].value;
                            key_t firstkey = siblingnode.children[0].key;
                            RemoveFromHead(siblingnode);
                            InsertFromTail(node,nkey,firstvalue);
                            ReplaceKey(node.parent, nkey, firstkey);
                        }
                        else {
                            value_t firstvalue = siblingnode.children[0].value;
                            key_t firstkey = siblingnode.children[0].key;
                            RemoveFromHead(siblingnode);
                            node.children[node.n].key = firstkey;
                            node.children[node.n].value = firstvalue;
                            node.n++;
                            ReplaceKey(node.parent, firstkey, siblingnode.children[0].key);
                        }
                    }
                    unmap(&node,p);
                    unmap(&siblingnode,sibling);
                    delete [] siblingnode.children;
                    delete [] node.children;
                }
            }
            else {
                delete [] node.children;
            }
            return true;
        }
        void RemoveFromHead(node_t &node){
            for(int i = 1;i<=node.n;i++){
                node.children[i-1].key = node.children[i].key;
                node.children[i-1].value = node.children[i].value;
            }
            node.n--;
        }
        void InsertFromTail(node_t &node,const key_t &key,const value_t &value){
            node.children[node.n].key = key;
            node.children[node.n+1].value = value;
            node.n++;
        }
        void ReplaceKey(const value_t &p,const key_t &oldkey,const key_t &newkey){
            node_t node;
            node.children = new record_t [meta.order+1];
            map(&node,p);
            for(int i = 0;i<node.n;i++)
                if(node.children[i].key == oldkey){
                    node.children[i].key = newkey;
                    break;
                }
            unmap(&node, p);
            delete [] node.children;
        }
        void InsertFromHead(node_t &node,const key_t &key,const value_t &value){
            for(int i = node.n+1;i>0;i++){
                node.children[i].key = node.children[i-1].key;
                node.children[i].value = node.children[i-1].value;
            }
            node.children[0].key = key;
            node.children[0].value = value;
            node.n++;
        }
        void AppendLeafNode(node_t &node,const key_t &key,const node_t appnode){
            int i = node.n;
            int j = 0;
            for(j = 0;j<appnode.n;i++,j++){
                node.children[i].key = appnode.children[j].key;
                node.children[i].value = appnode.children[j].value;
            }
            node.n += appnode.n;
        }
        void AppendInternalNode(const value_t &p,node_t &node,const key_t &key,const node_t appnode){
            node_t childnode;
            childnode.children = new record_t [meta.order+1];
            int i = node.n+1,j = 0;
            while(j<=appnode.n){
                node.children[i].value = appnode.children[j].value;
                map(&childnode,node.children[i].value);
                childnode.parent = p;
                unmap(&childnode,node.children[i].value);
                i++;
                j++;
            }
            delete [] childnode.children;
            i = node.n;
            j = 0;
            node.children[i].key = key;
            i++;
            while(j<appnode.n){
                node.children[i].key = appnode.children[j].key;
                i++;
                j++;
            }
            node.n += appnode.n + 1;
        }
        void SwapNode(node_t &anode,const value_t &pa,node_t &bnode,const value_t &pb){
            record_t *tmp = new record_t[meta.order+2];
            node_t childnode;
            childnode.children = new record_t [meta.order+1];
            for(int i = 0;i<=anode.n;i++){
                tmp[i].key = anode.children[i].key;
                tmp[i].value = anode.children[i].value;
            }
            for(int i = 0;i<=bnode.n;i++){
                anode.children[i].key = bnode.children[i].key;
                anode.children[i].value = bnode.children[i].value;
                if(!anode.isleaf){
                    map(&childnode,anode.children[i].value);
                    childnode.parent = pa;
                    unmap(&childnode, anode.children[i].value);
                }
            }
            for(int i = 0;i<=anode.n;i++){
                bnode.children[i].key = tmp[i].key;
                bnode.children[i].value = tmp[i].value;
                if(!bnode.isleaf){
                    map(&childnode,bnode.children[i].value);
                    childnode.parent = pb;
                    unmap(&childnode, bnode.children[i].value);
                }
            }
            size_t t = anode.n;
            anode.n = bnode.n;
            bnode.n = t;
            delete [] childnode.children;
            delete [] tmp;
        }
    public:
        off_t pos;
        /*
        bool map(meta_t *block,off_t offset,size_t size){
            Openfile();
            fseek(fp,offset,SEEK_SET);
            size_t rd = fread(block,size,1,fp);
            Closefile();
            if(rd!=1)
                return false;
            else return true;
        }
        bool unmap(meta_t *block,off_t offset,size_t size){
            Openfile();
            fseek(fp,offset,SEEK_SET);
            size_t wd = fwrite(block,size,1,fp);
            Closefile();
            if(wd == 1)
                return true;
            else return false;
        }
         */

        /*
        off_t AllocMeta(){
            size_t used;
            Openfile();
            fread(&used, sizeof(size_t), 1, fp);
            size_t size = sizeof(meta);
            size_t tmp = used;
            used += size;
            if(used <BLOCKSIZE){
                fwrite(&used, sizeof(size), 1, fp);
            }
        }
*/
        bool remove(const key_t &key){
            off_t p = SearchNode(meta.rootOffset, key);
            node_t node;
            node.children = new record_t [meta.order+1];
            map(&node,p);
            off_t target;
            int i;
            for(i = 0;i<node.n;i++)
                if(node.children[i].key == key)
                    break;
            if(i == node.n){
                delete [] node.children;
                return false;
            }
            else {
                target = node.children[i].value;
                return deleteEntry(p,key,target);
            }
        }
        void insert(const key_t &key,value_t &value){
            if(meta.rootOffset == -1){
                node_t root;
                root.children = new record_t[meta.order+1];
                root.n = 1;
                root.parent = root.pre = root.next = -1;
                root.children[0].value = value;
                root.children[0].key = key;
                root.isleaf = true;
                meta.rootOffset = AllocStorage();
                meta.leafOffset = meta.rootOffset;
                unmap(&root,meta.rootOffset);
                //unmap(&meta,pos,sizeof(meta));
                unmap(pos);
                delete [] root.children;
                return ;
            }
            off_t p = SearchNode(meta.rootOffset,key);
            node_t node;
            node.children = new record_t[meta.order+1];
            //std::cout << "insert:" <<node.children << std::endl;
            map(&node,p);
            if(node.n<meta.order){
               delete [] node.children;
                InsertInLeaf(p,key,value);
            }
            else {
                delete [] node.children;
                off_t newp = SplitNode(p,key,value);
                node_t newpnode;
                newpnode.children = new record_t [meta.order+1];
                map(&newpnode,newp);
                key_t mkey = newpnode.children[0].key;
                delete [] newpnode.children;
                InsertInParent(p,mkey,newp);
                //std::cout << newpnode.parent << std::endl;
            }
        };
        bool update(const key_t &key,value_t &value);
        void GetKeyAndValueSize(size_t keySize,size_t valueSize){
            meta.keySize = keySize;
            meta.valueSize = valueSize;
            meta.order = (BLOCKSIZE - 3*sizeof(off_t) - sizeof(size_t) - sizeof(bool))/(meta.keySize+meta.valueSize)-1;
        }
        //must use after GetKeyAndValueSize()
        void setOrder(size_t order){
            meta.order = order;
        }
        void BuildNewTree(off_t pos,size_t size){
            //meta.height = 1;
            //meta.slot = OFFSET_META + sizeof(meta);
            meta.rootOffset = -1;
            meta.leafOffset = -1;
            meta.keySize = size;
            meta.valueSize = sizeof(value_t);
            meta.order = (BLOCKSIZE - 3*sizeof(off_t) - sizeof(size_t) - sizeof(bool) - sizeof(record_t *))/(meta.keySize+meta.valueSize) - 1;
            //meta.valueSize = sizeof(record_t)*(meta.order+1);
            //unmap(&meta,pos,sizeof(meta));
            unmap(pos);
        }
        BplusTree(off_t pos = 0,bool newTree = false){
            if(!newTree){
                //map(&meta,pos,sizeof(meta));
                map(pos);
            }
           //else Openfile("w+");
            this->pos = pos;
        }
        void printAllLeaf(){
            off_t next = meta.leafOffset;
            while(next!=-1){
                node_t node;
                node.children = new record_t [meta.order+1];
                map(&node,next);
                next = node.next;
                for(int i = 0;i<node.n;i++)
                    std::cout << node.children[i].value << " ";
                //std::cout << std::endl;
                delete [] node.children;
            }
            std::cout << std::endl;
        }
        bool search(const key_t &key,value_t &value){
            if(meta.rootOffset == (off_t)-1)
                return false;
            off_t p = SearchNode(meta.rootOffset, key);
            if(p == (off_t)-1)
                return false;
            node_t node;
            node.children = new record_t [meta.order+1];
            map(&node,p);
            int i;
            for(i = 0;i<node.n;i++)
                if(node.children[i].key == key)
                   break;
            if(i<node.n)
            {
                value = node.children[i].value;
                delete [] node.children;
                return true;
            }
            if(node.next!=-1){
                node_t nextnode;
                nextnode.children = new record_t[meta.order+1];
                map(&nextnode,node.next);
                if(nextnode.n>=1&&nextnode.children[0].key == key){
                    value = nextnode.children[0].value;
                    delete [] node.children;
                    delete [] nextnode.children;
                    return true;
                }
                delete [] nextnode.children;
            }
            delete [] node.children;
            return false;
        }
        int searchrange(const key_t minkey,const key_t maxkey,std::vector<value_t> &result){
            //int n = 0;
            off_t p = SearchNode(meta.rootOffset, minkey);
            node_t node;
            node.children = new record_t [meta.order+2];
            map(&node,p);
            off_t next = p;
            while(next!=-1){
                next = node.next;
                int i;
                for(i = 0;i<node.n;i++)
                    if(node.children[i].key>=minkey&&node.children[i].key<=maxkey){
                        result.push_back(node.children[i].value);
                    }
                    else if(node.children[i].key>maxkey){
                        break;
                    }
                if(i<node.n)
                    break;
                map(&node,next);
            }
            delete [] node.children;
            return result.size();
        }
        void levelorder(){
            off_t next = meta.rootOffset;
            std::queue<off_t> q;
            q.push(next);
            node_t node;
            node.children = new record_t [meta.order+1];
            std::cout << "Start Levelorder" << std::endl;
            while(q.size()){
                off_t next = q.front();
                q.pop();
                map(&node,next);
                if(!node.isleaf){
                    for(int i = 0;i<=node.n;i++)
                        q.push(node.children[i].value);
                }
                for(int i = 0;i<node.n;i++)
                    std::cout << node.children[i].key.k << ' ';
                std::cout << std::endl;
            }
            delete [] node.children;
            std::cout << "End levelorder" << std::endl;
        }
        /*
        void printTree(){
            off_t next = meta.rootOffset;
            std::queue<key_t> q;
            while(!q.empty()){
                key_t
                std::cout <<
            }
        }*/
        ~BplusTree(){
            //unmap(&meta, pos, sizeof(meta));
            unmap(pos);
        }
        template <typename T> void Read(int index,int &offset,T &ele);
        template <typename T> void Write(int index,int &offset,T &ele);
        /*
        static void InitFromEmpty(){
            Openfile();
            mem.freeblock = mem.endblock = -1;
            fseek(fp, 0,SEEK_SET);
            fread(&mem, sizeof(mem), 1, fp);
        }
        static void InitFromFile(){
            Openfile();
            fseek(fp, 0, SEEK_SET);
            fread(&mem, sizeof(mem), 1, fp);
        }*/
    };
    template <> template<>
    void BplusTree<String>::Read<String>(int index,int &offset,String &ele){
        if(ele.value)
            delete ele.value;
        ele.size = meta.keySize - sizeof(size_t);
        ele.value = new char[ele.size];
        //fread(ele.value,sizeof(char)*ele.size,1,fp);
        //fread(&ele.size,sizeof(size_t),1,fp);
        bm->constReadBuffer(filepath, index, ele.value, offset, sizeof(char)*ele.size);
        offset += sizeof(char)*ele.size;
        bm->constReadBuffer(filepath, index, &ele.size, offset, sizeof(size_t));
        offset += sizeof(size_t);
        if(ele.size!=meta.keySize - sizeof(size_t))
            ele.size = meta.keySize - sizeof(size_t);
    }
    template<> template<>
    void BplusTree<String>::Write<String>(int index,int &offset,String &ele){
        ele.size = meta.keySize - sizeof(size_t);
        if(ele.value){
            //fwrite(ele.value,sizeof(char)*ele.size,1,fp);
            bm->writeBuffer(filepath, index, ele.value, offset, sizeof(char)*ele.size);
        }
        offset += sizeof(char)*ele.size;
        //else fseek(fp, sizeof(char)*ele.size, SEEK_CUR);
        //fwrite(&ele.size,sizeof(size_t),1,fp);
        bm->writeBuffer(filepath, index, &ele.size, offset, sizeof(size_t));
        offset += sizeof(size_t);
    }
    template<> template<>
    void BplusTree<Integer>::Write<Integer>(int index,int &offset,Integer &ele){
        //fwrite(&ele.value,sizeof(Integer), 1, fp);
        bm->writeBuffer(filepath, index, &ele.value, offset, sizeof(Integer));
        offset += sizeof(Integer);
    }
    template<> template<>
    void BplusTree<Integer>::Read<Integer>(int index,int &offset,Integer &ele){
        //fread(&ele.value,sizeof(Integer),1,fp);
        bm->constReadBuffer(filepath, index, &ele.value, offset, sizeof(Integer));
        offset += sizeof(Integer);
    }
    template<> template<>
    void BplusTree<Float>::Read<Float>(int index,int &offset,Float &ele){
        //fread(&ele.value,sizeof(Float),1,fp);
        bm->constReadBuffer(filepath, index, &(ele.value), offset, sizeof(Float));
        offset += sizeof(Float);
    }
    template<> template<>
    void BplusTree<Float>::Write(int index,int &offset,Float &ele){
        //fwrite(&ele.value,sizeof(Float),1,fp);
        bm->writeBuffer(filepath, index, &ele.value, offset, sizeof(Float));
        offset += sizeof(Float);
    }
}

#endif
