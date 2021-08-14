   #include <LCD5110_Graph.h>
   #include<EEPROM.h>
   #include<Wire.h>
   #include<Rtc_Pcf8563.h>

   Rtc_Pcf8563 rtc;

   char* days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
   LCD5110 myGLCD(13,11,10,9,7);
   extern uint8_t SmallFont[];
   extern uint8_t TinyFont[];
   extern uint8_t MediumNumbers[];

   long int sense=3,rot=0,d=0,b=0,tog=6,x=0,u=0,tpin=A1,tempi=0,dt=0,ch=0;

   float sp=000.00,distance=000.00,tmd=0,asp=000.00,temp,diff =00.00;

   int fl=0,msg=0,i=0,rad=31,m=0;

   char h[42];


void setup()
  {
      rad=EEPROM.read(0);

      Serial.begin(9600);

       myGLCD.InitLCD();
       pinMode(sense,INPUT);
       pinMode(tpin,INPUT);
       for(int i=-60;i<12;i++)
      {
        myGLCD.setFont(SmallFont);
        myGLCD.print("WELCOME TO",i,12);
        myGLCD.update();
      }
      for(int t=84;t>21;t--)
      {
        myGLCD.setFont(SmallFont);
        myGLCD.print("BICYCLE ",t,20);
        myGLCD.update();
      }
      for (int z=-48;z<19;z++)
      {
        myGLCD.setFont(SmallFont);
        myGLCD.print("COMPUTER",z,29);
        myGLCD.update();
      }
      delay(1000);
      myGLCD.clrScr();  
      myGLCD.setFont(SmallFont);
 //   myGLCD.print(rtc.formatTime(),35,37);
      rtc.getDate();
      rtc.getTime();
      myGLCD.print(days[rtc.getWeekday()],CENTER,12);
      myGLCD.print(rtc.formatDate(),CENTER,24);
      myGLCD.update();   
      delay(4000);
      myGLCD.clrScr();
  }
void loop()
  {
    
    temp=analogRead(tpin);//from lm35
    temp=(temp*500/1023.0);
    tempi=temp;   

    attachInterrupt(1,det,RISING);//from hall effect sensor
  
  
   
      myGLCD.setFont(SmallFont);
      myGLCD.printNumI(tempi,0,0,2,' ');
      myGLCD.print("C ",14,0);
      myGLCD.setFont(SmallFont);
      myGLCD.print(rtc.formatTime(),35,0);
      myGLCD.setFont(SmallFont);
   // myGLCD.print(days[rtc.getWeekday()],CENTER,40 );
      myGLCD.print(h,4,40);
   // myGLCD.printNumF(diff,2,4,40,'.',6,' ');
      myGLCD.update();
      
        
       if(sp==0)
     {   
      myGLCD.setFont(SmallFont);
      myGLCD.print("Avg.",7,9);
      myGLCD.print("Speed",0,18);
 
      if(dt==0)
      {
       
        myGLCD.setFont(SmallFont);
        myGLCD.print("(m/s)",40,15);
                              
      }
      else
     {
      myGLCD.setFont(SmallFont);
      myGLCD.printNumF(asp,2,40,15,'.',6,' ');
     }
     }
     else
     { 
       myGLCD.setFont(SmallFont);
       myGLCD.print("    ",7,9);
       myGLCD.print("Speed",0,18);
       if(dt==0)
      {
        myGLCD.setFont(SmallFont);
        myGLCD.print("(m/s)",35,10);
       
      }
      else
     {
   
      myGLCD.setFont(SmallFont);
      myGLCD.printNumF(sp,2,40,15,'.',6,' ');
     }
     }
      myGLCD.setFont(SmallFont);
      myGLCD.print("Dist.",2,30);
       if(dt==0)
      {
        myGLCD.setFont(SmallFont);
        myGLCD.print("(km)",40,30);
       
      }
      else 
      { 
      myGLCD.setFont(SmallFont);
      myGLCD.printNumF(distance,2,40,30,'.',6,' ');
      }
      myGLCD.update();
      
  
      if(Serial.available())
      { 
        for(int g=0;g<20;g++)
            {
              myGLCD.clrScr();
              h[g]=(char)0;
            }    
         while(Serial.available())
         { 
           // ch = 1;
          h[m]=Serial.read();
          if(h[m]=='~')
          {
            rad=Serial.read();
            EEPROM.write(0,rad);
          }
          m++;
         }
     
      }
      m=0;
      

 
Serial.println(asp);
Serial.println(distance);
Serial.println(sp); 
//Serial.println(h);
 //distance=(2*3.14*rad*rot)/100000;
 //sp=(2*3.14*rad*10)/(tmd);    
 if((millis()-b)>7000)

        {
          
          sp=0;
          if(b-x!=0)
          asp=(distance*1000000)/(b-x); 
        /*  myGLCD.setFont(SmallFont);
          myGLCD.print("         ",40,15);
          myGLCD.update();*/
         
          
        }
    //   delay(1000);
        }  

      void det()

{
            
              if(u==5)
               {
                x=millis();
               }
               // u++;
               // rot=rot+1;
if (u > 4)
             { 
               rot=rot+1; 
               distance=(2*3.14*rad*rot)/100000; 
              //distance=rot;            
             // d=d+1;
                
                tmd=millis()-b;
                             
                b=millis();
                sp=(2*3.14*rad*10)/(tmd);
               // diff = (b-x)/1000;
              }
              u++;
 // sp=(2*3.14*rad*10)/(tmd);
// sp=1000/(tmd);
  dt = 1;
             }

