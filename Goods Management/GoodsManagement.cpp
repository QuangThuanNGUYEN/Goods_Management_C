#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NSX
{
	int day;
	int month;
	int year;
} nsx;

typedef struct HangHoa
{
	char ID[5];
	nsx date;
	int quantity;
	float price;
	float total;
} Hang;

void NhapSoLuong(int &n)
{
	printf("Nhap so luong hang: ");
	scanf("%d", &n);
	FILE *f = fopen("soluong.inp", "w");
	fprintf(f, "%d", n);
	fclose(f);
}

void NhapTTHang(Hang *hang)
{
	fflush(stdin);
	printf("\nNhap ma hang: ");
	scanf("%s", &hang->ID);
	printf("Nhap nsx: ");
	scanf("%d%d%d", &hang->date.day, &hang->date.month, &hang->date.year);
	printf("Nhap so luong: ");
	scanf("%d", &hang->quantity);
	printf("Nhap don gia: ");
	scanf("%f", &hang->price);
	hang->total = hang->quantity * hang->price;
}

void NhapDS(Hang *hang, int n)
{
	for (int i = 0; i < n; i++)
		NhapTTHang(hang + i);
}

void XuatTTHang(Hang *hang, int no)
{
	printf("--------------------------------------------------------------------------------\n");
	printf("|%5d|%6s|%12d/%d/%d|%11d|%15.3f|%20.3f|", no, hang->ID, hang->date.day, hang->date.month, hang->date.year, hang->quantity, hang->price, hang->total);
}

void XuatDS(Hang *hang, int n)
{
	printf("--------------------------------------------------------------------------------\n");
	printf("|%5s|%6s|%16s|%11s|%15s|%20s|\n", "No", "ID", "Production Date", "Quantity", "Price", "Total");
	for (int i = 0; i < n; i++)
	{
		XuatTTHang(hang + i, i + 1);
		printf("\n");
	}
	printf("--------------------------------------------------------------------------------\n");
}

void ThemVaoCuoiDS(Hang *append, int &n)
{
	FILE *f;
	f = fopen("soluong.inp", "r");
	fscanf(f, "%d", &n);
	n++;
	fclose(f);
	f = fopen("soluong.inp", "w");
	fprintf(f, "%d", n);
	fclose(f);
	NhapTTHang(append);
	f = fopen("hanghoa.inp", "a");
	fprintf(f, "%s %d %d %d %d %f %f\n", append->ID, append->date.day, append->date.month, append->date.year, append->quantity, append->price, append->total);
	fclose(f);
}

void WriteFile(Hang *hang, int n)
{
	FILE *f;
	f = fopen("soluong.inp", "w");
	fprintf(f, "%d", n);
	fclose(f);
	f = fopen("hanghoa.inp", "w");
	for (int i = 0; i < n; i++)
	{
		fprintf(f, "%s %d %d %d %d %f %f\n", (hang + i)->ID, (hang + i)->date.day, (hang + i)->date.month, (hang + i)->date.year, (hang + i)->quantity, (hang + i)->price, (hang + i)->total);
	}
	fclose(f);
}

int GetQuantityOfGoods()
{
	FILE *f = fopen("soluong.inp", "r");
	int n;
	fscanf(f, "%d", &n);
	fclose(f);
	return n;
}

void ReadFile(Hang *hang, int n)
{
	FILE *f;
	f = fopen("hanghoa.inp", "r");
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%s %d %d %d %d %f %f", &(hang + i)->ID, &(hang + i)->date.day, &(hang + i)->date.month, &(hang + i)->date.year, &(hang + i)->quantity, &(hang + i)->price, &(hang + i)->total);
	}
	fclose(f);
}

void SapXepTangDanID(Hang *hang, int n)
{
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (strcmp((hang + i)->ID, (hang + j)->ID) > 0)
			{
				Hang temp = *(hang + i);
				*(hang + i) = *(hang + j);
				*(hang + j) = temp;
			}
}

int IDBinarySearch(Hang *hang, int n, char ID[])
{
	int left = 0, right = n - 1, mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (strcmp((hang + mid)->ID, ID) == 0)
			return mid;
		if (strcmp((hang + mid)->ID, ID) < 0)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return -1;
}

void DeleteGoodsByID(Hang *hang, int &n, char ID[])
{
	if (n < 1)
	{
		printf("\nNothing to delete");
		return;
	}
	for (int i = 0; i < n; i++)
	{
		if (strcmp((hang + i)->ID, ID) == 0)
		{
			for (int j = i; j < n - 1; j++)
				*(hang + j) = *(hang + j + 1);
			n--;
			printf("Deleted successfully!");
			return;
		}
	}
	printf("\nCan't find goods to remove");
}

int CountNumberOfData()
{
	FILE *f = fopen("hanghoa.inp", "r");
	int count_line = 0;
	char ch;
	ch = fgetc(f);
	while (ch != EOF)
	{
		if (ch == '\n')
		{
			count_line++;
		}
		ch = fgetc(f);
	}
	fclose(f);
	return count_line;
}
int CheckFileEmpty()
{
	int size, size1;
	FILE *f = fopen("hanghoa.inp", "r");
	if (NULL != f)
	{
		fseek(f, 0, SEEK_END);
		size = ftell(f);
	}
	fclose(f);
	f = fopen("soluong.inp", "r");
	if (NULL != f)
	{
		fseek(f, 0, SEEK_END);
		size1 = ftell(f);
	}
	fclose(f);
	if (size == size1 && 0 == size)
		return 1; // file is empty
	return 0;	  // files have content
}

int CheckData()
{
	FILE *f = fopen("soluong.inp", "r");
	int n;
	if (f != NULL)
	{
		if (CheckFileEmpty())
			return -2; // Both file are empty
		else
		{
			fscanf(f, "%d", &n);
			if (n != 0)
			{
				if (CountNumberOfData() != n)
				{
					fclose(f);
					return 1; // Data is conflict
				}
				fclose(f);
				return 0; // Data is good
			}
		}
	}
	fclose(f);
	return -1; // Data doesn't exist
}

int AreYouSureToDeleteData()
{
	char user;
	printf("Are you sure to reset all the data? (y: yes or n: no)\nYour selection: ");
	scanf("%c", &user);
	if (user == 'y')
		return 1;
	return 0;
}

void ResetData()
{
	FILE *f = fopen("soluong.inp", "w");
	fclose(f);
	f = fopen("hanghoa.inp", "w");
	fclose(f);
}

void Menu()
{
	int n;
	Hang *hang;
	Hang *hang1;

	int user;
	do
	{
		n = GetQuantityOfGoods();
		printf("\n1)Creat a new list of goods");
		printf("\n2)Display the list of goods");
		printf("\n3)Append the list of goods");
		printf("\n4)Sort the list ascendingly by the goods ID");
		printf("\n5)Remove goods by its ID");
		printf("\n6)Update attributes of goods");
		printf("\n7)Search goods by ID");
		printf("\n8)Reset data");
		printf("\n9)Quit");
		printf("\nYour selection: ");
		fflush(stdin);
		scanf("%d", &user);
		fflush(stdin);

		switch (user)
		{
		case 1:
		{
			printf("\n-----------------------------------------------------------------\n");
			if (CheckData() != -1 && CheckData() != -2)
			{
				if (AreYouSureToDeleteData())
				{
					NhapSoLuong(n);
					hang = (Hang *)malloc(sizeof(Hang) * n);
					NhapDS(hang, n);
					WriteFile(hang, n);
				}
			}
			else
			{
				NhapSoLuong(n);
				hang = (Hang *)malloc(sizeof(Hang) * n);
				NhapDS(hang, n);
				WriteFile(hang, n);
			}
			printf("\n-----------------------------------------------------------------\n");
			break;
		}

		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		{
			printf("\n-----------------------------------------------------------------\n");
			if (CheckData() == -1)
			{
				printf("\nData is empty");
				printf("\n-----------------------------------------------------------------\n");
				break;
			}
			else if (CheckData() == 1)
			{
				printf("\nData is conflict in numbers of goods");
				printf("\n-----------------------------------------------------------------\n");
				break;
			}
			else if (CheckData() == -2)
			{
				printf("Data is empty");
				printf("\n-----------------------------------------------------------------\n");
				break;
			}
			switch (user)
			{
			case 2:
			{
				hang1 = (Hang *)malloc(sizeof(Hang) * n);
				ReadFile(hang1, n);
				XuatDS(hang1, n);
				break;
			}

			case 3:
			{
				Hang append;
				ThemVaoCuoiDS(&append, n);
				break;
			}

			case 4:
			{
				ReadFile(hang1, n);
				SapXepTangDanID(hang1, n);
				WriteFile(hang1, n);
				printf("\nSorted sucessfully!!");
				break;
			}

			case 5:
			{
				char delete_ID[5];
				printf("Type ID to delete: ");
				scanf("%s", &delete_ID);
				ReadFile(hang1, n);
				DeleteGoodsByID(hang1, n, delete_ID);
				WriteFile(hang1, n);
				break;
			}

			case 6:
			{
				hang1 = (Hang *)malloc(sizeof(Hang) * n);
				ReadFile(hang1, n);
				XuatDS(hang1, n);
				int goods_update;
				printf("Choose which number of goods to update: ");
				scanf("%d", &goods_update);
				int update_select;
				printf("Type a number to update (1: ID, 2: Production Date, 3: Quantity, 4: Price): ");
				scanf("%d", &update_select);
				switch (update_select)
				{
				case 1:
					printf("Type new ID: ");
					scanf("%s", &(hang1 + goods_update - 1)->ID);
					break;
				case 2:
					printf("Type new Production Date: ");
					scanf("%d%d%d", &(hang1 + goods_update - 1)->date.day, &(hang1 + goods_update - 1)->date.month, &(hang1 + goods_update - 1)->date.year);
					break;
				case 3:
					printf("Type new Quantity: ");
					scanf("%d", &(hang1 + goods_update - 1)->quantity);
					break;
				case 4:
					printf("Type new Price: ");
					scanf("%f", &(hang1 + goods_update - 1)->price);
					break;
				}
				printf("Updated successfully!");
				WriteFile(hang1, n);
				break;
			}

			case 7:
			{
				char ID[5];
				ReadFile(hang1, n);
				SapXepTangDanID(hang1, n);
				printf("Type ID to search: ");
				scanf("%s", &ID);
				int search_result = IDBinarySearch(hang1, n, ID);
				if (search_result != -1)
				{
					XuatTTHang(hang1 + search_result, search_result + 1);
					break;
				}
				else
					printf("\nCan't find this ID");
				break;
			}
			}
			printf("\n-----------------------------------------------------------------\n");
			break;
		}

		case 8:
		{
			printf("\n-----------------------------------------------------------------\n");
			if (AreYouSureToDeleteData())
			{
				ResetData();
				printf("Reset Successfully!");
			}
			printf("\n-----------------------------------------------------------------\n");
			break;
		}

		case 9:
			break;

		default:
			printf("\nInvalid input");
			break;
		}
	} while (user != 9);
}

int main()
{
	system("cls");
	Menu();

	return 0;
}
