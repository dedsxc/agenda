#include "date.h"

// ######################################################################################################################## //
void lireDate(t_date *date)
{
    int jour = 0, mois = 0, annee = 0;

    printf("Saisir une date (jj/mm/aaaa) \n");
    scanf("%d/%d/%d", &jour, &mois, &annee);

    (*date).jour = jour; // pointeur sur struct t_date date.jour. Le pointeur va modifier la variable date.jour par jour
    (*date).mois = mois; // (*date).mois peut aussi s'ecrire date->mois
    (*date).an = annee;
}

// ######################################################################################################################## //
void afficherDate(t_date *date)
{
    printf("\n\t%02d/%02d/%d \n", date->jour, date->mois, date->an );
}

// ######################################################################################################################## //
int dateCorrecte(t_rdv *rdv)
{

    int fevrier = 0;

    // TEST JOUR
    if((*rdv).date.jour <= 31 && (*rdv).date.jour >= 1)
    {

    }
    else
    {
        return 1;
    }

    // TEST MOIS
    switch((*rdv).date.mois)
    {
    case 1:
        if(rdv->date.jour <= 31)
        {
                   return 0;
        }
        else
        {
            return 1;
        }
        break;

    case 2:
        // TEST ANNEE BISSEXSTILE => voir wikipedia
        fevrier = (*rdv).date.an % 4;

        if(fevrier == 0 && (*rdv).date.jour <= 29 && (*rdv).date.jour >= 1)
        {
            return 0;
        }
        else if(fevrier != 0  && (*rdv).date.jour <= 28 && (*rdv).date.jour >= 1)
        {
            return 0;
        }
        else
        {
            return 1;
        }
        break;

    case 3:
        if(rdv->date.jour <= 31)
        {
                   return 0;
        }
        else
        {
            return 1;
        }
        break;

    case 4:
        if(rdv->date.jour <= 30)
        {
                   return 0;
        }
        else
        {
            return 1;
        }
        break;

    case 5:
        if(rdv->date.jour <= 31)
        {
                   return 0;
        }
        else
        {
            return 1;
        }
        break;
    case 6:
        if(rdv->date.jour <= 30)
        {
                   return 0;
        }
        else
        {
            return 1;
        }
        break;
    case 7:
        if(rdv->date.jour <= 31)
        {
                   return 0;
        }
        else
        {
            return 1;
        }
        break;
    case 8:
        if(rdv->date.jour <= 31)
        {
                   return 0;
        }
        else
        {
            return 1;
        }
        break;
    case 9:
        if(rdv->date.jour <= 30)
        {
                   return 0;
        }
        else
        {
            return 1;
        }
        break;
    case 10:
        if(rdv->date.jour <= 31)
        {
                   return 0;
        }
        else
        {
            return 1;
        }
        break;
    case 11:
        if(rdv->date.jour <= 30)
        {
                   return 0;
        }
        else
        {
            return 1;
        }
        break;
    case 12:
        if(rdv->date.jour <= 31)
        {
                   return 0;
        }
        else
        {
            return 1;
        }
        break;

    default:
        return 1;
    }
}
