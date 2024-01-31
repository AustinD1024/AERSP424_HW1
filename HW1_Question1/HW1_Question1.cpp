// HW1_Question1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <array>
#include <numeric>
#include <iomanip>



int main()
{
	//AirplaneEW
	double AirplaneEW;
	std::cout << "Enter the Airplane empty weight (pounds): ";
	std::cin >> AirplaneEW;
	std::cout << "\n\n";

	double AirplaneEW_Moment;
	std::cout << "Enter the Airplane empty-weight moment (pounds-inches): ";
	std::cin >> AirplaneEW_Moment;
	std::cout << "\n\n";


	//FrontSeatOccupants
	int FrontSeatOccupants;
	std::cout << "Enter number of front seat occupants: ";
	std::cin >> FrontSeatOccupants;
	std::cout << "\n\n";

	//Front Seat Passenger Weights
	/*Got idea for line below from
	https ://stackoverflow.com/questions/28625465/c-creating-an-array-with-a-size-entered-by-the-user
	Ask TA/Instructor Question, says you have to delete the memory??
	*/
	double* FrontSeatWeights = new double[FrontSeatOccupants];


	for (int i = 0; i < FrontSeatOccupants; i++)
	{
		std::cout << "Enter weight of front seat occupant " << i + 1 << " (pounds): ";
		std::cin >> FrontSeatWeights[i];
		std::cout << "\n\n";
	}

	double sum1 = 0;
	double FrontSeatPassengerTotalWeight = std::accumulate(FrontSeatWeights, FrontSeatWeights + FrontSeatOccupants, sum1);

	double FrontSeatMomentArm;
	std::cout << "Enter the front seat moment arm (inches): ";
	std::cin >> FrontSeatMomentArm;
	std::cout << "\n\n";

	


	//RearSeatOccupants
	int RearSeatOccupants;
	std::cout << "Enter number of rear seat occupants: ";
	std::cin >> RearSeatOccupants;
	std::cout << "\n\n";

	/*	Got idea for line below (double* RearSeatWeights = new double[RearSeatOccupants];) from
		https ://stackoverflow.com/questions/28625465/c-creating-an-array-with-a-size-entered-by-the-user
		Ask TA/Instructor Question, says you have to delete the memory??	*/
	double* RearSeatWeights = new double[RearSeatOccupants];


	for (int i = 0; i < RearSeatOccupants; i++)
	{
		std::cout << "Enter weight of rear seat occupant " << i + 1 << " (pounds): ";
		std::cin >> RearSeatWeights[i];
		std::cout << "\n\n";
	}

	double sum2 = 0;
	double RearSeatPassengerTotalWeight = std::accumulate(RearSeatWeights, RearSeatWeights + RearSeatOccupants, sum2);

	double RearSeatMomentArm;
	std::cout << "Enter the rear seat moment arm (inches): ";
	std::cin >> RearSeatMomentArm;
	std::cout << "\n\n";

	

	//Gallons of Fuel
	double GallonsUsableFuel;
	std::cout << "Enter the number of gallons of usable fuel (gallons): ";
	std::cin >> GallonsUsableFuel;
	std::cout << "\n\n";

	double UsableFuelWeight;
	std::cout << "Enter the usable fuel weight per gallon (pounds): ";
	std::cin >> UsableFuelWeight;
	std::cout << "\n\n";

	double TotalFuelWeight = GallonsUsableFuel * UsableFuelWeight;
	double OriginalFuelWeight = TotalFuelWeight;

	double FuelTankMomentArm;
	std::cout << "Enter the fuel tank moment arm: ";
	std::cin >> FuelTankMomentArm;
	std::cout << "\n\n";


	//Baggage
	double BaggageWeight;
	std::cout << "Enter the baggage weight (pounds): ";
	std::cin >> BaggageWeight;
	std::cout << "\n\n";

	double BaggageMomentArm;
	std::cout << "Enter the baggage moment arm (inches): ";
	std::cin >> BaggageMomentArm;
	std::cout << "\n\n";

	

	//Calculate Gross Weight
	double GrossWeightConstant = AirplaneEW + FrontSeatPassengerTotalWeight + RearSeatPassengerTotalWeight + BaggageWeight;
	double GrossWeight =  GrossWeightConstant + TotalFuelWeight;
	double OriginalGW = GrossWeight;
	int MaxGrossWeight = 2950;

	//Calculate Moments
	double FrontSeatMoment = FrontSeatPassengerTotalWeight * FrontSeatMomentArm;
	double RearSeatMoment = RearSeatPassengerTotalWeight * RearSeatMomentArm;
	double FuelMoment = TotalFuelWeight * FuelTankMomentArm;
	double BaggageMoment = BaggageWeight * BaggageMomentArm;
	double MomentConstant = AirplaneEW_Moment + FrontSeatMoment + RearSeatMoment + BaggageMoment; //constant moment
	
	double TotalMoment;
	TotalMoment = MomentConstant + FuelMoment;

	//Find CG Location
	double CG = TotalMoment / GrossWeight;
	double MinCG = 82.1;
	double MaxCG = 84.7;

	//Output current Gross Weight and CG
	std::cout << "From the current design parameters:\n\n";
	std::cout << "		*The current Gross Weight is  " << std::fixed << std::setprecision(2) << GrossWeight << " pounds\n";
	std::cout << "		*The current C.G. is " << std::fixed << std::setprecision(1) << CG << " inches\n\n";

	//If design parameters are okay:
	
	if ((GrossWeight <= MaxGrossWeight) && (CG >= MinCG) && (CG <= MaxCG))
	{
		std::cout << "Therefore the design parameters are good!\n"
			"No fuel needs to be dumped.\n"
			"Gross Weight: " << std::fixed << std::setprecision(2) << GrossWeight << " pounds\n"
			"C.G. Location: " << std::fixed << std::setprecision(1) << CG << " inches\n";
	}
	
	//Adjust Fuel in order to correct parameters if design parameters are not okay
	else 
	{
		////This solution works but not the "logic" that is wanted
		bool Solution = false;
		////Possible Solution 1:
		//
		////CG Options
		//double CG_options;
		//double ReqFuelWeight;
		//double i = 0;
		//int j = 0;
		////Loop through all possible CG locations and see if there is a combination of fuel and gross weight to meet design specifications
		//for (i = MinCG; i < MaxCG; i += 0.01)	//loop through CG locations in increments of 0.01 inches
		//{
		//	CG_options = i;
		//	ReqFuelWeight = (CG_options * GrossWeightConstant - MomentConstant) / (FuelTankMomentArm - CG_options); //req fuel weight for CG
		//	TotalFuelWeight = ReqFuelWeight;
		//	FuelMoment = TotalFuelWeight * FuelTankMomentArm;
		//	GrossWeight = GrossWeightConstant + TotalFuelWeight;
		//	TotalMoment = MomentConstant + FuelMoment;
		//	CG = TotalMoment / GrossWeight;
		//	if (GrossWeight <= MaxGrossWeight && (ReqFuelWeight/UsableFuelWeight) > 0) //checks to make sure Gross weight is okay and Gallons of req fuel > 0
		//	{
		//		Solution = true;
		//		break;
		//	}
		//	j++;
		//}

		

		//Possible Solution 2: (Probably will delete)

		while (GrossWeight >= MaxGrossWeight || (CG < MinCG || CG > MaxCG))
		{
			if (CG < MinCG) //Need to remove fuel weight
			{
				GallonsUsableFuel -= 0.01;
				TotalFuelWeight = GallonsUsableFuel * UsableFuelWeight;
				FuelMoment = TotalFuelWeight * FuelTankMomentArm;
				GrossWeight = GrossWeightConstant + TotalFuelWeight;
				TotalMoment = MomentConstant + FuelMoment;
				CG = TotalMoment / GrossWeight;
				if (GallonsUsableFuel < 0)
				{
					Solution = false;
					break;
				}
			}
			if (CG > MaxCG) //Need to add fuel weight
			{
				if (GrossWeight >= MaxGrossWeight)
				{
					Solution = false;
					break;
				}
				GallonsUsableFuel += 0.01;
				TotalFuelWeight = GallonsUsableFuel * UsableFuelWeight;
				FuelMoment = TotalFuelWeight * FuelTankMomentArm;
				GrossWeight = GrossWeightConstant + TotalFuelWeight;
				TotalMoment = MomentConstant + FuelMoment;
				CG = TotalMoment / GrossWeight;

			}
		}
		if ((GrossWeight <= MaxGrossWeight) && (CG >= MinCG) && (CG <= MaxCG))
		{
			Solution = true;
		}

		//Output if there is a solution
		if (Solution == true)
		{

			
			std::cout << "Because the original design parameters did not meet the design limits,"
				" adjustments to the amount of gallons of fuel were made to meet the design limits.\n\n";
			double WeightChange = (TotalFuelWeight - OriginalFuelWeight) / UsableFuelWeight;
			if (WeightChange < 0)
			{
				std::cout << "There was a fuel adjustment of " << std::fixed << std::setprecision(2) << WeightChange << "gallons.\n\n";
			}
			else
			{
				std::cout << "There was a fuel adjustment of +" << WeightChange << " gallons.\n\n";
			}
			
			std::cout << "This resulted in the following new gross weight and C.G. Location:\n\n";
			std::cout << "		*New Gross Weight: " << std::fixed << std::setprecision(2) << GrossWeight << " pounds\n";
			std::cout << "		*New C.G. Location: " << std::fixed << std::setprecision(1) << CG << " inches\n";
			std::cout << "which satisfy the design requirements\n";

		}
		else
		{
			std::cout << "There is no possible design configuration that meets the specifications.";
		}


	}


	

	//Delete arrays from memory because of "new" usage
	delete[] FrontSeatWeights;
	delete[] RearSeatWeights;

	return 0;

}