/*
 * Medições
 * Tamanho de v   Tempo (microssegundos)
 *          100                   64460
 *          200                  128904
 *          300                  193364
 *          400                  257812
 *          500                  322264
 *          600                  386712
 *          700                  451156
 *          800                  515604
 *          900                  580056
 *         1000                  644504
 *         1100                  708956
 *         1200                  773412
 */

#include "xtea.c.h"
 
#define LED 13
#define btn_pin 2

int btn; 

uint32_t key[] = { 1, 2, 3, 4 };
const int TAM_V = 1200; 
uint32_t v[TAM_V];

int i, led = 0;

void setup () {
    pinMode(LED, OUTPUT);
    pinMode(btn_pin, INPUT);

    for (i = 0; i < TAM_V; i++) {
      v[i] = i * 10000;
    }

    Serial.begin(9600);
}
 
void loop () {

    static unsigned long t1 = micros();
    
    for (i = 0; i < TAM_V; i = i+2) {
        if (digitalRead(btn_pin) ) {
          digitalWrite(LED, HIGH);
          while(1);
        }
        encipher(32, &v[i], key);
        decipher(32, &v[i], key);
    }

    digitalWrite(LED, led=!led);

    static unsigned long t2 = micros();
    Serial.println(t2-t1);
    
}
