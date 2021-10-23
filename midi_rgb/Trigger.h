#pragma once

#include "ArduinoSTL.h"

class Trigger {
  public:
    //TODO: Store in array not vector
    Trigger(const std::vector<byte> leds, const float r, const float g, const float b, const int decay) : 
    r_(r),
    g_(g),
    b_(b),
    decay_(decay) {
      ledCount_ = leds.size();
      leds_ = malloc(ledCount_);
      std::copy(leds.begin(), leds.end(), leds_);      
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
