

/* This software is for use with an Arduino UNO powered USB Relay device, designed to control access to microscopes via their 240V power.

The software is designed to turn on the power sequentially, first to the accessories, then the microscope stand, then the lumencor light source

To Program the unit, put a magnet against the mark on the relay control box

serial commands:

a - power the accessories
s - power the microscope stand
l - power the lumencor lamp
p - power everyting with delays between each
f - turns off all power instantly
d - turn off all power with a delay
x - turns off only the lumencor
? - returns "USB_Relay_unit", used by the software to find the correct com port of the USB relay device.



James Springfield, 21/5/2012
*/

//  Define the digital pins on the arduino Uno to be used for each device

#define manPin 5  // Manual control mode Pin
#define autoPin 6  // Automatic control mode Pin

#define accPin 7  // Accessories  Relay Pin
#define standPin 8 // Microscope  Relay Pin
#define lumencorPin 9 // Lumencor Relay Pin

unsigned long standDelay = 5000, lumenDelay = 5000, offDelay = 300000;
unsigned long now = 0, offTimer = 0;
byte Data = '.';
boolean manFlag = false, accFlag=false, standFlag=false, lumenFlag=false, pFlag=false, offFlag=false;


// Declare Functions

void ReadUSB()   //Read USB Port
{
  if (Serial.available()>0) 
  {
    Data = Serial.read();
    Serial.flush();
   }
}


void ID()   //Reply to USB query for Device ID
{
  if(Data == '?')
    {
      Serial.flush();
      Serial.println("USB_Relay_unit");
      Data = '.';
    }
}


void powerOff()   //Reply to USB query for Device ID
 {
   if(offFlag == true)
     {
       if (millis() > (offTimer + offDelay))
         {
            digitalWrite(accPin, LOW);
            digitalWrite(standPin, LOW);
            digitalWrite(lumencorPin, LOW);
            offFlag = false;
          }
      }else offFlag = false;
 }
    


//Setup the device at Power-on

void setup()
{
  pinMode(manPin,INPUT); // initialize the manPin pin as an input
  pinMode(autoPin,INPUT); // initialize the autoPin as an input 
  pinMode(accPin, OUTPUT); // initialize the accPin as an output:
  pinMode(standPin,OUTPUT); // initialize the standPin as an output: 
  pinMode(lumencorPin,OUTPUT); // initialize the lumencorPin as an output

  digitalWrite(accPin, LOW);
  digitalWrite(standPin, LOW);
  digitalWrite(lumencorPin, LOW);
 
  Serial.begin(9600);//start communication
  Serial.flush();//flush Serial buffer;

  delay(1000);
  
  Data = '.';
  manFlag = true;
}


//Main Program

void loop()
{
  ReadUSB();
  ID(); 
  if ((digitalRead(manPin) == HIGH) && (manFlag == false))  // Manual control mode
   {
     delay(100);
     manFlag = true;
     now = millis();  // start timer
     digitalWrite(accPin, HIGH);  // turn on the accessories powerboard
     accFlag = true;
     offFlag = false;
   }
   
   if (manFlag == true && accFlag == true && standFlag == false)
     {

       if (millis() >= now + standDelay)
         {
           digitalWrite(standPin, HIGH);
           standFlag = true;
           offFlag = false;
         }
     }
     
     if (manFlag == true && accFlag == true && standFlag == true && lumenFlag == false)
       {
         if (millis() >= now + standDelay + lumenDelay)
           {
             digitalWrite(lumencorPin, HIGH);
             lumenFlag = true;
             offFlag = false;
           }
       }
    
 
  if (digitalRead(autoPin) == HIGH)  // Automatic Control mode
   {
     manFlag = false;
     ReadUSB(); 
     ID(); 
     if (Data == 'a' || Data == 'A') // 'a' turns on only the accessories and stand powerboards with a delay between them
       {
         Data = '.';
         offFlag = false;
         standFlag = false;
         accFlag = false;
         lumenFlag = false;
         now = millis();  // start timer
//         Serial.println("acc on");
         digitalWrite(accPin, HIGH);  // turn on the accessories powerboard
         accFlag = true;
       }
       
      if (Data == 'p' || Data == 'P')  // 'p' turns on everything in order with delays
       {
         Data = '.';
         offFlag = false;
         standFlag = false;
         accFlag = false;
         lumenFlag = false;
         now = millis();  // start timer
//         Serial.println("acc on");
         digitalWrite(accPin, HIGH);  // turn on the accessories powerboard
         accFlag = true;
         pFlag = true;
       } 
   
   
     if (accFlag == true && standFlag == false)
       {
         if (millis() >= now + standDelay)
           {
//             Serial.println("stand on");
             digitalWrite(standPin, HIGH);
             standFlag = true;
             offFlag = false;
           }
       }
       
     if (accFlag == true && standFlag == true && pFlag == true && lumenFlag == false)
       {
         if (millis() >= now + standDelay + lumenDelay)
           {
             digitalWrite(lumencorPin, HIGH);
             lumenFlag = true;
             offFlag = false;
           }
       }       
        
     if (Data == 'l' || Data == 'L')  // turn on the lumencor when requested
       {
         offFlag = false;
         Data = '.';
//         Serial.println("lumencor on"); 
         digitalWrite(lumencorPin, HIGH);
       }
       

     if (Data == 's' || Data == 'S')  // turn on the microscope stand when requested
       {
         offFlag = false;
         Data = '.';
//         Serial.println("stand on");         
         digitalWrite(standPin, HIGH);
       }
       

     if (Data == 'd' || Data == 'D')  // turn off all power with a dealy
       {
          offTimer = millis();
          Data = '.';
          offFlag = true;
       }
       
     if (Data == 'f' || Data == 'F')  // turn off all power instantly
       {
          offFlag = false; 
          Data = '.';
          digitalWrite(accPin, LOW);
          digitalWrite(standPin, LOW);
          digitalWrite(lumencorPin, LOW);
       }
       
    
      powerOff();  // Function to delay power off of systems after logoff
        
       
     if (Data == 'x' || Data == 'X')  // turn off the lumencor only
       {
         Data = '.';
//         Serial.println("lumencor off");         
         digitalWrite(lumencorPin, LOW);
         offFlag = false;
       }
       
      
   }

   
    if ((digitalRead(manPin) == LOW) && (digitalRead(autoPin) == LOW))
    {
      Data = '.';      
      manFlag = false, accFlag=false, standFlag=false, lumenFlag=false, pFlag=false, offFlag=false;
      digitalWrite(accPin, LOW);
      digitalWrite(standPin, LOW);
      digitalWrite(lumencorPin, LOW);
    }

}




