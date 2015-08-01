This is my first code for ARduino fridge controller.
It uses Arduino, DS18B20 temperature sensor, OLED display 0.9", relay and potentiometer.

DS18B20 sense temperature every 1 second, decide it it is higher than set temperature by potentiometer (+- hysteresis), and after turn on/off relay. also on OLEd display shows actual temperature and wanted temp.
