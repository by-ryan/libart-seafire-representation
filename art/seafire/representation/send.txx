namespace art::seafire::representation
{

  template<Representation R>
  void
  send(server::request_t& req,
       server::response_t& res,
       protocol::status_code_t status,
       R const& rep,
       bool send_content)
  {
    namespace rfc7231 = protocol::rfc7231;
    namespace rfc7232 = protocol::rfc7232;

    set<rfc7231::content_type_t>(res, rep.type());

    if (auto etag = get_etag(rep); etag) {
      set<rfc7232::etag_t>(res, *etag);
    }

    if (auto last_modified = get_last_modified(rep); last_modified) {
      set<rfc7232::last_modified_t>(res, *last_modified);
    }

    if (!send_content) {
      res.send(status);
      return;
    }

    auto content_stream = res.allocate_stream();
    rep.write_to(content_stream);

    res.send(status, content_stream);
  }

} // namespace art::seafire::representation
