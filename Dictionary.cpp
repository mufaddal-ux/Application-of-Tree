#include <iostream>
using namespace std;
class node
{
    string key, mean;
    node *left, *right;
    friend class tree;
};
class tree
{
    node *root;

public:
    tree()
    {
        root = NULL;
    }
    void create();
    void display();
    void insert();
    node *copy(node *);
    void copy();
    void inorder();
    void inorder(node *);
    void mirror();
    node *mirror(node *);
    void nonrec_search();
    void deleteNode();
};
class queue
{
    int top, rear;
    friend class tree;
    node *data2[30];

public:
    queue()
    {
        for (int i = 0; i < 30; i++)
        {
            data2[i] = 0;
        }
        top = -1;
        rear = -1;
    }
    void push(node *temp);
    node *pop();
    int empty();
    int size();
};
int queue::size()
{
    return (rear - top);
}
void queue::push(node *temp)
{
    ++rear;
    data2[rear] = temp;
}
int queue::empty()
{
    if (top == rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
node *queue::pop()
{
    node *temp;
    if (!empty())
    {

        ++top;
        temp = data2[top];

        return temp;
    }
    else
    {
        return NULL;
    }
}
void tree::create()
{
    root = new node();
    cout << "\nEnter Root Keyword:";
    cin >> root->key;
    cout << "\nEnter Meaning " << root->key << ":";
    cin >> root->mean;
    root->left = NULL;
    root->right = NULL;
    node *temp, *curr;
    char c = 'c';
    while (c == 'c')
    {
        temp = new node;
        temp = root;
        curr = new node();
        cout << "\nEnter Keyword:";
        cin >> curr->key;
        cout << "\nEnter Meaning of " << curr->key << ":";
        cin >> curr->mean;
        curr->left = curr->right = NULL;

        int flag = 0;
        while (flag == 0)
        {
            if (temp->key > curr->key)
            {
                if (temp->left == NULL)
                {
                    temp->left = curr;
                    flag = 1;
                }
                else
                    temp = temp->left;
            }
            else
            {
                if (temp->right == NULL)
                {
                    temp->right = curr;
                    flag = 1;
                }
                else

                    temp = temp->right;
            }
        }
        cout << "\nIf you want to continue press c or n:";
        cin >> c;
    }
}
void tree::inorder()
{
    inorder(root);
}
void tree::inorder(node *temp)
{
    if (temp != NULL)
    {
        inorder(temp->left);
        cout << " " << temp->key;
        cout << ":" << temp->mean;
        inorder(temp->right);
    }
}
void tree::display()
{
    queue q;
    node *temp;
    temp = root;
    q.push(temp);
    cout << "\nDisplaying Level-Wise\n";
    while (!q.empty())
    {
        int s = q.size();
        while (s > 0)
        {
            temp = q.pop();
            cout << " " << temp->key;
            cout << ":" << temp->mean;
            if (temp->left != NULL)
            {
                q.push(temp->left);
            }
            if (temp->right != NULL)
            {
                q.push(temp->right);
            }
            s--;
        }
        cout << "\n";
    }
}
void tree::insert()
{
    node *temp, *curr;
    temp = root;
    curr = new node();
    cout << "\nEnter Keyword to be inserted:";
    cin >> curr->key;
    cout << "\nEnter Meaning of " << curr->key << ":";
    cin >> curr->mean;
    string a = temp->key;
    string b = curr->key;
    int flag = 0;
    while (flag == 0)
    {
        if (a > b)
        {
            if (temp->left == NULL)
            {
                temp->left = curr;
                flag = 1;
            }
            else
                temp = temp->left;
        }
        else
        {
            if (temp->right == NULL)
            {
                temp->right = curr;
                flag = 1;
            }
            else
                temp = temp->right;
        }
    }
}
void tree::copy()
{
    node *s;
    s = copy(root);
    cout << "\nCopied tree:";
    inorder(s);
}
node *tree::copy(node *root)
{
    node *temp;
    temp = NULL;

    if (root != NULL)
    {
        temp = new node;
        temp->key = root->key;
        temp->mean = root->mean;
        temp->left = copy(root->left);
        temp->right = copy(root->right);
    }
    return temp;
}
void tree::mirror()
{
    node *s;
    s = mirror(root);
    // cout << "\nMirror tree:";
    // inorder(s);
}
node *tree::mirror(node *root)
{
    node *curr, *temp;
    curr = new node;
    if (root != NULL)
    {
        mirror(root->left);
        mirror(root->right);
        curr = root->left;
        root->left = root->right;
        root->right = curr;
    }
    return curr;
}
void tree::deleteNode()
{

    string a;
    cout << "Please enter the word which you want to delete :";
    cin >> a;
    node *temp;
    node *temp1;
    node *curr;
    node *parent;
    node *s;
    node *t1;

    temp = root;

    while (temp != NULL)
    {
        if (a == temp->key)
        {
            curr = temp;
            break;
        }
        else if (a < temp->key)
        {
            parent = temp;
            temp = temp->left;
        }
        else
        {
            parent = temp;
            temp = temp->right;
        }
    }

    if (curr == root)
    { // if the delete value is a root node
        if (curr->left == NULL)
        {
            root = root->right;
        }
        else if (curr->right == NULL)
        {
            root = root->left;
        }
        else if (curr->left != NULL && curr->right != NULL)
        {
            root = curr->right;
            temp1 = curr->left;
            s = curr->right;
            while (s->left != NULL)
            {

                s = s->left;
            }
            s->left = temp1;
        }
    }
    else if (curr != root)
    { // if the delete value is not root node

        if (curr->left != NULL && curr->right != NULL)
        { // if my left child and right child is not null
            s = curr->right;
            t1 = curr->left;

            while (s->left != NULL)
            {

                s = s->left;
            }

            s->left = t1;

            if (curr == parent->left)
            {

                parent->left = curr->right;
            }
            else
            {

                parent->right = curr->right;
            }
        }
        else if (curr->left == NULL && curr->right != NULL)
        { // When left child is NULL and Right child is not Null

            if (curr == parent->right)
            {

                parent->right = curr->right;
            }
            else
            {
                parent->left = curr->right;
            }
        }
        else if (curr->left != NULL && curr->right == NULL) // when left child is not NULL and right child is null
        {
            if (curr == parent->right)
            {

                parent->right = curr->left;
            }
            else
            {

                parent->left = curr->left;
            }
        }
        else
        { // when both are NULL
            if (curr == parent->left)
            {

                parent->left = NULL;
            }
            else
            {

                parent->right = NULL;
            }
        }
    }
    delete curr;
}

void tree::nonrec_search()
{
    string a;
    cout << "\nEnter Keyword to be searched:";
    cin >> a;
    int flag = 0;
    node *temp;
    temp = root;
    while (temp != NULL)
    {
        if (temp->key == a)
        {
            flag = 1;
            break;
        }
        else if (a > temp->key)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->left;
        }
    }
    if (flag == 1)
    {
        cout << "\nFound:";
    }
    else
        cout << "\nNot Found:";
}

int main()
{
    tree t;
    int choice;
    do
    {
        cout << "\n*****MENU***\n>> 1.Create\n>> 2.Insert\n>> 3.Delete\n>> 4.Mirror\n>> 5.Display Level Wise\n>> 6.Copy\n>> 7.Search\n>> Select an option : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            t.create();
            break;
        case 2:
            t.insert();
            break;
        case 3:
            t.deleteNode();
            t.display();
            break;

        case 4:
            cout << "\n>> Mirrored tree is : \n";
            t.mirror();
            t.display();
            break;

        case 5:
            t.display();
            break;

        case 6:

            t.copy();

            break;

        case 7:
            t.nonrec_search();
            break;

        default:
            cout << "\n>> Select a valid option !";
            break;
        }
    } while (choice != 8);

    return 0;
}
