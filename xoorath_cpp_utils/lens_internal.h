#pragma once

#include <algorithm>
#include <functional>
#include <vector>

typedef std::function<void()> LensAction;
typedef unsigned int          LensId;

//////////////////////////////////////////////////////////////////////////////////////////
// Lens (Internal)
// Stores the lens method and priority of this lens
template <typename T>
class Lens
{
  typedef std::function<void(T&)> Transformation;
public:
  Lens(const Transformation& transformation, int priority, LensId id)
    : m_Transformation(transformation)
    , m_Priority(priority)
    , m_Id(id)
  {
  }

  int             GetPriority()       const { return m_Priority; }
  Transformation  GetTransformation() const { return m_Transformation; }
  LensId          GetId()             const { return m_Id; }

private:
  Transformation  m_Transformation;
  int             m_Priority;
  LensId          m_Id;
};