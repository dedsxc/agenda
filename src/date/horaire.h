#ifndef HORAIRE_H_INCLUDED
#define HORAIRE_H_INCLUDED

#include <time.h>

#include "../menu/menu.h"

int horaireCorrect(t_rdv *rdv);
void lireHoraire(t_horaire *horaire);
void afficherHoraire(t_horaire *horaire);
int horairesCoherents(t_rdv *rdv);
void RecupererHeureDate(int *pointeurHeure, int *pointeurMinute, int *pointeurSeconde, int *pointeurJour, int *pointeurMois, int *pointeurAn);
void afficherDateSysteme(void);
int comparerHoraireSysteme(t_rdv *rdv);

#endif // HORAIRE_H_INCLUDED
