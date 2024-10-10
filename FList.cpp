#include "header.h"


// вывод
ostream& operator << (ostream& os, FListNode* head) {
    FListNode* curr = head;
    while (curr->next != nullptr) {
        os << curr->value << setw(16);
        curr = curr->next;
    }
    return os;
}

//добавление в голову
void AddFlist(FListNode*& fList, string& value) {
    FListNode* newNode = new FListNode{value, nullptr};
    newNode->next = fList;
    fList = newNode;
}

// добавление в хвост
void AddToTailFList(FListNode*& fList, string& value) {
    FListNode* newNode = new FListNode{value, nullptr};
    if (fList == nullptr) {
        fList = newNode; 
    } else {
        FListNode* temp = fList;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// удаление с головы
void DeleteFromHead(FListNode*& head) {
    if (head == nullptr) return;
    FListNode* temp = head;
    head = head->next;
    delete temp;
}

// удаление с хвоста
void DeleteFromTail(FListNode*& head) {
    if (head == nullptr) return;
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    FListNode* curr = head;
    while (curr->next->next != nullptr) {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = nullptr;
}

// удаление по значению
void DeleteByValue(FListNode*& head, string& value) {
    if (head == nullptr) {
        return;
    }
    if (head->value == value) {
        DeleteFromHead(head);
        return;
    }
    FListNode* curr = head;
    while (curr->next != nullptr && curr->next->value != value) {
        curr = curr->next;
    }
    if (curr->next != nullptr) {
        FListNode* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;
    }
}

// поиск по значению
bool SearchByValue(FListNode*& head, const string& value) {
    if (head == nullptr) {
        return false;
    }
    FListNode* curr = head;
    while (curr->next->next != nullptr) {
        if ( curr->next->value == value) return true;
        curr = curr->next;
    }
    return false;
}

// чтение ?????????????????????????????????????????????????


FListNode* FListFromFile(string& str) {
    MyVector<string>* vec = Split(str, ',');
    FListNode* result = new FListNode;
    if (str != "") {
        for (int i = vec->len - 1; i >= 0; i--) {
            AddFlist(result, vec->data[i]);
        }
    }
    return result;
}

// создание строки из массива
string FListToString(FListNode* vec, const string& name) {
    string resStr = name + " ";
    FListNode* curr = vec;
    while (curr->next->next != nullptr) {
        resStr = resStr + curr->value + ",";
        curr = curr->next;
    }
    resStr = resStr + curr->value;
    return resStr;
}

// обработка запроса для массива
void FListQuery(const MyVector<string>& words, const string& filename) {
    string doing = Substr(words.data[0], 2, words.data[0].size());
    string arr;
    // чтение массива из файла
    try {
        arr = DataRead(words.data[1], filename, "list", "queue");
    } catch (const exception& err) {
        cerr << err.what() << endl;
        return;
    }
    // создание массива из файла
    FListNode* initialArr = FListFromFile(arr);
    // обработка запроса для односвязного списка
    bool revriting = false;
    if (doing == "PUSHHEAD") {// добавление в голову
        AddFlist(initialArr, words.data[2]);
        cout << "-> " << words.data[2] << endl;
        revriting = true;

    } else if (doing == "PUSHTAIL") {// добавление в хвост
        AddToTailFList(initialArr, words.data[2]);
        cout << "-> " << words.data[2] << endl;
        revriting = true;

    } else if (doing == "DELHEAD") {// удаление с головы
        DeleteFromHead(initialArr);
        cout << "-> " << initialArr << endl;
        revriting = true;

    } else if (doing == "DELTAIL") {// удаление с хвоста
        DeleteFromTail(initialArr);
        cout << "-> " << initialArr << endl;
        revriting = true;

    } else if (doing == "DELVALUE") {// удаление по значению
        DeleteByValue(initialArr, words.data[2]);
        cout << "-> " << words.data[2] << endl;
        revriting = true;

    } else if (doing == "GETVAL") {// поиск по значению
        cout << "-> " << SearchByValue(initialArr, words.data[2]) << endl;
    } else if (doing == "GET") {// чтение из файла
        cout << "-> " << initialArr << endl;
    } else {
        cout << "Unknown command" << endl;
        return;
    }

    if (revriting) {
        string newStr = FListToString(initialArr, words.data[1]);
        string oldStr = words.data[1];
        if (arr != "") {
            oldStr = oldStr + " " + arr;
        }
        Rewrite(filename, oldStr, newStr, "list", "queue");
    }
}


/*
int main() {
    cout << 0 << endl;
    FListNode* head = new FListNode{"apple", nullptr};
    cout << 1 << endl;
    //DeleteFromTail(head);
    cout << head << endl;
    cout << 2 << endl;
    AddToTailFList(head, "kiwi");
    cout << 3 << endl;
    AddToTailFList(head, "mango");
    cout << 4 << endl;
    AddToTailFList(head, "pear");
    //DeleteFromHead(head);
    cout << 5 << endl;
    //PrintFlist(head);
    cout << head << endl;
    cout << 6 << endl;
    AddFlist(head, "das");
    //DeleteFromTail(head);
    cout << 7 << endl;
    DeleteByValue(head, "ma");
    //PrintFlist(head);
    cout << head << endl;
    cout << SearchByValue(head, "mago") << endl;
    cout << 8 << endl;


    return 0;
}*/