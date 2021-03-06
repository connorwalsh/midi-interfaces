#ifndef FLEX_SENSOR_H_
#define FLEX_SENSOR_H_

#include <Arduino.h>
#include "sensor.h"


namespace sensor {

  class Flex : public sensor::Sensor {
  public:

    enum class DispatcherType {Debug, Weirdo, MidiControlChange};

    Flex(byte pin,
         midi::MidiInterface<HardwareSerial>* midi_interface,
         DispatcherType dispatcher_type=DispatcherType::MidiControlChange,
         sensor::range_t input_range={0, 127},
         sensor::range_t output_range={0, 127},
         bool invert_values=true,
         bool debug=false)
      : pin(pin),
        sensor::Sensor(midi_interface,
                       input_range,
                       output_range,
                       invert_values,
                       debug)
    {
      dispatchers[static_cast<int>(DispatcherType::Debug)] = &Flex::debug_dispatcher;
      dispatchers[static_cast<int>(DispatcherType::Weirdo)] = &Flex::weird_dispatcher;
      dispatchers[static_cast<int>(DispatcherType::MidiControlChange)] = &Flex::midi_cc_dispatcher;

      if (debug) {
        dispatcher_type = DispatcherType::Debug;
      }
      this->set_dispatcher(dispatcher_type);
    };
    void calibrate(sensor::calibration_t calibration_bound);
    void set_midi_cc_number(byte cc_number) { midi_cc_number = cc_number; }
    void set_dispatcher(DispatcherType type) { dispatcher = dispatchers[static_cast<int>(type)]; }
    void read(bool do_transform=true);
    void send();

    typedef void (Flex::*Dispatcher)();
    Dispatcher dispatchers[2];
    Dispatcher dispatcher;
    
    byte pin;
    int v = 0;
    
  private:
    int transform(int value);

    /* dispatchers */
    void debug_dispatcher();
    void weird_dispatcher();
    void midi_cc_dispatcher();

    byte midi_channel = 1;
    byte midi_cc_number = 1;
  };
  
}

#endif
