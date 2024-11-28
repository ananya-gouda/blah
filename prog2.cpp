#include<iostream>
#include<omp.h>
#include<vector>
using namespace std;
int main() {
vector<string> sections = {"clothing", "gaming", "grocery", "stationary"};
vector<int> serial_sec(sections.size(), 0), parallel_sec(sections.size(), 0);

cout<<"serial \n";
double st_serial = omp_get_wtime();
for(int i = 0; i<sections.size(); i++){
int num_items, total=0;
cout<<"enter no of items: \n";
cin>>num_items;
cout<<"enter rpices of each item: \n";
for(int j = 0; j<num_items; j++){
int price;
cin>>price;
total+=price;
}
serial_sec[i] = total;
}
double end_serial = omp_get_wtime();

cout<<"parallel \n";
double st_par = omp_get_wtime();
for(int i = 0; i<sections.size(); i++){
int num_items, total=0;
cout<<"enter no of items: \n";
cin>>num_items;
cout<<"enter rpices of each item: \n";
#pragma omp parallel for reduction(+:total)
for(int j = 0; j<num_items; j++){
int price;
cin>>price;
total+=price;
}
parallel_sec[i] = total;
}
double end_par = omp_get_wtime();

cout<<"serial execeution \n";
int overall_ser = 0;
for(int i = 0; i<sections.size(); i++){
cout << sections[i] << ": " << serial_sec[i] << "\n";
overall_ser += serial_sec[i];
}
cout<<"\n overall price: "<<overall_ser<<"\n";
cout<<"time serial "<<end_serial - st_serial<< "\n";

cout<<"parallel execeution \n";
int overall_par = 0;
for(int i = 0; i<sections.size(); i++){
cout << sections[i] << ": " << parallel_sec[i] << "\n";
overall_par += parallel_sec[i];
}
cout<<"\n overall price: "<<overall_par<<"\n";
cout<<"time parallel "<<end_par - st_par<< "\n";

return 0;
}

