#define btn1 16
#define led_y 12
int btn_count = 0; // Counter for button presses
boolean value = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(btn1, INPUT);
  pinMode(led_y, OUTPUT);
}

void loop()
{
  boolean btn1_val = digitalRead(btn1);
  if(btn1_val == 0) // If button is pressed
  {
    delay(10);  // 10ms delay for debouncing
    while(btn1_val == 0) // Loop until button is released
    {
      btn1_val = digitalRead(btn1);
      if(btn1_val == 1)  // If button is released
      {
        btn_count++;    // Increment press counter
        Serial.println(btn_count);
      }
    }
    value = !value;
    if(value == 1)
    {
      digitalWrite(led_y, HIGH); // Turn LED on
    }
    else
    {
      digitalWrite(led_y, LOW); // Turn LED off
    }
  }
}