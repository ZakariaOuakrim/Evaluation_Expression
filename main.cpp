#include <iostream>
#include <cctype>  // Pour isdigit()
#include <cstring> // Pour strchr()

using namespace std;

// Implémentation d'une pile (stack)
class Stack
{
private:
    int top;
    int capacity;
    int *array;

public:
    Stack(int capacity)
    {
        this->capacity = capacity;
        array = new int[capacity];
        top = -1;
    }

    ~Stack()
    {
        delete[] array;
    }

    void push(int item)
    {
        if (isFull())
        {
            cout << "Stack Overflow\n";
            return;
        }
        array[++top] = item;
    }

    int pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow\n";
            return -1;
        }
        return array[top--];
    }

    int peek()
    {
        if (!isEmpty())
        {
            return array[top];
        }
        else
        {
            cout << "Stack is empty\n";
            return -1;
        }
    }

    bool isEmpty()
    {
        return top == -1;
    }

    bool isFull()
    {
        return top == capacity - 1;
    }
};

int evaluate_expression(const char *expression)
{
    int len = strlen(expression);
    Stack numbers(len);
    Stack operators(len);

    for (int i = 0; i < len; i++)
    {
        if (expression[i] == '(')
        {
            continue;
        }
        else if (isdigit(expression[i]))
        {
            int operand = 0;
            while (i < len && isdigit(expression[i]))
            {
                operand = operand * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            numbers.push(operand);
        }
        else if (strchr("+-", expression[i]))
        {
            operators.push(expression[i]);
        }
        else if (expression[i] == ')')
        {
            int operand2 = numbers.pop();
            int operand1 = numbers.pop();
            char op = operators.pop();
            if (op == '+')
            {
                numbers.push(operand1 + operand2);
            }
            else if (op == '-')
            {
                numbers.push(operand1 - operand2);
            }
        }
    }

    return numbers.pop();
}

int main()
{
    const char *expression = "((5+3)-2)";
    int result = evaluate_expression(expression);
    cout << "Result: " << result << endl;
    return 0;
}
