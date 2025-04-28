#include<stdio.h>
#include<stdlib.h>

typedef struct Noeud {
    int valeur;
    struct Noeud *suivant;
} Noeud;

Noeud* debut = NULL;
Noeud* fin = NULL;

void Enfiler(int value) {
    Noeud* nouveau = (Noeud*)malloc(sizeof(Noeud));
    if (nouveau == NULL) {
        printf("Erreur d'allocation\n");
        return;
    }
    
    nouveau->valeur = value;
    nouveau->suivant = NULL;
    
    if (debut == NULL) {
        debut = fin = nouveau;
    } else {
        fin->suivant = nouveau;
        fin = nouveau;
    }
}


void Defiler() {
    if (debut == NULL) {
        printf("File vide\n");
        return;
    }
    
    Noeud* temp = debut;
    debut = debut->suivant;
    free(temp);
    
    if (debut == NULL) {
        fin = NULL;
    }
}


void afficherFile() {
    Noeud* temp = debut;
    printf("Contenu de la file : ");
    while (temp != NULL) {
        printf("%d ", temp->valeur);
        temp = temp->suivant;
    }
    printf("\n");
}


void viderFile() {
    while (debut != NULL) {
        Defiler();
    }
}

int main() {
    Enfiler(5);
    Enfiler(15);
    Enfiler(25);
    afficherFile();

    Defiler();
    afficherFile();

    viderFile();
    afficherFile(); 

    return 0;
}
