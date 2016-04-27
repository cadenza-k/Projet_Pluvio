int led = 3;
int bp = 2;
boolean state = true;

void setup() {

pinMode(led, OUTPUT);
}

void loop() {
if (digitalRead (bp) == HIGH) {

     if (state == false) {
digitalWrite (led, HIGH); 
}      
else {
digitalWrite (led, LOW);
}
state = !state;
delay (200);
}  
}
