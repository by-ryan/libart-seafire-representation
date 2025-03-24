namespace art::seafire::representation
{

  template<
    typename T,
    typename... Formats
    >
  representation_t
  content_negotiable_t<T, Formats...>::
  select(std::optional<protocol::media_type_t> const& type) const
  {
    return select<Formats...>(type);
  }

  template<
    typename T,
    typename... Formats
    >
  bool
  content_negotiable_t<T, Formats...>::
  is_accepted(std::optional<protocol::media_type_t> const& type)
  {
    return is_accepted<Formats...>(type);
  }

  template<
    typename T,
    typename... Formats
    >
  template<
    typename CurrentFormat,
    typename... MoreFormats
    >
  representation_t
  content_negotiable_t<T, Formats...>::
  select(std::optional<protocol::media_type_t> const& type) const
  {
    // Does the CurrentFormat support serialization of type T?
    //
    static constexpr bool supported{CurrentFormat::supports_serialization};

    if constexpr (supported) {
      // Can the CurrentFormat produce output accepted by the client?
      //
      if (!type || CurrentFormat::is_accepted(*type)) {
        return CurrentFormat{*this};
      }
    }

    if constexpr (sizeof...(MoreFormats) > 0) {
      return select<MoreFormats...>(type);
    }

    // fixme: not acceptable, throw something.
    //

    throw "temporary"; // fixme: change
  }

  template<
    typename T,
    typename... Formats
    >
  template<
    typename CurrentFormat,
    typename... MoreFormats
    >
  bool
  content_negotiable_t<T, Formats...>::
  is_accepted(std::optional<protocol::media_type_t> const& type)
  {
    // Does the CurrentFormat support serialization of type T?
    //
    static constexpr bool supported{CurrentFormat::supports_serialization};

    if constexpr (supported) {
      // Can the CurrentFormat produce output accepted by the client?
      //
      if (!type || CurrentFormat::is_accepted(*type))
        return true;
    }

    if constexpr (sizeof...(MoreFormats) > 0) {
      return is_accepted<MoreFormats...>(type);
    }

    return false;
  }

} // namespace art::seafire::representation
