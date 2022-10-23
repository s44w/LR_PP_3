#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

int input_check()
{
	/*
	Функция, проверяет, являются ли введенные пользователем данные числом

	Если фукнция stoi не срабатывает ИЛИ to_string обрезает ввод, то выводит ошибку

	Возвращает:
		number: int -  число, переведенное из input: string, которое ввел пользователь
	*/
	string input;
	bool ok = true;
	int number = 0;

	while (ok)
	{
		getline(cin, input);
		try
		{
			number = stoi(input);
			if (to_string(number).length() != input.length())
			{
				throw (1);
			}
			return number;
		}
		catch (invalid_argument)
		{
			cerr << "Error (1)! Write an integer number!" << endl;
		}
		catch (int i)
		{
			cerr << "Error (2)! Write an integer number!" << endl;
		}
	}
}

bool limit = false;
int count_func()
{
	/*
	Функция, позволяет пользователю ввести длину вектора и управляет флагом limit
	*/
	int count = 0;
	while (count < 3)
	{
		count = input_check();
		if (count < 3) cout << "Number is too low! Try again" << endl;
	}

	if (count > 200)
	{
		cout << "Number is too big. Programm will show first 200 elements" << endl;
		limit = true;
	}
	return count;
}

vector <int> individual_record(int count)
{
	/*
	Функция, проводит запись вектора через пользовательский ввод
	Аргументы:
		count: int - длина вектора
	Возвращает:
		array: vector <int> - вектор чисел
	*/
	vector <int> array;

	cout << "You chose individual input" << endl;
	for (int i = 0; i < count; ++i)
	{
		cout << "\n Input #" << i + 1 << " element of sequence: ";
		int number = input_check();
		array.push_back(number);
	}
	return array;
}

vector <int> random_record(int count)
{
	/*
	Функция, проводит запись вектора через ввод случайных чисел
	Аргументы:
		count: int - длина вектора
	Возвращает:
		array: vector <int> - вектор чисел
	*/
	vector <int> array;

	cout << "You chose random input" << endl;
	for (int i = 0; i < count; ++i)
	{
		int number = (rand() % 20) - 10;
		array.push_back(number);
	}
	return array;
}

vector <int> sorting_elements(vector <int> array, bool almost)
{
	/*
	Функция, сортирует элементы по принципу "выбор"
	Аргументы:
		array: vector <int>  - изначальный вектор данных
		almost: bool - флаг: если он true, то ставит ограничение элементов сортировки
							 если он false, то сортировка идет до конца
	Возвращает:
		array: vector <int>  - отсортированный вектор данных

	*/
	double border = 0;
	almost ? border = (array.size() * 0.75) : border = (array.size() - 1);

	for (int i = 0; i < border; ++i)
	{
		for (int j = i; j < array.size(); ++j)
		{
			if (array[i] > array[j])
			{
				int minc = array[j];
				array[j] = array[i];
				array[i] = minc;
			}
		}
	}
	return array;
}

vector <int> almost_random_record(int count)
{
	/*
	Функция, заполняет вектор почти отсортированными случайными элементами
	Аргументы: 
		count: int - длина вектора
	Возвращает: 
		sorting_elements(array, true) - функция с маркером true на наличие ограничения
	*/
	vector <int> array = random_record(count);
	return sorting_elements(array, true);

}

vector <int> sort_choose(char choose, int count)
{
	vector <int> data;
	switch (choose)
	{
	case 'Y':
		data = individual_record(count);
		return data;
	case 'N':
		data = random_record(count);
		return data;
	case 'E':
		data = almost_random_record(count);
		return data;
	}
}


char YN_function(bool isElse)
{
	/*
	Функция узнает, вводит пользователь Y или N.
	В зависимости от этого возвращает:
		'true', если введено 'Y'
		'false', если введено 'N'
	*/
	string button;
	int end = 0;
	while (end == 0)
	{
		getline(cin, button);
		if (button[0] == 'Y' && button.length() == 1) return 'Y';
		if (button[0] == 'N' && button.length() == 1)  return 'N';
		if (button[0] == 'E' && button.length() == 1 && isElse)  return 'E';
		if (end == 0) cout << "Type one of the written buttons!" << endl;
	}
}

void output(vector <int>& array, bool limit)
{
	if (limit)
	{
		for (int i = 0; i < 200; ++i)
			cout << array[i] << "|";
	}
	else
	{
		for (int i = 0; i < array.size(); ++i)
			cout << array[i] << "|";
	}
}

int main()
{
	bool end = true;
	while (end)
	{
		cout << "Enter length of your sequence. It must be >2: ";
		int count = count_func();
		

		cout << "Do you want to input elements by yourself?"
			<< " (Write 'Y' to do it OR 'N' to make it random \n" <<
			"OR 'E' to make it random and almost sorted)" << endl;

		vector <int> sorted_func, sorted_auto;		
		vector <int> data = sort_choose(YN_function(true), count);


		//далее считаем время, занимаемое функциями 
		auto begin1 = chrono::steady_clock::now();

		sorted_func = sorting_elements(data, false);

		auto end1 = chrono::steady_clock::now();
		auto elapsed_ms1 = chrono::duration_cast<chrono::nanoseconds>(end1 - begin1);

		

		sorted_auto = data;
		auto begin2 = chrono::steady_clock::now();
		
		sort(sorted_auto.begin(), sorted_auto.end());

		auto end2 = chrono::steady_clock::now();
		auto elapsed_ms2 = chrono::duration_cast<chrono::nanoseconds>(end2 - begin2);

		
		//выводим все данные
		cout << '\n' << "Vector before sorting: " << endl;
		output(data, limit);
		cout << '\n' << "Vector after sorting : " << endl;
		output(sorted_func, limit);
		cout << '\n' << '\n' << "The time of functional sorting: " << elapsed_ms1.count() << " ns\n";
		cout << "The time of auto sorting: " << elapsed_ms2.count() << " ns\n";

		double faster = elapsed_ms1.count() / elapsed_ms2.count();
		cout << "Auto sorting is " << faster << "x faster" << endl;

		cout << '\n' << "Do you want to continue? Input 'Y' or 'N'" << endl;
		YN_function(false) == 'Y' ? end = true : end = false;
	}
}
