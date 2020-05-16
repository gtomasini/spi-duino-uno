/*
 * SPI master duino bus 
 * 
 */
 
#include <SPI.h>

/*
 * SPI consts from lib
 *
 * SS   - Slave Select pin 10 (AU) o pin 53 (AM)
 * MOSI - Master Out, Slave In pin 11 (AU) o pin 51 (AM)
 * MISO - Master In, Slave Out  pin 12 (AU) o pin 50 (AM)
 * SCLK - Serial Clock  pin 13 (AU) o pin 52 (AM)
 * 
 */

void setup(void){
  digitalWrite(SS, HIGH);//slave disable

  // Master Mode, SCK, MOSI, SS as output
  // SCK & MOSI (LOW), SS (HIGH)
  SPI.begin();
  Serial.begin (9600); 
  SPI.setClockDivider(SPI_CLOCK_DIV8);//2MHz
  Serial.println("SPI MASTER: Setup Done.");
}

void loop(void){
  static unsigned int n=0;
  
  digitalWrite(SS, LOW);//Enable slave

  //char byte2send;//Send text msg
  char text[32];
  sprintf(text, "*HI THERE (%d)!", n++);
  Serial.println(text);
  int i=0;
  for (const char *msg=text; /*byte2send=*/ *msg != '\0'; msg++){
     SPI.transfer(*msg);
     Serial.print(i++);
     Serial.print(" ");
  }
  SPI.transfer(0);//str end
  Serial.print(i++);
  Serial.print(" ");
  Serial.println("\n******************end of msg transmition");
  
  digitalWrite(SS, HIGH);//disable slave

  delay(1000);
}
