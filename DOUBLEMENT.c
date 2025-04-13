#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud {
    int valeur;
    struct Noeud *suivant;
    struct Noeud *precedent;
} Noeud;

Noeud* cree(int v) {
    Noeud* newE = (Noeud*)malloc(sizeof(Noeud));
    if (newE == NULL) {
        printf("Erreur d'allocation memoire\n");
        exit(1);
    }
    newE->valeur = v;
    newE->precedent = NULL;
    newE->suivant = NULL;
    return newE;
}

void affiche(Noeud* debut) {
    Noeud* temp = debut;
    printf("Liste depuis le debut : ");
    while (temp != NULL) {
        printf("%d ", temp->valeur);
        temp = temp->suivant;
    }
    printf("\n");
}

void afficherFin(Noeud* debut) {
    if (debut == NULL) {
        printf("Liste vide.\n");
        return;
    }
    Noeud* temp = debut;
    while (temp->suivant != NULL) {
        temp = temp->suivant;
    }
    printf("Liste inverse : ");
    while (temp != NULL) {
        printf("%d ", temp->valeur);
        temp = temp->precedent;
    }
    printf("\n");
}

Noeud* ajouterD(Noeud *debut, int v) {
    Noeud* nouveau = cree(v);
    if (debut != NULL) {
        nouveau->suivant = debut;
        debut->precedent = nouveau;
    }
    return nouveau;
}

Noeud* ajouterF(Noeud *debut, int v) {
    Noeud* nouveau = cree(v);
    if (debut == NULL) return nouveau;

    Noeud* temp = debut;
    while (temp->suivant != NULL) {
        temp = temp->suivant;
    }
    temp->suivant = nouveau;
    nouveau->precedent = temp;
    return debut;
}

int taille(Noeud* debut) {
    int compteur = 0;
    Noeud* temp = debut;
    while (temp != NULL) {
        compteur++;
        temp = temp->suivant;
    }
    return compteur;
}

Noeud* insertionPosition(Noeud* debut, int v, int position) {
    int t = taille(debut);
    if (position < 0 || position > t) {
        printf("Position invalide. Elle doit etre entre 0 et %d.\n", t);
        return debut;
    }
    if (position == 0) {
        return ajouterD(debut, v);
    }

    Noeud* nouveau = cree(v);
    Noeud* temp = debut;
    for (int i = 0; i < position - 1; i++) {
        temp = temp->suivant;
    }

    nouveau->suivant = temp->suivant;
    nouveau->precedent = temp;

    if (temp->suivant != NULL) {
        temp->suivant->precedent = nouveau;
    }

    temp->suivant = nouveau;
    return debut;
}

Noeud* suppressionD(Noeud* debut) {
    if (debut == NULL) return NULL;

    Noeud* temp = debut;
    debut = debut->suivant;
    if (debut != NULL) debut->precedent = NULL;
    free(temp);
    return debut;
}

Noeud* suppressionF(Noeud* debut) {
    if (debut == NULL) return NULL;

    Noeud* temp = debut;
    while (temp->suivant != NULL) {
        temp = temp->suivant;
    }

    if (temp->precedent != NULL)
        temp->precedent->suivant = NULL;
    else
        debut = NULL;

    free(temp);
    return debut;
}

Noeud* suppressionP(Noeud* debut, int position) {
    if (debut == NULL) return NULL;

    int t = taille(debut);
    if (position < 0 || position >= t) {
        printf("Position invalide.\n");
        return debut;
    }

    if (position == 0)
        return suppressionD(debut);

    Noeud* temp = debut;
    for (int i = 0; i < position; i++) {
        temp = temp->suivant;
    }

    if (temp->precedent != NULL)
        temp->precedent->suivant = temp->suivant;
    if (temp->suivant != NULL)
        temp->suivant->precedent = temp->precedent;

    free(temp);
    return debut;
}

Noeud* modifierD(Noeud* debut, int v) {
    if (debut != NULL)
        debut->valeur = v;
    return debut;
}

Noeud* modifierF(Noeud* debut, int v) {
    if (debut == NULL) return NULL;

    Noeud* temp = debut;
    while (temp->suivant != NULL) {
        temp = temp->suivant;
    }
    temp->valeur = v;
    return debut;
}

Noeud* modifierP(Noeud* debut, int position, int val) {
    if (debut == NULL) return NULL;

    int t = taille(debut);
    if (position < 0 || position >= t) {
        printf("Position invalide.\n");
        return debut;
    }

    Noeud* temp = debut;
    for (int i = 0; i < position; i++) {
        temp = temp->suivant;
    }

    temp->valeur = val;
    return debut;
}

Noeud* rechercher(Noeud* debut, int v) {
    Noeud* temp = debut;
    while (temp != NULL) {
        if (temp->valeur == v)
            return temp;
        temp = temp->suivant;
    }
    return NULL;
}

Noeud* tri(Noeud* debut) {
    if (debut == NULL || debut->suivant == NULL)
        return debut;

    int echange;
    do {
        echange = 0;
        Noeud* temp = debut;
        while (temp->suivant != NULL) {
            if (temp->valeur > temp->suivant->valeur) {
                int tmp = temp->valeur;
                temp->valeur = temp->suivant->valeur;
                temp->suivant->valeur = tmp;
                echange = 1;
            }
            temp = temp->suivant;
        }
    } while (echange);

    return debut;
}

int main() {
    Noeud* liste = NULL;
    int choix, val, pos;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Ajouter au debut\n");
        printf("2. Ajouter a la fin\n");
        printf("3. Inserer a une position\n");
        printf("4. Supprimer au debut\n");
        printf("5. Supprimer a la fin\n");
        printf("6. Supprimer a une position\n");
        printf("7. Modifier au debut\n");
        printf("8. Modifier a la fin\n");
        printf("9. Modifier a une position\n");
        printf("10. Rechercher une valeur\n");
        printf("11. Afficher la liste\n");
        printf("12. Afficher la liste en sens inverse\n");
        printf("13. Trier la liste\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez la valeur : ");
                scanf("%d", &val);
                liste = ajouterD(liste, val);
                break;
            case 2:
                printf("Entrez la valeur : ");
                scanf("%d", &val);
                liste = ajouterF(liste, val);
                break;
            case 3:
                printf("Entrez la position : ");
                scanf("%d", &pos);
                printf("Entrez la valeur : ");
                scanf("%d", &val);
                liste = insertionPosition(liste, val, pos);
                break;
            case 4:
                liste = suppressionD(liste);
                break;
            case 5:
                liste = suppressionF(liste);
                break;
            case 6:
                printf("Entrez la position : ");
                scanf("%d", &pos);
                liste = suppressionP(liste, pos);
                break;
            case 7:
                printf("Nouvelle valeur : ");
                scanf("%d", &val);
                liste = modifierD(liste, val);
                break;
            case 8:
                printf("Nouvelle valeur : ");
                scanf("%d", &val);
                liste = modifierF(liste, val);
                break;
            case 9:
                printf("Entrez la position : ");
                scanf("%d", &pos);
                printf("Nouvelle valeur : ");
                scanf("%d", &val);
                liste = modifierP(liste, pos, val);
                break;
            case 10:
                printf("Valeur a rechercher : ");
                scanf("%d", &val);
                if (rechercher(liste, val))
                    printf("Valeur %d trouvee !\n", val);
                else
                    printf("Valeur non trouvee.\n");
                break;
            case 11:
                affiche(liste);
                break;
            case 12:
                afficherFin(liste);
                break;
            case 13:
                liste = tri(liste);
                printf("Liste triee.\n");
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}
