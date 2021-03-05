#include <bits/stdc++.h>


#include <iostream>
#include <cstdlib>
#include <limits>
#include <cmath>


const int kBits = 8;


class BinaryOps {
    friend std::ostream &operator<<(std::ostream &out, const BinaryOps &a);
    friend BinaryOps operator+(const BinaryOps &a, const BinaryOps &b);

    friend BinaryOps operator*(const BinaryOps& a, const BinaryOps& b);

    friend BinaryOps operator-(const BinaryOps &a, BinaryOps &b);

private:
    int m_dec_num{};
    int m_binary_num[kBits]{};
public:
//    int& operator[] (int index);
    const int &operator[](int index) const;

    friend std::ostream &operator<<(std::ostream &out, const BinaryOps &a) {
        int bits = kBits;
        for (int j = bits - 1; j >= 0; j--)
            out << a.m_binary_num[j];
        return out << std::endl;
    }

    int &operator[](int index) {
        return m_binary_num[index];
    }



    BinaryOps() = default;

    void InputVariable() {
        std::cout << "Enter the number: ";
        while (!(std::cin >> m_dec_num)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.  Try again: ";
        }
    }


    void FillArray(int n) {
        int i = 0;
        if (n > 0) {
            while (n > 0) {
                m_binary_num[i] = n % 2;
                n = n / 2;
                i++;
            }
        }
    }

    void DecToBinary(int n) {
        if (n > 0) {
            FillArray(n);
        }

        if (n < 0) {
            int pos_n = abs(n);
            FillArray(pos_n);
            for (int p = 0; p <= (sizeof(m_binary_num) / sizeof(*m_binary_num)); p++) {
                if (m_binary_num[p] == 0) {
                    m_binary_num[p] = 1;
                } else {
                    m_binary_num[p] = 0;
                }
            }

            // Looping from right to left
            for (int position = 0; position <= kBits - 1; position++) {
                if (m_binary_num[position] == 0) {
                    m_binary_num[position] = 1;
                    break;
                }
                m_binary_num[position] = 0;
            }
        }
    }




    int getDec() const { return m_dec_num; }

    const int *getBinaryNum() const {
        return m_binary_num;
    }


};

const int &BinaryOps::operator[](int index) const {
    return m_binary_num[index];
}






BinaryOps signed2Complement2(const BinaryOps &arr) {
    int carry = 1;
    BinaryOps complement;
    BinaryOps ones;


    for (int i = kBits; i >= 0; i--) {
        if (arr[i] == 0)
            ones[i] = 1;
        else if (arr[i] == 1)
            ones[i] = 0;
    }
    for (int i = 0; i <= kBits; i++) {
        if (ones[i] == 1 && carry == 1) {
            complement[i] = 0;
        } else if (ones[i] == 0 && carry == 1) {
            complement[i] = 1;
            carry = 0;
        } else {
            complement[i] = ones[i];
        }
    }

    return complement;
}


int BinToDec(const BinaryOps &arr) {
    int btdbits = kBits;
    int decimal{};
    if (arr[kBits-1] == 0) {
        for (int j = kBits - 1; j != -1; j--) {
            btdbits--;
            decimal += arr[j] * ((int) pow(2, btdbits));
        }
        return decimal;
    } else{
        for (int j = kBits - 1; j != -1; j--) {
            btdbits--;
            decimal += arr[j] * ((int) pow(2, btdbits));
        }
        return decimal - ((int) pow(2, kBits));
    }
}




BinaryOps operator+(const BinaryOps &a, const BinaryOps &b) {
    BinaryOps result;
    int carry[kBits];
    int c = 0;
    for (int u = 0; u < kBits; u++) {
        result.m_binary_num[u] = ((a[u] ^ b[u]) ^ c); // c is carry
        c = ((a[u] & b[u]) | (a[u] & c)) | (b[u] & c);
        carry[u] = c;
    }
    if(carry[kBits-1]^carry[kBits-2]){
        throw std::runtime_error("OVERFLOW!!!!");
    }
    return result;
}


BinaryOps operator-(const BinaryOps &a, BinaryOps &b) {
    BinaryOps result_min;
    BinaryOps complement = signed2Complement2(b);
    int borrow[kBits];
    int c = 0;
    for (int u = 0; u < kBits; u++) {
        result_min.m_binary_num[u] = ((a[u] ^ complement[u]) ^ c); // c is carry
        c = ((a[u] & complement[u]) | (a[u] & c)) | (complement[u] & c);
        borrow[u] = c;
    }
    if(borrow[kBits-1]^borrow[kBits-2]){
        throw std::runtime_error("OVERFLOW!!!!");
    }
    return result_min;
}



BinaryOps operator*(const BinaryOps &a, const BinaryOps &b) {
    BinaryOps result_mult;
    int multiplicator;
    int sign = (a[kBits-1] ^ b[kBits-1]);
    multiplicator = std::abs(BinToDec(a));
    while (multiplicator > 0) {
        result_mult = result_mult + b;
        multiplicator--;
    }
    if (!sign) {
        result_mult[kBits-1] = sign;
        return result_mult;
    } else {
        return result_mult;
    }
}






//int main() {
//
//    BinaryOps dec_a{};
//    BinaryOps dec_b{};
//
//    dec_a.InputVariable();
//    dec_b.InputVariable();
//
//    dec_a.DecToBinary(dec_a.getDec());
//    dec_b.DecToBinary(dec_b.getDec());
//
//    std::cout << dec_a;
//    std::cout << dec_b;
//
//    std::cout << (dec_a + dec_b);
//    std::cout << (dec_a - dec_b);
//    std::cout << (dec_a * dec_b);
//
//
//    return 0;
//}
// TODO Классы, переполнение у умножения, названия классов и функций, хардкод в проверке, проверка не через десятичные числа, а через переполнение в бинарных

















// Stack type
class Stack
{
public:
    int top;
    unsigned capacity;
    int* array;
};

// Stack Operations
Stack* createStack( unsigned capacity )
{
    auto* stack = new Stack();

    if (!stack) return NULL;

    stack->top = -1;
    stack->capacity = capacity;
    stack->array = new int[(stack->capacity * sizeof(int))];

    if (!stack->array) return nullptr;

    return stack;
}

int isEmpty(Stack* stack)
{
    return stack->top == -1 ;
}

int peek(Stack* stack)
{
    return stack->array[stack->top];
}

int pop(Stack* stack)
{
    if (!isEmpty(stack))
        return stack->array[stack->top--] ;
    return '$';
}

void push(Stack* stack,int op)
{
    stack->array[++stack->top] = op;
}


// The main function that returns value
// of a given postfix expression
int evaluatePostfix(char* exp)
{
    // Create a stack of capacity equal to expression size
    Stack* stack = createStack(strlen(exp));
    int i;

    // See if stack was created successfully
    if (!stack) return -1;

    // Scan all characters one by one
    for (i = 0; exp[i]; ++i)
    {
        //if the character is blank space then continue
        if(exp[i] == ' ')continue;

            // If the scanned character is an
            // operand (number here),extract the full number
            // Push it to the stack.
        else if (isdigit(exp[i]))
        {
            int num=0;

            //extract full number
            while(isdigit(exp[i]))
            {
                num = num * 10 + (int)(exp[i] - '0');
                i++;
            }
            i--;

            //push the element in the stack
            push(stack,num);
        }

            // If the scanned character is an operator, pop two
            // elements from stack apply the operator
        else
        {
            int val1 = pop(stack);
            int val2 = pop(stack);
            BinaryOps val1_bin;
            BinaryOps val2_bin;
            BinaryOps op_result;

            val1_bin.DecToBinary(val1);
            val2_bin.DecToBinary(val2);

            switch (exp[i])
            {
                case '+' :{
                    op_result = val1_bin + val2_bin;
                    int dec_result = BinToDec(op_result);
                    push(stack, dec_result);
                    break;
                }
                case '-':
                {
                    op_result = val1_bin - val2_bin;
                    int dec_result = BinToDec(op_result);
                    push(stack, dec_result);
                    break;
                }
                case '*':
                {
                    op_result = val1_bin * val2_bin;
                    int dec_result = BinToDec(op_result);
                    push(stack, dec_result);
                    break;
                }

            }
        }
    }
    return pop(stack);
}


int main()
{
    char exp[] = "10 30 +";
    std::cout << evaluatePostfix(exp);
    return 0;
}