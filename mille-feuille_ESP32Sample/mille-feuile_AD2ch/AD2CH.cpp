#include "AD2CH.h"
#include "MILLE_FEUILLE.h"

AD2CH::AD2CH(uint8_t pin0, uint8_t pin1,uint8_t pin2,uint8_t pin3){

    if(pin0!=myMOSI){
      //not spi
      typeOfAD = 1;
      myPin[0] = pin0;
      myPin[1] = pin1;
      
    }else{
      typeOfAD = 0;
      myPin[0] = pin0;
      myPin[1] = pin1;
      myPin[2] = pin2;
      myPin[3] = pin3;
    }
}

void AD2CH::setup(void){
#ifdef ARDUINO
      SPI.begin();
#endif

#ifdef ESP32
  //SPI.setFrequency(1000000);
  //SPI.setDataMode(SPI_MODE0);
  SPI.begin();
#endif
      pinMode(myPin[3], OUTPUT);//CS pin
      digitalWrite(myPin[3], HIGH);
}

int AD2CH::read(uint8_t ch){
  uint8_t inByte, sendData;
  uint16_t myData;

  if(typeOfAD == 0){
    //Using MCP3202
    if(ch == 0){
        sendData = 0x80;
    }else if(ch == 1){
        sendData = 0xC0;
    }else{
        return -1;
    }
#ifdef ESP32
    SPI.setFrequency(1000000);
#endif
    delayMicroseconds(10);
    digitalWrite(myPin[3], LOW);
    delayMicroseconds(10);
    SPI.transfer(0x01);
    inByte = SPI.transfer(sendData);
    myData = inByte << 8;
    inByte = SPI.transfer(0x00);
    myData = myData + inByte - 0xE000;
    delayMicroseconds(10);
    digitalWrite(myPin[3], HIGH);
    delayMicroseconds(10);
  }else{
    //normal Analog read 
    if(ch == 0){
      myData = analogRead(myPin[0]);
    }else if(ch == 1){
      myData = analogRead(myPin[1]);
    }else{
        return -1;
    }
  }
  return myData;
}

int AD2CH::readDiff(uint8_t PN){
  uint8_t inByte, sendData;
  uint16_t myData;
  
  if(PN == 0){
    sendData = 0x00;
  }else if(PN == 1){
    sendData = 0x40;
  }else{
    return -1;
  }
  
#ifdef ESP32
    SPI.setFrequency(1000000);
#endif
  delayMicroseconds(10);
  digitalWrite(myPin[3], LOW);
  delayMicroseconds(10);
  SPI.transfer(0x01);
  inByte = SPI.transfer(sendData);
  myData = inByte << 8;
  inByte = SPI.transfer(0x00);
  myData = myData + inByte - 0xE000;
  delayMicroseconds(10);
  digitalWrite(myPin[3], HIGH);
  delayMicroseconds(10);
  
  return myData;
}
int AD2CH::readSimpleDiff(void){
  
  if(typeOfAD == 0){
    //using MCP3203  
    int reply = readDiff(0);
    if(reply == 0){
      reply = readDiff(1);
      reply = reply - 1;
    }else{
      readDiff(1);//for matching sampling rate
    }
    return reply;
  }else{
    //Normal AD pin
    return -1;//error
  }
}

