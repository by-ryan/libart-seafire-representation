namespace art::seafire::representation
{

  template<BasicRepresentation R>
  representation_t::
  representation_t(R r)
    : r_{std::make_shared<container_t<R>>(std::move(r))}
  {}

  template<BasicRepresentation R>
  representation_t::container_t<R>::
  container_t(representation_type r)
    : r{std::move(r)}
  {}

  template<BasicRepresentation R>
  protocol::media_type_t
  representation_t::container_t<R>::
  type() const
  {
    return r.type();
  }

  template<BasicRepresentation R>
  std::optional<protocol::rfc7232::entity_tag_t>
  representation_t::container_t<R>::
  etag() const
  {
    if constexpr (representation_traits::has_entity_tag)
      return r.etag();

    return {};
  }

  template<BasicRepresentation R>
  std::optional<std::chrono::system_clock::time_point>
  representation_t::container_t<R>::
  last_modified() const
  {
    if constexpr (representation_traits::has_last_modified)
      return r.last_modified();

    return {};
  }

  template<BasicRepresentation R>
  void
  representation_t::container_t<R>::
  write_to(std::ostream& o) const
  {
    r.write_to(o);
  }

} // namespace art::seafire::representation
