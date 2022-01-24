#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "fcm.hh"

using namespace std;

int main(int argc , int argv[]){
    fcm file;
    
    file.define_alphabet("text2.txt");
    file.generate_matrix(2);

}