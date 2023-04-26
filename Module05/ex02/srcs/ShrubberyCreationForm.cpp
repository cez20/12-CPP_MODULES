#include "ShrubberyCreationForm.hpp"
#include <fstream>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ShrubberyCreationForm::ShrubberyCreationForm(): AForm ("Shrubbery", "target",145, 137)
{
	std::cout << "[SHRUBBERY DEFAULT CONSTRUCTOR] Default construtor is called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target): AForm ("Shrubbery", target, 145, 137)
{
	std::cout << "[SHRUBBERY CONSTRUCTOR W/ ARGS] Construtor with arguments  is called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm( const ShrubberyCreationForm & src )
: AForm("Shrubbery", "target", 145, 137)
{
	std::cout << "[SHRUBBERY COPY CONSTRUCTOR] Copy construtor is called" << std::endl;
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "[SHRUBBERY DESTRUCTOR] DESTRUCTOR is called" << std::endl;
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ShrubberyCreationForm &				ShrubberyCreationForm::operator=( ShrubberyCreationForm const & rhs )
{
	(void)rhs;
	return *this;
}

// std::ostream &			operator<<( std::ostream & o, ShrubberyCreationForm const & i )
// {
// 	//o << "Value = " << i.getValue();
// 	(void)i;
// 	return o;
// }


/*
** --------------------------------- METHODS ----------------------------------
*/

void	ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	if (this->getSignStatus() == false || executor.getGrade() > this->getGradeToExecute())
		return;

	std::ofstream file("Cesar");

	if (file.is_open())
	{
		for (int i = 0; i < 3; i++)
		{
			file <<		 "oxoxoo    ooxoo\n"
			<<			"ooxoxo oo  oxoxooo\n"
			<<			"oooo xxoxoo ooo ooox\n"
			<<			"oxo o oxoxo  xoxxoxo\n"
			<<			"oxo xooxoooo o ooo\n"
			// <<				"ooo\oo\  /o/o\n"
			// <<					"\  \/ /\n"
			// <<					"|   /\n"
			// <<					"|  |\n"
			// <<					"| D|\n"
			// <<					"|  |\n"
			// <<					"|  |\n"
			// <<			"______/____\____\n"
			<< "\n\n";
		}
	}

	file.close();
}



/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */