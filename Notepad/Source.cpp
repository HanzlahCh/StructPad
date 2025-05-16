#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <Windows.h>

using namespace std;

struct Node {
    char value;
    int color;
    int lineNumber;
    Node* up;
    Node* down;
    Node* left;
    Node* right;

    Node(char val, int lineNumber) : value(val), color(7), lineNumber(lineNumber), up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}
};

class Editor {
private:
    Node* head;
    int maxLines;
    int maxLineLength;

public:
    Editor(int maxLines = 18, int maxLineLength = 100)
        : head(nullptr), maxLines(maxLines), maxLineLength(maxLineLength) {
    }

    Node* getHead()
    {
        return this->head;
    }

    bool insertData(char c, int& row, int& col, bool isEnterPressed, int& wordCount, int& lineCount, int* charCount)
    {
        if (wordCount >= (maxLines - 1) * maxLineLength)
        {
            return false;
        }

        if (row >= maxLines - 2 && col >= maxLineLength)
        {
            return false;
        }
        static bool first = false;

        Node* newNode = new Node(c, row);

        Node* placeFinder = head;
        Node* next = head;
        bool founded = false;

        for (int i = 0; i < row && next; i++)
        {
            next = next->down;
        }

        for (int i = 0; i < col && placeFinder; i++)
        {
            if (!(placeFinder->right) && next->down)
            {
                founded = true;
                break;
            }
            placeFinder = placeFinder->right;

        }
        for (int i = 0; i < row && placeFinder; i++)
        {
            placeFinder = placeFinder->down;
        }

        int coulumn = col;
        if (isEnterPressed || charCount[lineCount - 1] >= maxLineLength)
        {
            lineCount++;
            col = 0;
            row++;
            first = false;
            newNode->lineNumber = row;
        }
        int row2 = row;
        if (founded)
        {
            col = 0;
            row++;
            placeFinder = next->down;
            newNode->lineNumber = row;
        }
        if (row >= maxLines)
        {
            return false;
        }
        if (!placeFinder)
        {
            if (!head)
            {
                head = newNode;
            }
            else if (lineCount == 1)
            {
                Node* temp = head;
                for (int i = 0; i < charCount[lineCount - 1] && temp->right; i++)
                {
                    temp = temp->right;
                }
                temp->right = newNode;
                temp->right->left = temp;
            }
            else if (lineCount == maxLines)
            {
                Node* temp = head;
                Node* nextLine = nullptr;

                int j = 1;
                while (j < lineCount && temp->down)
                {
                    temp = temp->down;
                    j++;
                }

                if (!(temp->down) && !first)
                {
                    temp->down = newNode;
                    nextLine = temp->down;
                    nextLine->up = temp;
                    temp->down = nextLine;
                    first = true;
                }
                else
                {
                    for (int i = 0; i < charCount[lineCount - 1] && temp->right; i++)
                    {
                        temp = temp->right;
                    }
                    temp->right = newNode;
                    temp->right->left = temp;
                    if (temp->up && temp->up->right)
                    {
                        temp->right->up = temp->up->right;
                        temp->up->right->down = temp->right;
                    }
                }
            }
            else
            {
                Node* temp = head;
                Node* nextLine = nullptr;

                int j = 1;
                while (j < lineCount && temp->down)
                {
                    temp = temp->down;
                    j++;
                }

                if (!(temp->down) && !first)
                {
                    temp->down = newNode;
                    nextLine = temp->down;
                    nextLine->up = temp;
                    temp->down = nextLine;
                    first = true;
                }
                else
                {
                    for (int i = 0; i < charCount[lineCount - 1] && temp->right; i++)
                    {
                        temp = temp->right;
                    }
                    temp->right = newNode;
                    temp->right->left = temp;
                    if (temp->up && temp->up->right)
                    {
                        temp->right->up = temp->up->right;
                        temp->up->right->down = temp->right;
                    }
                    if (temp->down && temp->down->right)
                    {
                        temp->right->down = temp->down->right;
                        temp->down->right->up = temp->right;
                    }
                }
            }

            charCount[lineCount - 1]++;
            col++;
            wordCount++;
        }
        else
        {
            int r = 0;
            Node* temp2 = head;
            Node* next = head;
            int k = 0;
            int j = 0;
            bool spaceFull = 0;
            bool inserted = false;

            while (next)
            {
                temp2 = next;
                while (temp2->right)
                {
                    int j = 0;
                    temp2 = temp2->right;
                    j++;
                }
                if (charCount[r] < maxLineLength)
                    break;
                next = next->down;
                k++;
                spaceFull = 1;
                if (next)
                {
                    r++;
                    spaceFull = 1;
                }
                else
                    temp2 = next;
            }
            if (temp2)
            {
                temp2->right = newNode;
                temp2->right->left = temp2;
            }
            else
            {
                lineCount -= 1;
                inserted = insertData(c, k, j, true, wordCount, lineCount, charCount);
                if (!inserted)
                    return false;
                if (inserted)
                {
                    if (row > 1)
                    {
                        row--;
                        col++;

                    }
                }
            }

            if (!inserted)
            {
                if (r == maxLineLength)
                {
                    if (temp2->up && temp2->up->right)
                    {
                        temp2->right->up = temp2->up->right;
                        temp2->up->right->down = temp2->right;
                    }
                }
                else
                {
                    if (temp2->up && temp2->up->right)
                    {
                        temp2->right->up = temp2->up->right;
                        temp2->up->right->down = temp2->right;
                    }
                    if (temp2->down && temp2->down->right)
                    {
                        temp2->right->down = temp2->down->right;
                        temp2->down->right->up = temp2->right;
                    }
                }

                charCount[r]++;
                col++;
                wordCount++;
            }
            Node* nextLine = head;

            for (int i = 0; i < row2 && nextLine; i++)
            {
                nextLine = nextLine->down;
            }
            next = placeFinder;
            char preData = c;
            Node* copy = nextLine;
            bool executed = false;

            while (next)
            {
                temp2 = next;
                while (temp2)
                {
                    char t = temp2->value;
                    temp2->value = preData;
                    preData = t;
                    temp2 = temp2->right;
                    executed = true;
                }
                if (spaceFull)
                {
                    if (next == nextLine->down)
                        nextLine = nextLine->down;
                    next = nextLine->down;
                    nextLine = nextLine->down;
                    copy = nextLine;
                }
                else
                    break;
            }
            if (copy && !(copy->right))
                copy->value = preData;
        }
        return true;
    }

    bool deleteText(int& row, int& col, int& lineCount, int* cc, int& index)
    {
        if (!head)
            return false;

        if (row < 0 || col <= 0)
        {
            if (col <= 0 && row > 0)
            {
                row--;
                col = cc[row];
            }
            return false;
        }

        Node* temp = head;
        int c = 0;
        int r = 0;

        while (temp && r < row)
        {
            temp = temp->down;
            r++;
        }

        Node* next = temp;
        while (temp && c < col - 1)
        {
            temp = temp->right;
            c++;
        }

        Node* deleted = temp;

        while (next)
        {
            while (temp && temp->right)
            {
                temp->value = temp->right->value;
                temp = temp->right;
            }
            next = next->down;
            if (next)
            {
                temp->value = next->value;
                temp = next;
                index++;
            }
        }

        if (temp)
        {
            deleted = temp->left;
            if (temp->up)
                temp->up->down = nullptr;
            if (temp->down)
                temp->down->up = nullptr;
            delete temp;
            if (deleted)
            {
                deleted->right = nullptr;

            }
            else if (row == 0 && col == 1)
                head = nullptr;

            return true;
        }
        else
            return false;
    }



    void display()
    {
        system("cls");

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 7); // White

        cout << "Welcome to the Notepad." << endl;
        cout << "This is the area where you are supposed to write the content." << endl;
        cout << string(maxLineLength + 20, '-') << endl;

        Node* row = head;
        for (int i = 0; i < maxLines; ++i)
        {
            Node* col = row;
            for (int j = 0; j < maxLineLength + 18; ++j)
            {
                if (j < 100)
                {
                    if (col)
                    {
                        SetConsoleTextAttribute(hConsole, col->color);
                        cout << col->value;
                        SetConsoleTextAttribute(hConsole, 7);//resetting
                        col = col->right;
                    }
                    else
                    {
                        cout << " ";
                    }
                    if (j == 99)
                        cout << "|";
                }
                else
                {
                    if (i == 0 && j > 89)
                    {
                        cout << "Suggestions:     |";
                        break;
                    }
                    else if (j == 117)
                        cout << "|";
                    else
                        cout << " ";
                }
            }
            cout << endl;

            if (row)
            {
                row = row->down;
            }
        }

        cout << string(maxLineLength + 20, '-') << endl;
        cout << "Search" << endl;
        cout << string(maxLineLength + 20, '-') << endl;
    }




    bool jump(int& y, int& x, char direction, int* charCount)
    {
        Node* temp = head;
        int count = 0;
        Node* next = temp;
        switch (direction)
        {
        case 'u':
            for (int i = 0; i < y - 1 && temp; i++)
            {
                temp = temp->down;
            }
            if (!temp)
                return 0;

            for (int i = 0; i < x - 1 && temp->right; i++)
            {
                temp = temp->right;
                count++;
            }

            if (count < x - 1 && y > 0 && (temp && !(temp->right)))
            {
                x = charCount[y - 1];
                y--;
                return false;
            }
            if (temp && y > 0)
            {
                return true;
            }
            else
                return 0;
            break;
        case 'd':
            for (int i = 0; i < y + 1 && temp; i++)
            {
                temp = temp->down;
            }
            if (!temp)
                return 0;
            for (int i = 0; i < x - 1 && temp->right; i++)
            {
                temp = temp->right;
                count++;
            }

            if (count < x - 1 && y < maxLines && (temp && !(temp->right)))
            {
                if (y + 1 < maxLines)
                {
                    x = charCount[y + 1];
                    y++;
                }
                return false;
            }
            if (temp)
            {
                return true;
            }
            else
                return 0;
            break;
        case 'r':
            for (int i = 0; i < y && temp; i++)
            {
                temp = temp->down;
                next = temp;
            }
            for (int i = 0; i < x && temp; i++)
            {
                temp = temp->right;
            }
            if (temp)
            {
                return true;
            }
            if (next->down)
            {
                y++;
                x = 0;
                return 0;
            }
            else
                return 0;
            break;
        case 'l':
        {
            for (int i = 0; i < x - 1 && temp->right; i++)
            {
                temp = temp->right;
            }
            if (temp && x > 0)
            {
                return true;
            }
            if (!temp)
                return false;
            if (!(temp->left) && y > 0)
            {
                y--;
                x = charCount[y];
                return 0;
            }
            else
                return 0;
            break;
        }
        default:
            break;
        }
    }

    char getWord(int row, int col)
    {
        Node* temp = head;
        if (!temp || row < 0 || col < 0)
            return '\0';

        for (int j = 0; j < col && temp; j++)
        {
            temp = temp->down;
        }
        if (temp)
        {
            for (int i = 0; i < row && temp; i++)
            {
                temp = temp->right;
            }

            if (!temp)
                return '\0';
            return temp->value;
        }
        return '\0';
    }

    char getNextWord(int row, int col)
    {
        row++;
        if (row >= maxLineLength)
        {
            row = 0;
            col++;
        }
        return this->getWord(row, col);
    }
};

void saveList(Node* head, const string& filename)
{
    ofstream listFile;
    listFile.open(filename);

    if (!listFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    Node* current = nullptr;
    Node* next = head;
    while (next)
    {
        current = next;
        while (current)
        {
            listFile << current->value;
            current = current->right;
        }
        next = next->down;
        listFile << endl;
    }

    listFile.close();
}

void loadList(const string& filename, Editor* pad, int& row, int& col, bool isEnterPressed, int& wordCount, int& lineCount, int* charCount)
{
    ifstream listFile;
    listFile.open(filename);

    if (!listFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;
    int i = 0;
    while (getline(listFile, line))
    {
        i = 0;
        while (line[i] != '\0')
        {
            char data = line[i];
            i++;
            pad->insertData(data, row, col, isEnterPressed, wordCount, lineCount, charCount);
            isEnterPressed = false;
        }
        isEnterPressed = true;
    }

    listFile.close();
}

void welcome()
{
    cout << "Welcome to the NotePad.." << endl <<
        "Select an option from below." << endl <<
        "1. Create a new File." << endl <<
        "2. Load an existing File." << endl <<
        "3. Save the current File." << endl <<
        "4. Exit the NotePad" << endl <<
        "Enter your choice: ";
}

void decision(bool& newFile, string& fileName, string& saving, bool& queit, bool& openFile)
{
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 4)
    {
        cout << "Invalid choice please select again..." << endl;
        cin >> choice;
    }

    switch (choice)
    {
    case 1:
        newFile = true;
        cout << "Enter the file name: ";
        cin >> fileName;
        break;
    case 2:
        cout << "Enter the file name: ";
        cin >> fileName;
        openFile = true;
        break;

    case 4:
        cout << "\nDo you like to save the current file.";
        cin >> saving;
        queit = true;
        break;
    default:
        break;
    }
}
// Utility function to move cursor to (x, y) coordinates
void gotoxy(int x, int y) {
    y += 3;
    COORD c = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


// undo implementation

class Values {
private:
    int x[5];
    int y[5];
    int head, tail, size;

public:
    Values() {
        head = -1;
        tail = -1;
        size = 5;
    }

    void insert(int xx, int yy) {
        if ((tail + 1) % size == head) {
            this->remove();
            cout << "List is full" << x << endl;
        }

        if (head == -1) {
            head = 0;
            tail = 0;
        }
        else {
            tail = (tail + 1) % size;
        }

        x[tail] = xx;
        y[tail] = yy;
    }

    void remove() {
        if (head == -1) {
            cout << "List is empty" << endl;
            return;
        }


        if (head == tail) {
            head = -1;
            tail = -1;
        }
        else {
            head = (head + 1) % size;
        }
    }

    void removeLast() {
        if (tail == -1) {
            cout << "List is empty" << endl;
            return;
        }

        if (tail == head) {
            head = -1;
            tail = -1;
        }
        else {
            tail = (tail - 1 + size) % size;
        }
    }
    int getX() {
        if (tail == -1) {
            return -1;
        }
        else {
            return x[tail];
        }
    }
    int getY() {
        if (tail == -1) {
            return -1;
        }
        else {
            return y[tail];
        }
    }
};

class StackNode {
public:
    char data;
    StackNode* next;
};

class Stack {
private:
    StackNode* top;

public:
    Stack() {
        top = nullptr;
    }

    void push(char value) {
        StackNode* newNode = new StackNode();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (top == nullptr) {
            cout << "No elements to pop" << endl;
            return -1;
        }
        else {
            int poppedValue = top->data;
            StackNode* temp = top;
            top = top->next;
            delete temp;
            return poppedValue;
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }

    int peek() {
        if (top == nullptr) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        else {
            return top->data;
        }
    }

    ~Stack() {
        while (top != nullptr) {
            pop();
        }
    }
};

void deletion(Editor* wordPad, int& y, int& x, int& lineCount, int& wordCount, int* charCount)
{
    int index = y;
    if (wordPad->deleteText(y, x, lineCount, charCount, index))
    {
        x--;

        bool nextLine = true;
        if (x <= 0 && y != 0)
        {
            if (charCount[y] > 0)
            {
                charCount[y]--;
                wordCount--;
            }
            y--;
            x = charCount[y];
            lineCount--;
            nextLine = false;
        }
        gotoxy(x, y);
        if (charCount[y] > 0 && nextLine)
        {
            if (index == y)
            {
                charCount[y]--;
            }
            else
            {
                charCount[index]--;
            }
            wordCount--;
        }
        wordPad->display();
        gotoxy(x, y);
    }
    else
        gotoxy(x, y);
}


//*********************************************************** ASSIGNMENT 3 ************************************************//

struct NAryTree {
    struct Node1 {
        char letter;
        int lineNumber;
        Node1* childs[26];
        bool childExist;
        Node1(char letter, int lineNumber) :letter(letter), lineNumber(lineNumber)
        {
            for (int i = 0; i < 26; i++)
            {
                childs[i] = nullptr;
            }
            childExist = 0;
        }
    };

    Node1* root[26];
    NAryTree()
    {
        for (int i = 0; i < 26; i++)
        {
            root[i] = nullptr;
        }
    }

    void makeNull()
    {
        for (int i = 0; i < 26; i++)
        {
            root[i] = nullptr;
        }
    }
    void insert(char letter, queue<char>& q, bool space, int line)
    {
        if (letter < 97)
            letter += 32;
        if (space) {
            while (!q.empty())
                q.pop();
        }
        else {
            q.push(letter);
            insertH(root, letter, q, line);
        }
    }
    void insertH(Node1** root, char letter, queue<char> q, int line)
    {
        int size = q.size();
        while (size--)
        {
            char alpha = q.front();
            q.pop();
            q.push(alpha);

            if (alpha == letter)
            {
                if (!root[letter - 97])
                {
                    root[letter - 97] = new Node1(letter, line + 1);
                }
                else
                    root[letter - 97]->childExist = true;
            }
            else
                root[alpha - 97]->childExist = true;
            root = root[alpha - 97]->childs;
        }
    }

    void update(Node* head, queue<char>& q, int line, int maxLines, int maxLineLength)
    {
        this->makeNull();
        Node* row = head;
        bool space = false;
        for (int i = 0; i < maxLines; ++i)
        {
            Node* col = row;
            for (int j = 0; j < maxLineLength + 18; ++j)
            {
                if (col)
                {
                    space = 0;
                    if (col->value == ' ')
                        space = 1;
                    this->insert(col->value, q, space, col->lineNumber);
                    col = col->right;
                }
                else
                    break;
            }
            while (!q.empty())
                q.pop();
            if (row)
                row = row->down;
            else
                break;
        }
    }

    bool search(Node1** root, queue<char>& q, int& line)
    {
        int size = q.size();
        bool first = true;
        while (size--)
        {
            char alpha = q.front();
            q.pop();

            if (root[alpha - 97] == nullptr)
                return false;
            if (first)
            {
                line = root[alpha - 97]->lineNumber;
                first = false;
            }
            //root[alpha - 97]->color = 1;
            root = root[alpha - 97]->childs;
        }
    }

    queue<char> suggestWord(Node1** root, queue<char> q) {
        int size = q.size() - 1;
        string currentWord;

        char alpha = q.front();
        q.pop();
        while (size--)
        {
            if (root[alpha - 'a'] == nullptr)
                return queue<char>();
            currentWord += alpha;
            root = root[alpha - 'a']->childs;
            alpha = q.front();
            q.pop();
        }

        queue<char> suggested;

        if (!(root[alpha - 97])->childExist)
        {
            return suggested;
        }

        suggestionHelper(root[alpha - 97], suggested, currentWord);

        return suggested;
    }

    void suggestionHelper(Node1* root, queue<char>& suggested, string currentWord)
    {
        if (!root)
            return;

        currentWord += (root)->letter;

        if (!(root)->childExist)
        {
            for (char c : currentWord)
            {
                suggested.push(c);
            }
            suggested.push(' ');
        }

        for (int i = 0; i < 26; i++)
        {
            if ((root)->childs[i])
            {
                suggestionHelper((root)->childs[i], suggested, currentWord);
            }
        }
    }

    void displayTree()
    {
        for (int i = 0; i < 26; i++)
        {
            if (root[i])
            {
                displayTreeHelper(root[i], "");
            }
        }
    }

    void displayTreeHelper(Node1* node, string currentWord)
    {
        if (!node)
            return;

        currentWord += node->letter;

        bool hasChild = false;
        for (int i = 0; i < 26; i++)
        {
            if (node->childs[i])
            {
                hasChild = true;
                displayTreeHelper(node->childs[i], currentWord);
            }
        }

        if (!hasChild)
        {
            cout << currentWord << endl;
        }
    }
};

template <typename T>
struct LinkedList {

    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr)
        {       }
    };

    Node* head;

public:
    LinkedList() : head(nullptr)
    {    }

    void insertAtEnd(T value)
    {
        Node* newNode = new Node(value);
        if (!head)
        {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    Node* getHead()
    {
        return head;
    }

    char* getData(Node* currentNode)
    {
        if (currentNode)
        {
            return currentNode->data;
        }
        return nullptr;
    }
};

struct ChilliMilliTree {
    struct Node1 {
        char letter[26];
        LinkedList<Node1*> childs;
        int childCount;

        Node1() : childCount(0)
        {
            for (int i = 0; i < 26; i++)
            {
                letter[i] = '\0';
            }
        }
    };

    Node1* root;
    Node1* prev;
    ChilliMilliTree()
    {
        root = nullptr;
        prev = nullptr;
    }

    bool findWord(Node1* currentNode, const char* word, Node1*& prev)
    {
        if (!currentNode) return false;

        if (strcmp(currentNode->letter, word) == 0)
        {
            prev = currentNode;
            return true;
        }

        LinkedList<Node1*>::Node* childNode = currentNode->childs.getHead();
        while (childNode)
        {
            if (findWord(childNode->data, word, prev))
            {
                return true;
            }
            childNode = childNode->next;
        }

        return false;
    }

    void insert(char* word)
    {
        Node1* prev2 = nullptr;
        if (findWord(root, word, prev2))
        {
            if (prev2)
                this->prev = prev2;
            return;
        }

        Node1* newNode = new Node1();
        strcpy(newNode->letter, word);

        if (!root)
        {
            root = newNode;
            prev = root;
            return;
        }

        prev->childs.insertAtEnd(newNode);
        prev = newNode;
    }

    void update(Node* head, int maxLines, int maxLineLength)
    {
        this->root = nullptr;
        Node* row = head;
        char letter[26];
        int index = 0;

        for (int i = 0; i < maxLines; ++i)
        {
            Node* col = row;
            for (int j = 0; j < maxLineLength + 18; ++j)
            {
                if (col)
                {
                    letter[index++] = col->value;
                    if (col->value == ' ' || !col->right)
                    {
                        if (letter[index - 1] != ' ')
                            letter[index++] = ' ';
                        letter[index] = '\0';
                        this->insert(letter);
                        for (int i = 0; i < index; i++)
                        {
                            letter[i] = '\0';
                        }
                        index = 0;
                    }

                    col = col->right;
                }
                else
                    break;
            }
            if (row)
                row = row->down;
            else
                break;
        }
    }
    queue<char> suggestWord()
    {
        queue<char> suggested;

        if (!prev) return suggested;

        LinkedList<Node1*>::Node* childNode = prev->childs.getHead();
        while (childNode)
        {
            for (int i = 0; i < 26 && childNode->data->letter[i] != '\0'; i++)
            {
                suggested.push(childNode->data->letter[i]);
            }
            childNode = childNode->next;
        }

        return suggested;
    }

    void displayTree()
    {
        if (!root)
        {
            cout << "Tree is empty.\n";
            return;
        }

        queue<Node1*> q;
        q.push(root);
        cout << "\n";
        while (!q.empty())
        {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++)
            {
                Node1* currentNode = q.front();
                q.pop();

                cout << currentNode->letter << " ";

                LinkedList<Node1*>::Node* childNode = currentNode->childs.getHead();
                while (childNode)
                {
                    q.push(childNode->data);
                    childNode = childNode->next;
                }
            }
            cout << "\n";
        }
    }
};
int main() {

    welcome();
    bool newFile = false;
    string fileName;
    string saving;
    bool queit = false;
    bool openFile = false;
    decision(newFile, fileName, saving, queit, openFile);

    //creating Editor object

    Editor* wordPad = new Editor;
    int wordCount = 0;
    const int maxLineLength = 100;
    int lineCount = 1;
    const int maxLines = 18;
    int charCount[maxLines - 1] = { 0 };
    bool isEnterPressed = false;
    int* arr = nullptr;
    int x = 0, y = 0;
    int spaceY = 0;
    int spaceX = 0;
    bool spacePressed = false;
    int undoCounter = 0;

    //undo implementation
    Values* indexes = new Values;
    Stack* stack = new Stack;

    //assingment 3
    NAryTree* tree = new NAryTree;
    queue<char> q;
    queue<char> searchQueue;
    char newWord = 0;
    int prevX = 0;
    int prevY = 0;
    //char ch[26] = { '\0' };
    string ch;
    queue<char> suggestion;
    queue<char> suggesttedWords;
    char prevChar = '\0';

    //sentence completion.
    char sentComp[26];
    int index = 0;
    ChilliMilliTree chilli;
    queue<char> sentenceComplition;

    if (openFile)
    {
        loadList(fileName, wordPad, y, x, isEnterPressed, wordCount, lineCount, charCount);
        tree->update(wordPad->getHead(), q, y, maxLines, maxLineLength);
        chilli.update(wordPad->getHead(), maxLines, maxLineLength);
        newFile = true;
    }

    if (newFile)
    {
        system("cls");
        HANDLE  rhnd = GetStdHandle(STD_INPUT_HANDLE);  // handle to read console

        DWORD Events = 0;     // Event count
        DWORD EventsRead = 0; // Events read from console

        bool Running = true;

        wordPad->display();
        gotoxy(x, y);

        // Main program loop
        while (Running) {
            // Get the system's current event count
            GetNumberOfConsoleInputEvents(rhnd, &Events);

            if (Events != 0) { // If something happened, handle the events

                INPUT_RECORD eventBuffer[200];
                ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);

                for (DWORD i = 0; i < EventsRead; ++i) {
                    if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {
                        switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {
                        case VK_UP: // Up arrow
                            if (wordPad->jump(y, x, 'u', charCount))
                                y--;
                            gotoxy(x, y);
                            break;
                        case VK_DOWN: // Down arrow
                            if (wordPad->jump(y, x, 'd', charCount))
                                y++;
                            gotoxy(x, y);
                            break;
                        case VK_RIGHT: // Right arrow
                            if (wordPad->jump(y, x, 'r', charCount))
                                x++;
                            gotoxy(x, y);
                            break;
                        case VK_LEFT: // Left arrow
                            if (wordPad->jump(y, x, 'l', charCount))
                                x--;
                            gotoxy(x, y);
                            break;
                        case VK_RETURN:	 // Enter key for next line
                            if (lineCount < maxLines - 1)
                            {
                                isEnterPressed = true;
                                while (!q.empty())
                                    q.pop();
                                prevChar = ' ';
                                chilli.update(wordPad->getHead(), maxLines, maxLineLength);        //inserting in chilli milli tree
                            }
                            break;
                        case VK_BACK:  // Backspace key for deleting text
                        {
                            int index = y;
                            if (wordPad->deleteText(y, x, lineCount, charCount, index))
                            {
                                x--;
                                bool nextLine = true;
                                if (x <= 0 && y != 0)
                                {
                                    if (charCount[y] > 0)
                                    {
                                        charCount[y]--;
                                        wordCount--;
                                    }
                                    y--;
                                    x = charCount[y];
                                    lineCount--;
                                    nextLine = false;
                                }
                                gotoxy(x, y);
                                if (charCount[y] > 0 && nextLine)
                                {
                                    if (index == y)
                                    {
                                        charCount[y]--;
                                    }
                                    else
                                    {
                                        charCount[index]--;
                                    }
                                    wordCount--;
                                }
                                wordPad->display();
                                gotoxy(x, y);
                                tree->update(wordPad->getHead(), searchQueue, y, maxLines, maxLineLength);
                                chilli.update(wordPad->getHead(), maxLines, maxLineLength);
                            }
                            else
                                gotoxy(x, y);
                        }
                        break;
                        case VK_CONTROL:  //ctrl key for saving file
                            if (eventBuffer[i].Event.KeyEvent.bKeyDown)
                            {
                                //if (GetAsyncKeyState('S') & 0x8000) 
                                {
                                    saveList(wordPad->getHead(), fileName);
                                }
                            }
                            break;
                        case VK_MENU:  //alt key for undo
                            if (undoCounter < 5)
                            {
                                spaceX = indexes->getX();
                                spaceY = indexes->getY();
                                x = spaceX;
                                y = spaceY;
                                do
                                {
                                    stack->push(wordPad->getWord(spaceX, spaceY));

                                    deletion(wordPad, y, x, lineCount, wordCount, charCount);

                                } while ((wordPad->getWord(spaceX, spaceY) != ' ') && (wordPad->getWord(spaceX, spaceY) != '\0'));

                                stack->push(wordPad->getWord(spaceX, spaceY));

                                deletion(wordPad, y, x, lineCount, wordCount, charCount);
                                indexes->removeLast();
                                undoCounter++;

                            }
                            else
                                cout << "stack full" << endl;
                            break;
                        case VK_ESCAPE: //escape key for quitting
                            y = 21;
                            gotoxy(x, y);
                            cout << "\nDo you like to save the current file: ";
                            cin >> saving;
                            if (saving == "yes")
                                saveList(wordPad->getHead(), fileName);
                            cout << ".....GOOD BYE....." << endl;
                            return 0;
                            break;
                        case 0x31:  // 1 key for searching
                            prevX = 0;
                            prevY = 21;
                            gotoxy(prevX, prevY);
                            cout << "What you want to search? press Enter to continue: ";
                            /*cin.ignore(26, '\n');
                            cin.getline(ch, 26);*/
                            cin >> ch;
                            {
                                int i = 0;
                                int lineNumber = 0;
                                while (ch[i] != '\0')
                                {
                                    searchQueue.push(ch[i++]);
                                }
                                if (!tree->search(tree->root, searchQueue, lineNumber))
                                {
                                    cout << "Word not found.";
                                }
                                else
                                {
                                    cout << "Found at lineNumber: " << lineNumber;
                                }
                                while (!searchQueue.empty())
                                    searchQueue.pop();
                            }
                            gotoxy(x, y);
                            break;
                        default: // character input
                            if ((eventBuffer->Event.KeyEvent.uChar.AsciiChar >= 65 && eventBuffer->Event.KeyEvent.uChar.AsciiChar <= 90) ||
                                (eventBuffer->Event.KeyEvent.uChar.AsciiChar >= 97 && eventBuffer->Event.KeyEvent.uChar.AsciiChar <= 122) ||
                                eventBuffer->Event.KeyEvent.uChar.AsciiChar == 32)
                            {
                                if (wordPad->insertData(eventBuffer->Event.KeyEvent.uChar.AsciiChar, y, x, isEnterPressed, wordCount, lineCount, charCount))
                                {
                                    isEnterPressed = false;
                                    gotoxy(x, y);
                                    wordPad->display();
                                    gotoxy(x, y);
                                    suggestion.push(eventBuffer->Event.KeyEvent.uChar.AsciiChar);
                                    sentComp[index++] = (eventBuffer->Event.KeyEvent.uChar.AsciiChar);
                                    if (!spacePressed)
                                    {
                                        indexes->insert(x - 1, y);
                                        spacePressed = true;
                                        newWord = eventBuffer->Event.KeyEvent.uChar.AsciiChar;
                                    }
                                    if (eventBuffer->Event.KeyEvent.uChar.AsciiChar == 32)
                                    {
                                        spacePressed = 0;
                                        while (!suggestion.empty())
                                            suggestion.pop();

                                        sentComp[index] = '\0';
                                        //if (sentComp[0] != ' ')
                                        chilli.update(wordPad->getHead(), maxLines, maxLineLength);        //inserting in chilli milli tree
                                        index = 0;
                                    }

                                    // assignment 3 
                                    prevChar = eventBuffer->Event.KeyEvent.uChar.AsciiChar;
                                    tree->update(wordPad->getHead(), q, y, maxLines, maxLineLength);
                                }
                            }
                            else        //word completion
                            {
                                if (eventBuffer->Event.KeyEvent.uChar.AsciiChar == '@' && prevChar != ' ')
                                {
                                    suggesttedWords = tree->suggestWord(tree->root, suggestion);
                                    prevX = 101;
                                    prevY = 1;
                                    gotoxy(prevX, prevY);
                                    int count = 1;
                                    int size = suggesttedWords.size();
                                    if (size == 0)
                                        cout << "No words found";
                                    else
                                    {
                                        cout << count << ". ";
                                        while (size--)
                                        {
                                            char letter = suggesttedWords.front();
                                            suggesttedWords.pop();
                                            suggesttedWords.push(letter);
                                            if (letter == ' ' && size)
                                            {
                                                prevY++;
                                                gotoxy(prevX, prevY);
                                                cout << ++count << ". ";
                                            }
                                            else
                                                cout << letter;
                                        }
                                        int choice;
                                        cin >> choice;
                                        if (choice > 0 && choice <= count)
                                        {
                                            while (choice > 1)
                                            {
                                                char letter = suggesttedWords.front();
                                                suggesttedWords.pop();
                                                if (letter == ' ')
                                                {
                                                    choice--;
                                                }
                                            }

                                            while (1)
                                            {
                                                char letter = suggesttedWords.front();
                                                suggesttedWords.pop();
                                                char insertedLetter;
                                                if (!suggestion.empty())
                                                {
                                                    insertedLetter = suggestion.front();
                                                    suggestion.pop();
                                                }
                                                else
                                                    insertedLetter = '\0';
                                                if (letter == ' ')
                                                    break;

                                                if (letter != insertedLetter)
                                                {
                                                    if (wordPad->insertData(letter, y, x, isEnterPressed, wordCount, lineCount, charCount))
                                                    {
                                                        isEnterPressed = false;
                                                        gotoxy(x, y);
                                                        wordPad->display();
                                                        gotoxy(x, y);
                                                        suggestion.push(eventBuffer->Event.KeyEvent.uChar.AsciiChar);
                                                        if (!spacePressed)
                                                        {
                                                            indexes->insert(x - 1, y);
                                                            spacePressed = true;
                                                            newWord = eventBuffer->Event.KeyEvent.uChar.AsciiChar;
                                                        }
                                                        if (eventBuffer->Event.KeyEvent.uChar.AsciiChar == 32)
                                                        {
                                                            spacePressed = 0;
                                                            while (!suggestion.empty())
                                                                suggestion.pop();
                                                        }

                                                        prevChar = eventBuffer->Event.KeyEvent.uChar.AsciiChar;
                                                        tree->update(wordPad->getHead(), q, y, maxLines, maxLineLength);
                                                        chilli.update(wordPad->getHead(), maxLines, maxLineLength);
                                                    }
                                                }
                                            }
                                        }
                                        else if (choice == 0)
                                        {
                                            gotoxy(x, y);
                                        }
                                    }
                                }
                                if (eventBuffer->Event.KeyEvent.uChar.AsciiChar == '*' && prevChar == ' ')
                                {
                                    sentenceComplition = chilli.suggestWord();
                                    prevX = 101;
                                    prevY = 1;
                                    gotoxy(prevX, prevY);
                                    int count = 1;
                                    int size = sentenceComplition.size();
                                    if (size == 0)
                                        cout << "No words found";
                                    else
                                    {
                                        cout << count << ". ";
                                        while (size--)
                                        {
                                            char letter = sentenceComplition.front();
                                            sentenceComplition.pop();
                                            sentenceComplition.push(letter);
                                            if (letter == ' ' && size)
                                            {
                                                prevY++;
                                                gotoxy(prevX, prevY);
                                                cout << ++count << ". ";
                                            }
                                            else
                                                cout << letter;
                                        }
                                        int choice;
                                        cin >> choice;
                                        if (choice > 0 && choice <= count)
                                        {
                                            while (choice > 1)
                                            {
                                                char letter = sentenceComplition.front();
                                                sentenceComplition.pop();
                                                if (letter == ' ')
                                                {
                                                    choice--;
                                                }
                                            }

                                            while (1)
                                            {
                                                char letter = sentenceComplition.front();
                                                sentenceComplition.pop();

                                                if (letter == ' ')
                                                    break;

                                                if (wordPad->insertData(letter, y, x, isEnterPressed, wordCount, lineCount, charCount))
                                                {
                                                    isEnterPressed = false;
                                                    gotoxy(x, y);
                                                    wordPad->display();
                                                    gotoxy(x, y);
                                                    suggestion.push(eventBuffer->Event.KeyEvent.uChar.AsciiChar);
                                                    if (!spacePressed)
                                                    {
                                                        indexes->insert(x - 1, y);
                                                        spacePressed = true;
                                                        newWord = eventBuffer->Event.KeyEvent.uChar.AsciiChar;
                                                    }
                                                    if (eventBuffer->Event.KeyEvent.uChar.AsciiChar == 32)
                                                    {
                                                        spacePressed = 0;
                                                        while (!suggestion.empty())
                                                            suggestion.pop();
                                                    }

                                                    prevChar = eventBuffer->Event.KeyEvent.uChar.AsciiChar;
                                                    tree->update(wordPad->getHead(), q, y, maxLines, maxLineLength);
                                                    chilli.update(wordPad->getHead(), maxLines, maxLineLength);
                                                }
                                            }
                                        }
                                        else if (choice == 0)
                                        {
                                            gotoxy(x, y);
                                        }
                                    }
                                }
                            }
                            if (eventBuffer->Event.KeyEvent.uChar.AsciiChar == '2') //displaying N ary tree
                            {
                                system("cls");
                                tree->displayTree();
                            }
                            if (eventBuffer->Event.KeyEvent.uChar.AsciiChar == '3') //displaying chilli milli tree
                            {
                                system("cls");
                                chilli.displayTree();
                            }
                            break;
                        }
                    }
                } // end EventsRead loop
            }
        } // end program loop
    }

    return 0;
}