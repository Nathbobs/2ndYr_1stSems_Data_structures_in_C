#include<stdio.h>
#include<stdlib.h>

FILE *fin;
FILE *fout;

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node{
   ElementType element;
   Position next;
};

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void Insert(ElementType X, List L, Position P);
Position FindPrevious(ElementType X, List L);
Position Find(ElementType X, List L);
void Delete(ElementType X, List L);
void DeleteList(List L);
int* GetElements(List L);
int ListSize=0;

int main(int argc, char **argv){
   fin=fopen(argv[1], "r");
   fout=fopen(argv[2], "w");
   char x;
   int* elements;

   Position header=NULL, tmp=NULL;
   header = MakeEmpty(header);
   while(fscanf(fin,"%c",&x)!=EOF){
      if(x=='i'){
         int a,b;   fscanf(fin,"%d%d",&a,&b);
         tmp = Find(a, header);
         if(tmp!=NULL){
            fprintf(fout, "insertion(%d) failed : the key already exists in the list\n", a);
            continue;
         }
         tmp = Find(b, header);
         if(tmp==NULL){
            fprintf(fout, "insertion(%d) failed : can not find the location to be inserted\n", a);
            continue;
         }
         Insert(a, header, tmp);
      }
      else if(x=='d'){
         int a;   fscanf(fin,"%d",&a);
         tmp = Find(a, header);
         if(tmp==NULL){
            fprintf(fout, "deletion(%d) failed : element %d is not in the list\n", a, a);
            continue;
         }
         Delete(a, header);
      }
      else if(x=='f'){
         int a;   fscanf(fin,"%d",&a);
         tmp = FindPrevious(a, header);
         if(IsLast(tmp, header)) fprintf(fout, "finding(%d) failed : element %d is not in the list\n",a,a);
         else{
            if(tmp->element>0) fprintf(fout, "key of the previous node of %d is %d\n", a, tmp->element);
            else fprintf(fout, "key of the previous node of %d is head\n",a);
         }
      }
      else if(x=='p') {
         if(IsEmpty(header))
            fprintf(fout, "empty list!\n");
         else
         {
            elements = GetElements(header);
            for(int i = 0; i < ListSize; i++){
                  fprintf(fout, "key:%d ", elements[i]);
               }
               fprintf(fout, "\n");
            free(elements);
         }
      }
   }
   DeleteList(header);
   fclose(fin);
   fclose(fout);

   return 0;
}

List MakeEmpty(List L){
    List list;
   list=(List)malloc(sizeof(struct Node));
   list->next=NULL;
   list->element=-1;
   return list;
} // making a new list called L, assigning the next value to NULL and setting element to -1 

int IsEmpty(List L){
   return L->next==NULL; // head doesn't exist yet so it is set to empty(NULL)
}

int IsLast(Position P, List L){
   return P->next==NULL; // next of p is also set to NULL(empty)
}

void Insert(ElementType X, List L, Position P){ // creating tmp and inserting it between p and p next
    Position tmp;
    tmp=(Position) malloc(sizeof(struct Node));
    tmp->element=X;
    tmp->next=P->next;
    P->next=tmp;
}

int* GetElements(List L){ // until NULL is reached, head is repeated and the next elements follows to determine the size of the list
    int m=0;
    Position p;
    p=L->next;
    while(p!=NULL){
        p=p->next;
        m++;
    }
   int *ray=(int*) malloc(sizeof(int*)*m); // using malloc of the list size, values are entered and it is returned.
   if(m==0) {
      ListSize=0;
      return ray=NULL;
   }
   p=L->next;
   m=0;
   while(p!=NULL){
      ray[m]=p->element;
      p=p->next;
      m++;
   }
   ListSize=m;
    return ray;
}

Position FindPrevious(ElementType X, List L){ // if the elements in p->nrxt is the same with X, repeat the value of p and return it. else, next till the value of NULL is reached.
    Position p;
    p=L;
    while(p->next!=NULL&&p->next->element!=X){
        p=p->next;
    }
   return p;
}

Position Find(ElementType X, List L){ // if the element of p is equals to X, repeat the value of p and return. else, next until it reaches NULL.
    Position p;
    p=L;
    while(p!=NULL&&p->element!=X){
        p=p->next;
    }
    return p;
}

void Delete(ElementType X, List L){ // Location to be deleted is specified as tmp.Then make temp free like a bird.
    Position p,tmp;
   p=FindPrevious(X,L);
    tmp=p->next;
   if(!IsLast(p,L)){   
       p->next=tmp->next;
       free(tmp);
   }
}

void DeleteList(List L){ // since tmp has been free, use it to move to the next position before you free the current position and repeat it until it is NULL
    Position p,tmp;
    p=L->next;
    L->next=NULL;
    while(p!=NULL){
        tmp=p->next;
        free(p);
        p=tmp;
    }
}