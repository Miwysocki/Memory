#include<msp430x14x.h>
#include "lcd.h"
#include "portyLcd.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define seg_length 0x0080

unsigned char i;
unsigned char ch_1;
unsigned char ch_2;
unsigned char ch_3;
unsigned char ch_4;
unsigned char ch_5;
unsigned char ch_6;
unsigned char ch[32]={"123"};
unsigned char chMenu1[20]={"1.Gejm  2.autors"};
unsigned char chMenu2[11]={"3.highScore"};
unsigned char chAutor1[16]={"Kamil Lobasiuk"};
unsigned char chAutor2[16]={"Michal Wysocki"};
unsigned char nick[20];
unsigned char zgaduj[6]={"zgaduj"};
int wyniki[4]={0,0,0,0};
 int poprzedni_wynik=0; //przesuniecie wynkow
    int poprzedni_wynik2=0;

unsigned char chlost[9]={"GAME OVER"};
unsigned char chlwost[3]={"WIN"};
int b=1;
int ile_ma_nick=0;
int zycie=3;
int zarodek;
int l_liter =2;
long long int timerr=1000;
void rel1_ON();
void rel2_ON();
void status_ON();
void blad();
void zle();
void podaj_nick();
void sprawdzanie();
void initPrzyciski();
void rel1_OFF();
void rel2_OFF();
void Menu();
void status_OFF();
void buzz();
void Gra();
void reset_zycia();

  void main( void )
{
  P4DIR = 0x0C;//buzzeer
  


  initPrzyciski();
  
  srand(time(NULL));

//P2DIR |= BIT1 ;                               // STATUS LED
WDTCTL=WDTPW+ WDTHOLD;                        // zatrzymanie WDT
InitPortsLcd();                               // inicjalizacja portów  
InitLCD();                                    // inicjalizacja LCD
clearDisplay();                               // czyszczenie LCD  
  Menu();
}
void sprawdzanie(){
  int tmp=0;
  int tmp2=0;
  int wygrana=0;


  while(1){
  tmp2=0;
    if((P4IN & BIT4) == 0){ //B1
      if(ch[tmp]=='1')   {

      tmp++;
      tmp2=1;
   Delayx100us(1000); 
      continue;
      }
     else if(tmp2!=1){
	  blad();
	break;
	}
    }
    

    if((P4IN & BIT5) == 0) //B2
    {
    if(ch[tmp]=='2')
    {
    // SEND_CHAR('g');
      tmp++;
      tmp2=1;
  Delayx100us(1000); 
      continue;
      }  
	else if(tmp2!=1){
	  blad();
	break;
	}
    }


    if((P4IN & BIT6) == 0) {  //B3
      if(ch[tmp]=='3') {
	//SEND_CHAR('h');
	tmp++;
      tmp2=1;
  Delayx100us(1000); 
      continue;}
	else{
	  blad();
	break;
	}
    }


    if((P4IN & BIT7) == 0) {  //B4
      if(ch[tmp]=='4') { 

      tmp++;
      tmp2=1;

  Delayx100us(1000); 
      continue;}
		else {

		  blad();
		  break;
			}		
		    }
    
if(tmp==l_liter){ //dobrze
  wygrana =1;
  l_liter++;
  
char znak[8] = {0,0,10,0,17,14,0,0};
for(int i=0;i<8;i++) SEND_CHAR(znak[i]);
char napis[8] = {'D','o','b','r','z','e',' ',0};
SEND_CMD(DD_RAM_ADDR);
for(int i=0;i<8;i++) SEND_CHAR(napis[i]);
  /*SEND_CHAR('D');
  SEND_CHAR('o');
  SEND_CHAR('B');
  SEND_CHAR('r');
  SEND_CHAR('z');
  SEND_CHAR('E');*/
  
          for(int k=0;k<5;k++) Delayx100us(1000);
       clearDisplay();
  break;
	}
}
}

void blad(){ //wylaczamy diode zycie--  buzzer
  zle();
  zycie--;
 for(int i=0; i<10;i++) buzz();
  if(zycie==2)
    rel2_OFF();
  if(zycie==1)
    rel1_OFF();
  if(zycie==0)          //GAME OVER
  {clearDisplay();
   
      if(wyniki[i] < l_liter){ 
	wyniki[i] = l_liter; 
	podaj_nick();
	;}//zamienienie wynikow

    	
    status_OFF();
    clearDisplay();
    for(int i=0; i<9; i++)
    {
      SEND_CHAR(chlost[i]); //przegrana
 	zycie=3;
  }
        for(int k=0;k<5;k++) Delayx100us(1000);
       clearDisplay();
       l_liter=2;
      Menu();
}
}

void initPrzyciski() {
P4DIR &= ~(BIT4 | BIT5 | BIT6 | BIT7);
}

void status_ON(){ 
P2DIR |= BIT1; 
P2OUT &= ~BIT1;
}
void rel1_ON(){ 
P1DIR |= BIT5;
P1OUT |= BIT5;

}
void rel2_ON(){ 
P1DIR |= BIT6; 
P1OUT |= BIT6;

}
void status_OFF(){ 
P2DIR |= BIT1; 
P2OUT |= BIT1;

}
void rel1_OFF(){ 
P1DIR |= BIT5; 
P1OUT &= ~BIT5;

}
void rel2_OFF(){ 
P1DIR |= BIT6; 
P1OUT &= ~BIT6;
}


void Menu()
{

  for(int i=0; i<32; i++)
  {
  SEND_CHAR(chMenu1[i]);
  }
   gotoSecondLine();
    for(int i=0; i<11; i++)
  {
  SEND_CHAR(chMenu2[i]);
  }
  while(1)
  {
    if((P4IN & BIT4) == 0){ //B1  gejm
      Gra();
    break;
    }   
    
    if((P4IN & BIT5) == 0) //B2  autorzy
    {
      clearDisplay();
				for(int i=0; i<14; i++)
			  {
			  SEND_CHAR(chAutor1[i]);
			  }
			   gotoSecondLine();
			    for(int i=0; i<14; i++)
			  {
			  SEND_CHAR(chAutor2[i]);
			  }
			  
			      
  	}

    if((P4IN & BIT6) == 0) {  //B3  HIGHSCORRE
      clearDisplay();
      
      
    SEND_CHAR('1');
    SEND_CHAR('.');
    for(int i=0;i<ile_ma_nick;i++){
      SEND_CHAR(nick[i]);
    }
    gotoSecondLine();
    SEND_CHAR('W');
    SEND_CHAR('Y');
    SEND_CHAR('N');
    SEND_CHAR('I');
    SEND_CHAR('K');
    SEND_CHAR(' ');
    char pw = (char)(wyniki[0]+48);
    SEND_CHAR(pw);
    
    
    
    }    
    
    if((P4IN & BIT7) == 0) { //B4 powrót do menu
    clearDisplay();
    Menu();
    }
  }
}

void buzz()
{
	int i;
	P4OUT = 0x08;
	for(i=0; i<100; i++)
	{
	P4OUT = ~P4OUT;
	int j =0;
	for(j=0;j<100;j++){}
	}
  
} 



void Gra(){
  reset_zycia();
  ch[0]=(int)(rand() % 4 + 49);
  ch[1]=(int)(rand() % 4 + 49);
while(1){
  clearDisplay(); 

  
for(int i=0;i<l_liter;i++){
 ch[l_liter]=(int)(rand() % 4 + 49);  //1-4
 for(int k=0;k< 5;k++) Delayx100us(timerr);
SEND_CHAR(ch[i]);
for(int k=0;k< 5;k++){
 Delayx100us(timerr);
 //clearDisplay();
 // opóŸnienie
}

    clearDisplay();                               // czyszczenie LCD 
if(timerr>100) //poziom trudnosc
timerr=timerr * 0.85;
}
Delayx100us(timerr);
for(int i=0;i<6;i++){ //zgaduj
SEND_CHAR(zgaduj[i]);
}
sprawdzanie();


}
}

void reset_zycia(){
  status_ON();
  rel1_ON();
  rel2_ON();
}

void podaj_nick(){
clearDisplay();
int aski=65;
int koniec=90;

while(1){
  clearDisplay();
  if((P4IN & BIT6) == 0) { //b3 potwierdzenie
    Delayx100us(50);
	nick[ile_ma_nick] = aski;
	ile_ma_nick++;
  };
 for(int i =0;i<=ile_ma_nick;i++){
   SEND_CHAR(nick[i]);
 }
  gotoSecondLine();
 SEND_CHAR(aski);
 if((P4IN & BIT5) == 0) aski++;//B2  nast litera
 Delayx100us(50);
 if(aski == 91) aski=65;
   
if((P4IN & BIT4) == 0) aski--;//b1 poprzednia
if(aski == 64) aski=90;
if((P4IN & BIT7) == 0) break;//b4
gotoSecondLine();
}
}

void zle(){
  clearDisplay();
  SEND_CHAR(':');
    SEND_CHAR('(');
}