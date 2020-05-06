#define potentiometer  A0

#define echopin A2 // echo pin
#define trigpin A3 // Trigger pin

int read_ADC =0;
long set_time =0;
long rememTime;

long dis_cm;
long ultra_time;
int set_cm = 80;

int relay = 2; // Out for light 

int flag=0;

void setup(){
Serial.begin(9600);// initialize serial communication at 9600 bits per second:

pinMode(potentiometer, INPUT);

pinMode (trigpin, OUTPUT);
pinMode (echopin, INPUT);

pinMode(relay, OUTPUT); 

delay(1000); // Waiting for a while
}

void loop(){ 
//*************************
ultra_read();
//*************************

read_ADC = analogRead(potentiometer);
set_time = map(read_ADC, 0, 1023, 1000, 20000);

Serial.print("Dis :");Serial.println(dis_cm); 
Serial.print("Time:");Serial.println(set_time); 


if(dis_cm<set_cm && flag==0){flag=1; 
digitalWrite(relay,HIGH);
Serial.println("Relay On");
rememTime = millis();
}

if(dis_cm>set_cm){flag=0;}

if((millis()- rememTime) > set_time){   
digitalWrite(relay,LOW);
Serial.println("Relay Off");
}
delay(100); 
}

//**********************ultra_read****************************
void ultra_read(){
digitalWrite(trigpin, LOW);
delayMicroseconds(2);
digitalWrite(trigpin, HIGH);
delayMicroseconds(10);
ultra_time = pulseIn (echopin, HIGH);
dis_cm =  ultra_time / 29 / 2; 
}
