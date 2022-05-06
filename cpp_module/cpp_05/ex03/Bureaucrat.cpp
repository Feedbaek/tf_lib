/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:33:06 by minskim2          #+#    #+#             */
/*   Updated: 2022/05/04 21:59:42 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

const char	*Bureaucrat::GradeTooHighException::what(void) const throw() {
	return ("Bureaucrat Grade Too High");
}
const char	*Bureaucrat::GradeTooLowException::what(void) const throw() {
	return ("Bureaucrat Grade Too Low");
}

Bureaucrat::Bureaucrat() {
}
Bureaucrat::Bureaucrat(std::string str, int num) :name(str), grade(num){
	if (this->grade < 1)
		throw Bureaucrat::GradeTooHighException();
	if (this->grade > 150)
		throw Bureaucrat::GradeTooLowException();
}
Bureaucrat::Bureaucrat(const Bureaucrat &a) :name(a.name), grade(a.grade) {
	if (this->grade < 1)
		throw Bureaucrat::GradeTooHighException();
	if (this->grade > 150)
		throw Bureaucrat::GradeTooLowException();
}
Bureaucrat::~Bureaucrat() {
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &a) {
	if (this != &a) {
		*(const_cast<std::string *>(&this->name)) = a.name;
		this->grade = a.grade;
	}
	return *this;
}

std::string	Bureaucrat::getName() const {
	return this->name;
}
int	Bureaucrat::getGrade() const {
	return this->grade;
}
void	Bureaucrat::upGrade() {
	if (this->grade - 1 == 0)
		throw Bureaucrat::GradeTooHighException();
	this->grade--;
}
void	Bureaucrat::downGrade() {
	if (this->grade + 1 == 151)
		throw Bureaucrat::GradeTooLowException();
	this->grade++;
}

void	Bureaucrat::signForm(Form &a) {
	try {
		a.beSigned(*this);
		std::cout << this->name << " signs "
		<< a.getName() << std::endl;
	} catch (std::exception& e) {
		std::cerr  << this->name << " cannot sign "
		<< a.getName() << " because " << e.what() << std::endl;
	}
}

void Bureaucrat::executeForm(const Form &a) {
	try {
		a.execute(*this);
		std::cout << this->name << " executes "
		<< a.getType() << " : " << a.getName() << std::endl;
	} catch (std::exception& e) {
		std::cerr << this->name << " cannot execute "
		<< a.getType() << " : " << a.getName() << " because "
		<< a.getType() << " : " << e.what() << std::endl;
	}
}

std::ostream& operator<<(std::ostream &out, Bureaucrat &b) {
	out << b.getName() + ", bureaucrat grade " << b.getGrade();
	return out;
}
