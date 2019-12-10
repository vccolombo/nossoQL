
#ifndef BTREE_H
#define BTREE_H
#define M 5  // Order of B-tree: M link fields in each node
#include <vector> 
#include <string>

using namespace std;

#define SUCCESS 0
#define FINISH_PROGRAM 1

#define MIN_SIZE 18
#define PONTEIRO_HEAD_SIZE 10

void removeTREE(std::string tabela, std::string campo);

typedef int dtype;
enum status {InsertNotComplete, Success, DuplicateKey,
   Underflow, NotFound};

struct node {
   int n;        // Number of items stored in a node (n < M)
   dtype k[M-1]; // Data items (only the first n in use)
   long p[M];    // 'Pointers' to other nodes (n+1 in use)
};

class Btree {
public:
   Btree();
   Btree(string TreeFileName);
   ~Btree();

   void insert(dtype x);
   void insert(string InpFileName, int x, int opcao);
   void print(){cout << "Conteudo:\n"; pr(root, 0);}
   void DelNode(dtype x);
   void ShowSearch(dtype x);



   
private:
   enum {NIL=-1};
   long root, FreeList;
   node RootNode;
   fstream file;
   status ins(long r, dtype x, dtype &y, long &u);
   void pr(long r, int nSpace);
   int NodeSearch(dtype x, const dtype *a, int n)const;
   status del(long r, dtype x);
   void ReadNode(long r, node &Node);
   void WriteNode(long r, const node &Node);
   void ReadStart();
   long GetNode();
   void FreeNode(long r);
};

#endif