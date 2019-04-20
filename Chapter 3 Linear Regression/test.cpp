// UPDATE: map not working


#include<iostream>
#include<cmath>
#include<map>
#include<fstream>

using namespace std;

int main(){
	map<double, double> pizza;
	double x, y, xy, x_sq, x_sq_avg;
	ifstream fin;

	cout << "-------------\n";
	cout << "Data as read from file:\n";

	fin.open("pizza.data"); // opens file
	while(fin){	// check "end of file"
		fin >> x >> y ;
		pizza.insert(pair<double, double> (x, y) );

		cout << "x = " << x << ", y = " << y << endl;
	}fin.close();
	cout << "-------------------\n\n\n"; // 5:12 13/4 all ok

	double x_avg, y_avg, xy_avg, xy_sq_avg;
	double x_sum, y_sum, xy_sum;
	double x_sq_sum;

	x_sq_sum = x_sum = y_sum = xy_sum = 0;
	cout << "AFTER DECLARATION, x_sq_sum = " << x_sq_sum << endl;

	/*
		1. declare iterator
		2. get x_sum, y_sum, xy_sum
		3. calculate x_avg, y_avg, xy, avg
	*/

	cout << "---------- \n";
	map<double, double> :: iterator  it;
	for(it = pizza.begin(); it!= pizza.end(); it++){
		x = it->first;
		y = it->second;
		x_sq = x * x;
		xy = x * y;

		cout << ",,,\n";
		cout << "x^2 = " << x_sq ;
		cout << "\nxy = " << xy << endl;

		x_sum += x;
		y_sum += y;
		xy_sum += xy;
		x_sq_sum += x_sq;

		//cout << "x_sum = " << x_sum << endl;
		//cout << "y_sum = " << y_sum << endl;
		//cout << "xy_sum = " << xy_sum << endl;
		//cout << "x_sq_sum = "<< x_sq_sum  << endl;
		cout << ",,,\n\n\n";
	}cout << "----------- \n\n\n";
	cout << "ALRIGHT TILL HERE\n";

	// find avg
	double n, x_avg_sq;
	n = pizza.size();

	cout << "---------------\n";
	cout << "x_sum = " << x_sum << endl;// FINE
	cout << "y_sum = " << y_sum << endl; // FINE
	cout << "AFTER SUMMATION, x_sq_sum = "<< x_sq_sum << endl;
	cout << "--------------- \n\n\n";

	cout << "---------\n";
	cout << "GETTING AVERAGE,\n";
	x_avg = x_sum / n;
	y_avg = y_sum / n;
	xy_avg = xy_sum / n;
	cout << "\t\tbefore, x_sq_avg = " << x_sq_avg << endl;
	x_sq_avg = x_sq_sum / n;// returns a horrible value
	cout << "\t\tafter, x_sq_avg = " << x_sq_avg << endl;


	cout << "n = " << n << endl; // yields right answer
	cout << "x_avg = " << x_avg << endl;
	cout << "y_avg = " << y_avg << endl;
	cout << "xy_avg = " << xy_avg << endl;
       	//cout << "xy_sq_avg = " << xy_sq_avg << endl;

	//need x_avg_sq
	x_avg_sq = pow(x_avg, 2);
	cout << "x_avg_sq = " << x_avg_sq << endl;
	cout << "x_sq_avg = " << x_sq_avg << endl;

	cout << "---------------\n\n\n";

	cout << "UPDATE: The values immediately above are correct as per book\n\n\n";

	cout << "-------------\n";
	cout << "AGENDA: fix values of 'm' and 'c'" << endl;
	double m, c;
	//cout << "values of 'm' and 'c' are wrong\n";
	//m = ( x_avg * y_avg) - xy_avg/ pow(x_avg,2) - x_sq_avg;
	//c = y_avg - m * x_avg;

	m = x_avg * y_avg;
	m = m - xy_avg;
	m = m / (x_avg_sq - x_sq_avg);

	c = y_avg - m * x_avg;

	cout << "m = " << m << endl; // now okay
	cout << "c = " << c << endl;
	cout << "UPDATE: 'm' and 'c' return correct value\n";
	cout << "--------------\n\n\n";

	// UPDATE: Found 'm' and 'c'
	// Now find R^2
	cout << "---------\n";
	cout << "AGENDA: Fix R value\n";
	double y_pred, num, den;

	num = den = 0;
	fin.open("pizza.data");
	while(fin){
		fin >> x >> y;
		y_pred = m*x + c;
		cout << "\t\tx = " << x << ", y_pred = " << y_pred << endl;
		num += pow(y_pred - y_avg, 2);
		den += pow(y - y_avg, 2);
	}fin.close();

	cout << "R^2 = "<< num/den << endl;

       	cout << "runs fine\n";
	return 0;
}
