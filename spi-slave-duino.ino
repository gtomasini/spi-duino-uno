/*
 * SPI bus Slave duino  
 * 
 *
 */

#include <SPI.h>

/*
 * SPI lib spi consts
 * Arduino UNO (AU) o Arduino MEGA (AM):
 *
 * SS   - Slave Select pin 10 (AU) o pin 53 (AM)
 * MOSI - Master Out, Slave pin 11 (AU) o pin 51 (AM)
 * MISO - Master In, Slave Out pin 12 (AU) o pin 50 (AM)
 * SCLK - Serial Clock  pin 13 (AU) o pin 52 (AM)
 * 
 */

static char data[200];
static volatile byte ind=0;
static volatile bool endFlag=false;

void setup (void){
  Serial.begin (9600); 

  SPCR |= bit (SPE);//SPI mode slave using SPCR
  //ind=0;
  //endFlag=false;
  pinMode (MISO, OUTPUT);
  SPI.attachInterrupt();//IRQ enabled
  Serial.println("SPI SLAVE: Setup Done.");
}

//interrupt subroutine
ISR (SPI_STC_vect){
  //byte aux = SPDR;
  if (ind < sizeof data)  {
      data[ind] = SPDR;
      endFlag= (data[ind++] == '\0');
  }
  else{
     Serial.println("buffer full, discard!");
     ind=0;;
  }
}

void loop (void){
  if (!endFlag) return;
  
  Serial.print("SPI, received from master: ");
  Serial.println(data);
  ind = 0;
  endFlag = false;
}
