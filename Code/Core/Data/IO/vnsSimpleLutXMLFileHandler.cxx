/*
 * SimpleSMACXMLFileHandler.cpp
 *
 *  Created on: 26 oct. 2017
 *      Author: besquis
 */

#include <vnsSimpleLutXMLFileHandler.h>

#include "otb_tinyxml.h"

namespace vns
{
SimpleLutXMLFileHandler::SimpleLutXMLFileHandler()
{

}

SimpleLutXMLFileHandler::~SimpleLutXMLFileHandler() {

}

void SimpleLutXMLFileHandler::LoadFile(const std::string& filename) {

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
	n_DOC = handle.FirstChild("LUT").Element();

	if(!n_DOC)
	{
		return;
	}

	TiXmlElement *n_IdxNode = n_DOC->FirstChildElement("Indexes");
	if(!n_IdxNode)
	{
		vnsExceptionDataMacro("No Indexes in the lut xml file");
	}

	TiXmlElement *n_Node = n_IdxNode->FirstChildElement("Altitude_Indexes");
	if(n_Node)
	{
		m_Container.SetAltitude_Indexes( Utilities::SplitStringAsDouble(n_Node->GetText()));
	}
	n_Node = n_IdxNode->FirstChildElement("AOT_Indexes");
	if(n_Node)
	{
		m_Container.SetAOT_Indexes(Utilities::SplitStringAsDouble(n_Node->GetText()));
	}
	n_Node = n_IdxNode->FirstChildElement("TOA_Reflectance_Indexes");
	if(n_Node)
	{
		m_Container.SetTOA_Reflectance_Indexes( Utilities::SplitStringAsDouble(n_Node->GetText()));
	}
	n_Node = n_IdxNode->FirstChildElement("Reflectance_Ratio_Indexes");
	if(n_Node)
	{
		m_Container.SetReflectance_Ratio_Indexes( Utilities::SplitStringAsDouble(n_Node->GetText()));
	}
	n_Node = n_IdxNode->FirstChildElement("View_Zenith_Angle_Indexes");
	if(n_Node)
	{
		m_Container.SetView_Zenith_Angle_Indexes( Utilities::SplitStringAsDouble(n_Node->GetText()));
	}
	n_Node = n_IdxNode->FirstChildElement("Solar_Zenith_Angle_Indexes");
	if(n_Node)
	{
		m_Container.SetSolar_Zenith_Angle_Indexes( Utilities::SplitStringAsDouble(n_Node->GetText()));
	}
	n_Node = n_IdxNode->FirstChildElement("Relative_Azimuth_Angle_Indexes");
	if(n_Node)
	{
		m_Container.SetRelative_Azimuth_Angle_Indexes( Utilities::SplitStringAsDouble(n_Node->GetText()) );
	}
	n_Node = n_IdxNode->FirstChildElement("Zenithal_Angle_Indexes");
	if(n_Node)
	{
		m_Container.SetZenithal_Angle_Indexes( Utilities::SplitStringAsDouble(n_Node->GetText()) );
	}

	n_Node = n_DOC->FirstChildElement("List_Of_Files");
	if(n_Node)
	{
		ListOfStrings l_ListOfFiles;
		for( TiXmlElement* n_Parameter = n_Node->FirstChildElement("Relative_File_Path"); n_Parameter != ITK_NULLPTR;
				n_Parameter = n_Parameter->NextSiblingElement() )
		{
			l_ListOfFiles.push_back(n_Parameter->GetText());
		}
		const std::string l_RootBasePath = itksys::SystemTools::GetFilenamePath(filename);
		Utilities::RelativeToAbsoluteFilename(l_RootBasePath, l_ListOfFiles);
		Utilities::CheckingExistenceFilenames(l_ListOfFiles);
		m_Container.SetListOfPackaged_DBL_Files(l_ListOfFiles);
	}
	fclose(fp);

}

}
