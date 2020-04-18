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
 * VERSION : 1.0.0 : FA : LAIG-FA-MAC-1988-CNES : 21 octobre 2016 : Correction qualite (code mort)          *
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 11 mai 2010 : Creation                                                           
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsBenchRH7Filter_txx
#define __vnsBenchRH7Filter_txx

#include "vnsBenchRH7Filter.h"
#include "vnsMacro.h"
#include "itkNumericTraits.h"

namespace vns
{
extern "C"
{
typedef void *( *c_void_cast )(void *);
}

	struct ThreadInfoStruct
    {
    unsigned int ThreadID;
    unsigned int NumberOfThreads;
    unsigned int NumberOfBands;
    unsigned int NumberOfPixels;
    void *UserData;
    };

	template<class TInputImage, class TOutputImage>
	class machin
	{
	public :
		void doBidule(const unsigned int nbBands, const unsigned int nbPixels,const unsigned int threadId)
		{
			vnsLogDebugMacro("Plop "<<threadId);
			for (unsigned int i = 0; i < nbPixels;i++)
			{
				typename TInputImage::PixelType pix;
				pix.SetSize(nbBands);
				pix.Fill(i);
				typename TOutputImage::PixelType pixou = static_cast<typename TOutputImage::PixelType>(pix*100.0);
			}
		}
	};


    /** Constructor */
    template<class TInputImage, class TOutputImage>
    BenchRH7<TInputImage, TOutputImage>::BenchRH7(const unsigned int nbThreads, const unsigned int nbBands, const unsigned int nbPixels) :
	m_nbThreads(nbThreads),m_nbBands(nbBands),m_nbPixels(nbPixels)
        {
        }

    /** Destructor */
    template<class TInputImage, class TOutputImage>
    BenchRH7<TInputImage, TOutputImage>::~BenchRH7()
        {
        }

    template<class TInputImage, class TOutputImage>
        void
		BenchRH7<TInputImage, TOutputImage>::Update()
        {
            OutputImagePixelType outputVectorValue;

            outputVectorValue.SetSize(m_nbBands);
            outputVectorValue.Fill(itk::NumericTraits<OutputImageInternalPixelType>::Zero);
            const unsigned int nbValue = outputVectorValue.GetSize();

            //Doer
            machin<TInputImage,TOutputImage> un_machin;

            // thread loop
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            ThreadInfoStruct   infoarray[m_nbThreads];
            pthread_t threadarray[m_nbThreads];
            for (unsigned int i = 0; i< m_nbThreads;i++)
            {
            	infoarray[i].NumberOfBands = m_nbBands;
            	infoarray[i].NumberOfPixels = m_nbPixels;
            	infoarray[i].NumberOfThreads = m_nbThreads;
            	infoarray[i].ThreadID = i;
            	infoarray[i].UserData = (void*)(&un_machin);
            	int threadError = pthread_create( &( threadarray[i] ),
            			&attr, reinterpret_cast<c_void_cast>( this->ThreaderCallback ),
						( (void *)( &infoarray[i] ) ) );
            	 if( threadError != 0 )
            	 {
            		 vnsStaticExceptionMacro("Unable to create a thread.  pthread_create() returned "<< threadError);
            	 }
            }
            for (unsigned int i = 0; i< m_nbThreads;i++)
            {
            	// Using POSIX threads
            	if ( pthread_join(threadarray[i], ITK_NULLPTR) )
            	{
            		vnsStaticExceptionMacro("Unable to join thread : "<<i);
            	}
            }
        }

    // Callback routine used by the threading library. This routine just calls
    // the ThreadedGenerateData method after setting the correct region for this
    // thread.
    template<class TInputImage, class TOutputImage>
    ITK_THREAD_RETURN_TYPE
	BenchRH7<TInputImage,TOutputImage>
    ::ThreaderCallback(void *arg)
    {
      machin<TInputImage,TOutputImage> *str;
      unsigned int ThreadIdType,total, threadId, threadCount, nbBands, nbPixels;

      threadId = ( (ThreadInfoStruct *)( arg ) )->ThreadID;
      threadCount = ( (ThreadInfoStruct *)( arg ) )->NumberOfThreads;
      nbBands = ( (ThreadInfoStruct *)( arg ) )->NumberOfBands;
      nbPixels = ( (ThreadInfoStruct *)( arg ) )->NumberOfPixels;


      str = (machin<TInputImage,TOutputImage> *)( ( (ThreadInfoStruct *)( arg ) )->UserData );
      //Do bidule on the machin
      vnsLogDebugMacro("Starting thread number "<<threadId<<" / "<<threadCount);
      str->doBidule(nbBands, nbPixels, threadId);
      vnsLogDebugMacro("Finished thread number "<<threadId<<" / "<<threadCount);
      return ITK_THREAD_RETURN_VALUE;
    }

} // End namespace vns

#endif /* __vnsBenchRH7Filter_txx */
