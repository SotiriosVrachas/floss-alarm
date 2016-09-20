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

void setup(){
  pinMode(0, INPUT);  //Perimeter Sensors
  pinMode(1, OUTPUT); //Alarm
  pinMode(2, INPUT);  //Keypad
  pinMode(3, INPUT);  //Fire Sensors
  pinMode(4, INPUT);  //Fire Alarm Suspend/Fire Test
}
 
void loop(){
  if(check_arm() == true){
    delay(10000); //Time to arm and leave
    while(check_arm() == true){
      if (detect_breach() == true){
        delay(10000); //Time to enter and disarm
        if(check_arm() == true){
          alert();
        }
      } else if(detect_fire() == true){
        alert();
      }
    }
  }
  
  if(detect_fire() == true){
    fire_alarm();
  }
}
 
void alert(){
  digitalWrite(1, HIGH);
  while(check_arm() == true){
  }
  digitalWrite(1, LOW);
}

void fire_alarm(){
  digitalWrite(1, HIGH);
  while(check_fire_button() == false){
  }
  digitalWrite(1, LOW);
}

boolean detect_breach() {
  if(digitalRead(0) == LOW){
    return 1;
  } else {
    return 0;
  }
}

boolean check_arm(){
  if(digitalRead(2) == HIGH){
    return 1;
  } else {
    return 0;
  }
}

boolean check_fire_button(){
  if(digitalRead(4) == HIGH){
    return 1;
  } else {
    return 0;
  }
}

boolean detect_fire(){
  if(digitalRead(3) == LOW){
    return 1;
  } else {
    return 0;
  }
}
