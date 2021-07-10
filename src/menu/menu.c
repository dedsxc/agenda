#include "menu.h"

// ######################################################################################################################## //
int afficherMenu1()
{
    affichageAuteur();
    int choix = 0; char c[20];

    couleur("33");
    printf("\t-------------------------------------\n");
    printf("\t|\t       MENU 1    \t    |\n");
    printf("\t-------------------------------------\n");
    couleur("0");
    printf("\n[1] Creer un nouvel agenda\n");
    printf("[2] Ouvrir un agenda existant\n");
    printf("[3] Quitter\n");

     do
    {
        printf("\nVotre choix : ");

        fgets(c, sizeof(c), stdin);
        choix = atoi(c);
    }
    while (choix == 0 );

    return choix;
}

// ######################################################################################################################## //
int afficherMenu2()
{
    char c[20];
    int choix = 0;

    couleur("33");
    printf("\n\t-------------------------------------\n");
    printf("\t|\t       MENU 2    \t    |\n");
    printf("\t-------------------------------------\n");
    couleur("0");
    printf("\n[1] Afficher un RDV\n");
    printf("[2] Afficher tous les RDV\n");
    printf("[3] Modifier un RDV\n");
    printf("[4] Ajouter un RDV\n");
    printf("[5] Supprimer un RDV\n");
    printf("[6] Supprimer tous les RDV\n");
    printf("[7] Supprimer les rendez vous passe\n");
    printf("[8] Sauvegarder l'agenda\n");
    printf("[9] Afficher la date actuelle \n");
    printf("[10] Supprimer l'agenda actuel \n");
    couleur("32");
    printf("[11] Quitter le programme \n");
    couleur("0");

    do
    {
        printf("\nVotre choix : ");

        fgets(c, sizeof(c), stdin);
        choix = atoi(c);
    }
    while (choix == 0 );

    return choix;

}

// ######################################################################################################################## //
void traiterChoixCreerUnAgenda()
{
    t_agenda agenda = {NULL, 0};
    FILE* fichier = NULL;
    char nomAgenda[LGMAX_AGENDA];
    char chaine[LGMAX_AGENDA];
    int fermerAgenda = 0;

    printf("Nom du fichier agenda : ");
    scanf("%s", nomAgenda);
    viderBuffer();

    /* CONCATENER NOMAGENDA + .TXT */
    sprintf(chaine, "%s.txt", nomAgenda);
    fichier = fopen(chaine, "w+"); /* �crire dans le fichier */
    lireContenuFichierAgenda(fichier, &agenda); /* <------------------ stock tout le contenu dans le tableau agenda */

    if(fichier != NULL)
    {
        couleur("34");
        printf("\n\t\a-> Le fichier %s a ete cree :O\n\n", chaine);
        printf("\n\t\t -> Agenda \"%s\" ouvert \n\n", chaine);
        couleur("0");
        do
        {

            switch(afficherMenu2())
            {
            case 1 :
                afficherRDV(&agenda);
                break;
            case 2 :
                afficherTousRDV(&agenda);
                break;
            case 3 :
                traiterChoixModifierRDV(&agenda);
                break;
            case 4 :
                traiterChoixAjouterRDV(&agenda);
                break;
            case 5 :
                traiterChoixSupprimerRDV(&agenda);
                break;
            case 6 :
                traiterChoixSupprimerTousRDV(&agenda);
                break;
            case 7 :
                supprimerRDVFini(&agenda);
                break;
            case 8 :
                traiterChoixSauvegarderEtFermer(&agenda, fichier, chaine);
                break;
            case 9 :
                afficherDateSysteme();
                break;
            case 10 :
                fclose(fichier);
                if(supprimerAgenda(chaine)==0)
                {
                    exit(0);
                }
                else
                {
                    // ne rien faire
                }
                break;
            case 11 :
                couleur("33");
                printf("\n\t-> A bientot ^^ !\n");
                couleur("0");
                fermerAgenda = 1;
                break;
            default :
                couleur("31");
                printf("choix incoherent veuillez resaisir");
                couleur("0");
                break;

            }
            fclose(fichier);
        }
        while(fermerAgenda != 1);
    }
    else
    {
        couleur("31");
        printf("Le fichier n'a pas ete cree \n");
        couleur("0");
    }
}

// ######################################################################################################################## //
void traiterChoixOuvrirUnAgenda()
{
    t_agenda agenda = {NULL, 0};
    FILE* fichier = NULL;
    char *nomFichier;
    int fermerAgenda = 0;
    DIR *d;
    struct dirent *dir;
    /*########################## LISTE FICHIER .TXT EXISTANT ##############################*/   
    d = opendir("./");
    if (d) {

        printf("Liste des agendas : ");

        int i = 0;
        while ((dir = readdir(d)) != NULL) {
            if (i > 1)
                printf("\n %d. %s",i, dir->d_name);
            i++;
        }
        printf("\n\n");

        closedir(d);
    }

    /*########################## OUVERTURE D'UN FICHIER EXISTANT ##############################*/
    do
    {
        nomFichier = lireNomFichierAgenda();
        fichier = fopen(nomFichier, "r+");
        // lireContenuFichierAgenda(fichier, &agenda); /* <------------------ stock tout le contenu dans le tableau agenda */

        if(fichier != NULL)
        {
            lireContenuFichierAgenda(fichier, &agenda); /* <------------------ stock tout le contenu dans le tableau agenda */

            couleur("34");
            printf("\n\n\t\t -> Agenda \"%s\" ouvert\n\n", nomFichier);
            couleur("0");
            do
            {
                switch(afficherMenu2())
                {
                case 1 :
                    afficherRDV(&agenda);
                    break;
                case 2 :
                    afficherTousRDV(&agenda);
                    break;
                case 3 :
                    traiterChoixModifierRDV(&agenda);
                    break;
                case 4 :
                    traiterChoixAjouterRDV(&agenda);
                    break;
                case 5 :
                    traiterChoixSupprimerRDV(&agenda);
                    break;
                case 6 :
                    traiterChoixSupprimerTousRDV(&agenda);
                    break;
                case 7 :
                    supprimerRDVFini(&agenda);
                    break;
                case 8 :
                    traiterChoixSauvegarderEtFermer(&agenda, fichier, nomFichier);
                    break;
                case 9:
                    afficherDateSysteme();
                    break;
                case 10 :
                    fclose(fichier);
                    if(supprimerAgenda(nomFichier)==0)
                    {
                        exit(0);
                    }
                    else
                    {
                        // ne rien faire
                    }
                    break;
                case 11 :
                    couleur("33");
                    printf("\n\t-> A bientot ^^ !\n");
                    couleur("0");
                    fermerAgenda = 1;
                    break;
                default :
                    couleur("31");
                    printf("choix incoherent veuillez resaisir");
                    couleur("0");
                    break;
                }
                fclose(fichier);
            }
            while(fermerAgenda != 1);
        }
        else
        {
            printf("\n -> Oops ... Le fichier \"%s\" n'existe pas D': \n\n",nomFichier);
        }
    }
    while(fichier == NULL);
    //On libere la memoire dynamiquement alloue (cf. Fonction char *lireNomFichierAgenda() )
    free(nomFichier);
}

// ######################################################################################################################## //
void traiterChoixModifierRDV(t_agenda *agenda)
{
    int i = 0;
    char c[LGMAX_LIBEL];
    int jour = 0, mois = 0, annee = 0, heure = 0, minute = 0, seconde = 0;
    t_rdv rdvUtilisateur;

    /* RECUPERATION DE LA DATE DU SYSTEME */
    RecupererHeureDate(&heure, &minute, &seconde, &jour, &mois, &annee);

    couleur("36");
    printf("\t-------------------------------------\n");
    printf("\t|\t   NOMS LIBELLES    \t    |\n");
    printf("\t-------------------------------------\n");
    couleur("0");
    /* SI NOMBRE DE RDV = 0, IL N'Y A PAS DE RDV DANS L'AGENDA */
    if((*agenda).nombreRDV == 0)
    {
        couleur("33");
        printf("\n-> Il n'y a pas de libelles dans l'agenda :'( \n");
        couleur("0");
    }
    else
    {
        couleur("36");
        /*SINON SI RDV != 0, AFFICHAGE DE TOUS LES LIBELLES */
        for(i = 0; i < (*agenda).nombreRDV ; i++)
        {
            printf("[%d] %s\n",i+1,(*agenda).tableau[i].buffer);
        }
        couleur("0");
        // on verifie que la valeur saisie est un entier
        i = 0;
        do
        {
            printf("\nSaisir l'indice du rendez vous à modifier : ");
            fgets(c, sizeof(c), stdin);
            i = atoi(c);
        }while(i == 0);
        
        // ON AFFICHE LE RDV SUIVANT L'INDICE, RENVOIE UNE ERREUR SI CEST MAL ECRIT
        if(i < 1 || i > agenda->nombreRDV )
        {
            couleur("31");
            printf("Valeur saisie incorrecte\n");
            couleur("0");
        }
        else
        {
            // ON AFFICHE LE RDV
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

            // ON MODIFIE LE RENDEZ VOUS CORRESPONDANT AU LIBELLE 
                couleur("35");
                printf("\t-------------------------------------\n");
                printf("\t|\t   MODIFICATION    \t    |\n");
                printf("\t-------------------------------------\n");
                couleur("0");
                lireRDV(&rdvUtilisateur);
                
                switch(horaireCorrect(&rdvUtilisateur)
                        || dateCorrecte(&rdvUtilisateur)
                        || horairesCoherents(&rdvUtilisateur)
                        || comparerCreneauxRDV(&rdvUtilisateur, agenda)
                        || comparerHoraireSysteme(&rdvUtilisateur))
                {
                case 0 :
                    couleur("32");
                    (*agenda).tableau[i-1] = rdvUtilisateur;
                    printf("\nLe rendez vous \"%s\" a ete modifie :) \n", rdvUtilisateur.buffer);
                    couleur("0");
                    break;
                case 1 :
                    couleur("31");
                    printf("\nErreur sur la saisie [0 -> OK ; 1 -> NOK]\nDATE : %d\nHORAIRE : %d\nCOHERENCE HORAIRE : %d\nCHEVAUCHEMENT CRENEAUX : %d\nCOHERENCE AVEC DATE SYSTEME : %d\n",
                           dateCorrecte(&rdvUtilisateur),
                           horaireCorrect(&rdvUtilisateur),
                           horairesCoherents(&rdvUtilisateur),
                           comparerCreneauxRDV(&rdvUtilisateur, agenda),
                           comparerHoraireSysteme(&rdvUtilisateur));
                    couleur("0");
                    break;
                default :
                    exit(0);
                    break;
                }
        }
    }
    trierRDV(agenda);
}

// ######################################################################################################################## //
void traiterChoixAjouterRDV(t_agenda *agenda)
{
    t_rdv rdvUtilisateur;

    if(agenda->nombreRDV >= 300)
    {
        couleur("31");
        printf("\t-> /!\\ le nombre de rendez vous maximal a ete atteint /!\\ \n");
        couleur("0");
    }
    else
    {
        lireRDV(&rdvUtilisateur);
        horaireCorrect(&rdvUtilisateur);
        dateCorrecte(&rdvUtilisateur);
        switch(horaireCorrect(&rdvUtilisateur)
                || dateCorrecte(&rdvUtilisateur)
                || horairesCoherents(&rdvUtilisateur)
                || comparerCreneauxRDV(&rdvUtilisateur, agenda)
                || comparerHoraireSysteme(&rdvUtilisateur))
        {
        case 0 :
            couleur("32");
            (*agenda).tableau[(*agenda).nombreRDV] = rdvUtilisateur;
            agenda->nombreRDV ++;
            printf("\nLe rendez vous \"%s\" a ete ajouter a l'agenda :) \n", rdvUtilisateur.buffer);
            couleur("0");
            break;
        case 1 :
            couleur("31");
            printf("\nErreur sur la saisie [0 -> OK ; 1 -> NOK]\nDATE : %d\nHORAIRE : %d\nCOHERENCE HORAIRE : %d\nCHEVAUCHEMENT CRENEAUX : %d\nCOHERENCE AVEC DATE SYSTEME : %d\n",
                   dateCorrecte(&rdvUtilisateur),
                   horaireCorrect(&rdvUtilisateur),
                   horairesCoherents(&rdvUtilisateur),
                   comparerCreneauxRDV(&rdvUtilisateur, agenda),
                   comparerHoraireSysteme(&rdvUtilisateur));
            couleur("0");
            break;
        default :
            exit(0);
            break;
        }
    }
    trierRDV(agenda);

}

// ######################################################################################################################## //
void traiterChoixSupprimerRDV(t_agenda *agenda)
{
    int i = 0, j = 0;
    char c[20];

    if((*agenda).nombreRDV == 0)
    {
        couleur("33");
        printf("\n-> Il n'y a pas de rendez vous dans l'agenda\n");
        couleur("0");
    }
    else if((*agenda).nombreRDV != 0)
    {
        /* Si nombre rdv != 0, on affiche les rdv a traiter */
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
            printf("\nSaisir l'indice du rendez vous à supprimer : ");
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
            printf("\nLe rendez vous a bien été supprimé. Sauvegardez pour appliquer les modifications\n");
        }
    } // FIN IF
}

// ######################################################################################################################## //
void traiterChoixSupprimerTousRDV(t_agenda *agenda)
{
    effacerTousRDV(agenda);
}

// ######################################################################################################################## //
void traiterChoixSauvegarderEtFermer(t_agenda *agenda, FILE* fichier, char nomFichierParametre[])
{
    int i = 0;

    /* ON EFFACE LE CONTENU DU FICHIER TEXTE */
    fichier = fopen(nomFichierParametre, "w+");

    trierRDV(agenda);

       
    if(agenda->nombreRDV == 0)
    {
       // NE RIEN FAIRE
    }
    else
    {
        for(i = 0; i < agenda->nombreRDV ; i++)
        {
            fprintf(fichier,"%02d %02d %d:%02d %02d %02d %02d:%s\n",(*agenda).tableau[i].date.jour,
                    (*agenda).tableau[i].date.mois,
                    (*agenda).tableau[i].date.an,
                    (*agenda).tableau[i].horaireDeb.heure,
                    (*agenda).tableau[i].horaireDeb.minute,
                    (*agenda).tableau[i].horaireFin.heure,
                    (*agenda).tableau[i].horaireFin.minute,
                    (*agenda).tableau[i].buffer);
            
        }
    }
    couleur("32");
    printf("\n\t-> SAUVEGARDE REUSSI !\n");
    couleur("0");
}

// ######################################################################################################################## //
char *lireNomFichierAgenda()
{
    char nomAgenda[50];
    char* chaine = malloc(50 *sizeof(char));

    printf("Saisir le nom de l'agenda existant : ");
    scanf("%s", nomAgenda);
    viderBuffer();
    sprintf(chaine, "%s.txt", nomAgenda);

    return chaine;
}

// ######################################################################################################################## //
void lireContenuFichierAgenda(FILE *fichier, t_agenda *agenda)
{
    char ligne[80]; /* nombre maximum de caracteres de la ligne */
    int i = 0;
    int jour = 0, mois = 0, an = 0, heureDeb = 0, minuteDeb = 0, heureFin = 0, minuteFin = 0;
    int heureSysteme = 0, minuteSysteme = 0, secondeSysteme = 0, jourSysteme = 0, moisSysteme = 0, anSysteme = 0;
    int resultatDifference = 0, heureSystemeEnMinute = 0, heureRdvEnMinute = 0;
    char messageRendezVous[25] = "rdv dans 15min OKLM : ";


    RecupererHeureDate(&heureSysteme, &minuteSysteme, &secondeSysteme, &jourSysteme, &moisSysteme, &anSysteme);

    /* STOCK CHAQUE LIGNE DU FICHIER DANS TABLEAU DE TYPE t_agenda */

    while( fgets(ligne, sizeof(ligne), fichier) != NULL )
    {
        /* ON VERIFIE QU'ON RECUPERE BIEN TOUS LES ELEMENTS EN ENTREE */
        if(sscanf(ligne,"%02d %02d %d:%02d %02d %02d %02d:%[^\n]", &jour, &mois, &an, &heureDeb, &minuteDeb, &heureFin, &minuteFin, (*agenda).tableau[i].buffer) == 8)
        {
            agenda->tableau[i].flag = 0;
            /* AFFECTATION DES VARIABLES (JOUR/MOIS/AN)  DANS LA STRUCTURE t_date */
            (*agenda).tableau[i].date.jour = jour;
            (*agenda).tableau[i].date.mois = mois;
            (*agenda).tableau[i].date.an = an;

            (*agenda).tableau[i].horaireDeb.heure = heureDeb;
            (*agenda).tableau[i].horaireDeb.minute = minuteDeb;
            (*agenda).tableau[i].horaireFin.heure = heureFin;
            (*agenda).tableau[i].horaireFin.minute = minuteFin;
        }
        /* ON TEST SI LE RDV EST A 15 MINUTES AVANT L'HEURE */
        if(jour == jourSysteme && mois == moisSysteme && an == anSysteme)
        {
            /* CONVERTIR LES HEURES EN MINUTES */
            heureSystemeEnMinute = (heureSysteme*60) + minuteSysteme;
            heureRdvEnMinute = (heureDeb * 60) + minuteDeb;

            /* ON CALCULE LA DIFFERENCE ENTRE SES HEURES */
            resultatDifference = heureRdvEnMinute - heureSystemeEnMinute;

            /* SI LA DIFFERENCE = 15MIN , ON AFFICHE LE POPUP RAPPEL*/
            if(resultatDifference == 15)
            {
                /* ON AFFICHE LE POPUP RAPPEL */
                /* concatenation des chaines de caracteres */
                strcat(messageRendezVous, (*agenda).tableau[i].buffer);
                // MessageBox(0, messageRendezVous, "RAPPEL RDV hihi :D", MB_ICONASTERISK);
            }

        }
        i++;
    }

    /* ON RECUPERE LE NOMBRE DE RENDEZ VOUS GRACE AU COMPTAGE DE LIGNE PAR i */
    (*agenda).nombreRDV = i;
}

// ######################################################################################################################## //
void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

// ######################################################################################################################## //
void affichageAuteur(void)
{
    printf("Auteurs : \tdedsec\n");
    printf("Projet  : \tAgenda\n\n");
}

// ######################################################################################################################## //
int supprimerAgenda(char nomFichier[])
{
    int choix = 0;

    printf("\t-> Etes vous sur de vouloir supprimer l'agenda %s ? [0 : OUI / 1 : NON]\n", nomFichier);
    scanf("%d", &choix);
    viderBuffer();

    switch(choix)
    {
    case 0 :
        if(remove(nomFichier)==0)
        {
            printf("\n\t-> L'agenda \"%s\" a ete efface\n", nomFichier);
            printf("\t Fermeture du programme ...\n");
            return 0;
        }
        break;
    default :
        printf("\n\t-> Le fichier %s n'a pas ete supprime \n", nomFichier);
        return 1;

    }
}

// ######################################################################################################################## //
void trierRDV(t_agenda *agenda)
{
    int i = 0, check = 0;
    int horaireConvertiDebRDV1 = 0, horaireConvertiDebRDV2 = 0;
    t_rdv tamponRDV;

    do
    {
        check = 0;
        // parcours du tableau jusqu'a nbrdv - 1
        for(i = 0 ; i < agenda->nombreRDV - 1 ; i++)
        {

            // METTRE ICI CONVERSION HORAIRE HEURE EN MINUTE DES DEUX RDV DU TABLEAU TESTER
            horaireConvertiDebRDV1 = (agenda->tableau[i].horaireDeb.heure * 60) + agenda->tableau[i].horaireDeb.minute;
            horaireConvertiDebRDV2 = (agenda->tableau[i+1].horaireDeb.heure * 60) + agenda->tableau[i+1].horaireDeb.minute;

            // ON TEST SI RDV 1 > RDV 2
            if(agenda->tableau[i].date.an > agenda->tableau[i+1].date.an)
            {
                // On interchange les rdv si le premier rdv est superieur au deuxieme
                tamponRDV = agenda->tableau[i];
                agenda->tableau[i] = agenda->tableau[i+1];
                agenda->tableau[i+1] = tamponRDV;
                check = 1;
            }
            else if(agenda->tableau[i].date.an == agenda->tableau[i+1].date.an)
            {
                if(agenda->tableau[i].date.mois > agenda->tableau[i+1].date.mois)
                {
                    // On interchange les rdv si le premier rdv est superieur au deuxieme
                    tamponRDV = agenda->tableau[i];
                    agenda->tableau[i] = agenda->tableau[i+1];
                    agenda->tableau[i+1] = tamponRDV;
                    check = 1;
                }
                else if(agenda->tableau[i].date.mois == agenda->tableau[i+1].date.mois)
                {
                    if(agenda->tableau[i].date.jour > agenda->tableau[i+1].date.jour)
                    {
                        // On interchange les rdv si le premier rdv est superieur au deuxieme
                        tamponRDV = agenda->tableau[i];
                        agenda->tableau[i] = agenda->tableau[i+1];
                        agenda->tableau[i+1] = tamponRDV;
                        check = 1;
                    }
                    else if(agenda->tableau[i].date.jour == agenda->tableau[i+1].date.jour)
                    {
                        if(horaireConvertiDebRDV1 > horaireConvertiDebRDV2)
                        {
                            // On interchange les rdv si le premier rdv est superieur au deuxieme
                            tamponRDV = agenda->tableau[i];
                            agenda->tableau[i] = agenda->tableau[i+1];
                            agenda->tableau[i+1] = tamponRDV;
                            check = 1;
                        }
                        else
                        {
                            // NE RIEN FAIRE
                        }
                    }
                    else
                    {
                        // NE RIEN FAIRE
                    }
                }
                else
                {
                    // NE RIEN FAIRE
                }
            }
            else
            {
                // NE RIEN FAIRE
            }
        }

    }
    while(check != 0);
}
