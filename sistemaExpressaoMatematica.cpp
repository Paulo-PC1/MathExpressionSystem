#include <iostream> 
#include <stack> 
#include <string> 
#include <cctype> 
#include <vector> 

using namespace std;

struct Registro
{
    string expressao;
    double resultado;
};

vector<Registro> historico;

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

stack<string> criarTokens(const string& expressao) {

    stack<string> tokens;
    string numero;

    for (char c : expressao) {

        if (isdigit(c)) {
            numero += c;
        }

        else if (c == ' ') {

            if (!numero.empty()) {
                tokens.push(numero);
                numero.clear();
            }
        }

        else {

            string op(1, c);
            tokens.push(op);
        }
    }

    if (!numero.empty()) {
        tokens.push(numero);
    }

    return tokens;
}

string infixoParaPosfixo(const string& expressao){

    stack<char> operadores;
    string saida;

    for (int i = 0; i < expressao.size(); ++i) {

        char c = expressao[i];

        
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

double avaliarPosfixaRecursiva(stack<string>& tokens) {

    string token = tokens.top();
    tokens.pop();


    if (isdigit(token[0])) {
        return stod(token);
    }

    double b = avaliarPosfixaRecursiva(tokens);
    double a = avaliarPosfixaRecursiva(tokens);

    return aplicarOperador(a, b, token[0]);
}

double avaliarPosfixa(const string& expressao) {

    stack<string> tokens = criarTokens(expressao);

    return avaliarPosfixaRecursiva(tokens);
}

double avaliarExpressao(const string& expressao) {

    if (!parentesesValidos(expressao)) {
        cout << "Parenteses invalidos" << endl;
        return 0;
    }

    string posfixa = infixoParaPosfixo(expressao);

    return avaliarPosfixa(posfixa);
}

void ordenarHistorico(vector<Registro>& historico)
{
    int tamanho = historico.size();

    for (int i = 0; i < tamanho - 1; ++i){
        for (int j = 0; j < tamanho - 1 - i; ++j){
            if(historico[j].resultado > historico[j + 1].resultado){
                Registro temp = historico[j];
                historico[j] = historico[j + 1];
                historico[j + 1] = temp;
            }
        }

    }

}

void exibirHistorico()
{
    if(historico.empty()){
        cout << "Historico Vazio" << endl;
        return;
    }

    cout << "Historico:" << endl;

    for (size_t i = 0; i < historico.size(); ++i){
        cout << i + 1 << " - " << historico[i].expressao << " = " << historico[i].resultado << endl;
    }

}

int buscarExpressao(const vector<Registro>& historico, double valorBusca)
{
    int inicio = 0;
    int fim  = historico.size() - 1;

    while (inicio <= fim){
        int meio = (inicio + fim) / 2;
        if(valorBusca == historico[meio].resultado){
            return meio;
        }
        else if (valorBusca < historico[meio].resultado){
            fim = meio - 1;
        }
        else{
            inicio = meio + 1;
        }
    }
    return -1;

}

void limparHistorico()
{
    if (historico.empty())
    {
        cout << "Historico ja esta vazio." << endl;
        return;
    }

    historico.clear();

    cout << "Historico limpo com sucesso!" << endl;
}

int main()
{
    string expressao;
    int op;
    double valorBusca;

    do
    {

        cout << "Seja bem-vindo ao Sistema de Expressao Matematica!" << endl << endl;
        cout << "Escolha uma das opcoes a seguir:" << endl;
        cout << "1 - Avaliar Expressao" << endl;
        cout << "2 - Exibir Historico" << endl;
        cout << "3 - Buscar Expressao(Por resultado)" << endl;
        cout << "4 - Ordenar Historico" << endl;
        cout << "5 - Limpar Historico" << endl;
        cout << "6 - Sair do Sistema" << endl << endl;

        cin >> op;
        cin.ignore();
        cout << endl;

        switch (op)
        {
        case 1:
        {
            cout << "Digite uma expressao matematica: ";
            getline(cin, expressao);
            double resultado = avaliarExpressao(expressao);
            cout << "Resultado: " << resultado << endl;
            Registro novo;
            novo.expressao = expressao;
            novo.resultado = resultado;

            historico.push_back(novo);
            cout << endl;
            break;
        }
        case 2:
            cout << "Exibindo Historico..." << endl << endl;
            exibirHistorico();
            cout << endl;
            break;
        case 3:
        {
            cout << "Digite o resultado para buscar a expressao: ";
            cin >> valorBusca;

            ordenarHistorico(historico);

            int pos = buscarExpressao(historico, valorBusca);

            if (pos != -1){
                cout << "Expressao encontrada: " << historico[pos].expressao << " = " << historico[pos].resultado << endl << endl;
            }else{
                cout << "Resultado nao encontrado." << endl << endl;
            }

            break;
        }
        case 4:
            cout << "Historico Ordenado!" << endl << endl;
            ordenarHistorico(historico);
            break;
        case 5:
            cout << "Historico Limpo!" << endl << endl;
            limparHistorico();
            break;
        case 6:
            cout << "Fim do Programa..." << endl;
            break;
        default:
            cout << "Digite uma opcao valida!" << endl;
            break;
        }

    } while (op != 6);


    return 0;
}
