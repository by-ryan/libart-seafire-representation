namespace art::seafire::representation
{

  template<Representation R>
  representation_t
  select(R const& rep, std::optional<protocol::media_type_t> const& accepted_type)
  {
    using representation_traits = traits::representation_traits<R>;

    static constexpr bool is_content_negotiable{
      representation_traits::is_content_negotiable
    };

    if constexpr (is_content_negotiable) {
      return rep.select(accepted_type);
    }
    else {
      return rep;
    }
  }

} // namespace art::seafire::representation
