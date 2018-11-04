EESchema Schematic File Version 4
LIBS:sens-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Sensormodul"
Date "2018-10-15"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L sens-rescue:ACS715xLCTR-30A-taxi-sens-rescue AVSTÅNDSMÄTARE(FRAM)
U 1 1 5BC4BC08
P 8900 2350
F 0 "AVSTÅNDSMÄTARE(FRAM)" H 8200 2450 50  0000 C CNN
F 1 "GP2Y0A02YK" H 8250 2350 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9000 2000 50  0001 L CIN
F 3 "http://www.allegromicro.com/~/media/Files/Datasheets/ACS715-Datasheet.ashx?la=en" H 8900 2350 50  0001 C CNN
	1    8900 2350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8600 1450 6200 1450
Wire Wire Line
	8600 2350 8250 2350
Wire Wire Line
	8250 2350 8250 1650
Wire Wire Line
	8250 1650 6200 1650
Wire Wire Line
	8200 2650 8800 2650
Wire Wire Line
	8200 2650 8200 1750
Wire Wire Line
	8200 1750 8800 1750
Connection ~ 8200 2650
Wire Wire Line
	5600 5150 5600 5850
Wire Wire Line
	8800 1050 8800 1150
Wire Wire Line
	8450 1050 8450 2050
Wire Wire Line
	8450 2050 8800 2050
Connection ~ 8450 1050
Wire Wire Line
	8450 1050 8800 1050
Connection ~ 8450 2050
Wire Wire Line
	5700 1050 5700 1150
Wire Wire Line
	5700 1050 7000 1050
Wire Wire Line
	5700 1050 5600 1050
Wire Wire Line
	5600 1050 5600 1150
Connection ~ 5700 1050
Wire Wire Line
	5600 5850 7100 5850
Connection ~ 5600 5850
Wire Wire Line
	7000 800  7000 1050
Connection ~ 7000 1050
Wire Wire Line
	7000 1050 7100 1050
Wire Wire Line
	6200 3650 6600 3650
Wire Wire Line
	6200 3550 6600 3550
Wire Wire Line
	6200 3450 6600 3450
Wire Wire Line
	6600 3750 6200 3750
Connection ~ 7200 1050
Wire Wire Line
	7200 1050 8450 1050
Wire Wire Line
	7100 2950 7100 1050
Connection ~ 7100 1050
Wire Wire Line
	7100 1050 7200 1050
Wire Wire Line
	7100 4150 7100 5850
$Comp
L sens-rescue:IQEXO-3-exo3 KRISTALLOSCILLATOR
U 1 1 5BDCCBF2
P 3550 2400
F 0 "KRISTALLOSCILLATOR" V 3596 2070 50  0000 R CNN
F 1 "IQEXO-3" V 3505 2070 50  0000 R CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 3600 1650 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/NB3N511-D.PDF" H 3600 1550 50  0001 C CNN
	1    3550 2400
	0    1    -1   0   
$EndComp
Wire Wire Line
	3850 2000 3850 1050
Connection ~ 5600 1050
$Comp
L sens-rescue:ATmega1284-PU-MCU_Microchip_ATmega U?
U 1 1 5BDC5F4E
P 5600 3150
F 0 "U?" H 5600 1064 50  0000 C CNN
F 1 "ATmega1284-PU" H 5600 973 50  0000 C CNN
F 2 "Package_DIP:DIP-40_W15.24mm" H 5600 3150 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8272-8-bit-AVR-microcontroller-ATmega164A_PA-324A_PA-644A_PA-1284_P_datasheet.pdf" H 5600 3150 50  0001 C CNN
	1    5600 3150
	1    0    0    -1  
$EndComp
$Comp
L sens-rescue:ACS715xLCTR-30A-taxi-sens-rescue AVSTÅNDSMÄTARE(SIDA)
U 1 1 5BDC9DEC
P 8900 1450
F 0 "AVSTÅNDSMÄTARE(SIDA)" H 8250 1550 50  0000 C CNN
F 1 "GP2D120" H 8300 1450 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9000 1100 50  0001 L CIN
F 3 "http://www.allegromicro.com/~/media/Files/Datasheets/ACS715-Datasheet.ashx?la=en" H 8900 1450 50  0001 C CNN
	1    8900 1450
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5BDC9F18
P 7000 800
F 0 "#PWR?" H 7000 650 50  0001 C CNN
F 1 "+5V" H 7015 973 50  0000 C CNN
F 2 "" H 7000 800 50  0001 C CNN
F 3 "" H 7000 800 50  0001 C CNN
	1    7000 800 
	1    0    0    -1  
$EndComp
$Comp
L sens-rescue:A112X-hall-effect HALLEFFECTSENSOR
U 1 1 5BDCB7F9
P 8900 3650
F 0 "HALLEFFECTSENSOR" H 9129 3696 50  0000 L CNN
F 1 "A112X" H 9129 3605 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8900 3300 50  0001 L CIN
F 3 "http://www.allegromicro.com/en/Products/Part_Numbers/1101/1101.pdf" H 8900 4300 50  0001 C CNN
	1    8900 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR?
U 1 1 5BDCBACA
P 5600 5850
F 0 "#PWR?" H 5600 5600 50  0001 C CNN
F 1 "GNDREF" H 5605 5677 50  0000 C CNN
F 2 "" H 5600 5850 50  0001 C CNN
F 3 "" H 5600 5850 50  0001 C CNN
	1    5600 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 1050 5600 1050
Wire Wire Line
	3850 2800 4200 2800
Wire Wire Line
	4200 2800 4200 1650
Wire Wire Line
	4200 1650 5000 1650
$Comp
L jma162a:JMA162A _?
U 1 1 5BDF0219
P 8100 5100
F 0 "_?" H 8100 5050 50  0001 C CNN
F 1 "JMA162A" H 8100 4525 50  0000 C CNN
F 2 "Display_7Segment:DA04-11SYKWA" V 9275 5075 50  0001 C CNN
F 3 "http://www.kingbright.com/attachments/file/psearch/000/00/00/DA04-11SYKWA(Ver.6A).pdf" H 7980 4700 50  0001 C CNN
	1    8100 5100
	-1   0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR?
U 1 1 5BDF121A
P 3350 2800
F 0 "#PWR?" H 3350 2550 50  0001 C CNN
F 1 "GNDREF" H 3355 2627 50  0000 C CNN
F 2 "" H 3350 2800 50  0001 C CNN
F 3 "" H 3350 2800 50  0001 C CNN
	1    3350 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR?
U 1 1 5BDF1A61
P 8800 5450
F 0 "#PWR?" H 8800 5200 50  0001 C CNN
F 1 "GNDREF" H 8805 5277 50  0000 C CNN
F 2 "" H 8800 5450 50  0001 C CNN
F 3 "" H 8800 5450 50  0001 C CNN
	1    8800 5450
	0    -1   -1   0   
$EndComp
Connection ~ 3850 1050
Wire Wire Line
	3850 1050 2050 1050
Text Label 6200 2750 0    50   ~ 0
SS_Slave_Select
Text Label 6200 2850 0    50   ~ 0
MOSI
Text Label 6200 2950 0    50   ~ 0
MISO
Text Label 6200 3050 0    50   ~ 0
SPI_SCK
$Comp
L Connector:AVR-JTAG-10 J?
U 1 1 5BDC62E7
P 7100 3550
F 0 "J?" H 6721 3596 50  0000 R CNN
F 1 "AVR-JTAG-10" H 6721 3505 50  0000 R CNN
F 2 "" V 6950 3700 50  0001 C CNN
F 3 " ~" H 5825 3000 50  0001 C CNN
	1    7100 3550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7200 2950 7200 1050
Wire Wire Line
	6200 2750 6850 2750
Wire Wire Line
	6200 2850 6850 2850
Wire Wire Line
	6200 2950 6850 2950
Wire Wire Line
	6200 3050 6850 3050
Wire Wire Line
	8200 2650 8200 3650
Wire Wire Line
	8450 2050 8450 3800
Wire Wire Line
	8600 3800 8450 3800
Wire Wire Line
	8600 3650 8200 3650
Wire Wire Line
	7100 5850 9100 5850
Wire Wire Line
	9100 5850 9100 4000
Wire Wire Line
	9100 4000 8200 4000
Wire Wire Line
	8200 4000 8200 3650
Connection ~ 7100 5850
Connection ~ 8200 3650
Wire Wire Line
	8350 4550 8350 4500
Wire Wire Line
	8350 3800 8450 3800
Connection ~ 8350 4500
Wire Wire Line
	8350 4500 8350 3800
Connection ~ 8450 3800
Wire Wire Line
	7400 4650 7400 4150
Wire Wire Line
	6200 4150 7400 4150
Wire Wire Line
	7400 4750 7250 4750
Wire Wire Line
	7250 4750 7250 4250
Wire Wire Line
	7250 4250 6200 4250
Wire Wire Line
	7400 4850 7150 4850
Wire Wire Line
	7150 4850 7150 4350
Wire Wire Line
	6200 4350 7150 4350
Wire Wire Line
	7400 4950 7050 4950
Wire Wire Line
	7050 4950 7050 4450
Wire Wire Line
	7050 4450 6200 4450
Wire Wire Line
	7400 5050 6950 5050
Wire Wire Line
	6950 5050 6950 4550
Wire Wire Line
	6950 4550 6200 4550
Wire Wire Line
	6200 4650 6900 4650
Wire Wire Line
	6900 4650 6900 5150
Wire Wire Line
	6900 5150 7400 5150
Wire Wire Line
	7400 5250 6800 5250
Wire Wire Line
	6800 5250 6800 4750
Wire Wire Line
	6800 4750 6200 4750
Wire Wire Line
	6200 4850 6700 4850
Wire Wire Line
	6700 4850 6700 5350
Wire Wire Line
	6700 5350 7400 5350
Wire Wire Line
	7400 5450 6500 5450
Wire Wire Line
	6500 5450 6500 3950
Wire Wire Line
	6500 3950 6200 3950
$Comp
L Analog_Switch:ADG419BN U?
U 1 1 5BE987B7
P 2650 1450
F 0 "U?" H 2650 1692 50  0000 C CNN
F 1 "ADG419BN" H 2650 1601 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 2650 1150 50  0001 C CNN
F 3 "http://www.analog.com/media/en/technical-documentation/data-sheets/ADG419.pdf" H 2650 1250 50  0001 C CNN
	1    2650 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 1450 5000 1450
$EndSCHEMATC
