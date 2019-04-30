#ifndef _ADJL
#define _ADJL
#include <iostream>
//#include "stack.h"
using namespace std;

class node{
    public:
            node(){vertex = 0; weight = 1; next = NULL;visited = false;}
            node(int value, node* ptr){//for vertex
                vertex = value;
                weight = 1;
                next = ptr;
                visited = false;
            }
            node(int value, int num, node* ptr){
                vertex = value;
                weight = num;
                next = ptr;
                visited = false;
            }
            node* getNext(){return next;}
            int getVert(){return vertex;}
            void setNext(node* val){next = val;}
          //  void setVert(int val){vertex = val;}
            int getWeight(){
                return weight;
            }
            bool getVisit(){return visited;}
            void setVisit(bool choice){ visited = choice;}

    private:
            int vertex;
            int weight;
            node* next;
            bool visited;
};

class AL {
        private:
            node** list;
            int size;
        public:
            void printSize(){ //to double check size
                cout << size << endl;
            }
            AL(){ //empty adjL
                list = NULL;
            }
            AL(int n){ //Initialize a size of pointers
                size = n;
                list = new node*[size];
                for (int i = 0;i < size; i++){
                    list[i] = NULL; //each vertex is not adjacent to any other
                }
            }
            //resize
            resize(int n){ //Initialize a size of pointers
                size = n;
                list = new node*[size];
                for (int i = 0;i < size; i++){
                    list[i] = NULL; //each vertex is not adjacent to any other
                }
            }
            //
            void markVisit(node* temp){ //for shortest paths
                if (!temp->getVisit()) temp->setVisit(true);
                else cout << "already visited\n";
            }
            void addVert(int val,int num){
               if(isFull()){cout << "full\n";
                       return;
               }
               else{
               node* temp = new node(val,NULL);
               int i = 0;

               if (list[i] == NULL) list[i] = temp;
               else{
                   while ((list[i] != NULL)&&(i < size)){
                       i++;
                   }
                   if (list[i] != NULL)cout << "not enough space\n";
                   else list[i] = temp;

               }
            }
            }
            bool isFull(){
                    bool full = true;
                for (int i = 0; i< size; i++){
                    if (list[i] == NULL) full = false;
                }
                return full;
            }
            node* getVert(int input){
                bool found = false;
                for (int i = 0; i< size; i++){
                    if (list[i]->getVert() == input) return list[i];
                }
                if (!found) cout << "vertex not found\n";
            }
            void addEdge(int vert, int u, int num){//num is for weight
                node* trav = getVert(vert);
              //  cout <<"trav vert: " << trav->getVert() << endl;
                node* temp = new node(u,num,NULL);
              //  cout <<"temp vert: " << temp->getVert() << "weight: " << temp->getWeight()<< endl;
                bool added = false;
                    while (added == false){
                        if (trav->getNext() == NULL){
                           trav->setNext(temp);
                           added = true;
                        }
                        else trav = trav->getNext();
                        }

                    if (!added) cout << "cannot add edge\n";
                }



            void biDirectionalEdge(int vert, int u, int num){
                addEdge(vert,u,num);
                addEdge(u,vert,num);
            }
            void printAdj(){
            int i = 0,j=0;
                if (list[i] != NULL){
                    node* trav = list[i];
                    while((trav != NULL)&& i<size){
                        cout <<"Vertex:" <<trav->getVert() << endl;
                        if (trav->getNext() != NULL){
                            while (trav->getNext() != NULL){
                                trav = trav->getNext();
                                cout <<"has edge: "<< trav->getVert() << endl;
                                cout << "edge weight: " << trav->getWeight() << endl;
                            }
                            i++;
                            trav = list[i];
                        }
                        else {
                            i++;
                            trav = list[i];
                        }
                    }
                }
            }

   /*         void depthWalk(node* start, node* end){
               stack depStack(size);
                    depStack.push(start->getVert());
                    start->markVisit();
                    cout << start->getVert();
                    if (start->getNext()==NULL)depStack.pop();

                    if (start->getNext()!= NULL){
                        node* trav = start->getNext();
                        while (trav->getNext()!= NULL){
                            depStack.push((trav->getVert());
                            trav->markVisit();
                            cout << trav->getVert();
                        }
                    }


            }*/

};

#endif
