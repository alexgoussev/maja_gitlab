/*
 * SimpleLUTXMLFileHandler.h
 *
 *  Created on: 26 oct. 2017
 *      Author: besquis
 */
#ifndef CODE_CORE_DATA_IO_VNSSIMPLELUTXMLFILEHANDLER_H_
#define CODE_CORE_DATA_IO_VNSSIMPLELUTXMLFILEHANDLER_H_

#include "vnsUtilities.h"
#include "vnsSimpleLutXMLContainer.h"

namespace vns
{
class SimpleLutXMLFileHandler : public itk::Object
{
public:
	typedef SimpleLutXMLFileHandler Self;
	typedef itk::Object Superclass;
	typedef itk::SmartPointer<Self> Pointer;
	typedef itk::SmartPointer<const Self> ConstPointer;

	/** Run-time type information (and related methods). */
	itkTypeMacro( SimpleLutXMLFileHandler, itk::Object )

	/** New macro for creation of through a Smart Pointer */
	itkNewMacro( Self )

	typedef Utilities::ListOfDoubles ListOfDoubles;
	typedef Utilities::ListOfStrings ListOfStrings;

	void LoadFile(const std::string& filename);

    const SimpleLutXMLContainer& GetLutContainer() const
    {
    	return m_Container;
    }

protected:
	SimpleLutXMLFileHandler();
	virtual ~SimpleLutXMLFileHandler();

	SimpleLutXMLContainer m_Container;
};

}
#endif /* CODE_CORE_DATA_IO_VNSSIMPLESMACXMLFILEHANDLER_H_ */
