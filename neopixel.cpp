#include "hwlib.hpp"
#include "sam.h"
#include "neopixel.hpp"

void neo_leds::write_0(){
    port.PIO_SODR = 0x01 << pin;
    asm volatile("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"
            "nop; nop; nop; nop; nop; nop; nop; nop;nop; nop; nop; nop; nop; "
            "nop; nop; nop; nop; nop; nop; nop; nop;"); //0.4 us
    port.PIO_CODR = 0x01 << pin;
    asm volatile("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; "
            "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; "
            "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; "
            "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; "
            "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; "
            "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; "
            "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"); //0.85 us
}
    
void neo_leds::write_1(){
    port.PIO_SODR = 0x01 << pin;
    asm volatile( "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; "
            "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; "
            "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; "
            "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; "
            "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; "
            "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"
            "nop; nop; nop; nop; nop;"); //0.8 us
    port.PIO_CODR = 0x01 << pin;
    asm volatile( "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; "
            "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; "
            "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; "
            "nop; nop;"); // 0.85 us
}
    
    
void neo_leds::setup_leds(){
    WDT->WDT_MR = WDT_MR_WDDIS;
    port.PIO_OER = 0x01 << pin;
    port.PIO_CODR = 0x01 << pin;
    for(int i = 0; i < led_amount; i++){
        led_values[i][0] = 0;
        led_values[i][1] = 0;
        led_values[i][2] = 0;
    }
}
    
void neo_leds::set_green(int led, uint8_t green){
    led_values[led-1][1] = green;
}
    
void neo_leds::set_red(int led, uint8_t red){
    led_values[led-1][0] = red;
}
    
void neo_leds::set_blue(int led, uint8_t blue){
    led_values[led-1][2] = blue;
}
    
    
void neo_leds::set_all_leds(uint8_t red, uint8_t green, uint8_t blue){
    for(int i = 0; i < led_amount; i++){
        led_values[i][0] = red;
        led_values[i][1] = green;
        led_values[i][2] = blue;
    }
}

void neo_leds::set_all_leds(int collors[3]){
    for(int i = 0; i < led_amount; i++){
        led_values[i][0] = collors[0];
        led_values[i][1] = collors[1];
        led_values[i][2] = collors[2];
    }
}
    
void neo_leds::set_amount_leds(int amount, uint8_t red, uint8_t green, uint8_t blue){
    for(int i = 0; i < amount; i++){
        led_values[i][0] = red;
        led_values[i][1] = green;
        led_values[i][2] = blue;
    }
    for(int i = amount; i < led_amount; i++){
        led_values[i][0] = 0;
        led_values[i][1] = 0;
        led_values[i][2] = 0;
    }
}
    
    
void neo_leds::set_amount_leds(int amount, int collors[3]){
    for(int i = 0; i < amount; i++){
        led_values[i][0] = collors[0];
        led_values[i][1] = collors[1];
        led_values[i][2] = collors[2];
    }
    for(int i = amount; i < led_amount; i++){
        led_values[i][0] = 0;
        led_values[i][1] = 0;
        led_values[i][2] = 0;
    }
}
    

void neo_leds::shift_back(){
    int temp[3];
    temp[0] = led_values[0][0];
    temp[1] = led_values[0][1];
    temp[2] = led_values[0][2];
    for(int i = 0; i < led_amount-2; i++){
        led_values[i][0] = led_values[i+1][0];
        led_values[i][1] = led_values[i+1][1];
        led_values[i][2] = led_values[i+1][2];
    }
    led_values[led_amount -1][0] = temp[0];
    led_values[led_amount -1][1] = temp[1];
    led_values[led_amount -1][2] = temp[2];
}
    

void neo_leds::shift_in(uint8_t red, uint8_t green, uint8_t blue){
    for(volatile int i = led_amount-1; i >0; i--){
        led_values[i][0] = led_values[i-1][0];
        led_values[i][1] = led_values[i-1][1];
        led_values[i][2] = led_values[i-1][2];
    }
    led_values[0][0] = red;
    led_values[0][1] = green;
    led_values[0][2] = blue;
}

    
void neo_leds::flush(){
    for(int i = 0; i < led_amount; i++){
        for(int j = 0; j < 3; j++){
            for(int y = 7; y >= 0; y--){
                if(uint8_t(led_values[i][j]) & (1 << y)){
                    write_1();
                }else{
                    write_0();
                }
            }
        }
    }
    hwlib::wait_us(100);
}
