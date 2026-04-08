#include <iostream> //usado para cin e cout (padrão de aplicação c++)
#include <stack> //lib para uso de pilhas(sem necessidade de ponteiro manual) usada nas funções de validação de parenteses, operadores e tokens
#include <string> //lib para manipulação de textos
#include <cctype> //lib para funções de verificação como(isdigit)
#include <vector> //lib para listas dinâmicas(no caso o Histórico)


using namespace std;
/*
Criação de uma struct chamada registro para salvar a expressão e o seu resultado
*/
struct Registro
{
    string expressao;
    double resultado;
};
/*
Criação de um Vector(lista Dinamica) para guardar o histórico das expressões
*/
vector<Registro> historico;
/* 
Verifica se os parenteses estão válidos usando pilha da biblioteca <stack> onde ela cria uma pilha e percorre a expressão até o final quando achar '(' ela empilha se ')' 
e se a pilha estiver vazia(fechou parenteses sem abrir) retorna erro e desenpilha no final se a pilha estiver vazia = válida se não (sobrou algo não fechado) invlaida.
*/
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
/*
Verifica e define a precedencia dos operadores prioridade matemática se o operador for '+' ou '-' sua prioridade é 1, se o operador for '*' ou '/' sua prioridade é 2
*/
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
/*
Transformo uma String em uma pilha de "tokens" ou seja (3 5 2 * +) vira (+ * 2 5 3 VERTICALMENTE) cada numero vira um token separado 
Pois a recursão precisa trabalhar con tokens individuais e não a string inteira
Cria-se a pilha de tokens vazia e uma variavel para numeros(ex:123 e não 1 2 3), função percorre expressão char por char se for numero ele junta até achar espaço em branco ' '
Então faz push(empilha) numeros e limpa a variavel, se for operador transforma * em "*" e faz push(empilha)
*/
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
/*
Aqui está o uso do algoritimo de Shunting Yard esse algoritimo transforma uma expressão "infixa" = 3 + 5 * 2 para "posfixa" = 3 5 2 * +.
Para cada caractere ele Lê o numero completo adiciona ta variavel saida  e coloca um espaço no final, se for um '(' empilha se for ')' desempilha a lista até encontrar um '('.
Se for um operador  como "+ - * / " enquanto o operador do topo tiver prioridade(precedencia) maior move para saída = Regra central do algoritimo.
No final esvazia a pilha
*/
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
/*
Essa função executa a operação (a(numero) op(operador) b(numero)) usando um switch case e verifica se a divisão é por zero
*/
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
/*
Calculo da expressão poxfixa ex (3 5 2 * +) resursivamente nos trechos  das linhas 192 e 193
Passo a passo ele lê o token removendo o topo da pilha, caso for numero transforma em double (stod = String to double)
se for operador faz double b = avaliarPosfixaRecursiva(tokens); para lado direito e double a = avaliarPosfixaRecursiva(tokens); para lado esquerdo
if (isdigit(token[0])) {return stod(token);} ´ o caso base
*/
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
/*
Função Intermediaria não calcula diretamente apenas prepara dados para recursão
cria tokens (transforma expressão em pilha de tokens) e chama recursão
*/
double avaliarPosfixa(const string& expressao) {

    stack<string> tokens = criarTokens(expressao);

    return avaliarPosfixaRecursiva(tokens);
}
/*
Controla o fluxo a função valida o parenteses faz a conversão de infixo para poxfixo e avalia o poxfixo
Basicamente controla todo o algoritimo de calculo e validação,
*/
double avaliarExpressao(const string& expressao) {

    if (!parentesesValidos(expressao)) {
        cout << "Parenteses invalidos" << endl;
        return 0;
    }

    string posfixa = infixoParaPosfixo(expressao);

    return avaliarPosfixa(posfixa);
}
/*
Uso do algoritimo Bubble Sort para fazer a orndenação do historico de expressões
*/
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
/*
Função para exibir o histórico de expressões, se estiver vazio retorna mensagem informando que esta vazio
faz um for passando pela lista dinamica(vector) que armazena o histórico e exibe cada expressão e seu resultado
*/
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
/*
Algoritimo de Busca Binária para retornar a expressão buscada pelo usuario com pase no resultado dela
*/
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
/*
Função para limpar o histórico, verifica se está vazio, se não estiver da um .clear uma função da lib vector que apaga todos os registros que ele contem
*/
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
/*
Função Principal do Programa onde é executado todas as chamadas de funções das opções dispostas para os usuario
*/
int main()
{
    string expressao;
    int op;
    double valorBusca;
    
    do
    {
    
        cout << "Seja bem-vindo ao Sistema de Expressao Matematica!" << endl;
        cout << "Escolha uma das opcoes a seguir:" << endl;
        cout << "1 - Avaliar Expressao" << endl;
        cout << "2 - Exibir Historico" << endl;
        cout << "3 - Buscar Expressao(Por resultado)" << endl;
        cout << "4 - Ordenar Historico" << endl;
        cout << "5 - Limpar Historico" << endl;
        cout << "6 - Sair do Sistema" << endl;

        cin >> op;
        cin.ignore();
        
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
            break;
        }
        case 2:
            cout << "Exibindo Historico..." << endl;
            exibirHistorico();
            break;
        case 3:
        {
            cout << "Digite o resultado para buscar a expressao: ";
            cin >> valorBusca;

            ordenarHistorico(historico);
            
            int pos = buscarExpressao(historico, valorBusca);

            if (pos != -1){
                cout << "Expressao encontrada: " << historico[pos].expressao << " = " << historico[pos].resultado << endl;
            }else{
                cout << "Resultado nao encontrado." << endl;
            }

            break;
        }
        case 4:   
            cout << "Historico Ordenado!" << endl;
            ordenarHistorico(historico);
            break;       
        case 5:
            cout << "Historico Limpo!" << endl;
            limparHistorico();
            break;
        case 6:
            cout << "Fim do Programa..." << endl;
            break;
        default:
            cout << "Digite uma opção valida!" << endl;
            break;
        }
        
    } while (op != 6);


    return 0;
}