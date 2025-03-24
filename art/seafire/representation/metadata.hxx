#ifndef art__seafire__representation__metadata_hxx_
#define art__seafire__representation__metadata_hxx_

#include <art/seafire/protocol/media-type.hxx>
#include <art/seafire/protocol/rfc7232/entity-tag.hxx>

#include <art/seafire/representation/concepts.hxx>
#include <art/seafire/representation/representation.hxx>
#include <art/seafire/representation/traits.hxx>

#include <art/uri/uri.hxx>

#include <chrono>
#include <optional>

namespace art::seafire::representation
{

  // etag
  //
  template<BasicRepresentation BR>
  std::optional<protocol::rfc7232::entity_tag_t>
  get_etag(BR const& rep)
  {
    using local_traits = traits::representation_traits<BR>;

    if constexpr (local_traits::has_entity_tag_t)
      return rep.etag();

    return std::nullopt;
  }

  inline
  std::optional<protocol::rfc7232::entity_tag_t>
  get_etag(representation_t const& rep)
  {
    return rep.etag();
  }


  // last-modified
  //
  template<BasicRepresentation BR>
  std::optional<std::chrono::system_clock::time_point>
  get_last_modified(BR const& rep)
  {
    using local_traits = traits::representation_traits<BR>;

    if constexpr (local_traits::has_last_modified)
      return rep.last_modified();

    return std::nullopt;
  }

  inline
  std::optional<std::chrono::system_clock::time_point>
  get_last_modified(representation_t const& rep)
  {
    return rep.last_modified();
  }

} // namespace art::seafire::representation

#endif
