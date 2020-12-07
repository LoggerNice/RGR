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
	string profession[7] = {"Терапевт", "Окулист", "Врач-хирург", "Невролог", "Травматолог", "Кардиолог", "Гинеколог"},
		   name[7] = {"Александр", "Светлана", "Павел", "Александр", "Ксения", "Кирилл", "Ирина"},
		   surname[7] = {"Иванов", "Машухина", "Афанасов", "Комиссаров", "Воронина" , "Данилов" , "Горбенко" };
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
	cout<< "Добро пожаловать в приложние городской больницы №1" << endl << endl
		<< "Что вы желаете сделать?" << endl
		<< "[1] Создать медицинску карточку" << endl
		<< "[2] Просмотреть список всех врачей и запись на приём" << endl
		<< "[3] Просмотреть информацию о городской больнице" << endl
		<< "[4] Выход из программы" << endl << endl;	
	cin >> input;
	return input;
}

void ChoiceMenu()
{
	int inputLeave;

	cout << endl << "Что вы желаете сделать?" << endl
		<< "[1] Вернуться назад" << endl
		<< "[2] Выйти из приложения" << endl << endl;
	cin >> inputLeave;

	if (inputLeave == 1)
		Menu();
	else if (inputLeave == 2) {
		ClearFile();
		exit(0);
	}
	else
		cout << "Неверный ввод!" << endl;
}

void CreateCard()
{
	ofstream writeFile("Info_Patient.txt");

	system("cls");
	if (writeFile.is_open()) {
		cout << "Зполните информацию о себе" << endl << endl
			<< "Введите ваше имя: ";
		cin >> Info.name;
		cout << "Введите вашу фамилию: ";
		cin >> Info.surname;
		cout << "Введите ваше отчество: ";
		cin >> Info.patronymic;
		cout << "Введите вашу дату рождения (04.12.2020): ";
		cin >> Info.day;
		cout << "Введите ваш номер телефон: ";
		cin >> Info.numberPhone;

		writeFile << Info.surname << " " << Info.name << " " << Info.patronymic << " Дата рождения: " << Info.day << " Номер телефона: " << Info.numberPhone << "\n";
		writeFile.close();

		ChoiceMenu();
	}
	else
		cout << "Произошла ошибка сохранения данных :(" << endl;
}

void AppointmentWithDoctor(int inputDoctor, int inputDay)
{
	int timeAppointment = 2 * (inputDay - 1) + 8;
	ofstream writeFile("Info_Appointment.txt");

	if (writeFile.is_open()) {
		writeFile << "Приём к: " << Data.profession[inputDoctor - 1] << endl
				  << "Время приёма: " << timeAppointment << ".00" << endl 
				  << "Пациент: " << Info.surname << " " << Info.name << " " << Info.patronymic << endl
				  << "Врач: " << Data.surname[inputDoctor - 1] << " " << Data.name[inputDoctor - 1] << endl;
		writeFile.close();
	}
	else 
		cout << "Произошла ошибка сохранения данных :(" << endl;

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
		cout << "Произошла ошибка считывания данных :(" << endl;
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
				cout << "Вы не создали медицинскую карту!" << endl;
				ChoiceMenu();
			} 
			else {
				system("cls");
				cout << "Ниже представлен список врачей" << endl << endl;
				for (int i = 0; i < 7; i++)
					cout << "[" << i + 1 << "] " << Data.profession[i] << " - " << Data.surname[i] << " " << Data.name[i] << endl;
				cout << endl;
				cin >> inputItem;

				if (inputItem == 8)
					Menu();
				else if (inputItem > 0 && inputItem < 8) {
					system("cls");
					cout << "Рабочие дни: понедельник - суббота" << endl << endl
						<< "Выберите время на прием к врачу: " << endl;
					for (int i = 8; i <= 18; i += 2) {
						cout << "[" << (i - 8) / 2 + 1 << "]" << " " << i << ".00 часов" << endl;
					}
					cout << "[7] Назад" << endl << endl;
					cin >> inputTime;

					if (inputTime == 7)
						ListDoctor();
					else if (inputTime > 0 && inputTime < 7)
						AppointmentWithDoctor(inputItem, inputTime);
					else
						cout << "Неверный ввод!" << endl;
				}
				else
					cout << "Неверный ввод!" << endl;
			}
		}
	}
}

void Information()
{
	system("cls");
	cout<< "Информация о городской больнице" << endl << endl
		<< "Городская клиническая больница - многопрофильный стационар с коечной мощностью 1054 круглосуточных коек" << endl
		<< "Телефон: 8 (8453) 35-76-53" << endl
		<< "Адрес электронной почты: citypolis@mail.ru" << endl
		<< "Главный врач ГУЗ СО 'БГКБ': Крючкова Надежда Николаевна" << endl
		<< "Адрес: ул. Академика Жук, 64, Балаково" << endl;
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
			cout << "Неверный ввод!" << endl;
			system("cls");
			break;
		}
	}
}

int main()
{
	/* Название: городская больница №1
	   ===============================
	   Цели: 
	   1. +Запись пациентов;
	   2. +Предоставление информации о больнице;
	   3. ++Получение данных о пациенте (имя, фамилия, отчество, дата рождения, номер телефона;
	   4. ++Список всех врачей и их расписания;
	   5. +Создать главное меню с выбором операций;
	   ===============================
	   Защита:
	   1. Нельзя записываться без предоставления данных;
	   2. Запрещение на ввод лишних символов в дате рождения;
	   3. Обязателен ввод всех данных; 
	   4. Время записи должно попадать во время работы врача; */

	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251);

	Menu();

	system("pause");
	return 0;
}