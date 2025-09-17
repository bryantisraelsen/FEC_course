#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

int main()
{
   std::ifstream file("input.txt");
   if (!file) {
      std::cerr << "Could not open file\n";
      return 1;
   }
   std::vector<int> input;

   std::string line;
   while (std::getline(file, line))
   {
      if (!line.empty())
      {
         int value = std::stoi(line);
         input.push_back(value);
      }
   }

   int sum = 0;
   float auto_corr[30];
   int j = 0;
   for(int i = -15; i < 15; i++)
   {
      sum = 0;
      for(int k = 0; k < 15; k++)
      {
         //std::cout << "Starting sum\n";
         if ((i+k) < 0)
         {
            sum += (input[k] * input[i+k+15]);
         }
         else if ((i+k) < 15)
         {
            sum += (input[k] * input[i+k]);
            //std::cout << "Sum now is " << sum << std::endl;
         }
         else
         {
            sum += (input[k] * input[i+k-15]);
            //std::cout << "Sum now is " << sum << std::endl;
         }
      }
      std::cout << "Sum is now at the end of it " << sum << std::endl;
      auto_corr[j] = (1.0f/15.0f) * sum;
      std::cout << "auto_corr for iteration" << i << " is " << auto_corr[i] << std::endl;
      j++;
   }
   for (size_t i = 0; i < 30; i++)
   {
      std::cout << "auto_corr[" << i << "] = " << auto_corr[i] << "\n";
   }
   //output to a file
   std::ofstream outFile("output.txt");
   if (!outFile)
   {
      std::cerr << "Could not open file for writing\n";
      return 1;
   }

   for (int i = 0; i < 30; i++)
   {
      outFile << auto_corr[i] << "\n";
   }

   outFile.close();
   return 0;
}
