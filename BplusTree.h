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
namespace bpt {
#define FILENAME 512
#define OFFSET_META 0
#define BLOCKSIZE 4096
#define value_t off_t
#define NODESIZE (sizeof(node_t) - 2*sizeof(struct record_t*) + (meta.order+1)*sizeof(struct record_t)) + 4
    struct meta_t{
        size_t order;
        size_t valueSize;
        size_t keySize;
        //size_t internalNodeNum;
        //size_t leafNodeNum;
        size_t height;
        off_t slot;
        off_t rootOffset;
        off_t leafOffset;
    };
    template<typename key_t>
    class BplusTree{
    private:
        meta_t meta;
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
        char filepath[FILENAME] = "/Users/andyyang/Desktop/BplusTree/BplusTree/1.in";
        FILE *fp;
        int fp_level;
        void Openfile(const char *mode="rb+"){
            if(fp_level == 0)
                fp = fopen(filepath,mode);
            fp_level++;
        }
        void Closefile(){
            if(fp_level == 1)
                fclose(fp);
            fp_level--;
        }
        bool map(meta_t *block,off_t offset,size_t size){
            Openfile();
            fseek(fp,offset,SEEK_SET);
            size_t rd = fread(block,size,1,fp);
            Closefile();
            if(rd!=1)
                return false;
            else return true;
        }
        bool map(node_t *node,off_t offset){
            Openfile();
            fseek(fp,offset,SEEK_SET);
            size_t rd = fread(&(node->parent),sizeof(node->parent),1,fp);
            rd += fread(&(node->pre),sizeof(node->pre),1,fp);
            rd += fread(&(node->next),sizeof(node->next),1,fp);
            rd += fread(&(node->n),sizeof(node->n),1,fp);
            rd += fread(&(node->isleaf),sizeof(node->isleaf),1,fp);
            rd += fread(node->children,sizeof(*node->children)*(meta.order+1),1,fp);
            Closefile();
            //for(int i = 0;i<node->n;i++)
              //  std::cout << node->children[i].key.k << std::endl;
            if(rd == 6)
                return true;
            else return false;
        }
        off_t AllocStorage(size_t size){
            off_t slot = meta.slot;
            meta.slot += size;
            return slot;
        }
        off_t AllocStorage(node_t &node){
            //node.n = 1;
            //meta.internalNodeNum++;
            //return AllocStorage(sizeof(node));
            off_t slot = meta.slot;
            meta.slot += NODESIZE;//needed changed
            return slot;
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
        bool unmap(node_t *node,off_t offset){
            Openfile();
            fseek(fp,offset,SEEK_SET);
            size_t wd = fwrite(&(node->parent),sizeof(node->parent),1,fp);
            wd += fwrite(&(node->pre),sizeof(node->pre),1,fp);
            wd += fwrite(&(node->next),sizeof(node->next),1,fp);
            wd += fwrite(&(node->n),sizeof(node->n),1,fp);
            wd += fwrite(&(node->isleaf),sizeof(node->isleaf),1,fp);
            wd += fwrite(node->children,sizeof(*node->children)*(meta.order+1),1,fp);
            Closefile();
            //Openfile();
            //fseek(fp,offset,SEEK_SET);
            //off_t parent;
            //fread(&parent, sizeof(off_t), 1, fp);
            //std::cout << parent << std::endl;
            //Closefile();
            if(wd == 6)
                return true;
            else return false;
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
            off_t newPointer = AllocStorage(newnode);
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
            off_t newPointer = AllocStorage(newNode);
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
        void InsertInParent(off_t p,key_t key,off_t newp){
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
                off_t newrootpointer = AllocStorage(newroot);
                pnode.parent = newrootpointer;
                newpnode.parent = newrootpointer;
                newroot.isleaf = false;
                meta.rootOffset = newrootpointer;
                unmap(&pnode,p);
                unmap(&newpnode,newp);
                unmap(&newroot,newrootpointer);
                unmap(&meta,OFFSET_META,sizeof(meta));
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
    public:
        bool remove(const key_t &key);
        void insert(const key_t &key,value_t &value){
            if(meta.rootOffset == -1){
                node_t root;
                root.children = new record_t[meta.order+1];
                root.n = 1;
                root.parent = root.pre = root.next = -1;
                root.children[0].value = value;
                root.children[0].key = key;
                root.isleaf = true;
                meta.rootOffset = AllocStorage(root);
                meta.leafOffset = meta.rootOffset;
                unmap(&root,meta.rootOffset);
                unmap(&meta,OFFSET_META,sizeof(meta));
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
        void BuildNewTree(){
            meta.height = 1;
            meta.slot = OFFSET_META + sizeof(meta);
            meta.rootOffset = -1;
            meta.valueSize = sizeof(record_t)*(meta.order+1);
            unmap(&meta,OFFSET_META,sizeof(meta));
        }
        BplusTree(bool newTree = true):fp(NULL),fp_level(0){
           if(!newTree)
                map(&meta,OFFSET_META,sizeof(meta));
           else Openfile("w+");
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
            off_t p = SearchNode(meta.rootOffset, key);
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
        /*
        void printTree(){
            off_t next = meta.rootOffset;
            std::queue<key_t> q;
            while(!q.empty()){
                key_t
                std::cout <<
            }
        }*/
    };
}

#endif
