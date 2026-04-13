// 2025-2026 ikasturtea

/*-------------------------------------
definizioak.h
-------------------------------------*/

#include <nds.h>		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia

#define IME		(*(vuint32*)0x04000208) // Interrupt Master Enable -- Eten guztiak baimendu-galarazi
#define IE		(*(vuint32*)0x04000210) // Interrupt Enable -- Etenak banaka baimendu-galarazi
#define IF		(*(vuint32*)0x04000214) // Interrupt Flag -- Eten eskaeren erregistroa

// Etenak tratatzeko funtzioak
#define EtenakBaimendu() IME=1 // Eten guztiak baimendu
#define EtenakGalarazi() IME=0 // Eten guztiak galarazi

// Teklatuaren erregistroak
#define TEKLAK_KNT	(*(vu16*)0x4000132) // Teklatuaren kontrol-erregistroa
#define TEKLAK_DAT	(*(vu16*)0x4000130) // Teklatuaren datu-erregistroa

// Tenporizadorearen (Timer0) erregistroak
#define DENB0_KNT   (*(vuint16*)0x04000102) // Timer0-ren kontrol-erregistroa
#define DENB0_DAT    (*(vuint16*)0x04000100) // Timer0-ren datu-erregistroa

// Ukimen-pantailaren erregistroak
touchPosition PANT_DAT;

// Teklei izena eman diegu programaren irakurgarritasuna hobetzeko

#define A			0 
#define B			1
#define SELECT			2 
#define START			3
#define ESKUBI			4 
#define EZKER			5
#define GORA			6 
#define BEHERA			7
#define R			8 
#define L			9

// Automataren egoera posibleak ere irakurgarriagoak egiteko

#define ZAI 			0
#define INSTRUKZIOAK            1
#define ERAKUTSI 		2
#define JASO			3
#define ITXITA			4
#define GALDU			5
extern int EGOERA;
extern int zenbat;

/***********************2025-2026*******************************/

// Koloreak definitu
#define urdina 0
#define gorria 1
#define horia 2
#define berdea 3
#define beltza 4

#define  MAX 50