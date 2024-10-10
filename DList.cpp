#include "header.h"

// вывод
ostream& operator << (ostream& os, DListNode* tail) {
    DListNode* curr = tail;
    while (curr != nullptr) {
        os << curr->value  << setw(10);
        curr = curr->prev;
    }
    return os;
}

// добавление в голову
void AddDlist(DListNode*& head, DListNode*& tail, string value) {
    DListNode* newNode = new DListNode(nullptr, value, head);
    if (head == nullptr) {
        tail = newNode;
    } else {
        head->prev = newNode;
    }
    head = newNode;
}

// добавление push (добавляем в конец)
void AddToTailDList(DListNode*& head, DListNode*& tail, string value) {
    DListNode* newNode = new DListNode(nullptr, value, nullptr);
    if (tail == nullptr) {
        head = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
    }
    tail = newNode;
}

// удаление pop (удаляем из начала)
string DeleteFromHeadDList(DListNode*& head, DListNode*& tail) {
    if (head == nullptr) throw runtime_error("Queue is empty");
    DListNode* temp = head;
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

// удаление с хвоста
void DeleteFromTailDList(DListNode*& head, DListNode*& tail) {
    if (tail == nullptr) throw runtime_error("Queue is empty");
    DListNode* temp = tail;
    string value = temp->value;
    tail = tail->prev;
    if (tail == nullptr) {
        head = nullptr;
    } else {
        tail->next = nullptr;
    }
    delete temp;
}

// удаление по значению
void DeleteByValueDList(DListNode*& head, DListNode*& tail, string value) {
    DListNode* curr = head;
    while (curr != nullptr) {
        if (curr->value == value) {
            if (curr->prev != nullptr) {
                curr->prev->next = curr->next;
            } else {
                head = curr->next;
            }
            if (curr->next != nullptr) {
                curr->next->prev = curr->prev;
            } else {
                tail = curr->prev;
            }
            delete curr;
            return;
        }
        curr = curr->next;
    }
    throw runtime_error("Value not found");
}

// поиск по значению
bool SearchByValueDlist(DListNode*& head, DListNode*& tail, string value) {
    DListNode* curr = head;
    while (curr != nullptr) {
        if (curr->value == value) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// создание очереди
void DListFromFile(string& str, DListNode*& head, DListNode*& tail) {
    MyVector<string>* vec = Split(str, ',');
    if (str != "") {
        for (int i = vec->len - 1; i >= 0; i--) {
            AddDlist(head, tail, vec->data[i]);
        }
    }
}


// создание строки из очереди
string DListToString(DListNode*& tail, const string& name) {
    string resStr = name + " ";
    DListNode* curr = tail;
    while (curr != nullptr) {
        resStr += curr->value;
        if (curr->prev != nullptr) {
            resStr += ",";
        }
        curr = curr->prev;
    }
    return resStr;
}


// обработка запроса для массива
void DListQuery(const MyVector<string>& words, const string& filename) {
    string doing = Substr(words.data[0], 2, words.data[0].size());
    string arr;
    // чтение массива из файла
    try {
        arr = DataRead(words.data[1], filename, "list", "queue");
    } catch (const exception& err) {
        cerr << err.what() << endl;
        return;
    }

    DListNode* head = nullptr;
    DListNode* tail = nullptr;
    // создание массива из файла
    DListFromFile(arr, head, tail);

    // обработка запроса для односвязного списка
    bool revriting = false;
    if (doing == "PUSHHEAD") {// добавление в голову
        AddDlist(head, tail, words.data[2]);
        cout << "-> " << words.data[2] << endl;
        revriting = true;

    } else if (doing == "PUSHTAIL") {// добавление в хвост
        AddToTailDList(head, tail, words.data[2]);
        cout << "-> " << words.data[2] << endl;
        revriting = true;

    } else if (doing == "DELHEAD") {// удаление с головы
        DeleteFromHeadDList(head, tail);
        cout << "-> " << tail << endl;
        revriting = true;

    } else if (doing == "DELTAIL") {// удаление с хвоста
        DeleteFromTailDList(head, tail);
        cout << "-> " << tail << endl;
        revriting = true;

    } else if (doing == "DELVALUE") {// удаление по значению
        DeleteByValueDList(head, tail, words.data[2]);
        cout << "-> " << words.data[2] << endl;
        revriting = true;

    } else if (doing == "GETVAL") {// поиск по значению
        cout << "-> " << (SearchByValueDlist(head, tail, words.data[2]) ? "Found" : "Not Found") << endl;
    } else if (doing == "GET") {// чтение из файла
        cout << "-> " << tail << endl;
    } else {
        cout << "Unknown command" << endl;
        return;
    }

    if (revriting) {
        string newStr = DListToString(tail, words.data[1]);
        string oldStr = words.data[1];
        if (arr != "") {
            oldStr = oldStr + " " + arr;
        }
        Rewrite(filename, oldStr, newStr, "list", "queue");
    }
}
