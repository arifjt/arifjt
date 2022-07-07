//===============================================//
// IMPLEMENTASI LPF (LOW PASS FILTER)            //   
// DI ARDUINO, UNTUK FILTER DATA DARI            //
// SENSOR SUHU, AGAR DATA LEBIH HALUS            //
// Diprogram oleh: ARIF JOHAR TAUFIQ             //
//                 (arifjt@gmail.com)            //
//                 www.youtube.com/c/ArifJTaufiq //
// Out dapat dilihat lewat SERIAL MONITOR        //
// Out dapat dilihat lewat SERIAL PLOTTER        //
//===============================================//
float AktualTemp; 
float AktualTemp_1;   
float tempSet;
float Awal;
float tempC1;
float sensorSuhu = A0;   //sensor suhu LM35
int Ts= 10;            //10 mS
void setup()
{ Serial.begin(9600);                       //set baud rate 9600 bps
  pinMode(sensorSuhu, INPUT);
  TCCR2B=(TCCR2B&0xF8) | 2;                 //set PWM frequency to 3906 Hz for pin 3 (and 11)
  float Awal = analogRead(sensorSuhu);         // pancingan awal menyesuaikan suhu awal
  AktualTemp_1 = (5.0 * Awal * 100)/1024;   // konversi teg analog ke suhu Celcius
}
void loop()
{       
    float baca = analogRead(sensorSuhu);      // baca data dari sensor 
    tempC1 = (5.0 * baca * 100)/1024;      // konversi teg analog ke suhu
    
    //=========ini LPF DIGITAL ========================
    AktualTemp=(0.97 * AktualTemp_1) + (0.03 * tempC1);
    //=========ini  END LPF============================
         
    Serial.print(tempC1,1);             //plotter-1
    Serial.print(" ");               //chr jeda   
    Serial.println(AktualTemp,1);    //plotter-2
    AktualTemp_1=AktualTemp;
    delay(Ts); 
}
