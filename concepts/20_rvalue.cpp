#include <iostream>
#include <string>

using namespace std;

// comment and uncomment the diff fns to observe the changes

// const std::string& can bind to lvalues and rvalues
void printname(const string& name){
    cout << name << "\n";
}

void printname(string& name){
    cout << name << "\n";
}

// this can take the temp dying literal, but now fuillname errors out
void printname(string&& name){
    cout << name << "\n";
}

int main(){
    string fullname = "jino rohit";
    printname(fullname);
    // printname("jino rohit"); wont work bc youre trying to pass a rvalue, now change to const string& name, this accepts both
    printname("jino"); // printname("jino") now works : "jino" creates a temporary std::string const std::string& can bind to temporaries. The temporary’s lifetime is extended

}