#makefile configuration
CPU		= msp430g2553
CFLAGS		= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/

#switch the compiler (for the internal make rules)
CC 		= msp430-elf-gcc
AS		= msp430-elf-gcc -mmcu=${CPU} -c

all:gameDemo-c.elf gameDemo-s.elf 

gameDemo-c.elf: ${COMMON_OBJECTS} gameDemo.o wdt_handler.o switch_interrupt_handler-c.o switch_update_interrupt_sense-c.o buzzer.o switch-c.o
		${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load-c: gameDemo-c.elf
	msp430loader.sh $^

gameDemo-s.elf: ${COMMON_OBJECTS} gameDemo.o wdt_handler.o switch_interrupt_handler-s.o switch_update_interrupt_sense-s.o buzzer.o switch-s.o
		${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load-s: gameDemo-s.elf
	msp430loader.sh $^


clean:
	rm -f *.o *.elf *~ *#
