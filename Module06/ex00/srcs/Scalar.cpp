#include "Scalar.hpp"
#include <iomanip>
#include <sstream>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Scalar::Scalar()
{
	std::cout << "[DEFAULT CONSTRUCTOR] has been called." << std::endl;
}

Scalar::Scalar(std::string entry): _char(0), _int(0), _float(0.0f), _double(0.0), _type(IMPOSSIBLE) {

	if (entry.empty()){
		std::cout << "IMPOSSIBLE: Cannot convert because string is empty!" << std::endl;
		return;
	}
	
	detectType(entry);
	convertToAllTypes(entry);
	printChar();
	printInt();
	printFloat(entry);
	printDouble(entry);
}

Scalar::Scalar( const Scalar &src )
{
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Scalar::~Scalar()
{

}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Scalar &				Scalar::operator=( Scalar const &rhs )
{
	if ( this != &rhs )
	{
		this->_char = rhs._char;
		this->_int = rhs._int;
		this->_float = rhs._float;
		this->_double = rhs._double;
		this->_type = rhs._type;
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void	Scalar::detectType(std::string &entry){

	int len = entry.length();
	int nbrOfDots = findNbrOfDots(entry);
	
	if (nbrOfDots > 1)
		this->_type = IMPOSSIBLE;
	else if (len == 1 &&!std::isdigit(entry[0]))
		this->_type = CHAR;
	else if ((nbrOfDots == 1 && entry[len - 1] == 'f') || isPseudoLiteralFloat(entry))
	{
		if (isPseudoLiteralFloat(entry))
			this->_type = PSEUDOFLOAT;
		this->_type = FLOAT;
	}
	else if (nbrOfDots == 1 || isPseudoLiteralDouble(entry))
		this->_type = DOUBLE;
	else
		this->_type = INTEGER;
}

void Scalar::convertToAllTypes(std::string &entry)
{
	if (this->_type == CHAR)
		convertToChar(entry);
	else if (this->_type == INTEGER) 
		convertToInteger(entry);
	else if (this->_type == FLOAT) 
		convertToFloat(entry);
	else if (this->_type == DOUBLE)
		convertToDouble(entry);
}

void Scalar::convertToChar(std::string &entry)
{
	this->_char = entry[0];
	this->_int = static_cast<int>(this->_char);
	this->_float = static_cast<float>(this->_char);
	this->_double = static_cast<double>(this->_char);
}

void Scalar::convertToInteger(std::string &entry)
{
	char *end = NULL;

	this->_int = static_cast<int>(strtol(entry.c_str(), &end, 10));
	if (*end == '\0')
	{
		this->_char = static_cast<char>(this->_int);
		this->_float = static_cast<float>(this->_int);
		this->_double = static_cast<double>(this->_int);
	}
	else
		this->_type = IMPOSSIBLE;
}

void Scalar::convertToFloat(std::string &entry)
{
	char *end = NULL;
	
	entry.erase(entry.end() - 1);
	this->_float = std::strtof(entry.c_str(), &end);
	if (*end == '\0' || this->_type == PSEUDOFLOAT)
	{
		this->_char = static_cast<char>(this->_float);
		this->_int = static_cast<int>(this->_float);
		this->_double = static_cast<double>(this->_float);
	}
	else
		this->_type = IMPOSSIBLE;
}

void Scalar::convertToDouble(std::string &entry)
{
	char *end = NULL;

	this->_double = std::strtod(entry.c_str(), &end);
	if (*end == '\0')
	{
		this->_char = static_cast<char>(this->_double);
		this->_int = static_cast<int>(this->_double);
		this->_float = static_cast<float>(this->_double);
	}
	else
		this->_type = IMPOSSIBLE;
}

void	Scalar::printChar()
{
	if (this->_type == IMPOSSIBLE)
		std::cout << "char: impossible" << std::endl;
	else if (isNan(this->_double) || isInfinite(this->_double))
		std::cout << "char: impossible" << std::endl;
	else if (!std::isprint(static_cast<int>(this->_char)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << this->_char << "'" << std::endl;
}

void	Scalar::printInt()
{
	if (this->_type == IMPOSSIBLE)
		std::cout << "int: impossible" << std::endl;
	else if (isNan(this->_float) || isInfinite(this->_float))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << this->_int << std::endl;
}

void	Scalar::printFloat(std::string &entry)
{
	(void)entry;
	if (this->_type == IMPOSSIBLE)
		std::cout << "float: impossible" << std::endl;
	else{
		std::stringstream ss;
		ss << "float: " << std::fixed << std::setprecision(1) << this->_float << "f";
		std::cout << ss.str() << std::endl;
	}
}

void	Scalar::printDouble(std::string &entry)
{
	if (this->_type == IMPOSSIBLE)
		std::cout << "double: impossible" << std::endl;
	else if (entry == "+inff")
		std::cout << "double: +inf" << std::endl;
	else {
		std::stringstream ss;
		ss << "double: " << std::fixed << std::setprecision(1) << this->_float;
		std::cout << ss.str() << std::endl;
	}
}

int findNbrOfDots(std::string &entry)
{
	int count = 0;
	for (size_t i = 0; i < entry.length(); i++)
	{
		if(entry[i] == '.')
			count++;
	}
	return (count);
}

bool isPseudoLiteralFloat(std::string &entry)
{
	if (entry == "inff" || entry == "+inff" || entry == "-inff" || entry == "nanf")
		return (true);
	return (false);
}

bool isPseudoLiteralDouble(std::string &entry)
{
	if(entry == "inf"|| entry == "+inf" || entry == "-inf" || entry == "nan")
		return (true);
	return (false);
}

bool isNan(double nbr)
{
	// NaN of "Not a number" never equals itself. 
	if (nbr != nbr)
		return (true);
	return (false);
}

bool isInfinite(double nbr)
{
	double positiveInfinity = std::numeric_limits<double>::infinity();
	double negativeInfinity = -std::numeric_limits<double>::infinity();

	if (nbr == positiveInfinity || nbr == negativeInfinity)
		return (true);
	return (false);

}