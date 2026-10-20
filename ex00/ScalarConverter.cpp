#include "ScalarConverter.hpp"
#include <cctype>
#include <cstdlib>
#include <climits>
#include <cfloat>
#include <sstream>

ScalarConverter::ScalarConverter()
{
}
ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
    (void)other;
}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
    (void)other;
    return *this;
}
ScalarConverter::~ScalarConverter()
{
}

bool isChar(const std::string &literal)
{
    return literal.length() == 1 && !std::isdigit(static_cast<unsigned char>(literal[0]));
}
bool isInt(const std::string &literal)
{
    if (literal.empty())
        return false;
    size_t i = 0;
    if (literal[i] == '+' || literal[i] == '-')
        i++;
    if (i == literal.length())
        return false;
    while (i < literal.length())
    {
        if (!std::isdigit(literal[i]))
            return false;
        i++;
    }
    return true;
}

bool isFloat(const std::string &literal)
{
    if (literal.empty())
        return false;
    size_t i = 0;
    if (literal[i] == '+' || literal[i] == '-')
        i++;
    if (literal[literal.length() - 1] != 'f')
        return false;
    int dot = 0;
    bool hasDigit = false;
    while (i < literal.length() - 1)
    {
        if (literal[i] == '.')
        {
            if (dot == 1)
                return false;
            dot = 1;
        }
        else if (!std::isdigit(literal[i]))
            return false;
        else
            hasDigit = true;
        i++;
    }
    return dot == 1 && hasDigit;
}

bool isDouble(const std::string &literal)
{
    if (literal.empty())
        return false;
    size_t i = 0;
    if (literal[i] == '+' || literal[i] == '-')
        i++;
    int dot = 0;
    bool hasDigit = false;
    while (i < literal.length())
    {
        if (literal[i] == '.')
        {
            if (dot == 1)
                return false;
            dot = 1;
        }
        else if (!std::isdigit(literal[i]))
            return false;
        else
            hasDigit = true;
        i++;
    }
    return dot == 1 && hasDigit;
}

void ScalarConverter::convert(const std::string &literal)
{
    if (literal == "nan" || literal == "+inf" || literal == "-inf" || literal == "nanf" || literal == "+inff" || literal == "-inff")
    {
        std::string doubleText = literal;
        if (literal == "nanf" || literal == "+inff" || literal == "-inff")
            doubleText = literal.substr(0, literal.length() - 1);
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: " << doubleText << "f" << std::endl;
        std::cout << "double: " << doubleText << std::endl;
    }
    else if (isChar(literal))
    {
        // int i=literal.length();
        char c = literal[0];
        std::cout << "char: ";
        if (std::isprint(static_cast<unsigned char>(c)))
        {
            std::cout << "'" << c << "'" << std::endl;
        }
        else
            std::cout << "Non displayable" << std::endl;
        std::cout << "int: " << static_cast<int>(c) << std::endl;
        std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
        std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
    }
    else if (isInt(literal))
    {
        long value = std::atol(literal.c_str());

        char c = static_cast<char>(value);
        float f = static_cast<float>(value);
        double d = static_cast<double>(value);

        std::cout << "char: ";
        if (value < 0 || value > 127)
            std::cout << "impossible";
        else if (!std::isprint(static_cast<unsigned char>(c)))
        {
            std::cout << "Non displayable";
        }
        else
            std::cout << "'" << c << "'";
        std::cout << std::endl;
        std::cout << "int: ";
        if (value > INT_MAX || value < INT_MIN)
            std::cout << "impossible" << std::endl;
        else
            std::cout << static_cast<int>(value) << std::endl;
        std::ostringstream floatStream;
        floatStream << f;
        std::string floatText = floatStream.str();
        if (floatText.find_first_of(".eE") == std::string::npos)
            floatText += ".0";
        std::cout << "float: " << floatText << "f" << std::endl;

        std::ostringstream doubleStream;
        doubleStream << d;
        std::string doubleText = doubleStream.str();
        if (doubleText.find_first_of(".eE") == std::string::npos)
            doubleText += ".0";
        std::cout << "double: " << doubleText << std::endl;
    }

    else if (isFloat(literal))
    {
        double parsed = std::atof(literal.c_str());
        if (parsed > FLT_MAX || parsed < -FLT_MAX)
        {
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
            std::cout << "float: impossible" << std::endl;
            std::cout << "double: impossible" << std::endl;
            return;
        }
        float value = static_cast<float>(parsed);
        std::cout << "char: ";
        if (value < 0 || value > 127)
            std::cout << "impossible";
        else
        {
            char c = static_cast<char>(value);
            if (!std::isprint(static_cast<unsigned char>(c)))
                std::cout << "Non displayable";
            else
                std::cout << "'" << c << "'";
        }
        std::cout << std::endl;
        double d = static_cast<double>(value);
        std::cout << "int: ";
        if (d > INT_MAX || d < INT_MIN)
            std::cout << "impossible" << std::endl;
        else
            std::cout << static_cast<int>(value) << std::endl;
        std::ostringstream floatStream;
        floatStream << value;
        std::string floatText = floatStream.str();
        if (floatText.find_first_of(".eE") == std::string::npos)
            floatText += ".0";
        std::cout << "float: " << floatText << "f" << std::endl;

        std::ostringstream doubleStream;
        doubleStream << d;
        std::string doubleText = doubleStream.str();
        if (doubleText.find_first_of(".eE") == std::string::npos)
            doubleText += ".0";
        std::cout << "double: " << doubleText << std::endl;
    }
    else if (isDouble(literal))
    {
        double value = std::atof(literal.c_str());
        std::cout << "char: ";
        if (value < 0 || value > 127)
            std::cout << "impossible";
        else
        {
            char c = static_cast<char>(value);
            if (!std::isprint(static_cast<unsigned char>(c)))
                std::cout << "Non displayable";
            else
                std::cout << "'" << c << "'";
        }
        std::cout << std::endl;
        std::cout << "int: ";
        if (value > INT_MAX || value < INT_MIN)
            std::cout << "impossible" << std::endl;
        else
            std::cout << static_cast<int>(value) << std::endl;
        std::cout << "float: ";
        if (value > FLT_MAX || value < -FLT_MAX)
            std::cout << "impossible" << std::endl;
        else
        {
            float f = static_cast<float>(value);
            std::ostringstream stream;
            stream << f;
            std::string text = stream.str();
            if (text.find_first_of(".eE") == std::string::npos)
                text += ".0";
            std::cout << text << "f" << std::endl;
        }
        std::ostringstream stream;
        stream << value;
        std::string text = stream.str();
        if (text.find_first_of(".eE") == std::string::npos)
            text += ".0";
        std::cout << "double: " << text << std::endl;
    }
    else
        std::cout << "Invalid" << std::endl;
}
