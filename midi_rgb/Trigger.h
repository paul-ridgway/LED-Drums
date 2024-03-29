#pragma once
#include <Vector.h> // https://github.com/janelia-arduino/Vector

class Trigger {
  public:
    //TODO: Store in array not vector
    Trigger(const Vector<byte> leds, const float r, const float g, const float b, const int decay) : 
    r_(r),
    g_(g),
    b_(b),
    decay_(decay) {
      ledCount_ = leds.size();
      leds_ = malloc(ledCount_);
      for(unsigned int i = 0; i < ledCount_; ++i) {
        leds_[i] = leds[0];
      }
    }

    const float r() {
      return r_;
    }
    const float g() {
      return g_;
    }
    const float b() {
      return b_;
    }
    const int decay() {
      return decay_;
    }
    const byte* leds() {
      return leds_;
    }
    const int ledCount() {
      return ledCount_;
    }
  private:
    const float r_, g_, b_;
    const int decay_;
    byte* leds_;
    int ledCount_;
};
