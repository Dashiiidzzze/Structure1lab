#include "header.h"

// Возвращает длину строки
int Strlen(const string &str) {
    int len = 0;
    while (str[len]!= '\0') {
        len++;
    }
    return len;
}


// Возвращает подстроку от start до end (не включая end)
string Substr(const string &str, int start, int end) {
    string result;
    for (int i = start; i < end; i++) {
        result += str[i];
    }
    return result;
}

// Разбивает строку на слова с разделителем delim.
MyVector<string>* Split(const string &str, char delim) {
    int index = 0;
    MyVector<string>* words = CreateVector<string>(10, 75);
    int length = Strlen(str);

    while (true) {
        int delimIndex = index;
        while (str[delimIndex] != delim && delimIndex != length) delimIndex++;

        string word = Substr(str, index, delimIndex);
        AddVector(*words, word);
        index = delimIndex + 1;
        if (delimIndex == length) break;
    }

    return words;
}


// чтение??????????????????????????????????????????????????????????
string DataRead(const string& name, const string& fileName, const string& structure, const string& nextStructure) {
    ifstream file(fileName);
    if (!file.is_open()) {
        throw runtime_error("Failed to open " + fileName);
    }
    string line;
    bool massiv = false;
    while (getline(file, line)) {
        if (line == structure) {
            massiv = true;
        } else if (line == nextStructure) {
            throw runtime_error("Massiv with name " + name + " is not found");
            return "";
        } else if (massiv) {
            MyVector<string>* str = Split(line, ' ');
            if (str->data[0] == name) {
                return str->data[1];
            }
        }
    }
    return "";
}


// перезапись в файл
void Rewrite(const string& fileName, const string& oldStr, const string& newStr, const string& structure, const string& nextStructure) {
    ifstream file(fileName);
    if (!file.is_open()) {
        throw runtime_error("Failed to open " + fileName);
    }
    ofstream tempFile("temp_" + fileName);
    // перезапись
    bool massiv = false;
    string line;
    while (getline(file, line)) {
        if (line == structure) {
            massiv = true;
        } else if (line == nextStructure) {
            massiv = false;
        } else if (massiv) {
            if (line == oldStr) {
                tempFile << newStr << endl;
                continue;
            }
        }

        tempFile << line << endl;
    }
    tempFile.close();
    file.close();
    // удаление старого файла
    if (remove((fileName).c_str()) != 0) {
        cerr << "Error deleting file" << endl;
        return;
    }
    if (rename(("temp_" + fileName).c_str(), (fileName).c_str()) != 0) {
        cerr << "Error renaming file" << endl;
        return;
    }
}