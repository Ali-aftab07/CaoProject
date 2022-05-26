int det1=12;
int det2=13;
int buzz=25;
int led1=21;
int arr[]={4,2};
void setup(){
  Serial.begin(9600);
  pinMode(det1,INPUT);
  pinMode(det2,INPUT);
  pinMode(buzz,OUTPUT);
  pinMode(led1,OUTPUT);
  for(int i=0;i<2;i++){
    pinMode(arr[i],OUTPUT);
  }
}
void loop(){
  int out1=digitalRead(det1);
  int out2=digitalRead(det2);
  Serial.println(out1);
  Serial.println(out2);
  for(int i=0;i<2;i++){
    digitalWrite(arr[i],OUTPUT);
  }
  if(out1==LOW || out2==LOW){
    for(int i=0;i<10;i++){
     digitalWrite(led1,HIGH);
    digitalWrite(buzz,HIGH);
    delay(500);
    digitalWrite(led1,LOW);
    digitalWrite(buzz,LOW);
    delay(500);
    }
  }
  else{
    digitalWrite(buzz,LOW);
  }
}
