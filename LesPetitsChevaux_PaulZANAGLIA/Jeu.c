#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeu.h"
#include <windows.h>


//Position Y et X de la periphérie du plateau
int Y[98] = { 8,8,8,8,8,8,8,9,10,11,
				12,13,14,14,14,13,12,11,10,
				9,8,8,8,8,8,8,8,7,6,
				6,6,6,6,6,6,5,4,3,2,
				1,0,0,0,1,2,3,4,5,6,
				6,6,6,6,6,6,7,8,8,8,
				8,8,8,8,9,10,11,12,13,14,
				14,14,13,12,11,10,9,8,8,8,
				8,8,8,8,7,6,6,6,6,6,
				6,6,5,4,3,2,1,0,0 };
int X[98] = { 0,1,2,3,4,5,6,6,6,6,6,
			6,6,7,8,8,8,8,8,8,8,
			9,10,11,12,13,14,14,14,13,12,
			11,10,9,8,8,8,8,8,8,8,
			7,6,6,6,6,6,6,6,5,4,
			3,2,1,0,0,0,1,2,3,4,
			5,6,6,6,6,6,6,6,7,8,
			8,8,8,8,8,8,9,10,11,12,
			13,14,14,14,13,12,11,10,9,8,
			8,8,8,8,8,8,7 };

//Position des emplacements dans l'écurie
int EcuY[16] = { 11,12,11,12,11,12,11,12,2,3,2,3,2,3,2,3 };
int EcuX[16] = { 2,2,3,3,11,11,12,12,11,11,12,12,2,2,3,3 };

//Position des cases des échelles
int EchYJ[32] = { 7,7,7,7,7,7,7,7,14,13,
					12,11,10,9,8,7,7,7,7,7,
					7,7,7,7,0,1,2,3,4,5,6,7 };
int EchXJ[32] = { 0,1,2,3,4,5,6,7,7,7,
					7,7,7,7,7,7,14,13,12,11,
					10,9,8,7,7,7,7,7,7,7,7,7 };

//Simulation du dé, renvoie un chiffre entre 1 et 6
short roll(void)
{
	short nbr_rand = 0;
	srand(time(NULL));
	nbr_rand = rand() % (7 - 1) + 1;
	return nbr_rand;
}

//Simulation du lancer de dé
short lancer(struct joueur* J, short i)
{
	char choix = 'n';
	short resultat;
	if (J[i].bot != 1)
	{
		while (1)
		{
			if (choix != 'y' && choix != '\n')
			{
				printf("Pour lancer le de, appuyez sur y !\n");
			}
			else if (choix == 'y') { break; }
			choix = getchar();
		}
		printf("Ok de lancé...\n");
	}
	resultat = roll();
	printf("Vous avez obtenu un %hi !\n", resultat);
	return resultat;
}

//Renvoie 1 si le resultat du lancer est un 6
short RollIs6(joueur* J, short i)
{
	if (lancer(J, i) == 6) { return 1; }
	else { return 0; }
}

//Initialisation des structures joueurs et de leurs valeurs
int InitJ(void)
{
	int nbJ;
	printf("Combien de joueurs souhaitent jouer ?\n");
	scanf_s("%d", &nbJ);
	while (nbJ > 4 || nbJ < 1)
	{
		printf("Veuiller entrer un nombre de joueurs compris entre 1 et 4.\n");
		scanf_s("%d", &nbJ);
	}
	printf("Ok ! Il y a donc %d joueur(s).\n", nbJ);
	return nbJ;
}
joueur* InitstructJ(int joueurs, struct joueur* J)
{
	if (joueurs == 3)
	{
		J[0].bot = 0;
		J[1].bot = 0;
		J[2].bot = 0;
		J[3].bot = 1;
	}
	else if (joueurs == 2)
	{
		J[0].bot = 0;
		J[1].bot = 0;
		J[2].bot = 1;
		J[3].bot = 1;
	}
	else if (joueurs == 1)
	{
		J[0].bot = 0;
		J[1].bot = 1;
		J[2].bot = 1;
		J[3].bot = 1;
	}
	else
	{
		J[0].bot = 0;
		J[1].bot = 0;
		J[2].bot = 0;
		J[3].bot = 0;
	}

	J[0].posCh1 = EJ1CH1;
	J[0].posCh2 = EJ1CH2;
	J[0].posCh3 = EJ1CH3;
	J[0].posCh4 = EJ1CH4;

	J[1].posCh1 = EJ2CH1;
	J[1].posCh2 = EJ2CH2;
	J[1].posCh3 = EJ2CH3;
	J[1].posCh4 = EJ2CH4;

	J[2].posCh1 = EJ3CH1;
	J[2].posCh2 = EJ3CH2;
	J[2].posCh3 = EJ3CH3;
	J[2].posCh4 = EJ3CH4;

	J[3].posCh1 = EJ4CH1;
	J[3].posCh2 = EJ4CH2;
	J[3].posCh3 = EJ4CH3;
	J[3].posCh4 = EJ4CH4;

	for (int k = 0; k < 4; k++)
	{
		J[k].scaleCh1 = 0;
		J[k].scaleCh2 = 0;
		J[k].scaleCh3 = 0;
		J[k].scaleCh4 = 0;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			J[i].acc[j] = 1;
			J[i].lastroll[j] = 0;
		}
	}

	J[0].symb = '$';
	J[1].symb = '*';
	J[2].symb = '+';
	J[3].symb = '%';

	return J;
}

//Traitement du plateau de jeu, Initialisation,placement des pions en debut de jeu, et affichage du plateau de jeu
void InitTab(int tab[15][15])
{
	//Preparation du Plateau de jeu
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			//Ecurie
			if (j < 6 && i < 6) { tab[i][j] = 'B'; }
			else if (j >= 9 && i < 6) { tab[i][j] = 'R'; }
			else if (j < 6 && i > 8) { tab[i][j] = 'J'; }
			else if (j >= 9 && i > 8) { tab[i][j] = 'V'; }

			//Case des echelles
			else if ((i == 7 && (j == 1 || j == 13)) || (j == 7 && (i == 1 || i == 13))) { tab[i][j] = '1'; }
			else if ((i == 7 && (j == 2 || j == 12)) || (j == 7 && (i == 2 || i == 12))) { tab[i][j] = '2'; }
			else if ((i == 7 && (j == 3 || j == 11)) || (j == 7 && (i == 3 || i == 11))) { tab[i][j] = '3'; }
			else if ((i == 7 && (j == 4 || j == 10)) || (j == 7 && (i == 4 || i == 10))) { tab[i][j] = '4'; }
			else if ((i == 7 && (j == 5 || j == 9)) || (j == 7 && (i == 5 || i == 9))) { tab[i][j] = '5'; }
			else if ((i == 7 && (j == 6 || j == 8)) || (j == 7 && (i == 6 || i == 8))) { tab[i][j] = '6'; }

			else if (i == 7 && j == 7) { tab[i][j] = 'A'; } //Arrivée
			else { tab[i][j] = '0'; } //Parcours
		}
	}
}
void MajTab(int tab[15][15], struct joueur* J)
{
	tab[EcuX[J[0].posCh1]][EcuY[J[0].posCh1]] = J[0].symb;
	tab[EcuX[J[0].posCh2]][EcuY[J[0].posCh2]] = J[0].symb;
	tab[EcuX[J[0].posCh3]][EcuY[J[0].posCh3]] = J[0].symb;
	tab[EcuX[J[0].posCh4]][EcuY[J[0].posCh4]] = J[0].symb;

	tab[EcuX[J[1].posCh1]][EcuY[J[1].posCh1]] = J[1].symb;
	tab[EcuX[J[1].posCh2]][EcuY[J[1].posCh2]] = J[1].symb;
	tab[EcuX[J[1].posCh3]][EcuY[J[1].posCh3]] = J[1].symb;
	tab[EcuX[J[1].posCh4]][EcuY[J[1].posCh4]] = J[1].symb;

	tab[EcuX[J[2].posCh1]][EcuY[J[2].posCh1]] = J[2].symb;
	tab[EcuX[J[2].posCh2]][EcuY[J[2].posCh2]] = J[2].symb;
	tab[EcuX[J[2].posCh3]][EcuY[J[2].posCh3]] = J[2].symb;
	tab[EcuX[J[2].posCh4]][EcuY[J[2].posCh4]] = J[2].symb;

	tab[EcuX[J[3].posCh1]][EcuY[J[3].posCh1]] = J[3].symb;
	tab[EcuX[J[3].posCh2]][EcuY[J[3].posCh2]] = J[3].symb;
	tab[EcuX[J[3].posCh3]][EcuY[J[3].posCh3]] = J[3].symb;
	tab[EcuX[J[3].posCh4]][EcuY[J[3].posCh4]] = J[3].symb;
}
void AffTab(int tab[15][15])
{
	for (int j = 0; j < 15; j++)
	{
		for (int i = 0; i < 15; i++)
		{
			printf("%2c", tab[j][i]);
		}
		printf("\n");
	}
}

//Verification des cases pour savoir si elles sont occupées par un cheval ou pas en fonction du cheval joué
//et renvoie le premier cheval qui avait atteint la case à l'écurie
void CheckPosCh1(struct joueur* J, int tab[15][15], short k)
{

	int dif;
	for (int i = 0; i < 4; i++)
	{
		dif = J[k].posCh1;
		if (((X[J[k].posCh1] == X[J[i].posCh2]) && (Y[J[k].posCh1] == Y[J[i].posCh2])) || ((X[J[k].posCh1] == EchXJ[J[i].posCh2]) && (Y[J[k].posCh1] == EchYJ[J[i].posCh2])))
		{
			if (i == 0) { J[i].posCh2 = EJ1CH2; J[i].scaleCh2 = 0;}
			else if (i == 1) { J[i].posCh2 = EJ2CH2; J[i].scaleCh2 = 0;}
			else if (i == 2) { J[i].posCh2 = EJ3CH2; J[i].scaleCh2 = 0;}
			else if (i == 3) { J[i].posCh2 = EJ4CH2; J[i].scaleCh2 = 0;}
			tab[EcuX[J[i].posCh2]][EcuY[J[i].posCh2]] = J[i].symb;
		}
		else if (((X[J[k].posCh1] == X[J[i].posCh3]) && (Y[J[k].posCh1] == Y[J[i].posCh3])) || ((X[J[k].posCh1] == EchXJ[J[i].posCh3]) && (Y[J[k].posCh1] == EchYJ[J[i].posCh3])))
		{
			if (i == 0) { J[i].posCh3 = EJ1CH3; J[i].scaleCh3 = 0;}
			else if (i == 1) { J[i].posCh3 = EJ2CH3; J[i].scaleCh3 = 0; }
			else if (i == 2) { J[i].posCh3 = EJ3CH3; J[i].scaleCh3 = 0;}
			else if (i == 3) { J[i].posCh3 = EJ4CH3; J[i].scaleCh3 = 0;}
			tab[EcuX[J[i].posCh3]][EcuY[J[i].posCh3]] = J[i].symb;
		}
		else if (((X[J[k].posCh1] == X[J[i].posCh4]) && (Y[J[k].posCh1] == Y[J[i].posCh4])) || ((X[J[k].posCh1] == EchXJ[J[i].posCh4]) && (Y[J[k].posCh1] == EchYJ[J[i].posCh4])))
		{
			if (i == 0) { J[i].posCh4 = EJ1CH4; J[i].scaleCh4 = 0;}
			else if (i == 1) { J[i].posCh4 = EJ2CH4;  J[i].scaleCh4 = 0; }
			else if (i == 2) { J[i].posCh4 = EJ3CH4;  J[i].scaleCh4 = 0; }
			else if (i == 3) { J[i].posCh4 = EJ4CH4;  J[i].scaleCh4 = 0; }
			tab[EcuX[J[i].posCh4]][EcuY[J[i].posCh4]] = J[i].symb;
		}
		else if (((X[J[k].posCh1] == X[J[i].posCh1]) && (Y[J[k].posCh1] == Y[J[i].posCh1]) && k != i) || ((X[J[k].posCh1] == EchXJ[J[i].posCh1]) && (EchYJ[J[k].posCh1] == EchYJ[J[i].posCh1]) && k != i))
		{
			if (i == 0) { J[i].posCh1 = EJ1CH1; J[i].scaleCh1 = 0; }
			else if (i == 1) { J[i].posCh1 = EJ2CH1; J[i].scaleCh1 = 0;}
			else if (i == 2) { J[i].posCh1 = EJ3CH1; J[i].scaleCh1 = 0;}
			else if (i == 3) { J[i].posCh1 = EJ4CH1; J[i].scaleCh1 = 0;}
			tab[EcuX[J[i].posCh1]][EcuY[J[i].posCh1]] = J[i].symb;
		}
	}
}
void CheckPosCh2(struct joueur* J, int tab[15][15], short k)
{
	int dif;
	for (int i = 0; i < 4; i++)
	{
		dif = J[k].posCh2;
		if (((X[J[k].posCh2] == X[J[i].posCh2]) && (Y[J[k].posCh2] == Y[J[i].posCh2]) && k != i) || ((X[J[k].posCh2] == EchXJ[J[i].posCh2]) && (EchYJ[J[k].posCh2] == EchYJ[J[i].posCh2]) && k != i))
		{
			if (i == 0) { J[i].posCh2 = EJ1CH2; J[i].scaleCh2 = 0;}
			else if (i == 1) { J[i].posCh2 = EJ2CH2; J[i].scaleCh2 = 0;}
			else if (i == 2) { J[i].posCh2 = EJ3CH2; J[i].scaleCh2 = 0;}
			else if (i == 3) { J[i].posCh2 = EJ4CH2; J[i].scaleCh2 = 0;}
			tab[EcuX[J[i].posCh2]][EcuY[J[i].posCh2]] = J[i].symb;
		}
		else if ((X[J[k].posCh2] == X[J[i].posCh3] && Y[J[k].posCh2] == Y[J[i].posCh3]) || (X[J[k].posCh2] == EchXJ[J[i].posCh3] && Y[J[k].posCh2] == EchYJ[J[i].posCh3]))
		{
			if (i == 0) { J[i].posCh3 = EJ1CH3; J[i].scaleCh3 = 0;}
			else if (i == 1) { J[i].posCh3 = EJ2CH3; J[i].scaleCh3 = 0;}
			else if (i == 2) { J[i].posCh3 = EJ3CH3; J[i].scaleCh3 = 0;}
			else if (i == 3) { J[i].posCh3 = EJ4CH3; J[i].scaleCh3 = 0;}
			tab[EcuX[J[i].posCh3]][EcuY[J[i].posCh3]] = J[i].symb;
		}
		else if ((X[J[k].posCh2] == X[J[i].posCh4] && Y[J[k].posCh2] == Y[J[i].posCh4]) || (X[J[k].posCh2] == EchXJ[J[i].posCh4] && Y[J[k].posCh2] == EchYJ[J[i].posCh4]))
		{
			if (i == 0) { J[i].posCh4 = EJ1CH4; J[i].scaleCh4 = 0;}
			else if (i == 1) { J[i].posCh4 = EJ2CH4; J[i].scaleCh4 = 0;}
			else if (i == 2) { J[i].posCh4 = EJ3CH4; J[i].scaleCh4 = 0;}
			else if (i == 3) { J[i].posCh4 = EJ4CH4; J[i].scaleCh4 = 0;}
			tab[EcuX[J[i].posCh4]][EcuY[J[i].posCh4]] = J[i].symb;
		}
		else if ((X[J[k].posCh2] == X[J[i].posCh1] && Y[J[k].posCh2] == Y[J[i].posCh1]) || (X[J[k].posCh2] == EchXJ[J[i].posCh1] && Y[J[k].posCh2] == EchYJ[J[i].posCh1]))
		{
			if (i == 0) { J[i].posCh1 = EJ1CH1; J[i].scaleCh1 = 0;}
			else if (i == 1) { J[i].posCh1 = EJ2CH1; J[i].scaleCh1 = 0;}
			else if (i == 2) { J[i].posCh1 = EJ3CH1; J[i].scaleCh1 = 0;}
			else if (i == 3) { J[i].posCh1 = EJ4CH1; J[i].scaleCh1 = 0;}
			tab[EcuX[J[i].posCh1]][EcuY[J[i].posCh1]] = J[i].symb;
		}
	}
}
void CheckPosCh3(struct joueur* J, int tab[15][15], short k)
{
	int dif;
	for (int i = 0; i < 4; i++)
	{
		dif = J[k].posCh3;
		if ((X[J[k].posCh3] == X[J[i].posCh2] && Y[J[k].posCh3] == Y[J[i].posCh2]) || (X[J[k].posCh3] == EchXJ[J[i].posCh2] && Y[J[k].posCh3] == EchYJ[J[i].posCh2]))
		{
			if (i == 0) { J[i].posCh2 = EJ1CH2; J[i].scaleCh2 = 0;}
			else if (i == 1) { J[i].posCh2 = EJ2CH2; J[i].scaleCh2 = 0;}
			else if (i == 2) { J[i].posCh2 = EJ3CH2; J[i].scaleCh2 = 0;}
			else if (i == 3) { J[i].posCh2 = EJ4CH2; J[i].scaleCh2 = 0;}
			tab[EcuX[J[i].posCh2]][EcuY[J[i].posCh2]] = J[i].symb;
		}
		else if (((X[J[k].posCh3] == X[J[i].posCh3]) && (Y[J[k].posCh3] == Y[J[i].posCh3]) && k != i) || ((X[J[k].posCh3] == EchXJ[J[i].posCh3]) && (EchYJ[J[k].posCh3] == EchYJ[J[i].posCh3]) && k != i))
		{
			if (i == 0) { J[i].posCh3 = EJ1CH3; J[i].scaleCh3 = 0;}
			else if (i == 1) { J[i].posCh3 = EJ2CH3; J[i].scaleCh3 = 0;}
			else if (i == 2) { J[i].posCh3 = EJ3CH3; J[i].scaleCh3 = 0;}
			else if (i == 3) { J[i].posCh3 = EJ4CH3; J[i].scaleCh3 = 0;}
			tab[EcuX[J[i].posCh3]][EcuY[J[i].posCh3]] = J[i].symb;
		}
		else if ((X[J[k].posCh3] == X[J[i].posCh4] && Y[J[k].posCh3] == Y[J[i].posCh4]) || (X[J[k].posCh3] == EchXJ[J[i].posCh4] && Y[J[k].posCh3] == EchYJ[J[i].posCh4]))
		{
			if (i == 0) { J[i].posCh4 = EJ1CH4; J[i].scaleCh4 = 0;}
			else if (i == 1) { J[i].posCh4 = EJ2CH4; J[i].scaleCh4 = 0;}
			else if (i == 2) { J[i].posCh4 = EJ3CH4; J[i].scaleCh4 = 0;}
			else if (i == 3) { J[i].posCh4 = EJ4CH4; J[i].scaleCh4 = 0;}
			tab[EcuX[J[i].posCh4]][EcuY[J[i].posCh4]] = J[i].symb;
		}
		else if ((X[J[k].posCh3] == X[J[i].posCh1] && Y[J[k].posCh3] == Y[J[i].posCh1]) || (X[J[k].posCh3] == EchXJ[J[i].posCh1] && Y[J[k].posCh3] == EchYJ[J[i].posCh1]))
		{
			if (i == 0) { J[i].posCh1 = EJ1CH1; J[i].scaleCh1 = 0;}
			else if (i == 1) { J[i].posCh1 = EJ2CH1; J[i].scaleCh1 = 0;}
			else if (i == 2) { J[i].posCh1 = EJ3CH1; J[i].scaleCh1 = 0;}
			else if (i == 3) { J[i].posCh1 = EJ4CH1; J[i].scaleCh1 = 0;}
			tab[EcuX[J[i].posCh1]][EcuY[J[i].posCh1]] = J[i].symb;
		}
	}
}
void CheckPosCh4(struct joueur* J, int tab[15][15], short k)
{
	int dif;
	for (int i = 0; i < 4; i++)
	{
		dif = J[k].posCh4;
		if ((X[J[k].posCh4] == X[J[i].posCh2] && Y[J[k].posCh4] == Y[J[i].posCh2]) || (X[J[k].posCh4] == EchXJ[J[i].posCh2] && Y[J[k].posCh4] == EchYJ[J[i].posCh2]))
		{
			if (i == 0) { J[i].posCh2 = EJ1CH2; J[i].scaleCh2 = 0; }
			else if (i == 1) { J[i].posCh2 = EJ2CH2; J[i].scaleCh2 = 0;}
			else if (i == 2) { J[i].posCh2 = EJ3CH2; J[i].scaleCh2 = 0;}
			else if (i == 3) { J[i].posCh2 = EJ4CH2; J[i].scaleCh2 = 0;}
			tab[EcuX[J[i].posCh2]][EcuY[J[i].posCh2]] = J[i].symb;
		}
		else if ((X[J[k].posCh4] == X[J[i].posCh3] && Y[J[k].posCh4] == Y[J[i].posCh3]) || (X[J[k].posCh4] == EchXJ[J[i].posCh3] && Y[J[k].posCh4] == EchYJ[J[i].posCh3]))
		{
			if (i == 0) { J[i].posCh3 = EJ1CH3; J[i].scaleCh3 = 0;}
			else if (i == 1) { J[i].posCh3 = EJ2CH3; J[i].scaleCh3 = 0;}
			else if (i == 2) { J[i].posCh3 = EJ3CH3;  J[i].scaleCh3 = 0;}
			else if (i == 3) { J[i].posCh3 = EJ4CH3; J[i].scaleCh3 = 0;}
			tab[EcuX[J[i].posCh3]][EcuY[J[i].posCh3]] = J[i].symb;

		}
		else if (((X[J[k].posCh4] == X[J[i].posCh4]) && (Y[J[k].posCh4] == Y[J[i].posCh4]) && k != i) || ((X[J[k].posCh4] == EchXJ[J[i].posCh4]) && (EchYJ[J[k].posCh4] == EchYJ[J[i].posCh4]) && k != i))
		{
			if (i == 0) { J[i].posCh4 = EJ1CH4; J[i].scaleCh4 = 0;}
			else if (i == 1) { J[i].posCh4 = EJ2CH4; J[i].scaleCh4 = 0;}
			else if (i == 2) { J[i].posCh4 = EJ3CH4; J[i].scaleCh4 = 0;}
			else if (i == 3) { J[i].posCh4 = EJ4CH4; J[i].scaleCh4 = 0;}
			tab[EcuX[J[i].posCh4]][EcuY[J[i].posCh4]] = J[i].symb;
		}
		else if ((X[J[k].posCh4] == X[J[i].posCh1] && Y[J[k].posCh4] == Y[J[i].posCh1]) || (X[J[k].posCh4] == EchXJ[J[i].posCh1] && Y[J[k].posCh4] == EchYJ[J[i].posCh1]))
		{
			if (i == 0) { J[i].posCh1 = EJ1CH1; J[i].scaleCh1 = 0;}
			else if (i == 1) { J[i].posCh1 = EJ2CH1; J[i].scaleCh1 = 0;}
			else if (i == 2) { J[i].posCh1 = EJ3CH1; J[i].scaleCh1 = 0;}
			else if (i == 3) { J[i].posCh1 = EJ4CH1; J[i].scaleCh1 = 0;}
			tab[EcuX[J[i].posCh1]][EcuY[J[i].posCh1]] = J[i].symb;
		}
	}
}

//Traitement du jeu, pour le cas où un cheval est sur l'echelle, la périphérique ou s'insert sur celle-ci
short echellePlateau(struct joueur* J, short MajCh, int tab[15][15], int EchXJ[32], int EchYJ[32], short player, short resDe, short indScale)
{
	short Fin = 0;
	char nb2car;
	//(char)J[player].acc[MajCh - 1]
	if (J[player].lastroll[MajCh - 1] == 1)
	{
		if (MajCh == 1)
		{
			if (resDe == J[player].acc[MajCh - 1])
			{
				nb2car = '/' + J[player].acc[MajCh - 1];
				tab[EchXJ[J[player].posCh1]][EchYJ[J[player].posCh1]] = nb2car;
				J[player].posCh1++;
				tab[EchXJ[J[player].posCh1]][EchYJ[J[player].posCh1]];
				tab[EchXJ[J[player].posCh1]][EchYJ[J[player].posCh1]] = J[player].symb;
				J[player].acc[MajCh - 1] += indScale;
			}
		}
		else if (MajCh == 2)
		{
			if (resDe == J[player].acc[MajCh - 1])
			{
				nb2car = '/' + J[player].acc[MajCh - 1];
				tab[EchXJ[J[player].posCh2]][EchYJ[J[player].posCh2]] = nb2car;
				J[player].posCh2++;
				tab[EchXJ[J[player].posCh2]][EchYJ[J[player].posCh2]];
				tab[EchXJ[J[player].posCh2]][EchYJ[J[player].posCh2]] = J[player].symb;
				J[player].acc[MajCh - 1] += indScale;
			}
		}
		else if (MajCh == 3)
		{
			if (resDe == J[player].acc[MajCh - 1])
			{
				nb2car = '/' + J[player].acc[MajCh - 1];
				tab[EchXJ[J[player].posCh3]][EchYJ[J[player].posCh3]] = nb2car;
				J[player].posCh3++;
				tab[EchXJ[J[player].posCh3]][EchYJ[J[player].posCh3]];
				tab[EchXJ[J[player].posCh3]][EchYJ[J[player].posCh3]] = J[player].symb;
				J[player].acc[MajCh - 1] += indScale;
			}
		}
		else if (MajCh == 4)
		{
			if (resDe == J[player].acc[MajCh - 1])
			{
				nb2car = '/' + J[player].acc[MajCh - 1];
				tab[EchXJ[J[player].posCh4]][EchYJ[J[player].posCh4]] = nb2car;
				J[player].posCh4++;
				tab[EchXJ[J[player].posCh4]][EchYJ[J[player].posCh4]];
				tab[EchXJ[J[player].posCh4]][EchYJ[J[player].posCh4]] = J[player].symb;
				J[player].acc[MajCh - 1] += indScale;
			}
		}

		if (J[player].acc[MajCh - 1] >= 7)
		{
			Fin = 1;
		}

	}
	else
	{
		if (MajCh == 1)
		{
			if (resDe == J[player].acc[MajCh - 1])
			{
				nb2car = '/' + J[player].acc[MajCh - 1];
				tab[EchXJ[J[player].posCh1]][EchYJ[J[player].posCh1]] = nb2car;
				J[player].posCh1++;
				tab[EchXJ[J[player].posCh1]][EchYJ[J[player].posCh1]];
				tab[EchXJ[J[player].posCh1]][EchYJ[J[player].posCh1]] = J[player].symb;
				J[player].acc[MajCh - 1] += indScale;
			}
		}
		else if (MajCh == 2)
		{
			if (resDe == J[player].acc[MajCh - 1])
			{
				nb2car = '/' + J[player].acc[MajCh - 1];
				tab[EchXJ[J[player].posCh2]][EchYJ[J[player].posCh2]] = nb2car;
				J[player].posCh2++;
				tab[EchXJ[J[player].posCh2]][EchYJ[J[player].posCh2]];
				tab[EchXJ[J[player].posCh2]][EchYJ[J[player].posCh2]] = J[player].symb;
				J[player].acc[MajCh - 1] += indScale;
			}
		}
		else if (MajCh == 3)
		{
			if (resDe == J[player].acc[MajCh - 1])
			{
				nb2car = '/' + J[player].acc[MajCh - 1];
				tab[EchXJ[J[player].posCh3]][EchYJ[J[player].posCh3]] = nb2car;
				J[player].posCh3++;
				tab[EchXJ[J[player].posCh3]][EchYJ[J[player].posCh3]];
				tab[EchXJ[J[player].posCh3]][EchYJ[J[player].posCh3]] = J[player].symb;
				J[player].acc[MajCh - 1] += indScale;
			}
		}
		else if (MajCh == 4)
		{
			if (resDe == J[player].acc[MajCh - 1])
			{
				nb2car = '/' + J[player].acc[MajCh - 1];
				tab[EchXJ[J[player].posCh4]][EchYJ[J[player].posCh4]] = nb2car;
				J[player].posCh4++;
				tab[EchXJ[J[player].posCh4]][EchYJ[J[player].posCh4]];
				tab[EchXJ[J[player].posCh4]][EchYJ[J[player].posCh4]] = J[player].symb;
				J[player].acc[MajCh - 1] += indScale;
			}
		}

		if (J[player].acc[MajCh - 1] >= 7)
		{
			J[player].acc[MajCh - 1] = 6;
			J[player].lastroll[MajCh - 1] = 1;
		}
	}
	return Fin;
}
short jeuPlateau(struct joueur* J, short MajCh, int tab[15][15], int X[98], int Y[98], short player, int recul, short resDe, int EchXJ[32], int EchYJ[32], short indScale)
{
	int refScale = 0;
	short F = 0;

	if (player == 0) { refScale = 55; }
	if (player == 1) { refScale = 69; }
	if (player == 2) { refScale = 83; }
	if (player == 3) { refScale = 97; }

	if (MajCh == 1)
	{
		if (J[player].scaleCh1 != 1)
		{
			tab[X[J[player].posCh1]][Y[J[player].posCh1]] = '0';
			if (resDe + J[player].posCh1 > refScale) { recul = ((resDe + J[player].posCh1) % refScale) * 2; }
			J[player].posCh1 += resDe;
			J[player].posCh1 -= recul;
			tab[X[J[player].posCh1]][Y[J[player].posCh1]] = J[player].symb;
			CheckPosCh1(J, tab, player);
		}
		else { F = echellePlateau(J, MajCh, tab, EchXJ, EchYJ, player, resDe, indScale); }
	}
	else if (MajCh == 2)
	{
		if (J[player].scaleCh2 != 1)
		{
			tab[X[J[player].posCh2]][Y[J[player].posCh2]] = '0';
			if (resDe + J[player].posCh2 > refScale) { recul = ((resDe + J[player].posCh2) % refScale) * 2; }
			J[player].posCh2 += resDe;
			J[player].posCh2 -= recul;
			tab[X[J[player].posCh2]][Y[J[player].posCh2]] = J[player].symb;
			CheckPosCh2(J, tab, player);
		}
		else { F = echellePlateau(J, MajCh, tab, EchXJ, EchYJ, player, resDe, indScale); }
	}
	else if (MajCh == 3)
	{
		if (J[player].scaleCh3 != 1)
		{
			tab[X[J[player].posCh3]][Y[J[player].posCh3]] = '0';
			if (resDe + J[player].posCh3 > refScale) { recul = ((resDe + J[player].posCh3) % refScale) * 2; }
			J[player].posCh3 += resDe;
			J[player].posCh3 -= recul;
			tab[X[J[player].posCh3]][Y[J[player].posCh3]] = J[player].symb;
			CheckPosCh3(J, tab, player);
		}
		else { F = echellePlateau(J, MajCh, tab, EchXJ, EchYJ, player, resDe, indScale); }
	}
	else if (MajCh == 4)
	{
		if (J[player].scaleCh4 != 1)
		{
			tab[X[J[player].posCh4]][Y[J[player].posCh4]] = '0';
			if (resDe + J[player].posCh4 > refScale) { recul = ((resDe + J[player].posCh4) % refScale) * 2; }
			J[player].posCh4 += resDe;
			J[player].posCh4 -= recul;
			tab[X[J[player].posCh4]][Y[J[player].posCh4]] = J[player].symb;
			CheckPosCh4(J, tab, player);
		}
		else { F = echellePlateau(J, MajCh, tab, EchXJ, EchYJ, player, resDe, indScale); }
	}
	return F;
}
short insertPlateau(struct joueur* J, int tab[15][15], int EcuX[16], int EcuY[16], int X[98], int Y[98], short player)
{
	char couleur = 0;
	short sortie = 0;
	int caseDepart = 0;
	int posJCh1 = 0;
	int posJCh2 = 0;
	int posJCh3 = 0;
	int posJCh4 = 0;

	if (player == 0) { couleur = 'R'; caseDepart = DJ1; posJCh1 = EJ1CH1; posJCh2 = EJ1CH2; posJCh3 = EJ1CH3; posJCh4 = EJ1CH4; }
	if (player == 1) { couleur = 'V'; caseDepart = DJ2; posJCh1 = EJ2CH1; posJCh2 = EJ2CH2; posJCh3 = EJ2CH3; posJCh4 = EJ2CH4; }
	if (player == 2) { couleur = 'J'; caseDepart = DJ3; posJCh1 = EJ3CH1; posJCh2 = EJ3CH2; posJCh3 = EJ3CH3; posJCh4 = EJ3CH4; }
	if (player == 3) { couleur = 'B'; caseDepart = DJ4; posJCh1 = EJ4CH1; posJCh2 = EJ4CH2; posJCh3 = EJ4CH3; posJCh4 = EJ4CH4; }

	if (J[player].posCh1 == posJCh1)
	{
		tab[EcuX[J[player].posCh1]][EcuY[J[player].posCh1]] = couleur;
		J[player].posCh1 = caseDepart;
		tab[X[J[player].posCh1]][Y[J[player].posCh1]] = J[player].symb;
		sortie = 0;
	}
	else if (J[player].posCh2 == posJCh2)
	{
		tab[EcuX[J[player].posCh2]][EcuY[J[player].posCh2]] = couleur;
		J[player].posCh2 = caseDepart;
		tab[X[J[player].posCh2]][Y[J[player].posCh2]] = J[player].symb;
		sortie = 0;
	}
	else if (J[player].posCh3 == posJCh3)
	{
		tab[EcuX[J[player].posCh3]][EcuY[J[player].posCh3]] = couleur;
		J[player].posCh3 = caseDepart;
		tab[X[J[player].posCh3]][Y[J[player].posCh3]] = J[player].symb;
		sortie = 0;
	}
	else if (J[player].posCh3 == posJCh4)
	{
		tab[EcuX[J[player].posCh4]][EcuY[J[player].posCh4]] = couleur;
		J[player].posCh4 = caseDepart;
		tab[X[J[player].posCh4]][Y[J[player].posCh4]] = J[player].symb;
		sortie = 0;
	}

	return sortie;

}

//Voir si un cheval a atteint sa case objectif sur le périphérique du plateau de jeu
void testPosScale(struct joueur* J, short i)
{
	int refScale = 0;
	int pos = 0;
	if (i == 0) { refScale = 55; pos = 0; }
	else if (i == 1) { refScale = 69; pos = 8; }
	else if (i == 2) { refScale = 83; pos = 16; }
	else if (i == 3) { refScale = 97; pos = 24; }
	if (J[i].posCh1 == refScale) { J[i].scaleCh1 = 1; J[i].posCh1 = pos; }
	else if (J[i].posCh2 == refScale) { J[i].scaleCh2 = 1; J[i].posCh2 = pos; }
	else if (J[i].posCh3 == refScale) { J[i].scaleCh3 = 1; J[i].posCh3 = pos; }
	else if (J[i].posCh4 == refScale) { J[i].scaleCh4 = 1; J[i].posCh4 = pos; }
}