#ifndef JEU
#define JEU

//Nombres de joueurs
#define NBJS 4

//Position des chevaux en sortie d'ecurie
#define DJ1 0
#define DJ2 14
#define DJ3 28
#define DJ4 42

//Position des chevaux dans l'ecurie
#define EJ1CH1 0
#define EJ1CH2 1
#define EJ1CH3 2
#define EJ1CH4 3

#define EJ2CH1 4
#define EJ2CH2 5
#define EJ2CH3 6
#define EJ2CH4 7

#define EJ3CH1 8
#define EJ3CH2 9
#define EJ3CH3 10
#define EJ3CH4 11

#define EJ4CH1 12
#define EJ4CH2 13
#define EJ4CH3 14
#define EJ4CH4 15

extern int Y[98];
extern int X[98];
extern int EcuY[16];
extern int EcuX[16];
extern int EchYJ[32];
extern int EchXJ[32];

struct joueur
{
	//Ordinateur ou non
	int bot;
	//Couleur
	char symb;
	//Pos des chevaux
	int posCh1;
	int posCh2;
	int posCh3;
	int posCh4;
	//case atteinte pour l'echelle
	int scaleCh1;
	int scaleCh2;
	int scaleCh3;
	int scaleCh4;
	//Tableau pour memoriser l'ascension de chaque cheval sur l'echelle
	int acc[4];
	//Dernier Lancer de dé mémorisé
	int lastroll[4];
};
typedef struct joueur joueur;

extern short roll(void);

extern short lancer(struct joueur* J, short i);

extern short RollIs6(joueur* J, short i);

extern int InitJ(void);

extern joueur* InitstructJ(int joueurs, struct joueur* J);

extern void InitTab(int tab[15][15]);

extern void MajTab(int tab[15][15], struct joueur* J);

extern void AffTab(int tab[15][15]);

extern void CheckPosCh1(struct joueur* J, int tab[15][15], short k);
extern void CheckPosCh2(struct joueur* J, int tab[15][15], short k);
extern void CheckPosCh3(struct joueur* J, int tab[15][15], short k);
void CheckPosCh4(struct joueur* J, int tab[15][15], short k);

extern short echellePlateau(struct joueur* J, short MajCh, int tab[15][15], int EchXJ[32], int EchYJ[32], short player, short resDe, short indScale);
extern short jeuPlateau(struct joueur* J, short MajCh, int tab[15][15], int X[98], int Y[98], short player, int recul, short resDe, int EchXJ[32], int EchYJ[32], short indScale);
extern short insertPlateau(struct joueur* J, int tab[15][15], int EcuX[16], int EcuY[16], int X[98], int Y[98], short player);

extern void testPosScale(struct joueur* J, short i);


#endif