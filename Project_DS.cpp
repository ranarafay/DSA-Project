#include <iostream>
#include <fstream>
#include <string>

using namespace std;



// class for getting (character) with its (frequency)
class CharFreq
{
public:
    char chr;
    int freq;
};
// class for getting (array of objects of CharFreq) with the (length)
class CharFreqarrLen
{
public:
    CharFreq *arr;
    int len;
};

// ------------------------------------------------------------------------------

// (helper function) for checking character present in arrcharfreq
bool checkChar(char *arr, char ch)
{
    bool chk = false;
    // traversing through the given array and checking for character
    for (int i = 0; arr[i]; i++)
    {
        if (ch == arr[i])
        {
            chk = true;
        }
    }
    // returning the bool check
    return chk;
}

// function to evaluate the frequency of the characters
// it will return an object which will contain number of unique characters and array of object containing charcters anf their frequencies
CharFreqarrLen evaluateFreq(string str)
{
    char *arr = new char[100];
    int j = 0;
    // storing unique characters in array
    for (int i = 0; str[i]; i++)
    {
        char ch = str[i];
        if (checkChar(arr, ch))
        {
            continue;
        }
        else
        {
            arr[j] = str[i];
            j++;
        }
    }
    arr[j] = '\0';

    // fincing the number of unique charcters
    int len = 0;
    for (int i = 0; arr[i] != '\0'; i++)
    {
        len++;
    }

    // making array of objects for storing characters with their frequencies
    CharFreq *arrcharfreq = new CharFreq[len];

    // storing objects containing characters with their frequencies in the array of objects
    for (int i = 0; i < len; i++)
    {
        int cnt = 0;
        for (int j = 0; str[j]; j++)
        {
            if (arr[i] == str[j])
            {
                cnt++;
            }
        }
        arrcharfreq[i].chr = arr[i];
        arrcharfreq[i].freq = cnt;
    }

    // Applying "Bubble Sort" technique for sorting the frequency and characters in acending order
    // loop to access each arrcharfreq element
    for (int i = 0; i < len; i++)
    {
        // loop to comparearrcharfreq elements
        for (int j = i + 1; j < len; j++)
        {
            // compare two adjacent elements
            if (arrcharfreq[i].freq > arrcharfreq[j].freq)
            {
                CharFreq temp = arrcharfreq[j];
                arrcharfreq[j] = arrcharfreq[i];
                arrcharfreq[i] = temp;
            }
        }
    }

    // initializing the object datamembers
    CharFreqarrLen arrlen;
    arrlen.arr = arrcharfreq;
    arrlen.len = len;

    // returning final sorted array of characters with their frequencies
    return arrlen;
}

// ------------------------------------------------------------------------------

// class Queue for further implementation
// using template
template <class x>
class Queue
{
public:
    x *arr;       // array to store Queue elements
    int capacity; // maximum capacity of the Queue
    int front;    // front points to the front element in the Queue (if any)
    int rear;     // rear points to the last element in the Queue
    int count;    // ind size of the Queue

public:
    Queue(int size = 50); // constructor

    // functions
    x dequeue();
    void enqueue(x);
    x peek();
    int size();
    bool isEmpty();
    bool isFull();
};

// constructor to initialize Queue
template <class x>

Queue<x>::Queue(int size)
{
    arr = new x[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}

// function to dequeue the front element
template <class x>
x Queue<x>::dequeue()
{
    // check for Queue underflow
    if (isEmpty())
    {
        cout << "Underflow" << endl;
    }

    int temp = front;

    front = (front + 1) % capacity;
    count--;

    return arr[temp];
}

// function to add an item to the Queue
template <class x>
void Queue<x>::enqueue(x item)
{
    // check for Queue overflow
    if (isFull())
    {
        cout << "Overflow" << endl;
    }

    rear = (rear + 1) % capacity;
    arr[rear] = item;
    count++;
}

// function to return the front element of the Queue
template <class x>
x Queue<x>::peek()
{
    if (isEmpty())
    {
        cout << "UnderFlow" << endl;
    }
    return arr[front];
}

// function to return the size of the Queue
template <class x>
int Queue<x>::size()
{
    return count;
}

// function to check if the Queue is empty or not
template <class x>
bool Queue<x>::isEmpty()
{
    return (size() == 0);
}

// function to check if the Queue is full or not
template <class x>
bool Queue<x>::isFull()
{
    return (size() == capacity);
}

// ------------------------------------------------------------------------------

// class for huffmanNode
class huffmanNode
{
public:
    huffmanNode *left;
    int freq;
    char chr;
    huffmanNode *right;

    // constructor
    huffmanNode();
};

// constructor for initializing data members
huffmanNode ::huffmanNode()
{
    left = right = NULL;
    chr = '$';
    freq = -1;
}

// ----------------------------------------------------------------------------------------------
// (helper function) to return the height of the node
int height(huffmanNode *root)
{
    // Base case: empty tree has height 0
    if (root == nullptr)
    {
        return 0;
    }

    // recur for left and right subtree and consider maximum depth
    return 1 + max(height(root->left), height(root->right));
}

// checking balance of the overall tree
bool checkBalance(huffmanNode *node)
{
    bool chk = true;
    if (node == NULL)
    {
        return chk;
    }

    int right = height(node->right);
    int left = height(node->left);

    int balancefac = left - right;

    if (balancefac != -1 && balancefac != 0 && balancefac != 1)
    {
        chk = false;
        return chk;
    }

    return chk;
}

// (helper function) to compute the balance factor
int bfactor(huffmanNode *temp)
{
    int lheight = height(temp->left);
    int rheight = height(temp->right);
    int bfactor = lheight - rheight;
    return bfactor;
}

// (helper functions) functions for balancing the nodes

// Right - Right rotation
huffmanNode *rrRotaion(huffmanNode *node)
{
    huffmanNode *temp;
    temp = node->right;
    node->right = temp->left;
    temp->left = node;
    return temp;
}

// Left - Left rotation
huffmanNode *llRotation(huffmanNode *node)
{
    huffmanNode *temp;
    temp = node->left;
    node->left = temp->right;
    temp->right = node;
    return temp;
}

// Left - Right rotation
huffmanNode *lrRotation(huffmanNode *node)
{
    huffmanNode *temp;
    temp = node->left;
    node->left = rrRotaion(temp);
    return llRotation(node);
}

// Right - Left rotation
huffmanNode *rlRotation(huffmanNode *node)
{
    huffmanNode *temp;
    temp = node->right;
    node->right = llRotation(temp);
    return rrRotaion(node);
}

// to balance the nodes
huffmanNode *balance(huffmanNode *temp)
{
    int balfac = bfactor(temp);

    if (balfac > 1)
    {
        if (bfactor(temp->left) > 0)
        {
            temp = llRotation(temp);
        }
        else
        {
            temp = lrRotation(temp);
        }
    }
    else if (balfac < -1)
    {
        if (bfactor(temp->right) > 0)
        {
            temp = rlRotation(temp);
        }
        else
        {
            temp = rrRotaion(temp);
        }
    }
    return temp;
}

// ----------------------------------------------------------------------------------------------


// (helper function) to sort the queue in acending order
// Bubble Sort technique
void sortQueue(Queue<huffmanNode *> &huffque, int len)
{
    // Applying "Bubble Sort" technique for sorting the frequency and characters in acending order
    // loop to access eacharrcharfreq element
    for (int i = huffque.front; i < len; i++)
    {
        // loop to comparearrcharfreq elements
        for (int j = i + 1; j < len; j++)
        {
            // compare two adjacent elements
            if (huffque.arr[i]->freq > huffque.arr[j]->freq)
            {
                huffmanNode *temp = huffque.arr[j];
                huffque.arr[j] = huffque.arr[i];
                huffque.arr[i] = temp;
            }
        }
    }
}


// function to traverse the huffman tree and print the codes
void printCode(huffmanNode *root, string str)
{
    if (root == NULL)
        return;

    if (root->chr == '$')
    {
        printCode(root->left, str + "0");
        printCode(root->right, str + "1");
    }

    if (root->chr != '$')
    {
        cout << root->chr << " : " << str << "\n";
        printCode(root->left, str + "0");
        printCode(root->right, str + "1");
    }
}


// helper function to compute ABR and Compression Ratio
void SUM_FiLi(huffmanNode *root, string str, float *cr)
{
    // base condition
    if (root == NULL)
    {
        return;
    }

    // using recursion traversing the nodes and concatinating string with 0s and 1s then finding the length of string and multipyloing it by frequency
    if (root->chr == '$')
    {
        SUM_FiLi(root->left, str + "0", cr);
        SUM_FiLi(root->right, str + "1", cr);
    }

    if (root->chr != '$')
    {
        *cr += root->freq * str.length();

        SUM_FiLi(root->left, str + "0", cr);
        SUM_FiLi(root->right, str + "1", cr);
    }
}


// function to make balanced huffman tree
void balHuffmantree(string s1)
{
    // taking object containing array of objects of charcters with their frequencies
    CharFreqarrLen arrlen = evaluateFreq(s1);

    // 
    int len = arrlen.len;

    // creating huffmannodes and enqueueing them into queue
    Queue<huffmanNode *> huffque(len * 2);
    for (int i = 0; i < len; i++)
    {
        huffmanNode *node = new huffmanNode;

        node->chr = arrlen.arr[i].chr;
        node->freq = arrlen.arr[i].freq;

        // enqueueing nodes
        huffque.enqueue(node);
    }
    
    // making hufftree
    huffmanNode *hufftree = new huffmanNode;
    while (huffque.front != huffque.rear)
    {
        // declaring huffman node
        huffmanNode *newnode = new huffmanNode;
        // initializing node
        newnode->freq = 0;
        newnode->chr = '$';
        newnode->left = NULL;
        newnode->right = NULL;

        // making nodes for storing dequeued nodes
        huffmanNode *temp1 = new huffmanNode;
        huffmanNode *temp2 = new huffmanNode;
        // dequeueing nodes from queue
        temp1 = huffque.dequeue();
        temp2 = huffque.dequeue();

        // initialing data members of nodes
        newnode->left = temp2;
        newnode->right = temp1;
        newnode->freq = temp1->freq + temp2->freq;

        // balancing nodes
        newnode = balance(newnode);

        // enqueueing newnode in queue
        huffque.enqueue(newnode);
        len++;

        // soritng queue at every iteration (after enqueueing each node)
        sortQueue(huffque, len);

        hufftree = newnode;
    }

    // computing total frequency
    int totalfreq = 0;
    for (int i = 0; i < arrlen.len; i++)
    {
        totalfreq += arrlen.arr[i].freq;
    }

    // printing codes and compression ratio
    cout << "\n-----------------------" << endl;
    cout << "Optimized Huffman Tree: " << endl;
    cout << "-----------------------" << endl;

    cout << '\n';
    printCode(hufftree, "");

    // computing compression ratio
    float huffcr = 0;
    SUM_FiLi(hufftree, "", &huffcr);
    float HuffABR = huffcr / totalfreq;
    float compressionhuff = 8 / HuffABR;
    cout << "\nCompression Ratio: " << compressionhuff << endl;
    cout << "---------------------------\n"
         << endl;
}

void huffmanTree(string s1)
{
    // taking object containing array of objects of charcters with their frequencies
    CharFreqarrLen arrlen = evaluateFreq(s1);

    int len = arrlen.len;

    // creating huffmannodes and enqueueing them into queue
    Queue<huffmanNode *> huffque(len * 2);
    for (int i = 0; i < len; i++)
    {
        huffmanNode *node = new huffmanNode;

        node->chr = arrlen.arr[i].chr;
        node->freq = arrlen.arr[i].freq;

        huffque.enqueue(node);
    }

    // making hufftree
    huffmanNode *hufftree = new huffmanNode;
    while (huffque.front != huffque.rear)
    {
        // declaring huffman node
        huffmanNode *newnode = new huffmanNode;
        // initializing node
        newnode->freq = 0;
        newnode->chr = '$';
        newnode->left = NULL;
        newnode->right = NULL;

        // making nodes for storing dequeued nodes
        huffmanNode *temp1 = new huffmanNode;
        huffmanNode *temp2 = new huffmanNode;
        // dequeueing nodes from queue
        temp1 = huffque.dequeue();
        temp2 = huffque.dequeue();

        // initialing data members of nodes
        newnode->left = temp2;
        newnode->right = temp1;
        newnode->freq = temp1->freq + temp2->freq;

        // enqueueing newnode in queue
        huffque.enqueue(newnode);
        len++;

        // soritng queue at every iteration (after enqueueing each node)
        sortQueue(huffque, len);

        hufftree = newnode;
    }

    // computing total frequency
    int totalfreq = 0;
    for (int i = 0; i < arrlen.len; i++)
    {
        totalfreq += arrlen.arr[i].freq;
    }

    // printing codes and compression ratio
    cout << "\n\n-------------" << endl;
    cout << "Huffman Tree: " << endl;
    cout << "-------------" << endl;

    cout << "\n";
    printCode(hufftree, "");

    // computing compression rate
    float huffcr = 0;
    SUM_FiLi(hufftree, "", &huffcr);
    float HuffABR = huffcr / totalfreq;
    float compressionhuff = 8 / HuffABR;
    cout << "\nCompression Ratio: " << compressionhuff << endl;
    cout << "---------------------------\n"
         << endl;

    // checking balance of the tree and printing codes and compression ratio for optimized/balanced huffman tree
    if (checkBalance(hufftree) == true)
    {
        cout << "\nNote: Tree is balanced and in optimal state." << endl;
        balHuffmantree(s1);
    }
    else if (checkBalance(hufftree) == false)
    {
        balHuffmantree(s1);
    }
}

// instead of using main we are using function
void Implementation()
{
    // asking for a file or any input from keyborad
    int chk;
    cout << "\nPress: " << endl;
    cout << "1: For File" << endl;
    cout << "2: For Input" << endl;
    cout << "Enter: ";
    cin >> chk;

    // variable for taking data from file or from user
    string data;

    // file
    if (chk == 1)
    {
        cout << "\nEnter the Filename: ";
        string filename;
        cin >> filename;

        // opening file
        fstream file;
        file.open(filename, ios::in);

        // if file exist
        if (file.is_open())
        {

            // getting the text in the file (assuming only one line specifically)
            getline(file, data);
            huffmanTree(data);
        }
        // if file don't exist
        else
        {
            cout << "File not found!" << endl;
        }
        file.close();
    }
    // input
    else if (chk == 2)
    {
        cout << "\nEnter Text: ";
        cin >> data;

        huffmanTree(data);
    }
    // invalid
    else
    {
        cout << "Invalid Input!" << endl;
        cout << "Terminated!" << endl;
    }
}

int main()
{

    Implementation();
    return 0;
}