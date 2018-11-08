EESchema Schematic File Version 4
LIBS:komm-cache
EELAYER 26 0
EELAYER END
$Descr User 6694 5118
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
L komm-rescue:Raspberry_Pi_2_3-Connector J?
U 1 1 5BC49E7D
P 1550 2200
F 0 "J?" H 1550 3850 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" H 1550 3750 50  0000 C CNN
F 2 "" H 1550 2200 50  0001 C CNN
F 3 "https://www.raspberrypi.org/documentation/hardware/raspberrypi/schematics/rpi_SCH_3bplus_1p0_reduced.pdf" H 1550 2200 50  0001 C CNN
	1    1550 2200
	1    0    0    -1  
$EndComp
$Comp
L komm-rescue:BSS138_bidirectional_level_shifter-Logic_LevelTranslator levelshifter?
U 1 1 5BC4E4B2
P 4200 2150
F 0 "levelshifter?" H 4200 3050 50  0001 C CIN
F 1 "BSS138_bidirectional_level_shifter" H 4146 2826 50  0000 C CNN
F 2 "adafruit_i2c_level_shifter" H 4350 1100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/txb0104.pdf" H 4310 2245 50  0001 C CNN
	1    4200 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 900  1100 900 
Wire Wire Line
	1100 900  1100 750 
Wire Wire Line
	1100 750  5050 750 
Wire Wire Line
	5050 750  5050 1700
Wire Wire Line
	5050 1700 4600 1700
Text Notes 1500 2900 1    50   ~ 0
CAMERA \nPORT\n
$Comp
L komm-rescue:BSS138_bidirectional_level_shifter-Logic_LevelTranslator levelshifter?
U 1 1 5BE9F7E8
P 4200 3550
F 0 "levelshifter?" H 4200 4450 50  0001 C CIN
F 1 "BSS138_bidirectional_level_shifter" H 4146 4226 50  0000 C CNN
F 2 "adafruit_i2c_level_shifter" H 4350 2500 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/txb0104.pdf" H 4310 3645 50  0001 C CNN
	1    4200 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 3500 1750 4250
Wire Wire Line
	1750 4250 4200 4250
Wire Wire Line
	1850 4100 3700 4100
Wire Wire Line
	3700 4100 3700 2850
Wire Wire Line
	3700 2850 4200 2850
Wire Wire Line
	1850 3500 1850 4100
Wire Wire Line
	2350 2300 2500 2300
Wire Wire Line
	2500 2300 2500 1850
Wire Wire Line
	2500 1850 3800 1850
Wire Wire Line
	2350 2400 2650 2400
Wire Wire Line
	2650 2400 2650 2050
Wire Wire Line
	2650 2050 3800 2050
Wire Wire Line
	2350 2500 2800 2500
Wire Wire Line
	2800 2500 2800 2250
Wire Wire Line
	2800 2250 3800 2250
Wire Wire Line
	2350 2600 2900 2600
Wire Wire Line
	2900 2600 2900 2450
Wire Wire Line
	2900 2450 3800 2450
Wire Wire Line
	2350 2700 3150 2700
Wire Wire Line
	3150 2700 3150 3250
Wire Wire Line
	3150 3250 3800 3250
Connection ~ 5050 1700
Wire Wire Line
	5050 1700 5050 3100
Wire Wire Line
	5050 3100 4600 3100
Wire Wire Line
	3500 900  3500 1700
Wire Wire Line
	3500 3100 3800 3100
Wire Wire Line
	1750 900  3500 900 
Wire Wire Line
	3500 1700 3800 1700
Connection ~ 3500 1700
Wire Wire Line
	3500 1700 3500 3100
Text Label 5200 1800 0    50   ~ 0
CHIPSELECT_SENSOR
Wire Wire Line
	4600 1850 5200 1850
Wire Wire Line
	5200 1850 5200 1800
Text Label 5200 2000 0    50   ~ 0
CHIPSELECT_STYR
Wire Wire Line
	4600 2050 5200 2050
Wire Wire Line
	5200 2050 5200 2000
Text Label 5200 2150 0    50   ~ 0
MISO
Text Label 5200 2350 0    50   ~ 0
MOSI
Wire Wire Line
	4600 2250 5200 2250
Wire Wire Line
	5200 2250 5200 2150
Wire Wire Line
	4600 2450 5200 2450
Wire Wire Line
	5200 2450 5200 2350
Wire Wire Line
	4600 3250 5200 3250
Wire Wire Line
	5200 3250 5200 3150
Text Label 5200 3150 0    50   ~ 0
SPI_CLOCK
$EndSCHEMATC
