#ifndef art__seafire__representation__negotiate_hxx_
#define art__seafire__representation__negotiate_hxx_

#include <art/seafire/protocol/media-type.hxx>
#include <art/seafire/protocol/rfc7231/accept.hxx>
#include <art/seafire/representation/concepts.hxx>
#include <art/seafire/representation/traits.hxx>
#include <art/seafire/server/request.hxx>
#include <art/seafire/server/response.hxx>

#include <optional>

namespace art::seafire::representation
{

  // fixme: implement concept for handler.
  //

  template<Representation R, typename Handler>
  void
  negotiate(server::request_t& req,
            server::response_t& res,
            Handler&& handler);

} // namespace art::seafire::representation

#include <art/seafire/representation/negotiate.txx>

#endif
