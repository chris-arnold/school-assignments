#include <string>
#include <fstream>
using namespace std;

class OneLine
{
   public:
      OneLine();
      ~OneLine();
      void breakLine();
      void printReverse();
      void readLine(istream& is);
   //   istream &readLine(istream& is);
      string returnLine();
   private:
      string oneLine;
      char **words;
      int wordCount;
      void resetLine();
};
