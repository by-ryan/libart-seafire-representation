#ifndef art__seafire__representation__concepts_hxx_
#define art__seafire__representation__concepts_hxx_

#include <art/seafire/representation/traits.hxx>

namespace art::seafire::representation
{

  template<typename R>
  concept BasicRepresentation = traits::is_basic_representation_v<R>;

  template<typename R>
  concept ContentNegotiableRepresentation = traits::is_content_negotiable_representation_v<R>;

  template<typename R>
  concept Representation = traits::is_representation_v<R>;

} // namespace art::seafire::representation

#endif
