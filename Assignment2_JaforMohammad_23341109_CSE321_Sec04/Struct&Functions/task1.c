#include <stdio.h>

struct Item {
    int quantity;
    float unit_price;
};

int main() {
    struct Item paratha, vegetables, mineral_water;

    printf("Quantity Of Paratha: ");
    scanf("%d", &paratha.quantity);
    printf("Unit Price: ");
    scanf("%f", &paratha.unit_price);

    printf("Quantity Of Vegetables: ");
    scanf("%d", &vegetables.quantity);
    printf("Unit Price: ");
    scanf("%f", &vegetables.unit_price);

    printf("Quantity Of Mineral Water: ");
    scanf("%d", &mineral_water.quantity);
    printf("Unit Price: ");
    scanf("%f", &mineral_water.unit_price);

    int num_people;
    printf("Number of People: ");
    scanf("%d", &num_people);

    float total_bill = (paratha.quantity * paratha.unit_price) +
                      (vegetables.quantity * vegetables.unit_price) +
                      (mineral_water.quantity * mineral_water.unit_price);

    float amount_per_person = total_bill / num_people;

    printf("Individual people will pay: %.2f tk\n", amount_per_person);

    return 0;
}
