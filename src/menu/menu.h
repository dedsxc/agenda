#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define NBMAX_RDV 300
#define LGMAX_LIBEL 50
#define LGMAX_AGENDA 50
#define couleur(param) printf("\033[%sm",param)

#define LGMAX_LIBEL 50

// ################ DEFINITION STRUCTURE ################### //
typedef struct t_date t_date;
struct t_date
{
    int jour;
    int mois;
    int an;
};

typedef struct t_horaire t_horaire;
struct t_horaire
{
    int heure;
    int minute;
};

typedef struct t_rdv t_rdv;
struct t_rdv
{
    t_date date;
    t_horaire horaireDeb;
    t_horaire horaireFin;
    char buffer[LGMAX_LIBEL];
    int flag;
};

typedef struct t_agenda t_agenda;
struct t_agenda
{
    t_rdv tableau[300];
    int nombreRDV;
};


int afficherMenu1();
int afficherMenu2();
void affichageAuteur(void);

void traiterChoixCreerUnAgenda();
void traiterChoixOuvrirUnAgenda();
void traiterChoixModifierRDV(t_agenda *agenda);
void traiterChoixAjouterRDV(t_agenda *agenda);
void traiterChoixSupprimerRDV(t_agenda *agenda);
void traiterChoixSupprimerTousRDV(t_agenda *agenda);
void traiterChoixSauvegarderEtFermer(t_agenda *agenda, FILE* fichier, char nomFichierParametre[]);
int supprimerAgenda(char nomFichier[]);

void trierRDV(t_agenda *agenda);

char *lireNomFichierAgenda();
void lireContenuFichierAgenda(FILE *fichier, t_agenda *agenda);

void viderBuffer();

//void Color(int couleurFond, int couleurTexte);

#endif // MENU_H_INCLUDED
