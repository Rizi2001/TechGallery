#pragma once
#include <iostream>
#include <fstream>
#include "DataPair.h"
using namespace std;

int fileNameNum = 0000;

//template<class K>;
class avl
{
public:
    int key;
    string fileName;
    string fileName2;
    int lineNum;
    //static int totalLineCount;
    string value;
    avl* l;
    avl* r;

    avl()
    {
        lineNum = 0;
        fileName = " ";
        fileName2 = " ";
        l = NULL;
        r = NULL;
        value = " ";
        key = 0;

    }
};

//int avl::totalLineCount = 1;

void createFile(avl* node, DataPair d)
{
    //cout << "Going into createFile function \n";

    if (node->lineNum > 100)
    {
        fileNameNum++;
        node->fileName2 = to_string(fileNameNum) + ".txt";  //In case of 100 values in a file
    }

    string fileNameStr = to_string(fileNameNum) + ".txt";

    if (node->fileName == " ")
    {
        node->fileName = fileNameStr;
        fileNameNum++;
    }

    ofstream MyFile(node->fileName, ios::out | ios::app);

    //cout << "Going into createFile function \n";

    int i = 1;

    while (node->lineNum<=100)
    {
        if (i == (node->lineNum))
        {
            MyFile << node->lineNum << " Key: " << node->key << " Value: " << d.value << "\n";
            //node->lineNum++;
            return;
        }

        i++;
    }
}

void readFile(avl* node)
{
    //cout << "Going into Read FIle Fucntion" << endl;

    //node->l = NULL;
    //node->r = NULL;
    //node->fileName = "file1.txt";
    //node->lineNum = 2;

    ifstream file(node->fileName);

    //cout << node->fileName << endl;

    string text = " ";
    int lineCounter = 1, wordCounter = 0;

    //cout << node->lineNum << endl;

    while (file >> text)
    {
        if (wordCounter > 5)
        {
            lineCounter++;
            wordCounter = 0;
        }

        //cout << "Loop ke andar" << endl;

        if (lineCounter == node->lineNum)
        {
            if (wordCounter > 3)
            {
                //cout << "Loop ke andar andar";
                cout << text;
            }
                
        }

        wordCounter++;
    }
}

class avl_tree 
{
    avl* root;
public:
    avl_tree()
    {
        root = NULL;
    }

    int height(avl* t)
    {
        int h = 0;
        if (t != NULL)
        {
            int l_height = height(t->l);
            int r_height = height(t->r);
            int max_height = max(l_height, r_height);
            h = max_height + 1;
        }
        return h;
    }

    int difference(avl* t)
    {
        int l_height = height(t->l);
        int r_height = height(t->r);
        int b_factor = l_height - r_height;
        return b_factor;
    }

    avl* rr_rotat(avl* parent)
    {
        avl* t;
        t = parent->r;
        parent->r = t->l;
        t->l = parent;
        cout << "Right-Right Rotation";
        return t;
    }

    avl* ll_rotat(avl* parent)
    {
        avl* t;
        t = parent->l;
        parent->l = t->r;
        t->r = parent;
        cout << "Left-Left Rotation";
        return t;
    }

    avl* lr_rotat(avl* parent)
    {
        avl* t;
        t = parent->l;
        parent->l = rr_rotat(t);
        cout << "Left-Right Rotation";
        return ll_rotat(parent);
    }

    avl* rl_rotat(avl* parent)
    {
        avl* t;
        t = parent->r;
        parent->r = ll_rotat(t);
        cout << "Right-Left Rotation";
        return rr_rotat(parent);
    }

    avl* balance(avl* t)
    {
        int bal_factor = difference(t);
        if (bal_factor > 1)
        {
            if (difference(t->l) > 0)
                t = ll_rotat(t);
            else
                t = lr_rotat(t);
        }
        else if (bal_factor < -1) 
        {
            if (difference(t->r) > 0)
                t = rl_rotat(t);
            else
                t = rr_rotat(t);
        }

        return t;
    }

    avl* insert(DataPair d)
    {
        avl* temp = new avl;
        temp->key = d.key;
        //temp->lineNum = temp->totalLineCount++;
        temp->l = NULL;
        temp->r = NULL;

        avl* current;

        if (root == NULL)
        {
            root = temp;
            //root->lineNum++;

            current = balance(root);

            root->lineNum++;

            temp->lineNum = root->lineNum;

            createFile(temp, d);

            

            return root;
        }

        current = root;

        while (current)
        {
            if (d.key < current->key)
            {
                if (current->l)
                    current = current->l;
                else
                {
                    current->l = temp;
                    //current->l->lineNum++;
                    break;
                }
            }

            else if (d.key >= current->key)
            {
                if (d.key > current->key)
                    current = current->r;
                else
                {
                    current->r = temp;
                    //current->r->lineNum++;
                    break;
                }
            }

            else
            {
                cout << "Duplicate Value is entered" << endl;
                break;
            }
        }

        current = balance(root);

        //cout << "Neechey wala" << endl;

        root->lineNum++;

        temp->lineNum = root->lineNum;

        createFile(temp, d);

       // current->lineNum++;

        return current;
    }

    bool searchTree(int key)
    {
        avl* current = root;

        while (current)
        {
            if (key < current->l->key)
                current = current->l;
            else if (key > current->r->key)
                current = current->r;
            else 
                return true;
        }

        return false;
    }

    avl* getRoot()
    {
        return root;
    }

    void inorder(avl* t)
    {
        if (t == NULL)
            return;
        inorder(t->l);
    
        cout << t->key << " ";
        cout << root->fileName << " ";
        cout << root->lineNum << " ";
        inorder(t->r);
    }

    void preorder(avl* t)
    {
        if (t == NULL)
            return;

        cout << t->key << " ";
        cout << root->fileName << " ";
        cout << root->lineNum << " ";
        preorder(t->l);
        preorder(t->r);
    }

    void postorder(avl* t)
    {
        if (t == NULL)
            return;

        postorder(t->l);
        postorder(t->r);

        cout << t->key << " ";
        cout << root->fileName << " ";
        cout << root->lineNum << " ";
    }
};

