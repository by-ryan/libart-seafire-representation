#ifndef art__seafire__representation__content_negotiable_hxx_
#define art__seafire__representation__content_negotiable_hxx_

#include <art/seafire/representation/representation.hxx>

#include <optional>

namespace art::seafire::representation
{

  template<typename T, typename... Formats>
  class content_negotiable_t
    : public T
  {
  public:
    using model_type = T;
    using model_type::model_type;

    content_negotiable_t(model_type const& other)
      : model_type{other}
    {}

    content_negotiable_t(model_type&& other)
      : model_type{other}
    {}

    representation_t
    select(std::optional<protocol::media_type_t> const&) const;

    static
    bool
    is_accepted(std::optional<protocol::media_type_t> const&);

  private:
    template<
      typename CurrentFormat,
      typename... MoreFormats
    >
    representation_t
    select(std::optional<protocol::media_type_t> const&) const;

    template<
      typename CurrentFormat,
      typename... MoreFormats
      >
    static
    bool
    is_accepted(std::optional<protocol::media_type_t> const&);

  };

} // namespace art::seafire::representation

#include <art/seafire/representation/content-negotiable.txx>

#endif
