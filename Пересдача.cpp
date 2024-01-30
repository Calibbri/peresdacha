#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class EmployeeBase;						// предварительное объявление класса (какой-то метод не видел его без этого)

class UserProject						// класс пользовательских проектов
{
private:
	string project_name,				// имя проекта
		   project_description;			// описание проекта
	string project_creator[2];			// параметры создателя (имя, департамент)

	friend EmployeeBase;				// используется для свободной записи данных в методе write_to_file класса EmployeeBase
	

public:

	UserProject()						// конструктор класса, по умолчанию задает поля
	{
		project_name = "NULL";
		project_description = "NULL";
		project_creator[0] = "NULL";
		project_creator[1] = "NULL";
	}

	//UserProject(string *n, string*d, string *cr_1, string *cr_2)	// конструктор класса в случае, вроде ранее использовался. Точно не помню.
	//																	вероятно всего он нигде программой не используется. 
	//																Все проверил, однако оставил на всяки случай
	//{
	//	project_name = *n;
	//	project_description = *d;
	//	project_creator[0] = *cr_1;
	//	project_creator[1] = *cr_2;
	//}

	void createProject(string const *n, string const *d)// метод создания проекта, он вызывается только в случае создания проекта, вызванного пользователем
														// во время работы программы
	{
		system("cls");
		cout << "Заполните название проекта:";	getline(cin, project_name, '\n');
		cout << "Внесите описание проекта:";	getline(cin, project_description, '\n');
		project_creator[0] = *n;//
		project_creator[1] = *d;//
		system("pause");
		system("cls");
	}
	void createProject(ifstream *f, string const *n, string const *d) // перегруженный метод создания проекта, использутеся при запуске программы, читает файл
	{
		getline(*f, project_name, '\n');
		getline(*f, project_description, '\n');
		project_creator[0] = *n;//
		project_creator[1] = *d;//
	}

	void getProjectList(int const *number)						// метод вывода информации об имеющемся проекте, number отвечает за номер проекта
	{
		cout << "Информация о вашем проекте №" << *number + 1 << endl;
		cout << "Создатель: " << project_creator[0] << endl << "Департамент: " << project_creator[1] << endl;
		cout << "Название проекта: " << project_name << endl;
		cout << "Описание проекта: " << project_description << endl;
		cout << "__________________________________________________________" << endl; 
	}
};

class Employee						// класс сотрудника
{
private:
	int pr_len = 0;					// длина списка проектов сотрудника
	string login,					// эти параметры были внесены в раздел private в целях симуляции безопасности
		password;

	void firstProject()											// создание первого проекта
	{
		project_list[0].createProject(&name, &department);		// вызов обычного метода создания проекта
		pr_len++;												// так как проект уже был создан, то идет +1
	}

	void firstProject(ifstream *f)								// перегруженный метод создания первого проекта
	{
		project_list[0].createProject(f, &name, &department);	// вызов перегруженного метода создания проекта
		// здесь нет pr_len++ , потому что метод перегружен под ситуацию, Когда в файле записано pr_len = 1, => не нужно прибавлять
	}

	void newProject()															// внесение проекта в базу, когда проектов >= 1	
	{
		UserProject t_project;													// создается временный объект проекта
		t_project.createProject(&name, &department);							// заполняется
		UserProject *temp_project_list;											// создается временный список проектов
		temp_project_list = new UserProject[pr_len + 1];						// он на 1 больше, чем текущий
		for (int i = 0; i < pr_len; i++) temp_project_list[i] = project_list[i];// все старые данные переносятся в новый список
		temp_project_list[pr_len] = t_project;									// последний эл. равен новому проекту
		pr_len++;	
		delete[] project_list;													// чистится указатель на старый список
		project_list = temp_project_list;										// дается ссылка на новый список
	}
	void newProject(ifstream *f)									   // перегруженный метод создания списка проектов, когда проектов > 1
	{
		UserProject *temp_project_list = new UserProject[pr_len];	   // создается временный список объектов UserProject равный кол-ву проектов (pr_len)

		// по потоку данных мы считали длину, теперь идет pr_len * 2 строк - описания проектов. На каждый проект всего две строки
		for (int i = 0; i < pr_len; i++)
			temp_project_list[i].createProject(f, &name, &department); //вносится необходимое количество проектов в список проектов.

		delete[] project_list;											// стирается старый список проектов
		project_list = temp_project_list;								// дается ссылка на новый список pr_len проектов
	}

	void removeProjectList(int const *number)				// метод удаления любого номера проекта из списка
	{
		UserProject *temp_project_list;						// создается временный список объектов
		int k = 0;											// счетчик, используется для прохождения по temp_project_list
		if (pr_len - 1 == 0)								// ветвление, на случай удаления последнего проекта сотрудника
		{
			// в данном случае, когда мы удаляем последний список проектов, появляется баг, если не выделить память заново
			// действуя по стандартному алгоритму стирания данных, что описан ниже, указатель project_list "подвисает", стираются данные, но
			// память не очищается, адреса памяти теряются. Поэтому не было возможности создавать новые проекты - БАГ.
			// В целях фикса бага удаляется ссылка на project_list, затем динамическая память выделяется заново
			delete[] project_list;
			project_list = new UserProject[1];
		}
		else
		{
			// в случае удаления не последнего проекта:
			temp_project_list = new UserProject[pr_len - 1];									// создается временный список проектов на один меньше
			for (int i = 0; i < (*number - 1); i++) temp_project_list[k++] = project_list[i];	// до стертого, то есть number проекта все копируется
			for (int i = *number; i < pr_len; i++) temp_project_list[k++] = project_list[i];	// все копируется, но уже после number проекта
			delete[] project_list;																// удаляется старая память
			project_list = temp_project_list;													// дается ссылка на новые данные
		}

	}

	friend EmployeeBase;								// необходимо для работы метода write_to_file класса EmployeeBase

public: 
	UserProject *project_list;							// создается указатель на список проектов
	string name,										// имя сотрудника
		   department;									// отдел, в котором сотрудник работает

	Employee()										// конструктор класса сотрудника 
	{
		login = "Поле не задано";
		password = "Поле не задано";
		name = "Поле не задано";
		department = "Поле не задано";
		if (pr_len == 0)
			project_list = new UserProject[1];		// в случае, когда pr_len = 0, создается по умолчанию один проект
		else
			project_list = new UserProject[pr_len];	// в случае когда pr_len != 0, создается несколько проектов
	}

	void setInf()									// метод, задающий параметры сотрудника
	{
		system("cls");
		cout << "Внесите информацию о сотруднике:" << endl;
		cout << "Имя:";		getline(cin, name, '\n');
		cout << "Отдел:";	getline(cin, department, '\n');
		cout << "Логин:";	getline(cin, login, '\n');
		cout << "Пароль:";	getline(cin, password, '\n');
	}
	void setInf(ifstream *f)					// перегруженный метод задания параметров сотрудника, при чтении из файла
	{
		string buf;						// переменная, необходима для чтения символа конца строки
		getline(*f, buf, '\n');
		getline(*f, name, '\n');
		getline(*f, department, '\n');
		getline(*f, login, '\n');
		getline(*f, password, '\n');
	}

	bool check(string const *l, string const *p)	//метод, отвечающий за проверку введеных имени, логина и пароля
	{

		if (*l != login)
			return false;
		else if (*p != password)
			return false;
		else
			return true;		// в случае, если все данные верные, то возвращается true, и далее осуществляется вход в аккаунт
	}

	void userAccount()		// метод пользовательского аккаунта, который выводит инфу по сотруднику.
	{
		system("cls");
		cout << "---АВТОРИЗАЦИЯ ПРОШЛА УСПЕШНО---" << endl;
		system("pause");

		char choice = '0';
		while (choice != '4')
		{
			system("cls");
			cout << endl << "Выберите, что вы хотите сделать : " << endl;
			cout << "_____________________________" << endl
				 << "1. Создать проект."			<< endl 
				 << "2. Список проектов в работе."	<< endl 
				 << "3. Удалить проект."			<< endl 
				 << "4. Выйти из аккаунта."			<< endl
				 << "_____________________________" << endl;
			cout << "Выберите действие: ";	cin >> choice;
			string buf;			// переменная для чтения символа конца строки 
			getline(cin, buf);	// подчищаем ввод 
			
			switch (choice)
			{
			case '1':				// создание проекта
				if (pr_len == 0)	// когда у сотрудника 0 проектов
					firstProject();	
				else
					newProject();	// когда у сотрдника уже есть проект/проекты
				break;
			case '2':				// вывод списка проектов
				system("cls");
				if (pr_len != 0)
					for (int i = 0; i < pr_len; i++) project_list[i].getProjectList(&i);	// пробегаемся по списку и вызываем методы вывода, передавая номер
				else														// используется в случае, если проектов нет, то есть pr_len == 0
					cout << "---ПРОЕКТОВ НЕТ---" << endl;
				system("pause");
				break;
			case '3':				// удаление проекта
				int n_pr;			// номер проекта, который нужно удалить
				if (pr_len)			// уточняется, есть ли у сотрудника проекты
				{
					system("cls");			
					cout << "Укажите номер проекта:"; cin >> n_pr;
					if (pr_len < n_pr)
					{
						cout << "---ПРОЕКТА С УКАЗАННЫМ НОМЕР НЕ СУЩЕСТВУЕТ---" << endl;
						system("pause");
					}
					else
					{
						removeProjectList(&n_pr);		// метод удаления проекта по номеру проекта
						pr_len--;
						break;
					}
				}
				else				// когда проектов нет, то выводится уведомление
				{
					system("cls");
					cout << "---ПРОЕКТОВ НЕТ---" << endl;
					system("pause");
				}
				break;
			}
		}

	}

	void read_file(ifstream *f) // метод вызываемый только, когда читаем данные из файла 
	{
		*f >> pr_len;			// считываются данные из строки, которая по структуре ввода означает длину списка проектов сотрудника
		string buf;				// переменная для чистики символа новой строки
		getline(*f, buf, '\n');	// "съедаем" символ новой строки
		if (pr_len)				// длина строки не равна 0, то
		{
			if (pr_len == 1)	// вызывается перегруженный метод создания первого проекта
				firstProject(f);
			else
				newProject(f);	// иначе вызывается перегруженный метод создания очередного проекта
		}
	}

};

class EmployeeBase		// класс компании, возможна реализации разных компаний, по аналогии с классом сотрудника.
{
private:
	int len = 0;								// длина текущего списка сотрудников
	Employee *list_employee = new Employee[1];	// список сотрудников 

	void firstEmployee()						// создание первого сотрудника
	{
		list_employee[0].setInf();
		len++;									// теперь один сотрудник есть, len = 1
	}

	void firstEmployee(ifstream *f)		// перегруженный метод для создания первого сотрудника при чтении из файла
	{
		list_employee[0].setInf(f);
	}
	void newEmployee()					// внесение сотрудника в базу, когда сотрудников > 1	
	{
		Employee t_employee;				// создается временный ОБЪЕКТ сотрудника
		t_employee.setInf();				// заполняется
		Employee *temp_list;				// создается временный СПИСОК сотрудников
		temp_list = new Employee[len + 1];	// он на 1 больше, чем текущий
		for (int i = 0; i < len; i++) temp_list[i] = list_employee[i];	// все старые данные переносятся в новый список
		temp_list[len] = t_employee;									// последний эл. равен новому сотруднику
		len++;
		delete[] list_employee;				// чистится указатель на старый список
		list_employee = temp_list;			// дается ссылка на новый список
	}

public:
	EmployeeBase()		// конструктор класса
	{
		ifstream file;
		file.open("data.txt");
		file >> len;

		if (len)		// по сути аналог метода init, необходим для переноса всей инфы из файла в объекты
						// не нагружае программу, потому что если файла пустой, то len = 0 (стрк 271)
		{
			list_employee = new Employee[len];	// создается количество существующий сотрудников, вне зависимости 1 или > 1
			if (len == 1)
			{
				firstEmployee(&file);				// если длина = 1, то есть всего один сотрудник в базе, вызывается перегруженный метод первого сотрудника
				list_employee[0].read_file(&file);	// вызов перегруженного метода для записи данных по сотруднику из файла
			}
			else									// когда больше одного сотрудника, то
			{
				for (int i = 0; i < len; i++)
				{
					list_employee[i].setInf(&file);		// вызывается метод, который читает информацию о сотруднике
					list_employee[i].read_file(&file);	// потом вызывается метод, который читает файл и данные проектов
				}
			}
		}
		file.close();
	}
	void init()			// инциализация первого сотрудника, либо же нового (только по вызову пользователя, во время сессии)
	{
		if (len == 0)	
			firstEmployee();	// стандартный метод создания первого сотрудника
		else
			newEmployee();		// метод создания > 1 сотрудника, уже во время работ программы
	}


	void enter()											// метод входа в аккаунт сотрудника
	{
		string user_name, user_login, user_password;		// для этого используется имя, логин и пароль. Осуществляется поиск по имени
		system("cls");
		bool founded = false;							// переменная нужна, для проверки того, нашелся ли сотрудник или нет
		cout << "---АВТОРИЗАЦИЯ---" << endl;
		cout << "Введите имя сотрудника:";		getline(cin, user_name, '\n');
		cout << "Введите логин сотрудника:";	getline(cin, user_login, '\n');
		cout << "Введите пароль сотрудника:";	getline(cin, user_password, '\n');
		int i = 0;
		for (; i < len; i++)
		{
			if (list_employee[i].name == user_name)							// если имя совпадает и такой сотрудник есть, то
			{
				if (list_employee[i].check(&user_login, &user_password))	// вызывается метод check, проверяющий корректность логина и пароля
				{
					founded = true;										// сотрудник нашелся, значит true
					list_employee[i].userAccount();		// корректная авторизация, check вернул true, вызывается userAccount
					break;
				}
				else				// ошибка при авторизации
				{
					system("cls");
					cout << endl << "---ПРИ АВТОРИЗАЦИИ ДОПУЩЕНА ОШИБКА---" << endl;
					system("pause");
				}
			}

		}
		if (founded == false)					// за все итерации for сотрудник не нашелся, значит есть ошибка во введенных данных, либо нет аккаунта
		{
			system("cls");
			cout << endl << "---ПРИ АВТОРИЗАЦИИ ДОПУЩЕНА ОШИБКА---" << endl;
			system("pause");
		}
	}

	void write_to_file()					// метод записи данных в файл
	{
		ofstream file;
		file.open("data.txt");

		file << len << '\n';	//количество сотрудников в компании
		
		for (int i = 0; i < len; i++)
		{
			file << list_employee[i].name << '\n';				// вводится имя сотрудника
			file << list_employee[i].department << '\n';		// вводится отдел сотрудника
			file << list_employee[i].login << '\n';				// вводится логин сотрудника
			file << list_employee[i].password << '\n';			// вводится пароль сотрудника
			file << list_employee[i].pr_len << '\n';			// вводится количество проектов сотрудника
			for (int j = 0; j < list_employee[i].pr_len; j++)	// вводятся сами проекты сотрудника
			{
				file << list_employee[i].project_list[j].project_name << '\n';			// вводится имя проекта № i
				file << list_employee[i].project_list[j].project_description << '\n';	// вводится описание проекта № i
			}
		}
		file.close();
	}
};



int main()
{
	setlocale(LC_ALL, "Russian");

	char choice = '0';
	EmployeeBase Company;				// Создается объект "Компания". В дальнейшем возможно будет создавать различные компании. 
										// Программа будет хоститься на серверах издателя, а доступ компаниям будет предоставляться в ходе покупки лицензии
	string a;							// переменная для того, что бы "съедать" символ новой строки

	while (choice != '3')				// реализация меню
	{
		system("cls");
		cout << endl << "Выберите, что вы хотите сделать : " << endl;
		cout << "_________________________" << endl
			 << "1. Создать сотрудника."	<< endl
			 << "2. Войти как сотрудник."	<< endl
			 << "3. Выйти из программы."	<< endl
			 << "_________________________";
		cout << endl << "Ваш выбор:";	cin >> choice;
		getline(cin, a, '\n');

		switch (choice)
		{
		case '1':
			Company.init();						// метод инициализации 
			break;
		case '2':
			Company.enter();					// метод входа в аккаунт пользователя
		}
	}

	Company.write_to_file();					// метод записи данных в файл
}

