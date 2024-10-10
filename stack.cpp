#include "header.h"

// вывод
ostream& operator << (ostream& os, StackNode* head) {
    StackNode* curr = head;
    while (curr != nullptr) {
        os << curr->value << setw(10);
        curr = curr->next;
    }
    return os;
}

// добавление push
void StackPush(StackNode*& fList, string value) {
    StackNode* newNode = new StackNode{value, fList};
    fList = newNode;
}


// удаление pop
string StackPop(StackNode*& head) {
    if (head == nullptr) {
        throw runtime_error("Stack is enpty");
        return "";
    } if (head->next == nullptr) {
        string value = head->value;
        delete head;
        head = nullptr;
        return value;
    }
    StackNode* temp = head;
    head = head->next;
    string value = temp->value;
    delete temp;
    return value;
}

// чтение

// создание стека из файла
void StackFromFile(string& str, StackNode*& head) {
    MyVector<string>* vec = Split(str, ',');
    if (str != "") {
        for (int i = vec->len - 1; i >= 0; i--) {
            StackPush(head, vec->data[i]);
        }
    }
    delete vec;
}


// создание строки из стека
string StackToString(StackNode*& head, const string& name) {
    if (head == nullptr) {
        return name;
    }
    string resStr = name + " ";
    StackNode* curr = head;
    while (curr->next != nullptr) {
        resStr = resStr + curr->value + ",";
        curr = curr->next;
    }
    resStr = resStr + curr->value;
    return resStr;
}



void StackQuery(const MyVector<string>& words, const string& filename) {
    string doing = Substr(words.data[0], 1, words.data[0].size());
    string arr;
    // чтение массива из файла
    try {
        arr = DataRead(words.data[1], filename, "stack", "hashtable");
    } catch (const exception& err) {
        cerr << err.what() << endl;
        return;
    }

    StackNode* initialArr = nullptr;
    StackFromFile(arr, initialArr);
    // создание массива из файла

    bool revriting = false;
    if (doing == "PUSH") { // добавление в конец
        StackPush(initialArr, words.data[2]);
        cout << "-> " << words.data[2] << endl;
        revriting = true;

    } else if (doing == "POP") {
        StackPop(initialArr);
        cout << "-> " << initialArr << endl;
        revriting = true;

    } else {
        cout << "Unknown command" << endl;
        return;
    }
    if (revriting) {
        string newStr = StackToString(initialArr, words.data[1]);
        string oldStr = words.data[1];
        if (arr != "") {
            oldStr = oldStr + " " + arr;
        }
        Rewrite(filename, oldStr, newStr, "stack", "hashtable");
    }
}
/*

int main() {
    StackNode* sss = nullptr;
    StackPush(sss, "foo");
    StackPush(sss, "bar");
    StackPush(sss, "fff");
    cout << StackPop(sss) << endl;
    cout << StackPop(sss) << endl;
    cout << StackPop(sss) << endl;
    cout << StackPop(sss) << endl;

    return 0;
}*/