// 2025-2026 ikasturtea

/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"


int tekla; // Sakatutako tekla gordetzeko aldagaia; baloratu ea behar den

touchPosition pos_pantaila; // aldagai globala


int TeklaDetektatu() 
{
	// TRUE itzultzen du teklaren bat sakatu dela detektatzen badu
	if ((~TEKLAK_DAT & 0x03ff)!=0) return 1;
	else return 0;

}

int SakatutakoTekla() 
{
	if    ((~TEKLAK_DAT& 0x0001)!=0)  return A; //A 
	else if((~TEKLAK_DAT& 0x0002)!=0) return B; //B 
	else if((~TEKLAK_DAT& 0x0004)!=0) return SELECT; //Select
	else if((~TEKLAK_DAT& 0x0008)!=0) return START; //Start
	else if((~TEKLAK_DAT& 0x0010)!=0) return ESKUBI; //Esk
	else if((~TEKLAK_DAT& 0x0020)!=0) return EZKER; //Ezk
	else if((~TEKLAK_DAT& 0x0040)!=0) return GORA; //Gora
	else if((~TEKLAK_DAT& 0x0080)!=0) return BEHERA; //Behera
	else if((~TEKLAK_DAT& 0x0100)!=0) return R; //R
	else if((~TEKLAK_DAT& 0x0200)!=0) return L; //L
	



	// Sakatutako teklaren balioa itzultzen du: A=0;B=1;SELECT=2;START=3;ESKUBI=4;EZKER=5;
	// GORA=6;BEHERA=7;R=8;L=9;
        // Saiatu kodea irakurgarria idazten.

	

}

int ukimenUkitua() {

	touchRead(&pos_pantaila); // libnds-ko funtzioa
	
	// Ez badago pixelik ukituta, return 0, bestela 1
	
	return !(pos_pantaila.px==0 && pos_pantaila.py==0);

}

  

touchPosition ukimenPos() {

	touchPosition pos;
	
	touchRead(&pos); //Lortzen dugu objetu bat non dauden ikututako posizioaren datuak
	
	return pos;

}

int zona(){

	if (!ukimenPos)
	{
		return -1; //Ez bada ikutu edo ez badira egin 80 gramoko indarra -1 bat itzuliko du
	}
	
	touchPosition touch = ukimenPos(); // Lortzen ditugu ikututako posizioaren datuak

	int x= touch.px;
	
	int y = touch.py;

	//Depende ze zonetan ikutzen den bueltatuko du zona bat edo beste
	if (x<127 && y<95)
	{
		return urdina;
	}
	else if (x>=127 && y<95)
	{
		return gorria;
	}
	else if (x>=127 && y>=95)
	{
		return horia;
	}
	else if (x<127 && y>=95)
	{
		return berdea;
	}

	return -1;
	
	
	


}


void konfiguratuTeklatua(int TEK_konf)
{
	// Teklatuaren konfigurazioa bere S/I erregistroak aldatuz
	// Parametro bezala jasotako balioan 1 egoeran dauden bitak aldatu kontrol-erregistroan
	TEKLAK_KNT|=TEK_konf;
	
}

void konfiguratuTenporizadorea(int Latch, int TENP_konf)
{
	// Tenporizadorearen konfigurazioa bere S/I erregistroak aldatuz
	// Parametro bezala jasotako balioan 1 egoeran dauden bitak aldatu kontrol-erregistroan
	DENB0_DAT=Latch;
	DENB0_KNT|=TENP_konf;
}

void TekEtenBaimendu()
{
	// Teklatuaren etenak baimendu
	// Lan hau burutzeko hasieran eten guztiak galarazi behar dira eta bukaeran baimendu 
	EtenakGalarazi();   // IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE|=(0x1<<12); // 12.bitean 1 ekoarekin or egin
	EtenakBaimendu();   // IME=1;
}

void TekEtenGalarazi()
{

	// Teklatuaren etenak galarazi
	// Lan hau burutzeko hasieran eten guztiak galarazi behar dira eta bukaeran baimendu 
	EtenakGalarazi();   // IME=0;
	IE&=~(0x1<<12); //IE ko 12. bita zerora jartzeko, not egitean denak 1koa and en 12 bita ezik
	
	EtenakBaimendu();   // IME=1;
}  

void DenbEtenBaimendu()
{

// Tenporizadore baten etenak baimendu (Timer0)
// Horretarako hasieran eten guztiak galarazi eta bukaeran berriro baimendu
	EtenakGalarazi();   // IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE|=(0x1<<3);
	EtenakBaimendu();   // IME=1;
}

void DenbEtenGalarazi()
{

// Tenporizadore baten etenak galarazi (Timer0)
// Horretarako hasieran eten guztiak galarazi eta bukaeran berriro baimendu
	EtenakGalarazi();   // IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE&=~(0x1<<3);
	EtenakBaimendu();   // IME=1;

}

void ErlojuaMartxanJarri()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	DENB0_KNT|=(0x1<<7);
	
}

void ErlojuaGelditu()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE&=~(0x7<<3);
}

/***********************2025-2026*******************************/

