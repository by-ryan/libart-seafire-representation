#ifndef art__seafire__representation__send_hxx_
#define art__seafire__representation__send_hxx_

#include <art/seafire/representation/concepts.hxx>
#include <art/seafire/representation/metadata.hxx>

#include <art/seafire/protocol/rfc7231/content-type.hxx>

#include <art/seafire/server/request.hxx>
#include <art/seafire/server/response.hxx>

namespace art::seafire::representation
{

  template<Representation R>
  void
  send(server::request_t&,
       server::response_t&,
       protocol::status_code_t,
       R const&,
       bool);

} // namespace art::seafire::representation

#include <art/seafire/representation/send.txx>

#endif
