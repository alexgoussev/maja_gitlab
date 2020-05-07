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
 * VERSION : 1.0.0 : FA : LAIG-FA-MAC-148399-CS : 14 novembre 2016 : Audit code - Correction qualite        *
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 10 avril 2010 : Creation
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsCommandIterationUpdateLevenbergMarquardt_h
#define __vnsCommandIterationUpdateLevenbergMarquardt_h

#include "itkCommand.h"
#include "itkLevenbergMarquardtOptimizer.h"

namespace vns
{

    class CommandIterationUpdateLevenbergMarquardt : public itk::Command
    {
    public:
        typedef CommandIterationUpdateLevenbergMarquardt Self;
        typedef itk::Command Superclass;
        typedef itk::SmartPointer<Self> Pointer;
        itkNewMacro (Self);
    protected:
        CommandIterationUpdateLevenbergMarquardt()
        {
            m_IterationNumber = 0;
        }
    public:
        typedef itk::LevenbergMarquardtOptimizer OptimizerType;
        typedef const OptimizerType * OptimizerPointer;

        void
        Execute(itk::Object *caller, const itk::EventObject & event)
        {
            Execute((const itk::Object *) caller, event);
        }

        void
        Execute(const itk::Object * object, const itk::EventObject & event)
        {

            OptimizerPointer optimizer = dynamic_cast<OptimizerPointer>(object);
            if (m_FunctionEvent.CheckEvent(&event))
            {
            }
            else if (m_GradientEvent.CheckEvent(&event))
            {
                vnsLogDebugMacro("Gradient " << optimizer->GetCachedDerivative())
            }
            else
            {
                // Esle for quality checks !
                vnsLogSuperDebugMacro("Gradient Execute in Else !!")

            }

        }
    private:
        unsigned long m_IterationNumber;

        itk::FunctionEvaluationIterationEvent m_FunctionEvent;
        itk::GradientEvaluationIterationEvent m_GradientEvent;
    };

} // end namespace vns

#endif
