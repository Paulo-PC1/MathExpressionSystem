#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// =============================
// PILHA DE CHAR (operadores)
// =============================

struct NoOperadores {
    char valor;
    NoOperadores* prox;
};

void empilharOperadores(NoOperadores*& topo, char c) {
    NoOperadores* novo = new NoOperadores;
    novo->valor = c;
    novo->prox = topo;
    topo = novo;
}

char desempilharOperadores(NoOperadores*& topo) {

    if (topo == nullptr)
        return '\0';

    NoOperadores* temp = topo;
    char valor = temp->valor;

    topo = topo->prox;
    delete temp;

    return valor;
}

char topoPilhaOperadores(NoOperadores* topo) {

    if (topo == nullptr)
        return '\0';

    return topo->valor;
}

bool vazioOperadores(NoOperadores* topo) {
    return topo == nullptr;
}

// =============================
// PILHA DE DOUBLE (números)
// =============================

struct NoNumeros {
    double valor;
    NoNumeros* prox;
};

void empilhaNumeros(NoNumeros*& topo, double v) {

    NoNumeros* novo = new NoNumeros;

    novo->valor = v;
    novo->prox = topo;

    topo = novo;
}

double desempilhaNumeros(NoNumeros*& topo) {

    if (topo == nullptr)
        return 0;

    NoNumeros* temp = topo;

    double valor = temp->valor;

    topo = topo->prox;

    delete temp;

    return valor;
}

bool vazioNumeros(NoNumeros* topo) {
    return topo == nullptr;
}

// =============================

bool parentesesValidos(const string& expressao)
{
    NoOperadores* pilha = nullptr;

    for (char c : expressao) {

        if (c == '(') {
            empilharOperadores(pilha, c);
        }

        else if (c == ')') {

            if (vazioOperadores(pilha))
                return false;

            desempilharOperadores(pilha);
        }
    }

    return vazioOperadores(pilha);
}

// =============================

int precedencia(char operador)
{
    if (operador == '+' || operador == '-')
        return 1;

    if (operador == '*' || operador == '/')
        return 2;

    return 0;
}

// =============================

string infixoParaPosfixo(const string& expressao)
{
    NoOperadores* operadores = nullptr;

    string saida;

    for (int i = 0; i < expressao.size(); ++i) {

        char c = expressao[i];

        // Número completo
        if (isdigit(c)) {

            while (i < expressao.size() && isdigit(expressao[i])) {
                saida += expressao[i];
                ++i;
            }

            saida += ' ';
            --i;
        }

        else if (c == '(') {
            empilharOperadores(operadores, c);
        }

        else if (c == ')') {

            while (!vazioOperadores(operadores) && topoPilhaOperadores(operadores) != '(') {

                saida += desempilharOperadores(operadores);
                saida += ' ';
            }

            desempilharOperadores(operadores);
        }

        else if (c == '+' || c == '-' || c == '*' || c == '/') {

            while (!vazioOperadores(operadores) && precedencia(topoPilhaOperadores(operadores)) >= precedencia(c)) {

                saida += desempilharOperadores(operadores);
                saida += ' ';
            }

            empilharOperadores(operadores, c);
        }
    }

    while (!vazioOperadores(operadores)) {

        saida += desempilharOperadores(operadores);
        saida += ' ';
    }

    return saida;
}

// =============================

double aplicarOperador(double a, double b,char op)
{
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

// =============================

double avaliarPosfixa(const string& expressao)
{
    NoNumeros* pilha = nullptr;

    string numero;

    for (char c : expressao) {

        if (isdigit(c)) {
            numero += c;
        }

        else if (c == ' ') {
            if (!numero.empty()) {
                empilhaNumeros(pilha, stod(numero));
                numero.clear();
            }
        }

        else {

            double b = desempilhaNumeros(pilha);
            double a = desempilhaNumeros(pilha);

            double resultado = aplicarOperador(a, b, c);

            empilhaNumeros(pilha, resultado);
        }
    }

    return desempilhaNumeros(pilha);
}

// =============================

double avaliarExpressao(const string& expressao)
{
    if (!parentesesValidos(expressao)) {

        cout << "Parenteses invalidos\n";
        return 0;
    }

    string posfixa = infixoParaPosfixo(expressao);

    return avaliarPosfixa(posfixa);
}

// =============================

int main()
{
    string expressao;

    cout << "Digite uma expressao matematica: ";
    getline(cin, expressao);

    double resultado = avaliarExpressao(expressao);

    cout << "Resultado: " << resultado << endl;

    return 0;
}