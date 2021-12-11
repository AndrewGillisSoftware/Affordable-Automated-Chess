EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L OH49E:OH49E IC?
U 1 1 61822EA4
P 6500 3650
F 0 "IC?" H 7100 3915 50  0000 C CNN
F 1 "OH49E" H 7100 3824 50  0000 C CNN
F 2 "OH3144" H 7550 3750 50  0001 L CNN
F 3 "" H 7550 3650 50  0001 L CNN
F 4 "Linear Hall Effect IC" H 7550 3550 50  0001 L CNN "Description"
F 5 "3.28" H 7550 3450 50  0001 L CNN "Height"
F 6 "Ouzhuo" H 7550 3350 50  0001 L CNN "Manufacturer_Name"
F 7 "OH49E" H 7550 3250 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 7550 3150 50  0001 L CNN "Mouser Part Number"
F 9 "" H 7550 3050 50  0001 L CNN "Mouser Price/Stock"
F 10 "" H 7550 2950 50  0001 L CNN "Arrow Part Number"
F 11 "" H 7550 2850 50  0001 L CNN "Arrow Price/Stock"
	1    6500 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT?
U 1 1 6182412C
P 5900 3850
F 0 "BT?" H 6018 3946 50  0000 L CNN
F 1 "5V" H 6018 3855 50  0000 L CNN
F 2 "" V 5900 3910 50  0001 C CNN
F 3 "~" V 5900 3910 50  0001 C CNN
	1    5900 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 3650 6500 3650
Wire Wire Line
	7700 3650 7700 3950
Wire Wire Line
	7700 3950 5900 3950
$Comp
L Device:LED D?
U 1 1 61826DA8
P 6300 3250
F 0 "D?" H 6293 3467 50  0000 C CNN
F 1 "LED" H 6293 3376 50  0000 C CNN
F 2 "" H 6300 3250 50  0001 C CNN
F 3 "~" H 6300 3250 50  0001 C CNN
	1    6300 3250
	1    0    0    -1  
$EndComp
NoConn ~ 6500 3650
Wire Wire Line
	6500 3750 6500 3650
Wire Wire Line
	6500 3250 6450 3250
Connection ~ 6500 3650
Wire Wire Line
	6500 3650 6500 3250
$EndSCHEMATC
