/************************************************************************************************************
 *                                                                                                          *
 *                                ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo         *
 *                             o                                                                            *
 *                          o                                                                               *
 *                        o                                                                                 *
 *                      o                                                                                   *
 *                     o       ooooooo       ooooooo    o         o      oo                                 *
 *    o              o       o        o     o       o   o         o     o   o                               *
 *      o           o       o          o   o         o  o         o    o      o                             *
 *        o        o       o           o   o         o  o         o    o        o                           *
 *         o      o        o      oooo     o         o  o         o   o           o                         *
 *          o    o          o              o         o  o         o   o           o                         *
 *           o  o            o             o         o  o o      o   o          o                           *
 *            oo              oooooooo    o         o   o  oooooo   o      oooo                             *
 *                                                     o                                                    *
 *                                                     o                                                    *
 *                                                    o                            o                        *
 *                                                    o            o      oooo     o   o      oooo          *
 *                                                   o             o         o    o    o         o          *
 *                                                   o            o       ooo     o   o       ooo           *
 *                                                               o       o       o   o          o           *
 *                                                               ooooo   oooo    o   ooooo  oooo            *
 *                                                                              o                           *
 *                                                                                                          *
 ************************************************************************************************************
 *                                                                                                          *
 * Author: CS Systemes d'Information  (France)                                                              *
 *                                                                                                          *
 ************************************************************************************************************
 * HISTORIQUE                                                                                               *
 *                                                                                                          *
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 15 nov. 2017 : Creation
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#include "otbWrapperApplication.h"
#include "otbWrapperApplicationFactory.h"
#include "otbMultiImageFileWriter.h"
#include "vnsMacro.h"
#include "vnsLoggers.h"
#include "vnsUtilities.h"
#include <string>

namespace vns
{

namespace Wrapper
{

using namespace otb::Wrapper;

class ImageListWriter : public Application
{
public:
	/** Standard class typedefs. */
	typedef ImageListWriter               Self;
	typedef otb::Wrapper::Application     Superclass;
	typedef itk::SmartPointer<Self>       Pointer;
	typedef itk::SmartPointer<const Self> ConstPointer;

	/** Standard macro */
	itkNewMacro(Self);

	itkTypeMacro(ImageListWriter, otb::Wrapper::Application);

	/** Some convenient typedefs. */
	typedef DoubleImageType ImageType;
	typedef ImageType::ConstPointer ImageConstPointer;
	typedef ImageType::Pointer ImagePointer;
	typedef ImageType::PixelType PixelType;
	typedef DoubleVectorImageType                      VectorImageType;
	typedef VectorImageType::ConstPointer     VectorImageConstPointer;
	typedef VectorImageType::Pointer          VectorImagePointer;
	typedef ImageType::SizeType SizeType;
	typedef ImageType::SpacingType SpacingType;
	typedef ImageType::PointType PointType;



private:
	void DoInit()
	{
		SetName("ImageListWriter");
		SetDescription("ImageListWriter.");
		Loggers::GetInstance()->Initialize(GetName());
		// Documentation
		SetDocName("ImageListWriter");
		SetDocLongDescription("This application write a list of image to files, this is for in memory python use");
		SetDocLimitations("None");
		SetDocAuthors("MAJA-Team");
		SetDocSeeAlso("MAJA Doc");

		AddDocTag("Writer");

		AddParameter(ParameterType_InputImageList,  "il",   "Images");
		SetParameterDescription("il", "Images to write");
		AddParameter(ParameterType_StringList,  "filenames",   "Filenames to write to");
		SetParameterRole("filenames",Role::Role_Input);
		SetParameterDescription("filenames", "filenames to writeimages to");

		AddParameter(ParameterType_Int,  "nblinesperstrip",  "number of lines per strip");
		SetParameterDescription("nblinesperstrip","number of lines per strip");

		AddRAMParameter("ram");
		SetDefaultParameterInt("ram",2048);
	}

	void DoUpdateParameters()
	{
	}


	void DoExecute()
	{
		// Init filters
		vns::Utilities::ListOfStrings l_filename_list(GetParameterStringList("filenames"));

		if (GetNumberOfElementsInParameterInputImageList("il") != l_filename_list.size())
		{
			vnsExceptionDataMacro("Not the correct number of filenames for images");
		}

		otb::MultiImageFileWriter::Pointer l_multi_writer = otb::MultiImageFileWriter::New();

		for (unsigned int i = 0;i<GetNumberOfElementsInParameterInputImageList("il");i++ )
		{
			ImageBaseType* imgBase = GetParameterImageBase("il",i);
			const std::string l_filename = l_filename_list.at(i);
			// Guess the image type
			std::string className(imgBase->GetNameOfClass());
			bool l_type_found = false;
			if (className == "VectorImage")
			{
				UInt8VectorImageType* imgUInt8 = dynamic_cast<UInt8VectorImageType*>(imgBase);
				if (imgUInt8 )
				{
					l_multi_writer->AddInputImage(imgUInt8, l_filename);
					continue;
				}

				Int16VectorImageType* imgInt16 = dynamic_cast<Int16VectorImageType*>(imgBase);
				if (imgInt16)
				{
					l_multi_writer->AddInputImage(imgInt16, l_filename);
					continue;
				}

				UInt16VectorImageType* imgUInt16 = dynamic_cast<UInt16VectorImageType*>(imgBase);
				if (imgUInt16)
				{
					l_multi_writer->AddInputImage(imgUInt16, l_filename);
					continue;
				}

				Int32VectorImageType* imgInt32 = dynamic_cast<Int32VectorImageType*>(imgBase);
				if (imgInt32)
				{
					l_multi_writer->AddInputImage(imgInt32, l_filename);
					continue;
				}

				UInt32VectorImageType* imgUInt32 = dynamic_cast<UInt32VectorImageType*>(imgBase);
				if (imgUInt32)
				{
					l_multi_writer->AddInputImage(imgUInt32, l_filename);
					continue;
				}

				FloatVectorImageType* imgFloat = dynamic_cast<FloatVectorImageType*>(imgBase);
				if (imgFloat)
				{
					l_multi_writer->AddInputImage(imgFloat, l_filename);
					continue;
				}

				DoubleVectorImageType* imgDouble = dynamic_cast<DoubleVectorImageType*>(imgBase);
				if (imgDouble)
				{
					l_multi_writer->AddInputImage(imgDouble, l_filename);
					continue;
				}

			}
			else
			{
				UInt8ImageType* imgUInt8 = dynamic_cast<UInt8ImageType*>(imgBase);
				if (imgUInt8)
				{
					l_multi_writer->AddInputImage(imgUInt8, l_filename);
					continue;
				}

				Int16ImageType* imgInt16 = dynamic_cast<Int16ImageType*>(imgBase);
				if (imgInt16)
				{
					l_multi_writer->AddInputImage(imgInt16, l_filename);
					continue;
				}

				UInt16ImageType* imgUInt16 = dynamic_cast<UInt16ImageType*>(imgBase);
				if (imgUInt16)
				{
					l_multi_writer->AddInputImage(imgUInt16, l_filename);
					continue;
				}

				Int32ImageType* imgInt32 = dynamic_cast<Int32ImageType*>(imgBase);
				if (imgInt32)
				{
					l_multi_writer->AddInputImage(imgInt32, l_filename);
					continue;
				}

				UInt32ImageType* imgUInt32 = dynamic_cast<UInt32ImageType*>(imgBase);
				if (imgUInt32)
				{
					l_multi_writer->AddInputImage(imgUInt32, l_filename);
					continue;
				}

				FloatImageType* imgFloat = dynamic_cast<FloatImageType*>(imgBase);
				if (imgFloat)
				{
					l_multi_writer->AddInputImage(imgFloat, l_filename);
					continue;
				}

				DoubleImageType* imgDouble = dynamic_cast<DoubleImageType*>(imgBase);
				if (imgDouble)
				{
					l_multi_writer->AddInputImage(imgDouble, l_filename);
					continue;
				}

			}
			itkExceptionMacro("Unknown image type");
		}

		//Setup and execute the multiwriter
		l_multi_writer->SetNumberOfDivisionsStrippedStreaming(GetParameterInt("nblinesperstrip"));
		l_multi_writer->Update();

	}

	/** Filters declaration */

};

}
}

OTB_APPLICATION_EXPORT(vns::Wrapper::ImageListWriter)
