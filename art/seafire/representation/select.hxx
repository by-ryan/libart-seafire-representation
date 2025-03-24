#ifndef art__seafire__representation__select_hxx_
#define art__seafire__representation__select_hxx_

#include <art/seafire/protocol/media-type.hxx>

#include <art/seafire/representation/concepts.hxx>
#include <art/seafire/representation/representation.hxx>
#include <art/seafire/representation/traits.hxx>

#include <optional>

namespace art::seafire::representation
{

  template<Representation R>
  representation_t
  select(R const&, std::optional<protocol::media_type_t> const&);

} // namespace art::seafire::representation

#include <art/seafire/representation/select.txx>

#endif
