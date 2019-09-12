 /* 
  * This is a simple prgram to for Binary Search Tree,
  * with some pictorial tree presentaion, and
  * with a shell ported from "https://gist.github.com/parse/966049".
  *
  * Author: Murali Pitchai
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 
#include <sys/types.h>
#include <sys/wait.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
    int height; 
} node_t;

node_t *root = NULL;

static int rtheight;
//static int height;
static int verbosity;
static int *queue[10];
static int queue_prt[10];


/* Inorder printing of binary tree*/
void print_Inorder(node_t * node)
{
    if (node == NULL)
      return;

    /* left child */
    print_Inorder(node->left);

    /* Data printing*/
    printf("%d(%p) ", node->data, node);

    /* right child */
    print_Inorder(node->right);
}

int heightoftheTree(node_t * node) 
{
    if (node == NULL) {
       //height--;
       return -1; /* leaf height is zero, this be below that!! */
    }
    else
    {
        //height++;

        /* compute the depth of each subtree */
        int lDepth = heightoftheTree(node->left);
        int rDepth = heightoftheTree(node->right);

        /* use the larger one */
        if (lDepth > rDepth) 
        return(lDepth+1);
        else 
        return(rDepth+1);
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
            for(i=(level+1); i<=rtheight; i++){
                for(j=0; j<pow(2,(i-(level+1))); j++){
                    queue_prt[i]++;
                    queue_prt[i]++;
                }
            }
        }
    }

    if(node->left)
    if(!node->left->left && !node->left->right){
        if((level+2) >= depth){
            for(i=(level+1); i<=rtheight; i++){
                for(j=0; j<pow(2,(i-(level+1))); j++){
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
                for(j=0; j<pow(2,(i-(level+1))); j++){
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
                for(j=0; j<pow(2,(i-(level+1))); j++){
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
void printtree(struct node* rootpt){

    int i, j, x;
    int temp;
    int pivot, lvlstart, lvlspace;

    print_Inorder(rootpt);
    rtheight = heightoftheTree(rootpt);
    
    if(rtheight == -1)
        printf("No Element in the tree!!");
    else
        printf("\nroot height: %d\n===============\n", rtheight);

    printf("\n");
    for(i=0; i<=rtheight; i++){
        temp = pow(2,i);
        queue[i] = malloc(temp * sizeof(int));
        memset(queue[i], 0xFF, (temp * sizeof(int)));
    } 

    //if(verbosity == 2){
        //printf("\nRoot Inorder Traversal: ");
        //print_Inorder(rootpt);
    //}

    displaytree(rootpt, rtheight);

    /* pivot is the mid of whole tree to be printed: */
    pivot = pow(2,rtheight)/2;

    printf("\n");
    for(i=0 ;i<= rtheight; i++){

        printf("Level:%d ", (i+1));

        /* print the left empty space, to start printing the data */
        lvlstart = (pivot * wd)+ ((pivot-1) * spc);
        if(pivot)
        space(lvlstart);

        for(j=0; j<pow(2,i); j++){

            if(j){
                /* space between the printing the data */
                lvlspace = ((2 * pivot * wd) + (((2 * pivot)-1) * spc));

                if(pivot)
                space(lvlspace);
                else
                space(2);
            }

            /* print the data, and 0xFFFFFFFF is a kind of not print */
            if(queue[i][j] != 0xFFFFFFFF){
                printf("%.2d", queue[i][j]);
            } else{
                printf("%.2s", "..");
            }
        }

        /* pivot will get redcued to grow the tree */
        pivot /= 2;
        
        /* space between levels */
        for(x=i; x<= rtheight; x++)
        printf("\n");
    }

    /* clearing of all the queues for level */
    for(i=0; i<=rtheight; i++){
        free(queue[i]);
        queue_prt[i] = 0;
        queue[i] = NULL;
    }
}

node_t * newNode(int data) 
{
    node_t *root1 = (node_t *) malloc(sizeof(node_t));
    root1->data = data;
    root1->left = NULL;
    root1->right = NULL;
    root1->height = 1;
   
    return(root1);
}

node_t * minval(node_t * node)
{
    node_t * temp = node;

    if(!temp)
    return(NULL);

    if(temp->left)
    while(temp->left){
        temp = temp->left;
    }
    return(temp);
}
/*
 * #####################################################################
 * AVL:
 * Refer https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
 */

// A utility function to get height of the tree 
int height(node_t *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 

// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
node_t *rightRotate(node_t *y) 
{ 
    node_t *x = y->left; 
    node_t *T2 = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = T2; 
  
    // Update heights 
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
  
    // Return new root 
    return x; 
} 
  
// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
node_t *leftRotate(node_t *x) 
{ 
    node_t *y = x->right; 
    node_t *T2 = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = T2; 
  
    //  Update heights 
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
  
    // Return new root 
    return y; 
}

// Get Balance factor of node N 
int getBalance(node_t *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
}

node_t * AVL_insertion(node_t * node, int data) 
{ 
    /* 1.  Perform the normal BST rotation */
    if (node == NULL) 
        return(newNode(data)); 
  
    if (data < node->data) 
        node->left  = AVL_insertion(node->left, data); 
    else if (data > node->data) 
        node->right = AVL_insertion(node->right, data); 
    else // Equal datas not allowed 
        return node; 
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), 
                           height(node->right)); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance(node); 
  
    // If this node becomes unbalanced, then there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && data < node->left->data) 
        return rightRotate(node); 
  
    // Right Right Case 
    if (balance < -1 && data > node->right->data) 
        return leftRotate(node); 
  
    // Left Right Case 
    if (balance > 1 && data > node->left->data) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    // Right Left Case 
    if (balance < -1 && data < node->right->data) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    /* return the (unchanged) node pointer */
    return node; 
}

// Recursive function to delete a node with given data 
// from subtree with given root. It returns root of 
// the modified subtree. 
node_t* AVL_deletion(node_t* root, int data) 
{ 
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL) 
        return root; 
  
    // If the data to be deleted is smaller than the 
    // root's data, then it lies in left subtree 
    if ( data < root->data ) 
        root->left = AVL_deletion(root->left, data); 
  
    // If the data to be deleted is greater than the 
    // root's data, then it lies in right subtree 
    else if( data > root->data ) 
        root->right = AVL_deletion(root->right, data); 
  
    // if data is same as root's data, then This is 
    // the node to be deleted 
    else
    { 
        // node with only one child or no child 
        if( (root->left == NULL) || (root->right == NULL) ) 
        { 
            node_t *temp = root->left ? root->left : 
                                             root->right; 
  
            // No child case 
            if (temp == NULL) 
            { 
                temp = root; 
                root = NULL; 
            } 
            else // One child case 
             *root = *temp; // Copy the contents of 
                            // the non-empty child 
            free(temp); 
        } 
        else
        { 
            // node with two children: Get the inorder 
            // successor (smallest in the right subtree) 
            node_t* temp = minval(root->right); 
  
            // Copy the inorder successor's data to this node 
            root->data = temp->data; 
  
            // Delete the inorder successor 
            root->right = AVL_deletion(root->right, temp->data); 
        } 
    } 
  
    // If the tree had only one node then return 
    if (root == NULL) 
      return root; 

   // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
    root->height = 1 + max(height(root->left), 
                           height(root->right)); 
  
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
    // check whether this node became unbalanced) 
    int balance = getBalance(root); 
  
    // If this node becomes unbalanced, then there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && getBalance(root->left) >= 0) 
        return rightRotate(root); 
  
    // Left Right Case 
    if (balance > 1 && getBalance(root->left) < 0) 
    { 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
  
    // Right Right Case 
    if (balance < -1 && getBalance(root->right) <= 0) 
        return leftRotate(root); 
  
    // Right Left Case 
    if (balance < -1 && getBalance(root->right) > 0) 
    { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 
  
    return root; 
}

/*
 * #####################################################################
 * BST:
 * Refer https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
 */
node_t * BST_insertion(node_t * node, int value) 
{
    if(node == NULL){
        node = newNode(value);
    }
    else if(value < node->data){
        node->left = BST_insertion(node->left, value);
    }
    else if(value > node->data){
        node->right = BST_insertion(node->right, value);
    }

    return(node);
}
node_t* BST_deletion(node_t* node, int data)
{
    // base case
    if(node == NULL)
    return node;
 
    // If the data to be deleted is smaller than the node's data,
    // then it lies in left subtree
    if (data < node->data)
        node->left = BST_deletion(node->left, data);
 
    // If the data to be deleted is greater than the node's data,
    // then it lies in right subtree
    else if (data > node->data)
        node->right = BST_deletion(node->right, data);
 
    // if data is same as node's data, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (node->left == NULL)
        {
            struct node *temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            struct node *temp = node->left;
            free(node);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct node* temp = minval(node->right);
 
        // Copy the inorder successor's content to this node
        node->data = temp->data;
 
        // Delete the inorder successor
        node->right = BST_deletion(node->right, temp->data);
    }
    return node;
}

/*
 * #####################################################################
 * ################################ CLI ################################
 * #####################################################################
 */

/* The array below will hold the arguments: args[0] is the command. */
static char*    args[512];
pid_t           pid;
int             command_pipe[2];

static char     line[1024];
static int      n = 0; /* number of calls to 'command' */

#define READ    0
#define WRITE   1
 
/*
 * Handle commands separatly
 * input: return value from previous command (useful for pipe file descriptor)
 * first: 1 if first command in pipe-sequence (no input from previous pipe)
 * last: 1 if last command in pipe-sequence (no input from previous pipe)
 *
 * EXAMPLE: If you type "ls | grep shell | wc" in your shell:
 *    fd1 = command(0, 1, 0), with args[0] = "ls"
 *    fd2 = command(fd1, 0, 0), with args[0] = "grep" and args[1] = "shell"
 *    fd3 = command(fd2, 0, 1), with args[0] = "wc"
 *
 * So if 'command' returns a file descriptor, the next 'command' has this
 * descriptor as its 'input'.
 */
static int command(int input, int first, int last)
{
    int pipettes[2];
 
    /* Invoke pipe */
    pipe( pipettes );   
    pid = fork();

    /*
     SCHEME:
        STDIN --> O --> O --> O --> STDOUT
    */
 
    if (pid == 0) { // child
        if (first == 1 && last == 0 && input == 0) {
            // First command
            dup2( pipettes[WRITE], STDOUT_FILENO );
        } else if (first == 0 && last == 0 && input != 0) {
            // Middle command
            dup2(input, STDIN_FILENO);
            dup2(pipettes[WRITE], STDOUT_FILENO);
        } else {
            // Last command
            dup2( input, STDIN_FILENO );
        }

        if (execvp( args[0], args) == -1)
            _exit(EXIT_FAILURE); // If child fails
    }
 
    if (input != 0) 
        close(input);
 
    // Nothing more needs to be written
    close(pipettes[WRITE]);
 
    // If it's the last command, nothing more needs to be read
    if (last == 1)
        close(pipettes[READ]);
 
    return pipettes[READ];
}
 
/* Final cleanup, 'wait' for processes to terminate.
 *  n : Number of times 'command' was invoked.
 */
static void cleanup(int n)
{
    int i;
    for (i = 0; i < n; ++i) 
        wait(NULL); 
}
 
static char* skipwhite(char* s)
{
    while (isspace(*s)) ++s;
    return s;
}
 
static int split(char* cmd)
{
    cmd = skipwhite(cmd);
    char* next = strchr(cmd, ' ');
    int i = 0;
 
    while(next != NULL) {
        next[0] = '\0';
        args[i] = cmd;

        ++i;
        cmd = skipwhite(next + 1);
        next = strchr(cmd, ' ');
    }
 
    if (cmd[0] != '\0') {
        args[i] = cmd;
        next = strchr(cmd, '\n');
        next[0] = '\0';
        ++i; 
    }
    args[i] = NULL;
    return i;
}

void flushtree(node_t * node){
    printf("Reached flushtree!!");
}

char * tree_flag = "BST";
static int run(char* cmd, int input, int first, int last)
{
    int nu_opt, i;

    nu_opt = split(cmd);

    if (args[0] != NULL) {
        if (!strcmp(args[0], "BST") ||
            !strcmp(args[0], "bst"))
        {
            tree_flag = "BST";
        }

        if (!strcmp(args[0], "AVL") ||
            !strcmp(args[0], "avl"))
        {
            tree_flag = "AVL";
        }

        if (!strcmp(args[0], "exit") || 
            !strcmp(args[0], "quit") || 
            !strcmp(args[0], "q")){
            //printf("Really wanna quit?? [n]");
            //scanf("%c", ch)
            exit(0);
        }

        // tree add command parsing:
        if( !strcmp(args[0], "add") || 
            !strcmp(args[0], "a")){
            for(i=1; i<nu_opt; i++){
                if(tree_flag == "BST")
                root = BST_insertion(root, atoi(args[i]));
                if(tree_flag == "AVL")
                root = AVL_insertion(root, atoi(args[i]));
            }
            return 0;
        }

        // tree remove command parsing:
        if( !strcmp(args[0], "rem") || 
            !strcmp(args[0], "r")){
            for(i=1; i<nu_opt; i++){
                if(tree_flag == "BST")
                root = BST_deletion(root, atoi(args[i]));
                if(tree_flag == "AVL")
                root = AVL_deletion(root, atoi(args[i]));
            }
            return 0;
        }

        // tree flush command parsing:
        if( strcmp(args[0], "flush") == 0){
            flushtree(root);
            return 0;
        }

        // tree min command parsing:
        if( strcmp(args[0], "flush") == 0){
            flushtree(root);
            return 0;
        }

        // tree max command parsing:
        if( strcmp(args[0], "flush") == 0){
            flushtree(root);
            return 0;
        }

            // tree remove command parsing:
        if( !strcmp(args[0], "verbosity") || 
            !strcmp(args[0], "verb")){
            verbosity = atoi(args[1]);
            return 0;
        }

        // single command parsing: Help
        if( strcmp(args[0], "?") == 0){
            printf("\nCustom commands:\n"
                   "search or s <el1> <el2> <el3>....\n"
                   "add or a <el1> <el2> <el3>....\n"
                   "rem or r <el1> <el2> <el3>....\n"
                   "min ....\n"
                   "max ....\n"
                   "print or p \n"
                   "? \n");
            return 0;
        }

        // single command parsing: print
        if( !strcmp(args[0], "print") || 
            !strcmp(args[0], "p")){
            printtree(root);
            return 0;
        }

        return command(input, first, last);
    }
    return 0;
}

int main()
{
    while (1) {

        /* Print the command prompt */
        printf("\nTree:%s> ", tree_flag);
        fflush(NULL);

        /* Read a command line */
        if (!fgets(line, 1024, stdin)) 
            return 0;

        int input = 0;
        int first = 1;

        char* cmd = line; 
        input = run(cmd, input, first, 1);
    }
    return 0;
}

