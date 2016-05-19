#include <stdio.h>
#include <stdlib.h>
#include "RN.h"

RNtree* Insere(RNtree* t, int key)
{
            RNtree* x = t;

            if(t == NULL)  {
                 // aloca��o de espa�o
                 NodoNULL = (RNtree*) malloc(sizeof(RNtree));
                 x = (RNtree*) malloc(sizeof(RNtree));
                 //inicializa��es
                 // NULL
                 NodoNULL->red = 0; // null � preto;
                 NodoNULL->esq = NodoNULL;
                 NodoNULL->dir = NodoNULL;
                 NodoNULL->key = 32000;
                 NodoNULL->pai = NodoNULL;
                 // Raiz
                 x->key = key;
                 x->esq = x->dir = NodoNULL;
                 x->red = 0;
                 x->pai = NodoNULL;
                 return x;
            }

            RNtree* p= x->pai; // pai
			RNtree* v= v->pai;

            while( x != NodoNULL )  /* desce na �rvore */
            {
              v = p; p = x;
              if( key < x->key ) x = x->esq;
              else x = x->dir;
            };

            if(x != NodoNULL) return t; // Nodo Ja Existe

            x = (RNtree*) malloc(sizeof(RNtree));
            x->key = key;
            x->esq = x->dir = NodoNULL;
            x->pai = p;
            x->red = 1;

            if( key < p->key)
                p->esq = x;
            else
                p->dir = x;

            // Nodo Foi Inserido mas pode ter modificado as regras ent�o temos que verificar.

            return VerificaRN(t, key);
};

int Consulta(int X, RNtree* T )
{
  if( T == NodoNULL ) return 0;
  if(X == T->key) return 1;
  else if( X < T->key ) return Consulta( X, T->esq );
       else if( X > T->key ) return Consulta( X, T->dir );
            else return 0;
};


RNtree* Remove(RNtree* t, int key)
{
  RNtree* x = t;
  RNtree* y;
  RNtree* p = x->pai;
  RNtree* v = p->pai;

  NodoNULL->key = key;
  while(x->key != key)  /* desce na �rvore */
  {
   v = p; p = x;
   if( key < x->key ) x = x->esq;
   else x = x->dir;
  };
  if(x == NodoNULL) return t;
  if(x->red) // nodo � vermelho
  {
    if((x->esq == NodoNULL) && (x->dir == NodoNULL)) // nodo folha
    {
      if(x->key < p->key) p->esq = NodoNULL;
      else p->dir = NodoNULL;
      free(x);
      return t;
    };
    if(x->key < p->key)
    {
     y = Menor(t->dir);
     p->esq = y;
     y->esq = x->esq;
     y->dir = x->dir;
     free(x);
    } else
      {
        y = Maior(t->esq);
        p->dir = y;
        y->dir = x->dir;
        y->esq = x->esq;
        free(x);
      };
  }
  else // nodo � preto
  {
    if(x->key < p->key) // filho a esquerda
    {
      if((p->dir->red == 0) && ((x->esq->red == 0) && (x->dir->red == 0))) // irm�o preto e dois filhos pretos
      {
        if(p->red) p->red = 0; // troca a cor do pai
        else p->red = 1;
        p->dir->red = 1; // troca a cor do irmao
        y = Menor(t->dir);
        p->esq = y;
        y->esq = x->esq;
        y->dir = x->dir;
        free(x);
      } else if ((p->dir->red == 0) && ((x->esq->red != 0) || (x->dir->red != 0)))
        {
         y = Menor(t->dir);
         p->esq = y;
         y->esq = x->esq;
         y->dir = x->dir;
         RotacaoSimplesDir(p);
         if(x->red) x->red = 0; // troca a cor do nodo
         else x->red = 1;
         free(x);
        }else // irm�o vermelho
          {
            if(p->dir->red)
            {
               y = Menor(t->dir);
               p->esq = y;
               y->esq = x->esq;
               y->dir = x->dir;
               RotacaoSimplesDir(p);
               free(x);
            };
          };
    } else // filho a direita
      {
      if((p->esq->red == 0) && ((x->esq->red == 0) && (x->dir->red == 0))) // irm�o preto e dois filhos pretos
      {
        if(p->red) p->red = 0; // troca a cor do pai
        else p->red = 1;
        p->dir->red = 1; // troca a cor do irmao
        y = Maior(t->esq);
        p->dir = y;
        y->dir = x->dir;
        y->esq = x->esq;
        free(x);
      } else if ((p->dir->red == 0) && ((x->esq->red != 0) || (x->dir->red != 0)))
        {
         y = Maior(t->esq);
        p->dir = y;
        y->dir = x->dir;
        y->esq = x->esq;
         RotacaoSimplesEsq(p);
         if(x->red) x->red = 0; // troca a cor do nodo
         else x->red = 1;
         free(x);
        };
    };
  };
  VerificaRN(t,key);
  return t;
};

void Destroi(RNtree* t)
{

};

int corTio(RNtree* t, bool dir){
	RNtree* vo = t->pai->pai;
	if(dir)
		return vo->esq->red;
	return vo->dir->red;
}
void trocaCor(RNtree* t){
		if(t->pai==NodoNULL || t==NodoNULL )
			t->red = 0;
		else
			t->red = (t->red + 1) % 2;
}
/*
void trocaCorPai(RNtree* t){
	RNtree* pai = t->pai;
	if(pai!=NodoNULL)
		trocaCor(pai);
}
void trocaCorAvo(RNtree* t){
	RNtree* vo = t->pai->pai;
	if(vo!=NodoNULL)
		trocaCor(vo);
}
*/
void trocaCorTio(RNtree* t,bool dir){
	RNtree* vo=t->pai->pai;
	if(dir)
		trocaCor(vo->esq);
	else
		trocaCor(vo->dir);
}


RNtree* VerificaRN(RNtree* t,int key)
{
  RNtree* x = t;
  RNtree* p = x->pai;
  RNtree* v = p->pai;
  while( x->key != key )  /* desce na �rvore */
  {
    v = p; p = x;
    if( key < x->key ) x = x->esq;
    else x = x->dir;
  };
  RNtree* b = v->pai;//bisav�, se houver! :D
  // x cont�m o novo e p o pai do novo.

  if(p->red == 0) // pai preto- caso 1
  	return t;

//pai vermelho - caso 2
  bool pdir = p->key > v->key;
  bool xdir = x->key > p->key;
  if( v != NodoNULL) { // pai n�o � raiz - Caso 2.1
  	if(corTio(x,pdir)){ // tio � vermelho
		trocaCor(p);
		trocaCorTio(x,pdir);
		trocaCor(v);
		return t;
	}
		// caso 2.2 tio preto
	RNtree* base;
	if(pdir == xdir){
			trocaCor(p); 
			trocaCor(v);
			if(!pdir)
              	base = RotacaoSimplesDir(v);
			else
				base = RotacaoSimplesEsq(v);
//			v->pai=base;
	} else {
			trocaCor(v);
			trocaCor(x);
			RNtree* aux;
			if(!pdir){
				aux = RotacaoSimplesEsq(p);
				RotacaoSimplesDir(aux->pai);
			}else{
				aux = RotacaoSimplesDir(p);
				base=RotacaoSimplesEsq(aux->pai);
        	}
			base=x;
		}
	if(b == NodoNULL)
		return base;
	else{
		if(v->key > b->key)
			b->dir=base;
		else
			b->esq=base;	
	}
  }
  return t;
};

RNtree* RotacaoSimplesDir( RNtree* t )
        {
            RNtree* aux;
			aux->pai=t->pai;
            aux = t->esq;
            t->esq = aux->dir;
            aux->dir = t;
			t->pai = aux;
            return aux;  /* nova raiz */
        };


RNtree* RotacaoSimplesEsq( RNtree* t )
        {
            RNtree* aux;
			aux->pai=t->pai;
            aux = t->dir;
            t->dir = aux->esq;
            aux->esq = t;
			t->pai=aux;
            return aux;   /* nova raiz */
        };

void Desenha(RNtree* t , int nivel)
{
int x;

 if (t !=NodoNULL)
 {
   for (x=1; x<=nivel; x++)
      printf("=");
   if(t->red) printf("%d Red", t->key);
   else printf("%d Black", t->key);
   printf(" filho de: %d\n",t->pai->key);
   if (t->esq != NodoNULL) Desenha(t->esq, (nivel+1));
   if (t->dir != NodoNULL) Desenha(t->dir, (nivel+1));
 }
 else printf("Arvore Vazia\n");
};


RNtree* Maior(RNtree* t)
{
 while (t != NodoNULL) t = t->dir;
 return t->pai;
};


RNtree* Menor(RNtree* t)
{
  while (t != NodoNULL) t = t->esq;
  return t->pai;
};
