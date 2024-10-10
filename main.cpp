#include <iostream>
#include <filesystem>

#include "vectorDas.h"
#include "header.h"

using namespace std;

int QueryParsing(const string& filename, const string& query) {
    MyVector<string>* words = Split(query, ' ');
    cout << *words << endl;
    if (words->data[0][0] == 'M') {
        MasQuery(*words, filename);
    } else if (words->data[0][0] == 'L' && words->data[0][1] == 'F') {
        FListQuery(*words, filename);
    }  else if (words->data[0][0] == 'L' && words->data[0][1] == 'D') {
        //DListQuery(*words, filename);
    } else if (words->data[0][0] == 'Q') {
        QueueQuery(*words, filename);
    } else if (words->data[0][0] == 'S') {
        StackQuery(*words, filename);
    } else if (words->data[0][0] == 'H') {
        HashTableQuery(*words, filename);
    } else if (words->data[0][0] == 'T') {
        TreeQuery(*words, filename);
    } else if (words->data[0] == "PRINT") {
        
    } else {
        cout << "Unknown command" << endl;
        return 1;
    }
    return 0;
}

// проверка введенных параметров
int ParameterParsing(const int argc, char* argv[]) {
    if (string(argv[1]) == "--file" && string(argv[3]) == "--query") {
        if (!filesystem::exists(argv[2])) {
            throw runtime_error("db file not found");
            return 1;
        } else {
            QueryParsing(argv[2], argv[4]);
        }
    } else {
        throw runtime_error("Invalid parameters");
        return 1;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    try {
        ParameterParsing(argc, argv);
    } catch (const exception& err) {
        cerr << err.what() << endl;
        return 1;
    }
    return 0;
}