/**
EP 02
Henrique Turma 02
Matheus Turma 01
Prof. Marcelo Finger
**/

//OBSERVAÇÃO: As listas lineares não foram utilizadas de forma explicita, porém foram usadas
//as células diretamente, com comportamento final idêntico as listas. Eu tive problema pois as
// listas não estavam sendo inicializadas, e a solução encontrada foi fazer uso das células
//diretamente, e não utilizando as listas conexão até as células.


#include <iostream>
#include <cstdio>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <string>
#include <locale>
#include "ArvoreBuscaBinaria.h"
#include "No.h"
#include "Celula.h"
#include "ListaLinear.h"

ArvoreBuscaBinaria tree;

using namespace std;

string transforma_minuscula (string& palavra);


string transforma_minuscula(string& palavra)
{
    locale loc;
    for (string::size_type i=0; i<palavra.length(); ++i)
    {
        if(palavra[i]<'A' || (palavra[i]>'Z' && palavra[i]<'a') || palavra[i]>'z' || palavra[i] == ' ')
            palavra.erase(i, i+1);
        else
        palavra[i] = tolower(palavra[i],loc);
    }

    return palavra;
}
int main()
{
    string frase;
    string palavra;
    string comando;
    CelulaArq* nomesDosArquivos = new CelulaArq("", NULL);
    char inicio;
    int cont = 1;

    cout<<"EP2 MAC\n";
    cout<<"& incluir arquivo\n";
    cout<<"+ - consulta do usuario\n";
    cout<<"> geracao de arquivos de indice\n";
    cout<<"# sair do programa\n";

    cout << "Digite o comando: ";
    cin >> comando;

    inicio = comando[0];
    comando.erase(0, 1);

    while(inicio!='#')
    {

        if(inicio == '&')
        {
          CelulaArq* nomesTemp = new CelulaArq(comando, nomesDosArquivos);
          nomesDosArquivos = nomesTemp;
          fstream arq;
          arq.open(comando.c_str(), fstream::in);

          while(!arq.eof()){

          getline(arq, frase);
          stringstream sentence(frase);
          while(getline(sentence, palavra, ' ')){
                palavra = transforma_minuscula(palavra);
                if(palavra[0] >= 'a' && palavra[0] <= 'z'){
                tree.insereAVL(palavra);
                tree.insereLinha(cont, palavra, comando);}
          }
          cont ++;
          }
          arq.close();
        }

        else if(inicio == '+')
        {
            //Praquando se deseja pesquisar mais de uma palavra.
            //tree.imprimeWords(comando, nomesDosArquivos);

            if(tree.busca(comando)) tree.busca(comando)->getLinhas();

            if(!tree.busca(comando)) cout << "Nao ha essa palavra no texto." << endl;
        }

        else if(inicio=='>')
        {
            fstream saida("idx.txt", fstream::out);
            saida << tree.geraSaida(comando);
            saida.close();
        }
        // quando usuario digita # sai do programa
        else if(inicio=='#') return 0;

        cout << "Digite o comando: ";
        cin >> comando;

        inicio = comando[0];
        comando.erase(0, 1);
        cont = 1;
    }
    return 0;
}
