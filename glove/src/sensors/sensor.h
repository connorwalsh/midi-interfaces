#ifndef SENSOR_BASE_H_
#define SENSOR_BASE_H_

#include <Arduino.h>
#include <MIDI.h>


namespace sensor {

  // midi dispatcher function type
  // typedef void (*MidiDispatcher)(midi::MidiInterface<HardwareSerial>*);

  // typedef void (Sensor::*MidiDispatcher)();

  // default midi dispatcher
  // void default_midi_dispatcher(midi::MidiInterface<HardwareSerial>* m);

  // range_t defines a one-dimensional value range.
  struct range_t {
    int min;
    int max;
  };

  struct discontinuous_range_t {
    range_t lower;
    range_t upper;
  };

  enum calibration_t {CalibrateUpperBound, CalibrateLowerBound};
  
  class Sensor {
  public:
    Sensor(midi::MidiInterface<HardwareSerial>* midi_interface,
           range_t input_range,
           range_t output_range,
           bool invert_values,
           bool debug)
      : input_range(input_range),
        output_range(output_range),
        invert_values(invert_values),
        midi_interface(midi_interface),
        debug(debug)
    {}

    range_t input_range;
    range_t output_range;
    bool invert_values;
    int debounce_threshold = 3;
    midi::MidiInterface<HardwareSerial>* midi_interface;
    bool debug;

  protected:
    bool debounce(int current_value);

    int running_average[2] = {0, 0};
  };

}

#endif
