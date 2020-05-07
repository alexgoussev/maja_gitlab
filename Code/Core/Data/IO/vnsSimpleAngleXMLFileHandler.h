/*
 * SimpleLUTXMLFileHandler.h
 *
 *  Created on: 26 oct. 2017
 *      Author: besquis
 */
#ifndef CODE_CORE_DATA_IO_VNSSIMPLEANGLEXMLFILEHANDLER_H_
#define CODE_CORE_DATA_IO_VNSSIMPLEANGLEXMLFILEHANDLER_H_

#include "vnsUtilities.h"

namespace vns
{
class SimpleAngleXMLFileHandler : public itk::Object
{
public:
	typedef SimpleAngleXMLFileHandler Self;
	typedef itk::Object Superclass;
	typedef itk::SmartPointer<Self> Pointer;
	typedef itk::SmartPointer<const Self> ConstPointer;

	/** Run-time type information (and related methods). */
	itkTypeMacro( SimpleAngleXMLFileHandler, itk::Object )

	/** New macro for creation of through a Smart Pointer */
	itkNewMacro( Self )

	typedef Utilities::ListOfDoubles ListOfDoubles;
	typedef Utilities::ListOfStrings ListOfStrings;

	void LoadFile(const std::string& filename);

	double GetAngleSpacingCol() const {
		return m_angleSpacingCol;
	}
	double GetAngleSpacingRow() const {
		return m_angleSpacingRow;
	}
	const ListOfStrings& GetAngleZenithList() const {
		return m_angleZenithList;
	}

	const ListOfStrings& GetAngleAzimuthList() const {
		return m_angleAzimuthList;
	}

protected:
	SimpleAngleXMLFileHandler();
	virtual ~SimpleAngleXMLFileHandler();

	double m_angleSpacingCol;
	double m_angleSpacingRow;
	ListOfStrings m_angleZenithList;
	ListOfStrings m_angleAzimuthList;
};

}
#endif /* CODE_CORE_DATA_IO_VNSSIMPLESMACXMLFILEHANDLER_H_ */
