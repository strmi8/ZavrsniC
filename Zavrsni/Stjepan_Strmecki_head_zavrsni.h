#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
typedef struct Pice
{
	char ime[20];
	float cijena;
}PICE;
void izbornik(void);
void DodavanjeAlkohola(void);
void DodavanjeSoka(void);
void Narudzba(void);
void NNarudzba(void);
void izlaz(void);
void sortiranje(void);
int compare_ID_Asc_Chars(const void*, const void*);
int compare_ID_Desc_Chars(const void*, const void*);
#endif 