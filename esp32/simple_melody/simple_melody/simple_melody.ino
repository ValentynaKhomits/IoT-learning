#define NOTE_C 554
#define NOTE_D 587
#define NOTE_E 659
#define NOTE_F 740
#define NOTE_G 830
#define NOTE_A 880
#define NOTE_B 988

int melody[] = { NOTE_F, NOTE_F, NOTE_F, NOTE_E,
NOTE_F, NOTE_F, NOTE_F, NOTE_F, NOTE_G, NOTE_E };
int noteDurations[] = { 4, 8, 4, 4, 4, 8, 8, 4, 4, 4};
const int buzzerPin = 25;
void setup() { pinMode(buzzerPin, OUTPUT); }
void loop() { 
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    int noteFrequency = melody[i];
    int noteDuration = 2000 / noteDurations[i];
    tone(buzzerPin, noteFrequency, noteDuration);
    int pauseBetweenNotes = noteDuration * 1.3;
    delay(pauseBetweenNotes); 
  }
  delay(1000); 
}