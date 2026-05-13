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
int sekuentzia[MAX]; // Hemen gorde egiten dira koloreak
int asmatuta=0;		//	Hemen puntuazioa gorde egiten dugu
bool sortuta=false;	//	Erabiltzen da jakiteko ea sortu egin den seed bat, ez bada sortu, sortu egiten du
int zenbat=0;		// 	Erabiltzen da jakiteko zenbat kolore erakutsi diren pantailan
int luzera=0;		//	Jakiteko zenbat elementu dauden listan, hau da, zenbat kolore dauden
int input_index=0;	//	Honekin jakiten dugu zenbat aldiz klik egin dugun pantailan, hau da, jakiteko zenbatgaren kolorea asmatuko behar duen
int kol =-2;		//	Erabiltzen da jakiteko ze kolore ukitu den pantailan, eta horrekin konparatu input_index-en egon behar den kolorearekin

/*
Hemengo honek arrazoi berezi bat dauka, pantaila ukitzen dugunez, eta denbora guztian dagoenez detektatzen, nahi degu bakarrik kontuan artzeko altzatzen dugunean arkatza pantailatik.
Ordun honek interuptore moduan funtzionatzen du, jakiteko detektatu al duen pantaila edo ez
*/
int ukituDaiteke=BAI;

// Hasieratzen dugu proiektua ZAI egoeran.
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
	//konbinzaioan_gehitu();		// Gehitzen dugu listara lehenengo kolorea, bestela utzik hasiko zen.
	erakutsiDefault();			// Erakusten du lehenengo patroia, bakarrik atzeko fondoa

	ErlojuaMartxanJarri();		// Erlojua asieratzen dugu
	while (1)
	{	
		//iprintf("\x1b[1;1HEgoera: %d", EGOERA);

		// ZAI egoeran dagoela, teklatuaren inkesta egin, sakatu den tekla SELECT bada informazioa erakutsi, 
		// eta START sakatzean jokoa hasi

		
		if(TeklaDetektatu()||ukimenUkitua()){ // Nahi degu teklatua edo pantaila ukitzean kontuan artzea gertatzen dena
			//ErlojuaGelditu();


			/*
			Hemengo bi if hauek egiten dutena da, erakutsi log-ak, ikusteko guk ze aldagai dauden debugeatzeko.
			Eta R-ekin pantaila guztia garbitzen dugu
			Denbora guztian baldin bazegoen pantailan imprimatzen log-ak, oso gaizki ikusten zen, zegoelako borratzen eta idazten. Horregatik klikatzean egitea erabaki genuen
			*/
			if (SakatutakoTekla()==L)
			{
				logak();			
			}

			if (SakatutakoTekla()==R)
			{
				consoleClear();
			}
			
			
			

			// if (EGOERA==ERAKUTSI)
			// {
			// 	EGOERA=JASO;
			// 	//ErlojuaMartxanJarri();
			// 	//erakutsiDefault();
			// 	//erakutsiAteaIrekita();
			// 	//iprintf("\x1b[22;1HKolorea: %d", 6);

			// }

			// Erabiltzen genune jakiteko zein zen erantzun zuzena aukeratzekoan koloreak
			// if (EGOERA==JASO)
			// {
			// 	iprintf("\x1b[21;1HKolorea: %d", sekuentzia[input_index]);
			// }
			
			// Erabiltzen dugu jakiteko ea gauden JASO egoera, eta ukitu daiteken pantaila.
			// Bi baldintzak betetzen baditugu eta pantaila ukitzen bada, IF-eko kodea exekutatuko dugu.
			if (ukimenUkitua() && EGOERA==JASO && ukituDaiteke==BAI)
			{
				//ErlojuaMartxanJarri();
				//erakutsiDefault();
				// Lortzen dugu ukitu dugun zonaren kolorea eta esaten diogu pantaila ezin dela ukitu.
				kol = zona();
				ukituDaiteke=EZ;
				
				// Ikutun dugun kolorea baldin bada listako egokia asmatu dugula esan nahi du, bestela galdu egin dugula eta GALDU egoerara pasatzen gara
				if (sekuentzia[input_index]==kol)
				{
					// Asmatzen badugu erakusten dugu asmatutako kolorea jakiteko asmatu dugula
					erakutsiKolorea(kol);
					// Asmatzean, esaten diogu begiratu behar duela berriro klikatzean listako hurrengo balioa
					input_index++;
					// asmatutari +1 egiten diogu esanez asmatu dugula
					asmatuta++;
					iprintf("\x1b[16;1HPuntuazioa: %d", asmatuta);
					// jakinda zenbat den listaren luzeera eta klik egin duguela listako elementu guztietatikam, esan nahi du erakutsi egoerara pasatzen garela
					if (input_index >= luzera) {
						// gehitzen dugu listara beste elementu bat
						konbinzaioan_gehitu();
						// reiniziatzen dugu balorea esateko ez dugula klikatu baliorik
						input_index = 0;
						// erakusten dugu fondo belta
						//erakutsiBlack();
						// aldatzen gara erakutsi egoerara
						EGOERA=ERAKUTSI;
					}

				}else{
					
					erakutsiKolorea(sekuentzia[input_index]);
					// Galtzean deitzen diogu funtzio honeri erakusteko game over pantaila eta datuak berrabiarazteko
					galduDegu();
				}
			

			}
			// Iterazio bakoitzean begiratzen du ea ez dagoen pantaila ukitzen, ez badago esaten diogu pantaila ukitu daitekela
			if (!ukimenUkitua())
			{
				ukituDaiteke=BAI;
			}
			
			
			// Galdu egoeran baldin bagaude, eta A botoia klikatzean nahi degu hasieratu guztia hasieratikan
			if ((SakatutakoTekla()==A) && (EGOERA==GALDU))
			{
				// Ezartzen diogu egoera ZAI moduan
				EGOERA=ZAI;
				// Garbitu pantailako datuak
				consoleClear();
				// Pantailak buelta egin berriro ongi jartzeko
				lcdSwap();
				// Sarrerako pantaila erakusten dugu
				SarreraPantailaratu();
				erakutsiDefault();
			}
			
			
			
			
 
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
	return rand()%4; // Bueltatzen du zenbaki bat auzas 0-tik 3-ra. Koloreentzat

}
void konbinzaioan_gehitu(){  // Prozedura honek 0tik 3rako ausazko zenbaki bat konbinazio arrayan gehitzen du 
	// Gehitzen dugu kolore berri bat listara eta luezerari gehitzen diogu bat
	int gehitu = ausazko_zbki_bat_itzuli();  
	sekuentzia[luzera]=gehitu;
	luzera++;
	
} 
// Lehenagoko bertsio batean erabiliko genuke, baina gaur egun ez dugu erabiltzen
// void konbErakutsi(){
		
// 	int aukera=sekuentzia[zenbat];
// 	erakutsiKolorea(aukera);
// 	iprintf("\x1b[18;1Hkonbinazioa errepikatzea %d", zenbat);
// 	zenbat++;
// 	if (zenbat>=luzera)
// 	{
// 		zenbat=0;
// 		segPunt=0;
// 		input_index=0;
// 		EGOERA=JASO; //Erakutsi egoerara pasa
// 	}
	
// }

// Erabitlzen dugu ikusteko momentu honetan dauden balio guztiak, aldagaietan
void logak(){
	consoleClear();
	iprintf("\x1b[1;1HInputIndex: %d", input_index);
	iprintf("\x1b[3;1Hzenbat: %d", zenbat);
	iprintf("\x1b[5;1HLuzeera: %d", luzera);
	iprintf("\x1b[6;1HUkitu: %d", ukituDaiteke);
	iprintf("\x1b[16;1HPuntuazioa: %d", asmatuta);
	iprintf("\x1b[18;1HAukeratutako Kolorea: %d", kol);
	iprintf("\x1b[21;1HKolorea: %d", sekuentzia[input_index]);
	
	
	
	// Erabiltzen genuen ikusteko zeintzuk ziren listako balore guztiak
	// size_t i;
	// int non =7;
	// for (i = 0; i < luzera; i++)
	// {
	// 	if (i>(non*2))
	// 	{
	// 		non++;
	// 	}
		
	// 	iprintf("\x1b[%d;%dHSekuentzia: %d", non, i+2, sekuentzia[i]);
	// }
	
}

// Galtzen dugunean zer gertatu behar den erabakitzen duguna
void galduDegu(){
	// Kontsola garbitu erakusteko gameOver
	consoleClear();
			
	// Pantailei buelta heman ikusteko beheko pantailan game over mezua
	lcdSwap();
	iprintf("\x1b[14;1HGAME OVER");	
	iprintf("\x1b[16;1HPuntuazioa: %d", asmatuta);
	// Egoera aldatu galdura
	EGOERA=GALDU;
	// Berabiaratzi balio guztiak 0-ra
	asmatuta=0;
	zenbat=0;
	luzera=0;
	input_index=0;
}
/***********************2025-2026*******************************/

