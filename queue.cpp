#include "header.h"


// вывод
ostream& operator << (ostream& os, QueueNode* tail) {
    QueueNode* curr = tail;
    while (curr != nullptr) {
        os << curr->value  << setw(10);
        curr = curr->prev;
    }
    return os;
}


// добавление push (добавляем в конец)
void QueuePush(QueueNode*& head, QueueNode*& tail, string value) {
    QueueNode* newNode = new QueueNode(nullptr, value, nullptr);
    if (tail == nullptr) {
        head = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
    }
    tail = newNode;
}

// удаление pop (удаляем из начала)
string QueuePop(QueueNode*& head, QueueNode*& tail) {
    if (head == nullptr) throw runtime_error("Queue is empty");
    QueueNode* temp = head;
    string value = temp->value;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    } else {
        head->prev = nullptr;
    }
    delete temp;
    return value;
}


// создание очереди
void QueueFromFile(string& str, QueueNode*& head, QueueNode*& tail) {
    MyVector<string>* vec = Split(str, ',');
    if (str != "") {
        for (int i = vec->len - 1; i >= 0; i--) {
            QueuePush(head, tail, vec->data[i]);
        }
    }
}


// создание строки из очереди
string QueueToString(QueueNode*& tail, const string& name) {
    string resStr = name + " ";
    QueueNode* curr = tail;
    while (curr != nullptr) {
        resStr += curr->value;
        if (curr->prev != nullptr) {
            resStr += ",";
        }
        curr = curr->prev;
    }
    return resStr;
}


void QueueQuery(const MyVector<string>& words, const string& filename) {
    string doing = Substr(words.data[0], 1, words.data[0].size());
    string arr;
    // чтение массива из файла
    try {
        arr = DataRead(words.data[1], filename, "queue", "stack");
    } catch (const exception& err) {
        cerr << err.what() << endl; 
        return;
    }

    QueueNode* nach = nullptr;
    QueueNode* con = nullptr;
    // создание массива из файла
    QueueFromFile(arr, nach, con);

    bool revriting = false;
    if (doing == "PUSH") { // добавление в конец
        QueuePush(nach, con, words.data[2]);
        cout << "-> " << words.data[2] << endl;
        revriting = true;

    } else if (doing == "POP") {
        QueuePop(nach, con);
        cout << "-> " << con << endl;
        revriting = true;

    } else {
        cout << "Unknown command" << endl;
        return;
    }
    if (revriting) {
        string newStr = QueueToString(con, words.data[1]);
        string oldStr = words.data[1];
        if (arr != "") {
            oldStr = oldStr + " " + arr;
        }
        Rewrite(filename, oldStr, newStr, "queue", "stack");
    }
}

/*
int main() {
    QueueNode* nach = nullptr;
    QueueNode* con = nullptr;
    QueuePush(nach, con, "foo");
    cout << 1 << endl;
    QueuePush(nach, con, "fo2");
    cout << 2 << endl;
    QueuePush(nach, con, "fo3");
    cout << 3 << endl;
    QueuePush(nach, con, "fo4");
    cout << QueuePop(nach, con) << "  khghgkjg" << endl;
    cout << 4 << endl;
    QueueNode* qqq2 = nach;
    while (qqq2 != NULL) {
        cout << qqq2->value << endl;
        qqq2 = qqq2->next;
    }
}*/