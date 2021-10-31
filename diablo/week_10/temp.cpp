#include <iostream>
#include <string>
using namespace std;


class Countries {
   public:
      Countries(string name = "NoName", double population = 10.00);
   private:
      string contName;
      double pop;
};


Countries::Countries(string name, double population) {
   contName = name;
   pop = population;
}


int main() {

	Countries myCont(null, novalue);
}