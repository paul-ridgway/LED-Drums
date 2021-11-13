/// Arduino MEGA

#include "Trigger.h"
#include "ActiveTrigger.h"
#include <Vector.h> // https://github.com/janelia-arduino/Vector
#include <MIDI.h> // https://github.com/FortySevenEffects/arduino_midi_library

MIDI_CREATE_DEFAULT_INSTANCE();

#define LED 13
#define IDLE_TIME 20000

// RGB LEDs
#define LEDS 149

// Drum note mapping
#define HIHAT_TOP 46
#define HIHAT_TOP_CLOSED 42
#define HIHAT_RIM 26
#define HIHAT_RIM_CLOSED 22
#define HIHAT_PEDAL 44
#define CRASH_TOP 49
#define CRASH_RIM 55
#define RIDE_TOP 51
#define RIDE_RIM 59
#define RIDE_BELL 53
#define SPLASH_TOP 57
#define SPLASH_RIM 52
#define BASS 36
#define SNARE 38
#define SNARE_RIM 37
#define SNARE_RIM2 40
#define TOM1 48
#define TOM1_RIM 50
#define TOM2 45
#define TOM2_RIM 47
#define TOM3 43
#define TOM3_RIM 58
#define TOM4 41
#define TOM4_RIM 39

// Durations
#define SHORT 200
#define MEDIUM 300
#define LONG 400

// Midi state tracking
#define STATE_NONE 0
#define STATE_NOTE_ON 1
#define STATE_NOTE 2
#define MIDI_NOTE_ON 144
#define MIDI_NOTE_OFF 128

// Color buffer
byte color_r[LEDS];
byte color_g[LEDS];
byte color_b[LEDS];

int idleCount = 0;
long lastNoteAt = -IDLE_TIME;
long lastIdleAt = -IDLE_TIME;

const Vector<byte> range(const byte start, const byte end, const byte step) {
  Vector<byte> result;
  byte value = start;
  while (value <= end) {
    result.push_back(value);
    value += step;
  }
  return result;
}

Vector<Trigger*>* triggers[60]; //Note is a byte (could be smarter)

Vector<ActiveTrigger*> activeTriggers;

void setup()
{
  pinMode(LED, OUTPUT);

  MIDI.begin(10);
  Serial1.begin(115200);


  delay(100);
  digitalWrite(13, LOW);

  delay(250);
  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, LOW);
  delay(250);
  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, LOW);

  reset();
  allSet(255, 0, 0);
  writeOut();
  delay(100);
  allSet(0, 255, 0);
  writeOut();
  delay(100);
  allSet(0, 0, 255);
  writeOut();
  delay(100);
  allSet(255, 255, 0);
  writeOut();
  delay(100);
  allSet(255, 0, 255);
  writeOut();
  delay(100);
  allSet(0, 255, 255);
  writeOut();
  delay(100);
  allSet(128, 128, 128);
  writeOut();
  delay(1000);
  reset();

  byte snareLeds[] = {129, 132, 54, 57, 14, 97};
  Vector<byte> snare(snareLeds, sizeof(snareLeds));

  // Configure mapping
  addTrigger(BASS, range(58, 128, 2), 0.1, 0.1, 0.1, SHORT);
  addTrigger(BASS, range(87, 109,  1), 0.0, 1.0, 1.0, MEDIUM);

  addTrigger(SNARE, snare, 1.0, 1.0, 1.0, SHORT);
  addTrigger(SNARE, range(1, 58, 2), 0.1, 0.0, 0.0, 0.4);
  addTrigger(SNARE, range(128, LEDS, 2), 0.1, 0.0, 0.0, 0.4);
  addTrigger(SNARE_RIM, snare, 1.0, 1.0, 0.0, SHORT);
  addTrigger(SNARE_RIM2, snare, 1.0, 0.0, 1.0, SHORT);
  addTrigger(SNARE_RIM, range(1, 58, 2), 0.1, 0.0, 0.0, 0.4);
  addTrigger(SNARE_RIM, range(128, LEDS, 2), 0.1, 0.0, 0.0, 0.4);
  addTrigger(SNARE_RIM2, range(1, 58, 2), 0.1, 0.0, 0.0, 0.4);
  addTrigger(SNARE_RIM2, range(128, LEDS, 2), 0.1, 0.0, 0.0, 0.4);

  Vector<byte> hi_hat_round = range(1, 58, 2);
  const Vector<byte> two = range(128, LEDS, 2);
  for (unsigned int i = 0; i < two.size(); ++i) {
    hi_hat_round.push_back(two[i]);
  }
  addTrigger(HIHAT_RIM, range(132, 143, 1), 0.0, 1.0, 0.5, LONG);
  addTrigger(HIHAT_TOP, range(132, 143, 1), 0.0, 0.5, 1.0, LONG);
  addTrigger(HIHAT_PEDAL, range(132, 143, 1), 0.0, 1.0, 1.0, LONG);
  addTrigger(HIHAT_RIM_CLOSED, range(132, 143, 1), 1.0, 0.5, 0.75, LONG);
  addTrigger(HIHAT_TOP_CLOSED, range(132, 143, 1), 0.5, 1.0, 0.75, LONG);
  addTrigger(HIHAT_RIM, hi_hat_round, 0.0, 0.1, 0.0, LONG);
  addTrigger(HIHAT_TOP, hi_hat_round, 0.0, 0.1, 0.0, LONG);
  addTrigger(HIHAT_PEDAL, hi_hat_round, 0.0, 0.1, 0.0, LONG);
  addTrigger(HIHAT_RIM_CLOSED, hi_hat_round, 0.0, 0.1, 0.0, LONG);
  addTrigger(HIHAT_TOP_CLOSED, hi_hat_round, 0.0, 0.1, 0.0, LONG);
  addTrigger(HIHAT_RIM, range(115, 131, 2), 0.0, 1.0, 0.0, MEDIUM);
  addTrigger(HIHAT_TOP, range(115, 131, 2), 0.0, 1.0, 0.0, MEDIUM);
  addTrigger(HIHAT_PEDAL, range(115, 131, 2), 0.0, 1.0, 0.0, MEDIUM);
  addTrigger(HIHAT_RIM_CLOSED, range(115, 131, 2), 0.0, 1.0, 0.0, MEDIUM);
  addTrigger(HIHAT_TOP_CLOSED, range(115, 131, 2), 0.0, 1.0, 0.0, MEDIUM);

  addTrigger(CRASH_TOP, range(0, 3, 1), 0.5, 1.0, 0.0, LONG);
  addTrigger(CRASH_TOP, range(143, LEDS, 1), 0.5, 1.0, 0.0, LONG);
  addTrigger(CRASH_RIM, range(0, 3, 1), 1.0, 0.5, 0.0, LONG);
  addTrigger(CRASH_RIM, range(143, LEDS, 1), 1.0, 0.5, 0.0, LONG);
  addTrigger(CRASH_TOP, range(107, 122, 2) , 1.0, 0.0, 0.0, MEDIUM);
  addTrigger(CRASH_RIM, range(107, 122, 2) , 1.0, 0.0, 0.0, MEDIUM);


  addTrigger(TOM1, range(1, 15, 1), 0.0, 1.0, 0.0, LONG);
  addTrigger(TOM1_RIM, range(1, 15, 1), 1.0, 0.0, 1.0, LONG);
  addTrigger(TOM2, range(12, 27, 1), 0.0, 0.0, 1.0, LONG);
  addTrigger(TOM2_RIM, range(12, 27, 1), 1.0, 1.0, 0.0, LONG);

  addTrigger(RIDE_TOP, range(22, 35, 1), 0.0, 0.3, 1.0, LONG);
  addTrigger(RIDE_BELL, range(22, 35, 1), 1.0, 0.3, 0.0, LONG);
  addTrigger(RIDE_RIM, range(22, 35, 1), 0.3, 1.0, 0.0, LONG);

  addTrigger(RIDE_TOP, range(71, 91, 2), 0.0, 0.0, 1.0, MEDIUM);
  addTrigger(RIDE_BELL, range(71, 91, 2), 0.0, 0.0, 1.0, MEDIUM);
  addTrigger(RIDE_RIM, range(71, 91, 2), 0.0, 0.0, 1.0, MEDIUM);

  addTrigger(TOM3, range(27, 45, 1), 1.0, 0.0, 1.0, LONG);
  addTrigger(TOM3_RIM, range(27, 45, 1), 0.0, 1.0, 0.0, LONG);

  addTrigger(SPLASH_TOP, range(43, 46, 1), 1.0, 0.5, 0.0, LONG);
  addTrigger(SPLASH_RIM, range(43, 46, 1), 0.5, 1.0, 0.0, LONG);

  addTrigger(SPLASH_TOP, range(57, 73, 2), 0.0, 1.0, 0.0, MEDIUM);
  addTrigger(SPLASH_RIM, range(57, 73, 2), 0.0, 1.0, 0.0, MEDIUM);

  addTrigger(TOM4, range(45, 67, 1), 0.0, 1.0, 1.0, LONG);
  addTrigger(TOM4_RIM, range(45, 67, 1), 1.0, 0.0, 0.0, LONG);

}

void loop()
{
  const unsigned long now = millis();
  digitalWrite(13, ((now / 100) % 2) ? HIGH : LOW);

  allSet(0, 0, 0);
  for (unsigned int i = 0; i < activeTriggers.size(); ++i) {
    const ActiveTrigger* activeTrigger = activeTriggers[i];
    const Trigger* t = activeTrigger->getTrigger();
    const int r = activeTrigger->r();
    const int g = activeTrigger->g();
    const int b = activeTrigger->b();
    const byte* leds = t->leds();
    for (byte i = 0; i < t->ledCount(); ++i) {
      const byte j = leds[i];
      color_r[j] = clamp((r + color_r[j]), 0, 255);
      color_g[j] = clamp((g + color_g[j]), 0, 255);
      color_b[j] = clamp((b + color_b[j]), 0, 255);
    }
    if (!activeTrigger->decay(millis())) {
      activeTriggers.remove(i);
      delete activeTrigger;
    }
    handleMidi();  //Midi doesnt like external delays, seems to drop data
  }
  const long idleTime = now - lastNoteAt;
  if (idleTime > IDLE_TIME) {
    idleSequence(now);
  }

  writeOut();

  const unsigned long start = millis();
  while (millis() - start < 5) {
    handleMidi();
  }
}

void idleSequence(const unsigned long now) {
  if ((now - lastIdleAt) > 300) {
    lastIdleAt = now;
    if (idleCount == 0) {
      handleNote(BASS, 1.0f);
    } else if (idleCount == 1) {
      handleNote(SNARE, 1.0f);
    } else if (idleCount == 2) {
      handleNote(TOM1, 1.0f);
    } else if (idleCount == 3) {
      handleNote(TOM2, 1.0f);
    }
    ++idleCount;
    if (idleCount >= 6) {
      idleCount = 0;
    }
  }
}

void writeOut() {
  Serial1.write((byte)255); //Start
  Serial1.write((byte)254); //Set
  Serial1.write((byte)LEDS); //Length
  for (int i = 0; i < LEDS; ++i) {
    Serial1.write(color_r[i]);
    Serial1.write(color_g[i]);
    Serial1.write(color_b[i]);
    handleMidi();  //Midi doesnt like external delays, seems to drop data
  }
  Serial1.flush();
  //waitFor(254, 1000);
}

bool waitFor(const byte target, const unsigned long timeout) {
  const unsigned long start = millis();
  do {
    if (Serial1.available() && (Serial1.read() == target)) {
      return true;
    }
  } while ((millis - start) < timeout);
  return false;
}

void handleMidi() {
  //WRITEUP: Explain why basic midi loop did not work for close timing
  while (MIDI.read())                // Is there a MIDI message incoming ?
  {
    switch (MIDI.getType())     // Get the type of the message we caught
    {
      case midi::NoteOn:
        lastNoteAt = millis();
        {
          const float force = ((float)MIDI.getData2()) / 127.0f; //Max velocity from drums
          handleNote(MIDI.getData1(), force);
        }
        break;
      default:
        break;
    }
  }

}

void handleNote(const byte note, const float force) {
  Vector<Trigger*>* trigs = triggers[note];
  if (trigs) {
    for (Vector<Trigger*>::iterator it = trigs->begin(); it != trigs->end(); ++it) {
      activeTriggers.push_back(new ActiveTrigger(*it, force, millis()));
    }
  }
}

void addTrigger(const byte note, const Vector<byte> leds, const float r, const float g, const float b, const int d) {
  if (!triggers[note]) {
    triggers[note] = new Vector<Trigger*>();
  }
  triggers[note]->push_back(new Trigger(leds, r, g, b, d));
}

void reset() {
  bool on;
  do {
    digitalWrite(13, (on = !on) ? HIGH : LOW);
    Serial1.write(255); //Start
    Serial1.write(253); //Reset
    Serial1.flush();
  } while (!waitFor(253, 50)); // Reset confirm
}

void allSet(const byte r, const byte g, const byte b) {
  memset(color_r, r, sizeof(color_r));
  memset(color_g, g, sizeof(color_g));
  memset(color_b, b, sizeof(color_b));
}

const int clamp(const int value, const int min, const int max) {
  if (value < min) {
    return min;
  } else if (value > max) {
    return max;
  }
  return value;
}
