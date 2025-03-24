#ifndef art__seafire__representation__representation_hxx_
#define art__seafire__representation__representation_hxx_

#include <art/seafire/protocol/media-type.hxx>
#include <art/seafire/protocol/rfc7231/content-type.hxx>
#include <art/seafire/protocol/rfc7232/entity-tag.hxx>
#include <art/seafire/protocol/rfc7232/etag.hxx>
#include <art/seafire/protocol/rfc7232/last-modified.hxx>

#include <art/seafire/representation/concepts.hxx>
#include <art/seafire/representation/traits.hxx>

#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

namespace art::seafire::representation
{

  class representation_t
  {
  public:
    template<BasicRepresentation R>
    representation_t(R r);

    protocol::media_type_t
    type() const;

    std::optional<protocol::rfc7232::entity_tag_t>
    etag() const;

    std::optional<std::chrono::system_clock::time_point>
    last_modified() const;

    protocol::media_type_t
    write_to(std::ostream& o) const;

  private:
    struct concept_t;

    template<typename R>
    struct container_t;

    std::shared_ptr<concept_t const> r_;
  };

  struct representation_t::concept_t
  {
    virtual
    ~concept_t();

    virtual
    protocol::media_type_t
    type() const = 0;

    virtual
    std::optional<protocol::rfc7232::entity_tag_t>
    etag() const = 0;

    virtual
    std::optional<std::chrono::system_clock::time_point>
    last_modified() const = 0;

    virtual
    void
    write_to(std::ostream& o) const = 0;

  };

  template<BasicRepresentation R>
  struct representation_t::container_t<R>
    : representation_t::concept_t
  {
    using representation_type = R;
    using representation_traits = traits::representation_traits<representation_type>;

    container_t(representation_type r);

    protocol::media_type_t
    type() const override;

    std::optional<protocol::rfc7232::entity_tag_t>
    etag() const override;

    std::optional<std::chrono::system_clock::time_point>
    last_modified() const override;

    void
    write_to(std::ostream& o) const override;

    representation_type r;

  };

} // namespace art::seafire::representation

#include <art/seafire/representation/representation.txx>

#endif
