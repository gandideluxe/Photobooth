#pragma once

#include <vector>

class Printer
{
public:
    Printer();
    ~Printer();
    
    virtual bool print(std::vector<unsigned char> buffer, unsigned buffer_width, unsigned buffer_height) = 0;

private:
    //std::string m_printer_name;
    //etc

};

