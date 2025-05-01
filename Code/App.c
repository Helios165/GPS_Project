#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "UART.h"
#include "LCD.h"
#include "Logic.h"
#include <math.h>
#include <stdbool.h> 
#include <stdio.h>
// Gloabal variables to store the nearest place index and distance
unsigned int min_index = 0;        // Initialize to the first place
double min_distance = 100000000.0f; // Initialize to a large value

int main(void) {
	
		Init_PortF();
		red_led(0);
/*
    // Read GPS data (longitude and latitude)
    float lon = 0.0f; // Replace with actual GPS longitude reading
    float lat = 0.0f; // Replace with actual GPS latitude reading
    find_nearest_place_index(lon, lat);

    // Control LEDs based on distance to the nearest place
    LED_State(min_distance);

    // Update the LCD with the nearest place name
    Update_LCD(min_index);
*/
    return 0;
}