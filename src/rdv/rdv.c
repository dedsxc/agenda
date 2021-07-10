#include "rdv.h"

// ######################################################################################################################## //
void lireRDV(t_rdv *rdv)
{
    int horaireDebHeure = 0, horaireDebMinute = 0, horaireFinHeure = 0, horaireFinMinute = 0, dateJour = 0, dateMois = 0, dateAn = 0;

    printf("Saisir votre rendez vous : [jj/mm/aaaa] | [00h00] | [00h00] \n");
    scanf("%d/%d/%d %dh%d %dh%d", &dateJour, &dateMois, &dateAn, &horaireDebHeure, &horaireDebMinute, &horaireFinHeure, &horaireFinMinute);
    viderBuffer(); // On vide le buffer
    printf("[Libelle du rendez vous] : ");
    //fgets((*rdv).buffer, sizeof (*rdv).buffer, stdin);
    scanf("%[^\n]", &(*rdv).buffer);
    viderBuffer();

    (*rdv).date.jour = dateJour;
    (*rdv).date.mois = dateMois;
    (*rdv).date.an = dateAn;
    (*rdv).horaireDeb.heure = horaireDebHeure;
    (*rdv).horaireDeb.minute = horaireDebMinute;
    (*rdv).horaireFin.heure = horaireFinHeure;
    (*rdv).horaireFin.minute = horaireFinMinute;
}

// ######################################################################################################################## //
void afficherRDV(t_agenda *agenda)
{
    int i = 0;
    char c[LGMAX_LIBEL];

    if((*agenda).nombreRDV == 0)
    {
        couleur("33");
        printf("\n-> Il n'y a pas de rendez vous dans l'agenda\n");
        couleur("0");
    }
    else if((*agenda).nombreRDV != 0)
    {
        couleur("36");
        printf("\t-------------------------------------\n");
        printf("\t|\t   NOMS LIBELLES    \t    |\n");
        printf("\t-------------------------------------\n");
        

        // AFFICHAGE DE TOUS LES LIBELLES
        for(i = 0; i < (*agenda).nombreRDV ; i++)
        {
            printf("[%d] %s\n",i+1,(*agenda).tableau[i].buffer);
        }
        couleur("0");
        
        // on verifie que la valeur saisie est un entier
        i = 0;
        do
        {
            printf("\nSaisir l'indice du rendez vous à afficher : ");
            fgets(c, sizeof(c), stdin);
            i = atoi(c);
        }while(i == 0);
        
        // on affiche le rdv suivant l'indice
        if(i < 1 || i > agenda->nombreRDV)
        {
            couleur("31");
            printf("Valeur saisie incorrecte\n");
            couleur("0");
        }
        else
        {
            couleur("36");
            printf("\nRDV\t%02d/%02d/%d   %02dh%02d - %02dh%02d\n", (*agenda).tableau[i-1].date.jour,
                       (*agenda).tableau[i-1].date.mois,
                       (*agenda).tableau[i-1].date.an,
                       (*agenda).tableau[i-1].horaireDeb.heure,
                       (*agenda).tableau[i-1].horaireDeb.minute,
                       (*agenda).tableau[i-1].horaireFin.heure,
                       (*agenda).tableau[i-1].horaireFin.minute);
            printf("\t%s\n", (*agenda).tableau[i-1].buffer);
            couleur("0");
        }
    } // FIN IF
}

// ######################################################################################################################## //
int comparerCreneauxRDV(t_rdv *rdv1, t_agenda *agenda)
{

    int heureDebRDV1 = 0, heureFinRDV1 = 0;
    int heureDebRDV2 = 0, heureFinRDV2 = 0;
    int i = 0;
    int jourAgenda = 0, moisAgenda = 0, anAgenda = 0;
    int heureDebAgenda = 0, minuteDebAgenda = 0;
    int heureFinAgenda = 0, minuteFinAgenda = 0;

    // Conversion des heures en minute du rdv entrer par l'utilisateur
    heureDebRDV1 = ((*rdv1).horaireDeb.heure * 60) + (*rdv1).horaireDeb.minute ;
    heureFinRDV1 = ((*rdv1).horaireFin.heure * 60) + (*rdv1).horaireFin.minute ;

    // on compare les horaires et date de chaque rendez vous
    for(i = 0; i < agenda->nombreRDV; i++)
    {
        jourAgenda = agenda->tableau[i].date.jour;
        moisAgenda = agenda->tableau[i].date.mois;
        anAgenda = agenda->tableau[i].date.an;

        heureDebAgenda = agenda->tableau[i].horaireDeb.heure;
        minuteDebAgenda = agenda->tableau[i].horaireDeb.minute;
        heureFinAgenda = agenda->tableau[i].horaireFin.heure;
        minuteFinAgenda = agenda->tableau[i].horaireFin.minute;

        // Conversion des heures en minutes du rdv present dans l'agenda
        heureDebRDV2 = (heureDebAgenda * 60) + minuteDebAgenda;
        heureFinRDV2 = (heureFinAgenda * 60) + minuteFinAgenda;

        // Cas ou RDV1 = RDV2
        if((*rdv1).date.jour == jourAgenda &&
                (*rdv1).date.mois == moisAgenda &&
                (*rdv1).date.an == anAgenda &&
                (*rdv1).horaireDeb.heure == heureDebAgenda &&
                (*rdv1).horaireFin.heure == heureFinAgenda &&
                (*rdv1).horaireDeb.minute == minuteDebAgenda &&
                (*rdv1).horaireFin.minute == minuteFinAgenda )
        {
            return 1;
        }
        //test des autres cas
        if((*rdv1).date.jour == jourAgenda && (*rdv1).date.mois == moisAgenda && (*rdv1).date.an == anAgenda )
        {
            if(heureDebRDV2 <= heureDebRDV1 && heureFinRDV2 > heureDebRDV1) //(heureDebRDV2 <= heureDebRDV1 && heureFinRDV2 > heureDebRDV1)
            {
                return 1;
            }
            else if(heureDebRDV2 < heureFinRDV1 && heureFinRDV2 > heureDebRDV1)
            {
                return 1;
            }
            else if(heureDebRDV2 < heureFinRDV1 && heureDebRDV2 > heureDebRDV1)
            {
                return 1;
            }
            else
            {
                // NE RIEN FAIRE ON PASSE AU RDV SUIVANT
            }
        }
        else
        {
            // NE RIEN FAIRE ON PASSE AU RDV SUIVANT
        }
    }
    return 0;
}

// ######################################################################################################################## //
void afficherTousRDV(t_agenda *agenda)
{
    trierRDV(agenda);

    int i = 0, compteurRDV = 0;

    couleur("36");
    printf("\t-------------------------------------\n");
    printf("\t|\tLISTE DES RENDEZ VOUS\t    |\n");
    printf("\t-------------------------------------\n");
    couleur("0");
    if((*agenda).nombreRDV == 0)
    {
        couleur("33");
        printf("\n-> Aucun rendez vous dans l'agenda :O\n");
        couleur("0");
    }
    else
    {
        for(i = 0; i < (*agenda).nombreRDV ; i++)
        {
            compteurRDV++;
            // AFFICHAGE DES RDV SELON SI LE RDV EST FINI / EN COURS / A VENIR
            switch(evenement(agenda,i))
            {
            case -1 :
                couleur("0");
                printf("%d. Statut [FINI]\tRDV\t%02d/%02d/%d\t%02dh%02d - %02dh%02d\n", compteurRDV,(*agenda).tableau[i].date.jour,
                       (*agenda).tableau[i].date.mois,
                       (*agenda).tableau[i].date.an,
                       (*agenda).tableau[i].horaireDeb.heure,
                       (*agenda).tableau[i].horaireDeb.minute,
                       (*agenda).tableau[i].horaireFin.heure,
                       (*agenda).tableau[i].horaireFin.minute);
                printf("\t\t\t\t%s\n\n", (*agenda).tableau[i].buffer);
                break;
            case 0 :
                couleur("32");
                printf("%d. Statut [EN COURS]\tRDV\t%02d/%02d/%d\t%02dh%02d - %02dh%02d   <-\n", compteurRDV,(*agenda).tableau[i].date.jour,
                       (*agenda).tableau[i].date.mois,
                       (*agenda).tableau[i].date.an,
                       (*agenda).tableau[i].horaireDeb.heure,
                       (*agenda).tableau[i].horaireDeb.minute,
                       (*agenda).tableau[i].horaireFin.heure,
                       (*agenda).tableau[i].horaireFin.minute);
                printf("\t\t\t\t%s\n\n", (*agenda).tableau[i].buffer);
                couleur("0");
                break;
            case 1 :
                couleur("37");
                printf("%d. Statut [A VENIR]\tRDV\t%02d/%02d/%d\t%02dh%02d - %02dh%02d\n", compteurRDV,(*agenda).tableau[i].date.jour,
                       (*agenda).tableau[i].date.mois,
                       (*agenda).tableau[i].date.an,
                       (*agenda).tableau[i].horaireDeb.heure,
                       (*agenda).tableau[i].horaireDeb.minute,
                       (*agenda).tableau[i].horaireFin.heure,
                       (*agenda).tableau[i].horaireFin.minute);
                printf("\t\t\t\t%s\n\n", (*agenda).tableau[i].buffer);
                couleur("0");
                break;
            }
        }
    }
}

// ######################################################################################################################## //
void effacerTousRDV(t_agenda *agenda)
{
    int i;

    for(i = 0; i < agenda->nombreRDV; i ++)
    {
        (*agenda).tableau[i].date.jour = 0;
        (*agenda).tableau[i].date.mois = 0;
        (*agenda).tableau[i].date.an = 0;

        (*agenda).tableau[i].horaireDeb.heure = 0;
        (*agenda).tableau[i].horaireDeb.minute = 0;
        (*agenda).tableau[i].horaireFin.heure = 0;
        (*agenda).tableau[i].horaireFin.minute = 0;

        strcpy((*agenda).tableau[i].buffer,"");
    }
    agenda->nombreRDV = 0;
    couleur("33");
    printf("\n-> Tous les rdv ont ete effaces avec succes ! \n");
    couleur("0");
}

// ######################################################################################################################## //
int evenement(t_agenda *agenda, int i)
{
    int heure = 0, minute = 0, seconde = 0, jourSysteme = 0, moisSysteme = 0, anSysteme = 0;
    int heureEnMinuteDeb = 0, heureEnMinuteFin = 0, heureEnMinuteSysteme = 0;

    RecupererHeureDate(&heure, &minute, &seconde, &jourSysteme, &moisSysteme, &anSysteme);

    // ON CONVERTIT LES HEURES EN MINUTE
    heureEnMinuteSysteme = heure * 60 + minute;
    heureEnMinuteDeb = agenda->tableau[i].horaireDeb.heure * 60 + agenda->tableau[i].horaireDeb.minute;
    heureEnMinuteFin = agenda->tableau[i].horaireFin.heure * 60 + agenda->tableau[i].horaireFin.minute;

    // return 1 si date > dateSysteme
    // return 0 si date == dateSysteme
    // return -1 si date < dateSysteme

    if(agenda->tableau[i].date.an > anSysteme)
    {
        return 1;
    }
    if(agenda->tableau[i].date.an == anSysteme)
    {
        if(agenda->tableau[i].date.mois > moisSysteme)
        {
            return 1;
        }
        else if(agenda->tableau[i].date.mois == moisSysteme)
        {
            if(agenda->tableau[i].date.jour > jourSysteme)
            {
                return 1;
            }
            else if(agenda->tableau[i].date.jour == jourSysteme)
            {
                // date > datesysteme
                if(heureEnMinuteDeb > heureEnMinuteSysteme )
                {
                    return 1;
                }
                // date < datesysteme
                else if (heureEnMinuteDeb < heureEnMinuteSysteme && heureEnMinuteFin <= heureEnMinuteSysteme)
                {
                    return -1;
                }
                // dateDeb <= dateSysteme <= dateFin
                else if (heureEnMinuteSysteme <= heureEnMinuteFin && heureEnMinuteSysteme >= heureEnMinuteDeb)
                {
                    return 0;
                }
            }
            else if (agenda->tableau[i].date.jour < jourSysteme)
            {
                return -1;
            }
        }
        else if (agenda->tableau[i].date.mois < moisSysteme)
        {
            return -1;
        }
    }
    else if (agenda->tableau[i].date.an < anSysteme)
    {
        return -1;
    }
}

// ######################################################################################################################## //
void supprimerRDVFini(t_agenda *agenda)
{
    int j = 0, i = 0;

    // on parcourt le tableau agenda
    do
    {
        // si evenement est fini, on efface, et on decremente le nombre de rdv
        if(evenement(agenda, i) == -1)
        {
            (*agenda).tableau[i-1].date.jour = 0;
            (*agenda).tableau[i-1].date.mois = 0;
            (*agenda).tableau[i-1].date.an = 0;
            (*agenda).tableau[i-1].horaireDeb.heure = 0;
            (*agenda).tableau[i-1].horaireDeb.minute = 0;
            (*agenda).tableau[i-1].horaireFin.heure = 0;
            (*agenda).tableau[i-1].horaireFin.minute = 0;
            strcpy((*agenda).tableau[i-1].buffer, "");
            
            for(j = i - 1; j < (*agenda).nombreRDV - 1; j++)
            {
                (*agenda).tableau[j] = (*agenda).tableau[j+1];
            }
            agenda->nombreRDV--;
            printf("Rendez vous \"%s\" datant du %02d/%02d/%d a ete supprime \n",agenda->tableau[i].buffer,
                                                                                 agenda->tableau[i].date.jour,
                                                                                 agenda->tableau[i].date.mois,
                                                                                 agenda->tableau[i].date.an);
        }
    }while(evenement(agenda,i) == -1);
}