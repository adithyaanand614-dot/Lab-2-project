#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h> // for random number generation

// ---------------- Global Variables ----------------

// Admin password
int admin_pass = 12345;

// Ingredient totals in the machine
int total_beans = 50;
int total_water = 900;
int total_milk = 1000;
int total_choccy = 500;
float total_sales = 0; // total money earned

// Espresso recipe and price
int esp_beans = 8;
int esp_water = 30;
int esp_milk = 0;
int esp_choccy = 0;
float esp_price = 3.5;

// Cappuccino recipe and price
int capp_beans = 8;
int capp_water = 30;
int capp_milk = 70;
int capp_choccy = 0;
float capp_price = 4.5;

// Mocha recipe and price
int mocha_beans = 8;
int mocha_water = 39;
int mocha_milk = 160;
int mocha_choccy = 30;
float mocha_price = 5.5;

// ---------------- Function Definitions ----------------

// Display ingredient levels if any are low (<20% of starting)
void check_low_ingredients()
{
    printf("\n--- Ingredient Status ---\n");
    if (total_beans < 10)
        printf("Low on beans (%d remaining)\n", total_beans);
    if (total_water < 200)
        printf("Low on water (%d ml remaining)\n", total_water);
    if (total_milk < 200)
        printf("Low on milk (%d ml remaining)\n", total_milk);
    if (total_choccy < 50)
        printf("Low on chocolate (%d g remaining)\n", total_choccy);
    printf("--------------------------\n");
}

// Displays the current coffee menu and availability
void print_menu()
{
    printf("\n--- Coffee Menu ---\n");

    if (total_beans < esp_beans || total_water < esp_water)
        printf("Espresso Unavailable: Insufficient Ingredients\n");
    else
        printf("Espresso : %.2f AED\n", esp_price);

    if (total_beans < capp_beans || total_water < capp_water || total_milk < capp_milk)
        printf("Cappuccino Unavailable: Insufficient Ingredients\n");
    else
        printf("Cappuccino : %.2f AED\n", capp_price);

    if (total_beans < mocha_beans || total_water < mocha_water || total_milk < mocha_milk || total_choccy < mocha_choccy)
        printf("Mocha Unavailable: Insufficient Ingredients\n");
    else
        printf("Mocha : %.2f AED\n", mocha_price);
}

// Handles coffee purchase by the consumer
void order()
{
    print_menu();

    int choice = 0;
    float coin_used = 0.0f;
    float money_entered = 0.0f;

    printf("Enter your choice (1: Espresso, 2: Cappuccino, 3: Mocha): ");
    scanf("%d", &choice);

    // ----- Option 1: Espresso -----
    if (choice == 1) {
        printf("Espresso selected. Please make payment with 1 AED and 0.5 AED coins only\n");
        while (money_entered < esp_price) {
            printf("Enter coin (1 or 0.5): ");
            scanf("%f", &coin_used);
            if (coin_used == 0.5 || coin_used == 1)
                money_entered += coin_used;
            else
                printf("Invalid coin. Use only 1 AED or 0.5 AED.\n");
        }

        total_beans -= esp_beans;
        total_water -= esp_water;
        total_sales += esp_price;

        printf("Enjoy your Espresso!\n");
        check_low_ingredients(); // show ingredient status
    }

    // ----- Option 2: Cappuccino -----
    else if (choice == 2) {
        printf("Cappuccino selected. Please make payment with 1 AED and 0.5 AED coins only\n");
        while (money_entered < capp_price) {
            printf("Enter coin (1 or 0.5): ");
            scanf("%f", &coin_used);
            if (coin_used == 0.5 || coin_used == 1)
                money_entered += coin_used;
            else
                printf("Invalid coin. Use only 1 AED or 0.5 AED.\n");
        }

        total_beans -= capp_beans;
        total_water -= capp_water;
        total_milk -= capp_milk;
        total_sales += capp_price;

        printf("Enjoy your Cappuccino!\n");
        check_low_ingredients(); // show ingredient status
    }

    // ----- Option 3: Mocha -----
    else if (choice == 3) {
        printf("Mocha selected. Please make payment with 1 AED and 0.5 AED coins only\n");
        while (money_entered < mocha_price) {
            printf("Enter coin (1 or 0.5): ");
            scanf("%f", &coin_used);
            if (coin_used == 0.5 || coin_used == 1)
                money_entered += coin_used;
            else
                printf("Invalid coin. Use only 1 AED or 0.5 AED.\n");
        }

        total_beans -= mocha_beans;
        total_water -= mocha_water;
        total_milk -= mocha_milk;
        total_choccy -= mocha_choccy;
        total_sales += mocha_price;

        printf("Enjoy your Mocha!\n");
        check_low_ingredients(); // show ingredient status
    }

    else {
        printf("Invalid choice.\n");
    }
}

// Admin-only mode for operator management
void admin_mode()
{
    int entered_pass = 0;
    int admin_choice = -1;

    printf("Please enter admin password: ");
    scanf("%d", &entered_pass);

    if (entered_pass == admin_pass) {
        srand(time(NULL)); // seed random generator

        do {
            printf("\n--- Admin Menu ---\n");
            printf("1: Display ingredients and total sales\n");
            printf("2: Replenish ingredients (randomly 1–20 units)\n");
            printf("3: Change coffee price\n");
            printf("0: Exit Admin Mode\n");
            printf("Enter choice: ");
            scanf("%d", &admin_choice);

            // Option 1: Display quantities
            if (admin_choice == 1) {
                printf("\nBeans: %d\nWater: %d\nMilk: %d\nChocolate: %d\nSales: %.2f AED\n",
                       total_beans, total_water, total_milk, total_choccy, total_sales);
            }

            // Option 2: Randomly replenish ingredients
            else if (admin_choice == 2) {
                int add_beans = rand() % 20 + 1;
                int add_water = rand() % 20 + 1;
                int add_milk = rand() % 20 + 1;
                int add_choccy = rand() % 20 + 1;

                total_beans += add_beans;
                total_water += add_water;
                total_milk += add_milk;
                total_choccy += add_choccy;

                printf("\nReplenished: Beans +%d, Water +%d, Milk +%d, Chocolate +%d\n",
                       add_beans, add_water, add_milk, add_choccy);
            }

            // Option 3: Change drink prices
            else if (admin_choice == 3) {
                int which_price;
                printf("Which coffee price do you want to change?\n");
                printf("1: Espresso (%.2f)\n2: Cappuccino (%.2f)\n3: Mocha (%.2f)\n",
                       esp_price, capp_price, mocha_price);
                scanf("%d", &which_price);

                if (which_price == 1) {
                    printf("Enter new Espresso price: ");
                    scanf("%f", &esp_price);
                } else if (which_price == 2) {
                    printf("Enter new Cappuccino price: ");
                    scanf("%f", &capp_price);
                } else if (which_price == 3) {
                    printf("Enter new Mocha price: ");
                    scanf("%f", &mocha_price);
                }
            }

        } while (admin_choice != 0);
    } else {
        printf("Incorrect password.\n");
    }
}

// ---------------- Main Program ----------------
int main(void)
{
    int main_choice;

    while (1) {
        printf("\n=== Coffee Vending Machine ===\n");
        printf("1. Purchase a Product\n");
        printf("2. Admin Mode\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &main_choice);

        if (main_choice == 1)
            order();
        else if (main_choice == 2)
            admin_mode();
        else if (main_choice == 3) {
            printf("Exiting program. Goodbye!\n");
            break;
        } else
            printf("Invalid choice. Try again.\n");
    }

    return 0;
}

