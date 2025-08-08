#include <iostream>
#include <stack>
#include <string>
#include <iomanip>
#include <cmath>   
#include <sstream> 

using namespace std;

// Priority function for operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Function to perform basic arithmetic operations
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);  // Using math library for power
    }
    return 0;
}

// Check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Infix to Postfix conversion using array method 
string infixToPostfixArray(const string& expression) {
    char stack[100];  // Stack for operators
    int top = -1;
    string postfix;

    cout << "Execution Sequence\n";
    cout << "+-----+--------------------+----------------+--------+\n";
    cout << "| Step| Current Character  | Stack          | Output |\n";
    cout << "+-----+--------------------+----------------+--------+\n";

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        cout << "| " << setw(4) << i + 1 << " | " << setw(18) << c << " | ";

        if (isdigit(c)) {
            postfix += c;
        } else if (c == '(') {
            stack[++top] = c;
        } else if (c == ')') {
            while (top >= 0 && stack[top] != '(') {
                postfix += stack[top--];
            }
            top--; // Pop '('
        } else if (isOperator(c)) {
            while (top >= 0 && precedence(stack[top]) >= precedence(c)) {
                postfix += stack[top--];
            }
            stack[++top] = c;
        }

        // Print the stack 
        string stack_str = "";
        for (int j = 0; j <= top; j++) {
            stack_str += stack[j];
        }
        cout << setw(14) << stack_str << " | " << setw(6) << postfix << " |\n";
    }

    while (top >= 0) {
        postfix += stack[top--];
    }
    
    cout << "+-----+--------------------+----------------+--------+\n";

    return postfix;
}

// Infix to Postfix conversion using pointer method 
string infixToPostfixPointer(const string& expression) {
    char* stack = new char[100];  // Stack for operators
    int top = -1;
    string postfix;

    cout << "Execution Sequence\n";
    cout << "+-----+--------------------+----------------+--------+\n";
    cout << "| Step| Current Character  | Stack          | Output |\n";
    cout << "+-----+--------------------+----------------+--------+\n";

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
      cout << "| " << setw(4) << i + 1 << " | " << setw(18) << c << " | "; 

        if (isdigit(c)) {
            postfix += c;
        } else if (c == '(') {
            stack[++top] = c;
        } else if (c == ')') {
            while (top >= 0 && stack[top] != '(') {
                postfix += stack[top--];
            }
            top--; // Pop '('
        } else if (isOperator(c)) {
            while (top >= 0 && precedence(stack[top]) >= precedence(c)) {
                postfix += stack[top--];
            }
            stack[++top] = c;
        }

        // Print the stack 
        string stack_str = "";
        for (int j = 0; j <= top; j++) {
            stack_str += stack[j];
        }
      cout << setw(14) << stack_str << " | " << setw(6) << postfix << " |\n";
    }

    while (top >= 0) {
        postfix += stack[top--];
    }

    delete[] stack;
    
    cout << "+-----+--------------------+----------------+--------+\n";
    return postfix;
}

// Infix to Postfix conversion using Linked List method 
struct Node {
    char data;
    Node* next;
};

void push(Node*& top, char c) {
    Node* newNode = new Node;
    newNode->data = c;
    newNode->next = top;
    top = newNode;
}

char pop(Node*& top) {
    if (!top) return '\0';
    char data = top->data;
    Node* temp = top;
    top = top->next;
    delete temp;
    return data;
}

string infixToPostfixLinkedList(const string& expression) {
    Node* stack = NULL;  // Stack using linked list
    string postfix;

    cout << "Execution Sequence\n";
    cout << "+-----+--------------------+----------------+--------+\n";
    cout << "| Step| Current Character  | Stack          | Output |\n";
    cout << "+-----+--------------------+----------------+--------+\n";
    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
       cout << "| " << setw(4) << i + 1 << " | " << setw(18) << c << " | ";

        if (isdigit(c)) {
            postfix += c;
        } else if (c == '(') {
            push(stack, c);
        } else if (c == ')') {
            while (stack && stack->data != '(') {
                postfix += pop(stack);
            }
            pop(stack); // Pop '('
        } else if (isOperator(c)) {
            while (stack && precedence(stack->data) >= precedence(c)) {
                postfix += pop(stack);
            }
            push(stack, c);
        }

        // Print the stack 
        string stack_str = "";
        Node* temp = stack;
        while (temp) {
            stack_str += temp->data;
            temp = temp->next;
        }
       cout << setw(14) << stack_str << " | " << setw(6) << postfix << " |\n";  
    }

    while (stack) {
        postfix += pop(stack);
    }
cout << "+-----+--------------------+----------------+--------+\n";

    return postfix;
}

// Infix to Postfix conversion using Doubly Linked List method 
struct DNode {
    char data;
    DNode* next;
    DNode* prev;
};

void push(DNode*& top, char c) {
    DNode* newNode = new DNode;
    newNode->data = c;
    newNode->next = top;
    newNode->prev = NULL;
    if (top) top->prev = newNode;
    top = newNode;
}

char pop(DNode*& top) {
    if (!top) return '\0';
    char data = top->data;
    DNode* temp = top;
    top = top->next;
    if (top) top->prev = NULL;
    delete temp;
    return data;
}

string infixToPostfixDoublyLinkedList(const string& expression) {
    DNode* stack = NULL;  // Stack using doubly linked list
    string postfix;

    cout << "Execution Sequence\n";
    cout << "+-----+--------------------+----------------+--------+\n";
    cout << "| Step| Current Character  | Stack          | Output |\n";
    cout << "+-----+--------------------+----------------+--------+\n";

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
     cout << "| " << setw(4) << i + 1 << " | " << setw(18) << c << " | ";

        if (isdigit(c)) {
            postfix += c;
        } else if (c == '(') {
            push(stack, c);
        } else if (c == ')') {
            while (stack && stack->data != '(') {
                postfix += pop(stack);
            }
            pop(stack); // Pop '('
        } else if (isOperator(c)) {
            while (stack && precedence(stack->data) >= precedence(c)) {
                postfix += pop(stack);
            }
            push(stack, c);
        }

        // Print the stack
        string stack_str = "";
        DNode* temp = stack;
        while (temp) {
            stack_str += temp->data;
            temp = temp->next;
        }
        cout << setw(14) << stack_str << " | " << setw(6) << postfix << " |\n";
    }

    while (stack) {
        postfix += pop(stack);
    }
    
    cout << "+-----+--------------------+----------------+--------+\n";

    return postfix;
}

// Custom Stack implementation (for conversion and evaluation)
struct CustomStack {
    char* stackArr;
    int top;
    int size;

    CustomStack(int s) {
        stackArr = new char[s];
        size = s;
        top = -1;
    }

    void push(char c) {
        if (top < size - 1) {
            stackArr[++top] = c;
        }
    }

    char pop() {
        if (top == -1) return '\0';
        return stackArr[top--];
    }

    bool isEmpty() {
        return top == -1;
    }

    ~CustomStack() {
        delete[] stackArr;
    }
};

string infixToPostfixCustomStack(const string& expression) {
    CustomStack stack(100);
    string postfix;

    cout << "Execution Sequence\n";
    cout << "+-----+--------------------+----------------+--------+\n";
    cout << "| Step| Current Character  | Stack          | Output |\n";
    cout << "+-----+--------------------+----------------+--------+\n";

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
    cout << "| " << setw(4) << i + 1 << " | " << setw(18) << c << " | ";

        if (isdigit(c)) {
            postfix += c;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.stackArr[stack.top] != '(') {
                postfix += stack.pop();
            }
            stack.pop(); // Pop '('
        } else if (isOperator(c)) {
            while (!stack.isEmpty() && precedence(stack.stackArr[stack.top]) >= precedence(c)) {
                postfix += stack.pop();
            }
            stack.push(c);
        }

        // Print the stack 
        string stack_str = "";
        for (int j = 0; j <= stack.top; j++) {
            stack_str += stack.stackArr[j];
        }
      cout << setw(14) << stack_str << " | " << setw(6) << postfix << " |\n";
    }

    while (!stack.isEmpty()) {
        postfix += stack.pop();
    }
    
    cout << "+-----+--------------------+----------------+--------+\n";


    return postfix;
}

// Expression Evaluation function
int evaluatePostfix(const string& postfix) {
    stack<int> s;

    cout << "\nEvaluation Sequence:\n";
    cout << "+-----+--------+-------------------+\n";
    cout << "| Step| Symbol |       Stack       |\n";
    cout << "+-----+--------+-------------------+\n";

    for (int i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        if (isdigit(c)) {
            s.push(c - '0');  // Convert char to int
        } else if (isOperator(c)) {
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            s.push(applyOp(a, b, c));
        }

        // Print the stack 
       cout << "| " << setw(4) << i + 1 << " | " << setw(6) << c << " | ";
        stack<int> temp = s;
        string stackContent = "";
        while (!temp.empty()) {
            // Use stringstream to convert integer to string
            stringstream ss;
            ss << temp.top();
            stackContent = ss.str() + " " + stackContent;
            temp.pop();
        }
       cout << setw(17) << stackContent << " |\n";
    }
    cout << "+-----+--------+-------------------+\n";
    return s.top();
}


// Function to simulate the conversion process
void simulateConversion(const string& expression, int method) {
    string postfix;
    switch (method) {
        case 1:
            postfix = infixToPostfixArray(expression);
            break;
        case 2:
            postfix = infixToPostfixPointer(expression);
            break;
        case 3:
            postfix = infixToPostfixLinkedList(expression);
            break;
        case 4:
            postfix = infixToPostfixDoublyLinkedList(expression);
            break;
        case 5:
            postfix = infixToPostfixCustomStack(expression);
            break;
        default:
            cout << "Invalid method choice!\n";
            return;
    }

    cout << "Postfix Expression: " << postfix << endl;
    cout << "Evaluating Postfix Expression...\n";
    int result = evaluatePostfix(postfix);
    cout << "Evaluation Result: " << result << endl;
}

int main() {
    cout << "Welcome to My Calculator!\n";
    cout << "This is a calculator that performs two main tasks:\n";
    cout << "1. Expression Conversion (Infix to Postfix)\n";
    cout << "2. Expression Evaluation (Postfix Expression)\n";
    cout << "3. Exit\n";

    while (true) {
        cout << "\nPlease choose an option:\n";
        cout << "1. Convert Infix to Postfix\n";
        cout << "2. Evaluate Postfix Expression\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Enter an infix expression (e.g a+b): ";
            string infix;
            cin.ignore();
            getline(cin, infix);

            cout << "\nChoose conversion method:\n";
            cout << "1. Using Array\n";
            cout << "2. Using Pointer\n";
            cout << "3. Using Linked List\n";
            cout << "4. Using Doubly Linked List\n";
            cout << "5. Using Custom Stack\n";
            cout << "Enter your choice: ";
            int method;
            cin >> method;

            string postfix;
            switch (method) {
                case 1:
                    postfix = infixToPostfixArray(infix);
                    break;
                case 2:
                    postfix = infixToPostfixPointer(infix);
                    break;
                case 3:
                    postfix = infixToPostfixLinkedList(infix);
                    break;
                case 4:
                    postfix = infixToPostfixDoublyLinkedList(infix);
                    break;
                case 5:
                    postfix = infixToPostfixCustomStack(infix);
                    break;
                default:
                    cout << "Invalid method choice!\n";
                    continue;
            }
            cout << "\nPostfix Expression: " << postfix << endl;

        } else if (choice == 2) {
            cout << "Enter a postfix expression (e.g ab+): ";
            string postfix;
            cin.ignore();
            getline(cin, postfix);

            cout << "\nEvaluating Postfix Expression...\n";
            int result = evaluatePostfix(postfix);
            cout << "Evaluation Result: " << result << endl;

        } else if (choice == 3) {
            cout << "Exiting the program. Goodbye!\n";
            break;

        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}



