#include "header.h"

// вывод
ostream& operator << (ostream& os, const Massiv& vec) {
    for (int i = 0; i < vec.len; i++) {
        os << vec.data[i];
        if (i < vec.len - 1) cout << setw(25);
    }
    return os;
} 

// создание
Massiv* CreateMassiv(int initCapacity, int initLoadFactor) {
    if (initCapacity <= 0 || initLoadFactor <= 0 || initLoadFactor > 100) {
        throw runtime_error("Index out of range");
    }

    Massiv* vec = new Massiv;
    vec->data = new string[initCapacity];
    vec->len = 0;
    vec->cap = initCapacity;
    vec->LoadFactor = initLoadFactor;
    return vec;
}

// расширение
void ExpansMassiv(Massiv& vec) {
    int newCap = vec.cap * 2;
    string* newData = new string[newCap];
    for (int i = 0; i < vec.len; i++) {     //копируем данные из старого массива в новый
        newData[i] = vec.data[i];
    }
    delete[] vec.data;                      // очистка памяти
    vec.data = newData;
    vec.cap = newCap;
}

// добавление в конец массива
void AddMassiv(Massiv& vec, string value) {
    if ((vec.len + 1) * 100 / vec.cap >= vec.LoadFactor) { //обновление размера массива
        ExpansMassiv(vec);
    }
    vec.data[vec.len] = value;
    vec.len++;
}

// получение по индексу же и так работает a.data[i]

// удаление по индексу
void DeleteMassiv(Massiv& vec, int index) {
    if (index < 0 || index >= vec.len) {
        throw runtime_error("Index out of range");
    }

    for (int i = index; i < vec.len - 1; i++) {
        vec.data[i] = vec.data[i + 1];
    }

    vec.len--;
}

// замена по индексу
void ReplaceMassiv(Massiv& vec, int index, string value) {
    if (index < 0 || index >= vec.len) {
        throw runtime_error("Index out of range");
    }
    vec.data[index] = value;
}

// длина массива и так работает a->len

void PushAtIndex(Massiv& vec, int index, string value) {
    if (index < 0 || index > vec.len) {
        throw runtime_error("Index out of range");
    }
    if ((vec.len + 1) * 100 / vec.cap >= vec.LoadFactor) { //обновление размера массива
        ExpansMassiv(vec);
    }
    for (int i = vec.len; i >= index; i--) {
        vec.data[i + 1] = vec.data[i];
    }
    vec.data[index] = value;
    vec.len++;
}


// создание массива, сохраненного в файле
Massiv* MassivFromFile(string& str) {
    MyVector<string>* vec = Split(str, ',');
    Massiv* result = CreateMassiv(vec->len*2, 50);
    if (str != "") {
        for (int i = 0; i < vec->len; i++) {
            AddMassiv(*result, vec->data[i]);
        }
    }
    return result;
}

// создание строки из массива
string MassToString(const Massiv& vec, const string& name) {
    string resStr = name + " ";
    for (int i = 0; i < vec.len; i++) {
        resStr = resStr + vec.data[i];
        if (i < vec.len - 1) {
            resStr = resStr + ",";
        }
    }
    return resStr;
}

// обработка запроса для массива
void MasQuery(const MyVector<string>& words, const string& filename) {
    string doing = Substr(words.data[0], 1, words.data[0].size());
    string arr;
    // чтение массива из файла
    try {
        arr = DataRead(words.data[1], filename, "array", "list");
    } catch (const exception& err) {
        cerr << err.what() << endl;
        return;
    }
    // создание массива из файла
    Massiv* initialArr = MassivFromFile(arr);

    QueueNode* nach = nullptr;
    QueueNode* con = nullptr;
    bool revriting = false;
    if (doing == "PUSH") { // добавление в конец
        AddMassiv(*initialArr, words.data[2]);
        cout << "-> " << words.data[2] << endl;
        revriting = true;
    } else if (doing == "PUSHATINDEX") {
        PushAtIndex(*initialArr, stoi(words.data[2]), words.data[3]);
        cout << "-> " << words.data[3] << endl;
        revriting = true;
    } else if (doing == "GETVAL") {// получение по индексу
        cout << "-> " << initialArr->data[stoi(words.data[2])] << endl;
    } else if (doing == "DEL") { // удаление по индексу
        DeleteMassiv(*initialArr, stoi(words.data[2]));
        cout << "-> " << words.data[2] << endl;
        revriting = true;
    } else if (doing == "REPLACE") { // замена по индексу (MREPLACE A 2 hehe)
        ReplaceMassiv(*initialArr, stoi(words.data[2]), words.data[3]);
        cout << "-> " << words.data[3] << endl;
        revriting = true;
    } else if (doing == "LEN") { // длина массива
        cout << "-> " << initialArr->len << endl;
    } else if (doing == "GET") { // чтение?????
        cout << "-> " << *initialArr << endl;
    } else {
        cout << "Unknown command" << endl;
        return;
    }

    if (revriting) {
        string newStr = MassToString(*initialArr, words.data[1]);
        string oldStr = words.data[1];
        if (arr != "") {
            oldStr = oldStr + " " + arr;
        }
        Rewrite(filename, oldStr, newStr, "array", "list");
    }
}