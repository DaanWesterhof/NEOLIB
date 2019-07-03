///////////////////////////////////////////////////////////////
//          Copyright Daan Westerhof 2019.                   //
// Distributed under the Boost Software License, Version 1.0.//
//    (See accompanying file LICENSE_1_0.txt or copy at      //
//          https://www.boost.org/LICENSE_1_0.txt)           //
///////////////////////////////////////////////////////////////

#ifndef NEOLIB
#define NEOLIB

#include "hwlib.hpp"
#include "sam.h"

/**
 * @class neo_leds
 * @author Daan
 * @date 01/07/19
 * @file neopixel.hpp
 * @brief neo_leds
 * This class controlls neopixel leds on a arduino due over a one wire interface.
 */

class neo_leds{
protected:
    int pin;
    Pio & port;
    uint8_t led_values[64][3];
    int led_amount; 
                                
        /**
         * @brief  write 0
         * 
         * writes a 0 to the leds over the connected wire
         */
    void write_0();
    
        /**
         * @brief  write 1
         * 
         * writes a 1 to the leds over the connected wire
         */
    void write_1();
    
    
public:
        /**
         * @brief neo_leds
         * The constructor of the class
         * @param pin a hwlib::pin_in wich is used to determine the pin register and the coresponding bit.
         * @param led_amount the amount of leds on the used ledstrip or amount of neopixel leds taht are put in series
         */
    neo_leds(hwlib::target::pins pin, int led_amount) : pin((hwlib::target::pin_info(pin).pin)),
 port(hwlib::target::port_registers((hwlib::target::pin_info(pin).port))), led_amount(led_amount) {}
                        
                        
        /**
         * @brief setup leds
         * 
         * setup the leds for use, (initialize all leds at 0,0,0 and enable the used pin for output)
         */
    void setup_leds();
    
    
        /**
         * @brief set green
         * 
         * set the given leds value of green
         * @param led the led to be changed
         * @param green the green color value 0->255
         */
    void set_green(int led, uint8_t green);
    
        /**
         * @brief set red
         * 
         * set the given leds value of red
         * @param led the led to be changed
         * @param red the red color value 0->255
         */
    void set_red(int led, uint8_t red);
    
        /**
         * @brief set blue
         * 
         * set the given leds value of blue
         * @param led the led to be changed
         * @param blue the blue color value 0->255
         */
    void set_blue(int led, uint8_t blue);
    
    
    /**
     * @brief set all leds
     * 
     * set all leds to the given values per color
     * @param red red color value
     * @param green green color value
     * @param blue blue color value
     */
    void set_all_leds(uint8_t red, uint8_t green, uint8_t blue);
    
    /**
     * @brief set all leds
     * sets all leds to the colors provided
     * @param collors an array of color values wich should be in the order of red, green, blue
     */

    void set_all_leds(int collors[3]);
    
    
    /**
     * @brief set amount leds
     * 
     * set the given amount of leds to the given values per color, others will be turned off
     * @param amount the amount of leds
     * @param red red color value
     * @param green green color value
     * @param blue blue color value
     */
    void set_amount_leds(int amount, uint8_t red, uint8_t green, uint8_t blue);
    
    
        /**
         * @brief set amount leds
         * 
         * set the given amount of leds to the color values of the given array
         * @param amount amount of leds to change color
         * @param collors array of color values in the order of red, green, blue
         */
    void set_amount_leds(int amount, int collors[3]);
    
        /**
         * @brief shift back
         * 
         * shift all leds one place counter clockwise
         */
    void shift_back();
    
        /**
         * @brief shift in
         * 
         * Shift all leds one place clockwise and set the first led to the given color values
         * @param red red color value
         * @param green green color value
         * @param blue blue color value
         */
    
    void shift_in(uint8_t red, uint8_t green, uint8_t blue);

    
        /**
         * @brief flush
         * 
         * This function writes the values to the actual leds,
         * this is to be called each time you change a leds color.
         */
    void flush();
};// End of class neo_leds

#endif //NEOLIB