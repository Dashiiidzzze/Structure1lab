#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "vectorDas.h"

using namespace std;

// вспомогательные функции
int Strlen(const string &str);
string Substr(const string &str, int start, int end);
MyVector<string>* Split(const string &str, char delim);
string DataRead(const string& name, const string& fileName, const string& structure, const string& nextStructure);
void Rewrite(const string& fileName, const string& oldStr, const string& newStr, const string& structure, const string& nextStructure);


// работа с массивом:
struct Massiv {
    string* data;       //сам массив
    int len;            //длина
    int cap;            //capacity - объем
    int LoadFactor;     //с какого процента заполнения увеличиваем объем = 50%
};

ostream& operator << (ostream& os, const Massiv& vec);
Massiv* CreateMassiv(int initCapacity, int initLoadFactor);
void ExpansMassiv(Massiv& vec);
void AddMassiv(Massiv& vec, string value);
void DeleteMassiv(Massiv& vec, int index);
void ReplaceMassiv(Massiv& vec, int index, string value);
Massiv* MassivFromFile(string& str);
string MassToString(const Massiv& vec, const string& name);
void MasQuery(const MyVector<string>& words, const string& filename) ;


// работа с односвязным списком
struct FListNode {
    string value;
    FListNode* next;

    FListNode(string v = "", FListNode* n = nullptr) : value(v), next(n) {}
};

ostream& operator << (ostream& os, FListNode* head);
void AddFlist(FListNode*& fList, string& value);
void AddToTailFList(FListNode*& fList, string& value);
void DeleteFromHead(FListNode*& head);
void DeleteFromTail(FListNode*& head);
void DeleteByValue(FListNode*& head, string& value);
bool SearchByValue(FListNode*& head, const string& value);
FListNode* FListFromFile(string& str);
string FListToString(FListNode* vec, const string& name);
void FListQuery(const MyVector<string>& words, const string& filename);


// работа с двусвязным списком
struct DListNode {
    DListNode* prev;
    string value;
    DListNode* next;

    DListNode(DListNode* p = nullptr, string v = "", DListNode* n = nullptr) : prev(p), value(v), next(n) {}
};

ostream& operator << (ostream& os, DListNode* tail);
void AddDlist(DListNode*& head, DListNode*& tail, string value);
void AddToTailDList(DListNode*& head, DListNode*& tail, string value);
string DeleteFromHeadDList(DListNode*& head, DListNode*& tail);
void DeleteFromTailDList(DListNode*& head, DListNode*& tail);
void DeleteByValueDList(DListNode*& head, DListNode*& tail, string value);
bool SearchByValueDlist(DListNode*& head, DListNode*& tail, string value);
void DListFromFile(string& str, DListNode*& head, DListNode*& tail);
string DListToString(DListNode*& tail, const string& name);
void DListQuery(const MyVector<string>& words, const string& filename);


// работа с очередью
struct QueueNode {
    QueueNode* prev;
    string value;
    QueueNode* next;

    QueueNode(QueueNode* p = nullptr, string v = "", QueueNode* n = nullptr) : prev(p), value(v), next(n) {}
};

void QueuePush(QueueNode*& head, QueueNode*& tail, string value);
string QueuePop(QueueNode*& head, QueueNode*& tail);
void QueueFromFile(string& str, QueueNode*& head, QueueNode*& tail);
string QueueToString(QueueNode*& tail, const string& name);
void QueueQuery(const MyVector<string>& words, const string& filename);


// работа со стеком
struct StackNode {
    string value;
    StackNode* next;

    StackNode(string v, StackNode* n = nullptr) : value(v), next(n) {}
};

void StackPush(StackNode*& fList, string value);
string StackPop(StackNode*& head);
void StackFromFile(string& str, StackNode*& head);
string StackToString(StackNode*& head, const string& name);
void StackQuery(const MyVector<string>& words, const string& filename);

// работа с хеш-таблицей
struct Nod {
    string key;
    string value;
    Nod* next;
};

struct MyHashT {
    Nod** data;
    int len;
    int cap;
    int LoadFactor;
};

int HashCode(const string& key);
MyHashT* CreateMap(int initCapacity, int initLoadFactor);
void Expansion(MyHashT& map);
void CollisionManage(MyHashT& map, int index, const string& key, const string& value);
void AddMap(MyHashT& map, const string& key, const string& value);
void DeleteMap(MyHashT& map, const string& key);
void DestroyMap(MyHashT& map);
MyHashT* HashTFromFile(string& str);
string HashTToString(const MyHashT& map, const string& name);
void HashTableQuery(const MyVector<string>& words, const string& filename);

// работа с деревом
struct TreeNode {
    int value;
    int height;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const int val) : value(val), height(1), left(nullptr), right(nullptr) {}
};

int height(TreeNode* N);
void updateHeight(TreeNode* node);
int getBalance(TreeNode* node);
TreeNode* rotateRight(TreeNode* y);
TreeNode* rotateLeft(TreeNode* x);
TreeNode* balanceNode(TreeNode* node);
TreeNode* TreeInsert(TreeNode* node, int value);
TreeNode* GetTree(TreeNode* node, int value);
TreeNode* getMinValueNode(TreeNode* node);
TreeNode* DeleteTree(TreeNode* node, int value);
TreeNode* unserializeSS(istringstream& ss);
void TreeToString(TreeNode* node, string& resStr);
void TreeQuery(const MyVector<string>& words, const string& filename);
