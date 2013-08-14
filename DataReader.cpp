#include "DataReader.h"
#include <string>
#include <fstream>
#include <iostream>

DataReader::DataReader(){};

DataReader::~DataReader(){};

void DataReader::loadObj(std::string obj)
{
    obj += ".dat";
    obj = "data/"+obj;
    ifs.open((obj).c_str(),std::ifstream::in);
    if(ifs.good()){
        std::cout << "File: " << obj << " Opened Successfully\n";
    }
    else{
        std::cout << "Error Opening file: " << obj << "\n";
    }
}

void DataReader::closeObj(){
if(ifs.is_open()){
    ifs.close();
    std::cout << "File Closed\n";
}
}

std::string DataReader::getValue(std::string s)
{
    //std::cout << "Searching for: " << s << "\n";
    ifs.seekg(0);
    std::string temp;
    while(ifs.good())
    {
        std::getline(ifs,temp);
        if(temp.find(s) != std::string::npos)
        {
            temp.erase(temp.begin(), temp.begin()+s.length()+1);
            break;
        }
    }
    return temp;
}
