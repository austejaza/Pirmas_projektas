#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using std::string;
using std::vector;

struct studentas{
    string vardas, pavarde;
    vector<int> paz;
    int exam;
    float galutinis;
    float galutinis_med;
};

float Mediana(vector<int> paz) {
  if (paz.empty()) return 0.0;
  std::sort(paz.begin(), paz.end());
  size_t n = paz.size();
  if (n % 2 == 0){
     return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;
  } else{
     return paz[n / 2];
  }
}

void printas(studentas &A);

int main(){
  int k;    
  std::vector<studentas> grupe;
  studentas A;
  std::cout<<"kiek yra studentu sarase: ";
  int n;
  std::cin>>n;
  for(int j=0;j<n;j++)
  {
  std::cout<<"iveskite per tarpa studento varda ir pav: ";
  std::cin>>A.vardas>>A.pavarde;
  std::cout<<"iveskite semestro paz. kieki: ";
  std::cin>>k;
  for (int i=0; i<k;i++){
      std::cout<<"iveskite "<<+i <<"paz.: ";
      int a;
      std::cin>>a;
      A.paz.push_back(a);
  }   
  std::cout<<"iveskite semestro Egzamino paz: ";
  std::cin>>A.exam;
  float sum = 0;
  for (int p : A.paz){
     sum+=p;
}
float vid = k >0? sum/k:0;
A.galutinis = 0.4*vid+0.6*A.exam;

float med = Mediana(A.paz);
A.galutinis_med = 0.4 * med + 0.6 * A.exam;
  grupe.push_back(A);
  A.paz.clear();
}

std::sort(grupe.begin(), grupe.end(), [](const studentas &a, const studentas &b) {
    return a.pavarde < b.pavarde;
});
  
  std::cout<<"\n"
           << std::left << std::setw(12) << "Vardas"
           << std::left << std::setw(12) << "Pavarde"
           << std::right << std::setw(18) << "Galutinis (Vid.)"
           << std::right << std::setw(18) << "Galutinis (Med.)" <<"\n";
 std::cout << string(60, '-') << "\n";
  
for (studentas &B:grupe)
{
printas(B);
}
  return(0);
}


void printas( studentas &A){
  std::cout<<std::left<<std::setw(12)<<A.vardas<<std::left<<std::setw(12)<<A.pavarde;
  std::cout<<std::right<<std::setw(20)<<std::fixed<<std::setprecision(2)<<A.galutinis;
  std::cout<<std::right<<std::setw(20)<<std::fixed<<std::setprecision(2)<<A.galutinis_med;
  std::cout << "\n";
}
