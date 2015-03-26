;; Output Handler
;; Author: Carlos Lemus
;; The input handler checks for a pressed button, and when pressed
;; ignores all other "presses," while updating the "mode" variable.
;; Modes: (1) LEDs off (2) Counter-Clockwise (3) Clockwise
;; Pressed: (0) not pressed (1) pressed

GPIOA	EQU 0x40020000
IDR		EQU 0x10
	
GPIOA_IDR EQU GPIOA + IDR

	AREA INPUT, CODE
	EXPORT input_handler
	IMPORT mode
	IMPORT pressed

input_handler
	LDR r0, =pressed		;r0 = address of "pressed"
	LDR r1, [r0] 			;r1 = status of "pressed"
	CMP r1, #1				;compare "pressed" to 1
	BEQ exit				;if "pressed" is 1 (button is pressed), exit
loop
	LDR r2, =GPIOA_IDR			;r2 = address of GPIOA
	LDR r3, [r2]		;r3 = Input Data Register at GPIOA
	AND r3, r3, #1			;only need bit 1 (for PA0)
	
	CMP r3, #1				;compare input to 1
	BLT exit				;if input is 0 (button isn't pressed), exit
	CMP r1, #1				;compare "pressed" to 1
	BEQ loop				;if "pressed" is 1, continue looping

	;mode variable is set here
	LDR r2, =mode			;r2 = address of "mode"
	LDR r3, [r2]			;r3 = current "mode"
	ADD r3, r3, #1			;increase mode by 1
	CMP r3, #4				;if mode is 4 (>3)
	MOVEQ r3, #1			;then loop back around
	STR r3, [r2]			;store new mode in "mode"

	MOV r1, #1				;r1 = 1
	STR r1, [r0]			;store 1 in pressed
	B loop
exit
	BX r14
	END