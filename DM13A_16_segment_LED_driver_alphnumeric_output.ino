// DM13A 16-segment LED digit driver demo

#define DAI 8  // Serial data input terminal (pin 2 on DM13A)
#define DCK 10 // Synchronous clock input terminal for serial data transfer (pin 3 on DM13A)
#define LAT 11 // Input terminal of data strobe (pin 4 on DM13A)

int buffer[36] = {
  0b0101101100110010, // A
  0b1101101110001001, // B
  0b1000001100100011, // C
  0b1100101110001001, // D
  0b1000001100110011, // E
  0b0000001100110010, // F
  0b1101001100100011, // G
  0b0101100000110010, // H
  0b1000001110001001, // I
  0b1100100000000011, // J
  0b0010010000110010, // K
  0b1000000000100011, // L
  0b0100110001100010, // M
  0b0110100001100010, // N
  0b1100101100100011, // O
  0b0001101100110010, // P
  0b1110101100100011, // Q
  0b0011101100110010, // R
  0b1101001100110001, // S
  0b0000001110001000, // T
  0b1100100000100011, // U
  0b0000010000100110, // V
  0b0110100000100110, // W
  0b0010010001000100, // X
  0b1101100000110001, // Y
  0b1000011100000101, // Z
  0b1100111100100111, // 0
  0b0100110000000000, // 1
  0b1001101100010011, // 2
  0b1101101100000001, // 3
  0b0101100000110000, // 4
  0b1101001100110001, // 5
  0b1101001100110011, // 6
  0b0100101100000000, // 7
  0b1101101100110011, // 8
  0b1101101100110001  // 9
}; // bit patterns for A-Z 0-9.

void setup() 
{
  pinMode(DAI, OUTPUT);
  pinMode(DCK, OUTPUT);
  pinMode(LAT, OUTPUT);
}

void loop() 
{
  for (int i = 0; i < 36; i++) // Loop through all 16 segments
  {
    shiftOut(buffer[i]); // Shift out the 16-bit value
    latch_output();      // Latch the data
    delay(1000);         // Delay for 1 second
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