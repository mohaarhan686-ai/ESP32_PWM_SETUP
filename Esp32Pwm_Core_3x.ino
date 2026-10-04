// ================================================================
// ESP32 PWM / LEDC BASIC EXAMPLE
// ================================================================
//
// Is program ka purpose:
// ESP32 ke GPIO 12 pin par hardware PWM generate karna.
//
// PWM = Pulse Width Modulation
//
// PWM ka use generally hota hai:
//   - LED brightness control
//   - DC motor speed control
//   - Servo/actuator control (specific PWM settings ke saath)
//   - Heater/power control
//   - Other devices jahan variable power/control signal chahiye
//
// IMPORTANT:
// Ye ESP32 ke new Arduino-ESP32 API ka syntax use kar raha hai.
//
// New API mein manually LEDC channel define karne ki zarurat
// nahi hoti. `ledcAttach()` pin ko automatically ek available
// LEDC channel ke saath associate kar deta hai.
//
// ================================================================


// ---------------------------------------------------------------
// 1. PWM OUTPUT PIN
// ---------------------------------------------------------------
//
// GPIO 12 ko PWM output ke liye use karenge.
//
// Matlab:
// ESP32 GPIO 12 par PWM signal generate karega.
//
// Agar GPIO 12 se LED connected hai:
//
// GPIO12 ───── LED ───── Resistor ───── GND
//
// to PWM duty cycle change karke LED ki brightness control
// ki ja sakti hai.
//
// Agar motor driver ka PWM/EN pin connected hai, to isi signal
// se motor speed control ki ja sakti hai.
//
// ---------------------------------------------------------------

const int ledPin = 12;


// ---------------------------------------------------------------
// 2. PWM FREQUENCY
// ---------------------------------------------------------------
//
// PWM frequency = 5000 Hz
//
// 5000 Hz ka matlab:
// PWM signal ek second mein 5000 complete cycles karega.
//
// Formula:
//
// Frequency = 1 / Time Period
//
// Therefore:
//
// T = 1 / 5000
// T = 0.0002 second
// T = 200 microseconds
//
// Matlab har PWM cycle approximately 200 µs ka hoga.
//
// Example:
//
//       HIGH       LOW
//        ┌───┐     ┌────────┐
//        │   │     │        │
// ───────┘   └─────┘        └─────
//
// Ek complete HIGH + LOW cycle = 200 µs
//
//
//
// Frequency ka effect:
//
// Higher frequency:
// - PWM switching faster hoti hai
// - LED flicker kam hota hai
// - Motor/driver applications mein useful ho sakti hai
//
// Lower frequency:
// - Switching slower hoti hai
// - Kuch applications mein audible noise aa sakta hai
//
// 5000 Hz = 5 kHz
//
// ---------------------------------------------------------------

const int freq = 5000;


// ---------------------------------------------------------------
// 3. PWM RESOLUTION
// ---------------------------------------------------------------
//
// Resolution = 8 bits
//
// 8-bit resolution ka matlab duty cycle ko:
//
// 0 se 255
//
// tak represent kiya jayega.
//
// Formula:
//
// Maximum value = (2^resolution) - 1
//
// 8-bit:
//
// 2^8 = 256
//
// Values:
//
// 0, 1, 2, 3, ................. 254, 255
//
// Total = 256 possible PWM levels
//
//
//
// Approximate duty-cycle calculation:
//
// Duty Cycle (%) = duty / 255 × 100
//
// Examples:
//
// duty = 0
// → 0%
//
// duty = 64
// → approximately 25%
//
// duty = 128
// → approximately 50%
//
// duty = 192
// → approximately 75%
//
// duty = 255
// → 100%
//
// ---------------------------------------------------------------

const int resolution = 8;


// ================================================================
// SETUP
// ================================================================
//
// setup() sirf ek baar execute hota hai jab:
//
// - ESP32 power ON hota hai
// - Reset hota hai
// - Program upload ke baad restart hota hai
//
// ================================================================

void setup() {

  // -------------------------------------------------------------
  // LEDC PWM ko GPIO 12 par attach/configure karna
  // -------------------------------------------------------------
  //
  // Function:
  //
  // ledcAttach(pin, frequency, resolution);
  //
  // Yahan:
  //
  // pin        = GPIO 12
  // frequency  = 5000 Hz
  // resolution = 8 bits
  //
  // Is function ke baad ESP32 ka LEDC peripheral GPIO 12 par
  // PWM generate karne ke liye configured ho jata hai.
  //
  // IMPORTANT:
  //
  // Purane ESP32 Arduino core versions mein commonly syntax
  // kuch is tarah hota tha:
  //
  // ledcSetup(channel, freq, resolution);
  // ledcAttachPin(pin, channel);
  //
  // Lekin newer Arduino-ESP32 API mein:
  //
  // ledcAttach(pin, freq, resolution);
  //
  // use kiya ja sakta hai.
  //
  // Isliye is code mein channel number manually define nahi
  // kiya gaya hai.
  //
  // ESP32 internally pin ko available LEDC channel se associate
  // karta hai.
  //
  // -------------------------------------------------------------

  ledcAttach(ledPin, freq, resolution);
}


// ================================================================
// LOOP
// ================================================================
//
// loop() continuously repeat hota rahta hai.
//
// Arduino/ESP32 framework internally approximately:
//
// setup()
// ↓
// loop()
// ↓
// loop()
// ↓
// loop()
// ↓
// ...
//
// karta rehta hai.
//
// ================================================================

void loop() {

  // -------------------------------------------------------------
  // GPIO 12 par PWM duty cycle set karna
  // -------------------------------------------------------------
  //
  // Function:
  //
  // ledcWrite(pin, dutyCycle);
  //
  // Yahan:
  //
  // pin        = GPIO 12
  // dutyCycle  = 128
  //
  // Kyunki resolution = 8 bit hai:
  //
  // Minimum duty = 0
  // Maximum duty = 255
  //
  // 128 approximately half of 255 hai.
  //
  // Therefore:
  //
  // 128 / 255 × 100
  // ≈ 50.2%
  //
  // Isliye ye approximately 50% duty cycle generate karega.
  //
  // -------------------------------------------------------------

  ledcWrite(ledPin, 128);

  // -------------------------------------------------------------
  // IMPORTANT:
  //
  // Is line ko baar-baar loop mein execute karne se PWM signal
  // baar-baar start nahi hota.
  //
  // LEDC hardware PWM peripheral automatically signal generate
  // karta rehta hai.
  //
  // CPU ko har HIGH/LOW transition manually control nahi karna
  // padta.
  //
  // ESP32 hardware continuously:
  //
  // HIGH → LOW → HIGH → LOW → ...
  //
  // 5000 times per second generate karta rahega.
  //
  // CPU sirf duty cycle/value set karta hai.
  //
  // -------------------------------------------------------------
}
