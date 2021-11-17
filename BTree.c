//Name: Pragat Sharma
//Entry no:2020csb1109
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<unistd.h>
struct BTree {
   int *d;//Here d is array of keys
   struct BTree **child_ptr;//This is array of child pointers
   bool l;//Is true when node is leaf. Otherwise false
   int n;// Current number of keys
}*r = NULL, *np = NULL, *x = NULL;//r is root
struct BTree* B_TREE_CREATE(int t) {
   int i;
   np =  (struct BTree*)malloc(sizeof(struct BTree));
    // Allocate memory for maximum number of possible keys
    // and child pointers
   np->d = (int*)malloc((2*t-1)*sizeof(int));//minimum
   np->child_ptr = (struct BTree**)malloc((2*t)*sizeof(struct BTree*));
   np->l = true;
   np->n = 0;
   for (i = 0; i < 7; i++) {
      np->child_ptr[i] = NULL;
   }
   return np;
}
int B_TREE_SPLIT_CHILD(struct BTree *x, int i,int t) {
   int j, mid;
   struct BTree *np1, *np3, *y;
   np3 = B_TREE_CREATE(t);//create new node
   np3->l = true;
   if (i == -1) {
      mid = x->d[t-1];//find mid
      x->d[t-1] = 0;
      x->n--;
      np1 = B_TREE_CREATE(t);
      np1->l= false;
      x->l= true;
      for (j = t; j < (2*t); j++) {
         np3->d[j - t] = x->d[j];
         np3->child_ptr[j - t] = x->child_ptr[j];
         np3->n++;
         x->d[j] = 0;
         x->n--;
      }
      for (j = 0; j < t; j++) {
         x->child_ptr[j] = NULL;
      }
      np1->d[0] = mid;
      np1->child_ptr[np1->n] = x;
      np1->child_ptr[np1->n + 1] = np3;
      np1->n++;
      r = np1;
   } else {
      y = x->child_ptr[i];
      mid = y->d[t-1];
      y->d[t-1] = 0;
      y->n--;
      for (j = t; j <(2*t) ; j++) {
         np3->d[j - t] = y->d[j];
         np3->n++;
         y->d[j] = 0;
         y->n--;
      }
      x->child_ptr[i + 1] = y;
      x->child_ptr[i + 1] = np3;
   }
   return mid;
}
void B_TREE_INSERT_NONFULL(struct BTree *p,int k,int t){
    int i=p->n;
    if(p->l){
        while(i>=1 && k<(p->d[i])){
            p->d[i+1]=p->d[i];
            i=i-1;
        }
    p->d[i+1]=k;
    p->n++;
    }
    else{
        while(i>=1 && k<(p->d[i])){
            i=i-1;
        }
    i=i+1;
    }
    if((p->child_ptr[i])->n==(2*t-1)){
        B_TREE_SPLIT_CHILD(p,i,t);
        if(k>p->d[i]){
            i=i+1;
        }
    B_TREE_INSERT_NONFULL(p->child_ptr[i],k,t);
    }

}
//Inorder traversal
void B_TREE_INORDER_TRAVERSE(struct BTree *p) {
   printf("");
   int i;
   for (i = 0; i < p->n; i++) {
      if (p->l == false) {
         B_TREE_INORDER_TRAVERSE(p->child_ptr[i]);
      }
      printf("%d ",p->d[i]);
   }
   if (p->l == false) {
      B_TREE_INORDER_TRAVERSE(p->child_ptr[i]);
   }
   printf("");
}
void sort(int *p, int n) {
   int i, j, t;
   for (i = 0; i < n; i++) {
      for (j = i; j <= n; j++) {
         if (p[i] >p[j]) {
            t = p[i];
            p[i] = p[j];
            p[j] = t;
         }
      }
   }
}
//Function for inserting
void B_TREE_INSERT(int a,int t) {
   int i, s;
   x = r;
   if (x == NULL) {
      r = B_TREE_CREATE(t);
      x = r;
   } else {
    if (x->l== true && x->n == (2*t)) {
         s = B_TREE_SPLIT_CHILD(x, -1,t);
         x = r;
         for (i = 0; i < (x->n); i++) {
            if ((a >x->d[i]) && (a < x->d[i + 1])) {
               i++;
               break;
            } else if (a < x->d[0]) {
               break;
            } else {
               continue;
            }
         }
         x = x->child_ptr[i];
         } else {
         while (x->l == false) {
            for (i = 0; i < (x->n); i++) {
               if ((a >x->d[i]) && (a < x->d[i + 1])) {
                  i++;
                  break;
               } else if (a < x->d[0]) {
                  break;
               } else {
                  continue;
               }
            }
            if ((x->child_ptr[i])->n == (2*t)) {
               s = B_TREE_SPLIT_CHILD(x, i,t);
               x->d[x->n] = s;
               x->n++;
               continue;
            } else {
               x = x->child_ptr[i];
            }
         }
      }
    }
   x->d[x->n] = a;
   sort(x->d, x->n);
   x->n++;
}
//function for searching
struct BTree *B_TREE_SEARCH(struct BTree *p,int k){
    int i=0;
    while(i<(p->n) && k>(p->d[i])){
        i=i+1;
    }
    if(k==p->d[i]){
        return p;
    }
    else if(p->l){
        return NULL;
    }

        return B_TREE_SEARCH(p->child_ptr[i],k);
    }
//function for finding minimum
int B_TREE_MIN(struct BTree **r){
    struct BTree *p=NULL;
    p=*r;

    int min=p->d[0];//min element initialized to first key in btree
   if(p->child_ptr[0]!=NULL){
       do{
           min=p->child_ptr[0]->d[0];//traverse through the child node and their keys till minimum is found
           p=p->child_ptr[0];
       }while(!(p->l));
   }
    return min;
}
int main() {
   int i, n, t,m,search;
   char s;
   char str[101]="Options: I for insertion, S for search, M for finding minimum, T for traversal of B-Tree, E for exit:";
   printf("Enter the minimum degree of the B-Tree t:");
   scanf("%d",&m);
   printf("Enter A or B:");
   scanf(" %c",&s);
   if(s=='A'){
    int f;
   for(i = 1; i<=100 ; i++) {
     B_TREE_INSERT(i,101);
   }
   printf("Traversal of constructed B tree\n");
   B_TREE_INORDER_TRAVERSE(r);
   printf("\n");
   printf("Enter a number to search:");
   scanf("%d",&f);

    if(B_TREE_SEARCH(r,f)){
        printf("Element is present\n");
        }
    else{printf("Element is not present\n");}
       }
else if(s=='B'){
char userq;
while(userq!='E'){
  printf("%s",str);
  scanf(" %c",&userq);
 if(userq=='I'){
    int size;
    printf("Enter number of elements you want to insert:");
    scanf("%d",&size);
    for(int i=0;i<size;i++){
        int p;
        printf("Insert element:");
        scanf("%d",&p);
        B_TREE_INSERT(p,m);
}}
else if(userq=='M'){
    printf("Minimum element is:");
    printf("%d",B_TREE_MIN(&r));
    printf("\n");
}
else if(userq=='T'){
    B_TREE_INORDER_TRAVERSE(r);
    printf("\n");
}
else if(userq=='S'){
    int k;
    printf("Enter element you want to search:");
    scanf("%d",&k);
    if(B_TREE_SEARCH(r,k)!=NULL){
        printf("Element is present\n");
        }
    else{printf("Element is not present\n");}
}
else if(userq=='E'){break;}
}
}}
