#pragma once

template <typename T>
LensedValue<T>::LensedValue(const T& initialValue)
  : m_Value(initialValue)
{
}

template <typename T>
LensToken LensedValue<T>::CreateLens(const Transformation& transform, int priority, bool shouldAdd)
{
  auto tokenID = LensToken::NextId();
  auto token = LensToken(
    // ****** LensToken::m_Add
    [this, tokenID, transform, priority]()
    {
      auto existing = FindLens(tokenID);
      if (existing == m_Lenses.end())
      {
        m_Lenses.push_back(Lens<T>(transform, priority, tokenID));
        SortLenses();
      }
    },
    // ****** LensToken::m_Remove
    [this, tokenID]()
    {
      // no need to sort lenses after removing, should still be in order.
      RemoveLens(tokenID);
    }, 
    tokenID);

  if (shouldAdd)
    token.Add();

  return token;
}

template <typename T>
T LensedValue<T>::GetValue()
{
  T temp = m_Value;
  for (auto & lens : m_Lenses)
    lens.GetTransformation()(temp);

  return temp;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Helpers

template <typename T>
void LensedValue<T>::RemoveLens(U32 tokenID)
{
  auto existing = FindLens(tokenID);

  if (existing != m_Lenses.end())
    m_Lenses.erase(existing);
}

template <typename T>
void LensedValue<T>::SortLenses()
{
  std::sort(m_Lenses.begin(), m_Lenses.end(),
    [](const Lens<T>& a, const Lens<T>& b)
  {
    return a.GetPriority() > b.GetPriority();
  });
}

template <typename T>
typename LensedValue<T>::LensIterator LensedValue<T>::FindLens(U32 tokenID) const
{
  return std::find_if(m_Lenses.begin(), m_Lenses.end(),
    [tokenID](const Lens<T>& lens)
  {
    return tokenID == lens.GetId();
  });
}