void kaannos_oikeaan(void); // DEF
void kaannos_vasempaan(void);
void aja_eteenpain(void);
void aja_taakse(void);
void seis(void);

void mittaus(void);        // HC SR 04 UltraSonic Distance Sensor
void tulostus(void);
void seis(void);

const int trigPin = 2;    // PINS used for Arduino UNO
const int echoPin = 3;
const int GNDPin = 11;
const int VccPin = 12;

int etaisyys = 0;
long kesto = 0;
char t;                    


void setup() {
  pinMode(5, OUTPUT);     //ENA
  pinMode(6, OUTPUT);     //ENB
  pinMode(7, OUTPUT);     // input 1 R Front
  pinMode(8, OUTPUT);     // input 2 R Back
  pinMode(9, OUTPUT);     // input 3 L Front 
  pinMode(10, OUTPUT);    // input 4 L Back 

  pinMode(trigPin, OUTPUT);   //UltraSonic HC SR 04 Setup
  pinMode(echoPin, INPUT);
  pinMode(GNDPin, OUTPUT);
  pinMode(VccPin, OUTPUT);
  digitalWrite(VccPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(GNDPin, LOW);
  delayMicroseconds(2);

  Serial.begin(9600);     // Sync HC05 Bluetooth Module
}

void loop() {
  if (Serial.available()) {    //Read Serial Monitor
    t = Serial.read();         
    Serial.println(t);
    if (t == '6') {
      kaannos_oikeaan();      // Command Right
    }
    if (t == '4') {
      kaannos_vasempaan();    // Command Left
    }
    if (t == '2') {
      aja_eteenpain();        // Command Forward
    }
    if ( t == '8') {
      aja_taakse();           // Command Back
    }
    if (t == '5') {
      seis();                 // Command Stop
    }
  }
   digitalWrite(trigPin, LOW);
  delay(10);
  
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  
}

void kaannos_oikeaan(void)  // Drive Right
{
  digitalWrite(5, HIGH);    //  Stop
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH); 
 
}

void kaannos_vasempaan(void) // Drive Left
{
  digitalWrite(6, HIGH);     
  digitalWrite(5, HIGH);    //  Stop
  digitalWrite(9, HIGH); 

}

void aja_eteenpain(void)     // Drive Forward
{
  mittaus();
  if(etaisyys <= 20) {      // 20 cm danger zone
  digitalWrite(5, LOW);     // Stop if obsticle in way
  digitalWrite(7, LOW); 
  digitalWrite(6, LOW); 
  digitalWrite(9, LOW); 
  }
  else {
  digitalWrite(5, HIGH);    
  digitalWrite(7, HIGH);    
  digitalWrite(6, HIGH); 
  digitalWrite(9, HIGH); 
  } 
}
void aja_taakse(void)       // Drive Back
{

  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH); 
  digitalWrite(8, HIGH); 
  digitalWrite(10, HIGH); 
}
void seis(void)           // STOP
{
  digitalWrite(7, LOW);   
  digitalWrite(8, LOW);   
  digitalWrite(9, LOW);   
  digitalWrite(10, LOW);
}
void mittaus(void)        // Distance (cm)
{
   kesto = pulseIn(echoPin, HIGH);
  etaisyys = kesto*0.034/ 2;
}
void tulostus(void)      // Print Distance
{
  Serial.print("etaisyys: ");
  Serial.println(etaisyys);
}
