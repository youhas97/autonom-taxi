EESchema Schematic File Version 4
LIBS:styr-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Styrmodul"
Date "2018-10-09"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:AVR-JTAG-10 J?
U 1 1 5BBCAF71
P 5050 3550
F 0 "J?" H 4670 3596 50  0000 R CNN
F 1 "AVR-JTAG-10" H 4670 3505 50  0000 R CNN
F 2 "" V 4900 3700 50  0001 C CNN
F 3 " ~" H 3775 3000 50  0001 C CNN
	1    5050 3550
	-1   0    0    -1  
$EndComp
$Comp
L MCU_Microchip_ATmega:ATmega1284P-PU U?
U 1 1 5BEA84E2
P 2850 3150
F 0 "U?" H 2850 1064 50  0000 C CNN
F 1 "ATmega1284P-PU" H 2850 973 50  0000 C CNN
F 2 "Package_DIP:DIP-40_W15.24mm" H 2850 3150 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8272-8-bit-AVR-microcontroller-ATmega164A_PA-324A_PA-644A_PA-1284_P_datasheet.pdf" H 2850 3150 50  0001 C CNN
	1    2850 3150
	1    0    0    -1  
$EndComp
$Comp
L exo3:IQEXO-3 U?
U 1 1 5BEB103D
P 1350 2150
F 0 "U?" H 1350 2717 50  0000 C CNN
F 1 "IQEXO-3" H 1350 2626 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 1400 1400 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/NB3N511-D.PDF" H 1400 1300 50  0001 C CNN
	1    1350 2150
	0    1    -1   0   
$EndComp
$Comp
L jma162a:JMA162A _?
U 1 1 5BEB1179
P 4800 6000
F 0 "_?" V 4600 5650 50  0001 C CNN
F 1 "JMA162A" H 4800 5425 50  0000 C CNN
F 2 "Display_7Segment:DA04-11SYKWA" V 5975 5975 50  0001 C CNN
F 3 "http://www.kingbright.com/attachments/file/psearch/000/00/00/DA04-11SYKWA(Ver.6A).pdf" V 4600 6420 50  0001 C CNN
	1    4800 6000
	0    1    -1   0   
$EndComp
$Comp
L Analog_Switch:ADG419BN U?
U 1 1 5BEB1382
P 1950 1250
F 0 "U?" H 1950 1492 50  0000 C CNN
F 1 "ADG419BN" H 1950 1401 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 1950 950 50  0001 C CNN
F 3 "http://www.analog.com/media/en/technical-documentation/data-sheets/ADG419.pdf" H 1950 1050 50  0001 C CNN
	1    1950 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 1750 1150 900 
Wire Wire Line
	1150 900  2850 900 
Wire Wire Line
	2850 900  2850 1150
Wire Wire Line
	1650 2550 2100 2550
Wire Wire Line
	2100 2550 2100 1650
Wire Wire Line
	2100 1650 2250 1650
Wire Wire Line
	1150 5150 2850 5150
Connection ~ 2850 900 
Wire Wire Line
	2850 900  5050 900 
Wire Wire Line
	5050 900  7600 900 
Connection ~ 5050 900 
Wire Wire Line
	4450 5300 4100 5300
Wire Wire Line
	4100 5300 4100 3950
Wire Wire Line
	4100 3950 3450 3950
Wire Wire Line
	4550 5300 4550 4850
Wire Wire Line
	4550 4850 3450 4850
Wire Wire Line
	4650 5300 4650 4750
Wire Wire Line
	4650 4750 3450 4750
Wire Wire Line
	4750 5300 4750 4650
Wire Wire Line
	4750 4650 3450 4650
Wire Wire Line
	3450 4550 4850 4550
Wire Wire Line
	4850 4550 4850 5300
Wire Wire Line
	3450 4450 4950 4450
Wire Wire Line
	4950 4450 4950 5300
Wire Wire Line
	5050 5300 5050 4350
Wire Wire Line
	5050 4350 3450 4350
Wire Wire Line
	3450 4250 5150 4250
Wire Wire Line
	5150 4250 5150 5300
Wire Wire Line
	5250 5300 5250 4200
Wire Wire Line
	5400 6250 7600 6250
Wire Wire Line
	7600 900  7600 6250
Wire Wire Line
	4450 6700 5850 6700
Wire Wire Line
	2850 5150 2850 6700
Wire Wire Line
	2850 6700 4450 6700
Connection ~ 2850 5150
Connection ~ 4450 6700
Wire Wire Line
	4550 3750 3450 3750
Wire Wire Line
	2950 1150 5150 1150
Wire Wire Line
	1150 2500 1150 5150
Wire Wire Line
	3450 3650 4550 3650
Wire Wire Line
	3450 3550 4550 3550
Wire Wire Line
	3450 3450 4550 3450
Wire Wire Line
	4950 4150 4950 4200
Wire Wire Line
	4950 4200 5250 4200
Wire Wire Line
	3450 4150 4950 4150
Wire Wire Line
	5850 4150 5850 6700
Wire Wire Line
	5050 4150 5850 4150
Wire Wire Line
	5050 900  5050 2950
Wire Wire Line
	5150 1150 5150 2950
Wire Wire Line
	3450 3050 4150 3050
Wire Wire Line
	3450 2950 4150 2950
Wire Wire Line
	3450 2850 4150 2850
Wire Wire Line
	3450 2750 4150 2750
Text Label 4150 3050 0    50   ~ 0
SPI_CLK
Text Label 4150 2950 0    50   ~ 0
MISO
Text Label 4150 2850 0    50   ~ 0
MOSI
Text Label 4150 2750 0    50   ~ 0
CHIP_SELECT
Wire Wire Line
	3450 2650 4150 2650
Wire Wire Line
	3450 2550 4150 2550
Text Label 4150 2650 0    50   ~ 0
PWM_MOTOR
Text Label 4150 2550 0    50   ~ 0
PWM_SVÄNG
$EndSCHEMATC
