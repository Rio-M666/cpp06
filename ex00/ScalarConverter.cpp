#include"ScalarConverter.hpp"
#include<cctype>
#include<cstdlib>

ScalarConverter::ScalarConverter()
{
}
ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
    (void)other;
}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter& other)
{
    (void)other;
    return *this;
}
ScalarConverter::~ScalarConverter()
{
}

bool isChar(const std::string& literal)
{
    return(literal.length()==3&&literal[0]=='\''&&literal[2]=='\'');
}
bool isInt(const std::string& literal)
{
    if(literal.empty())
        return false;
    size_t i=0;
    if(literal[i]=='+'||literal[i]=='-')
        i++;
    if(i==literal.length())
        return false;
    while(i<literal.length())
    {
        if(!std::isdigit(literal[i]))
            return false;
        i++;
    }
    return true;
}

bool isFloat(const std::string& literal)
{
    if(literal.empty())
        return false;
    size_t i=0;
    if(literal[i]=='+'||literal[i]=='-')
        i++;
    if(literal[literal.length()-1]!='f')
        return false;
    int dot=0;
    while(i<literal.length()-1)
    {
        if(literal[i]=='.')
        {
            if(dot==1)
                return false;
            dot=1;
        }
        else if (!std::isdigit(literal[i]))
            return false;
        i++;
    }
    return dot==1;

}
  


bool isDouble(const std::string& literal)
{
        if(literal.empty())
        return false;
    size_t i=0;
    if(literal[i]=='+'||literal[i]=='-')
        i++;
    int dot=0;
    while(i<literal.length())
    {
        if(literal[i]=='.')
        {
            if(dot==1)
                return false;
            dot=1;
        }
        else if (!std::isdigit(literal[i]))
            return false;
        i++;
    }
    return dot==1;
}


void ScalarConverter::convert(const std::string& literal)
{
    if(literal=="nan"||literal=="+inf"||literal=="-inf"||literal=="nanf"||literal=="+inff"||literal=="-inff")
    {
        std::cout<<"special"<<std::endl;
    }
    else if(isChar(literal))
    {
        std::cout<<"char"<<std::endl;
    }
    else if(isInt(literal))
    {
        int value=std::atoi(literal.c_str());

        char c=static_cast<char>(value);
        float f=static_cast<float>(value);
        double d=static_cast<double>(value);

        std::cout<<"char: ";
        if(value<0||value>127)
            std::cout<<"impossible";
        else
            std::cout<<"'"<<c<<"'";
        std::cout<<std::endl;

        std::cout << "int: " << value << std::endl;

        std::cout<<"float: "<<f<<".0f"<<std::endl;

        std::cout<<"double: "<<d<<".0"<<std::endl;


    }
    else if(isFloat(literal))
    {
        std::cout<<"float"<<std::endl;
    }
    else if(isDouble(literal))
    {
        std::cout<<"double"<<std::endl;
    }
    else
        std::cout<<"Invalid"<<std::endl;


}
