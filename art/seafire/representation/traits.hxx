#ifndef art__seafire__representation__traits_hxx_
#define art__seafire__representation__traits_hxx_

#include <art/seafire/common/traits.hxx>

#include <art/seafire/protocol/traits.hxx>
#include <art/seafire/protocol/media-type.hxx>

#include <art/seafire/protocol/rfc7232/entity-tag.hxx>
#include <art/seafire/protocol/rfc7232/last-modified.hxx>

#include <optional>
#include <tuple>
#include <type_traits>
#include <variant>

namespace art::seafire::representation::traits
{

  // has_entity_tag
  //

  template<typename, typename = std::void_t<>>
  struct has_entity_tag
    : std::false_type
  {};

  template<typename R>
  struct has_entity_tag<
    R,
    std::void_t<
      decltype(
        protocol::rfc7232::entity_tag_t{
          std::declval<
            common::traits::remove_optional_t<decltype(std::declval<R const>().etag())>
          >()
        }
      )
    >
  > : std::true_type
  {};

  template<typename R>
  constexpr bool has_entity_tag_v{has_entity_tag<R>::value};

  // has_last_modified
  //

  template<typename, typename = std::void_t<>>
  struct has_last_modified
    : std::false_type
  {};

  template<typename R>
  struct has_last_modified<
    R,
    std::void_t<
      decltype(
        std::chrono::system_clock::time_point{
          std::declval<
            common::traits::remove_optional_t<decltype(std::declval<R const>().last_modified())>
          >()
        }
      )
    >
  > : std::true_type
  {};

  template<typename R>
  constexpr bool has_last_modified_v{has_last_modified<R>::value};


  // =============================================================================
  // input representation.
  //

  template<
    typename R,
    typename = std::void_t<>
  >
  struct is_input_representation
    : std::false_type
  {};

  template<typename M>
  struct is_input_representation<
    M,
    std::void_t<
      decltype(
        bool{
          M::can_accept_input(
            std::declval<protocol::media_type_t>()
          )
        }
      ),
      decltype(
        M{
          std::declval<
            decltype(
              M::read_from(
                std::declval<std::optional<protocol::media_type_t>>(),
                std::declval<std::istream&>()
              )
            )
          >()
        }
      )
    >
  > : std::true_type {
  };

  template<typename... M>
  struct is_input_representation<
    std::variant<M...>
  > : std::bool_constant<
    (is_input_representation<M>::value && ...)
  > {
  };

  template<typename M>
  constexpr bool is_input_representation_v{is_input_representation<M>::value};

  template<typename M>
  struct is_variant_input_representation : std::false_type {};

  template<typename... M>
  struct is_variant_input_representation<
    std::variant<M...>
  > : is_input_representation<std::variant<M...>> {
  };

  template<typename M>
  constexpr bool is_variant_input_representation_v{is_variant_input_representation<M>::value};

  template<typename M>
  struct input_representation_traits
  {
    // TODO: DO.
  };


  // =============================================================================
  // (output) representation.
  //

  // is_basic_representation<R>
  //

  template<
    typename R,
    typename = std::void_t<>
  >
  struct is_basic_representation
    : std::false_type
  {};

  template<typename R>
  struct is_basic_representation<
    R,
    std::void_t<
      decltype(
        protocol::media_type_t{
          std::declval<R const>().type()
        }
      ),
      decltype(
        std::declval<R const>().write_to(std::declval<std::ostream&>())
      )
    >
  > : std::true_type
  {};

  template<typename R>
  constexpr bool is_basic_representation_v{
    is_basic_representation<R>::value
  };

  // is_content_negotiable_representation<R>
  //

  template<typename R, typename = std::void_t<>>
  struct is_content_negotiable_representation
    : std::false_type
  {};

  template<typename R>
  struct is_content_negotiable_representation<
    R,
    std::void_t<
      // check that r::is_accepted(protocol::media_type_t) is valid.
      //
      decltype(
        bool{
          R::is_accepted(
            std::declval<std::optional<protocol::media_type_t>>()
          )
        }
      ),
      // check that r{}.select(protocol::media_type_t) is valid.
      //
      decltype(
        std::declval<R const>().select(
          std::declval<std::optional<protocol::media_type_t>>()
        )
      )
    >
  > : std::bool_constant<
    is_basic_representation_v<
      // check that the type of the return value of r{}.select(...) is a representation.
      //
      decltype(
        std::declval<R const>().select(
          std::declval<std::optional<protocol::media_type_t>>()
        )
      )
    >
  >
  {};

  template<typename R>
  constexpr bool is_content_negotiable_representation_v{
    is_content_negotiable_representation<R>::value
  };

  // is_representation<R>
  //

  template<typename R>
  struct is_representation : std::bool_constant<
    is_basic_representation_v<R>
      || is_content_negotiable_representation_v<R>
  >
  {};

  template<typename R>
  constexpr bool is_representation_v{is_representation<R>::value};

  template<typename R>
  struct is_optional_representation
    : std::false_type
  {};

  template<typename R>
  struct is_optional_representation<std::optional<R>> : std::bool_constant<
    is_basic_representation_v<R>
      || is_content_negotiable_representation_v<R>
  >
  {};

  // is_optional_representation<R>
  //

  template<typename R>
  constexpr bool is_optional_representation_v{is_optional_representation<R>::value};

  // representation_traits<R>
  //

  template<typename R>
  struct representation_traits
  {
    using representation_type = common::traits::remove_optional_t<R>;

    static constexpr bool is_optional{
      // Using R here since optional<> is removed from representation_type.
      is_optional_representation_v<R>
    };

    static constexpr bool is_basic {
      is_basic_representation_v<representation_type>
    };

    static constexpr bool is_content_negotiable {
      is_content_negotiable_representation_v<representation_type>
    };

    static constexpr bool has_entity_tag{
      has_entity_tag_v<representation_type>
    };

    static constexpr bool has_last_modified{
      has_last_modified_v<representation_type>
    };
  };

} // namespace art::seafire::representation::traits

#endif
