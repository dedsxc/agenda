#ifndef RDV_H_INCLUDED
#define RDV_H_INCLUDED

#include <string.h>

#include "../menu/menu.h"
#include "../date/horaire.h"

#define couleur(param) printf("\033[%sm",param)

void lireRDV(t_rdv *rdv);
void afficherRDV(t_agenda *agenda);
int comparerCreneauxRDV(t_rdv *rdv1, t_agenda *agenda);
void afficherTousRDV(t_agenda *agenda);
void effacerTousRDV(t_agenda *agenda);
int evenement(t_agenda *agenda, int i);
void supprimerRDVFini(t_agenda *agenda);

#endif // RDV_H_INCLUDED

