/*_____________________________________________________________________________

   Program:
       ___  ___     ____  ____  ____
      / __)(__ \   (_  _)(  _ \( ___)
      \__ \ / _/    _)(_  )___/ )__)
      (___/(____)  (____)(__)  (__)


   Group:           CS Systemes d'Information  (France)
                    GMV  (Spain)
                    GAEL Systems  (France)

   SW Component:    IDP-SC
   Author:          CS Systemes d'Information

   Language:        C++
  _____________________________________________________________________________

  HISTORY

  VERSION : 01.00.00 : <AR/CR> : <JIRA #> : <Date> : Creation of the file.

  END-HISTORY
  _____________________________________________________________________________

  $Id: vnsXmlFileHandlerTest.cxx 5019 2013-02-11 14:35:16Z tfeuvrie $
  _____________________________________________________________________________*/



#include <cstdlib>
#include <ctime>
#include "vnsUtilities.h"

#include "vnsXMLFileHandler.h"

int vnsXmlFileHandlerReadXPathTest(int /*argc*/, char * argv[])
{
	vns::XMLFileHandler::Pointer handler = vns::XMLFileHandler::New();
	handler->LoadFile(argv[1]);

	std::string result = handler->GetStringValue(argv[2]);

	std::cout<<"result= "<<result<<std::endl;

	return EXIT_SUCCESS;
}
