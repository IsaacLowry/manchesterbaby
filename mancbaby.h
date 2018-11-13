#include <vector>
#include <iostream>

using namespace std;

int memLines = 32;
int counter = 0;

vector<string> store(memLines, 0);
vector<string> memLocation(memLines, 0);
vector<string> accumulator(memLines, 0);


vector<string> fetchDecode(vector<string> memLocation);

vector<string> execute(vector<string> accumulator );

void printout(vector<string> store, int counter);
