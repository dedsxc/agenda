#include "horaire.h"

#define couleur(param) printf("\033[%sm",param)

// ######################################################################################################################## //
int comparerHoraireSysteme(t_rdv *rdv)
{
    int heureSysteme = 0, minuteSysteme = 0, secondeSysteme = 0, jourSysteme = 0, moisSysteme = 0, anSysteme = 0;
    // RECUPERATION DE DATE + HEURE DU SYSTEME
    RecupererHeureDate(&heureSysteme, &minuteSysteme, &secondeSysteme, &jourSysteme, &moisSysteme, &anSysteme);

    if((*rdv).date.an > anSysteme)
    {
        return 0;
    }
    if((*rdv).date.an == anSysteme)
    {
        if((*rdv).date.mois > moisSysteme)
        {
            return 0;
        }
        else if((*rdv).date.mois == moisSysteme)
        {
            if((*rdv).date.jour > jourSysteme)
            {
                return 0;
            }
            else if((*rdv).date.jour == jourSysteme)
            {
                if((*rdv).horaireDeb.heure > heureSysteme)
                {
                    return 0;
                }
                else if((*rdv).horaireDeb.heure == heureSysteme)
                {
                    if((*rdv).horaireDeb.minute >= minuteSysteme)
                    {
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }
}

// ######################################################################################################################## //
int horaireCorrect(t_rdv *rdv)
{

    if((*rdv).horaireDeb.heure < 24 &&
            (*rdv).horaireDeb.heure >= 0 &&
            (*rdv).horaireDeb.minute < 60 &&
            (*rdv).horaireDeb.minute >= 0 &&
            (*rdv).horaireFin.heure < 24 &&
            (*rdv).horaireFin.heure >= 0 &&
            (*rdv).horaireFin.minute < 60 &&
            (*rdv).horaireFin.minute >= 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}

// ######################################################################################################################## //
void lireHoraire(t_horaire *horaire)
{
    int heure = 0, minute = 0;

    printf("Saisir horaire [00h00] \n");
    scanf("%dh%d", &heure, &minute);

    (*horaire).heure = heure;
    (*horaire).minute = minute;
}

// ######################################################################################################################## //
void afficherHoraire(t_horaire *horaire)
{
    printf("\n\t%02dh%02d", (*horaire).heure, (*horaire).minute);
}

// ######################################################################################################################## //
int horairesCoherents(t_rdv *rdv)
{
    // TANT QUE HEURE DEBUT SUPERIEUR ou EGAL A HEURE FIN FAIRE
    while((*rdv).horaireDeb.heure >= (*rdv).horaireFin.heure)
    {
        // TANT QUE HEURE DEB = HEURE FIN FAIRE
        while((*rdv).horaireDeb.heure == (*rdv).horaireFin.heure)
        {
            // SI MINUTE DEBUT INFERIEUR A MINUTE FIN, OK !!!
            if((*rdv).horaireDeb.minute <= (*rdv).horaireFin.minute)
            {
                return 0;
            }
            // SINON CEST FAUX
            else
            {
                return 1;
            }
        }
        // FAUX SI HEURE DEBUT SUPERIEUR A HEURE FIN
        return 1;
    }
    return 0;
}

// ######################################################################################################################## //
void RecupererHeureDate(int *pointeurHeure, int *pointeurMinute, int *pointeurSeconde, int *pointeurJour, int *pointeurMois, int *pointeurAn)
{
    time_t timer1;
    time(&timer1);
    struct tm *newTime1;
    newTime1 = localtime(&timer1);

    *pointeurJour = newTime1->tm_mday;
    *pointeurMois = newTime1->tm_mon + 1;
    *pointeurAn = newTime1->tm_year + 1900;
    *pointeurHeure = newTime1->tm_hour;		// Les heures sont dans "heures"
    *pointeurMinute = newTime1->tm_min;		// Les minutes sont dans "minutes"
    *pointeurSeconde = newTime1->tm_sec;		// Les secondes sont dans "secondes"
}

// ######################################################################################################################## //
void afficherDateSysteme(void)
{
    int heureSysteme = 0, minuteSysteme = 0, secondeSysteme = 0, jourSysteme = 0, moisSysteme = 0, anSysteme = 0;
    // on recupere l'heure du systeme
    RecupererHeureDate(&heureSysteme, &minuteSysteme, &secondeSysteme, &jourSysteme, &moisSysteme, &anSysteme);
    couleur("35");
    printf("\nDate actuelle \t ->\t %02d/%02d/%d\nHeure actuelle \t ->\t %02dh%02d : %02d\n", jourSysteme, moisSysteme, anSysteme, heureSysteme, minuteSysteme, secondeSysteme);
    couleur("0");
}


