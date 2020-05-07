
#include <iostream>
#include "vnsLoggers.h"

static int TestCharge()
{
	vns::Loggers* log = vns::Loggers::GetInstance();
    	
	return (log == NULL)?EXIT_FAILURE:EXIT_SUCCESS;
}

static int TestConfigure()
{
	vns::Loggers* log = vns::Loggers::GetInstance();
    log->Initialize("Test Logger");
	return EXIT_SUCCESS;
}

static int TestMessageSort()
{

	vns::Loggers* log = vns::Loggers::GetInstance();
	log->SetMinLevel(vns::LoggerBase::INFO);

	vnsLogInfoMacro("Message INFO : should appear");

	vnsLogDebugMacro("Message DEBUG : should not appear");

	return EXIT_SUCCESS;

}

int vnsLoggerTU(int argc, char* argv[])
{

	if (TestCharge() != EXIT_SUCCESS)
	{
		std::cout << "TestCharge failed !" << std::endl;
		return EXIT_FAILURE;
	}

	if (TestConfigure() != EXIT_SUCCESS)
	{
		std::cout << "TestConfigure failed !" << std::endl;
		return EXIT_FAILURE;
	}

	if (TestMessageSort() != EXIT_SUCCESS)
	{
		std::cout << "TestMessageSort failed !" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}


