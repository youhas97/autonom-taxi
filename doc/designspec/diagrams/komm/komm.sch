EESchema Schematic File Version 4
LIBS:komm-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Kommunikationsmodul"
Date "2018-10-16"
Rev "v0.1"
Comp ""
Comment1 "Raspberry pi connected to I2C bus via a level shifter"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Raspberry_Pi_2_3 J?
U 1 1 5BC49E7D
P 2000 3450
F 0 "J?" H 2000 5100 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" H 2000 5000 50  0000 C CNN
F 2 "" H 2000 3450 50  0001 C CNN
F 3 "https://www.raspberrypi.org/documentation/hardware/raspberrypi/schematics/rpi_SCH_3bplus_1p0_reduced.pdf" H 2000 3450 50  0001 C CNN
	1    2000 3450
	1    0    0    -1  
$EndComp
$Comp
L Logic_LevelTranslator:BSS138_bidirectional_level_shifter levelshifter?
U 1 1 5BC4E4B2
P 4650 3400
F 0 "levelshifter?" H 4650 4300 50  0001 C CIN
F 1 "BSS138_bidirectional_level_shifter" H 4596 4076 50  0000 C CNN
F 2 "adafruit_i2c_level_shifter" H 4800 2350 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/txb0104.pdf" H 4760 3495 50  0001 C CNN
	1    4650 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 2850 3900 2850
Wire Wire Line
	3900 2850 3900 3100
Wire Wire Line
	3900 3100 4250 3100
Wire Wire Line
	2800 2950 3700 2950
Wire Wire Line
	3700 2950 3700 3300
Wire Wire Line
	3700 3300 4250 3300
Text Notes 5100 3100 0    50   ~ 0
I2C SDA\n
Text Notes 5100 3300 0    50   ~ 0
I2C SCL
Wire Wire Line
	4250 2950 3950 2950
Wire Wire Line
	3950 2950 3950 2750
Wire Wire Line
	3950 2750 3100 2750
Wire Wire Line
	3100 2750 3100 2150
Wire Wire Line
	3100 2150 2200 2150
Wire Wire Line
	1800 2150 1550 2150
Wire Wire Line
	1550 2150 1550 2000
Wire Wire Line
	1550 2000 5500 2000
Wire Wire Line
	5500 2000 5500 2950
Wire Wire Line
	5500 2950 5050 2950
Wire Wire Line
	4650 4100 4650 4800
Wire Wire Line
	4650 4800 2300 4800
Wire Wire Line
	2300 4800 2300 4750
Text Notes 1950 4150 1    50   ~ 0
CAMERA \nPORT\n
$EndSCHEMATC
