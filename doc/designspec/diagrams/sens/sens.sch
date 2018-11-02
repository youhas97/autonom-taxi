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
L sens-rescue:ACS715xLCTR-30A-taxi HALLEFFEKTSENSOR
U 1 1 5BC4BC08
P 9250 4500
F 0 "HALLEFFEKTSENSOR" H 9250 5000 50  0000 C CNN
F 1 "A112X/A3240" H 9250 4900 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9350 4150 50  0001 L CIN
F 3 "http://www.allegromicro.com/~/media/Files/Datasheets/ACS715-Datasheet.ashx?la=en" H 9250 4500 50  0001 C CNN
	1    9250 4500
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5BC4BEF7
P 7000 800
F 0 "#PWR?" H 7000 650 50  0001 C CNN
F 1 "+5V" V 7000 1000 50  0000 C CNN
F 2 "" H 7000 800 50  0001 C CNN
F 3 "" H 7000 800 50  0001 C CNN
	1    7000 800 
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 5BC4BFE6
P 5600 5850
F 0 "#PWR?" H 5600 5600 50  0001 C CNN
F 1 "Earth" H 5600 5700 50  0001 C CNN
F 2 "" H 5600 5850 50  0001 C CNN
F 3 "~" H 5600 5850 50  0001 C CNN
	1    5600 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 4350 8850 4350
$Comp
L Interface_Optical:QSE159 AVSTÅNDSMÄTARE(SIDA)
U 1 1 5BC4D282
P 8900 1450
F 0 "AVSTÅNDSMÄTARE(SIDA)" H 8638 1496 50  0000 R CNN
F 1 "GP2D120" H 8638 1405 50  0000 R CNN
F 2 "OptoDevice:ONSemi_QSE15x" H 8900 1050 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QSE159-D.pdf" H 9550 1750 50  0001 C CNN
	1    8900 1450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8600 1450 6200 1450
$Comp
L Interface_Optical:QSE159 AVSTÅNDSMÄTARE(FRAM)
U 1 1 5BC4D9A0
P 8900 2350
F 0 "AVSTÅNDSMÄTARE(FRAM)" H 8638 2396 50  0000 R CNN
F 1 "GP2Y0A02YK" H 8638 2305 50  0000 R CNN
F 2 "OptoDevice:ONSemi_QSE15x" H 8900 1950 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/QSE159-D.pdf" H 9550 2650 50  0001 C CNN
	1    8900 2350
	-1   0    0    -1  
$EndComp
$Comp
L sens-rescue:ACS715xLCTR-30A-taxi REFLEXSENSOR
U 1 1 5BC4DCED
P 8950 3450
F 0 "REFLEXSENSOR" H 8950 3950 50  0000 C CNN
F 1 "?" H 8950 3850 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9050 3100 50  0001 L CIN
F 3 "http://www.allegromicro.com/~/media/Files/Datasheets/ACS715-Datasheet.ashx?la=en" H 8950 3450 50  0001 C CNN
	1    8950 3450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8550 3300 7800 3300
Wire Wire Line
	8600 2350 8250 2350
Wire Wire Line
	8250 2350 8250 1650
Wire Wire Line
	8250 1650 6200 1650
Wire Wire Line
	7800 1950 6200 1950
Wire Wire Line
	7800 1950 7800 3300
$Comp
L Connector:AVR-JTAG-10 JTAG
U 1 1 5BC4E425
P 7100 3550
F 0 "JTAG" H 6721 3596 50  0000 R CNN
F 1 "AVR-JTAG-10" H 6721 3505 50  0000 R CNN
F 2 "" V 6950 3700 50  0001 C CNN
F 3 " ~" H 5825 3000 50  0001 C CNN
	1    7100 3550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8200 5850 8200 4500
Wire Wire Line
	8200 4500 8850 4500
Wire Wire Line
	8200 4500 8200 3450
Wire Wire Line
	8200 3450 8550 3450
Connection ~ 8200 4500
Wire Wire Line
	8200 3450 8200 2650
Wire Wire Line
	8200 2650 8800 2650
Connection ~ 8200 3450
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
Wire Wire Line
	8450 2050 8450 3600
Wire Wire Line
	8450 3600 8550 3600
Connection ~ 8450 2050
Wire Wire Line
	8450 3600 8450 4650
Wire Wire Line
	8450 4650 8850 4650
Connection ~ 8450 3600
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
Wire Wire Line
	7200 2950 7200 1050
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
Connection ~ 7100 5850
Wire Wire Line
	7100 5850 8200 5850
$Comp
L MCU_Microchip_ATmega:ATmega1284-PU U?
U 1 1 5BDC69D9
P 5600 3150
F 0 "U?" H 5600 1064 50  0000 C CNN
F 1 "ATmega1284-PU" H 5600 973 50  0000 C CNN
F 2 "Package_DIP:DIP-40_W15.24mm" H 5600 3150 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8272-8-bit-AVR-microcontroller-ATmega164A_PA-324A_PA-644A_PA-1284_P_datasheet.pdf" H 5600 3150 50  0001 C CNN
	1    5600 3150
	1    0    0    -1  
$EndComp
$Comp
L exo3:IQEXO-3 U?
U 1 1 5BDCCBF2
P 3150 2400
F 0 "U?" V 3196 2070 50  0000 R CNN
F 1 "IQEXO-3" V 3105 2070 50  0000 R CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 3200 1650 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/NB3N511-D.PDF" H 3200 1550 50  0001 C CNN
	1    3150 2400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5600 5850 3350 5850
Wire Wire Line
	3350 5850 3350 2800
Wire Wire Line
	2850 2000 2850 1050
Wire Wire Line
	2850 1050 5600 1050
Connection ~ 5600 1050
$EndSCHEMATC
