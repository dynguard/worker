/*
 * test.h
 *
 *  Created on: 20 Feb 2014
 *      Author: chris
 */

#ifndef TEST_H_
#define TEST_H_

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>

class test {

private:
	std::string m_nmachine_name;
	std::string m_nmachine_status;

public:
	test();

	int get_vm_status(std::string machine_name);
	void set_vm_name(std::string machine_name);
	void set_vm_status(std::string machine_status);
	void print_machine_details();

	virtual ~test();
};

#endif /* TEST_H_ */
