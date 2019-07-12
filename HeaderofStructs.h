struct date {
	int day;
	int month;
	int year;
	bool operator != (const date & dat) {
		if (day != dat.day && month != dat.month && year != dat.year) return 1;
		else return 0;
	}
};
struct products {
	bool block;
	char name[36];
	int buyc;
	char buyers[50][36];
} product[50];
struct cargos {
	char id[10];
	char prodname[36];
	char factory[21];
	date gen;
	date exptime;
	date exp;
	int buynum;
	int stocknum;
	long long int buycost;
	long long int sellcost;
	int redcount;
} cargo[100];
struct stores {
	char name[36];
	string address;
	int delord;
	int undelord;
	long long int liability;
} store[50];
struct orders {
	bool del;
	char id[10];
	char storname[36];
	char cargid[10];
	int num;
	date orddate;
	date deldate;
} order[5000];
struct reducSells {
	bool del;
	char id[10];
	char storname[36];
	char cargid[10];
	double redperc;
	int num;
	date selldate;
	date deldate;
} reducSell[200];
date checkdate;
