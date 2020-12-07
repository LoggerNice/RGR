#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;

struct patient
{
	string name, surname, patronymic, numberPhone, day;
} Info;

struct doctor
{
	string profession[7] = {"��������", "�������", "����-������", "��������", "�����������", "���������", "���������"},
		   name[7] = {"���������", "��������", "�����", "���������", "������", "������", "�����"},
		   surname[7] = {"������", "��������", "��������", "����������", "��������" , "�������" , "��������" };
} Data;

void Menu();

void ClearFile()
{
	ofstream file;
	file.open("Info_Patient.txt", ofstream::trunc);
	file.close();
	file.open("Info_Appointment.txt", ofstream::trunc);
	file.close();
}

int MainMenu()
{
	int input;

	system("cls");
	cout<< "����� ���������� � ��������� ��������� �������� �1" << endl << endl
		<< "��� �� ������� �������?" << endl
		<< "[1] ������� ���������� ��������" << endl
		<< "[2] ����������� ������ ���� ������ � ������ �� ����" << endl
		<< "[3] ����������� ���������� � ��������� ��������" << endl
		<< "[4] ����� �� ���������" << endl << endl;	
	cin >> input;
	return input;
}

void ChoiceMenu()
{
	int inputLeave;

	cout << endl << "��� �� ������� �������?" << endl
		<< "[1] ��������� �����" << endl
		<< "[2] ����� �� ����������" << endl << endl;
	cin >> inputLeave;

	if (inputLeave == 1)
		Menu();
	else if (inputLeave == 2) {
		ClearFile();
		exit(0);
	}
	else
		cout << "�������� ����!" << endl;
}

void CreateCard()
{
	ofstream writeFile("Info_Patient.txt");

	system("cls");
	if (writeFile.is_open()) {
		cout << "�������� ���������� � ����" << endl << endl
			<< "������� ���� ���: ";
		cin >> Info.name;
		cout << "������� ���� �������: ";
		cin >> Info.surname;
		cout << "������� ���� ��������: ";
		cin >> Info.patronymic;
		cout << "������� ���� ���� �������� (04.12.2020): ";
		cin >> Info.day;
		cout << "������� ��� ����� �������: ";
		cin >> Info.numberPhone;

		writeFile << Info.surname << " " << Info.name << " " << Info.patronymic << " ���� ��������: " << Info.day << " ����� ��������: " << Info.numberPhone << "\n";
		writeFile.close();

		ChoiceMenu();
	}
	else
		cout << "��������� ������ ���������� ������ :(" << endl;
}

void AppointmentWithDoctor(int inputDoctor, int inputDay)
{
	int timeAppointment = 2 * (inputDay - 1) + 8;
	ofstream writeFile("Info_Appointment.txt");

	if (writeFile.is_open()) {
		writeFile << "���� �: " << Data.profession[inputDoctor - 1] << endl
				  << "����� �����: " << timeAppointment << ".00" << endl 
				  << "�������: " << Info.surname << " " << Info.name << " " << Info.patronymic << endl
				  << "����: " << Data.surname[inputDoctor - 1] << " " << Data.name[inputDoctor - 1] << endl;
		writeFile.close();
	}
	else 
		cout << "��������� ������ ���������� ������ :(" << endl;

	ifstream readFile("Info_Appointment.txt");
	string text;
	if (readFile.is_open()) {
		system("cls");
		while (getline(readFile, text))
			cout << text << endl;
		ChoiceMenu();
		readFile.close();
	}
	else
		cout << "��������� ������ ���������� ������ :(" << endl;
}

void ListDoctor()
{
	int inputItem, inputTime;

	system("cls");
	ifstream readFile("Info_Patient.txt");
	if (readFile.is_open()) {
		string text;

		while (readFile) {
			readFile >> text;
			if (text.length() == 0) {
				cout << "�� �� ������� ����������� �����!" << endl;
				ChoiceMenu();
			} 
			else {
				system("cls");
				cout << "���� ����������� ������ ������" << endl << endl;
				for (int i = 0; i < 7; i++)
					cout << "[" << i + 1 << "] " << Data.profession[i] << " - " << Data.surname[i] << " " << Data.name[i] << endl;
				cout << endl;
				cin >> inputItem;

				if (inputItem == 8)
					Menu();
				else if (inputItem > 0 && inputItem < 8) {
					system("cls");
					cout << "������� ���: ����������� - �������" << endl << endl
						<< "�������� ����� �� ����� � �����: " << endl;
					for (int i = 8; i <= 18; i += 2) {
						cout << "[" << (i - 8) / 2 + 1 << "]" << " " << i << ".00 �����" << endl;
					}
					cout << "[7] �����" << endl << endl;
					cin >> inputTime;

					if (inputTime == 7)
						ListDoctor();
					else if (inputTime > 0 && inputTime < 7)
						AppointmentWithDoctor(inputItem, inputTime);
					else
						cout << "�������� ����!" << endl;
				}
				else
					cout << "�������� ����!" << endl;
			}
		}
	}
}

void Information()
{
	system("cls");
	cout<< "���������� � ��������� ��������" << endl << endl
		<< "��������� ����������� �������� - ��������������� ��������� � ������� ��������� 1054 �������������� ����" << endl
		<< "�������: 8 (8453) 35-76-53" << endl
		<< "����� ����������� �����: citypolis@mail.ru" << endl
		<< "������� ���� ��� �� '����': �������� ������� ����������" << endl
		<< "�����: ��. ��������� ���, 64, ��������" << endl;
	ChoiceMenu();
}

void Menu()
{
	int inputFunction = 0;

	while (inputFunction != 4) {
		inputFunction = MainMenu();
		switch (inputFunction)
		{
		case 1:
			CreateCard();
			break;
		case 2:
			ListDoctor();
			break;
		case 3:
			Information();
			break;
		case 4:
			ClearFile();
			exit(0);
		default:
			cout << "�������� ����!" << endl;
			system("cls");
			break;
		}
	}
}

int main()
{
	/* ��������: ��������� �������� �1
	   ===============================
	   ����: 
	   1. +������ ���������;
	   2. +�������������� ���������� � ��������;
	   3. ++��������� ������ � �������� (���, �������, ��������, ���� ��������, ����� ��������;
	   4. ++������ ���� ������ � �� ����������;
	   5. +������� ������� ���� � ������� ��������;
	   ===============================
	   ������:
	   1. ������ ������������ ��� �������������� ������;
	   2. ���������� �� ���� ������ �������� � ���� ��������;
	   3. ���������� ���� ���� ������; 
	   4. ����� ������ ������ �������� �� ����� ������ �����; */

	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251);

	Menu();

	system("pause");
	return 0;
}