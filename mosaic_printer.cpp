#include "pch.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <algorithm>

char ESC = 27;	//kod znaku <ESC>, niezbêdny do wypisywania znaków

void printer() {
	int customChar[] = { 0, 0, 0, 7, 0, 0, 8, 0, 0, 23, 0, 0, 40, 0, 0, 19, 15, 192, 140, 16, 0, 80, 47, 192, 32, 80, 0, 80, 175, 192, 47, 80, 0, 80, 175, 192, 47, 80, 0, 80, 163, 192, 33, 64, 0, 80, 163, 192, 33, 64, 0, 80, 163, 192, 47, 80, 0, 80, 175, 192, 47, 80, 0, 80, 175, 192, 32, 80, 0, 80, 47, 192, 40, 16, 0, 19, 15, 192, 40, 0, 0, 23, 0, 0, 8, 0, 0, 7, 0, 0, 0, 0, 0 };

	std::fstream lptPort;
	std::string portName;
	std::cout << "Enter the name of the printer port (Information can be found in Device manager): ";
	std::cin >> portName;
	std::transform(portName.begin(), portName.end(), portName.begin(), ::toupper);
	std::cout << portName;
	lptPort.open(portName, std::ios::out);
	if (lptPort.is_open()) {
		
		lptPort << ESC << "h" << "0";	// domyœlny rozmiar znaków
		lptPort << ESC << "l" << char(0);	// instrukcja ustawiaj¹ca margines
		lptPort << ESC << (char)13;

		std::string text = "Profesor Janusz Biernat ukoñczy³ studia na Wydziale Elektroniki Politechniki Wroc³awskiej w roku 1972.";
		lptPort << ESC << "x" << "0" << "Draft quality (lower quality) text: " << text << "\n";
		lptPort << ESC << "x" << "1" << "Letter quality (higher quality) text: " << text << "\n";
		lptPort << ESC << "k" << "3" << ESC << "x1" << "Prestige Font: " << text << std::endl;
		//lptPort << ESC << "0" << ESC << "k10" << ESC << "x1" << "(Leading 1/8 inch)Letter Gothic Font: " << text << std::endl;
		lptPort << ESC << "2" << ESC << "k1" << ESC << "x1" << "(Leading 1/6 inch)Sanserif Font: " << text << std::endl;
		lptPort << ESC << "+" << "1" << ESC << "k2" << ESC << "x1" << "(Leading 1/360 inch)Courier Font: " << text << std::endl;
		lptPort << ESC << "l" << char(40) << ESC << "x1" << "(Left margin 40)Courier Font: " << text << std::endl;

		lptPort << ESC << ":" << (char)0 << (char)3 << (char)0;
		lptPort << ESC << "x1";
		lptPort << ESC << "&" << "0";
		lptPort << (char)59 << (char)59;
		lptPort << (char)2 << (char)31 << (char)2;

		for (int i = 0; i < 31 * 3; i++) {
			lptPort << (char)customChar[i];
		}
		

		lptPort << ESC << "h" << "1";
		lptPort << ESC << "%" << "1";
		lptPort << (char)59 << std::endl;

		lptPort << ESC << "l" << (char)0;
		lptPort << ESC << "h" << "0";
		lptPort << ESC << (char)13;

		for (int i = 0; i < 5; i++) {
			lptPort << ";";
		}

		lptPort.close();
	}
	else {
		std::cout << "Port opening error\n";
	}
}

int main() {
	printer();
	std::cin.get();
	std::cin.get();
}
