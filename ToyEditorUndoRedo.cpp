#include <iostream>
#include <string>

const int MAX = 11;

class Stack {
private:
    char data[MAX];
    int top; // 맨 위의 문자
public:
    Stack() { top = 0; }

    // 맨 아래 한 칸을 비워둔다
    bool isEmpty() { return top == 0; } 
    // 맨 위의 한 칸을 비워둔다
    bool isFull() { return top == MAX - 1; }
    
    bool push(char item) {
        if (isFull()) {
            // 스택이 가득 찼을 때,
            // 바닥에 있는 문자를 pop 하고 
            // 새로운 문자를 push 한다
            char bottom;
            popBottom(bottom);
        }
        data[++top] = item;
        return true;
    }
    
    bool pop() {
        if (isEmpty()) return false;
        top--;
        return true;
    }
    
    bool popBottom(char& bottom) {
        // 바닥에 있는 문자를 pop 하는 함수
        if (isEmpty()) return false;
        bottom = data[1];
        for (int i = 1; i < top; i++) {
            data[i] = data[i + 1];
        }
        top--;
        return true;
    }
    
    char getTop() {
        if (isEmpty()) return NULL;
        return data[top];
    }
    
    void print() {
        if (isEmpty()) std::cout << "EMPTY";
        else {
            for (int i = top; i >= 1; i--)
                std::cout << data[i] << " ";
        }
    }
};

int main() {
    // U와 R을 위한 스택 두 개 선언
    Stack undo, redo;
    std::string input;

    // '\n'을 기준으로 한 줄 입력받음
    getline(std::cin, input); 

    for (int i = 0; i < input.size(); i++) {
        char c = input[i]; // 문자열인 input의 한글자씩

        if (c == ' ') continue; // 띄어쓰기는 무시
        
        else if (c == 'U') {
            if (undo.isEmpty()) {
                // undo가 비어있는데 U 하려고 하면
                std::cout << "ERROR";
                return 0;
            }
            char lastChar = undo.getTop();
            undo.pop();
            redo.push(lastChar);
        }
        
        else if (c == 'R') {
            if (redo.isEmpty()) {
                // redo가 비어있는데 R 하려고 하면
                std::cout << "ERROR";
                return 0;
            }
            char lastChar = redo.getTop();
            redo.pop();
            undo.push(lastChar);
        }
        
        else {
            while (!redo.isEmpty()) redo.pop();
            undo.push(c);
        }
    }
    
    undo.print();
    std::cout << std::endl;
    redo.print();
    return 0;
}