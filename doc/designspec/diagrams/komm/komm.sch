EESchema Schematic File Version 4
LIBS:komm-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Kommunikationsmodul"
Date "2018-11-06"
Rev "v0.1"
Comp ""
Comment1 "Raspberry pi connected to SPI bus via two level shifter"
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
	1800 2150 1550 2150
Wire Wire Line
	1550 2150 1550 2000
Wire Wire Line
	1550 2000 5500 2000
Wire Wire Line
	5500 2000 5500 2950
Wire Wire Line
	5500 2950 5050 2950
Text Notes 1950 4150 1    50   ~ 0
CAMERA \nPORT\n
$Comp
L Logic_LevelTranslator:BSS138_bidirectional_level_shifter levelshifter?
U 1 1 5BE9F7E8
P 4650 4800
F 0 "levelshifter?" H 4650 5700 50  0001 C CIN
F 1 "BSS138_bidirectional_level_shifter" H 4596 5476 50  0000 C CNN
F 2 "adafruit_i2c_level_shifter" H 4800 3750 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/txb0104.pdf" H 4760 4895 50  0001 C CNN
	1    4650 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 4750 2200 5500
Wire Wire Line
	2200 5500 4650 5500
Wire Wire Line
	2300 5350 4150 5350
Wire Wire Line
	4150 5350 4150 4100
Wire Wire Line
	4150 4100 4650 4100
Wire Wire Line
	2300 4750 2300 5350
Wire Wire Line
	2800 3550 2950 3550
Wire Wire Line
	2950 3550 2950 3100
Wire Wire Line
	2950 3100 4250 3100
Wire Wire Line
	2800 3650 3100 3650
Wire Wire Line
	3100 3650 3100 3300
Wire Wire Line
	3100 3300 4250 3300
Wire Wire Line
	2800 3750 3250 3750
Wire Wire Line
	3250 3750 3250 3500
Wire Wire Line
	3250 3500 4250 3500
Wire Wire Line
	2800 3850 3350 3850
Wire Wire Line
	3350 3850 3350 3700
Wire Wire Line
	3350 3700 4250 3700
Wire Wire Line
	2800 3950 3600 3950
Wire Wire Line
	3600 3950 3600 4500
Wire Wire Line
	3600 4500 4250 4500
Connection ~ 5500 2950
Wire Wire Line
	5500 2950 5500 4350
Wire Wire Line
	5500 4350 5050 4350
Wire Wire Line
	3950 2150 3950 2950
Wire Wire Line
	3950 4350 4250 4350
Wire Wire Line
	2200 2150 3950 2150
Wire Wire Line
	3950 2950 4250 2950
Connection ~ 3950 2950
Wire Wire Line
	3950 2950 3950 4350
Text Label 5650 3050 0    50   ~ 0
CHIPSELECT_SENSOR
Wire Wire Line
	5050 3100 5650 3100
Wire Wire Line
	5650 3100 5650 3050
Text Label 5650 3250 0    50   ~ 0
CHIPSELECT_STYR
Wire Wire Line
	5050 3300 5650 3300
Wire Wire Line
	5650 3300 5650 3250
Text Label 5650 3400 0    50   ~ 0
MISO
Text Label 5650 3600 0    50   ~ 0
MOSI
Wire Wire Line
	5050 3500 5650 3500
Wire Wire Line
	5650 3500 5650 3400
Wire Wire Line
	5050 3700 5650 3700
Wire Wire Line
	5650 3700 5650 3600
Wire Wire Line
	5050 4500 5650 4500
Wire Wire Line
	5650 4500 5650 4400
Text Label 5650 4400 0    50   ~ 0
SPI_CLOCK
$EndSCHEMATC
