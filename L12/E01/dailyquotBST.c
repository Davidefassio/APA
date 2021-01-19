#include "dailyquotBST.h"

typedef struct node{
    DailyQuot dq;
    struct node* left;
    struct node* right;
}Node;

struct dqBST{
    Node *root;
    int n;
};

// Node's functions
static Node* Node_new(DailyQuot dq){
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->dq = dq;
    tmp->left = tmp->right = NULL;
    return tmp;
}

static void Node_free(Node *n){
    free(n);
}

// BST's functions
BST BST_init(){
    BST tmp = (BST) malloc(sizeof(struct dqBST));
    tmp->root = NULL;
    tmp->n = 0;
    return tmp;
}

// Stampa in order
static void fprintR(FILE *fp, Node *ptr){
    if(ptr == NULL) return;
    fprintR(fp, ptr->left);
    DQ_fprint(fp, ptr->dq);
    fprintR(fp, ptr->right);
}

void BST_fprint(FILE *fp, BST bst){
    fprintR(fp, bst->root);
}

void BST_insert(BST bst, DailyQuot dq){
    Node *tmp = Node_new(dq);

    ++(bst->n);

    // Inserisci nella radice
    if(bst->root == NULL){
        bst->root = tmp;
        return;
    }

    Node *ptr = bst->root;

    // Inserisci in foglia
    while(1){
        if(data_cmp(dq.day, ptr->dq.day) > 0){
            if(ptr->right == NULL){ // inserisci
                ptr->right = tmp;
                return;
            }
            ptr = ptr->right;
        }
        else{
            if(ptr->left == NULL){ // inserisci
                ptr->left = tmp;
                return;
            }
            ptr = ptr->left;
        }
    }
}

DailyQuot* BST_search(BST bst, Data d){
    Node *ptr = bst->root;
    int b;

    while(ptr != NULL){
        b = data_cmp(d, ptr->dq.day);
        if(b == 0)
            return &ptr->dq;
        else if(b > 0)
            ptr = ptr->right;
        else
            ptr = ptr->left;
    }

    return DQ_ItemSetVoid();
}

static DailyQuot qmin, qmax; // Usate da BST_minmax

static void BST_minmaxR(Node *n, Data d1, Data d2){
    if(n == NULL) return;

    int b;

    if((b = data_cmp(d1, n->dq.day)) >= 0){ // Cerco solo a destra
        if(b == 0){ // Controllo anche il nodo
            if(n->dq.avg > qmax.avg)
                qmax = n->dq;
            if(n->dq.avg < qmin.avg)
                qmin = n->dq;
        }

        // Ricorro a destra
        BST_minmaxR(n->right, d1, d2);

        return;
    }

    if((b = data_cmp(d2, n->dq.day)) <= 0){ // Cerco solo a sinistra
        // Ricorro a sinistra
        BST_minmaxR(n->left, d1, d2);

        if(b == 0){ // Controllo anche il nodo
            if(n->dq.avg > qmax.avg)
                qmax = n->dq;
            if(n->dq.avg < qmin.avg)
                qmin = n->dq;
        }

        return;
    }

    // Cerco sia dx che sx
    BST_minmaxR(n->left, d1, d2);

    // Controllo il nodo
    if(n->dq.avg > qmax.avg)
        qmax = n->dq;
    if(n->dq.avg < qmin.avg)
        qmin = n->dq;

    BST_minmaxR(n->right, d1, d2);

    return;
}

void BST_minmaxInterval(BST bst, Data d1, Data d2){
    qmin.avg = FLT_MAX;
    qmax.avg = FLT_MIN;
    BST_minmaxR(bst->root, d1, d2);

    printf("Min: ");
    DQ_fprint(stdout, qmin);
    printf("Max: ");
    DQ_fprint(stdout, qmax);
}

void BST_minmaxAll(BST bst){
    qmin.avg = FLT_MAX;
    qmax.avg = FLT_MIN;
    BST_minmaxR(bst->root, data_getMin(), data_getMax());

    printf("Min: ");
    DQ_fprint(stdout, qmin);
    printf("Max: ");
    DQ_fprint(stdout, qmax);
}

static void freeR(Node *n){
    if(n == NULL) return;
    freeR(n->left);
    freeR(n->right);
    Node_free(n);
}

static void in_orderR(Node *ptr, DailyQuot *dq){
    int cnt = 0;
    if(ptr == NULL) return;
    in_orderR(ptr->left, dq);
    dq[cnt++] = ptr->dq;
    in_orderR(ptr->right, dq);
}

static void createBalanced(Node *ptr, DailyQuot *dq, int l, int r){
    if(l > r) return;

    int m = (l + r) / 2;

    ptr = Node_new(dq[m]);
    createBalanced(ptr->left, dq, l, m-1);
    createBalanced(ptr->right, dq, m+1, r);
}


void BST_balance(BST bst, int S){
    DailyQuot *dq = (DailyQuot*) malloc(bst->n * sizeof(DailyQuot));

    in_orderR(bst->root, dq);

    freeR(bst->root);

    int m = bst->n / 2;

    bst->root = Node_new(dq[m]);
    createBalanced(bst->root->left, dq, 0, m-1);
    createBalanced(bst->root->right, dq, m+1, bst->n);

    free(dq);
}

void BST_free(BST bst){
    if(bst == NULL) return;
    freeR(bst->root);
    free(bst);
}
