#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Etudiant {
    int id;
    char nom[50];
    float moyenne;
    struct Etudiant* suivant;
    struct Etudiant* precedent;
} Etudiant;

Etudiant* creer_etudiant() 
{
    Etudiant* e = (Etudiant*)malloc(sizeof(Etudiant));
    printf("ID: ");
    scanf("%d", &e->id);
    printf("Nom: ");
    scanf("%s", e->nom);
    printf("Moyenne: ");
    scanf("%f", &e->moyenne);
    e->suivant = NULL;
    e->precedent = NULL;
    return e;
}

int longueur(Etudiant* tete) 
{
    int P= 0;
    while (tete != NULL) {
        P++;
        tete = tete->suivant;
    }
    return P;
}

Etudiant* insertion(Etudiant* tete, Etudiant* nouveau, int position) 
{
    if (position <= 0 || tete == NULL) 
	{
        nouveau->suivant = tete;
        if (tete) tete->precedent = nouveau;
        return nouveau;
    }

    Etudiant* courant = tete;
    for (int i = 0; i < position - 1 && courant->suivant != NULL; i++)
        courant = courant->suivant;

    nouveau->suivant = courant->suivant;
    nouveau->precedent = courant;
    if (courant->suivant)
	{
        courant->suivant->precedent = nouveau;
    courant->suivant = nouveau;
    }

    return tete;
}

Etudiant* supprimer_position(Etudiant* tete, int position) 
{
    if (tete == NULL) return NULL;

    Etudiant* courant = tete;
    if (position == 0) {
        tete = tete->suivant;
        if (tete) tete->precedent = NULL;
        free(courant);
        return tete;
    }

    for (int i = 0; i < position && courant != NULL; i++)
        courant = courant->suivant;

    if (courant == NULL) return tete;

    if (courant->precedent)
        courant->precedent->suivant = courant->suivant;
    if (courant->suivant)
        courant->suivant->precedent = courant->precedent;

    free(courant);
    return tete;
}

void afficher_liste(Etudiant* tete) 
{
    while (tete != NULL) {
        printf("ID: %d | Nom: %s | Moyenne: %.2f\n", tete->id, tete->nom, tete->moyenne);
        tete = tete->suivant;
    }
}

Etudiant* derniere_cellule(Etudiant* tete) 
{
    if (tete == NULL) 
	return NULL;
    while (tete->suivant != NULL)
        tete = tete->suivant;
    return tete;
}

void afficher_liste_inverse(Etudiant* dernier) 
{
    while (dernier != NULL) 
	{
        printf("ID: %d | Nom: %s | Moyenne: %.2f\n", dernier->id, dernier->nom, dernier->moyenne);
        dernier = dernier->precedent;
    }
}

int chercher_etudiant(Etudiant* tete, int id) 
{
    while (tete != NULL) {
        if (tete->id == id) return 1;
        tete = tete->suivant;
    }
    return 0;
}

Etudiant* tri(Etudiant* tete) 
{
    if (tete == NULL) return NULL;
    int permut;
    Etudiant *p1, *p2;
    do {
        permut = 0;
        p1 = tete;
        while (p1->suivant != NULL) {
            p2 = p1->suivant;
            if (p1->moyenne > p2->moyenne) {
                int id_tmp = p1->id;
                float moy_tmp = p1->moyenne;
                char nom_tmp[50];
                strcpy(nom_tmp, p1->nom);

                p1->id = p2->id;
                p1->moyenne = p2->moyenne;
                strcpy(p1->nom, p2->nom);

                p2->id = id_tmp;
                p2->moyenne = moy_tmp;
                strcpy(p2->nom, nom_tmp);

                permut = 1;
            }
            p1 = p1->suivant;
        }
    } while (permut);
    return tete;
}

Etudiant* modifier_moyenne(Etudiant* tete, int position, float nouvelle_moyenne) 
{
    Etudiant* courant = tete;
    for (int i = 0; i < position && courant != NULL; i++)
        courant = courant->suivant;
    if (courant != NULL)
        courant->moyenne = nouvelle_moyenne;
    return tete;
}

int main() {
    Etudiant* liste = NULL;
    int choix, pos, id;
    float nouvelle_moy;

    while (1) {
        printf("\n1. Ajouter | 2. Afficher | 3. Supprimer | 4. Inverser | 5. Chercher | 6. Trier | 7. Modifier moyenne | 8. Quitter\n");
        scanf("%d", &choix);
        if (choix == 1) {
            Etudiant* e = creer_etudiant();
            printf("Position d'insertion : ");
            scanf("%d", &pos);
            liste = insertion(liste, e, pos);
        } else if (choix == 2) {
            afficher_liste(liste);
        } else if (choix == 3) {
            printf("Position à supprimer : ");
            scanf("%d", &pos);
            liste = supprimer_position(liste, pos);
        } else if (choix == 4) {
            afficher_liste_inverse(derniere_cellule(liste));
        } else if (choix == 5) {
            printf("ID à chercher : ");
            scanf("%d", &id);
            printf(chercher_etudiant(liste, id) ? "Trouvé\n" : "Non trouvé\n");
        } else if (choix == 6) {
            liste = tri(liste);
            printf("Liste triée.\n");
        } else if (choix == 7) {
            printf("Position à modifier : ");
            scanf("%d", &pos);
            printf("Nouvelle moyenne : ");
            scanf("%f", &nouvelle_moy);
            liste = modifier_moyenne(liste, pos, nouvelle_moy);
        } else {
            break;
        }
    }

    return 0;
}