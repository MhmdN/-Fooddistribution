void addReducSell(cargos a) {
	int sellpack, j, k[50] = { 0 }, l, prod = 0, stor = 0;
	for (; prod < prodnum; prod++) if (!strcmp(product[prod].name, a.prodname)) break;
	if (product[prod].buyc > 4 && a.stocknum > 20) {
		sellpack = (product[prod].buyc / 4);
		for (int i = 0; i < sellpack; i++) {
			for (; ; ) {
				j = randrange(0, product[prod].buyc);
				int f = 0;
				for (l = 0; k[l] != 0; l++) if (k[i] == j)f++;
				if (f == 0)break;
			}
			k[i] = j;
			strcpy(reducSell[redsnum].cargid, a.id);
			strcpy(reducSell[redsnum].storname, product[prod].buyers[j]);
			reducSell[redsnum].del = 0;
			if (i != sellpack - 1) reducSell[redsnum].num = a.stocknum / sellpack;
			else reducSell[redsnum].num = a.stocknum;
			reducSell[redsnum].redperc = 0.2;
			a.stocknum = 0;
			reducSell[redsnum].selldate = todaydate();
			for (stor = 0; stor < stornum; stor++) if (!strcmp(store[stor].name, reducSell[redsnum].storname)) break;
			store[stor].liability += (a.sellcost * (1 - reducSell[redsnum].redperc)) * reducSell[redsnum].num;
			redsnum++;
		}
	}
	else if (product[prod].buyc < 4 && a.stocknum > 20) {
		sellpack = product[prod].buyc;
		int m = a.stocknum / sellpack;
		for (int i = 0; i < sellpack; i++) {
			j = i;
			strcpy(reducSell[redsnum].cargid, a.id);
			strcpy(reducSell[redsnum].storname, product[prod].buyers[j]);
			reducSell[redsnum].del = 0;
			if (i != sellpack - 1) reducSell[redsnum].num = m;
			else reducSell[redsnum].num = a.stocknum;
			reducSell[redsnum].redperc = 0.2;
			a.stocknum -= reducSell[redsnum].num;
			reducSell[redsnum].selldate = todaydate();
			for (stor = 0; stor < stornum; stor++) if (!strcmp(store[stor].name, reducSell[redsnum].storname)) break;
			store[stor].liability += (a.sellcost * (1 - reducSell[redsnum].redperc)) * reducSell[redsnum].num;
			redsnum++;
		}
	}
	else {
		sellpack = 1;
		j = randrange(0, product[prod].buyc);
		strcpy(reducSell[redsnum].cargid, a.id);
		strcpy(reducSell[redsnum].storname, product[prod].buyers[j]);
		reducSell[redsnum].del = 0;
		reducSell[redsnum].num = a.stocknum;
		reducSell[redsnum].redperc = 0.2;
		a.stocknum = 0;
		reducSell[redsnum].selldate = todaydate();
		for (stor = 0; stor < stornum; stor++) if (!strcmp(store[stor].name, reducSell[redsnum].storname)) break;
		store[stor].liability += (a.sellcost * (1 - reducSell[redsnum].redperc)) * reducSell[redsnum].num;
		redsnum++;
	}
}
void sellAnalysis() {
	checkdate = todaydate();
	for (int i = 0; i < cargnum; i++) {
		if (cargo[i].stocknum >((cargo[i].buynum * 4) / 5)) {
			int prod = 0;
			for (; prod < prodnum; prod++) if (!strcmp(product[prod].name, cargo[i].prodname)) break;
			product[prod].block = 1;
		}
		if (timeinday(dateDiff(cargo[i].gen, checkdate)) >(((timeinday(cargo[i].exptime)) * 2) / 3)) addReducSell(cargo[i]);
	}
}
