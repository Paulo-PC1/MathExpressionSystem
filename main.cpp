#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

bool parentesesValidos(const string& expressao)
{
    stack<char> pilha;
    
    for(char c : expressao){
        if (c == '('){
            pilha.push(c);
        }
        else if(c == ')'){
            if (pilha.empty())
                return false;
            pilha.pop();
        }
    }
    return pilha.empty();
}

int precedencia(char operador)
{
    if(operador == '+' || operador == '-'){
        return 1;
    }
    else if(operador == '*' || operador == '/'){
        return 2;
    }
    return 0;
}

string infixoParaPosfixo(const string& expressao){

    stack<char> operadores;
    string saida;

    for (int i = 0; i < expressao.size(); ++i) {

        char c = expressao[i];

        // Ler número completo
        if (isdigit(c)) {

            while (i < expressao.size() && isdigit(expressao[i])) {
                saida += expressao[i];
                ++i;
            }

            saida += ' ';
            --i;
        }

        else if(c == '('){
            operadores.push(c);
        }

        else if (c == ')') {

            while(!operadores.empty() && operadores.top() != '('){

                saida += operadores.top();
                saida += ' ';
                operadores.pop();
            }

            operadores.pop();
        }

        else if(c == '+' || c == '-' || c == '*' || c == '/'){

            while(!operadores.empty() && precedencia(operadores.top()) >= precedencia(c)){

                saida += operadores.top();
                saida += ' ';
                operadores.pop();
            }

            operadores.push(c);
        }
    }

    while(!operadores.empty()){
        saida += operadores.top();
        saida += ' ';
        operadores.pop();
    }

    return saida;
}

double aplicarOperador(double a, double b,char op) {

    switch (op) {

        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0){
                cout << "Divisao por zero\n";
                return 0;
            }
            return a / b;
    }

    return 0;
}

double avaliarPosfixa(const string& expressao) {

    stack<double> pilha;
    string numero;

    for (char c : expressao) {

        if (isdigit(c)) {
            numero += c;
        }

        else if (c == ' ') {

            if (!numero.empty()) {
                pilha.push(std::stod(numero));
                numero.clear();
            }
        }

        else { // operador

            double b = pilha.top();
            pilha.pop();

            double a = pilha.top();
            pilha.pop();

            double resultado = aplicarOperador(a, b, c);

            pilha.push(resultado);
        }
    }

    return pilha.top();
}

double avaliarExpressao(const string& expressao) {

    if (!parentesesValidos(expressao)) {
        cout << "Parenteses invalidos" << endl;
        return 0;
    }

    string posfixa = infixoParaPosfixo(expressao);

    return avaliarPosfixa(posfixa);
}
int main() {

    string expressao;
    
    cout << "Digite uma expressao matematica: ";
    getline(cin, expressao);
    
    double resultado = avaliarExpressao(expressao);

    cout << "Resultado: " << resultado << endl;

    return 0;
}