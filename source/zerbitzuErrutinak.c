// 2025-2026 ikasturtea

/*-------------------------------------
ZerbitzuErrutinak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"
#include "periferikoak.h"
#include "fondoak.h"
#include "spriteak.h"
#include "grafikoak.h"
//#include "proiektua01.c";


#define denbora 3

int EGOERA; // Automata zein egoeratan dagoen adierazteko erabilia
//int 3seg;   // Hiru segundo pasatzen ote diren ikusten joateko

void tekEten ()
{
if(EGOERA==INSTRUKZIOAK || EGOERA==ZAI){
	if(SakatutakoTekla()==START){
		GrafikoakHasieratu();
		iprintf("\x1b[1;5H INST HASI");
		EGOERA=ERAKUTSI;
		ErlojuaMartxanJarri();
	}
}



}

void tenpEten()
{
	static int tik=0;
	static int seg=0;
	static int seg3=0;
	static int segPunt=0;

	if (EGOERA==ERAKUTSI){
		tik++; 
		if (tik==2)
		{
			seg++;
			seg3++;
			iprintf("\x1b[13;5HPasa diren segunduak=%d", seg);
			tik=0;
			if (seg3==denbora){
				konbErakutsi();
				seg3=0;
			}
		}

	}
	if (EGOERA==ZAI){
		tik++;
		if (tik==2){
			seg++;
			tik=0;
			if (seg==1){
				erakutsiurdin();
			}
			else if (seg==2){
				erakutsigorri();
			}
			else if (seg==3){
				erakutsiberde();
			}
			else if (seg==4){
				erakutsihori();
				seg=0;
			}
	

		}
	}

	if (EGOERA==JASO)
	{
		tik++;
		
		if (tik==2)
		{
			segPunt++;
			tik=0;
			if (segPunt>zenbat+5)
			{
				EGOERA==ITXITA;
			}
			
		}
		
	}
	

}



void etenZerbErrutEzarri()
{
// HAU BETE BEHAR DUZUE
	irqSet(IRQ_TIMER0,tenpEten); // Timer0 ren zerbitzu errutina ezarri
	irqSet(IRQ_KEYS,tekEten);    // Teklatuaren zerbitzu errutina ezarri


	
}

/***********************2025-2026*******************************/

