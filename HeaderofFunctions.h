date todaydate() {
	date tod;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	tod.year = 1900 + ltm->tm_year;
	tod.month = 1 + ltm->tm_mon;
	tod.day = ltm->tm_mday;
	return tod;
}
date dateDiff(date b, date a) {
	date c;
	c.day = a.day - b.day;
	c.month = a.month - b.month;
	c.year = a.year - b.year;
	if (c.day < 0) {
		c.day += 30;
		c.month--;
	}
	if (c.month < 0) {
		c.month += 12;
		c.year--;
	}
	return c;
}
int timeinday(date a) {
	a.day += (a.month * 30) + (a.year * 365);
	return a.day;
}
int randrange(int min, int max) {
	srand(time(0));
	return (rand() % (max - min)) + min;
}
void addStore() {
	int i = stornum;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Store Name: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin >> store[i].name;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Store Address: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin.ignore();
	getline(cin, store[i].address);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "Store Successfuly Registered!\n";
	store[i].delord = store[i].undelord = store[i].liability = 0;
	stornum++;
}
void editStore() {
	char str[36];
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Store Name: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin >> str;
	int i = 0;
	for (; i<stornum; i++) if (!strcmp(str, store[i].name)) break;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	if (i != stornum) {
		cout << "Address: " << store[i].address;
		cout << "\nDelivered Oreders: " << store[i].delord;
		cout << "\nUndelivered Orders: " << store[i].undelord;
		cout << "\nLiability = " << store[i].liability;
		cout << "\nWhat You Want to Edit(Name, Address, Liability, Done)? ";
		for (; ; ) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cin >> str;
			if (!strcmp(str, "Done")) break;
			else if (!strcmp(str, "Name")) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				cout << "Enter New Name: ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cin >> str;
				strcpy(store[i].name, str);
			}
			else if (!strcmp(str, "Address")) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				cout << "Enter New Address: ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				string address;
				cin.ignore();
				getline(cin, address);
				store[i].address = address;
			}
			else if (!strcmp(str, "Liability")) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout << "This Store's Liability is " << store[i].liability;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				cout << "\nEnter New Liability: ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cin >> store[i].liability;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			cout << "What You Want to Edit Next(Name, Address, Liability, Done)? ";
		}
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << "Store Not Found!\n";
	}
	cin.ignore();
}
void addProduct(char * name) {
	strcpy(product[prodnum].name, name);
	product[prodnum].block = 0;
	product[prodnum].buyc = 0;
	prodnum++;
}
void addOrder() {
	int j, i = ordnum, k, l;
	order[i].del = 0;
	char input[36];
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Enter Order's ID: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin >> input;
	strcpy(order[i].id, input);
	for (; ; ) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout << "Enter Cargo's ID: ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cin >> input;
		strcpy(order[i].cargid, input);
		for (j = 0; j < cargnum; j++) if (!strcmp(order[i].cargid, cargo[j].id)) break;
		if (j != cargnum) break;
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			cout << "Cargo Not Found!\n";
		}
	}
	for (; ; ) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout << "Enter Store's Name: ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cin >> input;
		strcpy(order[i].storname, input);
		for (k = 0; k < stornum; k++) if (!strcmp(order[i].storname, store[k].name)) break;
		if (k != stornum) {
			for (l = 0; l < prodnum; l++) if (!strcmp(product[l].name, cargo[j].prodname)) break;
			strcpy(product[l].buyers[product[l].buyc], order[i].storname);
			product[l].buyc++;
			store[j].undelord++;
			break;
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			cout << "Store Not Found!\n";
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Enter Amount of Order: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin >> order[i].num;
	cargo[j].stocknum -= order[i].num;
	store[k].liability = (order[i].num * cargo[j].sellcost);
	order[i].orddate = todaydate();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "Order Successfuly Registered!\n";
	cin.ignore();
	ordnum++;
}
void addCargo() {
	int i = cargnum;
	char input[36];
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Enter Cargo's ID: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin >> input;
	strcpy(cargo[i].id, input);
	int j = 0;
	for (; ; ) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout << "Enter Product Name: ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cin >> input;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		strcpy(cargo[i].prodname, input);
		for (; j < prodnum; j++) if (!strcmp(cargo[i].prodname, product[j].name)) break;
		if (j != prodnum) {
			if (product[j].block == 0) break;
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout << "\nThis Product Kind is Forbidden!";
			}
		}
		else {
			addProduct(cargo[i].prodname);
			break;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Enter Factory Name: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin >> input;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	strcpy(cargo[i].factory, input);
	cout << "Enter Generating Date(as day month year): ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin >> cargo[i].gen.day >> cargo[i].gen.month >> cargo[i].gen.year;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Enter Expiring Date(as day month year): ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin >> cargo[i].exp.day >> cargo[i].exp.month >> cargo[i].exp.year;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cargo[i].exptime = dateDiff(cargo[i].gen, cargo[i].exp);
	cout << "Enter Purchase Amount: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin >> cargo[i].buynum;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cargo[i].stocknum = cargo[i].buynum;
	cout << "Enter Purchase Price: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin >> cargo[i].buycost;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Enter Sales Price: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin >> cargo[i].sellcost;
	cargo[i].redcount = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "Cargo Successfully Registered!\n";
	cargnum++;
	cin.ignore();
}
void editCargo() {
	char str[36];
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Enter Cargo's ID: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin >> str;
	int i = 0;
	for (; i < cargnum; i++) if (!strcmp(cargo[i].id, str)) break;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	if (i != cargnum) {
		cout << "Product Name: " << cargo[i].prodname;
		cout << "\nFactory Name: " << cargo[i].factory;
		cout << "\nGenerating Date: " << cargo[i].gen.day << " / " << cargo[i].gen.month << " / " << cargo[i].gen.year;
		cout << "\nExpiring Date: " << cargo[i].exp.day << " / " << cargo[i].exp.month << " / " << cargo[i].exp.year;
		cout << "\nStock Amount: " << cargo[i].stocknum << "/" << cargo[i].buynum;
		cout << "\nPurchase Price: " << cargo[i].buycost;
		cout << "\nSales Price: " << cargo[i].sellcost;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << "\nWhat You Want to Edit?\n";
		cout << "(ID, Product, Factory, Generatin Date, Expiring Date,\n";
		cout << " Purchase Price, Sales Price, Stock Amount, Purchase Amount, Done)\n";
		for (; ; ) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			string strin;
			cin.ignore();
			getline(cin, strin);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			if (strin == "ID") {
				cout << "Enter New ID: ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cin >> cargo[i].id;
			}
			else if (strin == "Product") {
				cout << "Enter Product of Cargo: ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cin >> cargo[i].prodname;
				int j = 0;
				for (; j < prodnum; j++) if (!strcmp(cargo[i].prodname, product[j].name)) break;
				if (j == prodnum) addProduct(cargo[i].prodname);
				strcpy(cargo[i].prodname, product[j].name);
			}
			else if (strin == "Factory") {
				cout << "Enter Factory Name: ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cin >> cargo[i].factory;
			}
			else if (strin == "Generatin Date") {
				cout << "Enter Generating Date(as day month year): ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cin >> cargo[i].gen.day >> cargo[i].gen.month >> cargo[i].gen.year;
			}
			else if (strin == "Expiring Date") {
				cout << "Enter Expiring Date(as day month year): ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cin >> cargo[i].exp.day >> cargo[i].exp.month >> cargo[i].exp.year;
			}
			else if (strin == "Purchase Price") {
				cout << "Enter Purchase Price: ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cin >> cargo[i].buycost;
			}
			else if (strin == "Sales Price") {
				cout << "Enter Sales Price: ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cin >> cargo[i].sellcost;
			}
			else if (strin == "Stock Amount") {
				cout << "Enter Stock Amount: ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cin >> cargo[i].stocknum;
			}
			else if (strin == "Purchase Amount") {
				cout << "Enter Purchase Amount: ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cin >> cargo[i].buynum;
			}
			else if (strin == "Done") break;
			else {
				cout << "Wrong Input!\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			cout << "What You Want to Edit Next?\n";
		}
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << "Cargo Not Found!\n";
	}
	//	cin.ignore();
}
void deliveredOrder() {
	char id[10];
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Enter Order's ID: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin >> id;
	int i = 0, j;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	for (; i<ordnum; i++) if (!strcmp(order[i].id, id)) break;
	if (i != ordnum) {
		order[i].del = 1;
		for (j = 0; j < stornum; j++) if (!strcmp(store[j].name, order[i].storname)) break;
		store[j].delord++;
		store[j].undelord--;
		order[i].deldate = todaydate();
		cout << "Order Delivering Registered!\n";
	}
	else cout << "Order Not Found!\n";
	cin.ignore();
}
void deliveredReducSell() {
	char id[10];
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Enter Order's ID: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cin >> id;
	int i = 0;
	for (; i<redsnum; i++) if (!strcmp(reducSell[i].id, id)) break;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	if (i != redsnum) {
		reducSell[i].del = 1;
		reducSell[i].deldate = todaydate();
		cout << "Reduction Sell Delivering Registered!\n";
	}
	else cout << "Order Not Found!\n";
	cin.ignore();
}
