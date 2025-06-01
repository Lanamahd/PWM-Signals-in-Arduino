#define PWM_PIN 9  // OC1A - Timer1 PWM Output

int duty = 0; // Initial duty cycle percentage

void setup() {
  pinMode(PWM_PIN, OUTPUT);
  
  Serial.begin(9600); 

  // Stop Timer1
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // Set Fast PWM mode using ICR1 as TOP (Mode 14)
  TCCR1A |= (1 << COM1A1);
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM13) | (1 << WGM12);

  ICR1 = 1999; // 1 kHz
  OCR1A = (duty * ICR1) / 100;

  TCCR1B |= (1 << CS11);  // Prescaler = 8
}


void loop() {
  // Increase duty cycle
  for (duty = 0; duty <= 100; duty += 10) {
    OCR1A = (duty * ICR1) / 100;
    
    // Log to Serial Monitor
    Serial.print("Increasing - Duty Cycle: ");
    Serial.println(duty);

    delay(1000);
  }

  // Decrease duty cycle
  for (duty = 100; duty >= 0; duty -= 10) {
    OCR1A = (duty * ICR1) / 100;

    // Log to Serial Monitor
    Serial.print("Decreasing - Duty Cycle: ");
    Serial.println(duty);

    delay(1000);
  }
}

