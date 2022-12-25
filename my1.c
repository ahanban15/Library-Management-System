#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct date{
    int day;
    int month;
    int year;
}date;

typedef struct book{
    char code[10];
    char b_name[30];
    char s_name[30];
    struct date issue_date;
}book;

void display();
void add();
void search();
int countLeapYears(date d);
int getDifference(date dt1, date dt2);
void fine();

void display()
{
    FILE *fp;
    fp = fopen("libr.bin", "rb");
    book disbook = {0};

    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }

    int count = 0, flag = 0;
    while(fread(&disbook, sizeof(disbook), 1, fp))
    {
        printf("\nSr no.: %d\n", count + 1);
        printf("Book ID: %s\n", disbook.code);
        printf("Name of the Book: %s\n", disbook.b_name);
        printf("Name of the issuer: %s\n", disbook.s_name);
        printf("Date of Issue: %d/%d/%d\n", disbook.issue_date.day, disbook.issue_date.month, disbook.issue_date.year);
        count++;
        flag = 1;
    }

    if(flag == 0)
        printf("No Record Found!!!\n");

    fclose(fp);
}

void add()
{
    FILE *fp;
    fp = fopen("libr.bin", "ab+");
    book addbook = {0};

    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }

    printf("Enter the Book ID: ");
    scanf("%s", addbook.code);
    fflush(stdin);

    printf("Enter the name of the book: ");
    scanf("%s", addbook.b_name);
    fflush(stdin);

    printf("Enter the name of the issuer: ");
    scanf("%s", addbook.s_name);
    fflush(stdin);

    printf("Enter the date of issue: ");
    scanf("%d %d %d", &addbook.issue_date.day, &addbook.issue_date.month, &addbook.issue_date.year);
    fflush(stdin);

    fwrite(&addbook, sizeof(addbook), 1, fp);
    fclose(fp);
}

void search()
{
    FILE *fp;
    fp = fopen("libr.bin", "rb");
    book findbook = {0};

    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }

    int option = 0;
    printf("\nSearching Menu:\n");
    printf("1. Search by ID\n");
    printf("2. Search by name of book\n");
    printf("3. Search by name of issuer\n");
    printf("Choose an option from 1 to 3: ");
    scanf("%d", &option);

    switch(option)
    {
        case 1:
        {
            int found = 0;
            char b_id[30];
            fflush(stdin);
            printf("Enter the book ID: ");
            scanf("%s", b_id);

            while(fread(&findbook, sizeof(findbook), 1, fp))
            {
                if(!strcmp(findbook.code, b_id))
                {
                    printf("\nBook ID: %s\n", findbook.code);
                    printf("Name of the Book: %s\n", findbook.b_name);
                    printf("Name of the issuer: %s\n", findbook.s_name);
                    printf("Date of Issue: %d/%d/%d\n", findbook.issue_date.day, findbook.issue_date.month, findbook.issue_date.year);
                    found = 1;
                }
            }

            if(!found)
                printf("No such record found in the Library database\n");
            break;
        }

        case 2:
        {
            int found = 0;
            char book_name[30];
            fflush(stdin);

            printf("\nEnter the name of the book: ");
            scanf("%s", book_name);

            while(fread(&findbook, sizeof(findbook), 1, fp))
            {
                if(!strcmp(findbook.b_name, book_name))
                {
                    printf("\nBook ID: %s\n", findbook.code);
                    printf("Name of the Book: %s\n", findbook.b_name);
                    printf("Name of the issuer: %s\n", findbook.s_name);
                    printf("Date of Issue: %d/%d/%d\n", findbook.issue_date.day, findbook.issue_date.month, findbook.issue_date.year);
                    found = 1;
                }
            }

            if(!found)
                printf("No such record found in the Library database\n");
            break;
        }

        case 3:
        {
            int found = 0;
            char issuer_name[30];
            fflush(stdin);

            printf("Enter the name of the issuer: ");
            scanf("%s", issuer_name);

            while(fread(&findbook, sizeof(findbook), 1, fp))
            {
                if(!strcmp(findbook.s_name, issuer_name))
                {
                    printf("\nBook ID: %s\n", findbook.code);
                    printf("Name of the Book: %s\n", findbook.b_name);
                    printf("Name of the issuer: %s\n", findbook.s_name);
                    printf("Date of Issue: %d/%d/%d\n", findbook.issue_date.day, findbook.issue_date.month, findbook.issue_date.year);
                    found = 1;
                }
            }

            if(!found)
                printf("No such record found in the Library database\n");
            break;

        }

        fclose(fp);
    }
}

int countLeapYears(date d)
{
    int years = d.year;

    if (d.day <= 2)
        years--;

    return (years / 4 - years / 100 + years / 400);
}

const int monthDays[12]
    = { 31, 28, 31, 30, 31, 30,
       31, 31, 30, 31, 30, 31 };

int getDifference(date dt1, date dt2)
{
    long int n1 = dt1.year * 365 + dt1.day;

    for (int i = 0; i < dt1.month - 1; i++)
        n1 += monthDays[i];

    n1 += countLeapYears(dt1);

    long int n2 = dt2.year * 365 + dt2.day;
    for (int i = 0; i < dt2.month - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);

    return (n2 - n1);
}

void fine()
{
    printf("\nFine Calculation\n");
    printf("Rate of fine is Rs.1 per day after 15 days\n");

    FILE *fp;
    fp = fopen("libr.bin", "rb");

    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }

    book findbook = {0};
    date d_user;

    int found = 0;
    char b_id[30];
    fflush(stdin);

    printf("\nEnter the book ID: ");
    scanf("%s", b_id);

    while(fread(&findbook, sizeof(findbook), 1, fp))
    {
        if(!strcmp(findbook.code, b_id))
        {
            d_user = findbook.issue_date;
            found = 1;
        }
    }

    if(!found)
    {
        printf("No such record found in the Library database\n");
        exit(1);
    }

    date d;
    printf("Enter today's date: ");
    scanf("%d %d %d", &d.day, &d.month, &d.year);

    int diff = getDifference(d_user, d);
    if(diff > 15)
        printf("Fine: Rs. %d\n", diff - 15);
    else
        printf("No Fine\n");

    fclose(fp);
}

void drop()
{
    FILE *fp;
    FILE *tmp;

    fp = fopen("libr.bin", "rb");
    tmp = fopen("newlibr.bin", "wb");

    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }

    if(tmp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }

    int found = 0;
    char b_id[30];
    fflush(stdin);
    book findbook = {0};

    printf("\nEnter the book ID of the book to be deleted: ");
    scanf("%s", b_id);

    while(fread(&findbook, sizeof(findbook), 1, fp))
    {
        if(strcmp(findbook.code, b_id) != 0)
            fwrite(&findbook, sizeof(findbook), 1, tmp);
        else
            found = 1;
    }

    if(found == 1)
        printf("Required record deleted\n");
    else
        printf("No such record found in the Library database\n");

    fclose(fp);
    fclose(tmp);
    remove("libr.bin");
    rename("newlibr.bin", "libr.bin");
}

int main()
{
    printf("Welcome to Ahan's Library Database Management Systems!!!\n");
    int option = 0;
    do{
        printf("\nMenu:\n");
        printf("1. Display record\n");
        printf("2. Add a record\n");
        printf("3. Drop a record\n");
        printf("4. Search any book\n");
        printf("5. Calculate fine\n");
        printf("6. Exit\n");

        printf("\nChoose an option: ");
        scanf("%d", &option);

        switch(option)
        {
            case 1:
                display();
                break;

            case 2:
                add();
                break;

            case 3:
                drop();
                break;

            case 4:
                search();
                break;

            case 5:
                fine();
                break;

            case 6:
                printf("Exiting library database!!!\n");
                break;

            default:
                printf("Wrong option. Please enter again!!!\n");
        }
    }while(option != 6);

    return 0;
}
