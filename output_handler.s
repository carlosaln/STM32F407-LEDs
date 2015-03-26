;; Output Handler
;; Author: Carlos Lemus
;; MOdified output handler only provides functions to turn
;; LEDs on and off

GPIOD EQU 0x40020C00
BSRRL EQU 0x18
BSRRH EQU 0x1A

GPIOD_BSSRL EQU GPIOD + BSRRL
GPIOD_BSSRH EQU GPIOD + BSRRH

    AREA OUTPUT, CODE
    EXPORT led_on
	EXPORT led_off

led_on MOV r2, #1				; r2 = 1
	MOV r2, r2, LSL r0			; place at argument given by bit
	LDR r3, =GPIOD_BSSRL		; load address of output pin
	STR r2, [r3]				; write to output pin

	BX r14						; return

led_off MOV r2, #1				; r2 = 1
	MOV r2, r2, LSL r0			; place at argument given by bit
	LDR r3, =GPIOD_BSSRH		; load address of output pin
	STR r2, [r3]				; write to output pin

	BX r14						; return

	END