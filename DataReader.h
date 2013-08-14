#ifndef DATAREADER_H
#define DATAREADER_H
#include <string>
#include <fstream>
#include <iostream>

class DataReader{
public:
    DataReader();
    ~DataReader();
    void loadObj(std::string obj);
    void closeObj();
    std::string getValue(std::string s);
private:
    std::ifstream ifs;
};
#endif // DATAREADER_H
