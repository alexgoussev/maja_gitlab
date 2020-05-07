
#include "itkObjectFactoryBase.h"
#include "itkFastMutexLock.h"
#include "itkMetaImageIOFactory.h"

namespace vns
{

template<typename TFactory>
class AtomicRegistry
{
public:
  AtomicRegistry()
    {
    m_Lock.Lock();
    if (m_Factory == ITK_NULLPTR)
      {
      typename TFactory::Pointer fac = TFactory::New();
      //itk::ObjectFactoryBase::UnRegisterFactory(factory);
      itk::ObjectFactoryBase::RegisterFactory(fac);
      m_Factory = fac;
      }
    m_Factory->Register();
    m_Lock.Unlock();
    }

  ~AtomicRegistry()
    {
    m_Lock.Lock();
    assert(m_Factory->GetReferenceCount() >= 2);
    m_Factory->UnRegister();
    if (m_Factory->GetReferenceCount() == 1)
      {
      itk::ObjectFactoryBase::UnRegisterFactory(m_Factory);
      m_Factory = ITK_NULLPTR;
      }
    m_Lock.Unlock();
    }

protected:

private:
  static itk::ObjectFactoryBase * m_Factory;

  itk::SimpleFastMutexLock m_Lock;
};

template<typename TFactory>
itk::ObjectFactoryBase * AtomicRegistry<TFactory>::m_Factory = ITK_NULLPTR;

/* Explicit instanciation */
template class AtomicRegistry<itk::MetaImageIOFactory>;

}
