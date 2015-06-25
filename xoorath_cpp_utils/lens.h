#pragma once

#include "xoorath_cpp_utils.h"
#include "lens_internal.h"

#include <algorithm>
#include <functional>
#include <vector>


// The idea for the lens system is taken from Twisted Oak Studios             (see: http://twistedoakstudios.com/blog/Post1823_decoupling-shared-control)
// It's a game developers practical approach to monoids                       (see: http://mathworld.wolfram.com/Monoid.html)
// A C# implementation from Twisted Oak Studios is available on their github  (see: https://github.com/TwistedOakStudios/TOUnityUtilities/tree/master/Assets/Lenses)

// Here I implement their system for use in C++ with some minor modifications I found helpful.


class LensToken
{
public:
  LensToken(const LensAction& addAction, const LensAction& removeAction, LensId id);

          void        Add();
          void        Remove();
          LensId      GetID() const;
  static  LensId      NextId();

private:
          LensAction  m_Add;
          LensAction  m_Remove;
          LensId      m_Id;
  static  LensId      ms_UniqueId;
};

template <typename T>
class LensedValue
{
  typedef           std::function<void(T&)>         Transformation;
  typedef           std::vector<Lens<T>>            LensCollection;
  typedef typename  LensCollection::const_iterator  LensIterator;

public:
  LensedValue(const T& initialValue);

  LensToken       CreateLens(const Transformation& transform, int priority = 0, bool shouldAdd = true);
  T               GetValue();

private:
  explicit        LensedValue(const LensedValue& other) { }; // disallow copying
  LensIterator    FindLens(LensId tokenID) const;
  void            RemoveLens(LensId tokenID);
  void            SortLenses();

  T               m_Value;
  LensCollection  m_Lenses;
};

#include "lens_impl.h"