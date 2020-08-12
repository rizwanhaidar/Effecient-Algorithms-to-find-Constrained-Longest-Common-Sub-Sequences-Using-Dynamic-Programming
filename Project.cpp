//i180536
//Rizwan Haidar
//Effecient Algorithms for LCS
//Project of Course "Design and Analysis of Alggorithms"
//Spring 2020
//Deadline 5th June 2020
// We are asked to implement
//Dynamic Programming for LCS
// and anyone theorem from the
// Paper we have presented
//I have implemented Ist theorem
//And cross checked my answer with the given example 
//Provided in the paper


#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <string>
#include <unistd.h>
#include <fstream>
using namespace std;
	fstream output_file;
	fstream output_file1;
struct Special_Arr
{
	//A structure for Array
	//Having weight and Arrow type for bach tracking
	int weight;
	string arrow_type;
};

//----------------------------------------Part 1 Functionality--------------------------------//
//Dynamic Programming Algorithm For LCS

void Dynammic_Prog_LCS(string s1, string s2)
{

	//Initializations

	int row_size = s1.length();
	int col_size = s2.length();

	//Memory Allocation
	Special_Arr **Matrix = new Special_Arr *[row_size + 1];
	for (int i = 0; i < row_size + 1; i++)
	{
		Matrix[i] = new Special_Arr[col_size + 1];
	}

	//Dynamic Programming Algorithm
	for (int i = 0; i <= row_size; i++)
	{
		for (int j = 0; j <= col_size; j++)
		{
			if (i == 0 || j == 0)
			{
				//default fill
				Matrix[i][j].weight = 0;
				Matrix[i][j].arrow_type = "null";
			}
			else if (s1[i] == s2[j])
			{
				//if value at rowth and column index is same
				Matrix[i][j].weight = Matrix[i - 1][j - 1].weight + 1;
				Matrix[i][j].arrow_type = "up_left";
			}
			else if (Matrix[i - 1][j].weight >= Matrix[i][j - 1].weight)
			{
				//If previous row is max than previous col
				Matrix[i][j].weight = Matrix[i - 1][j].weight;
				Matrix[i][j].arrow_type = "up";
			}
			else
			{
				//If previous col is max than previous row
				Matrix[i][j].weight = Matrix[i][j - 1].weight;
				Matrix[i][j].arrow_type = "left";
			}
		}
	}

	//Initialization for Result
	vector<char> result_;
	int i = s1.length();
	int j = s2.length();

	//Extracting the required SubString/Subsequence
	while (i > 0 || j > 0)
	{

		if (i == 0 || j == 0)
		{
			break;
		}
		if (Matrix[i][j].arrow_type == "up_left")
		{
			result_.push_back(s1[i]);

			i -= 1;
			j -= 1;
		}
		else if (Matrix[i][j].arrow_type == "up")
		{
			i -= 1;
		}
		else
		{
			j -= 1;
		}
	}

	//Printing LCS
	output_file << "LCS = ";
	for (int i = result_.size() - 1; i > 0; i--)
	{
		output_file << result_.at(i);
	}
	output_file << endl;
}

//-------------------------------------Implementation of A Part 2-------------------------------//

//Layer Zero Implementation
//A more simplified form of
//Dynamic Programming for LCS

Special_Arr **layer_Zero(string s1, string s2)
{

	//cout << endl;

	//Initialization

	int m = s1.length();
	int n = s2.length();

	//Memory Allocation
	Special_Arr **Matrix = new Special_Arr *[m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		Matrix[i] = new Special_Arr[n + 1];
	}

	//Initialization
	int i, j;

	//Nested iteration for the filling of Array that will be returned
	//As a simple Dynamic Programming Algorithm for LCS
	for (i = 0; i <= m; i++)
	{
		for (j = 0; j <= n; j++)
		{
			if (i == 0 || j == 0)
			{
				//Default fill
				Matrix[i][j].weight = 0;
			}
			else if (s1[i - 1] == s2[j - 1])
			{
				//if rowth index has same value as the column
				Matrix[i][j].weight = Matrix[i - 1][j - 1].weight + 1;
			}
			else if (Matrix[i - 1][j].weight >= Matrix[i][j - 1].weight)
			{
				//If pre row is max than pre col
				Matrix[i][j].weight = Matrix[i - 1][j].weight;
				//Matrix[i][j].arrow_type = "up";
			}
			else
			{
				//if pre col is max than pre row
				Matrix[i][j].weight = Matrix[i][j - 1].weight;
				//Matrix[i][j].arrow_type = "left";
			}
		}
	}
	//return;
	return Matrix;
}

//-------------------------------------------------Implementation of B of Part 2-----------------------//
//Implementation of Previous Match Table
//Takes 2 strings as Arguments

int **prevMatch(string s1, string s2)
{
	//Initialization
	int row = s2.length();
	int col = s1.length();
	int val;

	//Memory Allocation
	int **to_ret = new int *[row];
	for (int i = 0; i < row; i++)
	{
		to_ret[i] = new int[col];
	}

	//Algorithm to generate prematch table of 2 provided Strings
	for (int i = 0; i < row; i++)
	{
		val = -1; //Set value to -1 when starting a new row
		for (int j = 0; j < col; j++)
		{
			to_ret[i][j] = val;
			if (s2[i] == s1[j])
			{
				val = j + 1; //col + 1 value
			}
		}
	}
	return to_ret;
}

//-------------------------------Implementation of C part 2----------------------//
struct Args
{
	//Another Structure
	//Saves Position and
	//Value at that Position
	int pos;
	int val;
};

//--------------------------------A utility function---------------------------------//
//This function is a helper function for creating
//Start Position table
//That are later used for crating the layer 2

int find_pre(string cons, int curr_pos, string str)
{
	//Ierates in the reverse form
	//to find the previous same character
	//from the current position
	//And would return that position
	//cout << endl;

	//Initialization
	int to_ret = 0;
	int cons_len = cons.length() - 1;
	int counter = 0;

	//Algorithm Implementation
	for (int i = curr_pos; i > -1; i--)
	{
		if (cons[cons_len] == str[i])
		{
			counter++;
			cons_len--;
		}
		if (cons_len < 0)
		{
			to_ret = i + 1;
			break;
		}
	}
	return to_ret;
}

//----------------------------------------Implementation of D part 2-------------------------//
//One D Start Pos table creator
//Used in creation of layer 2
int *start_pos_thr_one(string str, string cons)
{

	//Initialization
	char last = cons.back();
	char ist = cons.front();

	//Memory Allocation
	int *to_ret = new int[str.length()];
	for (int i = 0; i < str.length(); i++)
	{
		to_ret[i] = -1;
	}

	//Main Algorithm
	//working in reverse from
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == last && i > cons.size() - 1)
		{
			to_ret[i] = find_pre(cons, i, str);
		}
	}

	return to_ret;
}
//Main Function
int main()
{



	output_file.open("OutputDP.txt",ios::out);
	
//----------------------------------------------------------------------------------------------------------//
	//-------------------------------------------------------------------------------------------------//
		//----------------------------------------------------------------------------------------//
			//--------------------------------------------------------------------------------//
				//-----------------------------------------------------------------------//
					//---------------------------------------------------------------//
							 //Dynamic Programming For LOngest Common Subsequence//	
							 					//Implementation//

	//LCS with Dynamic Programming
	//Basic Initialization
	//For reading number of test cases
	//and strungs;
	//Along Filestream	fstream output_file;
	string s1, s2;
	string test_numbers;
	
	fstream dyn_prog;

//Working Starts here
	output_file << "\n------------------LCS after Algorithm Of Dynamic Programming:--------------------\n";
//File opening	
	dyn_prog.open("DynamicProgrammingInput.txt", ios::in);
//Testcase Reading	
	int test_cases_;
	dyn_prog >> test_numbers;
	stringstream conversion1(test_numbers); 
	conversion1 >>test_cases_;
//To integer	
	int t= 1;
//Loop untill itertator  > 0 (iterator = test cases)	
	while (test_cases_ > 0)
	{	output_file << "Test Number = "<<t<<endl;
		t++;
		dyn_prog >> s1 >> s2;
		output_file << "String one = " << s1 << endl;
		output_file << "String two = " << s2 << endl;
		s1.insert(0, " ");
		s2.insert(0, " ");

		Dynammic_Prog_LCS(s1, s2);
		test_cases_--;
	}
	dyn_prog.close();



	//String Inclusion CLCS

//Initialization	
	string s1_, s2_, s3_;
//Filestream	
	fstream theo1;
	output_file.close();
	output_file1.open("output_fileCLCS.txt",ios::out);
	theo1.open("Theorem_One_Input.txt", ios::in);
	theo1 >> test_numbers;
	stringstream conversion(test_numbers); 
	conversion >>test_cases_;
//Some important initialization
//
	int see_layer_0 = 0, see_prev_match_table = 0, see_start_pos_table = 0, see_layer_1 = 0;
	int r = 0;

	output_file1 << "\n------------------String Inclusion CLCS After Theorem 1:--------------------\n";
	int test_no = 1;
	//loop untill test cases
	while (test_cases_ > 0)
	{
		//Theorem 1 
		//read three strings
		output_file1 << "\nTest Case = " << test_no << endl;
		test_no++;
		theo1 >> s1_ >> s2_ >> s3_;

		output_file1 << "s1 = " << s1_ <<"\n"<< "s2 = " << s2_;

//-----------------------------------------------------------------------------------------------------//
								//Layer Zero Working//
		
		output_file1 << "\nCalculating Layer 0 : ";
		Special_Arr **layer_0 = layer_Zero(s1_, s2_);
		output_file1 << "\nLayer Zero is Calculated : ";
		output_file1 << endl;
		//cout << "Do you Want to see Layer Zero : (1 for yes 0 for no) ";
		//cin >> see_layer_0;
		see_layer_0 =1;
		output_file1 << endl;

		if (see_layer_0){
			//If user wants to see
			//layer 0 
			//Printing Layer zero
			for (int i = 0; i <= s1_.length(); i++){
				for (int j = 0; j <= s2_.length(); j++){
					output_file1 << layer_0[i][j].weight << "\t";
				}
				output_file1 << endl;
			}
		}


//=====================================================================================================//
							//Previous Match Table Working//

		output_file1 << "Calculating Ist PrevMatch Table : ";
		int **prev_Match_Table_1 = prevMatch(s1_, s3_);
		//cout << "\nDo you Want to see Ist PrevMatch Table : (1 for yes 0 for no) ";
		//cin >> see_prev_match_table;
		see_prev_match_table =1;
		output_file1 << endl;
		if (see_prev_match_table)
		{
			//If user wants to see Pre Match Table
			//Showing it
			for (int i = 0; i < s3_.length(); i++){
				for (int j = 0; j < s1_.length(); j++){
					output_file1 << prev_Match_Table_1[i][j] << "\t";
				}
				output_file1 << endl;
			}
		}
		output_file1 << "Ist PrevMatch Table Calculated: ";
		see_prev_match_table = 0;

//=====================================================================================================//
							//Previous Match Table Working//
		
		output_file1 << "Calculating 2nd PrevMatch Table : ";
		int **prev_Match_Table_2 = prevMatch(s2_, s3_);
		//cout << "\nDo you Want to see Ist PrevMatch Table : (1 for yes 0 for no) ";
		//cin >> see_prev_match_table;
		see_prev_match_table =1;
		output_file1 << endl;
		if (see_prev_match_table){
			//If user wants to see Pre Match Table
			//Showing it
			for (int i = 0; i < s3_.length(); i++){
				for (int j = 0; j < s2_.length(); j++){
					output_file1 << prev_Match_Table_2[i][j] << "\t";
				}
				output_file1 << endl;
			}
		}
		output_file1 << "2nd PrevMatch Table Calculated: ";



//=====================================================================================================//
							//Start Position Table Working//
		//Startpos Table
		output_file1 << "Calculaing Start Pos Table # 1: ";
		int *start_pos_1 = start_pos_thr_one(s1_, s3_);
		//cout << "\nDo you want to see start Pos Table : (1 for yes 0 for no) ";
		//cin >> see_start_pos_table;
		//cout << endl;
		see_start_pos_table = 1;
		if (see_start_pos_table){
			//If user wants to Start Pos Table
			//Showing it
			for (int i = 0; i < s1_.size(); i++){
				output_file1 << start_pos_1[i] << "\t";
			}
			output_file1 << endl;
		}

		see_start_pos_table = 0;

//=====================================================================================================//
							//Start Position Table Working//

		output_file1 << "Calculaing Start Pos Table # 2: ";
		int *start_pos_2 = start_pos_thr_one(s2_, s3_);
		//cout << "\nDo you want to see start Pos Table : (1 for yes 0 for no) ";
		//cin >> see_start_pos_table;
		see_start_pos_table =1;
		output_file1 << endl;

		if (see_start_pos_table){
			//If user wants to Start Pos Table
			//Showing it
			for (int i = 0; i < s1_.size(); i++)
			{
				output_file1 << start_pos_2[i] << "\t";
			}
			output_file1 << endl;
		}



//----------------------------------------Layer One Implementation-------------------------------//

		//Layer one Implementation

		//Initialization
		int m1 = s1_.size();
		int n2 = s2_.size();
		bool t_eq = false;
		int cross_row = 0, cross_col = 0;
		r = s3_.size();

		//Memory Allocation
		Special_Arr **Matrix = new Special_Arr *[m1 + 1];
		for (int i = 0; i < m1 + 1; i++)
		{
			Matrix[i] = new Special_Arr[n2 + 1];
		}

		//Main ALgorithm Working
		for (int i = 0; i <= m1; i++){
			for (int j = 0; j <= n2; j++){
				
				if (i == 0 || j == 0){
					//Defult fill
					Matrix[i][j].weight = INT16_MIN;
				}
				else if ((s1_[i - 1] == s2_[j - 1]) && (s1_[i - 1] == s3_[r - 1])){
					//If A of I
					//is Same as 
					//B of J
					//is same as 
					//C of R	
					
					if ((start_pos_1[i - 1] - 1 >= 0) && (start_pos_2[j - 1] - 1 >= 0)){
						//A basic check if vlues at that index are even accessable
						
						if (!t_eq){	
							//If not initialized before
							//Means ist match
							Matrix[i][j].weight = layer_0[start_pos_1[i - 1] - 1][start_pos_2[j - 1] - 1].weight + r;
							t_eq = true;
							cross_row = i;
							cross_col = j;
						}
						else{
							//If not ist match
							if ((i == cross_row) || (j == cross_col)){
								//if same row and col as ist initialization
								Matrix[i][j].weight = layer_0[start_pos_1[i - 1] - 1][start_pos_2[j - 1] - 1].weight + r;
							}
							else{
								//if not same row and col as ist initialization
								Matrix[i][j].weight = Matrix[i - 1][j - 1].weight + 1;
							}
						}
					}
					else{
						Matrix[i][j].weight = INT16_MIN;
					}
				}
				else if (s1_[i - 1] == s2_[j - 1]){
					//2 main strings match case
					if (t_eq){
						Matrix[i][j].weight = Matrix[i - 1][j - 1].weight + 1;
					}
					else{
						Matrix[i][j].weight = INT16_MIN;
					}
				}
				else if (Matrix[i - 1][j].weight >= Matrix[i][j - 1].weight){
					//Previous row has 
					//max than previous
					//column
					if (t_eq){
						Matrix[i][j].weight = Matrix[i - 1][j].weight;
					}
					else{
						Matrix[i][j].weight = INT16_MIN;
					}
				}
				else{
					//Previous col has 
					//max than previous
					//row
					if (t_eq){
						Matrix[i][j].weight = Matrix[i][j - 1].weight;
					}
					else{
						Matrix[i][j].weight = INT16_MIN;
					}
				}
			}
		}

//If user wants to see the Layer one Printing it
		//cout << "\nDo you want to see Layer 1 : (1 for yes 0 for no) ";
		//cin >> see_layer_1;
		if(Matrix[m1][n2].weight >= 0){
			output_file1 << "\nLength of the Sub-sequence is " << Matrix[m1][n2].weight << endl<< endl;
		}
		else{
			output_file1 << "\nLength of the Sub-sequence is " << 0 << endl<< endl;
		}
		for (int i = 0; i <= m1; i++){
			for (int j = 0; j <= n2; j++){
				if (Matrix[i][j].weight < 0){
					output_file1 << "inf\t";
				}
				else{
					output_file1 << Matrix[i][j].weight << "\t";
				}
			}
			output_file1 << endl;
		}


		output_file1<<"\nTheorem One Concluded as given in the Paper \n";
		 output_file1<<"As no information regarding backtracting is given\n";
		  output_file1<<"I tried to do that part too to extract the sub-sequence \n";
		   output_file1<<"but could not get desired result\n";
		test_cases_--;
	}
	//	Theorem_One_Input.txt
}