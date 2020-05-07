/*
 * SimpleAngleXMLFileHandler.cpp
 *
 *  Created on: 26 oct. 2017
 *      Author: besquis
 */

#include <vnsSimpleAngleXMLFileHandler.h>

#include "otb_tinyxml.h"

namespace vns
{
SimpleAngleXMLFileHandler::SimpleAngleXMLFileHandler()
{

}

SimpleAngleXMLFileHandler::~SimpleAngleXMLFileHandler() {

}

void SimpleAngleXMLFileHandler::LoadFile(const std::string& filename) {

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
	    vnsExceptionDataMacro("Impossible to open "<<filename);
	}

	TiXmlHandle handle(&doc);

	TiXmlElement *n_DOC;
	n_DOC = handle.FirstChild("ANGLE").Element();

	if(!n_DOC)
	{

	    fclose(fp);
	    return;
	}

	TiXmlElement *n_Node = n_DOC->FirstChildElement("Zenithal_Angle_List");
	if(n_Node)
	{
		for( TiXmlElement* n_Parameter = n_Node->FirstChildElement("VALUES"); n_Parameter != ITK_NULLPTR;
				n_Parameter = n_Parameter->NextSiblingElement() )
		{
			m_angleZenithList.push_back(n_Parameter->GetText());
		}
	}

	n_Node = n_DOC->FirstChildElement("Azimuth_Angle_List");
	if(n_Node)
	{
		for( TiXmlElement* n_Parameter = n_Node->FirstChildElement("VALUES"); n_Parameter != ITK_NULLPTR;
				n_Parameter = n_Parameter->NextSiblingElement() )
		{
			m_angleAzimuthList.push_back(n_Parameter->GetText());
		}
	}

	n_Node = n_DOC->FirstChildElement("COL_STEP");
	if(n_Node)
	{
		m_angleSpacingCol = Utilities::AsDouble(n_Node->GetText());
	}

	n_Node = n_DOC->FirstChildElement("ROW_STEP");
	if(n_Node)
	{
		m_angleSpacingRow = Utilities::AsDouble(n_Node->GetText());
	}

	fclose(fp);



}

}
