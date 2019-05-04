#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <MIDI.h>

#include "src/glove.h"
#include "src/config.h"

// declare global glove
Glove *glove;

void setup() {
  // create configuration
  Config *config = new Config(true // debug
                              );

  // instantiate new glove
  glove = new Glove(config);

  // setup glove
  glove->setup();
}

void loop() {
  // read from glove sensors and dispatch values
  glove->read_and_dispatch();
}
