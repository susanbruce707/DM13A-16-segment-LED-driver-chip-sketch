// DM13A 16-segment LED digit driver demo
// Author Susan Amber Bruce 27/4/2025.

#define DAI 8  // Serial data input terminal (pin 2 on DM13A)
#define DCK 10 // Synchronous clock input terminal for serial data transfer (pin 3 on DM13A)
#define LAT 11 // Input terminal of data strobe (pin 4 on DM13A)

int buffer[16] = {0b0000000000000001, 0b0000000000000010, 0b0000000000000100, 
                  0b0000000000001000, 0b0000000000010000, 0b0000000000100000, 
                  0b0000000001000000, 0b0000000010000000, 0b0000000100000000, 
                  0b0000001000000000, 0b0000010000000000, 0b0000100000000000, 
                  0b0001000000000000, 0b0010000000000000, 0b0100000000000000, 
                  0b1000000000000000}; // Example bit patterns for 16 segments

void setup() 
{
  Serial.begin(9600);
  pinMode(DAI, OUTPUT);
  pinMode(DCK, OUTPUT);
  pinMode(LAT, OUTPUT);
  
  digitalWrite(DAI, LOW);
  digitalWrite(DCK, LOW);
  digitalWrite(LAT, LOW);
}

void loop() 
{
  for (int i = 0; i < 16; i++) // Loop through all 16 segments
  {
    shiftOut(buffer[i]); // Shift out the 16-bit value
    latch_output();      // Latch the data
    delay(500);         // Delay for 1/2 second
  }
}

void shiftOut(int data) // Function to shift out 16 bits
{
  for (int j = 0; j < 16; j++) // Loop through all 16 bits
  {
    int bit = (data >> j) & 0x01; // Extract the j-th bit
    digitalWrite(DAI, bit);       // Write the bit to DAI
    digitalWrite(DCK, HIGH);      // Clock pulse
    digitalWrite(DCK, LOW);
  }
}

void latch_output() // Push latch pulse to LAT pin to latch the output data
{
  digitalWrite(LAT, HIGH);
  digitalWrite(LAT, LOW);
}