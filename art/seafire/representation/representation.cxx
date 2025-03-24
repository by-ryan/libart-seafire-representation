#include <art/seafire/representation/representation.hxx>

namespace art::seafire::representation
{

  protocol::media_type_t
  representation_t::
  type() const
  {
    return r_->type();
  }

  std::optional<protocol::rfc7232::entity_tag_t>
  representation_t::
  etag() const
  {
    return r_->etag();
  }

  std::optional<std::chrono::system_clock::time_point>
  representation_t::
  last_modified() const
  {
    return r_->last_modified();
  }

  protocol::media_type_t
  representation_t::
  write_to(std::ostream& o) const
  {
    r_->write_to(o);
    return r_->type();
  }

  representation_t::concept_t::
  ~concept_t() = default;

} // namespace art::seafire::representation
