//FIle name: Lab6.cpp
//Author: Kevin Cevallos
//Date: April 5, 2016
//Course: CISC 1600

#include <iostream>
using std::cout;
using std::endl;
using std::fixed;

#include <iomanip>
using std::setprecision;

#include <stdlib.h>

int houseOption();

//Arrays
int custom[5];
int bedNum[5];
int deckChoice[5];
int kitchenChoice[5];
int designChoice[5];
double squareFoot[5];
double baseCostNum[5];
double optionalFeatureCostNum[5];
double discountNum[5];
double finalNum[5];

//Custom house
int bedroomOption(int choice, const double size);
int deckOption(int choice);
int kitchenOption(int choice);
int designOption(int choice);

//Calculations
double calculateFinalDiscount(double feat);
double houseCost(double disc, double feat, double sqFt, const double PERCENT_PROFIT, const double STATE_TAX_RATE, const double COST_PER_SQUARE_FT);
int moreQuoteOption();

//Displays
void welcomeMessage();
void displaySummary(double baseCost, double featureCost, double discount, double total);
void displayReport();
void thankYouMessage();
        
//counter
int counter = 0;                                                                                                                                         
	int main()
	{
		//Variables
		//Optional Variables
		int houseChoice = 0;
		int additionalSpace = 0;
		int deck = 0;
		int deluxeCab = 0;
		int houseInterior = 0;

		//Constants
		const double BEDROOM_SIZE = 360;
		const double PERCENT_PROFIT = 0.25;
		const double STATE_TAX_RATE = 0.075;
		const double COST_PER_SQUARE_FT = 66.67;

		//Variables
		double houseSquareFootage = 3000;
		double optionalFeatures = 0;
		double discount = 0;
		
		double basicHomeCost;
		double totalHomeCost;
		
		while(counter < 5) 
		{
			welcomeMessage();
			houseChoice = houseOption();
			if(houseChoice == 1)
			{
				std::cout << "You have chosen a standard house." <<endl;
				totalHomeCost = houseCost(discount, optionalFeatures, houseSquareFootage, PERCENT_PROFIT, STATE_TAX_RATE, COST_PER_SQUARE_FT);
				basicHomeCost = houseSquareFootage * COST_PER_SQUARE_FT;
				displaySummary(basicHomeCost, optionalFeatures, discount, totalHomeCost);
			
				//Store
				custom[counter] = 1;	
				squareFoot[counter] = houseSquareFootage;
				baseCostNum[counter] = basicHomeCost;
				optionalFeatureCostNum[counter] = optionalFeatures;
				finalNum[counter] = totalHomeCost;
			}
			else
			{
				//Bedrooms
				std::cout << "Enter if you want 0,1, or 2, extra bedrooms." <<endl;
				std::cin >> additionalSpace;
				houseSquareFootage += bedroomOption(additionalSpace, BEDROOM_SIZE);
				//Deck
				std::cout << "Enter 1 if you want to keep the deck, or any other value if not."<<endl;
				std::cin >> deck;
				optionalFeatures -= deckOption(deck);
				//Cabinets & Counter tops
				std::cout << "Enter 1 for standard counter tops, enter any other value for deluxe caninets and counter tops." << endl;
				std::cin >> deluxeCab;
				optionalFeatures += kitchenOption(deluxeCab);
				//House Interior
				std::cout << "Enter 1 for hard wood floors, enter 2 for solid brass lighting fixtures, enter 3 for special plush carpeting, ceramic tile, and real wood paneling, enter 4 for a jacuzzi and sauna." << endl;
				std::cin >> houseInterior;
				optionalFeatures += designOption(houseInterior);			
				//Discount Calculation
				discount = calculateFinalDiscount(optionalFeatures);
				//Final Cost
				basicHomeCost = houseSquareFootage * COST_PER_SQUARE_FT;
				
				totalHomeCost = houseCost(discount, optionalFeatures, houseSquareFootage, PERCENT_PROFIT, STATE_TAX_RATE, COST_PER_SQUARE_FT);
				displaySummary(basicHomeCost, optionalFeatures, discount, totalHomeCost);
				
				//Store
				custom[counter] = 2;
				squareFoot[counter] = houseSquareFootage;
				baseCostNum[counter] = basicHomeCost;
				optionalFeatureCostNum[counter] = optionalFeatures;
				discountNum[counter] = discount;
				finalNum[counter] = totalHomeCost;
			}

			if(counter == 5)
			{
				std::cout << "This was your final attempt." << endl;
				return 0;
			}
			//Redo
			moreQuoteOption();
			discount = 0;
			optionalFeatures = 0;
			houseSquareFootage = 3000;
			counter++;		
		}

		return 0;	
	}

	void welcomeMessage()
	{
		std::cout << "Welcome.  Please choose what kind of house you want."  << endl;
	}

	int houseOption()
	{
		int choice;
		std::cout << "If you want a standard house enter 1, if not enter any other value." << endl;
		std::cin >> choice;
		return choice; 
	}

	int bedroomOption(int choice, const double size)
	{
		if(choice >= 3)
		{
			std::cout << "You have entered an invalid value. Default of no bedrooms is chosen." << endl;
			bedNum[counter] = 0;
			return 0;
		}
		bedNum[counter] = choice;
		return (choice * size); 
	}

	int deckOption(int choice)
	{
		if(choice != 1)
		{		
			deckChoice[counter] = 1;
			return 2000;
		}
		deckChoice[counter] = 0;
		return 0;
	}

	int kitchenOption(int choice)
	{
		if(choice != 1)
		{
			kitchenChoice[counter] = 1;
			return 20000;	
		}
		kitchenChoice[counter] = 0;
		return 0;		
	}

	int designOption(int choice)
	{
		designChoice[counter] = choice;
		if(choice == 1)
			return 10000;
		if(choice == 2)
			return 20000;
		if(choice == 3)
			return 25000;
		if(choice == 4)
			return 30000;
		
		std::cout << "Wrong input, default of 1 chosen." << endl;
		designChoice[counter] = 1;
		return 10000;
		
	}

	double calculateFinalDiscount(double feat)
	{
		double totalDiscount = feat;
		if(feat > 30000)
		{
			totalDiscount = feat * .1;
		}
		return totalDiscount;
	}

	double houseCost(double disc, double feat, double sqFt, const double PERCENT_PROFIT, const double STATE_TAX_RATE, const double COST_PER_SQUARE_FT)
	{
		double baseCost;
		double profit;
		double netHomeCost;
		double taxes;
		double totalCost;

		baseCost = sqFt * COST_PER_SQUARE_FT;
		profit = (baseCost + feat) * PERCENT_PROFIT;
		netHomeCost = baseCost + feat + profit - disc;
		taxes = netHomeCost * STATE_TAX_RATE;
		totalCost = netHomeCost + taxes;
		
		return totalCost;
	}

	void displaySummary(double baseCost, double featureCost, double discount, double total)
	{
		std::cout << "Base cost: $" << baseCost << endl;
		std::cout << "Optional feature cost: $" << featureCost << endl;
		std::cout << "Total discount: $" << discount << endl;
		std::cout << "Total cost is: $" << setprecision(2) << fixed << total << endl;
	}
	
	int moreQuoteOption()
	{
		int choice;
		std::cout << "If you would like to make another house enter 1, otherwise enter any other value." << endl;
		std::cin >> choice;
		if(choice != 1)
		{
			displayReport();
			exit(0);
		}
		return 0;
	}

	void thankYouMessage()
	{
		std::cout << "Thank you for using our program." << endl;
	}

	void displayReport()
	{
		int decision;

		for(int i = 0; i <= counter; i++)
		{
			if(custom[i] == 1)
			{
				std::cout<< "House: " << i + 1 << endl;
				std::cout<< "Basic Home" << endl;
				std::cout<< "House Square Footage: " << squareFoot[i] << endl;
				std::cout<< "Base Cost: $" << baseCostNum[i] << endl;
				std::cout<< "Optional Features: $" << optionalFeatureCostNum[i] << endl;
				std::cout<< "Total Cost: $" << finalNum[i] << endl;
			}
			else if(custom[i] == 2)
			{
				std::cout<< "House: " << i + 1 << endl;
				std::cout<< "Custom House" << endl;
				std::cout<< "This house has:" << endl;
				std::cout<< "Number of bedrooms: " << bedNum[counter] << endl;
				if(deckChoice[counter] == 0)
					std::cout<< "Deck included" <<endl;
				else
					std::cout<< "No deck" <<endl;
				
				if(kitchenChoice[counter] == 0)
					std::cout<< "Standard countertops" <<endl;
				else
					std::cout<< "Deluxe cabinets and countertops" <<endl;

				if(designChoice[counter] == 1)
					std::cout<< "Hardwood floors" <<endl;
				if(designChoice[counter] == 2)
					std::cout<< "Solid brass lighting" <<endl;
				if(designChoice[counter] == 3)
					std::cout<< "Plush carpeting, ceramic tile, and real wood paneling" <<endl;
				if(designChoice[counter] == 4)				
					std::cout<< "Jacuzzi and sauna" <<endl;
				
				std::cout<< "House Square Footage: " << squareFoot[i] << endl;
				std::cout<< "Base Cost: $" << baseCostNum[i] << endl;
				std::cout<< "Optional Features: $" << optionalFeatureCostNum[i] <<endl;
				std::cout<< "Discount: $" << discountNum[i] << endl;
				std::cout<< "Total Cost: $" << finalNum[i] << endl;
			}
		}

                std::cout<< "Choose which house you would like to purchase from 1 to " << counter + 1 << ", if you do not want to purchase a house enter 0." << endl;
		std::cin >> decision;
		if(decision == 0 || decision > counter+1)
		{
			thankYouMessage();
		}
		else
			std::cout << "Thank you for choosing house #" << decision << endl;	
	}

	

//End of Program


