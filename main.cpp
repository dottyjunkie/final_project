#include "mbed.h"
#include "bbcar.h"

Thread thread_main;
Thread xbee_thread(osPriorityHigh);

EventQueue xbee_queue(32 * EVENTS_EVENT_SIZE);
EventQueue send_queue(32 * EVENTS_EVENT_SIZE);

Ticker servo_ticker;
Ticker encoder_ticker;
Ticker encoder_ticker2;

PwmOut pin8(D8), pin9(D9);
DigitalIn pin3(D3);
DigitalIn pin4(D4);

DigitalInOut pin10(D10);

parallax_encoder encoder0(pin3, encoder_ticker); 
parallax_encoder encoder1(pin4, encoder_ticker2);                     
parallax_ping  ping1(pin10);


Serial uart(D1,D0); 
RawSerial pc(USBTX, USBRX);
RawSerial xbee(D12, D11);
BBCar car(pin8, pin9, servo_ticker);

///////
char buf=[];
void right(){
    encoder0.reset();
    encoder1.reset();
    car.turn(100,-0.2);
    while(encoder0.get_cm()<20){
        wait(0.01);
    }
    car.stop();
}
void left(){
    encoder0.reset();
    encoder1.reset();
    car.turn(100,0.2);
    while(encoder1.get_cm()<20){
        wait(0.01);
    }
    car.stop();
}
void send_status{
    xbee.printf("%s",buff);
}

void walk_len_stop (float length){
    car.goStraight(150);
    while(1){
        if((float)ping1<length){
            car.stop();
            break;
        }
        wait(.01);
    }   
}

void send_status(){
    while(1) {
        if(uart.readable()){
            char recv = uart.getc();
            if(!flag){
                buff=recv;
                xbee.printf("buff %c",buff);
                break;
            }                         
      }
   }
}
int main() {

    encoder0.reset();
    encoder1.reset();

    uart.baud(9600);
    xbee.baud(9600);
    pc.baud(9600);

    thread_main.start(callback(&sendqueue, &EventQueue::dispatch_forever));
    xbee_thread.start(callback(&xbeequeue, &EventQueue::dispatch_forever));

    send_queue.call(send_thread);
    xbee_queue.call_every(1000,send_status);

    /////////////////////////
    walk_len_stop(30);
    left();
    walk_len_stop(45);
    left();
    walk_len_stop(50);
    left();
    left();
    walk_len_stop(50);
    right();
    walk_len_stop(40);
    right();
    ////////////////////////
    walk_len_stop(30);
    right();
    walk_len_stop(50);
    right();
    walk_len_stop(30);
    right();
    right();
    walk_len_stop(30);
    walk_len_stop(10);
    car.stop();
}