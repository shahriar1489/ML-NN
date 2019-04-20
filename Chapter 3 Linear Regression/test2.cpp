/*
   Description: Gradient Descent Problem.
 */
#include<iostream>
#include<fstream>
#include<cmath>
#include<map> 
using namespace std;

double del_J_by_del_w0(double , double, std::map<double, double>& );
double del_J_by_del_w1(double , double , std::map<double, double>& ); 

double Cost(double, double, double, double);
double J(double, double, std::map<double, double>& );	// write this down below 

double w0_new(double w0, double w1, map<double, double>& pizza);
double w1_new(double w0, double w1, map<double, double>& pizza);

void update(double&, double&, map<double, double>& pizza); 	// This function will update w0 and w1


double alpha = 0.01; 

int main(){
  map<double, double> pizza;

  ifstream fin;
  double w0, w1, x, y, alpha;
  w0 = w1 = 1.0; // P1 
  
  cout << "----------\n";
  //cout << "\t\tReading file and storing data in map\n";

  fin.open("pizza.data");	
  while(fin){// update: the last data is being red twice, not fixed.
    fin >> x >> y;
    pizza.insert(pair<double, double> (x, y) );
    //cout << "\t\t\t"<< x << ", " << y << endl;
  }fin.close();

  cout << "----------\n\n\n";
  
  cout << "Calling update(....)\n\n"; 
  
  update(w0, w1, pizza); // w0 and w1 are updated in this function		
  
  cout << "---------------------------\n\n\n"; 		
  return 0;
} // end of main function


double Cost(double w0, double w1, double x, double Y){	// p.54
	cout << "----------------------------------\n"; 	
	cout << "\n\n\t\tIn function Cost(....)" << endl; 	
	cout << "-----------------------------------\n\n\n";
	return w0 + (w1 * x) -Y;	// as per definition on p.54 
}	// Function is used 

double J(double w0, double w1, std::map<double, double>& pizza){	// This function will only calculate J
	cout << "----------------------------------\n\n"; 	
	cout << "\t\t\tIn J(.....)\n\n"; 

	map<double, double> :: iterator it; 
	double Cost_sq_sum, x, Y, m;
	double result; 	
	Cost_sq_sum = 0; 	
	m = pizza.size();

	ifstream fin; 
	fin.open("pizza.data");	// opened the pizza file 	
	while(fin){
		fin >> x  >> Y; 
		Cost_sq_sum += pow( Cost(w0, w1, x, Y), 2); 
	}fin.close(); 

	// final calculation 
	result = 0.5 * Cost_sq_sum / m; 
	cout << "result = " << result << endl; 
	cout << "m = " << m << endl; 	
	
        //update(w0, w1, pizza);	// How long will the update happen?? Ans: This is answered in the update function. The update function will itself call it 	

	cout << "--------------------------------------------\n\n\n"; 

	return result; 
}	// Function has used all the above functions

double del_J_by_del_w0(double w0, double w1, std::map<double, double>& pizza){
	ifstream fin; 
	fin.open("pizza.data"); 	

	double m, x, Y, num; 
		
	m = pizza.size();
	num  = 0; 
	map<double, double> :: iterator it; 
	for(it = pizza.begin(); it != pizza.end(); it++){
		fin >> x >> Y; 
		num += Cost(w0, w1, x, Y);
	}fin.close(); 	
	
	// now avg and return 
	return num / m;
}

double del_J_by_del_w1(double w0, double w1, std::map<double, double>& pizza){
	ifstream fin;
	fin.open("pizza.data");

	double m, x, Y, num; 
	num = 0; 	
	m = pizza.size();
	//cout << "pizza.size() = " << pizza.size() << endl; 
	std::map<double, double> :: iterator it; //
	for(it = pizza.begin(); it != pizza.end(); it++){
		fin >> x >> Y; 
		num += Cost(w0, w1, x, Y) * x;	// 13:23 This is the 'x' you are talking about.
	}fin.close(); 	
	
	// now avg
	return num / m;
}


double w0_new(double w0, double w1, std::map<double, double>& pizza){
	return w0 - alpha * del_J_by_del_w0(w0, w1, pizza);// alpha is 0.01
}

double w1_new(double w0, double w1, std::map<double, double>& pizza){
	return w1 - alpha * del_J_by_del_w1(w0, w1, pizza) ;// alpha is 0.01
}

void update(double& w0, double& w1, std::map<double, double>& pizza){	// 
//Unlike J, this function will make modifications
	// Things to update: w0 and w1
	
	cout << "----------------------------------------\n"; 
	cout << "update(....)\n\n";         
	double J1, J2, J_, diff, w0_, w1_;	 
	int i, iter1, iter2; 	
	ofstream fout; 	

	fout.open("J.data"); 
	iter1 = iter2 = 0; 	
	w0_ = w0; w1_ = w1;
	J_ = J( w0,  w1, pizza);	//  J updated

	for(i = 1; i < 10000; i++){	// change the type of the loop 
		J_ = J( w0_,  w1_, pizza);
		w0_ = w0_new( w0_, w1_, pizza);	// updated w0 
		w1_ = w1_new( w0_, w1_, pizza); // updated w1
		
		cout << "J_ = " << J_ << ", w0_ = " << w0_ << ", w1_ = " << w1_ << ", iteration = " << i << endl << endl << endl;	
		fout << i << " " << J_ << endl; 

	}// end of for loop 
	w1 = w1_; w0 = w0_; 
	cout << "Final weights: w0 = " << w0 << ", w1 = " << w1 << endl;
	// write down J on the file 

	cout << "---------------------------------------\n\n\n"; 
}// end of update(...) functions		

/*
  // Things to do to look at err_sq_function_ to reduce error  	
	1. Pass the whole dataset- pizza.data 
	2. w0, w1, and x values and the real value- Y --> squared error function 
	3. update w0 and w1 accordingly 
		i)  
		ii) 	
			
*/	
