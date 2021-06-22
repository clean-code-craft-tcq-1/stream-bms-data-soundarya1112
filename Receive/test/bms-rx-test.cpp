#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "bms-rx-data.h"
#include "stddef.h"
#include "string.h"


TEST_CASE("Test from Console - Valid data")
{
    float tempCalc, ChrgRateCalc;
    char str[100];
    strcpy(str,"{'temperature': 37.37, 'state_of_charge': 23.64, 'charge_rate': 0.35}");
    tempCalc = getParameterFromConsole(str,temperature);
    ChrgRateCalc = getParameterFromConsole(str,charge_rate);
    
    REQUIRE(fabs(tempCalc - 37.37)<0.01);
    REQUIRE(fabs(ChrgRateCalc - 0.35)<0.01);
    
}

TEST_CASE("Test from Console - Invalid temperature data")
{
    float tempCalc, ChrgRateCalc;
    char str[100];
    strcpy(str,"{'TemperAture': 37.37, 'state_of_charge': 23.64, 'charge_rate': 0.35}");
    tempCalc = getParameterFromConsole(str,temperature);
    ChrgRateCalc = getParameterFromConsole(str,charge_rate);
    
    REQUIRE(fabs(tempCalc - VALUE_NOTFOUND) <0.01);
    REQUIRE(fabs(ChrgRateCalc - 0.35)<0.01);
    
}

TEST_CASE("Test from Console - ChargeRate data invalid")
{
    float tempCalc, ChrgRateCalc;
    char str[100];
    strcpy(str,"{'TemperAture': 37.37, 'state_of_charge': 23.64, 'ChargeRate': 0.35}");
    tempCalc = getParameterFromConsole(str,temperature);
    ChrgRateCalc = getParameterFromConsole(str,charge_rate);
    
    REQUIRE(fabs(tempCalc - 37.37) <0.01);
    REQUIRE(fabs(ChrgRateCalc - VALUE_NOTFOUND)<0.01);
    
}
