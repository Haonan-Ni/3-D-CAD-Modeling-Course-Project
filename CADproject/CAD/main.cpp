#include "Half_Edge_DS.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	cout << "******************************3D CAD Modeling Course Project******************************\n " << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------\n " << endl;
	cout << "The default program has four sections. Section 1, 2, 3 creates three individual quadrilaterals in 2-D x-z plane, which means 4 vertices in each section.\n " << endl;
	cout << "Section 4 uses the 'sweep' function to extrude in the third dimension to create 3-D solid based on the planar quadrilateral.\n " << endl;
	cout << "Section 5 employs the 'kfmrh' function to make ring holes on the 3-D solid model.\n " << endl;
	cout << "Now, there are three options:" << "\n" << endl;
	cout << "1.Input 'd' to use default points for demonstration in every steps." << "\n" << endl;
	cout << "2.Input 's' to skip all steps and automatically produce default demonstration data." << "\n" << endl;
	cout << "3.Input 'c' to follow the steps and apply custom points." << "\n" << endl;
	bool Defaultvalue = false;
	auto input = [Defaultvalue](Coord def, const std::string& info) mutable
	{
		Coord coord = def;
		if (Defaultvalue) return coord;
		char ch;
		std::cin >> ch;
		switch (ch) {
		case 'c':
			cout << info << std::endl;
			cout << "Please input custom points in the format of 'x y z' in the next line: " << endl;
			std::cin >> coord.x;
			std::cin >> coord.y;
			std::cin >> coord.z;
			cout << "Please input 'c' to continue." << endl;
			break;
		case 'd':
			std::cout << info << std::endl
				<< "The default value is : " << def.x << ' ' << def.y << ' ' << def.z << std::endl;
			cout << "" << endl;
			break;
		case 's':
			Defaultvalue = true;
			break;
		default:
			std::cout << "Input format error, please check and try again." << std::endl;
			system("pause");
			std::terminate();
			break;
		}
		return coord;
	};


	//Default Euler operation section with fixed steps.
	//Secion1
	auto ret0 = mvfs(input(Coord{ 0.f, 0.f, 0.f }, "The 1st vertex"));
	auto loop = std::get<2>(ret0)->faces.front()->Loopout;
	auto ret1 = mev(std::get<0>(ret0), loop, input(Coord{ 10.f, 0.f, -4.f }, "The 2nd vertex"));
	auto ret2 = mev(std::get<1>(ret1), loop, input(Coord{ 20.f, 0.f, 0.f }, "The 3rd vertex"));
	auto ret3 = mev(std::get<1>(ret2), loop, input(Coord{ 10.f, 0.f, 4.f }, "The 4th vertex"));
	auto ret4 = mef(loop, std::get<1>(ret3), std::get<0>(ret0));

	//Secion2
	loop = std::get<1>(ret4)->Loopout;
	auto ret5 = mev(std::get<0>(ret0), loop, input(Coord{ 7.5f, 0.f, 2.f }, "The 5th vertex"));
	auto ret6 = kemr(std::get<0>(ret0), std::get<1>(ret5), loop);

	loop = std::get<0>(ret6);
	auto ret7 = mev(std::get<1>(ret5), loop, input(Coord{ 10.f, 0.f, 1.f }, "The 6th vertex"));
	auto ret8 = mev(std::get<1>(ret7), loop, input(Coord{ 12.5f, 0.f, 2.f }, "The 7th vertex"));
	auto ret9 = mev(std::get<1>(ret8), loop, input(Coord{ 10.f, 0.f, 3.f }, "The 8th vertex"));
	auto ret10 = mef(loop, std::get<1>(ret9), std::get<1>(ret5));

	//Secion3
	loop = std::get<1>(ret4)->Loopout;
	auto ret11 = mev(std::get<1>(ret1), loop, input(Coord{ 7.5f, 0.f, -2.f }, "The 9th vertex"));
	auto ret12 = kemr(std::get<1>(ret1), std::get<1>(ret11), loop);

	loop = std::get<0>(ret12);
	auto ret13 = mev(std::get<1>(ret11), loop, input(Coord{ 10.f, 0.f, -3.f }, "The 10th vertex"));
	auto ret14 = mev(std::get<1>(ret13), loop, input(Coord{ 12.5f, 0.f, -2.f }, "The 11th vertex"));
	auto ret15 = mev(std::get<1>(ret14), loop, input(Coord{ 10.f, 0.f, -1.f }, "The 12th vertex"));
	auto ret16 = mef(loop, std::get<1>(ret15), std::get<1>(ret11));

	//Secion4
	Sweep(std::get<1>(ret4), input(Coord{ 0.f, 5.f, 0.f }, "The sweeping direction"));
	kfmrh(std::get<2>(ret0)->faces.front()->Loopout, std::get<1>(ret10)->Loopout);
	kfmrh(std::get<2>(ret0)->faces.front()->Loopout, std::get<1>(ret16)->Loopout);

	Print(std::get<2>(ret0), "B-rep_Result.brp");

	cout << "Congratulation! Data has been successfully stored." << endl;
	cout << "Please use MeshFramework to open the newly generated .brp file in the CAD folder to view the model." << endl;
	return 0;
}
