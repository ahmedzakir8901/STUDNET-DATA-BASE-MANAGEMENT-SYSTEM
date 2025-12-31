#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct student {
    char first_name[20];
    char last_name[20];
    int roll_no;
    char Class[10];
    char vill[20];
    float per;
};

/* Function declarations */
void addstudent();
void viewstudents();
void searchstudent();
void deletestudent();

int main() {
    int choice = 0;

    while (choice != 5) {
        system("cls");
        printf("===== STUDENT DATABASE MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student Record\n");
        printf("2. View Student Records\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addstudent();
                break;
            case 2:
                viewstudents();
                break;
            case 3:
                searchstudent();
                break;
            case 4:
                deletestudent();
                break;
            case 5:
                printf("\nThank you for using the system!\n");
                break;
            default:
                printf("\nInvalid choice!");
        }
        getch();
    }
    return 0;
}

/* ---------------- ADD STUDENT ---------------- */
void addstudent() {
    FILE *fp;
    struct student s;
    char ch;

    fp = fopen("student.dat", "ab");
    if (fp == NULL) {
        printf("\nFile cannot be opened!");
        return;
    }

    do {
        system("cls");
        printf("----- ADD STUDENT -----\n");
        printf("First Name  : ");
        scanf("%s", s.first_name);
        printf("Last Name   : ");
        scanf("%s", s.last_name);
        printf("Roll No     : ");
        scanf("%d", &s.roll_no);
        printf("Class       : ");
        scanf("%s", s.Class);
        printf("ADDRESS     : ");
        scanf("%s", s.vill);
        printf("Percentage  : ");
        scanf("%f", &s.per);

        fwrite(&s, sizeof(struct student), 1, fp);
        printf("\nRecord added successfully!");

        printf("\nAdd another record? (y/n): ");
        scanf(" %c", &ch);

    } while (ch == 'y' || ch == 'Y');

    fclose(fp);
}

/* ---------------- VIEW STUDENTS ---------------- */
void viewstudents() {
    FILE *fp;
    struct student s;

    fp = fopen("student.dat", "rb");
    if (fp == NULL) {
        printf("\nNo records found!");
        return;
    }

    system("cls");
    printf("----- STUDENT RECORDS -----\n");

    while (fread(&s, sizeof(struct student), 1, fp)) {
        printf("\nName       : %s %s", s.first_name, s.last_name);
        printf("\nRoll No    : %d", s.roll_no);
        printf("\nClass      : %s", s.Class);
        printf("\nADDRESS    : %s", s.vill);
        printf("\nPercentage : %.2f", s.per);
        printf("\n---------------------------");
    }

    fclose(fp);
}

/* ---------------- SEARCH STUDENT ---------------- */
void searchstudent() {
    FILE *fp;
    struct student s;
    int roll, found = 0;

    fp = fopen("student.dat", "rb");
    if (fp == NULL) {
        printf("\nNo records found!");
        return;
    }

    system("cls");
    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll_no == roll) {
            printf("\n----- STUDENT FOUND -----");
            printf("\nName       : %s %s", s.first_name, s.last_name);
            printf("\nRoll No    : %d", s.roll_no);
            printf("\nClass      : %s", s.Class);
            printf("\nADDRESS    : %s", s.vill);
            printf("\nPercentage : %.2f", s.per);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nRecord not found!");

    fclose(fp);
}

/* ---------------- DELETE STUDENT ---------------- */
void deletestudent() {
    FILE *fp, *fp1;
    struct student s;
    int roll, found = 0;

    fp = fopen("student.dat", "rb");
    fp1 = fopen("temp.dat", "wb");

    if (fp == NULL) {
        printf("\nNo records found!");
        return;
    }

    system("cls");
    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll_no == roll) {
            found = 1;   // skip record
        } else {
            fwrite(&s, sizeof(struct student), 1, fp1);
        }
    }

    fclose(fp);
    fclose(fp1);

    if (found) {
        remove("student.dat");
        rename("temp.dat", "student.dat");
        printf("\nRecord deleted successfully!");
    } else {
        remove("temp.dat");
        printf("\nRecord not found!");
    }
}
