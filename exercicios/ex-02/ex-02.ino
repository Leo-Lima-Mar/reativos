const int ledPin = 13;
const int btnDesPin = 2;
const int btnAcePin = 3;
const int maxInt = 32727;
const int dt = 5;

int btnDes;
int btnAce;
int ledState = LOW;
int timeRange = 1000; //1s - intervalo de tempo entre mudança de estado do led

unsigned long momentoAtual;
unsigned long momentoAnterior;

unsigned long primeiroClique;
unsigned long segundoClique;
int clickState = 0;
/*
 * 0: não cliquei em ninguém ainda
 * 1: cliquei primeiro no btnDes
 * 2: cliquei primiero no btnAce
 * 3: cliquei nos 2 botões
 */

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(btnDesPin, INPUT);
  pinMode(btnAcePin, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  
  btnDes = digitalRead(btnDesPin);
  if (btnDes) {
    timeRange += timeRange <= maxInt - dt ? dt : 0;
    if (clickState == 0 || clickState == 1) {
      /*  primeira vez que clico no botão
       *  o clickStatus == 1: receta caso o usuário clique no botão 2x.
       */      
      primeiroClique = millis();
      clickState = 1;
    }
    else if (clickState == 2){ //O primeiro botão clicado foi o Ace
      segundoClique = millis();
      clickState = 3;
    }  
  }
  
  btnAce  = digitalRead(btnAcePin);
  if (btnAce) {
    timeRange -= (timeRange >= dt) ? dt : 0;
    if (clickState == 0 || clickState == 2) {
      primeiroClique = millis();
      clickState = 2;
    } else if (clickState == 1){ //O primeiro botão clicado foi o Des
      segundoClique = millis();
      clickState = 3;
    } 
  }

  if (clickState == 3 && segundoClique - primeiroClique <= 500) {
    digitalWrite(ledPin, HIGH);
    Serial.println("fim");
    while(1);
  }
  else {
    clickState = 0;
  }
  
  Serial.println(timeRange);
  
  momentoAtual = millis();
  if (momentoAtual - momentoAnterior > timeRange) {
    ledState = !ledState;
    
    digitalWrite(ledPin, ledState);
    momentoAnterior = momentoAtual;
  }
  
}
