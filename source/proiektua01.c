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
#define  MAX 50 /// MAX definituta (ARRAYAREN TAMAINA MAXIMOA)
int sekuentzia[MAX];
int zenbat=0;
int asmatuta=0;
bool sortuta=false;
void proiektua01()
{
	

	
	// Aldagai baten definizioa
	int tekla=0;

	EGOERA=ZAI; 	        // Egoera definitu

	SarreraPantailaratu(); // Sarreran dagoen testua pantailan idatzi, Grafikoak.c -n definituta
		
	konfiguratuTenporizadorea(49152,0x43);   //Tenporizadorea segunduan 20 aldiz kontatzeko segunduro.
	konfiguratuTeklatua(0X4009);	           // A tekla eta START teklak etenen bidez erabiltzeko.
	etenZerbErrutEzarri();			  // Zerbitzu errutinak gordetzen ditu.
	TekEtenBaimendu();			 // Teklatuaren etenak baimendu
	DenbEtenBaimendu();			// Tenporizadorearen etenak baimendu.
	

	while (1)
	{	
		
		// ZAI egoeran dagoela, teklatuaren inkesta egin, sakatu den tekla SELECT bada informazioa erakutsi, 
		// eta START sakatzean jokoa hasi

		ErlojuaMartxanJarri();
		if(TeklaDetektatu()){
			ErlojuaGelditu();
			if (SakatutakoTekla()==SELECT && EGOERA==ZAI){
				EGOERA=INSTRUKZIOAK;
				
				InfoPantailaratu(); //Informazioa pantailan jartzen du
			
			}

			/*if (SakatutakoTekla()==START && (EGOERA==ZAI || EGOERA==INSTRUKZIOAK))
			{
				ErlojuaMartxanJarri();
				EGOERA=ERAKUTSI; //Erakutsi egoerara pasa
			}*/

			if (ukimenUkitua()&&EGOERA==ERAKUTSI)
			{
				EGOERA=JASO;
				ErlojuaMartxanJarri();
				erakutsiDefault();
				consoleClear();
				iprintf("\x1b[16;1HPuntuazioa: %d", asmatuta);
			}
			
			if (ukimenUkitua() && EGOERA==JASO)
			{
				ErlojuaMartxanJarri();
				erakutsiDefault();
				int kol = zona();
				iprintf("\x1b[24;1HKolorea: %d", kol);
				if (kol==-1)
				{
					EGOERA=ITXITA;
					asmatuta=0;
				}else{
					if (sekuentzia[asmatuta]==kol)
					{
						asmatuta++;
						iprintf("\x1b[16;1HPuntuazioa: %d", asmatuta);

					}else{
						
						EGOERA=ITXITA;
						erakutsiKolorea(sekuentzia[asmatuta]);
					}
					
				}
				

			}
			if (EGOERA==ITXITA)
			{
				consoleClear();
				
				lcdSwap();
				iprintf("\x1b[14;1HGAME OVER");	
				iprintf("\x1b[16;1HPuntuazioa: %d", asmatuta);
				asmatuta=0;
			}

			if (SakatutakoTekla==A && EGOERA==ITXITA)
			{
				lcdSwap();
				EGOERA==ZAI;
				SarreraPantailaratu();
				erakutsiDefault();
			}
			
			
			
			
 
		}
	
			
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
	if (zenbat<MAX){
		int gehitu = ausazko_zbki_bat_itzuli();  
		sekuentzia[zenbat]=gehitu;
		zenbat++;
	}
} 
void konbErakutsi(){
		
	size_t i;
	for (i = 0; i < MAX; i++)
	{
		int aukera=sekuentzia[i];
		erakutsiKolorea(aukera);
		iprintf("\x1b[18;1Hkonbinazioa errepikatzea %d", aukera);
	}
	
}

/***********************2025-2026*******************************/

