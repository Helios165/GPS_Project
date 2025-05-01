#ifndef LOGIC_H
#define LOGIC_H
#include <stdbool.h>  

// from radians to degrees
float to_radians(float degrees);

// calculate the distance between two points on the earth
double calc_distance(float lon1, float lat1, float lon2, float lat2);

// find the nearest landmark and the index of it
void find_nearest_place_index(float lon, float lat);

//  Function to control LEDS based on distance    
void LED_State(double min_distance);

//  Function to update the LCD with the nearest place
void Update_LCD(unsigned int min_index);

#endif