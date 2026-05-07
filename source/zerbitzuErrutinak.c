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

void tekEten () // Sakatu egin den teklatuaren etenarentzat erabiltzen da
{
	 /*
	 Egoera baldin bata INTSUKZIOAK edo ZAI eta sakatzen bada START botoia, garbitzen dugu goiko pantaila, eta imprimatzen dugu daukagun puntuazioa, kasu honetan beti izango dela 0
	 Ondoren gehitzen dugu listara zein izango den hurrengo kolorea, asieran denez, utzi dago, ordun gehitzen dugu lehenengoa eta beltza jartzen dugu fondoa, horrela animazioa garbitzen dugun.
	 Eta pasatzen gara erakutsi egoerara.
	 */
	if(EGOERA==INSTRUKZIOAK || EGOERA==ZAI){
		if(SakatutakoTekla()==START){
			consoleClear();
			iprintf("\x1b[16;1HPuntuazioa: %d", asmatuta);
			konbinzaioan_gehitu();
			erakutsiKolorea(beltza);
			EGOERA=ERAKUTSI;
			input_index=0;
		}
	}


	/*
	Baldin bagaude ZAI egoeran eta select klikatzen badugu erakusten digu jolasaren instrukzioak.
	*/
	if (SakatutakoTekla()==SELECT && EGOERA==ZAI){
				EGOERA=INSTRUKZIOAK;
				
				InfoPantailaratu(); //Informazioa pantailan jartzen du
			
			}




}
int segPunt=0;
void tenpEten()
{ // Hemen daukagu kodea erlojuak zein komandu exekutatu behar dituen
	static int tik=0;
	static int seg=0;
	static int seg3=0;
	

	

	//iprintf("\x1b[23;5HErlojua hasita");

	/*
	ERAKUTSI egoeran egiten duguna da erakutsi koloreen sekuentzia. Hortako bi segundutikan behin erakusten dugu listako hurrengo zenbakia eta horrek esaten digu zein kolore erakutsi behar den.
	Gordetzen dugu zenbat aldagaian zenbat kolore erakutsi ditugun. Erakutsi ditugun kolorean baldin badira listan dauden elementuen baino luzeago edo berdin den ordun esan nahi du bukatu duela eta JASO egoerara pasatzen da.
	*/
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


	/*
	ZAI egoeran, hau da jolasa asieratzean, animazio txiki bat jarri dugu, non dauden 4 koloreak bueltaka. Ordun egiten dugu da, 2 tik egitean segundu bat gehitu eta ondoren erakutsi kolorea.
	Egiten dugu seg-1 da koloreak 0-tik 3-ra daudenez  (4 da beltza) erakusteko zero garen kolorea eta horrela zirkulu batean.
	*/
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


	/* JASO egoeran gertatzen dena da, jolasa prest dagoela jasotzeko jokalariak non ukitzen duen. Ordun dagoenez denboragailu bat 0-ra iristean galtzeko.
		Baina egin dugun moduan denbora goraka doa ordun iristean listararen luzeera+5 segundutan galtzen dugu automatikoki.
		Egiten denbora pantailan beraka joatea, simplemente egiten dugu, eduki al dugun denbora maximoa - zenbat segundu goazen. Horrela 0-ra iristean da gauza bera denbora pasatzea ditugun segundu maximotikan.
	*/
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
				galduDegu();
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

