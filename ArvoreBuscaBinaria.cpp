#include <iostream>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <string>
#include "ArvoreBuscaBinaria.h"
#include "No.h"
#include "CelulaArq.h"

using namespace std;

ArvoreBuscaBinaria::ArvoreBuscaBinaria()
{
    _raiz = NULL;
}


bool ArvoreBuscaBinaria::vazia() const {
    return (_raiz == NULL);
}

No* ArvoreBuscaBinaria::busca(Tipo t){
    No* no = _raiz;
    while ((no != NULL) && (no->getChave() != t)) {
        if (no->getChave() < t)
            no = no->getDir();
        else no = no->getEsq();
    }
    return no;
}

void ArvoreBuscaBinaria::insere( Tipo t, TipoDoElemento linha ) {
    if( _raiz ) {
        _raiz->insere(t, linha); }
    else
        _raiz = new No(t);
}

void ArvoreBuscaBinaria::insereAVL( Tipo t ) {
    insereAVL(t, &_raiz);
}

int ArvoreBuscaBinaria::insereAVL( Tipo t, No** ppNo ) {
    int cresceu;
    if ((*ppNo)==NULL) {
        (*ppNo) = new No(t);
        cresceu = 1;
    } else if ((*ppNo)->getChave() > t) {
        cresceu = insereAVL(t, &(*ppNo)->_esq);
        if (cresceu) {
            switch ((*ppNo)->getBal()) {
            case 1:
                (*ppNo)->_bal = 0;
                cresceu = 0;
                break;
            case 0:
                (*ppNo)->_bal = -1;
                cresceu = 1;
                break;
            case -1:
                if ((*ppNo)->getEsq()->getBal() == -1) {
                    rotDir(ppNo);
                    (*ppNo)->_bal = 0;
                    (*ppNo)->getDir()->_bal = 0;
                } else {
                    rotEsq(&((*ppNo)->_esq));
                    rotDir(ppNo);
                    if ((*ppNo)->getBal() == -1) {
                        (*ppNo)->getEsq()->_bal = 0;
                        (*ppNo)->getDir()->_bal = 1;
                    } else {
                        (*ppNo)->getDir()->_bal = 0;
                        (*ppNo)->getEsq()->_bal = -(*ppNo)->getBal();
                    }
                    (*ppNo)->_bal = 0;
                }
                cresceu = 0;
                break;
            }
        }
    } else if ((*ppNo)->getChave() < t) {
        cresceu = insereAVL(t, &(*ppNo)->_dir);
        if (cresceu) {
            switch ((*ppNo)->getBal()) {
            case -1:
                (*ppNo)->_bal = 0;
                cresceu = 0;
                break;
            case 0:
                (*ppNo)->_bal = 1;
                cresceu = 1;
                break;
            case 1:
                if ((*ppNo)->getDir()->getBal() == 1) {
                    rotEsq(ppNo);
                    (*ppNo)->_bal = 0;
                    (*ppNo)->getEsq()->_bal = 0;
                } else {
                    rotDir(&((*ppNo)->_dir));
                    rotEsq(ppNo);
                    if ((*ppNo)->getBal() == -1) {
                        (*ppNo)->getEsq()->_bal = 0;
                        (*ppNo)->getDir()->_bal = 1;
                    } else {
                        (*ppNo)->getDir()->_bal = 0;
                        (*ppNo)->getEsq()->_bal = -(*ppNo)->getBal();
                    }
                    (*ppNo)->_bal = 0;
                }
                cresceu = 0;
                break;
            }
        }
    } else cresceu = 0;

    return cresceu;
}

void ArvoreBuscaBinaria::imprime(){
    imprimeRecursivo(_raiz, 0);
}

void ArvoreBuscaBinaria::imprimeRecursivo(No* no, int nivel){
    int i;
    if (no == NULL) return;
    imprimeRecursivo(no->getDir(), nivel + 1);
    for(i = 0; i < nivel; i++)
		cout << " ";
	cout << no->getChave() << " " << no->getNElems() << endl;
    imprimeRecursivo(no->getEsq(), nivel + 1);
}


ArvoreBuscaBinaria::~ArvoreBuscaBinaria()
{
    delete _raiz;
}

bool ArvoreBuscaBinaria::verificaAVL(No** ppNo)
{
    if(*ppNo == NULL) return true;

    else
    {
        int x = altura((*ppNo)->_esq);
        int y = altura((*ppNo)->_dir);

        if(y-x > -1 && y-x < 1){
            if(verificaAVL(&(*ppNo)->_esq) && verificaAVL(&(*ppNo)->_dir))
            return true;
        }

        else return false;
    }

    return false;
}

int ArvoreBuscaBinaria::altura(No *raiz){
     if (raiz == NULL) return -1;
    else return maximo(altura(raiz->getEsq()),altura(raiz->getDir())) + 1;
}

int ArvoreBuscaBinaria::maximo(int x, int y)
{
    if(x >= y) return x;

    else
    return y;
}

bool ArvoreBuscaBinaria::verificaBalanceamento(No** ppNo)
{
    if(*ppNo == NULL) return true;

    if(*ppNo != NULL)
    {
        if(altura((*ppNo)->_dir) - altura((*ppNo)->_esq) == (*ppNo)->getBal())
        {
            if( verificaBalanceamento(&(*ppNo)->_esq) && verificaBalanceamento(&(*ppNo)->_dir) )
            return true;

            else return false;
        }
    }

    return false;
}

void ArvoreBuscaBinaria::insereLinha(int linha, string palavra, string arquivo)
{
    No* no = busca(palavra);

    no->insereLinhaNo(linha, arquivo);
}

string ArvoreBuscaBinaria::geraSaida(string arquivo)
{
    return geraSaida(arquivo, _raiz);
}

string ArvoreBuscaBinaria::geraSaida(string arquivo, No* pNo)
{
    string saida = "";

    if(pNo == NULL) return "";

    saida = saida + geraSaida(arquivo, pNo->_esq);

    CelulaArq* temp = pNo->arquivos;

    while(temp->getInfo() != arquivo && temp->getProx() != NULL) {
            temp = temp->getProx();
    }
    if(temp->getInfo() == arquivo){
    Celula* aux = temp->nLinhas;
    cout << pNo->getChave() << ": ";
    saida = saida + pNo->getChave() + ": ";
    while(aux != NULL){

        stringstream ss;
        ss << aux->getInfo();
        string str = ss.str();

        cout << str << " ";

        saida = saida + str + " ";
        aux = aux->getProx();
    }
    cout << endl;
    saida = saida + "\n";
    }
    saida = saida + geraSaida(arquivo, pNo->_dir);

    return saida;
}

void ArvoreBuscaBinaria::imprimeWords(string comando, CelulaArq* nomesDosArquivos)
{

//Ideia: Para cada arquivo é feito separadamente. Primeiro pega-se as palavras desejadas.
//Todos os arquivos em que as palavras estão são adicionados em archive.
//O archive é percorrido e comparado com o nomeDoArquivo atualmente em questão.
//É construída uma lista (mesmoArquivo) contendo as células de todos os arquivos de mesmo nome que contèm a palavra
//A prmieira e segunda palavra do mesmoArquivo são comparadas e os valores de linhas iguais são postos no LinhasWords
//O linhasWords é então comparado com todas as demais palavras contidas em mesmoArquivo.
//Cada linha presente no LinhasWords e não presente em mesmoArquivo é removido da lista.
//Terminada a checagem, somente existem em LinhasWords as linhas presentes em todas as palavras escolhidas pelo usuário.
//Finalmente as linhas do LinhasWords são imprimidas e o processo se repete pro arquivo txt seguinte.

    string palavra;
    stringstream sentence(comando);
    CelulaArq* archives = new CelulaArq("", NULL);

    while(nomesDosArquivos != NULL){
    while(getline(sentence, palavra, '+')){
        CelulaArq* archAdd = busca(palavra)->arquivos;
        archAdd->setProx(archives);
        archives = archAdd;
    }
       Celula* LinhasWords = new Celula(0, NULL);
       CelulaArq* mesmoArquivo = new CelulaArq("", NULL);

        while(archives != NULL){
               // cout << "*" << archives->getInfo() << endl;
            if(archives->getInfo() == nomesDosArquivos->getInfo()){
                CelulaArq* add = archives;
                add->setProx(mesmoArquivo);
                mesmoArquivo = add;
            }
            archives = archives->getProx();
        }

        CelulaArq* word1 = mesmoArquivo;
        CelulaArq* word2 = mesmoArquivo->getProx();
        Celula* Lword1 = word1->nLinhas;
        Celula* Lword2 = word2->nLinhas;
        while(Lword1 != NULL){
            while(Lword2 != NULL){
                if(Lword1->getInfo() == Lword2->getInfo()){
                    Celula* Ltemp = new Celula(Lword1->getInfo(), LinhasWords);
                    LinhasWords = Ltemp;
                    cout << " Deu igual!" << endl;
                }
                Lword2 = Lword2->getProx();
            }
            Lword2 = word2->nLinhas;
            Lword1 = Lword1->getProx();
        }

      Celula* aux1 = new Celula(0, LinhasWords);
    word2 = (mesmoArquivo->getProx())->getProx();

    while(word2 != NULL){
        Celula* Lword2 = word2->nLinhas;
        Celula* aux2 = aux1;
        while(aux2->getProx() != NULL){
            bool mesmaLinha = false;
            while(Lword2 != NULL){
                if(Lword2->getInfo() == (aux2->getProx())->getInfo())
                    mesmaLinha = true;
                Lword2 = Lword2->getProx();
            }
            Lword2 = word2->nLinhas;
            if(mesmaLinha) aux2 = aux2->getProx();
            if(!mesmaLinha) aux2->setProx((aux2->getProx())->getProx());
        }
        word2 = word2->getProx();
    }

    cout << nomesDosArquivos->getInfo() << ":-----------------------------------" << endl;
    while(LinhasWords != NULL){
    string frase;
    fstream arq;
    arq.open((nomesDosArquivos->getInfo()).c_str(), fstream::in);

    for(int i = 0; i<LinhasWords->getInfo()-1; i++)
          getline(arq,frase);

          cout << LinhasWords->getInfo() << ": " << frase << endl;

          LinhasWords = LinhasWords->getProx();

    arq.close();
    }
    nomesDosArquivos = nomesDosArquivos->getProx();
    }
}
