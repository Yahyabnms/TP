#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Date {
    char jour[3];
    char mois[3];
    char annee[5];
} date;

typedef struct Produit {
    char *Nom_produit;
    char Reference[100];
    float Montant;
    date DateAchat;
} produit;

typedef struct liste {
    produit cellule;
    struct liste* psuiv;
} liste;

liste* creer_liste_produits() {
    return NULL;
}

int est_vide(liste* tete) {
    return (tete == NULL);
}

liste* creer_produit() {
    liste* nouveau = (liste*)malloc(sizeof(liste));
    if (!nouveau) {
        printf("Erreur d'allocation memoire\n");
        return NULL;
    }

    char nom[100];
    nouveau->cellule.Nom_produit = (char*)malloc(100);
    if (!nouveau->cellule.Nom_produit) {
        printf("Erreur d'allocation memoire pour le nom du produit\n");
        free(nouveau);
        return NULL;
    }

    printf("Nom du produit : ");
    scanf("%s", nom);
    strcpy(nouveau->cellule.Nom_produit, nom);

    printf("Reference : ");
    scanf("%s", nouveau->cellule.Reference);

    printf("Montant : ");
    scanf("%f", &nouveau->cellule.Montant);

    printf("Date d'achat (JJ MM AAAA) : ");
    scanf("%s %s %s", nouveau->cellule.DateAchat.jour, nouveau->cellule.DateAchat.mois, nouveau->cellule.DateAchat.annee);

    nouveau->psuiv = NULL;
    return nouveau;
}

void afficher_produit(liste* produit) {
    if (produit == NULL) {
        printf("Produit inexistant.\n");
        return;
    }
    printf("Nom: %s, Reference: %s, Montant: %.2f, Date: %s/%s/%s\n",
           produit->cellule.Nom_produit,
           produit->cellule.Reference,
           produit->cellule.Montant,
           produit->cellule.DateAchat.jour,
           produit->cellule.DateAchat.mois,
           produit->cellule.DateAchat.annee);
}

liste* ajouter_debut(liste* tete) {
    liste* nv = creer_produit();
    if (!nv) return tete;

    nv->psuiv = tete;
    return nv;
}

void ajouter_fin(liste** tete) {
    liste* nv = creer_produit();
    if (!nv) return;

    if (*tete == NULL) {
        *tete = nv;
    } else {
        liste* temp = *tete;
        while (temp->psuiv != NULL) {
            temp = temp->psuiv;
        }
        temp->psuiv = nv;
    }
}

void afficher_produits(liste* tete) {
    if (est_vide(tete)) {
        printf("La liste est vide.\n");
        return;
    }
    liste* temp = tete;
    while (temp != NULL) {
        afficher_produit(temp);
        temp = temp->psuiv;
    }
}

int longueur(liste* tete) {
    int count = 0;
    while (tete != NULL) {
        count++;
        tete = tete->psuiv;
    }
    return count;
}

void filtrer_date(liste* tete, date dt) {
    liste* temp = tete;
    int trouve = 0;
    while (temp != NULL) {
        if (strcmp(temp->cellule.DateAchat.jour, dt.jour) == 0 &&
            strcmp(temp->cellule.DateAchat.mois, dt.mois) == 0 &&
            strcmp(temp->cellule.DateAchat.annee, dt.annee) == 0) {
            afficher_produit(temp);
            trouve = 1;
        }
        temp = temp->psuiv;
    }
    if (!trouve) {
        printf("Aucun produit trouve pour cette date.\n");
    }
}

liste* supprimer_debut(liste* tete) {
    if (tete == NULL) return NULL;

    liste* temp = tete;
    tete = tete->psuiv;
    free(temp->cellule.Nom_produit);
    free(temp);
    return tete;
}

void supprimer_fin(liste** tete) {
    if (*tete == NULL) return;

    if ((*tete)->psuiv == NULL) {
        free((*tete)->cellule.Nom_produit);
        free(*tete);
        *tete = NULL;
        return;
    }

    liste* temp = *tete;
    while (temp->psuiv->psuiv != NULL) {
        temp = temp->psuiv;
    }
    free(temp->psuiv->cellule.Nom_produit);
    free(temp->psuiv);
    temp->psuiv = NULL;
}

void liberer_liste(liste* tete) {
    liste* temp;
    while (tete != NULL) {
        temp = tete;
        tete = tete->psuiv;
        free(temp->cellule.Nom_produit);
        free(temp);
    }
}

int main() {
    liste* stock = creer_liste_produits();
    int choix;
    date dt_filtre;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Ajouter un produit au debut\n");
        printf("2. Ajouter un produit a la fin\n");
        printf("3. Afficher les produits\n");
        printf("4. Supprimer le premier produit\n");
        printf("5. Supprimer le dernier produit\n");
        printf("6. Afficher la longueur de la liste\n");
        printf("7. Filtrer par date\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                stock = ajouter_debut(stock);
                break;
            case 2:
                ajouter_fin(&stock);
                break;
            case 3:
                afficher_produits(stock);
                break;
            case 4:
                stock = supprimer_debut(stock);
                break;
            case 5:
                supprimer_fin(&stock);
                break;
            case 6:
                printf("Longueur de la liste: %d\n", longueur(stock));
                break;
            case 7:
                printf("Entrer la date (JJ MM AAAA) : ");
                scanf("%s %s %s", dt_filtre.jour, dt_filtre.mois, dt_filtre.annee);
                filtrer_date(stock, dt_filtre);
                break;
            case 0:
                printf("Fermeture du programme...\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    liberer_liste(stock);
    return 0;
}
