/*  
    floss-alarm.ino - hsgr digispark based alarm prototype
    
    Copyright (C) 2016 Sotirios Vrachas <sotirios@vrachas.com>
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <OneWire.h>
#include "keys.h"
#include "config.h"

boolean g_armed;

OneWire ds(onewire);  // OneWire read pin

void setup(){
  pinMode(intrudersensors, INPUT);  //Perimeter Sensors
  pinMode(sirens, OUTPUT); //Alarm
  pinMode(firesensors, INPUT);  //Fire Sensors
  pinMode(firebutton, INPUT_PULLUP);  //Fire Alarm Suspend/Fire Test
  pinMode(tamper, INPUT);  //Fire Alarm Suspend/Fire Test
}
 
void loop(){
  if(check_arm()){
    delay(exit_delay); //Time to arm and leave
    while(check_arm()){
      if (detect_intruder()){
        delay(entry_delay); //Time to enter and disarm
        if(check_arm()){
          alert(intrudersensors);
        }
      } else if(detect_fire()){
        alert(firesensors);
      }
    }
  } else {
    if(detect_fire()){
      fire_alarm();
    }
  }
}
 
void alert(int zone){
  digitalWrite(sirens, HIGH);
  
  //Send SMS to operators including zone.
  //TODO: Add function with AT Comands loop here 
  
  while(check_arm()){
    delay(100);
  }
  digitalWrite(sirens, LOW);
}

void fire_alarm(){
  digitalWrite(sirens, HIGH);
  while(check_fire_button()){
    delay(100);
  }
  digitalWrite(sirens, LOW);
}

boolean detect_intruder() {
  return (digitalRead(intrudersensors) == LOW);
}

boolean check_arm(){
  int permited = 0;
  byte id[8] = { 0, 0, 0, 0, 0, 0, 0, 0};
  
  if ( !ds.search(id)) {
    ds.reset_search();
    delay(100);
    return g_armed;
  }

  //Go through keys permitted for an ID match
  for(int k = 0; k < BD_size; k++) {
    permited=0;

    //Verify if there is a match
    for(int b = 0; b < 8; b++) {
      if(keys[k][b]==id[b]){
         permited++;
      }
    }
    if(permited==8){
      g_armed = toggle(g_armed); // Arm/Disarm the alarm
      permited=0;
      for(int b = 0; b < 8; b++) {
      id[b]=B0000000;}
      return g_armed; 
    }
    else if(k==BD_size-1) // No match found
      return true; //Wrong key, exit_delay/1000 seconds to leave.
  }
}

boolean check_fire_button(){
  return toggle(digitalRead(firebutton) == LOW);
}

boolean detect_fire(){
    return (digitalRead(firesensors) == HIGH);
}

boolean toggle(boolean x){
    return (!x);
}
