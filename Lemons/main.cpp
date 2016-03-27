//
//  main.cpp
//  lemonade
//
//  Created by Herman Sollerman on 27/03/16.
//  Copyright © 2016 Herman Sollerman. All rights reserved.
//

#include <iostream>
using namespace std;

int main()
{
    int number_of_cases, number_of_days, lemon_per_cup, sugar_per_cup, cups_sold, lemon_price, total_cost=0, sugar_price, j, k;
    FILE *input;

    input = stdin;
    fscanf(input, "%d", &number_of_cases);
    
    for (k=1; k <= number_of_cases; k++)
    {
        fscanf(input, "%d %d %d", &number_of_days, &lemon_per_cup, &sugar_per_cup);
        int total_cups [number_of_days];
        int lprices [number_of_days];
        int sprices [number_of_days];
        
        int n=0;
        
        for (j=1; j<=number_of_days; j++)
        {
            fscanf(input, "%d %d %d", &cups_sold, &lemon_price, &sugar_price);
            total_cups[n] = cups_sold;
            lprices [n] = lemon_price;
            sprices [n] = sugar_price;
            ++n;
        }
        int cheap_lemon = lprices[0];
        int lemons_to_buy = total_cups[0]*lemon_per_cup;
        for (int i=1; i<number_of_days; i++)
        {
            if (cheap_lemon<=lprices[i])
                lemons_to_buy += total_cups[i]*lemon_per_cup;
            else
            {
                total_cost += lemons_to_buy*cheap_lemon;
                cheap_lemon=lprices[i];
                lemons_to_buy=total_cups[i]*lemon_per_cup;
            }
            if (i==number_of_days-1)
                total_cost += lemons_to_buy*cheap_lemon;
        }
        int cheap_sugar = sprices[0];
        double sugar_to_buy = double (total_cups[0])*double (sugar_per_cup)/80;
        for (int i=1; i<number_of_days; i++)
        {
            if (cheap_sugar<=sprices[i])
                sugar_to_buy += double(total_cups[i])*double(sugar_per_cup)/80;
            else
            {
                if(sugar_to_buy + 0.99 >= int(sugar_to_buy))
                    total_cost += (int(sugar_to_buy)+1)*cheap_sugar;
                else
                    total_cost += int(sugar_to_buy)*cheap_sugar;
                cheap_sugar=sprices[i];
                sugar_to_buy-=int(sugar_to_buy);
                sugar_to_buy+=double (total_cups[i])*double (sugar_per_cup)/80;
            }
            if (i==number_of_days-1)
            {
                double cups_left=0;
                int smallest = sprices[0];
                for (int n=1; n<number_of_days; n++)                                    //Denna del blev väldigt messy...
                    if (sprices[n] < smallest)                                          //Syftet var att veta hur många
                        smallest = n;                                                   //kunder man behövde fixa socker
                if (smallest == sprices[0])                                             //till sista gången man handlar,
                    smallest = 0;                                                       //när sockret var allra billigast.
                /*sätter smallest till 0 här, för om den första dagen hade det 
                 billigaste sockret kommer värdet på smallest vara kostnaden på 
                 sockret, inte dagen det var billigast eftersom
                 initialisationen fortfarande gäller */                                 //Därför var man först tvungen att
                for (int n=smallest; n<number_of_days; n++)                             //hitta minsta värdet i sprices
                    cups_left += total_cups [n];                                        //och sedan addera cups från alla
                                                                                        //dagar från den billiga dagen
                                                                                        //och framåt :)
                if(double (sugar_to_buy) <= double(cups_left)*double(sugar_per_cup)/80)
                    total_cost += (int(sugar_to_buy)+1)*cheap_sugar;
                else
                    total_cost += int(sugar_to_buy)*cheap_sugar;
                cups_left=0;
            }
        }

        printf("%d\n", total_cost);
        total_cost = 0;
    }

}
