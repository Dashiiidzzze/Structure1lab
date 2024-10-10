#include "header.h"

// Функция для печати дерева
void printTree(string& result, TreeNode* tree, int depth = 0, string prefix = "") {
    if (tree == nullptr) {
        return;
    }

    // Вывод правое поддерево
    if (tree->right != nullptr) {
        printTree(result, tree->right, depth + 1, prefix + "\t");
    }

    // Выводим текущий узел
    result += prefix;
    if (depth > 0) {
        result += "───";
    }
    result += "(" + to_string(tree->value) + ")\n";

    // Вывод левое поддерево
    if (tree->left != nullptr) {
        printTree(result, tree->left, depth + 1, prefix + "\t");
    }
}

ostream& operator<<(ostream& os, TreeNode*& tree) {
    string stringTree = "";
    printTree(stringTree, tree);
    os << stringTree;
    return os;
}

// высота узла N
int height(TreeNode* N) {
    if (N == nullptr) return 0;
    return N->height;
}


// Oбновления высоты узла
void updateHeight(TreeNode* node) {
    if (node != nullptr) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }
}

// Получение значения баланса узла
int getBalance(TreeNode* node) {
    return node == nullptr ? 0 : height(node->left) - height(node->right);
}

// Правое вращение
TreeNode* rotateRight(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Левое вращение
TreeNode* rotateLeft(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Балансировка узла
TreeNode* balanceNode(TreeNode* node) {
    updateHeight(node);
    int balance = getBalance(node);

    // Левое вращение, если баланс > 1 и вставка произошла в левое поддерево
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }

    // Правое вращение, если баланс < -1 и вставка произошла в правое поддерево
    if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Левое-правое вращение, если баланс > 1 и вставка произошла в правое поддерево левого поддерева
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Правое-левое вращение, если баланс < -1 и вставка произошла в левое поддерево правого поддерева
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Вставка узла с балансировкой
TreeNode* TreeInsert(TreeNode* node, int value) {
    if (node == nullptr) {
        return new TreeNode(value);
    }

    if (value < node->value) {
        node->left = TreeInsert(node->left, value);
    } else if (value > node->value) {
        node->right = TreeInsert(node->right, value);
    } else {
        return node;
    }

    return balanceNode(node);
}


// поиск по значению
TreeNode* GetTree(TreeNode* node, int value) {
    if (node == nullptr || node->value == value) {
        return node;
    }

    if (value < node->value) {
        return GetTree(node->left, value);
    } else {
        return GetTree(node->right, value);
    }
}

 // Получение минимального значения узла
TreeNode* getMinValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Удаление узла
TreeNode* DeleteTree(TreeNode* node, int value) {
    if (node == nullptr) {
        return node;
    }

    // Находим узел для удаления
    if (value < node->value) {
        node->left = DeleteTree(node->left, value);
    } else if (value > node->value) {
        node->right = DeleteTree(node->right, value);
    } else {
        // Узел найден
        if (node->left == nullptr || node->right == nullptr) {
            TreeNode* temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
                delete temp;
        } else {
            TreeNode* temp = getMinValueNode(node->right);
            node->value = temp->value;
            node->right = DeleteTree(node->right, temp->value);
        }
    }

    if (node == nullptr) {
        return node;
    }

    return balanceNode(node);
}


// Рекурсивная функция для восстановления дерева
TreeNode* TreeFromFile(istringstream& ss) {
    string val;
    getline(ss, val, '-');

    if (val == "*") {
        return nullptr;  // если встречаем символ пустого узла
    }

    TreeNode* node = new TreeNode(stoi(val));   // создаём новый узел
    node->left = TreeFromFile(ss);              // восстанавливаем левое поддерево
    node->right = TreeFromFile(ss);             // восстанавливаем правое поддерево

    return node;
}

// запись структуры дерева в строку
void TreeToString(TreeNode* node, string& resStr) {
    if (node == nullptr) {
        resStr += "*-";  // символ для обозначения пустого узла
        return;
    }
    resStr += to_string(node->value) + "-";     // записываем значение узла
    TreeToString(node->left, resStr);           // левое поддерево
    TreeToString(node->right, resStr);          // правое поддерево
}
    


void TreeQuery(const MyVector<string>& words, const string& filename) {
    string doing = Substr(words.data[0], 1, words.data[0].size());
    string arr;
    // чтение массива из файла
    try {
        arr = DataRead(words.data[1], filename, "tree", "end");
    } catch (const exception& err) {
        cerr << err.what() << endl;
        return;
    }

    // создание массива из файла
    istringstream ss(arr);
    TreeNode* initialTree = TreeFromFile(ss);

    bool revriting = false;
    if (doing == "INSERT") { // добавление
        initialTree = TreeInsert(initialTree, stoi(words.data[2]));
        cout << "-> " << words.data[2] << " - " << words.data[3] << endl;
        revriting = true;

    } else if (doing == "GET") { // получение по ключу
        cout << "-> " << GetTree(initialTree, stoi(words.data[2])) << endl;
        
    } else if (doing == "DEL") { // удаление по ключу
        initialTree = DeleteTree(initialTree, stoi(words.data[2]));
        cout << "-> " <<  words.data[2] << endl;
        revriting = true;

    } else {
        cout << "Unknown command" << endl;
        return;
    }

    cout << initialTree << endl;


    if (revriting) {
        string newStr = words.data[1];
        if (initialTree != nullptr) {
            newStr += " ";
            TreeToString(initialTree, newStr);
        }
        string oldStr = words.data[1];
        if (arr != "") {
            oldStr = oldStr + " " + arr;
        }
        Rewrite(filename, oldStr, newStr, "tree", "end");
    }
}
