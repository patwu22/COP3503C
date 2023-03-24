#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
   
   /* Overall flow of the program:
   Get some input for the title
   Get some input for column header #1
   Get some input for column header #2
   
   Until the user types "-1":
   Get input for a string
   Validate input
   If valid...
      Split
      Validate second half of input
      If also valid...
         Store separate pieces
   
   Print out data in table format
   
   Print out data in chart format
   */
   
   string title;
   string col1;
   string col2;
   
   cout << "Enter a title for the data:" << endl;
   getline(cin, title);
   cout << "You entered: " << title << endl;
   
   cout << "Enter the column 1 header:" << endl;
   getline(cin, col1);
   cout << "You entered: " << col1 << endl;
   
   cout << "Enter the column 2 header:" << endl;
   getline(cin, col2);
   cout << "You entered: " << col2 << endl;
   
   string datapoint;
   vector<string> authors;
   vector<int> numbers;
   
   while (true)
   {
      cout << "Enter a data point (-1 to stop input):" << endl;
      getline(cin, datapoint);
      
      try
      {
         if (datapoint == "-1")
         {
            break;
         }
         
         size_t comma = datapoint.find(",");
         
         if (comma == string::npos)
         {
            throw string("Error: No comma in string.");
         }
         if (datapoint.find(",", comma + 1) != string::npos)
         {
            throw string("Error: Too many commas in input.");
         }
         if (!isdigit(datapoint.substr(comma + 2)[0]))
         {
            throw string("Error: Comma not followed by an integer.");
         }
         
         string author = datapoint.substr(0, comma);
         int number = stoi(datapoint.substr(comma + 2));
         
         cout << "Data string: " << author << endl;
         cout << "Data integer: " << number << endl;
         authors.push_back(author);
         numbers.push_back(number);
         
      }
      catch (string e)
      {
         cout << e << endl;
      }
   }
   
   //Table
   int size = (int)authors.size();
   cout << endl;
      
   cout << right << setw(33) << title<< endl;
   cout << left << setw(20) << col1 << "|" << right << setw(23) << col2 << endl;
   cout << setfill('-') << setw(44) << "-" << endl;
   cout << setfill(' ');
   
   for (int i = 0; i < size; i++)
   {
      cout << left << setw(20) << authors[i] << "|" << right << setw(23) << numbers[i] << endl;
   }
   
   //Histogram
   cout << endl;
   
   for (int i = 0; i < size; i++)
   {
      cout << right << setw(20) << authors[i] << ' ';
      for (int j = 0; j < numbers[i]; j++)
      {
         cout << '*';
      }
      cout << endl;
   }
   
   return 0;
}
