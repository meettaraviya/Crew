#include <iostream>
#include <vector>
#include <string>
#include "game.cpp"

using namespace std;

int main()
{
   vector<string> msg {"Hello", "C++", "World", "from", "VS Code!!"};

   for (const string& word : msg)
   {
      cout << word << " ";
   }
   cout << endl;
   salute();
}