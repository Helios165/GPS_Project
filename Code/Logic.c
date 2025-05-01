#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "LCD.h"
#include <math.h>
#include "GPIO.h"
#define EARTH_RADIUS_KM 6378.0
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

//  Constant places configurations (change with actual values)
const float place_longitudes[5] = {30.0, 30.1, 30.2, 30.3, 30.4};
const float place_latitudes[5]  = {31.0, 31.1, 31.2, 31.3, 31.4};

//decleration of global values
extern unsigned int min_index;
extern double min_distance;

//  Landmarks names (subject to change)
//  The names are stored in a 2D array, where each row represents a place name. (auto sized)
 unsigned char place_names[5][7] = {
    "CREDIT",
    "HALL A",
    "MOSQUE",
    "LIBRARY",
    "CIVIL"
    // Add more places as needed
};
// Landmarks names lengths (adjust as per the names above)
const unsigned int place_name_lengths[5] = {6, 6, 6, 7, 5};


//  Function to convert degrees to radians
float to_radians(float degrees) {         
    return degrees * (3.14159265f / 180.0f);
}



//  Haversine formula to calculate the distance between two points on the earth
double calc_distance(float lon1, float lat1, float lon2, float lat2) {  
    float dlat = to_radians(abs(lat2 - lat1));  // Absolute Difference in Latitudes
    float dlon = to_radians(abs(lon2 - lon1));  // Absolute Difference in Longitudes

    float a = sinf(dlat / 2.0f) * sinf(dlat / 2.0f) +              //sin^2(dlat/2)
              cosf(to_radians(lat1)) * cosf(to_radians(lat2)) *    //cos(lat1)*cos(lat2)
              sinf(dlon / 2.0f) * sinf(dlon / 2.0f);               //sin^2(dlon/2)
                 
    double c = 2.0f * atanf(sqrtf(a) / sqrtf(1.0f - a));
    return EARTH_RADIUS_KM * c;
}



//  Find Nearest Landmark and the Index of it
void find_nearest_place_index(float lon, float lat) {
    double d;
	  unsigned int i;
    // loop through all Landmarks to find the nearest one
    for(i = 0; i < ARRAY_SIZE(place_longitudes); i++){  
        d = calc_distance(lon, lat, place_longitudes[i], place_latitudes[i]);
        if (d < min_distance) {
            min_distance = d;
            min_index = i;
        }
    }
}

//  Function to control LEDS based on distance
void LED_State(double min_distance) {
    double upp_threshold = 50.0f; // Upper threshold for distance
    double low_threshold = 10.0f;  // Lower threshold for distance
    Init_PortF(); // Initialize Port F for LED control
    // If the distance is less than 10m turn on the green LED
    if (min_distance<low_threshold) 
    {
        red_led(0); 
        blue_led(0);
        green_led(1); 
    }
    // If the distance is between 10m AND 50m turn of the blue LED
    else if (min_distance<upp_threshold && min_distance >= low_threshold) 
    {
        red_led(0); 
        blue_led(1);
        green_led(0); 
    }
    // If the distance is greater than 50m turn on the red LED (worst case)
    else 
    {
        red_led(1); 
        blue_led(0);
        green_led(0);
    }
}

//  Display on LCD 
void Update_LCD(min_index) {
    Init_PortB(); // Initialize Port B for LCD data pins
    Init_PortC(); // Initialize Port C for LCD data pins
    Init_PortD(); // Initialize Port D for LCD control pins
  //  LCD_int(); // Initialize the LCD 
	//  LCD_string(place_names[min_index][sizeof(place_name_lengths[min_index])], 
	//	sizeof(place_names[min_index][sizeof(place_name_lengths[min_index])])-1); // calls LCD_string function to display
}