void loadFile() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	prodnum = cargnum = stornum = ordnum = redsnum = 0;
	FILE * fStores = fopen("D:/finalProject/data/Stores.bin", "rb");
	if (fStores) {
		for (stornum = 0; !feof(fStores); stornum++) fread(&store[stornum], sizeof(stores), 1, fStores);
		cout << "Stores' File Loaded!\n";
		fclose(fStores);
	}
	else cout << "Stores' File not Exist!\n";
	FILE * fProducts = fopen("D:/finalProject/data/Products.bin", "rb");
	if (fProducts) {
		for (prodnum = 0; !feof(fProducts); prodnum++) fread(&product[prodnum], sizeof(products), 1, fProducts);
		cout << "Products' File Loaded!\n";
		fclose(fProducts);
	}
	else cout << "Products' File not Exist!\n";
	FILE * fCargos = fopen("D:/finalProject/data/Cargos.bin", "rb");
	if (fCargos) {
		for (cargnum = 0; !feof(fCargos); cargnum++) fread(&cargo[cargnum], sizeof(cargos), 1, fCargos);
		cout << "Cargos' File Loaded!\n";
		fclose(fCargos);
	}
	else cout << "Cargos' File not Exist!\n";
	FILE * fOrders = fopen("D:/finalProject/data/Orders.bin", "rb");
	if (fOrders) {
		for (ordnum = 0; !feof(fOrders); ordnum++) fread(&order[ordnum], sizeof(orders), 1, fOrders);
		cout << "Orders' File Loaded!\n";
		fclose(fOrders);
	}
	else cout << "Orders' File not Exist!\n";
	FILE * fReducSells = fopen("D:/finalProject/data/ReducSells.bin", "rb");
	if (fReducSells) {
		for (redsnum = 0; !feof(fReducSells); redsnum++) fread(&reducSell[redsnum], sizeof(reducSells), 1, fReducSells);
		cout << "Reduction Sells' File Loaded!\n";
		fclose(fReducSells);
	}
	else cout << "Reduction Sells' File not Exist!\n";
	checkdate.day = checkdate.month = checkdate.year = 0;
	FILE * fDate = fopen("D:/finalProject/data/date.txt", "r");
	if (fDate != NULL) {
		char year[5], month[3], day[3];
		fseek(fDate, -15, SEEK_END);
		fscanf(fDate, "%s / %s / %s\n", &year, &month, &day);
		for (int i = 0; i < 4; i++) {
			if (day[i] <= '9' && day[i] >= '0') checkdate.day = (day[i] - '0') + (checkdate.day * 10);
			if (month[i] <= '9' && month[i] >= '0') checkdate.month = (month[i] - '0') + (checkdate.month * 10);
			checkdate.year = (year[i] - '0') + (checkdate.year * 10);
		}
		fclose(fDate);
	}
}
void saveFile() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	FILE * fOrders = fopen("D:/finalProject/data/Orders.bin", "wb");
	fwrite(order, sizeof(orders), ordnum, fOrders);
	cout << "Orders' File Saved!\n";
	fclose(fOrders);
	FILE * fReducSells = fopen("D:/finalProject/data/ReducSells.bin", "wb");
	fwrite(reducSell, sizeof(reducSells), redsnum, fReducSells);
	cout << "Reduction Sells' File Saved!\n";
	fclose(fReducSells);
	FILE * fCargos = fopen("D:/finalProject/data/Cargos.bin", "wb");
	fwrite(cargo, sizeof(cargos), cargnum, fCargos);
	cout << "Cargos' File Saved!\n";
	fclose(fCargos);
	FILE * fProducts = fopen("D:/finalProject/data/Products.bin", "wb");
	fwrite(product, sizeof(products), prodnum, fProducts);
	cout << "Products' File Saved!\n";
	fclose(fProducts);
	FILE * fStores = fopen("D:/finalProject/data/Stores.bin", "wb");
	fwrite(store, sizeof(stores), stornum, fStores);
	cout << "Stores' File Saved!\n";
	fclose(fStores);
	FILE * fDate = fopen("D:/finalProject/data/date.txt", "w");
	fseek(fDate, 0, SEEK_END);
	fprintf(fDate, "%d / %d / %d\n", checkdate.year, checkdate.month, checkdate.day);
	fclose(fDate);
}
