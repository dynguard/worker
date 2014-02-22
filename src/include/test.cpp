/*
 * test.cpp
 *
 *  Created on: 20 Feb 2014
 *      Author: chris
 */

#include "test.h"

test::test() {
	//This could take the machine name on construction to be fair
}

int test::get_vm_status(std::string machine_name)
{
	test::set_vm_name(machine_name);
	char buf[1024];

	std::ostringstream command;
	command << "vboxmanage showvminfo " << machine_name;

	//This seems wasteful and would probably have been better as a char *
	std::string command_to_run = command.str();

	FILE *fp = popen(command_to_run.c_str(), "r");

	while (fgets(buf, 1024, fp))
	{
		if (strstr(buf, "saved"))
		{
			test::set_vm_status("saved");
			return 1;
		}
		else
		{
			test::set_vm_status("UNKNOWN");
			return 0;
		}
	}

	return 0;
}

void test::set_vm_name(std::string machine_name)
{
	m_nmachine_name = machine_name;
}

void test::set_vm_status(std::string machine_status)
{
	m_nmachine_status = machine_status;
}

void test::print_machine_details()
{
	std::cout << "Machine name: " << m_nmachine_name << "\n";
	std::cout << "Machine state: " << m_nmachine_status << "\n";
}

test::~test() {
	// TODO Auto-generated destructor stub
}

