#include "Stjepan_Strmecki_head_zavrsni.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <conio.h>
#include <time.h>



void izbornik()
{
	int broj;

	while (1)
	{
		do 
		{
			system("cls");
			printf("Odaberite jedan od izbora:\n(1)Dodavanje alokoholnog pica u datoteku alkohol. \n(2)Dodavanje bezalokoholnog pica u datoteku sokovi. \n(3)Narucivanje i ispis racuna.\n(4)Nasumicna narudzba \n(5)Pregled menija po cijeni. \n(6)Zavrsetak rada.\n \nOdabir: ");
			scanf("%d", &broj);
		} while (broj < 1 || broj > 6);
		switch (broj) 
		{
		case 1:
			DodavanjeAlkohola();
			break;
		case 2:
			DodavanjeSoka();
			break;
		case 3:
			Narudzba();
			break;
		case 4:
			NNarudzba();
			break;
		case 5:
			sortiranje();
			break;
		case 6:
			izlaz();
			break;
		}
	}
}
	


	
void DodavanjeAlkohola()
{
	int brojAlkohola = 0;
	PICE* unos = NULL;
	unos = (PICE*)calloc(1, sizeof(PICE));
	if (unos == NULL)
	{
		printf(" Greska pri alociranju memorije");
		exit(EXIT_FAILURE);
	}
	FILE* fp1 = NULL;
	fp1 = fopen("AlkoholnaPica.bin", "rb+");
	if (fp1 == NULL)
	{
		fp1 = fopen("AlkoholnaPica.bin", "wb");
		if (fp1 == NULL)
		{
			perror("Greška kod wb");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("Unesite ime pica: ");		
		scanf("%19s*[\n]", unos->ime);
		printf("Unesite cijenu pica: ");
		scanf("%f", &unos->cijena);
		brojAlkohola += 1;
		fwrite(&brojAlkohola, sizeof(int), 1, fp1);
		fwrite(unos, sizeof(PICE), 1, fp1);
		fclose(fp1);
		free(unos);
		_getch();
		return;
	}
	else
	{
		fp1 = fopen("AlkoholnaPica.bin", "r+b");
		if (fp1 == NULL)
		{
			perror("Greška kod r+b");
			exit(EXIT_FAILURE);
		}
		fread(&brojAlkohola, sizeof(int), 1, fp1);
		getchar();
		printf("Unesite ime pica: ");
		scanf("%19s*[\n]", unos->ime);
		printf("Unesite cijenu pica: ");
		scanf("%f", &unos->cijena);
		brojAlkohola += 1;
		rewind(fp1);
		fwrite(&brojAlkohola, sizeof(int), 1, fp1);
		brojAlkohola--;
		fseek(fp1, sizeof(int) + (brojAlkohola * sizeof(PICE)), SEEK_SET);
		fwrite(unos, sizeof(PICE), 1, fp1);
		fclose(fp1);
		free(unos);
		_getch();
		return;
	}
}




void DodavanjeSoka()
{
	int brojSoka = 0;
	PICE* unos = NULL;
	unos = (PICE*)calloc(1, sizeof(PICE));
	if (unos == NULL)
	{
		printf("Greska pri alociranju memorije");
		exit(EXIT_FAILURE);
	}
	FILE* fp1 = NULL;
	fp1 = fopen("BezAlkoholnaPica.bin", "rb+");
	if (fp1 == NULL)
	{
		fp1 = fopen("BezAlkoholnaPica.bin", "wb");
		if (fp1 == NULL) 
		{
			perror("Greška kod wb");
			exit(EXIT_FAILURE);
		}
		getchar();
		printf("Unesite ime pica: ");
		scanf("%19s*[\n]", unos->ime);
		printf("Unesite cijenu pica: ");
		scanf("%f", &unos->cijena);
		brojSoka += 1;
		fwrite(&brojSoka, sizeof(int), 1, fp1);
		fwrite(unos, sizeof(PICE), 1, fp1);
		fclose(fp1);
		free(unos);
		_getch();
		return;
	}
	else 
	{
		fp1 = fopen("BezAlkoholnaPica.bin", "r+b");
		if (fp1 == NULL) 
		{
			perror("Greška kod r+b");
			exit(EXIT_FAILURE);
		}
		fread(&brojSoka, sizeof(int), 1, fp1);
		getchar();
		printf("Unesite ime pica: ");
		scanf("%19s*[\n]", unos->ime);
		printf("Unesite cijenu pica: ");
		scanf("%f", &unos->cijena);
		brojSoka += 1;
		rewind(fp1);
		fwrite(&brojSoka, sizeof(int), 1, fp1);
		brojSoka--;
		fseek(fp1, sizeof(int) + (brojSoka * sizeof(PICE)), SEEK_SET);
		fwrite(unos, sizeof(PICE), 1, fp1);
		fclose(fp1);
		free(unos);
		_getch();
		return;
	}
}




void Narudzba()
{
	char upit[20] = {0};
	char odabir[20] = { 0 };
	system("cls");
	printf("Upisite kakvo pice zelite naruciti (alkoholno) ili (bezalkoholno]): ");
	scanf("%19s", &upit);
	while (1)
	{
		if (strcmp(upit, "alkoholno") == 0 || strcmp(upit, "ALKOHOLNO") == 0)
		{
			PICE* ispis = NULL;
			FILE* fp2 = NULL;
			fp2 = fopen("AlkoholnaPica.bin", "rb");
			if (fp2 == NULL)
			{
				perror("Greska kod rb");
				exit(EXIT_FAILURE);
			}
			else
			{
				int prviIscitani;
				rewind(fp2);
				fread(&prviIscitani, sizeof(int), 1, fp2);
				ispis = (PICE*)calloc(prviIscitani, sizeof(PICE));
				if (ispis == NULL)
				{
					printf("Greska pri alociranju memorije\n");
					exit(EXIT_FAILURE);
				}
				fseek(fp2, sizeof(int), SEEK_SET);
				for (int i = 0; i < prviIscitani; i++)
				{
					fread(ispis, sizeof(PICE), 1, fp2);
					fprintf(stdout, "ime alkoholnog pica je %s ", ispis->ime);
					fprintf(stdout, " cijena alkoholnog pica je %.2f\n", ispis->cijena);
				}
				printf("\nOdabir: ");
				scanf("%19s", &odabir);
				FILE* fp3 = NULL;
				fp3 = fopen("PovijestNarucivanja.txt", "a");
				if (fp3 == NULL)
				{
					perror("Greska kod a");
					exit(EXIT_FAILURE);
				}
				else 
				{
					fseek(fp2, sizeof(int), SEEK_SET);
					for (int i = 0; i < prviIscitani; i++)
					{
						fread(ispis, sizeof(PICE), 1, fp2);
						if (strcmp(ispis->ime, odabir) == 0)
						{
							fprintf(fp3, "Ime: %s\n", ispis->ime);
							fprintf(fp3, "Cijena: %.2f\n", ispis->cijena);
							break;
						}
					}
					fclose(fp3);
					fclose(fp2);
					free(ispis);
					_getch();
					return;
				}
			}
		}
		else if (strcmp(upit, "bezalkoholno") == 0 || strcmp(upit, "BEZALKOHOLNO") == 0)
		{
			PICE* ispis = NULL;
			FILE* fp2 = NULL;
			fp2 = fopen("BezAlkoholnaPica.bin", "rb");
			if (fp2 == NULL)
			{
				perror("Greska kod rb");
				exit(EXIT_FAILURE);
			}
			else
			{
				int prviIscitani;
				rewind(fp2);
				fread(&prviIscitani, sizeof(int), 1, fp2);
				ispis = (PICE*)calloc(prviIscitani, sizeof(PICE));
				if (ispis == NULL)
				{
					printf("Greska pri alociranju memorije\n");
					exit(EXIT_FAILURE);
				}
				fseek(fp2, sizeof(int), SEEK_SET);
				for (int i = 0; i < prviIscitani; i++)
				{
					fread(ispis, sizeof(PICE), 1, fp2);
					fprintf(stdout, "ime bezalkoholnog pica je %s ", ispis->ime);
					fprintf(stdout, " cijena bezalkoholnog pica je %.2f\n", ispis->cijena);
				}
				printf("\nOdabir: ");
				scanf("%19s", &odabir);
				FILE* fp3 = NULL;
				fp3 = fopen("PovijestNarucivanja.txt", "a");
				if (fp3 == NULL)
				{
					perror("Greska kod a");
					exit(EXIT_FAILURE);

				}
				else 
				{
					fseek(fp2, sizeof(int), SEEK_SET);
					for (int i = 0; i < prviIscitani; i++)
					{
						fread(ispis, sizeof(PICE), 1, fp2);
						if (strcmp(ispis->ime, odabir) == 0)
						{
							fprintf(fp3, "Ime: %s\n", ispis->ime);
							fprintf(fp3, "Cijena: %.2f\n", ispis->cijena);
							break;
						}
					}
					fclose(fp3);
					fclose(fp2);
					free(ispis);
					_getch();
					return;
				}
			}
		}
		else
		{
			printf("Mozete izabrati samo iz alkoholnog i bezalkoholnog asortimana!");
			_getch();
			return;
		}
	}
	
	
}




void NNarudzba()
{
	int file_Od, citaj, pice_Od;
	file_Od = rand() % 2 + 1;
	FILE* fp = NULL;
	PICE* selekcija = NULL;	

	if (file_Od == 1)
	{		
		fp = fopen("AlkoholnaPica.bin", "rb");
		if (fp == NULL)
		{
			perror("Alkoholna bin");
			exit(EXIT_FAILURE);
		}
		fread(&citaj, sizeof(int), 1, fp);
		selekcija = (PICE*)calloc(citaj, sizeof(PICE));
		if (selekcija == NULL) 
		{
			perror("Struktura");
			exit(EXIT_FAILURE);
		}
		fread(selekcija, sizeof(PICE), citaj, fp);
		pice_Od = rand() % citaj;		
		FILE* fp3 = NULL;
		fp3 = fopen("PovijestNarucivanja.txt", "a");
		if (fp3 == NULL)
		{
			perror("Greska kod a");
			exit(EXIT_FAILURE);
		}
		else
		{
			fprintf(fp3, "Ime: %s\nCijena: %.2f\n\n", (selekcija + pice_Od)->ime, (selekcija + pice_Od)->cijena);
			fprintf(stdout, "Ime: %s\nCijena: %.2f\n", (selekcija + pice_Od)->ime, (selekcija + pice_Od)->cijena);
		}
		_getch();
		fclose(fp);
		fclose(fp3);
		free(selekcija);
		return;
	}
	else
	{
		fp = fopen("BezAlkoholnaPica.bin", "rb");
		if (fp == NULL)
		{
			perror("BezAlkoholna bin");
			exit(EXIT_FAILURE);
		}
		fread(&citaj, sizeof(int), 1, fp);
		selekcija = (PICE*)calloc(citaj, sizeof(PICE));
		if (selekcija == NULL)
		{
			perror("Struktura");
			exit(EXIT_FAILURE);
		}
		fread(selekcija, sizeof(PICE), citaj, fp);
		pice_Od = rand() % citaj;
		FILE* fp3 = NULL;
		fp3 = fopen("PovijestNarucivanja.txt", "a");
		if (fp3 == NULL)
		{
			perror("Greska kod a");
			exit(EXIT_FAILURE);
		}
		else
		{
			fprintf(fp3, "Ime: %s\nCijena: %.2f\n\n", (selekcija + pice_Od)->ime, (selekcija + pice_Od)->cijena);
			fprintf(stdout, "Ime: %s\nCijena: %.2f\n", (selekcija + pice_Od)->ime, (selekcija + pice_Od)->cijena);
		}
		_getch();
		fclose(fp);
		fclose(fp3);
		free(selekcija);
		return;
	}
}




void izlaz()
{
	int odabirizlaza;
	printf("jeste li sigurni?\n(1) DA\n(2) NE\n");
	scanf("%d", &odabirizlaza);
	if (odabirizlaza == 1)
	{
		exit(EXIT_SUCCESS);
	}
	else
	{
		return;
	}
}




int compare_ID_Asc_Chars(const void* x, const void* y)
{
	PICE* ID_x = (PICE*)x;
	PICE* ID_y = (PICE*)y;
	return (int)(ID_x->cijena - ID_y->cijena);
}
int compare_ID_Desc_Chars(const void* x, const void* y)
{
	PICE* ID_x = (PICE*)x;
	PICE* ID_y = (PICE*)y;
	return (int)(ID_y->cijena - ID_x->cijena);
}




void sortiranje()
{
	int odabir, prviIscitani, alk_Bezalk;
	do
	{
		system("cls");
		printf("\n(1) Alkoholno\n(2) Bezalkoholno\n\nOdabir: ");
		scanf("%d", &alk_Bezalk);
	} while (alk_Bezalk < 1 || alk_Bezalk > 2);
	FILE* fp2 = NULL;
	if(alk_Bezalk == 1)
	{
		fp2 = fopen("AlkoholnaPica.bin", "rb");
		if (fp2 == NULL)
		{
			perror("Greska kod rb");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fp2 = fopen("BezAlkoholnaPica.bin", "rb");
		if (fp2 == NULL)
		{
			perror("Greska kod rb");
			exit(EXIT_FAILURE);
		}
	}
	rewind(fp2);
	fread(&prviIscitani, sizeof(int), 1, fp2);
	PICE* ispis = NULL;
	ispis = (PICE*)calloc(prviIscitani, sizeof(PICE));
	if (ispis == NULL)
	{
		printf(" Greska pri alociranju memorije\n");
		exit(EXIT_FAILURE);
	}
	do
	{
		system("cls");
		printf("Sortiraj:\n(1) Uzlazno\n(2) Silazno\n\nOdabir: ");
		scanf("%d", &odabir);
	} while (odabir < 1 || odabir > 2);
	fseek(fp2, sizeof(int), SEEK_SET);
	fread(ispis, sizeof(PICE), prviIscitani, fp2);
	if (odabir == 1)
	{
		qsort(ispis, prviIscitani, sizeof(PICE), compare_ID_Asc_Chars);
	}
	else
	{
		qsort(ispis, prviIscitani, sizeof(PICE), compare_ID_Desc_Chars);
	}
	for (int i = 0; i < prviIscitani; i++)
	{
		if (alk_Bezalk == 1)
		{
			fprintf(stdout, "ime alkoholnog pica je %s ", (ispis + i)->ime);
			fprintf(stdout, " cijena alkoholnog pica je %.2f\n", (ispis + i)->cijena);
		}
		else
		{
			fprintf(stdout, "ime bezalkoholnog pica je %s ", (ispis + i)->ime);
			fprintf(stdout, " cijena bezalkoholnog pica je %.2f\n", (ispis + i)->cijena);
		}
	}
	free(ispis);
	fclose(fp2);
	_getch();
	return;
}
































