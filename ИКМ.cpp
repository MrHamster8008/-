#include <iostream>
#include <string>
#include <vector>
using namespace std;
string vvod(string a) { // функция для ввода чисел и проверки правильности ввода
	cout << "Введите число\n";
	cin >> a;
	bool vern = true;
	for (int u = 0; u < a.size(); u++) {
		if (u == 0) {
			string pro = "123456789";
			int tempcou = 0;
			for (int j = 0; j < pro.size(); j++) {
				if (a[0] == pro[j])
					tempcou++;
			}
			if (tempcou == 0)
				vern = false;
		}
		else {
			string pro = "1234567890";
			int tempcou = 0;
			for (int j = 0; j < pro.size(); j++) {
				if (a[u] == pro[j])
					tempcou++;
			}
			if (tempcou == 0)
				vern = false;
		}
	}
	if (vern == false) {
		cout << "В числе содержатся недопустимые символы или оно начинается с 0 или оно равно 0(Остаток от деления нуля на другое число будет равен нулю), пожалуйста исправьте\n";
		a = vvod(a);
	}
	vector <int> b(20);
	if (a.size() < b.size()) {
		cout << "Число слишком маленькое. Введите 1 если хотите дополнить его нулями или 2 если хотите ввести заного\n"; 
		// нули вставляются в число до тех пор, пока его длина не станет > 20
		int choese, i = 1;
		cin >> choese;
		while (i != 0) {
			if (choese == 1) {
				while (a.size() < b.size()) {
					a += "0";
				}
				if (a[0] == '-')
					a += "0";
				cout << "Готово!\n";
				i = 0;
			}
			else if (choese == 2) {
				a = vvod(a);
				i = 0;
			}
			else {
				cout << "Ошибка, попробуйте снова\n";
				cin >> choese;
			}
		}

	}
	return a;
}
int chto_bolshe(string a, string b) { // функция для проверки какое из чисел больше
	int bolshe = 0,i = 0;
	bool flag = true;
	if (a.size() > b.size())
		bolshe = 1;
	else if (a.size() < b.size())
		bolshe = 2;
	else if (a.size() == b.size()) {
		vector <int> newa(a.size()), newb(b.size());
		while (flag) {
			newa[i] = a[i];
			newb[i] = b[i];
			if (newa[i] > newb[i]) {
				flag = false;
				bolshe = 1;
			}
			else if (newa[i] < newb[i]) {
				flag = false;
				bolshe = 2;
			}
			i++;
			if (i >= a.size())
				flag = false;
		}
	}
	return bolshe;
}
string slozenie(string a, string b) { // сложение чисел
	int cur, nextplus = 0;
	vector <int> newa(a.size()+1), newb(b.size()), tempb(b.size() + 1), mnogb(b.size() + 1); 
	for (int i = 0;i < a.size();i++) {
		newa[i+1] = a[i] - '0';
	}
	for (int i = 0;i < b.size();i++) {
		newb[i] = b[i] - '0';
		mnogb[i + 1] = newb[i];
	}
	while (chto_bolshe(a, b) == 1) {
		tempb = mnogb;
		for (int i = b.size() - 1; i >= 0; i--) {
			cur = newb[i] + mnogb[i+1] + nextplus;
			if (cur >= 10) {
				nextplus = 1;
				cur = cur % 10;
			}
			else
				nextplus = 0;
			mnogb[i+1] = cur;
		}
		if (nextplus == 1) {
			mnogb[0] = mnogb[0] + 1;
			nextplus = 0;
		}
		b = "";
		if (mnogb[0] == 0) {
			for (int i = 1; i < mnogb.size();i++)
				b += to_string(mnogb[i]);
		}
		else {
			for (int i = 0; i < mnogb.size();i++)
				b += to_string(mnogb[i]);
		}
	}
	mnogb = tempb;
	nextplus = 0;
	cur = 0;
	for (int i = newa.size()-1; i >= 0; i--) {
		if (newa[i] - nextplus < mnogb[i]) {
			cur = newa[i] - nextplus + 10 - mnogb[i];
			nextplus = 1;
		}
		else {
			cur = newa[i] - nextplus - mnogb[i];
			nextplus = 0;
		}
		newa[i] = cur;
	}
	int j = 0;
	while (newa[j] == 0)
		j++;
	string c = "";
	for (int i = j; i < newa.size();i++) 
		c += to_string(newa[i]);
	return c;
}

string del(string a, string b) { // деление чисел и поиска остатка от деления
	int schet = 1, bolshe;
	bool flag = true;
	string ost = "";
	vector <int> resultat(0);
	bolshe = chto_bolshe(a, b);
	if (bolshe == 0)
		ost = "0";
	else if (bolshe == 2) {
		ost = a;
	}
	else if (bolshe == 1) {
		while (a.size() >= b.size() and flag) {
			if (chto_bolshe(a.substr(0, schet), b) == 1) { 
				ost = slozenie(a.substr(0,b.size()), b);
				a.replace(0, schet, ost);
				schet = 0;
			}
			else {
				schet++;
				if (schet > a.size())
					flag = false;
			}

		}
		ost = a;
	}
	return ost;
}


int main()
{
	setlocale(LC_ALL, "RUS");
	cout << "Добро пожаловать, пользователь. Это программа для нахождения остатка от деления 20+ занчных чисел\n";
	string a = "0", b = "0";
	cout << "Сначала введите числитель\n";
	a = vvod(a);
	cout << "А теперь введите знаменатель\n";
	b = vvod(b);
	string res;
	res = del(a, b);
	int answ;
	bool flag = true;
	cout << "Остаток от деления равен " << res << "\nХотите продолжить? (Введите 1 для продолжения или 0 для выхода) ";
	while (flag){
		cin >> answ;
		if (answ == 0)
			flag = false;
		else if (answ == 1) {
			cout << "Сначала введите числитель\n";
			a = vvod(a);
			cout << "А теперь введите знаменатель\n";
			b = vvod(b);
			string res;
			res = del(a, b);
			cout << "Остаток от деления равен " << res << "\nХотите продолжить? (Введите 1 для продолжения или 0 для выхода) ";
		}
		else
			cout << "Ошибка, введите свой ответ заного";
	}


}

