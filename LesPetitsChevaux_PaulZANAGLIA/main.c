#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeu.h"
#include <windows.h>


void main(void)
{
	int tab[15][15];
	int joueurs;
	joueur* J;
	char start = 'x';
	char path;

	short sortie1 = 0;
	short sortie2 = 0;
	short sortie3 = 0;
	short sortie4 = 0;

	short lancer1 = 0;
	short lancer2 = 0;
	short lancer3 = 0;
	short lancer4 = 0;

	short recul1 = 0;
	short recul2 = 0;
	short recul3 = 0;
	short recul4 = 0;

	short resDe = 0;
	short De = 0;
	short choixCh = 1;
	short relancer = 1;
	short MajCh = 0;
	short EndGame = 0;
	short i;
	short indScale = 1;
	short victoire = 7;

	joueurs = InitJ(); //Renvoie le nombre de joueur pour la partie en cours

	//Allocation dynamique de la structure joueur
	J = malloc(NBJS * sizeof(J));
	J = InitstructJ(joueurs, J);

	InitTab(tab);
	MajTab(tab, J);

	if (joueurs != 4) { printf("Le reste sera joue par des PNJ.\n"); }
	printf("Voici le plateau de jeu.\n");

	AffTab(tab);

	// Attente confirmation joueur(s) pour commencer la partie
	while (1)
	{
		if (start != 'y' && start != '\n')
		{
			printf("Appuyer sur y pour commencer la partie...\n");
		}
		else if (start == 'y') { break; }
		start = getchar();
	}
	//--------------------------------------------------------------
	while (1)
	{
		{
			
			printf("Tour de J1.\n");
			i = 0;
			if ((J[0].posCh1 == EJ1CH1 && J[0].posCh2 == EJ1CH2 && J[0].posCh3 == EJ1CH3 && J[0].posCh4 == EJ1CH4) && (J[0].scaleCh1 == 0 && J[0].scaleCh2 == 0 && J[0].scaleCh3 == 0 && J[0].scaleCh4 == 0)) // On regarde si tous les chevaux sont à l'écurie
			{
				while (1) // Tour de J1
				{
					if (sortie1 == 0 && choixCh == 1)
					{
						if (J[0].posCh1 == EJ1CH1)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer1 = RollIs6(J, i);
							MajCh = 1;
							//lancer1 = 1;
						}
						else if (J[0].posCh2 == EJ1CH2)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer1 = RollIs6(J, i);
							MajCh = 2;
						}
						else if (J[0].posCh3 == EJ1CH3)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer1 = RollIs6(J, i);
							MajCh = 3;
						}
						else if (J[0].posCh4 == EJ1CH4)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer1 = RollIs6(J, i);
							MajCh = 4;
						}
						if (lancer1) { sortie1 = 1; De = 6; }
					}

					if (lancer1 == 0 && resDe == 0) { relancer = 0; }
					else { choixCh = 0; }

					if (sortie1 == 1)
					{
						sortie1 = insertPlateau(J, tab, EcuX, EcuY, X, Y, i); //On fait sortir le cheval de son ecurie
						
					}
					else if (sortie1 == 0 && resDe != 0)
					{
						EndGame = jeuPlateau(J, MajCh, tab, X, Y, i, recul1, resDe, EchXJ, EchYJ, indScale); //Deroulement du jeu
					}

					if (EndGame == 1) { victoire = i; EndGame = 0; } //Si partie fini, victoire prends la valeur du joueur gagnant

					if (De == 6) { relancer = 1; } //Si le lancer de dé vaut 6 alors le joueur peut rejoueur
					if (resDe != 6 && resDe != 0) { relancer = 0; }

					if (relancer == 1 && victoire == 7) //Lancer du de
					{
						resDe = lancer(J, i);
						De = resDe;
						lancer1 = 0;
					}
					else { break; }
				}
			}
			else
			{
				start = ' ';
				while (1)
				{
					if (start != 'y' && start != '\n' && start != 'n')
					{
						printf("y pour jouer un cheval de l'écurie, n pour jouer un cheval sur le terrain.\n");
					}
					else if (start == 'y' || start == 'n')
					{
						path = start;
						break;
					}
					start = getchar();
				}
				if (path == 'y')
				{
					/*sortie1 = 0;
					choixCh = 1;*/
					relancer = 1;
					choixCh = 1;
				}
				else
				{
					/*sortie1 = 0;
					resDe = 0;*/
					relancer = 1;
					choixCh = 0;
					//Selectionner le cheval
					while (1)
					{
						if (J[0].posCh1 != EJ1CH1 || J[0].scaleCh1 == 1)
						{
							start = ' ';
							while (1)
							{
								if (start != 'y' && start != '\n' && start != 'n')
								{
									printf("Pour jouer le Cheval 1 appuyer sur y, sinon n.\n");
								}
								else if (start == 'y' || start == 'n')
								{
									path = start;
									break;
								}
								start = getchar();
							}
							if (path == 'y')
							{
								MajCh = 1;
								relancer = 1;
								break;
							}
							else
							{
								if (J[0].posCh2 != EJ1CH2 || J[0].scaleCh2 == 1)
								{
									start = ' ';
									while (1)
									{
										if (start != 'y' && start != '\n' && start != 'n')
										{
											printf("Pour jouer le Cheval 2 appuyer sur y, sinon n.\n");
										}
										else if (start == 'y' || start == 'n')
										{
											path = start;
											break;
										}
										start = getchar();
									}
									if (path == 'y')
									{
										MajCh = 2;
										relancer = 1;
										break;
									}
									else
									{
										if (J[0].posCh3 != EJ1CH3 || J[0].scaleCh3 == 1)
										{
											start = ' ';
											while (1)
											{
												if (start != 'y' && start != '\n' && start != 'n')
												{
													printf("Pour jouer le Cheval 3 appuyer sur y, sinon n.\n");
												}
												else if (start == 'y' || start == 'n')
												{
													path = start;
													break;
												}
												start = getchar();
											}
											if (path == 'y')
											{
												MajCh = 3;
												relancer = 1;
												break;
											}
											else
											{
												if (J[0].posCh4 != EJ1CH4 || J[0].scaleCh4 == 1)
												{
													start = ' ';
													while (1)
													{
														if (start != 'y' && start != '\n' && start != 'n')
														{
															printf("Pour jouer le Cheval 4 appuyer sur y, sinon n.\n");
														}
														else if (start == 'y' || start == 'n')
														{
															path = start;
															break;
														}
														start = getchar();
													}
													if (path == 'y')
													{
														MajCh = 4;
														relancer = 1;
														break;
													}
												}
											}
										}
									}
								}
							}
						}
					}
					De = 6;
				}
				while (1) // Tour de J1
				{
					if (sortie1 == 0 && choixCh == 1)
					{
						if (J[0].posCh1 == EJ1CH1)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer1 = RollIs6(J, i);
							MajCh = 1;
							//lancer1 = 1;
						}
						else if (J[0].posCh2 == EJ1CH2)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer1 = RollIs6(J, i);
							MajCh = 2;
						}
						else if (J[0].posCh3 == EJ1CH3)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer1 = RollIs6(J, i);
							MajCh = 3;
						}
						else if (J[0].posCh4 == EJ1CH4)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer1 = RollIs6(J, i);
							MajCh = 4;
						}
						if (lancer1) { sortie1 = 1; De = 6; }
					}

					if (lancer1 == 0 && resDe == 0) { relancer = 0; }
					else { choixCh = 0; }

					if (sortie1 == 1)
					{
						sortie1 = insertPlateau(J, tab, EcuX, EcuY, X, Y, i);
						
					}
					else if (sortie1 == 0 && resDe != 0)
					{

						EndGame = jeuPlateau(J, MajCh, tab, X, Y, i, recul1, resDe, EchXJ, EchYJ, indScale);
						
					}

					if (EndGame == 1) { victoire = i; EndGame = 0; }

					if (De == 6) { relancer = 1; }
					else if (resDe != 6 && resDe != 0) { relancer = 0; }
					if (relancer == 1 && victoire == 7)
					{
						resDe = lancer(J, i);
						De = resDe;
						lancer1 = 0;
					}
					else { break; }
					recul1 = 0;
				}
			}
			De = 0;
			resDe = 0;
		}

		testPosScale(J, i); //On verifie si le cheval joué ce tour est arrivé à sa case reservé

		sortie1 = 0;
		lancer1 = 0;
		recul1 = 0;

		resDe = 0;
		De = 0;
		choixCh = 1;
		relancer = 1;
		MajCh = 0;

		AffTab(tab);
		Sleep(1000);

		if (victoire != 7) { break; }  //Si victoire a pris la valeur 0,1,2 ou 3, on quitte la grande boucle pour afficher le gagnant

		{
			printf("Tour de J2.\n");
			i = 1;
			if ((J[1].posCh1 == EJ2CH1 && J[1].posCh2 == EJ2CH2 && J[1].posCh3 == EJ2CH3 && J[1].posCh4 == EJ2CH4) && (J[1].scaleCh1 == 0 && J[1].scaleCh2 == 0 && J[1].scaleCh3 == 0 && J[1].scaleCh4 == 0))
			{
				while (1) // Tour de J2
				{
					if (sortie2 == 0 && choixCh == 1)
					{
						if (J[1].posCh1 == EJ2CH1)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer2 = RollIs6(J, i);
							MajCh = 1;
							//lancer2 = 1;
						}
						else if (J[1].posCh2 == EJ2CH2)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer2 = RollIs6(J, i);
							MajCh = 2;
						}
						else if (J[1].posCh3 == EJ2CH3)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer2 = RollIs6(J, i);
							MajCh = 3;
						}
						else if (J[1].posCh4 == EJ2CH4)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer2 = RollIs6(J, i);
							MajCh = 4;
						}
						if (lancer2) { sortie2 = 1; De = 6; }
					}

					if (lancer2 == 0 && resDe == 0) { relancer = 0; }
					else { choixCh = 0; }

					if (sortie2 == 1)
					{
						sortie2 = insertPlateau(J, tab, EcuX, EcuY, X, Y, i);
						
					}
					else if (sortie2 == 0 && resDe != 0)
					{
						EndGame = jeuPlateau(J, MajCh, tab, X, Y, i, recul2, resDe, EchXJ, EchYJ, indScale);
						
					}

					if (EndGame == 1) { victoire = i; EndGame = 0; }

					if (De == 6) { relancer = 1; }
					if (resDe != 6 && resDe != 0) { relancer = 0; }

					if (relancer == 1 && victoire == 7)
					{
						resDe = lancer(J, i);
						De = resDe;
						lancer2 = 0;
					}
					else { break; }
				}
			}
			else
			{
				start = ' ';
				while (1)
				{
					if (J[i].bot == 0)
					{
						if (start != 'y' && start != '\n' && start != 'n')
						{
							printf("y pour jouer un cheval de l'ecurie, sinon n.\n");
						}
						else if (start == 'y' || start == 'n')
						{
							path = start;
							break;
						}
						start = getchar();
					}
					else
					{
						if (roll() % 2 == 1)
						{
							path = 'y';
						}
						else
						{
							path = 'n';
						}
						break;
					}
				}
				if (path == 'y')
				{
					/*sortie2 = 0;
					choixCh = 1;*/
					relancer = 1;
					choixCh = 1;
				}
				else
				{
					/*sortie2 = 0;
					resDe = 0;*/
					relancer = 1;
					choixCh = 0;
					//Selectionner le cheval
					while (1)
					{
						if (J[1].posCh1 != EJ2CH1 || J[1].scaleCh1 == 1)
						{
							start = ' ';
							while (1)
							{
								if (J[i].bot == 0)
								{
									if (start != 'y' && start != '\n' && start != 'n')
									{
										printf("Pour jouer le Cheval 1 appuyer sur y, sinon n.\n");
									}
									else if (start == 'y' || start == 'n')
									{
										path = start;
										break;
									}
									start = getchar();
								}
								else
								{
									if (roll() % 2 == 1)
									{
										path = 'y';
									}
									else
									{
										path = 'n';
									}
									break;
								}
							}
							if (path == 'y')
							{
								MajCh = 1;
								relancer = 1;
								break;
							}
							else
							{
								if (J[1].posCh2 != EJ2CH2 || J[1].scaleCh2 == 1)
								{
									start = ' ';
									while (1)
									{
										if (J[i].bot == 0)
										{
											if (start != 'y' && start != '\n' && start != 'n')
											{
												printf("Pour jouer le Cheval 2 appuyer sur y, sinon n.\n");
											}
											else if (start == 'y' || start == 'n')
											{
												path = start;
												break;
											}
											start = getchar();
										}
										else
										{
											if (roll() % 2 == 1)
											{
												path = 'y';
											}
											else
											{
												path = 'n';
											}
											break;
										}
									}
									if (path == 'y')
									{
										MajCh = 2;
										relancer = 1;
										break;
									}
									else
									{
										if (J[1].posCh3 != EJ2CH3 || J[1].scaleCh3 == 1)
										{
											start = ' ';
											while (1)
											{
												if (J[i].bot == 0)
												{
													if (start != 'y' && start != '\n' && start != 'n')
													{
														printf("Pour jouer le Cheval 3 appuyer sur y, sinon n.\n");
													}
													else if (start == 'y' || start == 'n')
													{
														path = start;
														break;
													}
													start = getchar();
												}
												else
												{
													if (roll() % 2 == 1)
													{
														path = 'y';
													}
													else
													{
														path = 'n';
													}
													break;
												}
											}
											if (path == 'y')
											{
												MajCh = 3;
												relancer = 1;
												break;
											}
											else
											{
												if (J[1].posCh4 != EJ2CH4 || J[1].scaleCh4 == 1)
												{
													start = ' ';
													while (1)
													{
														if (J[i].bot == 0)
														{
															if (start != 'y' && start != '\n' && start != 'n')
															{
																printf("Pour jouer le Cheval 4 appuyer sur y, sinon n.\n");
															}
															else if (start == 'y' || start == 'n')
															{
																path = start;
																break;
															}
															start = getchar();
														}
														else
														{
															if (roll() % 2 == 1)
															{
																path = 'y';
															}
															else
															{
																path = 'n';
															}
															break;
														}
													}
													if (path == 'y')
													{
														MajCh = 4;
														relancer = 1;
														break;
													}
												}
											}
										}
									}
								}
							}
						}
					}
					De = 6;
				}
				while (1) // Tour de J2
				{
					if (sortie2 == 0 && choixCh == 1)
					{
						if (J[1].posCh1 == EJ2CH1)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer2 = RollIs6(J, i);
							MajCh = 1;
							//lancer2 = 1;
						}
						else if (J[1].posCh2 == EJ2CH2)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer2 = RollIs6(J, i);
							MajCh = 2;
						}
						else if (J[1].posCh3 == EJ2CH3)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer2 = RollIs6(J, i);
							MajCh = 3;
						}
						else if (J[1].posCh4 == EJ2CH4)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer2 = RollIs6(J, i);
							MajCh = 4;
						}
						if (lancer2) { sortie2 = 1; De = 6; }
					}

					if (lancer2 == 0 && resDe == 0) { relancer = 0; }
					else { choixCh = 0; }

					if (sortie2 == 1)
					{
						sortie2 = insertPlateau(J, tab, EcuX, EcuY, X, Y, i);
						
					}
					else if (sortie2 == 0 && resDe != 0)
					{
						EndGame = jeuPlateau(J, MajCh, tab, X, Y, i, recul2, resDe, EchXJ, EchYJ, indScale);
						
					}

					if (EndGame == 1) { victoire = i; EndGame = 0; }

					if (De == 6) { relancer = 1; }
					else if (resDe != 6 && resDe != 0) { relancer = 0; }
					if (relancer == 1 && victoire == 7)
					{
						resDe = lancer(J, i);
						De = resDe;
						lancer2 = 0;
					}
					else { break; }
					recul2 = 0;
				}
			}
			De = 0;
			resDe = 0;
		}

		testPosScale(J, i);

		sortie2 = 0;
		lancer2 = 0;
		recul2 = 0;

		resDe = 0;
		De = 0;
		choixCh = 1;
		relancer = 1;
		MajCh = 0;

		AffTab(tab);
		Sleep(1000);

		if (victoire != 7) { break; }

		{
			
			printf("Tour de J3.\n");
			i = 2;
			if ((J[2].posCh1 == EJ3CH1 && J[2].posCh2 == EJ3CH2 && J[2].posCh3 == EJ3CH3 && J[2].posCh4 == EJ3CH4) && (J[2].scaleCh1 == 0 && J[2].scaleCh2 == 0 && J[2].scaleCh3 == 0 && J[2].scaleCh4 == 0))
			{
				while (1) // Tour de J3
				{
					if (sortie3 == 0 && choixCh == 1)
					{
						if (J[2].posCh1 == EJ3CH1)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer3 = RollIs6(J, i);
							MajCh = 1;
							//lancer3 = 1;
						}
						else if (J[2].posCh2 == EJ3CH2)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer3 = RollIs6(J, i);
							MajCh = 2;
						}
						else if (J[2].posCh3 == EJ3CH3)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer3 = RollIs6(J, i);
							MajCh = 3;
						}
						else if (J[2].posCh4 == EJ3CH4)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer3 = RollIs6(J, i);
							MajCh = 4;
						}
						if (lancer3) { sortie3 = 1; De = 6; }
					}

					if (lancer3 == 0 && resDe == 0) { relancer = 0; }
					else { choixCh = 0; }

					if (sortie3 == 1)
					{
						sortie3 = insertPlateau(J, tab, EcuX, EcuY, X, Y, i);
						
					}
					else if (sortie3 == 0 && resDe != 0)
					{
						EndGame = jeuPlateau(J, MajCh, tab, X, Y, i, recul3, resDe, EchXJ, EchYJ, indScale);
						
					}

					if (EndGame == 1) { victoire = i; EndGame = 0; }

					if (De == 6) { relancer = 1; }
					if (resDe != 6 && resDe != 0) { relancer = 0; }

					if (relancer == 1 && victoire == 7)
					{
						resDe = lancer(J, i);
						De = resDe;
						lancer3 = 0;
					}
					else { break; }
				}
			}
			else
			{
				start = ' ';
				while (1)
				{
					if (J[i].bot == 0)
					{
						if (start != 'y' && start != '\n' && start != 'n')
						{
							printf("y pour jouer un cheval de l'ecurie, sinon n.\n");
						}
						else if (start == 'y' || start == 'n')
						{
							path = start;
							break;
						}
						start = getchar();
					}
					else
					{
						if (roll() % 2 == 1)
						{
							path = 'y';
						}
						else
						{
							path = 'n';
						}
						break;
					}
				}
				if (path == 'y')
				{
					/*sortie3 = 0;
					choixCh = 1;*/
					relancer = 1;
					choixCh = 1;
				}
				else
				{
					/*sortie3 = 0;
					resDe = 0;*/
					relancer = 1;
					choixCh = 0;
					//Selectionner le cheval
					while (1)
					{
						if (J[2].posCh1 != EJ3CH1 || J[2].scaleCh1 == 1)
						{
							start = ' ';
							while (1)
							{
								if (J[i].bot == 0)
								{
									if (start != 'y' && start != '\n' && start != 'n')
									{
										printf("Pour jouer le Cheval 1 appuyer sur y, sinon n.\n");
									}
									else if (start == 'y' || start == 'n')
									{
										path = start;
										break;
									}
									start = getchar();
								}
								else
								{
									if (roll() % 2 == 1)
									{
										path = 'y';
									}
									else
									{
										path = 'n';
									}
									break;
								}
							}
							if (path == 'y')
							{
								MajCh = 1;
								relancer = 1;
								break;
							}
							else
							{
								if (J[2].posCh2 != EJ3CH2 || J[2].scaleCh2 == 1)
								{
									start = ' ';
									while (1)
									{
										if (J[i].bot == 0)
										{
											if (start != 'y' && start != '\n' && start != 'n')
											{
												printf("Pour jouer le Cheval 2 appuyer sur y, sinon n.\n");
											}
											else if (start == 'y' || start == 'n')
											{
												path = start;
												break;
											}
											start = getchar();
										}
										else
										{
											if (roll() % 2 == 1)
											{
												path = 'y';
											}
											else
											{
												path = 'n';
											}
											break;
										}
									}
									if (path == 'y')
									{
										MajCh = 2;
										relancer = 1;
										break;
									}
									else
									{
										if (J[2].posCh3 != EJ3CH3 || J[2].scaleCh3 == 1)
										{
											start = ' ';
											while (1)
											{
												if (J[i].bot == 0)
												{
													if (start != 'y' && start != '\n' && start != 'n')
													{
														printf("Pour jouer le Cheval 3 appuyer sur y, sinon n.\n");
													}
													else if (start == 'y' || start == 'n')
													{
														path = start;
														break;
													}
													start = getchar();
												}
												else
												{
													if (roll() % 2 == 1)
													{
														path = 'y';
													}
													else
													{
														path = 'n';
													}
													break;
												}
											}
											if (path == 'y')
											{
												MajCh = 3;
												relancer = 1;
												break;
											}
											else
											{
												if (J[2].posCh4 != EJ3CH4 || J[2].scaleCh4 == 1)
												{
													start = ' ';
													while (1)
													{
														if (J[i].bot == 0)
														{
															if (start != 'y' && start != '\n' && start != 'n')
															{
																printf("Pour jouer le Cheval 4 appuyer sur y, sinon n.\n");
															}
															else if (start == 'y' || start == 'n')
															{
																path = start;
																break;
															}
															start = getchar();
														}
														else
														{
															if (roll() % 2 == 1)
															{
																path = 'y';
															}
															else
															{
																path = 'n';
															}
															break;
														}
													}
													if (path == 'y')
													{
														MajCh = 4;
														relancer = 1;
														break;
													}
												}
											}
										}
									}
								}
							}
						}
					}
					De = 6;
				}
				while (1) // Tour de J3
				{
					if (sortie3 == 0 && choixCh == 1)
					{
						if (J[2].posCh1 == EJ3CH1)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer3 = RollIs6(J, i);
							MajCh = 1;
							//lancer3 = 1;
						}
						else if (J[2].posCh2 == EJ3CH2)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer3 = RollIs6(J, i);
							MajCh = 2;
						}
						else if (J[2].posCh3 == EJ3CH3)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer3 = RollIs6(J, i);
							MajCh = 3;
						}
						else if (J[2].posCh4 == EJ3CH4)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer3 = RollIs6(J, i);
							MajCh = 4;
						}
						if (lancer3) { sortie3 = 1; De = 6; }
					}

					if (lancer3 == 0 && resDe == 0) { relancer = 0; }
					else { choixCh = 0; }

					if (sortie3 == 1)
					{
						sortie3 = insertPlateau(J, tab, EcuX, EcuY, X, Y, i);
						
					}
					else if (sortie3 == 0 && resDe != 0)
					{
						EndGame = jeuPlateau(J, MajCh, tab, X, Y, i, recul3, resDe, EchXJ, EchYJ, indScale);
						
					}

					if (EndGame == 1) { victoire = i; EndGame = 0; }

					if (De == 6) { relancer = 1; }
					else if (resDe != 6 && resDe != 0) { relancer = 0; }
					if (relancer == 1 && victoire == 7)
					{
						resDe = lancer(J, i);
						De = resDe;
						lancer3 = 0;
					}
					else { break; }
					recul3 = 0;
				}
			}
			De = 0;
			resDe = 0;
		}

		testPosScale(J, i);

		sortie3 = 0;
		lancer3 = 0;
		recul3 = 0;

		resDe = 0;
		De = 0;
		choixCh = 1;
		relancer = 1;
		MajCh = 0;

		AffTab(tab);
		Sleep(1000);

		if (victoire != 7) { break; }

		{
			
			printf("Tour de J4.\n");
			i = 3;
			if ((J[3].posCh1 == EJ4CH1 && J[3].posCh2 == EJ4CH2 && J[3].posCh3 == EJ4CH3 && J[3].posCh4 == EJ4CH4) &&(J[3].scaleCh1 == 0 && J[3].scaleCh2 == 0 && J[3].scaleCh3 == 0 && J[3].scaleCh4 == 0))
			{
				while (1) // Tour de J4
				{
					if (sortie4 == 0 && choixCh == 1)
					{
						if (J[3].posCh1 == EJ4CH1)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer4 = RollIs6(J, i);
							MajCh = 1;
							//lancer4 = 1;
						}
						else if (J[3].posCh2 == EJ4CH2)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer4 = RollIs6(J, i);
							MajCh = 2;
						}
						else if (J[3].posCh3 == EJ4CH3)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer4 = RollIs6(J, i);
							MajCh = 3;
						}
						else if (J[3].posCh4 == EJ4CH4)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer4 = RollIs6(J, i);
							MajCh = 4;
						}
						if (lancer4) { sortie4 = 1; De = 6; }
					}

					if (lancer4 == 0 && resDe == 0) { relancer = 0; }
					else { choixCh = 0; }

					if (sortie4 == 1)
					{
						sortie4 = insertPlateau(J, tab, EcuX, EcuY, X, Y, i);
						
					}
					else if (sortie4 == 0 && resDe != 0)
					{
						EndGame = jeuPlateau(J, MajCh, tab, X, Y, i, recul4, resDe, EchXJ, EchYJ, indScale);
						
					}

					if (EndGame == 1) { victoire = i; EndGame = 0; }

					if (De == 6) { relancer = 1; }
					if (resDe != 6 && resDe != 0) { relancer = 0; }

					if (relancer == 1 && victoire == 7)
					{
						resDe = lancer(J, i);
						De = resDe;
						lancer4 = 0;
					}
					else { break; }
				}
			}
			else
			{
				start = ' ';
				while (1)
				{
					if (J[i].bot == 0)
					{
						if (start != 'y' && start != '\n' && start != 'n')
						{
							printf("y pour sortir un cheval de l'ecurie, sinon n.\n");
						}
						else if (start == 'y' || start == 'n')
						{
							path = start;
							break;
						}
						start = getchar();
					}
					else
					{
						if (roll() % 2 == 1)
						{
							path = 'y';
						}
						else
						{
							path = 'n';
						}
						break;
					}
				}
				if (path == 'y')
				{
					/*sortie4 = 0;
					choixCh = 1;*/
					relancer = 1;
					choixCh = 1;
				}
				else
				{
					/*sortie4 = 0;
					resDe = 0;*/
					relancer = 1;
					choixCh = 0;
					//Selectionner le cheval
					while (1)
					{
						if (J[3].posCh1 != EJ4CH1 || J[3].scaleCh1 == 1)
						{
							start = ' ';
							while (1)
							{
								if (J[i].bot == 0)
								{
									if (start != 'y' && start != '\n' && start != 'n')
									{
										printf("Pour jouer le Cheval 1 appuyer sur y, sinon n.\n");
									}
									else if (start == 'y' || start == 'n')
									{
										path = start;
										break;
									}
									start = getchar();
								}
								else
								{
									if (roll() % 2 == 1)
									{
										path = 'y';
									}
									else
									{
										path = 'n';
									}
									break;
								}
							}
							if (path == 'y')
							{
								MajCh = 1;
								relancer = 1;
								break;
							}
							else
							{
								if (J[3].posCh2 != EJ4CH2 || J[3].scaleCh2 == 1)
								{
									start = ' ';
									while (1)
									{
										if (J[i].bot == 0)
										{
											if (start != 'y' && start != '\n' && start != 'n')
											{
												printf("Pour jouer le Cheval 2 appuyer sur y, sinon n.\n");
											}
											else if (start == 'y' || start == 'n')
											{
												path = start;
												break;
											}
											start = getchar();
										}
										else
										{
											if (roll() % 2 == 1)
											{
												path = 'y';
											}
											else
											{
												path = 'n';
											}
											break;
										}
									}
									if (path == 'y')
									{
										MajCh = 2;
										relancer = 1;
										break;
									}
									else
									{
										if (J[3].posCh3 != EJ4CH3 || J[3].scaleCh3 == 1)
										{
											start = ' ';
											while (1)
											{
												if (J[i].bot == 0)
												{
													if (start != 'y' && start != '\n' && start != 'n')
													{
														printf("Pour jouer le Cheval 3 appuyer sur y, sinon n.\n");
													}
													else if (start == 'y' || start == 'n')
													{
														path = start;
														break;
													}
													start = getchar();
												}
												else
												{
													if (roll() % 2 == 1)
													{
														path = 'y';
													}
													else
													{
														path = 'n';
													}
													break;
												}
											}
											if (path == 'y')
											{
												MajCh = 3;
												relancer = 1;
												break;
											}
											else
											{
												if (J[3].posCh4 != EJ4CH4 || J[3].scaleCh4 == 1)
												{
													start = ' ';
													while (1)
													{
														if (J[i].bot == 0)
														{
															if (start != 'y' && start != '\n' && start != 'n')
															{
																printf("Pour jouer le Cheval 4 appuyer sur y, sinon n.\n");
															}
															else if (start == 'y' || start == 'n')
															{
																path = start;
																break;
															}
															start = getchar();
														}
														else
														{
															if (roll() % 2 == 1)
															{
																path = 'y';
															}
															else
															{
																path = 'n';
															}
															break;
														}
													}
													if (path == 'y')
													{
														MajCh = 4;
														relancer = 1;
														break;
													}
												}
											}
										}
									}
								}
							}
						}
					}
					De = 6;
				}
				while (1) // Tour de J4
				{
					if (sortie4 == 0 && choixCh == 1)
					{
						if (J[3].posCh1 == EJ4CH1)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer4 = RollIs6(J, i);
							MajCh = 1;
							//lancer4 = 1;
						}
						else if (J[3].posCh2 == EJ4CH2)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer4 = RollIs6(J, i);
							MajCh = 2;
						}
						else if (J[3].posCh3 == EJ4CH3)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer4 = RollIs6(J, i);
							MajCh = 3;
						}
						else if (J[3].posCh4 == EJ4CH4)
						{
							printf("Il faut faire un 6 pour sortir votre cheval de l'ecurie.\n");
							lancer4 = RollIs6(J, i);
							MajCh = 4;
						}
						if (lancer4) { sortie4 = 1; De = 6; }
					}

					if (lancer4 == 0 && resDe == 0) { relancer = 0; }
					else { choixCh = 0; }

					if (sortie4 == 1)
					{
						sortie4 = insertPlateau(J, tab, EcuX, EcuY, X, Y, i);
						
					}
					else if (sortie4 == 0 && resDe != 0)
					{
						EndGame = jeuPlateau(J, MajCh, tab, X, Y, i, recul4, resDe, EchXJ, EchYJ, indScale);
						
					}

					if (EndGame == 1) { victoire = i; EndGame = 0; }

					if (De == 6) { relancer = 1; }
					else if (resDe != 6 && resDe != 0) { relancer = 0; }
					if (relancer == 1 && victoire == 7)
					{
						resDe = lancer(J, i);
						De = resDe;
						lancer4 = 0;
					}
					else { break; }
					recul4 = 0;
				}
			}
			De = 0;
			resDe = 0;
		}

		testPosScale(J, i);

		sortie4 = 0;
		lancer4 = 0;
		recul4 = 0;

		resDe = 0;
		De = 0;
		choixCh = 1;
		relancer = 1;
		MajCh = 0;

		AffTab(tab);
		Sleep(1000);

		if (victoire != 7) { break; }
	}

	printf("Joueur %d a gagner !\n", victoire+1);

	AffTab(tab);
	Sleep(1000);
	system("pause");
	free(J);
}