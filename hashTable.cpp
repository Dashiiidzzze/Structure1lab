#include "header.h"


// хэш функция для string
int HashCode(const string& key) {
    unsigned long hash = 5381;
    int c = 0;
    for (char ch : key) {
        hash = ((hash << 5) + hash) + ch; /* hash * 33 + c */
    }
    return hash;
}

// инициализация хэш таблицы
MyHashT* CreateMap(int initCapacity, int initLoadFactor) {
    if (initCapacity <= 0 || initLoadFactor <= 0 || initLoadFactor > 100) {
        throw runtime_error("Index out of range");
    }

    MyHashT* map = new MyHashT;
    map->data = new Nod*[initCapacity];
    for (int i = 0; i < initCapacity; i++) {
        map->data[i] = nullptr;
    }

    map->len = 0;
    map->cap = initCapacity;
    map->LoadFactor = initLoadFactor;
    return map;
}

// расширение
void Expansion(MyHashT& map) {
    int newCap = map.cap * 2;
    Nod** newData = new Nod*[newCap];
    for (int i = 0; i < newCap; i++) {
        newData[i] = nullptr;
    }
    // проход по всем ячейкам
    for (int i = 0; i < map.cap; i++) {
        Nod* curr = map.data[i];
        // проход по парам коллизионных значений и обновление
        while (curr != nullptr) {
            Nod* next = curr->next;
            int index = HashCode(curr->key) % newCap;
            if (newData[index] != nullptr) {
                Nod* temp = newData[index]; //              ЗАТЕСТИТЬ!!!!!!!!!
                while (temp->next!= nullptr) {
                    temp = temp->next;
                }
                temp->next = curr;
            } else {
                curr->next = newData[index];
                newData[index] = curr;
                //curr = next;
            }
            curr = next;
        }
    }

    delete[] map.data;

    map.data = newData;
    map.cap = newCap;
}


// обработка коллизий
void CollisionManage(MyHashT& map, int index, const string& key, const string& value) {
    Nod* newNod = new Nod{key, value, nullptr};
    Nod* curr = map.data[index];
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newNod;
}


// добавление элементов
void AddMap(MyHashT& map, const string& key, const string& value) {
    if ((map.len + 1) * 100 / map.cap >= map.LoadFactor) {
        Expansion(map);
    }
    int index = HashCode(key) % map.cap;
    Nod* temp = map.data[index];
    if (temp != nullptr) {
        if (temp->key == key) {
            // обновить значение ключа
            temp->value = value;
            map.data[index] = temp;
        } else {
            CollisionManage(map, index, key, value);
        }
    } else {
        Nod* newNod = new Nod{key, value, map.data[index]};
        map.data[index] = newNod;
        map.len++;
    }

}

// поиск элементов по ключу
string GetMap(const MyHashT& map, const string& key) {
    int index = HashCode(key) % map.cap;
    Nod* curr = map.data[index];
    while (curr != nullptr) {
        if (curr->key == key) {
            return curr->value;
        }
        curr = curr->next;
    }

    throw runtime_error("Key not found");
}


// удаление элементов
void DeleteMap(MyHashT& map, const string& key) {
    int index = HashCode(key) % map.cap;
    Nod* curr = map.data[index];
    Nod* prev = nullptr;
    while (curr != nullptr) {
        if (curr->key == key) {
            if (prev == nullptr) {
                map.data[index] = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            map.len--;
            return;
        }
        prev = curr;
        curr = curr->next; 
    }
    throw runtime_error("Key not found");
}

// очистка памяти
void DestroyMap(MyHashT& map) {
    for (int i = 0; i < map.cap; i++) {
        Nod* curr = map.data[i];
        while (curr != nullptr) {
            Nod* next = curr->next;
            delete curr;
            curr = next;
        }
    }
    delete[] map.data;
    map.data = nullptr;
    map.len = 0;
    map.cap = 0;
}


// создание массива, сохраненного в файле
MyHashT* HashTFromFile(string& str) {
    MyVector<string>* vec = Split(str, ',');
    MyHashT* result = CreateMap(vec->len*2, 50);
    if (str != "") {
        for (int i = 0; i < vec->len; i++) {
            MyVector<string>* keyVal = Split(vec->data[i], '-');
            AddMap(*result, keyVal->data[0], keyVal->data[1]);
        }
    }
    return result;
}

// создание строки из массива
string HashTToString(const MyHashT& map, const string& name) {
    string resStr = name + " ";
    bool comma = false;
    for (int i = 0; i < map.cap; i++) {
        Nod* curr = map.data[i];
        while (curr != nullptr) {
            if (comma) {
                resStr += ",";
            }
            resStr += curr->key + "-" + curr->value;
            comma = true;
            curr = curr->next;
        }
    }
    return resStr;
}

void HashTableQuery(const MyVector<string>& words, const string& filename) {
    string doing = Substr(words.data[0], 1, words.data[0].size());
    string arr;
    // чтение массива из файла
    try {
        arr = DataRead(words.data[1], filename, "hashtable", "tree");
    } catch (const exception& err) {
        cerr << err.what() << endl;
        return;
    }
    MyHashT* initialArr = HashTFromFile(arr);
    // создание массива из файла

    bool revriting = false;
    if (doing == "SET") { // добавление
        AddMap(*initialArr, words.data[2], words.data[3]);
        cout << "-> " << words.data[2] << " - " << words.data[3] << endl;
        revriting = true;

    } else if (doing == "GET") { // получение по ключу
        cout << "-> " << GetMap(*initialArr, words.data[2]) << endl;
        cout << "-> " << HashTToString(*initialArr, words.data[1]) << endl;
        
    } else if (doing == "DEL") { // удаление по ключу
        DeleteMap(*initialArr, words.data[2]);
        cout << "-> " <<  words.data[2] << endl;
        revriting = true;

    } else {
        cout << "Unknown command" << endl;
        return;
    }
    if (revriting) {
        string newStr = HashTToString(*initialArr, words.data[1]);
        string oldStr = words.data[1];
        if (arr != "") {
            oldStr = oldStr + " " + arr;
        }
        Rewrite(filename, oldStr, newStr, "hashtable", "tree");
    }
}