/*
 * SimpleSMACXMLFileHandler.cpp
 *
 *  Created on: 26 oct. 2017
 *      Author: besquis
 */

#include <vnsSimpleSMACXMLFileHandler.h>

#include "otb_tinyxml.h"

namespace vns
{
SimpleSMACXMLFileHandler::SimpleSMACXMLFileHandler() : m_NumberOfBands(0)
{

}

SimpleSMACXMLFileHandler::~SimpleSMACXMLFileHandler() {

}

void SimpleSMACXMLFileHandler::LoadFile(const std::string& filename) {

	if(filename.empty())
	{
		std::cerr <<"Input XML Filename is empty" << std::endl;
	}

	// Open the xml file
	TiXmlDocument doc;

	//Use itksys::SystemTools::FOpen() and close it below because
	//TiXmlDocument::TiXmlFileOpen( ) is not exposed from tinyXML library. Even
	//though its available in the TiXmlDocument::SaveFile().
	FILE* fp =  itksys::SystemTools::Fopen(filename.c_str(), "rb");

	if (!doc.LoadFile(fp , TIXML_ENCODING_UTF8))
	{
	    fclose(fp);
		return;
	}

	TiXmlHandle handle(&doc);

	TiXmlElement *n_DOC;
	n_DOC = handle.FirstChild("SMAC").Element();

	if(!n_DOC)
	{
		return;
	}

	TiXmlElement *n_SMACNumberNode   = n_DOC->FirstChildElement("SMAC_NumberOfBands");
	if(!n_SMACNumberNode)
	{
		return;
	}
	m_NumberOfBands = Utilities::AsUnsignedInt(n_SMACNumberNode->GetText());

	TiXmlElement *n_SMACCoeffsNode   = n_DOC->FirstChildElement("SMAC_Coefficients");
	if(!n_SMACCoeffsNode)
	{
		return;
	}
	m_SMACCoeffs = Utilities::SplitStringAsDouble(n_SMACCoeffsNode->GetText());

	fclose(fp);


}

}
