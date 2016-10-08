#define onewire 0 // OneWire read pin
#define intrudersensors 1 //Perimeter Sensors  pin
#define sirens 2 //Alarm pin
#define firesensors 3 //Fire Sensors pin
#define firebutton 4 //Fire Alarm Suspend/Fire Test pin
#define tamper 6 //Tampering Sensores pin

#define exit_delay 10000 //Time to arm and leave
#define entry_delay 10000 //Time to enter and disarm

#define zones_size 6  //number of zones

// in this matrix configure the zones
// pin, mode, safevalue, delay1, delay2, armedonly, admin
static int zones[zones_size][7] = {
  {4, INPUT_PULLUP, 0, 0, 0, 0, 0},
  {6, INPUT, 1, 0, 0, 0, 1},
  {3, INPUT, 1, 0, 0, 0, 0},
  {2, OUTPUT, 0, 0, 0, 0, 0},
  {1, INPUT, 0, 10000, 10000, 1, 0}
};

static int char zone_names[zones_size][0] = {
  {"fire but"},
  {"tamper zone"},
  {"fire zone"},
  {"siren"},
  {"perimeter"}
};
