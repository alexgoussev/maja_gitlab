/*
 * SimpleLUTXMLFileHandler.h
 *
 *  Created on: 26 oct. 2017
 *      Author: besquis
 */
#ifndef CODE_CORE_DATA_IO_VNSSIMPLECAMSMAPXMLFILEHANDLER_H_
#define CODE_CORE_DATA_IO_VNSSIMPLECAMSMAPXMLFILEHANDLER_H_

#include "vnsUtilities.h"


namespace vns
{
class SimpleCAMSMapXMLFileHandler : public itk::Object
{
public:
	typedef SimpleCAMSMapXMLFileHandler Self;
	typedef itk::Object Superclass;
	typedef itk::SmartPointer<Self> Pointer;
	typedef itk::SmartPointer<const Self> ConstPointer;

	/** Run-time type information (and related methods). */
	itkTypeMacro( SimpleLutMapXMLFileHandler, itk::Object )

	/** New macro for creation of through a Smart Pointer */
	itkNewMacro( Self )

	typedef Utilities::ListOfDoubles ListOfDoubles;
	typedef Utilities::ListOfUIntegers ListOfUIntegers;
	typedef Utilities::ListOfStrings ListOfStrings;

    //Storage type
    struct ExtinctionCoeff {
        std::string Name;
        std::vector<double> Values;
        std::string Description;
    };

    struct ExtinctionCoeffList {
    	std::vector<ExtinctionCoeff> extinctionCoeffs;
    	bool RHDep;
    };

	typedef std::map<std::string, ExtinctionCoeffList> CAMSMapXml;

	void LoadFile(const std::string& filename);

	const CAMSMapXml& GetExtinctionMap() const
	{
		return m_MapContainer;
	}

	const ListOfUIntegers& GetRhTab() const
	{
		return m_RhTab;
	}

protected:
	SimpleCAMSMapXMLFileHandler();
	virtual ~SimpleCAMSMapXMLFileHandler();

	CAMSMapXml m_MapContainer;
	ListOfUIntegers m_RhTab;
};

}
#endif /* CODE_CORE_DATA_IO_VNSSIMPLESMACXMLFILEHANDLER_H_ */
