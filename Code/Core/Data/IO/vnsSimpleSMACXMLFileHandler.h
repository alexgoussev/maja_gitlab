/*
 * SimpleSMACXMLFileHandler.h
 *
 *  Created on: 26 oct. 2017
 *      Author: besquis
 */
#ifndef CODE_CORE_DATA_IO_VNSSIMPLESMACXMLFILEHANDLER_H_
#define CODE_CORE_DATA_IO_VNSSIMPLESMACXMLFILEHANDLER_H_

#include "vnsUtilities.h"

namespace vns
{
class SimpleSMACXMLFileHandler : public itk::Object
{
public:
	typedef SimpleSMACXMLFileHandler Self;
	typedef itk::Object Superclass;
	typedef itk::SmartPointer<Self> Pointer;
	typedef itk::SmartPointer<const Self> ConstPointer;

	/** Run-time type information (and related methods). */
	itkTypeMacro( SimpleSMACXMLFileHandler, itk::Object )

	/** New macro for creation of through a Smart Pointer */
	itkNewMacro( Self )

	typedef Utilities::ListOfStrings ListOfStrings;
	typedef Utilities::ListOfDoubles ListOfDoubles;
	typedef Utilities::ListOfFilenames ListOfFilenames;

	void LoadFile(const std::string& filename);

	// Read the EarthExplorer field SMAC 'SMAC_NumberOfBands'
	unsigned int
	GetSMAC_NumberOfBands() const
	{
		return m_NumberOfBands;
	}
	// Read the EarthExplorer field SMAC 'SMAC_Coefficients'
	ListOfDoubles
	GetSMAC_Coefficients() const
	{
		return m_SMACCoeffs;
	}

protected:
	SimpleSMACXMLFileHandler();
	virtual ~SimpleSMACXMLFileHandler();
	unsigned int m_NumberOfBands;
	ListOfDoubles m_SMACCoeffs;
};

}
#endif /* CODE_CORE_DATA_IO_VNSSIMPLESMACXMLFILEHANDLER_H_ */
