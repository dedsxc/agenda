#include "rdv/rdv.h"
#include "date/date.h"
#include "date/horaire.h"
#include "menu/menu.h"

int main(void)
{
    printf("\033[H\033[2J");
    switch(afficherMenu1())
    {
    case 1 :
        traiterChoixCreerUnAgenda();
        break;

    case 2 :
        traiterChoixOuvrirUnAgenda();
        break;

    case 3 :
        return 0;
        break;

    default :
        printf("erreur sur la saisie \n");
        break;
    }

    return 0;
}
