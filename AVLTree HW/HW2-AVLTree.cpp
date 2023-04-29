#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

class node{
    public:
        string key;
        int bf, h; // bf is Balance Factor, h = height
        node *left, *right;
        node():key(), bf(0), h(1), left(NULL), right(NULL){};
        node(string s):key(s), bf(0), h(1), left(NULL), right(NULL){}; //constructor
};

int max(int a, int b){ // compare a with b
    return (a > b) ? a:b; // if a > b return a, else return b 
};

int height(node *N){ // return node->h
    if (N == NULL)
        return 0;
    return N->h;
};

int get_balance_factor(node *n){ // compute value of node bf
    if(n == NULL)
        return 0;
    return height(n->left) - height(n->right);
};

node* newnode(string key){ // create node and assignment
    node *temp = new node(key);
    return temp;
};

node* left_rotate(node *x){ // from / left rotate to ^

    node *y = x->right;
    node *temp = y->left;

    y->left = x;
    x->right = temp;

    x->h = max(height(x->left), height(x->right))+1;
    y->h = max(height(y->left), height(y->right))+1;

    return y; // return node is connect parent node
};

node* right_rotate(node *x){ // from \ right rotate to ^

    node *y = x->left;
    node *temp = y->right;
    
    y->right = x;
    x->left = temp;

    x->h = max(height(x->left), height(x->right))+1;
    y->h = max(height(y->left), height(y->right))+1;

    return y; // return node is connect parent node
}

node* insert_node(node *node, string key){
    if(node == NULL)
        return newnode(key);
        // tree is empty
    if(key < node->key)
        node->left = insert_node(node->left, key);
        // like binary search, recursive to left node and return node
    else if(key > node->key)
        node->right = insert_node(node->right, key);
        // like binary search, recursive to right node and return node
    else // if key = node->key back to previous step 
        return node; // return node = nonchange

    // Update the balance factor of each node and balance the tree

    node->h = 1 + max(height(node->left), height(node->right)); // the default height is 1, add max childnode height = node height
    node->bf = get_balance_factor(node);

    if(node->bf > 1){ // the left subtree height > right subtree height
        // do right rotation or left-right rotation two options
        if(key < node->left->key) // do right rotation 
            return right_rotate(node); // let parent node connect this node
        else if(key > node->left->key){ // do left-right  rotation
            node->left = left_rotate(node->left);
            return right_rotate(node); // let parent node connect this node
        }
    }
    if(node->bf < -1){ // the left subtree height < right subtree height
        // do left rotation or right-left rotation two options
        if(key > node->right->key) // do left roration
            return left_rotate(node); // let parent node connect this node
        else if(key < node->right->key){ // do left-right rotation
            node->right = right_rotate(node->right);
            return left_rotate(node); // let parent node connect this node
        }
    }
    
    return node;
};

node *max_value_node(node *n){ // find current child max node
    node *current = n;
    while(current->right != NULL)
        current = current->right;
    return current;
};

node *min_value_node(node *n){ // find current child min node
    node *current = n;
    while(current->left != NULL)
        current = current->left;
    return current;
}

node *delete_node(node *root, string key){

    //find the node and delete it
    if(root == NULL)
        return root;
        // tree is empty can't delete
    if(key < root->key)
        root->left = delete_node(root->left, key);
        // like binary search, recursive to left node and return node
    else if(key > root->key)
        root->right = delete_node(root->right, key);
        // like binary search, recursiveto right node and return node
    else{ // key == root->key
        if((root->left == NULL) || (root->right == NULL)){
            node *temp = (root->left != NULL) ? root->left : root->right;
            // if root->left != NULL, temp = root->left, else if root == NULL, temp = root->right

            if(temp == NULL){ // the case is that both node is NULL
                temp = root;
                root = NULL;
            }
            else {// the case is have one child node
                *root = *temp; // Modify the value of the index pointing to the root node
                /*
                To modify the value of the index pointing to the root node, we need to pass 
                it as an index pointing to the index, so that we can modify the value of the 
                index pointing to the root node inside the function
                */
            }
        free(temp);
        }
        else {
            node *temp = max_value_node(root->left); // or min_value(root->right)
            // temp node instead of root node
            root->key = temp->key;
            root->bf = temp->bf;
            root->h = temp->h;

            root->left = delete_node(root->left, temp->key); 
            // put temp node to delete_node function and delete it
        }
        // else {
            // node *temp = min_value_node(root->right); 
            // temp node instead of root node
            // root->key = temp->key;
            // root->bf = temp->bf;
            // root->h = temp->h;
            // root->right = delete_node(root->right, temp->key); 
            // put temp node to delete_node function and delete it
        // }
    }

    if(root == NULL) // recheck after delete
        return root; // return self

    // Update the balance factor of each node and
    // balance the tree

    root->h = 1 + max(height(root->left), height(root->right)); // the default height is 1, add max childnode height = node height
    root->bf = get_balance_factor(root);
    if (root->left)
        root->left->bf = get_balance_factor(root->left);
    if (root->right)
        root->right->bf = get_balance_factor(root->right);

    if(root->bf > 1){
        if(root->left->bf >= 0) // the case is / , root->left->h left > right
            return right_rotate(root);
        else{
            root->left = left_rotate(root->left);
            return right_rotate(root);
        }
    }
    if(root->bf < -1){
        if(root->right->bf <= 0)
            return left_rotate(root);
        else{
            root->right = right_rotate(root->right);
            return left_rotate(root);
        }
    }

    return root;
};

void rectify_bf(node *root){ // Recalculate BF value
    if(root != NULL){
        root->bf = get_balance_factor(root);
        rectify_bf(root->left);
        rectify_bf(root->right);
    }
};

void preorder(node *root){
    if(root != NULL){
        cout << "key is = " << root->key << endl;
        preorder(root->left);
        preorder(root->right);
    }
};

void inorder(node *root, string s){
    ofstream outfile;
    outfile.open(s, ios_base::in | ios_base::app);
    if(root != NULL){
        inorder(root->left, s);
        cout << "inorder is = " << root->key << ", Height = " << root->h << ", BF = " << root->bf<< endl;
        outfile << "inorder => " << root->key << endl;
        inorder(root->right, s);
    }
};

void postorder(node *root, string s){
    ofstream outfile;
    outfile.open(s, ios_base::in | ios_base::app);
    if(root != NULL){
        postorder(root->left, s);
        postorder(root->right, s);
        outfile << "postorder => " << root->key << endl;
        cout << "postorder is = " << root->key << ", Height = " << root->h << ", BF = " << root->bf<< endl;
    }
};

int main(){

    ifstream infile;
    ofstream outfile;
    node *root = NULL;
    string buff;

    infile.open("範例一輸入.txt", ios_base::in);
    if(infile.fail())
    {
        cerr << "Error: input 範例一輸入 opening fail !" << endl;
        exit(1);
    }
    outfile.open("範例一輸出.txt", ios_base::out);
    if(outfile.fail())
    {
        cerr << "Error: output 範例一輸入 opening fail" << endl;
        exit(1);
    }

    int i;
    for(i = 0; i < 8; i++){
        infile >> buff;
        root = insert_node(root, buff);
    }
    for(i = 0; i < 2; i++){
        infile >> buff;
        root = delete_node(root, buff);
    }
    for(i = 0 ; i < 4; i++){
        infile >> buff;
        root = insert_node(root, buff);
    }
    for(i = 0; i < 2; i++){
        infile >> buff;
        root = delete_node(root, buff);
    }
    for(i = 0; i < 4; i++){
        infile >> buff;
        root = insert_node(root, buff);
    }

    // root = insert_node(root, "blueberry");
    // root = insert_node(root, "raspberry");
    // root = insert_node(root, "mulberry");
    // root = insert_node(root, "orange");
    // root = insert_node(root, "citron");
    // root = insert_node(root, "pomelo");
    // root = insert_node(root, "sunkist");
    // root = insert_node(root, "grapefruit");
    // root = delete_node(root, "orange");
    // root = delete_node(root, "citron");
    // root = insert_node(root, "apple");
    // root = insert_node(root, "mango");
    // root = insert_node(root, "cherry");
    // root = insert_node(root, "olive");
    // root = delete_node(root, "mulberry");
    // root = delete_node(root, "cherry");
    // root = insert_node(root, "guava");
    // root = insert_node(root, "pear");
    // root = insert_node(root, "tomato");
    // root = insert_node(root, "watermelon");
    rectify_bf(root);

    cout << "First AVLTree" << endl;
    inorder(root, "範例一輸出.txt");
    postorder(root, "範例一輸出.txt");

    outfile.close();
    infile.close();
    cout << "_____________________________________________"<< endl << endl;
    node *root2 = NULL;

    infile.open("範例二輸入.txt", ios_base::in);
    if(infile.fail())
    {
        cerr << "Error: input 範例二輸入 opening fail " << endl;
        exit(1);
    }
    outfile.open("範例二輸出.txt", ios_base::out);
    if(outfile.fail())
    {
        cerr << "Error: output 範例二輸入 opening fail " << endl;
        exit(1); 
    }

    for(i = 0; i < 7; i++){
        infile >> buff;
        root2 = insert_node(root2, buff);
    }
    for(i = 0; i < 3; i++){
        infile >> buff;
        root2 = delete_node(root2, buff);
    }
    for(i = 0; i < 6; i++){
        infile >> buff;
        root2 = insert_node(root2, buff);
    }
    for(i = 0; i < 2; i++){
        infile >> buff;
        root2 = delete_node(root2, buff);
    }
    for(i = 0; i < 3; i++){
        infile >> buff;
        root2 = insert_node(root2, buff);
    }

    // root2 = insert_node(root2, "F");
    // root2 = insert_node(root2, "D");
    // root2 = insert_node(root2, "Z");
    // root2 = insert_node(root2, "G");
    // root2 = insert_node(root2, "A");
    // root2 = insert_node(root2, "B");
    // root2 = insert_node(root2, "O");
    // root2 = delete_node(root2, "F");
    // root2 = delete_node(root2, "G");
    // root2 = delete_node(root2, "Z");
    // root2 = insert_node(root2, "K");
    // root2 = insert_node(root2, "I");
    // root2 = insert_node(root2, "J");
    // root2 = insert_node(root2, "U");
    // root2 = insert_node(root2, "Y");
    // root2 = insert_node(root2, "E");
    // root2 = delete_node(root2, "E");
    // root2 = delete_node(root2, "U");
    // root2 = insert_node(root2, "T");
    // root2 = insert_node(root2, "W");
    // root2 = insert_node(root2, "E");
    rectify_bf(root2);

    cout << "Second AVLTree" << endl;
    inorder(root2, "範例二輸出.txt");
    postorder(root2, "範例二輸出.txt");

    outfile.close();
    infile.close();

    cout << "_____________________________________________"<< endl << endl;
    node *root3 = NULL;

    infile.open("範例三輸入.txt", ios_base::in);
    if(infile.fail())
    {
        cerr << "Error: input 範例三輸入 opening fail " << endl;
        exit(1);
    }
    outfile.open("範例三輸出.txt", ios_base::out);
    if(outfile.fail())
    {
        cerr << "Error: output 範例三輸出 opening fail " << endl;
        exit(1);
    }
    
    for(i = 0 ; i < 12; i++){
        infile >> buff;
        root3 = insert_node(root3, buff);
    }
    for(i = 0; i < 2; i++){
        infile >> buff;
        root3 = delete_node(root3, buff);
    }
    for(i = 0 ; i < 5; i++){
        infile >> buff;
        root3 = insert_node(root3, buff);
    }
    for(i = 0; i < 3; i++){
        infile >> buff;
        root3 = delete_node(root3, buff);
    }
    for(i = 0 ; i < 6; i++){
        infile >> buff;
        root3 = insert_node(root3, buff);
    }

    // root3 = insert_node(root3, "turtle");
    // root3 = insert_node(root3, "swan");
    // root3 = insert_node(root3, "rabbit");
    // root3 = insert_node(root3, "porpoise");
    // root3 = insert_node(root3, "owl");
    // root3 = insert_node(root3, "alligator");
    // root3 = insert_node(root3, "camel");
    // root3 = insert_node(root3, "zebra");
    // root3 = insert_node(root3, "wren");
    // root3 = insert_node(root3, "toad");
    // root3 = insert_node(root3, "skunk");
    // root3 = insert_node(root3, "platypus");
    // root3 = delete_node(root3, "owl");
    // root3 = delete_node(root3, "rabbit");
    // root3 = insert_node(root3, "penguin");
    // root3 = insert_node(root3, "monkey");
    // root3 = insert_node(root3, "leopard");
    // root3 = insert_node(root3, "jellyfish");
    // root3 = insert_node(root3, "hyena");
    // root3 = delete_node(root3, "camel");
    // root3 = delete_node(root3, "swan");
    // root3 = delete_node(root3, "monkey");
    // root3 = insert_node(root3, "hummingbird");
    // root3 = insert_node(root3, "hawk");
    // root3 = insert_node(root3, "gorilla");
    // root3 = insert_node(root3, "ferret");
    // root3 = insert_node(root3, "elk");
    // root3 = insert_node(root3, "coyote");
    rectify_bf(root3);

    cout << "Third AVLTree" << endl;
    inorder(root3, "範例三輸出.txt");
    postorder(root3, "範例三輸出.txt");
    outfile.close();
    infile.close(); 

    return 0;
}