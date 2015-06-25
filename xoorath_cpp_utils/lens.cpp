#include "lens.h"

LensId LensToken::ms_UniqueId = 0;

LensToken::LensToken(const LensAction& addAction, const LensAction& removeAction, LensId id)
  : m_Add(addAction)
  , m_Remove(removeAction)
  , m_Id(id)
{
}

void LensToken::Add()
{
  m_Add(); 
}

void LensToken::Remove()
{ 
  m_Remove(); 
}

LensId LensToken::GetID() const 
{
  return m_Id;
}

LensId LensToken::NextId()
{ 
  return ms_UniqueId++; 
}