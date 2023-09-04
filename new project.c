//Departmental store Management System
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<windows.h>
#include<process.h>

#define MAX 20

//defining coordinate for using gotoxy function
COORD coord= {0,0};
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//structure for items
struct items
{
	char item_code[MAX];
	char item_name[MAX];
	int item_quantity;
	int item_rate;
};
struct items x,temp;

//structure for sold items
struct sitems
{
	char name[MAX];
	int qty;
	int rate;
	int amount;
};
struct sitems a;

//structure for bill
struct bill
{
	char particulars[MAX];
	int qnty;
	int r;
	int amt;
};
struct bill y;

//functions declared;
//funtion for start pages and title
void start();//start page
void l_title();//login title
void title();//title
void end();//exiting
void login();//for login username and password
void loading();//loading animation

//main menu functions
void main_menu();//main menu screen
void calculate_bill();//for calculating
void display_items();//for displaying existing data
void add_items();//for adding new data
void edit_items();//for editing existing data
void delete();//for deleting data
void search_items();//for searching data
void sold_items();//displaying sold data

void bill();//display bill0

//function to check item code
int c_code(char[]);//check new code
int check(char[]);//check code while edit

//functions under delete menu
void delete_items();//delete specific data
void delete_all();//delete all data
void sdelete();//delete sold items data

//functions under search menu
void search_code();//search using item code
void search_name();//search using item name
void search_qty();//search using quantity
void search_rate();//search using rate

void main()
{
	start();
}

void start()
{
	printf("\n\n\n\n\t\t************************************************************************************");
	printf("\n\t\t\t\t\t\t  WELCOME TO\n");
	printf("\n\t\t\t\t\t    XYZ DEPARTMENTAL STORE");
	printf("\n\t\t************************************************************************************");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\tPress any key to continue...");
	getch();
	login();
}

void l_title()
{
	printf("\n\n\n\n\t\t************************************************************************************");
	printf("\n\t\t\t\t\t    XYZ DEPARTMENTAL STORE");
	printf("\n\n\t\t\t\t\t\t    LOGIN");
	printf("\n\t\t************************************************************************************");
}

void title()
{
	printf("\n\n\n\n\t\t************************************************************************************");
	printf("\n\t\t\t\t\t    XYZ DEPARTMENTAL STORE");
	printf("\n\t\t************************************************************************************");
}

void end()
{
	exit(0);
}

void login()
{
		int try=0;
		int i,l;
		char ch;
		char username[10];
		char password[10];
		char def_username[10]="admin";
		char def_password[10]="admin";
		l = strlen(def_password);
		flag:
		system("cls");
		l_title();
		if(try<3)
		{
			printf("\n\n\t\t\t\t\t    Enter Username:: ");
			scanf("%s",&username);
			printf("\n\n\t\t\t\t\t    Enter Password:: ");
			for(i=0;i<l;i++)
 			{
  				ch = getch();
  				password[i] = ch;
  				ch = '*' ;
  				printf("%c",ch);
 			}
 			password[l] = '\0';
			if(strcmp(username,def_username) == 0 && strcmp(password,def_password) == 0)
			{
				loading();
			}
			else
			{
				try++;
				printf("\n\n\n\n\n\t\t\t\t    Incorrect Username or Password! Try Again!!\n");
				getch();
				goto flag;
			}
		}
		if(try>2)
		{
			printf("\n\n\n\n\n\n\n\t\t\t\t      Limit Crossed! Program Exiting!!");
			getch();
			end();
		}
		system("cls");
}

void loading()
{
    int r;
	gotoxy(44,20);
	printf("Please wait...Loading");
	gotoxy(26,22);
	for(r=0;r<=60;r++)
	{
		Sleep(10);
		printf("%c",219);
	}
	main_menu();
}

void main_menu()
{
	system("cls");
	int choice;	
	flag1:
	printf("\n\n\n\n\t\t************************************************************************************");
	printf("\n\t\t\t\t\t\t    MAIN MENU");
	printf("\n\t\t************************************************************************************");	
	printf("\n\n\t\t\t\t\t\t 1. Calculate Bill");
	printf("\n\t\t\t\t\t\t 2. Display All Items");
	printf("\n\t\t\t\t\t\t 3. Add Items");
	printf("\n\t\t\t\t\t\t 4. Edit Items");
	printf("\n\t\t\t\t\t\t 5. Delete Items");
	printf("\n\t\t\t\t\t\t 6. Search Items");
	printf("\n\t\t\t\t\t\t 7. Sold Items");
	printf("\n\t\t\t\t\t\t 8. Exit");
	printf("\n\n\t\t\t\t\t      Enter your choice(1-8):: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			calculate_bill();
			break;
		
		case 2:
			display_items();
			break;
			
		case 3:
			add_items();
			break;
		
		case 4:
			edit_items();
			break;
			
		case 5:
			delete();
			break;
			
		case 6:
			search_items();
			break;

		case 7:
			sold_items();
			break;
						
		case 8:
			end();
			break;
		
		default:
			printf("\n\t\t\t\t\t\t Invalid choice!");
			system("cls");
			goto flag1;
	};
	getch();
}

void calculate_bill()
{
	system("cls");
	title();
	gotoxy(46,8);
	printf("Calculate Bill");
	char c[MAX],ch='Y';
	int q,total=0,total2=0;
	int size=0;
	FILE *ftp,*fp,*fpt;
	ftp = fopen("data.txt","r+");
	fp  = fopen("sdata.txt","a");
	fpt = fopen("bill.txt","w");
	if(ftp == NULL)
	{
		main_menu();		
	}	
	else
	{
		while(ch == 'Y')
		{
			rewind(ftp);
			printf("\n\n\t\t\t\t\t   Enter item code: ");
			scanf("%s",&c);
			printf("\n\t\t\t\t\t   Enter quantity : ");
    		scanf("%d",&q);
    		while(fread(&x,sizeof(x),1,ftp)==1)
    		{
    			if(strcmp(x.item_code,c)==0)
    			{
    				total = q * x.item_rate;
    				printf("\n\t\tItem Code: %s",x.item_code);
    				printf("    Item Name: %s",x.item_name);
    				printf("\t  Buy Qty: %d",q);
    				printf("    Item Rate: %d",x.item_rate);
    				printf("\t    Amount: %d",total);
    				total2 = total2 + total;
    				size = sizeof(x);
    				x.item_quantity = x.item_quantity - q;
    				fseek(ftp,-size,SEEK_CUR);
					fwrite(&x,sizeof(x),1,ftp);
					fflush(stdin);
					//for sold items
					strcpy(a.name,x.item_name);
					a.qty = q;
					a.rate = x.item_rate;
					a.amount = total;
					fwrite(&a,sizeof(a),1,fp);
					fflush(stdin);
					//for bill
					strcpy(y.particulars,x.item_name);
					y.qnty = q;
					y.r = x.item_rate;
					y.amt = total;
					fwrite(&y,sizeof(y),1,fpt);
					fflush(stdin);
                	break;
				}	
			}	
			if(strcmp(x.item_code,c)!=0)
			{
				printf("\n\t\t\t\t\t   Item Doesn't Exist!!");
				getch();
			}
			printf("\n\n\t\t\t\t\t  Add More Items(Y/N)?: ");
			ch = toupper(getche());
		}
	}
	fclose(fp);
	fclose(ftp);
	fclose(fpt);
	getch();
	bill();
}

void bill()
{
	system("cls");
	title();
	int row=11,sn=1;
	int total;
	FILE *fp;
	fp = fopen("bill.txt","r");
	rewind(fp);
	gotoxy(50,8);
	printf("RECEIPT");
	gotoxy(17,10);
	printf("SN");
	gotoxy(25,10);
	printf("Particulars");
	gotoxy(50,10);
	printf("Quantity");
	gotoxy(71,10);
	printf("Rate");
	gotoxy(92,10);
	printf("Amount");
	gotoxy(25,25);
	printf("Total");
	gotoxy(50,27);
	printf("THANK YOU!!");
	while(fread(&y,sizeof(y),1,fp))
	{
		gotoxy(17,row);
		printf("%d",sn);
		gotoxy(25,row);
		printf("%s",y.particulars);
		gotoxy(50,row);
		printf("%d",y.qnty);
		gotoxy(71,row);
		printf("%d",y.r);
		gotoxy(92,row);
		printf("%d",y.amt);	
		total = total + y.amt;	
		sn++;
		row++;
	}
	gotoxy(92,25);
	printf("%d/-",total);
	fflush(stdin);
	fclose(fp);
	getch();
	main_menu();
}

void display_items()
{
	system("cls");
	title();
	FILE *ftp;
	ftp = fopen("data.txt","r");
	gotoxy(50,8);
	printf("ALL ITEMS");
	gotoxy(17,10);
	printf("Item Code");
	gotoxy(40,10);
	printf("Item Name");
	gotoxy(65,10);
	printf("Item Quantity");
	gotoxy(90,10);
	printf("Item Rate");
	int row = 11;
	while(fread(&x,sizeof(x),1,ftp))
	{
		gotoxy(17,row);
		printf("%s",x.item_code);
		gotoxy(40,row);
		printf("%s",x.item_name);
		gotoxy(65,row);
		printf("%d",x.item_quantity);
		gotoxy(90,row);
		printf("%d\n",x.item_rate);
		row++;
	}
	fclose(ftp);
	getch();
	main_menu();
}

void add_items()
{
	system("cls");
	title();
	int c=0;
	char y[MAX];
	char ch = 'Y';
	FILE *ftp;
	ftp = fopen("data.txt","a");
	if (ftp == NULL)
	{
		printf("Invalid!! Cannot open file!!");
		end();
	}
	else
	{
		flag3:
		printf("\n\n\t\t\t\t\t 1.Enter Item Code: ");
		scanf(" %[^\n]",&y);
		c=c_code(y);
		if(c==1)
		{
			strcpy(x.item_code,y);
			printf("\n\t\t\t\t\t 2.Enter Item Name: ");
			scanf(" %[^\n]",&x.item_name);
			strupr(x.item_name);
			printf("\n\t\t\t\t\t 3.Enter Item Quantity: ");
			scanf("%d",&x.item_quantity);
			printf("\n\t\t\t\t\t 4.Enter Item Rate: ");
			scanf("%d",&x.item_rate);
			fwrite(&x,sizeof(x),1,ftp);
			fclose(ftp);
		}
		else
		{
			printf("\n\t\t\t\t    Code Already Exists! Try Again!!");
			getch();
			goto flag3;
		}
	}
	flag2:
	printf("\n\n\t\t\t\t Do you want to enter more items(Y/N)?: ");
	ch = toupper(getche());
	if(ch == 'Y')
	{
		add_items();
	}
	else if(ch == 'N')
	{
		main_menu();
	}
	else
	{
		printf("\n\n\t\t\t\t\t Invalid Input!!");
		goto flag2;
	}
}

int c_code(char y[MAX])
{
	FILE *ftp;
    int flag=1;
    ftp=fopen("data.txt","r");
    rewind(ftp);
    while (fread(&x,sizeof(x),1,ftp))
    {
        if(strcmp(y,x.item_code)==0)
        {
            flag=0;
            break;
        }
    }
    fclose(ftp);
    return flag;
}

void edit_items()
{
    system("cls");
    title();
    int flag=0,choice;
    int size=0;
    char y[MAX];
    char ch;
    FILE *ftp;
    gotoxy(50,8);
    printf("EDIT DATA");
    gotoxy(47,10);
    printf("Enter Item Code: ");
    scanf("%s",&y);
    flag=check(y);
    if(flag==0)
    {
        ftp=fopen("data.txt","r+");
        rewind(ftp);
        while (fread(&x,sizeof(x),1,ftp))
        {
            if(strcmp(x.item_code,y)==0)
            {
           		gotoxy(17,12);
				printf("Item Code");
				gotoxy(40,12);
				printf("Item Name");
				gotoxy(65,12);
				printf("Item Quantity");
				gotoxy(90,12);
				printf("Item Rate");			
                gotoxy(17,13);
                printf("%s",x.item_code);
                gotoxy(40,13);
                printf("%s",x.item_name);
                gotoxy(65,13);
                printf("%d",x.item_quantity);
                gotoxy(90,13);
                printf("%d",x.item_rate);
                gotoxy(40,15);
                printf("Do you want to edit this record?(y/n): ");
                ch = toupper(getche());
                if(ch=='Y')
                {
                    gotoxy(47,17);
                    printf("1. Edit Item Name");
                    gotoxy(47,18);
                    printf("2. Edit Item Quantity");
                    gotoxy(47,19);
                    printf("3. Edit Item Rate");
                    flag1:
                    printf("\n\n\t\t\t\t\t    Enter your choice(1-3): ");
                    scanf("%d",&choice);
                    switch(choice)
                    {
                        case 1:
                        system("cls");
                        title();
                        gotoxy(50,8);
                        printf("EDIT NAME");
                        gotoxy(43,10);
                        printf("Enter New Item Name: ");
                        scanf(" %[^\n]",x.item_name);
                        strupr(x.item_name);
                        size=sizeof(x);
                        fseek(ftp,-size,SEEK_CUR);
                        fwrite(&x,sizeof(x),1,ftp);
                    	fflush(stdin);
                        break;
                        
                        case 2:
                        system("cls");
                        title();
                        gotoxy(48,8);
                        printf("EDIT QUANTITY");
                        gotoxy(41,10);
                        printf("Enter New Item Quantity: ");
                        scanf("%d",&x.item_quantity);
                        size=sizeof(x);
                        fseek(ftp,-size,SEEK_CUR);
                        fwrite(&x,sizeof(x),1,ftp);
                        fflush(stdin);
                        break;
                        
                        case 3:
                        system("cls");
                        title();
                        gotoxy(50,8);
                        printf("EDIT RATE");
                        gotoxy(43,10);
                        printf("Enter New Item Rate: ");
                        scanf("%d",&x.item_rate);
                        size=sizeof(x);
                        fseek(ftp,-size,SEEK_CUR);
                        fwrite(&x,sizeof(x),1,ftp);
                    	fflush(stdin);
                        break;
                        	
                        default:
                        	printf("\n\n\t\t\t\t\t\t Invalid Choice!!");
                        	getch();
                        	goto flag1;
                        	
                    }
                    gotoxy(45,13);
                    printf("--- Item Edited ---");
                    break;
                }
            }
        }
    }
    if (flag==1)
    {
        gotoxy(46,12);
        printf("Item doesn't exist!!");
        gotoxy(50,14);
        printf("TRY AGAIN!!");
        getch();
		edit_items();
    }
    getch();
    fclose(ftp);
    main_menu();
}

int check(char y[MAX])
{
    FILE *ftp;
    int flag=1;
    ftp=fopen("data.txt","r");
    rewind(ftp);
    while (fread(&x,sizeof(x),1,ftp))
    {
        if(strcmp(y,x.item_code)==0)
        {
            flag=0;
            break;
        }
    }
    fflush(stdin);
    fclose(ftp);
    return flag;
}

void delete()
{
	system("cls");
	title();
	int ch;
	gotoxy(49,8);
	printf("Delete Data");
	gotoxy(44,10);
	printf("1. Delete a Data");
	gotoxy(44,11);
	printf("2. Delete All Data");
	gotoxy(44,12);
	printf("3. Delete Sold Items Data");
	gotoxy(44,13);
	printf("4. Exit to Main Menu");
	gotoxy(44,15);
	printf("Enter your choice(1-4):");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			delete_items();
			break;
		
		case 2:
			delete_all();
			break;

		case 3:
			sdelete();
			break;
		
		case 4:
			main_menu();
			break;
			
		default:
			printf("\n\t\t\t\t\t\t Invalid choice!");
			getch();
			delete();
	}
}

void delete_items()
{
	system("cls");
	title();
	char dlt[MAX],ch;
	int found=0;
	FILE *ftp,*ftp1;
	ftp = fopen("data.txt","r");
	ftp1 = fopen("temp.txt","w");
	rewind(ftp);
	gotoxy(49,8);
	printf("Delete Items");
	gotoxy(47,10);
	printf("Enter Item Code:");
	scanf(" %[^\n]",dlt);
	if(ftp == NULL && ftp1 == NULL)
	{
		printf("Invalid!! Cannot open file!!");
		end();		
	}
	else
	{
		while(fread(&x,sizeof(x),1,ftp)==1)
		{
			if(strcmp(x.item_code,dlt)!=0)
			{
				fwrite(&x,sizeof(x),1,ftp1);
			}
			else
			{
				gotoxy(17,13);
				printf("Item Code");
				gotoxy(40,13);
				printf("Item Name");
				gotoxy(65,13);
				printf("Item Quantity");
				gotoxy(90,13);
				printf("Item Rate");
				gotoxy(17,14);
				printf("%s",x.item_code);
				gotoxy(40,14);
				printf("%s",x.item_name);
				gotoxy(65,14);
				printf("%d",x.item_quantity);
				gotoxy(90,14);
				printf("%d\n",x.item_rate);
				found = 1;
			}
		}
		if (found==0)
		{
			gotoxy(48,13);
			printf("Data Not Found!");
			getch();
			main_menu();
		}
		else
		{
			fclose(ftp);
			fclose(ftp1);
			remove("data.txt");
			rename("temp.txt","data.txt");
			gotoxy(43,19);
			printf("Data Deleted Successfully!");
			getch();
		}
	}
	flag:
	printf("\n\n\t\t\t\t Do you want to delete more items(Y/N)?: ");
	ch = toupper(getche());
	if(ch == 'Y')
	{
		delete_items();
	}
	else if(ch == 'N')
	{
		main_menu();
	}
	else
	{
		printf("\n\n\t\t\t\t\t Invalid Input!!");
		goto flag;
	}
}

void delete_all()
{
	system("cls");
	char ch;
	title();
	FILE *ftp,*ftp1;
	ftp = fopen("data.txt","r");
	ftp1 = fopen("temp.txt","w");
	if(ftp == NULL && ftp1 == NULL)
	{
		printf("Invalid!! Cannot open file!!");
		end();		
	}
	else
	{
		gotoxy(33,13);
		printf("Do you really want to delete all the data? (Y/N): ");
		ch = toupper(getche());
		if(ch == 'Y')
		{
			fclose(ftp);
			fclose(ftp1);
			remove("data.txt");
			rename("temp.txt","data.txt");
			gotoxy(43,18);
			printf("All Data Deleted Successfully!");
			getch();
		}
		else if(ch == 'N')
		{
			delete();
		}
		else
		{
			gotoxy(45,16);
			printf("Invalid Choice!! Try again!!");
			getch();
			delete();
		}
	}
	main_menu();
}

void sdelete()
{
	system("cls");
	char ch;
	title();
	FILE *ftp,*ftp1;
	ftp = fopen("sdata.txt","r");
	ftp1 = fopen("temp.txt","w");
	if(ftp == NULL && ftp1 == NULL)
	{
		printf("Invalid!! Cannot open file!!");
		end();		
	}
	else
	{
		gotoxy(30,13);
		printf("Do you really want to delete all the sales data? (Y/N): ");
		ch = toupper(getche());
		if(ch == 'Y')
		{
			fclose(ftp);
			fclose(ftp1);
			remove("sdata.txt");
			rename("temp.txt","sdata.txt");
			gotoxy(43,18);
			printf("All Data Deleted Successfully!");
			getch();
		}
		else if(ch == 'N')
		{
			delete();
		}
		else
		{
			gotoxy(45,16);
			printf("Invalid Choice!! Try again!!");
			getch();
			delete();
		}
	}
	main_menu();
}

void search_items()
{
	system("cls");
	int ch;
	flag:
	title();
	printf("\n\n\t\t\t\t\t        Search Data");
	printf("\n\n\t\t\t\t\t   1. Search by code");
	printf("\n\t\t\t\t\t   2. Search by name");
	printf("\n\t\t\t\t\t   3. Search by Quantity");
	printf("\n\t\t\t\t\t   4. Search by Rate");
	printf("\n\t\t\t\t\t   5. Exit to Main Menu");
	printf("\n\n\t\t\t\t\t   Enter your choice(1-5):");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			search_code();
			break;
			
		case 2:
			search_name();
			break;
			
		case 3:
			search_qty();
			break;
	
		case 4:
			search_rate();
			break;
					
		case 5:
			main_menu();
			break;
			
		default:
			printf("\n\t\t\t\t\t\t Invalid choice!");
			system("cls");
			goto flag;
	};
	getch();
}

void search_code()
{
	char sc[MAX],ch;
	int row=12;
	FILE *ftp;
	ftp = fopen("data.txt","r");
	rewind(ftp);
	system("cls");
	title();
	printf("\n\n\t\t\t\t\t     Enter item code: ");
	scanf(" %[^\n]",&sc);
	gotoxy(17,11);
	printf("Item Code");
	gotoxy(40,11);
	printf("Item Name");
	gotoxy(65,11);
	printf("Item Quantity");
	gotoxy(90,11);
	printf("Item Rate");
	while(fread(&x,sizeof(x),1,ftp)>0)
	{
		if(strcmp(x.item_code,sc)==0)
		{
			gotoxy(17,row);
			printf("%s",x.item_code);
			gotoxy(40,row);
			printf("%s",x.item_name);
			gotoxy(65,row);
			printf("%d",x.item_quantity);
			gotoxy(90,row);
			printf("%d\n",x.item_rate);
			break;
		}
	}
	fflush(stdin);
	fclose(ftp);
	flag:
	printf("\n\n\n\t\t\t\t Do you want to search more items(Y/N)?: ");
	ch = toupper(getche());
	if(ch == 'Y')
	{
		search_code();
	}
	else if(ch == 'N')
	{
		search_items();
	}
	else
	{
		printf("\n\n\t\t\t\t\t      Invalid Input!");
		goto flag;
	}			
	row++;
}

void search_name()
{
	char sn[MAX],ch;
	int row=12;
	FILE *ftp;
	ftp = fopen("data.txt","r");
	rewind(ftp);
	system("cls");
	title();
	printf("\n\n\t\t\t\t\t     Enter item name: ");
	scanf(" %[^\n]",&sn);
	strupr(sn);
	gotoxy(17,11);
	printf("Item Code");
	gotoxy(40,11);
	printf("Item Name");
	gotoxy(65,11);
	printf("Item Quantity");
	gotoxy(90,11);
	printf("Item Rate");
	gotoxy(17,row);
	while(fread(&x,sizeof(x),1,ftp))
	{
		if(strcmp(x.item_name,sn)==0)
		{
			gotoxy(17,row);
			printf("%s",x.item_code);
			gotoxy(40,row);
			printf("%s",x.item_name);
			gotoxy(65,row);
			printf("%d",x.item_quantity);
			gotoxy(90,row);
			printf("%d\n",x.item_rate);
			row++;
		}
	}
	fflush(stdin);
	fclose(ftp);
	flag:
	printf("\n\n\n\t\t\t\t Do you want to search more items(Y/N)?: ");
	ch = toupper(getche());
	if(ch == 'Y')
	{
		search_name();
	}
	else if(ch == 'N')
	{
		search_items();
	}
	else
	{
		printf("\n\n\t\t\t\t\t      Invalid Input!");
		goto flag;
	}			
	row++;
}

void search_qty()
{
	char ch;
	int max,min;
	int row=13;
	FILE *ftp;
	ftp = fopen("data.txt","r");
	rewind(ftp);
	system("cls");
	title();
	printf("\n\n\t\t\t\t\t     Enter low term:  ");
	scanf("%d",&min);
	printf("\n\t\t\t\t\t     Enter high term: ");
	scanf("%d",&max);
	gotoxy(17,12);
	printf("Item Code");
	gotoxy(40,12);
	printf("Item Name");
	gotoxy(65,12);
	printf("Item Quantity");
	gotoxy(90,12);
	printf("Item Rate");
	gotoxy(17,row);
	while(fread(&x,sizeof(x),1,ftp))
	{
		if(x.item_quantity>=min && x.item_quantity<=max)
		{
			gotoxy(17,row);
			printf("%s",x.item_code);
			gotoxy(40,row);
			printf("%s",x.item_name);
			gotoxy(65,row);
			printf("%d",x.item_quantity);
			gotoxy(90,row);
			printf("%d\n",x.item_rate);
			row++;
		}
	}
	fclose(ftp);
	flag:
	printf("\n\n\n\t\t\t\t Do you want to search more items(Y/N)?: ");
	ch = toupper(getche());
	if(ch == 'Y')
	{
		search_qty();
	}
	else if(ch == 'N')
	{
		search_items();
	}
	else
	{
		printf("\n\n\t\t\t\t\t      Invalid Input!");
		goto flag;
	}			
	row++;
}

void search_rate()
{
	char ch;
	int hgr,lwr;
	int row=13;
	FILE *ftp;
	ftp = fopen("data.txt","r");
	rewind(ftp);
	system("cls");
	title();
	printf("\n\n\t\t\t\t\t     Enter low rate:  ");
	scanf("%d",&lwr);
	printf("\n\t\t\t\t\t     Enter high rate: ");
	scanf("%d",&hgr);
	gotoxy(17,12);
	printf("Item Code");
	gotoxy(40,12);
	printf("Item Name");
	gotoxy(65,12);
	printf("Item Quantity");
	gotoxy(90,12);
	printf("Item Rate");
	gotoxy(17,row);
	while(fread(&x,sizeof(x),1,ftp))
	{
		if(x.item_rate>=lwr && x.item_rate<=hgr)
		{
			gotoxy(17,row);
			printf("%s",x.item_code);
			gotoxy(40,row);
			printf("%s",x.item_name);
			gotoxy(65,row);
			printf("%d",x.item_quantity);
			gotoxy(90,row);
			printf("%d\n",x.item_rate);
			row++;
		}
	}
	fclose(ftp);
	flag:
	printf("\n\n\n\t\t\t\t Do you want to search more items(Y/N)?: ");
	ch = toupper(getche());
	if(ch == 'Y')
	{
		search_rate();
	}
	else if(ch == 'N')
	{
		search_items();
	}
	else
	{
		printf("\n\n\t\t\t\t\t      Invalid Input!");
		goto flag;
	}			
	row++;
}

void sold_items()
{
	system("cls");
	title();
	int sn=1;
	FILE *ftp;
	ftp = fopen("sdata.txt","r");
	gotoxy(50,8);
	printf("SOLD ITEMS");
	gotoxy(17,10);
	printf("SN");
	gotoxy(24,10);
	printf("Item Name");
	gotoxy(45,10);
	printf("Item Quantity");
	gotoxy(73,10);
	printf("Item Rate");
	gotoxy(93,10);
	printf("Amount");
	int row = 11;
	while(fread(&a,sizeof(a),1,ftp))
	{
		gotoxy(17,row);
		printf("%d",sn);
		gotoxy(24,row);
		printf("%s",a.name);
		gotoxy(45,row);
		printf("%d",a.qty);
		gotoxy(73,row);
		printf("%d",a.rate);
		gotoxy(93,row);
		printf("%d",a.amount);
		row++;
		sn++;
	}
	fflush(stdin);
	fclose(ftp);
	getch();
	main_menu();
}
