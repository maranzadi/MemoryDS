// 2025-2026 ikasturtea

/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia

/* Fondo desberdinak erakutsi nahi izango baditugu, hemen fondo bakoitzaren burukoa (.h fitxategia) gehitu behar da. Buruko horiek
automatikoki sortzen dira, konpilatzerako garaian, baina horretarako gogoratu behar da */

#include "fondoak.h"
#include "grafikoak.h"
#include "Atea.h"
#include "AteaIrekita.h"
#include "fondo1.h"
#include "gorri.h"
#include "hori.h"
#include "urdin.h"
#include "berde.h"
#include "definizioak.h"

/* Irudiak memorian kopiatzeko DMA kanala aukeratu (3.a) */
static const int DMA_CHANNEL = 3;

/* Pantailaratu nahi den grafiko bakoitzerako horrelako prozedura bat idatzi behar da */

void erakutsifondo1() {    //ALDATU DAGOKION IRUDIA !!!!
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     fondo1Bitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     fondo1BitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}

void erakutsiKolorea(int kolorea){
    if (kolorea==urdina)
    {
        erakutsiurdin();
    }
    else if (kolorea==gorria)
    {
        erakutsigorri();
    }
    else if (kolorea==horia)
    {
        erakutsihori();
    }
    else if (kolorea==berdea)
    {
        erakutsiberde();
    }
    else if (kolorea==beltza)
    {
        erakutsiBlack();
    }
    
    
    
    
    
}

void erakutsigorri() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     gorriBitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     gorriBitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}

void erakutsiBlack() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     blackBitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     blackBitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}

void erakutsihori() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     horiBitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     horiBitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}
void erakutsiurdin() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     urdinBitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     urdinBitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}
void erakutsiberde() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     berdeBitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     berdeBitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}


void erakutsiAtea() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     AteaBitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     AteaBitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}

void erakutsiDefault() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     fondo1Bitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     fondo1BitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}

void erakutsiAteaIrekita() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     AteaIrekitaBitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     AteaIrekitaBitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}
/***********************2025-2026*******************************/

