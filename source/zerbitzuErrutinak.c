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
#include "proiektua01.h";


#define denbora 3

int EGOERA; // Automata zein egoeratan dagoen adierazteko erabilia
//int 3seg;   // Hiru segundo pasatzen ote diren ikusten joateko

void tekEten ()
{
	if(EGOERA==INSTRUKZIOAK || EGOERA==ZAI){
		if(SakatutakoTekla()==START){
			consoleClear();
				iprintf("\x1b[16;1HPuntuazioa: %d", asmatuta);
				erakutsiKolorea(beltza);
				//ErlojuaMartxanJarri();
				//erakutsiDefault();
				//erakutsiAtea();
				EGOERA=ERAKUTSI;
				//zenbat=0;
				input_index=0;
		}
	}

	if (SakatutakoTekla()==SELECT && EGOERA==ZAI){
				EGOERA=INSTRUKZIOAK;
				
				InfoPantailaratu(); //Informazioa pantailan jartzen du
			
			}




}
int segPunt=0;
void tenpEten()
{
	static int tik=0;
	static int seg=0;
	static int seg3=0;
	

	

	//iprintf("\x1b[23;5HErlojua hasita");
	if (EGOERA==ERAKUTSI){
		tik++;
		if (tik==2){
			tik=0;
			seg++;

			if (seg % 2 == 1){
				// Mostrar color de la secuencia
				int aukera = sekuentzia[zenbat];
				erakutsiKolorea(aukera);
			} else {
				// Limpiar pantalla
				//erakutsiDefault();
				zenbat++;

				if (zenbat >= luzera){
					zenbat = 0;
					seg = 0;
					segPunt = 0;
					EGOERA = JASO;
				}
			}
		}
	}

	// if (EGOERA==zerbait){
	// 	tik++;
	// 	if (tik==2){
	// 		tik=0;
	// 		seg++;

	// 		erakutsiKolorea(beltza);
	// 		EGOERA=ERAKUTSI;
	// 	}
	// }


	if (EGOERA==ZAI){
		//consoleClear();
		tik++;
		if (tik==2){
			seg++;
			tik=0;
			//iprintf("\x1b[13;5HPasa diren segunduak=%d", seg);
			erakutsiKolorea(seg-1);
			if (seg==4)
			{
				seg=0;
			}
			
			
			// if (seg==1){
			// 	erakutsiurdin();
			// }
			// else if (seg==2){
			// 	erakutsigorri();
			// }
			// else if (seg==3){
			// 	erakutsihori();
			// }
			// else if (seg==4){
			// 	erakutsiberde();
			// 	seg=0;
			// }
	

		}
	}

	if (EGOERA==JASO)
	{
		tik++;
		
		if (tik==2)
		{
			erakutsiKolorea(beltza);
			segPunt++;
			tik=0;
			iprintf("\x1b[13;5HDenbora=%d", (luzera+5)-segPunt);
			if (segPunt>luzera+5)
			{
				EGOERA=ITXITA;
			}
			
		}
		
	}

	// if (logEgin=LOG)
	// {
	// 	tik++;
		
	// 	if (tik==3)
	// 	{
	// 		logak();
	// 		tik=0;
			
	// 	}
	// }
	
	

}



void etenZerbErrutEzarri()
{
// HAU BETE BEHAR DUZUE
	irqSet(IRQ_TIMER0,tenpEten); // Timer0 ren zerbitzu errutina ezarri
	irqSet(IRQ_KEYS,tekEten);    // Teklatuaren zerbitzu errutina ezarri


	
}

/***********************2025-2026*******************************/

