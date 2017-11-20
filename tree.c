#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define TREE

typedef struct node {
    int data;
#ifdef TREE
    struct node *left;
    struct node *right;
#else
    struct node *next;
#endif
} node_t;

static int rtheight;
static int height;
static int* queue[10];
static int queue_prt[10];


int heightoftheTree(node_t * node) 
{
   if (node == NULL) {
       height--;
       return -1; /* leaf height is zero, this be below that!! */
   }
   else
   {
       height++;

       /* compute the depth of each subtree */
       int lDepth = heightoftheTree(node->left);
       int rDepth = heightoftheTree(node->right);

       /* use the larger one */
       if (lDepth > rDepth) 
           return(lDepth+1);
       else return(rDepth+1);
   }
}

int word_size(int value){
  int len=!value;
  while(value){ len++; value/=10; }
  return len;
}

#define FILLQ(row, elem, prlvl, lvl, val) row[ ((prlvl-1)+lvl) ][ elem[((prlvl-1)+lvl)]++ ] = val

int displaytree(struct node* node, int height)
{
    int level, depth;
    int i, j;

    if (node == NULL)
    return 0;

    depth = rtheight - height;
    level = depth + 1;

    if(!node->left) {
        queue_prt[level]++;
            
        if((level+1) >= depth){
            printf("**(%d), lvl:%d, depth:%d ",node->data, level, depth);
            for(i=(level+1); i<=rtheight; i++){
                for(j=(level+1); j<=i; j++){
                    printf("@");
                    queue_prt[i]++;
                    queue_prt[i]++;
                }
            }
        }
    }

    if(node->left)
    if(!node->left->left && !node->left->right){
        if((level+2) >= depth){
            printf("**(%d), lvl:%d, depth:%d ",node->data, level, depth);
            for(i=(level+1); i<=rtheight; i++){
                for(j=(level+1); j<=i; j++){
                    printf("#");
                    queue_prt[i]++;
                    queue_prt[i]++;
                }
            }
        }

        FILLQ(queue, queue_prt, level, 1, node->left->data);
        goto right;
    }

    /* first recur on left child */
    if(node->left)
    displaytree(node->left, (height-1));

right:

    /* Then fill the data of node in the buffer */
    FILLQ(queue, queue_prt, level, 0, node->data);

    if(!node->right){
        queue_prt[level]++;
            
            if((level+1) >= depth){
            for(i=(level+1); i<=rtheight; i++){
                for(j=(level+1); j<=i; j++){
                    printf("@");
                    queue_prt[i]++;
                    queue_prt[i]++;
                }
            }
        }
    }
    

    if(node->right)
    if(!node->right->left && !node->right->right) {

        if((level+2) >= depth){
            for(i=(level+1); i<=rtheight; i++){
                for(j=(level+1); j<=i; j++){
                    printf("!!");
                    queue_prt[i]++;
                    queue_prt[i]++;
                }
            }
        }

        FILLQ(queue, queue_prt, level, 1, node->right->data);
        return 0;
    }
 
    // now recur on right child 
    if(node->right)
    displaytree(node->right, (height-1));

    return 0;
}

void space(int x){
    int i;
    for(i=0;i<x;i++)
    printf(" ");
}

/*         start        space
level 1    8wd+7s       NA
level 2    4wd+3s       8wd+7s
level 3    2wd+1s       4wd+3s
level 4    1wd+0s       2wd+1s
level 5    0wd+0s       2*/

#define wd 2
#define spc 2
int printtree(struct node* root){

    int i, j, x;
    int temp;
    int pivot, lvlstart, lvlspace;

    printf("\n");
    for(i=0; i<=rtheight; i++){
        temp = pow(2,i);
        queue[i] = malloc(temp * sizeof(int));
        memset(queue[i], 0xFF, (temp * sizeof(int)));
    }

    displaytree(root, rtheight);

    pivot = pow(2,rtheight)/2;

    printf("\n");
    for(i=0 ;i<= rtheight; i++){

        printf("Level:%d ", (i+1));

        lvlstart = (pivot * wd)+ ((pivot-1) * spc);
        if(pivot)
        space(lvlstart);

        for(j=0; j<pow(2,i); j++){

            if(j){
                lvlspace = ((2 * pivot * wd) + (((2 * pivot)-1) * spc));

                if(pivot)
                space(lvlspace);
                else
                space(2);
            }

            if(queue[i][j]){
                if(queue[i][j] != 0xFFFFFFFF){
                    printf("%.2x", queue[i][j]);
                } else{
                    printf("%.2s", "..");
                }
            } else 
            printf("%.2s", "..");
        }
        pivot /= 2;
        
        for(x=i; x<= rtheight; x++)
        printf("\n");

        //printf("\n");
    }

    for(i=0; i<=rtheight; i++){
        free(queue[i]);
    }
}

node_t * newNode(int data) 
{
    node_t *root = (node_t *) malloc(sizeof(node_t));
    root->data = data;
    root->left = NULL;
    root->right = NULL;
   
    return(root);
}

void printf_inspace(int x, int val){
    switch(x){
    case 1:
        printf("%-1d ", val);
    case 2:
        printf("%-2d ", val);
    case 3:
        printf("%-3d ", val);
    case 4:
        printf("%-3d ", val);
    default:
        printf("%-3d ", val);
    }
}

int main()
{

    node_t *root = newNode(1);
 
    root->left = newNode(2);
    root->right = newNode(3);

    root->left->left = newNode(4);
    root->left->right = newNode(5); 
    root->right->left = newNode(6);
    root->right->right = newNode(7); 

    root->left->left->left = newNode(44);
    root->left->right->left = newNode(8); 
    root->left->right->right = newNode(9); 
    root->right->right->left = newNode(10); 
    root->left->left->right = newNode(11);
    root->right->right->left->left = newNode(14); 
    root->right->right->left->right = newNode(99); 
    root->right->right->left->right->right = newNode(78);

    rtheight = heightoftheTree(root);
    printf("\nroot height: %d", rtheight);

    printtree(root);

    getchar();
    return 0;
}

