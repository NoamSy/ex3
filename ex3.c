/******************
Name: Noam Sayada
ID: 216308825
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};
//this function will set the total sales of a brand in each car type
void insertDailySales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
    int carIndex, int suv, int sedan, int coupe, int gt, int days[NUM_OF_BRANDS])
{
    int day = days[carIndex];
    /*if (day >= DAYS_IN_YEAR) //check if we have a available day
    {
        printf("no more space for data");
        return;
    }*/

    if (carIndex >= NUM_OF_BRANDS || carIndex < 0) //check if index is a valid brand number
    {
        printf("This brand is not valid\n");
        return;
    }

    cube[day][carIndex][0] = suv; //apply the daily sales
    cube[day][carIndex][1] = sedan;
    cube[day][carIndex][2] = coupe;
    cube[day][carIndex][3] = gt;
    days[carIndex]++;


}
//check what brands from the smallest day need to get numbers;
int missingBrands(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{

    int unfilledAmount = 0;
    for (int brand = 0; brand < NUM_OF_BRANDS; ++brand)
    {
        if(cube[day][brand][0] == -1) //check if no numbers were assigned
        {
            if (unfilledAmount == 0) //check if we already found one, if so no need to printf the text again
            {
                printf("No data for brands %s", brands[brand]);
                unfilledAmount++;
            } else
            {
                printf(" %s", brands[brand]);
                unfilledAmount++;
            }
        }

    }
    printf("\n");
    return unfilledAmount;
}
//get the smallest day in which we have a brand that doesnt have numbers set
//i realised this function is useless after implementing it in almost every function im using...
//yet it still works so i still use it
int getSmallestDay(int days[NUM_OF_BRANDS])
{
    int smallest = days[0];
    for (int q = 0; q < NUM_OF_BRANDS; ++q)
    {
        if (smallest > days[q])
            smallest = days[q];
    }
    return smallest;
}
void insertBrandData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS])
{
    int changed [NUM_OF_BRANDS] = {0};
    int checkData = 0;
    int smallestDay = getSmallestDay(days);
    do
    {
        checkData = missingBrands(cube, smallestDay);
        if (checkData > 0)
        {
            printf("Please complete the data\n");
            int carIndex, suv, sedan, coupe, gt;
            scanf("%d", &carIndex);
            if(changed[carIndex] !=0)
            {
                //check if nubmers are already assigned(for addAll),
                //i am checking only for 0 as if it is assigned, every other is also assigned
                printf("This brand is not valid\n");
            }
            else{
            scanf("%d %d %d %d", &suv, &sedan, &coupe, &gt);
            insertDailySales(cube, carIndex, suv,  sedan,  coupe,  gt,  days);
        }
            changed[carIndex] = 1;
        }
    } while (checkData != 0);

}


//functions for stats
//function that returns total sales for a specific day.
int totalSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    int totalSales = 0;
    day--;
    for (int type = 0; type < NUM_OF_TYPES; ++type)
    {
        for (int brand = 0; brand < NUM_OF_BRANDS; ++brand)
        {
            if(cube[day][brand][type] == -1)
                break;
            totalSales += cube[day][brand][type];
        }
    }
    return totalSales;
}
//functions that will check which brand sold the most
void mostSoldBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    int mostSold = 0;
    int mostSoldSum = 0;
    day--;
    for (int brand = 0; brand < NUM_OF_BRANDS; ++brand)
        //go over all brands and check in which brand sum of types is biggest
    {
        int totalBrandSales = 0;
        for (int type = 0; type < NUM_OF_TYPES; ++type) //go over all types in every single brand
        {
            if (cube[day][brand][type] == -1)
                break;
            totalBrandSales += cube[day][brand][type];
        }
        if (mostSoldSum < totalBrandSales) //if the last brand sum is smaller then this one, change the biggest sum
        {
            mostSoldSum = totalBrandSales;
            mostSold = brand;
        }
    }
    printf("The best sold brand with %d sales was %s\n", mostSoldSum, brands[mostSold]);
}
//function that checks the most sold type in a given day
void mostSoldType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    int mostSold = 0;
    int mostSoldSum = 0;
    day--;
    for (int type = 0; type < NUM_OF_TYPES; ++type)//go over all brands and check in which brand sum of types is biggest
    {
        int totalTypeSales = 0;
        for (int brand = 0; brand < NUM_OF_BRANDS; ++brand) //go over all types in every single brand
        {
            if (cube[day][brand][type] == -1)
                break;
            totalTypeSales += cube[day][brand][type];
        }
        if (mostSoldSum < totalTypeSales) //if the last brand sum is smaller then this one, change the biggest sum
        {
            mostSoldSum = totalTypeSales;
            mostSold = type;
        }
    }
    printf("The best sold type with %d sales was %s\n", mostSoldSum, types[mostSold]);
}


//functions for print
//function that will print all the sales
void printData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS])
{
    printf("*****************************************\n");
    for (int brand = 0; brand < NUM_OF_BRANDS; ++brand)
    {
        printf("Sales for %s:\n", brands[brand]); //print the brand
        for (int day = 0; day < getSmallestDay(days); ++day)//go trhough all days
        {
            if (cube[day][brand][0] == -1) //if no data in this type then theres no data in the entire day
                break;
            int userDay = day+1;
            printf("Day %d- ", userDay);//if the number is x in the array then we need to show it as x+1
            //since we start with 0
            for (int type = 0; type < NUM_OF_TYPES; ++type)
            {
                printf("%s: %d ", types[type], cube[day][brand][type]);//print all types
            }
            printf("\n");
        }
    }
    printf("*****************************************\n");

}

// functions for part insights
//function that will go through all days and check which is the best selling-brand, type, and most profitable day
void bestSelling(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS])
{
    int maxDay = getSmallestDay(days);//get the biggest day in which all brands have sales
    int mostProfitableDay = 0;;
    int mostProfitableDayPos = 0;
    int bestSellingType = 0;
    int bestSellingTypePos = 0;
    int bestSellingBrand = 0;
    int bestSellingBrandPos=0;
    //loop that will find the most profitable day
    for (int day = 0; day < maxDay; ++day)
    {
        int profitSum = 0;
        for (int brand = 0; brand < NUM_OF_BRANDS; ++brand)
        {
            for (int type = 0; type < NUM_OF_TYPES; ++type)
            {
                profitSum += cube[day][brand][type];
            }
        }
        if (profitSum > mostProfitableDay) //check if daily profit is higher then last day's profit
        {
            mostProfitableDay = profitSum;
            mostProfitableDayPos = day;
        }
    }
    //loop that will find the best selling brand
    for (int brand = 0; brand < NUM_OF_BRANDS; ++brand)
    {
        int brandSum = 0;
        for (int day = 0; day < maxDay; ++day)
        {
            for (int type = 0; type < NUM_OF_TYPES; ++type)
            {
                brandSum += cube[day][brand][type];
            }
        }
        if (brandSum > bestSellingBrand)
        {
            bestSellingBrand = brandSum;
            bestSellingBrandPos = brand;
        }
        
    }
    //loop that will find the best selling type
    for (int type = 0; type < NUM_OF_TYPES; ++type)
    {
        int sumType = 0;
        for (int day = 0; day < maxDay; ++day)
        {
            for (int brand = 0;  brand < NUM_OF_BRANDS; ++brand)
            {
                sumType += cube[day][brand][type];
            }
        }
        if (sumType > bestSellingType) //check if sum of current type is bigger then types before
        {
            bestSellingType = sumType;
            bestSellingTypePos = type;
        }
    }
    mostProfitableDayPos++;
    printf("The best-selling brand overall is %s: %d$\n", brands[bestSellingBrandPos], bestSellingBrand);
    printf("The best-selling type of car is %s: %d$\n", types[bestSellingTypePos], bestSellingType);
    printf("The most profitable day was day number %d: %d$\n", mostProfitableDayPos, mostProfitableDay);
}

//functiosn for insights
void averageDelta(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS])
{
    int maxDay = getSmallestDay(days); //get biggest day that has data

    for (int brand = 0; brand < NUM_OF_BRANDS; ++brand)
    {
        int sumDelta = 0;
        for (int day = 1; day < maxDay; ++day)
        {
            for (int type = 0; type < NUM_OF_TYPES; ++type)
            {
                //sum up all the difference between the day and the one before
                sumDelta +=cube[day][brand][type]-cube[day-1][brand][type];
            }

        }
        //take the entire Sum of the brand and divide by the maximum day minus 1
        //minus one because we only do sumdelta for maxday-1 days.
        float averageData;
        //since we cannot divide with zero, if maxday is equal to one then we will set the averagedata to 0
        if (maxDay != 1)
            averageData =  (float) sumDelta/ (float) (maxDay-1);
        else
            averageData = 0;
        printf("Brand: %s, Average Delta: %.6f\n", brands[brand],  averageData);

    }
}
void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}


int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    for (int i = 0; i < DAYS_IN_YEAR; ++i) //set every array object to -1
    {
        for (int j = 0; j < NUM_OF_BRANDS; ++j)
        {
            for (int m = 0; m < NUM_OF_TYPES; ++m)
            {
                cube[i][j][m] = -1;
            }
        }
    }
    int days[NUM_OF_BRANDS] = {0,0 ,0 ,0,0};
    int choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice)
        {
        case addOne:
            int carIndex, suv, sedan, coupe, gt;
            printf("brand name:\n");
            scanf("%d", &carIndex);
            scanf("%d %d %d %d", &suv, &sedan, &coupe, &gt);
            insertDailySales(cube, carIndex, suv,  sedan,  coupe,  gt,  days);
            break;

        case addAll:{
            insertBrandData(cube, days);
            break;
        }
        case stats:
            {
                int chosenDay;
                do
                {
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &chosenDay);
                    if (chosenDay<365 && chosenDay<=getSmallestDay(days) && chosenDay>0)
                    {
                        printf("In day number %d:\n", chosenDay);
                        break;
                    }
                    printf("Please enter a valid day.\n");

                } while(1);
                printf("The sales total was %d\n", totalSales(cube, chosenDay));
                mostSoldBrand(cube, chosenDay);
                mostSoldType(cube, chosenDay);
                break;
            }
        case print:
            {
            printData(cube, days);
            break;
            }
        case insights:
        {
        bestSelling(cube, days);
        break;
        }
        case deltas:
            {

            averageDelta(cube, days);
            break;

            }

            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}


