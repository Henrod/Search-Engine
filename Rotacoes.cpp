#include <iostream>
#include <stdio.h>
#include "ArvoreBuscaBinaria.h"

using namespace std;

/* Rotação à direita */
void ArvoreBuscaBinaria::rotDir( No** ppNo ) {
  No *aux = (*ppNo)->_esq;
  (*ppNo)->_esq = aux->_dir;
  aux->_dir = *ppNo;
  *ppNo = aux; // modifica o nó no topo da rotação
}

/* Rotação à esquerda */
void ArvoreBuscaBinaria::rotEsq( No **ppNo ) {
  No *aux = (*ppNo)->_dir;
  (*ppNo)->_dir = aux->_esq;
  aux->_esq = *ppNo;
  *ppNo = aux; // modifica o nó no topo da rotação
}

void ArvoreBuscaBinaria::insereTopo( Tipo t, No **ppNo ) {
	/* Se a arvore esta vazia e facil inserir no topo */
  if( *ppNo == NULL ) {
    *ppNo = new No( t ); // construtor de folha
  }
  else {
  	Tipo x = (*ppNo)->getChave();
    if( t < x ) {
      insereTopo( t, &(*ppNo)->_esq );
      rotDir( ppNo );
    }
    else if( t > x ) {
      insereTopo( t, &(*ppNo)->_dir );
      rotEsq( ppNo );
    }
  }
}

void ArvoreBuscaBinaria::insereNoTopo( Tipo t )
{
	insereTopo( t, &_raiz );
}

No* ArvoreBuscaBinaria::selecao( int k, No* r )
{
	int l;

	/* Pode ser que o k-esimo elemento nao exista. */
	if (r->_nElems < k)
		return NULL;

	l = (r->_esq == NULL) ? 0 : r->_esq->_nElems;
	if (l > k - 1)
		return selecao(k, r->_esq);
	if (l < k -1 )
		return selecao(k-l-1, r->_dir);
	return r;
}


void ArvoreBuscaBinaria::sobeMenor( No **ppNo ) {
  if ((*ppNo)->_esq != NULL) {
    sobeMenor(&(*ppNo)->_esq);
    rotDir(ppNo);
  }
}

No* ArvoreBuscaBinaria::uneDirEsq(No *e, No **d) {

  /* Se a sub-arvore a direita é vazia, retorna a outra. */
  if (*d == NULL)
	return e;
  sobeMenor(d);
  (*d)->_esq = e;
  return *d;
}

void ArvoreBuscaBinaria::removeNo(Tipo x, No **ppNo) {
	No *aux;

	/* Verifica se o item esta na arvore. */
	if (*ppNo == NULL)
		return;

	Tipo chave = (*ppNo)->getChave();
	if (x < chave)
		removeNo(x, &(*ppNo)->_esq);
	if (x > chave)
		removeNo(x, &(*ppNo)->_dir);
	if (x == chave) {
		aux = *ppNo;
		*ppNo = uneDirEsq((*ppNo)->_esq, &(*ppNo)->_dir);

		// Prepara Nó para remoção e remove
		aux->_dir = aux->_esq = NULL;
		delete aux;
	}
}
