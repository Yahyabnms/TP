#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Noeud {
    int valeur;
    struct Noeud *suivant;
} Noeud;

void push(Noeud **top, int valeur) {
    Noeud* nv = (Noeud*)malloc(sizeof(Noeud));
    if (nv == NULL) {
        printf("Erreur d'allocation\n");
        return;
    }
    nv->valeur = valeur;
    nv->suivant = *top;
    *top = nv;
}

void pop(Noeud **top) {
    if (*top == NULL) {
        printf("Pile vide\n");
        return;
    }
    Noeud* temp = *top;
    *top = (*top)->suivant;
    free(temp);
}

void peek(Noeud* top) {
    if (top == NULL) {
        printf("Pile vide\n");
    } else {
        printf("Sommet de la pile : %d\n", top->valeur);
    }
}

void afficherPile(Noeud* top) {
    printf("Contenu de la pile : ");
    while (top != NULL) {
        printf("%d ", top->valeur);
        top = top->suivant;
    }
    printf("\n");
}

int taille(Noeud *top) {
    int a = 0;
    while (top != NULL) {
        a++;
        top = top->suivant;
    }
    return a;
}
int main() {
    Noeud* pile = NULL;

    push(&pile, 10);
    push(&pile, 20);
    push(&pile, 30);

    afficherPile(pile);
    peek(pile);
    printf("Taille de la pile : %d\n", taille(pile));

    pop(&pile);
    pop(&pile);

    afficherPile(pile);

 }