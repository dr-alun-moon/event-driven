#include "mbed.h"
#include "C12832.h"

#include <stdio.h>

enum { On, Off };

/* for mbed pin names see
 *     https://os.mbed.com/teams/Freescale/wiki/frdm-k64f-pinnames
 */   
DigitalOut red(LED_RED,Off);
DigitalOut green(LED_GREEN,Off);
DigitalOut blue(LED_BLUE,Off);

InterruptIn left(SW2);

/* for Application shield pins see 
 *     https://os.mbed.com/teams/Freescale/wiki/frdm-k64f-pinnames
 */
DigitalOut s_red(D5,Off);
DigitalOut s_green(D9,Off);
DigitalOut s_blue(D8,Off);

Ticker pit;

EventQueue queue;


void ledon(DigitalOut p)
{
	p = On;
}

void ledoff(DigitalOut p)
{
	p = Off;
}

Event<void(DigitalOut)>  on(&queue, ledon);
Event<void(DigitalOut)> off(&queue, ledoff);

int main()
{
	DigitalOut indicator(LED_BLUE);
	on.delay(0);
	on.period(2000);
	on.post(red);

	off.delay(200);
	off.period(2000);
	off.post(red);

	on.delay(200);
	on.post(green);
	off.delay(400);
	off.post(green);

	on.delay(400);
	on.post(indicator);
	off.delay(600);
	off.post(indicator);

	queue.dispatch_forever();
}

