// 2025-2026 ikasturtea

/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia

// Guk garatutako fitxategiak
	
#include "definizioak.h"
#include "periferikoak.h"
#include "zerbitzuErrutinak.h"
#include "fondoak.h"
#include "grafikoak.h"
#include <stdio.h>    //Ausazkotasuna lortzeko
#include <stdlib.h> //Ausazkotasuna lortzeko
#include <time.h> //Alea sortzeko

int denb; // denbora neurtzen joateko; baloratu ea beharrezkoa den
int sekuentzia[MAX];
int asmatuta=0;
bool sortuta=false;
int zenbat=0;
int luzera=0;
int input_index=0;
int kol =-2;

int ukituDaiteke=BAI;

int logEgin=0;
EGOERA=ZAI; 
void proiektua01()
{
	

	
	// Aldagai baten definizioa
	int tekla=0;
	zenbat=0;

		        // Egoera definitu

	SarreraPantailaratu(); // Sarreran dagoen testua pantailan idatzi, Grafikoak.c -n definituta
		
	konfiguratuTenporizadorea(49152,0x43);   //Tenporizadorea segunduan 20 aldiz kontatzeko segunduro.
	konfiguratuTeklatua(0X400C);	           // SELECT tekla eta START teklak etenen bidez erabiltzeko.
	etenZerbErrutEzarri();			  // Zerbitzu errutinak gordetzen ditu.
	TekEtenBaimendu();			 // Teklatuaren etenak baimendu
	DenbEtenBaimendu();			// Tenporizadorearen etenak baimendu.
	konbinzaioan_gehitu();
	erakutsiDefault();

	ErlojuaMartxanJarri();
	while (1)
	{	
		//iprintf("\x1b[1;1HEgoera: %d", EGOERA);

		// ZAI egoeran dagoela, teklatuaren inkesta egin, sakatu den tekla SELECT bada informazioa erakutsi, 
		// eta START sakatzean jokoa hasi

		
		if(TeklaDetektatu()||ukimenUkitua()){
			//ErlojuaGelditu();

			if (SakatutakoTekla()==L)
			{
				logak();
				logEgin=LOG;
				
			}

			if (SakatutakoTekla()==R)
			{
				consoleClear();
				logEgin=0;
				
			}
			
			
			

			// if (EGOERA==ERAKUTSI)
			// {
			// 	EGOERA=JASO;
			// 	//ErlojuaMartxanJarri();
			// 	//erakutsiDefault();
			// 	//erakutsiAteaIrekita();
			// 	//iprintf("\x1b[22;1HKolorea: %d", 6);

			// }

			if (EGOERA==JASO)
			{
				iprintf("\x1b[21;1HKolorea: %d", sekuentzia[input_index]);
			}
			
			
			if (ukimenUkitua() && EGOERA==JASO && ukituDaiteke==BAI)
			{
				//ErlojuaMartxanJarri();
				//erakutsiDefault();
				kol = zona();
				ukituDaiteke=EZ;
				
				if (sekuentzia[input_index]==kol)
				{
					erakutsiKolorea(kol);
					input_index++;
					asmatuta++;
					iprintf("\x1b[16;1HPuntuazioa: %d", asmatuta);
					if (input_index >= luzera) {
						konbinzaioan_gehitu();
						input_index = 0;
						erakutsiBlack;
						EGOERA=ERAKUTSI;
					}

				}else{
					
					EGOERA=ITXITA;
					erakutsiKolorea(sekuentzia[input_index]);
				}
			

			}
			if (!ukimenUkitua())
			{
				ukituDaiteke=BAI;
			}
			
			

			if ((SakatutakoTekla()==A) && (EGOERA==GALDU))
			{
				EGOERA=ZAI;
				consoleClear();
				asmatuta=0;
				zenbat=0;
				luzera=0;
				input_index=0;
				lcdSwap();
				SarreraPantailaratu();
				erakutsiDefault();
			}
			
			
			
			
 
		}
		if (EGOERA==ITXITA)
		{
			
			consoleClear();
			
			lcdSwap();
			iprintf("\x1b[14;1HGAME OVER");	
			iprintf("\x1b[16;1HPuntuazioa: %d", asmatuta);
			EGOERA=GALDU;
			asmatuta=0;
			zenbat=0;
			luzera=0;
			input_index=0;
			
		}
	
		// if(logEgin==LOG){
		// 	logak();
		// }
			
	}
	IME=0;// Bukaeran etenak galarazi.

	
}//Proiektua01 amaiera

int ausazko_zbki_bat_itzuli(){	// Funtzio honek 0tik 3rako ausazko zenbaki bat itzultzen du.
	if(!sortuta){
		srand(time(NULL)); //Denborarekin ale bat sortu
		sortuta=true;
	}
	return rand()%4;

}
void konbinzaioan_gehitu(){  // Prozedura honek 0tik 3rako ausazko zenbaki bat konbinazio arrayan gehitzen du 
			    // hau beteta ez dagoen bitartean 
	int gehitu = ausazko_zbki_bat_itzuli();  
	sekuentzia[luzera]=gehitu;
	luzera++;
	
} 
void konbErakutsi(){
		
	int aukera=sekuentzia[zenbat];
	erakutsiKolorea(aukera);
	iprintf("\x1b[18;1Hkonbinazioa errepikatzea %d", zenbat);
	zenbat++;
	if (zenbat>=luzera)
	{
		zenbat=0;
		segPunt=0;
		input_index=0;
		EGOERA=JASO; //Erakutsi egoerara pasa
	}
	
}

void logak(){
	consoleClear();
	iprintf("\x1b[1;1HInputIndex: %d", input_index);
	iprintf("\x1b[3;1Hzenbat: %d", zenbat);
	iprintf("\x1b[5;1HLuzeera: %d", luzera);
	iprintf("\x1b[6;1HUkitu: %d", ukituDaiteke);
	iprintf("\x1b[16;1HPuntuazioa: %d", asmatuta);
	iprintf("\x1b[18;1HKolorea: %d", kol);
	iprintf("\x1b[21;1HKolorea: %d", sekuentzia[input_index]);
	
	
	
	
	size_t i;
	int non =7;
	for (i = 0; i < luzera; i++)
	{
		if (i>(non*2))
		{
			non++;
		}
		
		iprintf("\x1b[%d;%dHSekuentzia: %d", non, i+2, sekuentzia[i]);
	}
	
}
/***********************2025-2026*******************************/

