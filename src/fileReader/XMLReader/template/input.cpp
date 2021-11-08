// Copyright (c) 2005-2014 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "input.h"

// cuboid_t
// 

const cuboid_t::Position_type &cuboid_t::Position() const {
  return this->Position_.get();
}

cuboid_t::Position_type &cuboid_t::Position() {
  return this->Position_.get();
}

void cuboid_t::Position(const Position_type &x) {
  this->Position_.set(x);
}

void cuboid_t::Position(::std::unique_ptr<Position_type> x) {
  this->Position_.set(std::move(x));
}

const cuboid_t::distance_type &cuboid_t::distance() const {
  return this->distance_.get();
}

cuboid_t::distance_type &cuboid_t::distance() {
  return this->distance_.get();
}

void cuboid_t::distance(const distance_type &x) {
  this->distance_.set(x);
}

const cuboid_t::mass_type &cuboid_t::mass() const {
  return this->mass_.get();
}

cuboid_t::mass_type &cuboid_t::mass() {
  return this->mass_.get();
}

void cuboid_t::mass(const mass_type &x) {
  this->mass_.set(x);
}

const cuboid_t::meanValue_type &cuboid_t::meanValue() const {
  return this->meanValue_.get();
}

cuboid_t::meanValue_type &cuboid_t::meanValue() {
  return this->meanValue_.get();
}

void cuboid_t::meanValue(const meanValue_type &x) {
  this->meanValue_.set(x);
}


// vector_t
// 

const vector_t::x_type &vector_t::x() const {
  return this->x_.get();
}

vector_t::x_type &vector_t::x() {
  return this->x_.get();
}

void vector_t::x(const x_type &x) {
  this->x_.set(x);
}

const vector_t::y_type &vector_t::y() const {
  return this->y_.get();
}

vector_t::y_type &vector_t::y() {
  return this->y_.get();
}

void vector_t::y(const y_type &x) {
  this->y_.set(x);
}

const vector_t::z_type &vector_t::z() const {
  return this->z_.get();
}

vector_t::z_type &vector_t::z() {
  return this->z_.get();
}

void vector_t::z(const z_type &x) {
  this->z_.set(x);
}


// input_t
// 

const input_t::location_type &input_t::location() const {
  return this->location_.get();
}

input_t::location_type &input_t::location() {
  return this->location_.get();
}

void input_t::location(const location_type &x) {
  this->location_.set(x);
}

void input_t::location(::std::unique_ptr<location_type> x) {
  this->location_.set(std::move(x));
}


// simulation_t
// 

const simulation_t::Cuboid_sequence &simulation_t::Cuboid() const {
  return this->Cuboid_;
}

simulation_t::Cuboid_sequence &simulation_t::Cuboid() {
  return this->Cuboid_;
}

void simulation_t::Cuboid(const Cuboid_sequence &s) {
  this->Cuboid_ = s;
}

const simulation_t::Source_sequence &simulation_t::Source() const {
  return this->Source_;
}

simulation_t::Source_sequence &simulation_t::Source() {
  return this->Source_;
}

void simulation_t::Source(const Source_sequence &s) {
  this->Source_ = s;
}

const simulation_t::endTime_optional &simulation_t::endTime() const {
  return this->endTime_;
}

simulation_t::endTime_optional &simulation_t::endTime() {
  return this->endTime_;
}

void simulation_t::endTime(const endTime_type &x) {
  this->endTime_.set(x);
}

void simulation_t::endTime(const endTime_optional &x) {
  this->endTime_ = x;
}

const simulation_t::deltaT_optional &simulation_t::deltaT() const {
  return this->deltaT_;
}

simulation_t::deltaT_optional &simulation_t::deltaT() {
  return this->deltaT_;
}

void simulation_t::deltaT(const deltaT_type &x) {
  this->deltaT_.set(x);
}

void simulation_t::deltaT(const deltaT_optional &x) {
  this->deltaT_ = x;
}

const simulation_t::name_optional &simulation_t::name() const {
  return this->name_;
}

simulation_t::name_optional &simulation_t::name() {
  return this->name_;
}

void simulation_t::name(const name_type &x) {
  this->name_.set(x);
}

void simulation_t::name(const name_optional &x) {
  this->name_ = x;
}

void simulation_t::name(::std::unique_ptr<name_type> x) {
  this->name_.set(std::move(x));
}

#include <xsd/cxx/xml/dom/parsing-source.hxx>

// cuboid_t
//

cuboid_t::cuboid_t(const Position_type &Position, const distance_type &distance, const mass_type &mass,
                   const meanValue_type &meanValue)
    : ::xml_schema::type(), Position_(Position, this), distance_(distance, this), mass_(mass, this),
      meanValue_(meanValue, this) {
}

cuboid_t::cuboid_t(::std::unique_ptr<Position_type> Position, const distance_type &distance, const mass_type &mass,
                   const meanValue_type &meanValue)
    : ::xml_schema::type(), Position_(std::move(Position), this), distance_(distance, this), mass_(mass, this),
      meanValue_(meanValue, this) {
}

cuboid_t::cuboid_t(const cuboid_t &x, ::xml_schema::flags f, ::xml_schema::container *c) : ::xml_schema::type(x, f, c),
                                                                                           Position_(x.Position_, f,
                                                                                                     this),
                                                                                           distance_(x.distance_, f,
                                                                                                     this),
                                                                                           mass_(x.mass_, f, this),
                                                                                           meanValue_(x.meanValue_, f,
                                                                                                      this) {
}

cuboid_t::cuboid_t(const ::xercesc::DOMElement &e, ::xml_schema::flags f, ::xml_schema::container *c)
    : ::xml_schema::type(e, f | ::xml_schema::flags::base, c), Position_(this), distance_(this), mass_(this),
      meanValue_(this) {
  if ((f & ::xml_schema::flags::base) == 0) {
    ::xsd::cxx::xml::dom::parser<char> p(e, true, false, true);
    this->parse(p, f);
  }
}

void cuboid_t::parse(::xsd::cxx::xml::dom::parser<char> &p, ::xml_schema::flags f) {
  for (; p.more_content(); p.next_content(false)) {
    const ::xercesc::DOMElement &i(p.cur_element());
    const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(i));

    // Position
    //
    if (n.name() == "Position" && n.namespace_().empty()) {
      ::std::unique_ptr<Position_type> r(Position_traits::create(i, f, this));

      if (!Position_.present()) {
        this->Position_.set(::std::move(r));
        continue;
      }
    }

    break;
  }

  if (!Position_.present()) {
    throw ::xsd::cxx::tree::expected_element<char>("Position", "");
  }

  while (p.more_attributes()) {
    const ::xercesc::DOMAttr &i(p.next_attribute());
    const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(i));

    if (n.name() == "distance" && n.namespace_().empty()) {
      this->distance_.set(distance_traits::create(i, f, this));
      continue;
    }

    if (n.name() == "mass" && n.namespace_().empty()) {
      this->mass_.set(mass_traits::create(i, f, this));
      continue;
    }

    if (n.name() == "meanValue" && n.namespace_().empty()) {
      this->meanValue_.set(meanValue_traits::create(i, f, this));
      continue;
    }
  }

  if (!distance_.present()) {
    throw ::xsd::cxx::tree::expected_attribute<char>("distance", "");
  }

  if (!mass_.present()) {
    throw ::xsd::cxx::tree::expected_attribute<char>("mass", "");
  }

  if (!meanValue_.present()) {
    throw ::xsd::cxx::tree::expected_attribute<char>("meanValue", "");
  }
}

cuboid_t *cuboid_t::_clone(::xml_schema::flags f, ::xml_schema::container *c) const {
  return new class cuboid_t(*this, f, c);
}

cuboid_t &cuboid_t::operator=(const cuboid_t &x) {
  if (this != &x) {
    static_cast< ::xml_schema::type & > (*this) = x;
    this->Position_ = x.Position_;
    this->distance_ = x.distance_;
    this->mass_ = x.mass_;
    this->meanValue_ = x.meanValue_;
  }

  return *this;
}

cuboid_t::~cuboid_t() {
}

// vector_t
//

vector_t::vector_t(const x_type &x, const y_type &y, const z_type &z)
    : ::xml_schema::type(), x_(x, this), y_(y, this), z_(z, this) {
}

vector_t::vector_t(const vector_t &x, ::xml_schema::flags f, ::xml_schema::container *c) : ::xml_schema::type(x, f, c),
                                                                                           x_(x.x_, f, this),
                                                                                           y_(x.y_, f, this),
                                                                                           z_(x.z_, f, this) {
}

vector_t::vector_t(const ::xercesc::DOMElement &e, ::xml_schema::flags f, ::xml_schema::container *c)
    : ::xml_schema::type(e, f | ::xml_schema::flags::base, c), x_(this), y_(this), z_(this) {
  if ((f & ::xml_schema::flags::base) == 0) {
    ::xsd::cxx::xml::dom::parser<char> p(e, false, false, true);
    this->parse(p, f);
  }
}

void vector_t::parse(::xsd::cxx::xml::dom::parser<char> &p, ::xml_schema::flags f) {
  while (p.more_attributes()) {
    const ::xercesc::DOMAttr &i(p.next_attribute());
    const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(i));

    if (n.name() == "x" && n.namespace_().empty()) {
      this->x_.set(x_traits::create(i, f, this));
      continue;
    }

    if (n.name() == "y" && n.namespace_().empty()) {
      this->y_.set(y_traits::create(i, f, this));
      continue;
    }

    if (n.name() == "z" && n.namespace_().empty()) {
      this->z_.set(z_traits::create(i, f, this));
      continue;
    }
  }

  if (!x_.present()) {
    throw ::xsd::cxx::tree::expected_attribute<char>("x", "");
  }

  if (!y_.present()) {
    throw ::xsd::cxx::tree::expected_attribute<char>("y", "");
  }

  if (!z_.present()) {
    throw ::xsd::cxx::tree::expected_attribute<char>("z", "");
  }
}

vector_t *vector_t::_clone(::xml_schema::flags f, ::xml_schema::container *c) const {
  return new class vector_t(*this, f, c);
}

vector_t &vector_t::operator=(const vector_t &x) {
  if (this != &x) {
    static_cast< ::xml_schema::type & > (*this) = x;
    this->x_ = x.x_;
    this->y_ = x.y_;
    this->z_ = x.z_;
  }

  return *this;
}

vector_t::~vector_t() {
}

// input_t
//

input_t::input_t(const location_type &location) : ::xml_schema::type(), location_(location, this) {
}

input_t::input_t(const input_t &x, ::xml_schema::flags f, ::xml_schema::container *c) : ::xml_schema::type(x, f, c),
                                                                                        location_(x.location_, f,
                                                                                                  this) {
}

input_t::input_t(const ::xercesc::DOMElement &e, ::xml_schema::flags f, ::xml_schema::container *c)
    : ::xml_schema::type(e, f | ::xml_schema::flags::base, c), location_(this) {
  if ((f & ::xml_schema::flags::base) == 0) {
    ::xsd::cxx::xml::dom::parser<char> p(e, false, false, true);
    this->parse(p, f);
  }
}

void input_t::parse(::xsd::cxx::xml::dom::parser<char> &p, ::xml_schema::flags f) {
  while (p.more_attributes()) {
    const ::xercesc::DOMAttr &i(p.next_attribute());
    const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(i));

    if (n.name() == "location" && n.namespace_().empty()) {
      this->location_.set(location_traits::create(i, f, this));
      continue;
    }
  }

  if (!location_.present()) {
    throw ::xsd::cxx::tree::expected_attribute<char>("location", "");
  }
}

input_t *input_t::_clone(::xml_schema::flags f, ::xml_schema::container *c) const {
  return new class input_t(*this, f, c);
}

input_t &input_t::operator=(const input_t &x) {
  if (this != &x) {
    static_cast< ::xml_schema::type & > (*this) = x;
    this->location_ = x.location_;
  }

  return *this;
}

input_t::~input_t() {
}

// simulation_t
//

simulation_t::simulation_t()
    : ::xml_schema::type(), Cuboid_(this), Source_(this), endTime_(this), deltaT_(this), name_(this) {
}

simulation_t::simulation_t(const simulation_t &x, ::xml_schema::flags f, ::xml_schema::container *c)
    : ::xml_schema::type(x, f, c), Cuboid_(x.Cuboid_, f, this), Source_(x.Source_, f, this),
      endTime_(x.endTime_, f, this), deltaT_(x.deltaT_, f, this), name_(x.name_, f, this) {
}

simulation_t::simulation_t(const ::xercesc::DOMElement &e, ::xml_schema::flags f, ::xml_schema::container *c)
    : ::xml_schema::type(e, f | ::xml_schema::flags::base, c), Cuboid_(this), Source_(this), endTime_(this),
      deltaT_(this), name_(this) {
  if ((f & ::xml_schema::flags::base) == 0) {
    ::xsd::cxx::xml::dom::parser<char> p(e, true, false, true);
    this->parse(p, f);
  }
}

void simulation_t::parse(::xsd::cxx::xml::dom::parser<char> &p, ::xml_schema::flags f) {
  for (; p.more_content(); p.next_content(false)) {
    const ::xercesc::DOMElement &i(p.cur_element());
    const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(i));

    // Cuboid
    //
    if (n.name() == "Cuboid" && n.namespace_().empty()) {
      ::std::unique_ptr<Cuboid_type> r(Cuboid_traits::create(i, f, this));

      this->Cuboid_.push_back(::std::move(r));
      continue;
    }

    // Source
    //
    if (n.name() == "Source" && n.namespace_().empty()) {
      ::std::unique_ptr<Source_type> r(Source_traits::create(i, f, this));

      this->Source_.push_back(::std::move(r));
      continue;
    }

    break;
  }

  while (p.more_attributes()) {
    const ::xercesc::DOMAttr &i(p.next_attribute());
    const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(i));

    if (n.name() == "endTime" && n.namespace_().empty()) {
      this->endTime_.set(endTime_traits::create(i, f, this));
      continue;
    }

    if (n.name() == "deltaT" && n.namespace_().empty()) {
      this->deltaT_.set(deltaT_traits::create(i, f, this));
      continue;
    }

    if (n.name() == "name" && n.namespace_().empty()) {
      this->name_.set(name_traits::create(i, f, this));
      continue;
    }
  }
}

simulation_t *simulation_t::_clone(::xml_schema::flags f, ::xml_schema::container *c) const {
  return new class simulation_t(*this, f, c);
}

simulation_t &simulation_t::operator=(const simulation_t &x) {
  if (this != &x) {
    static_cast< ::xml_schema::type & > (*this) = x;
    this->Cuboid_ = x.Cuboid_;
    this->Source_ = x.Source_;
    this->endTime_ = x.endTime_;
    this->deltaT_ = x.deltaT_;
    this->name_ = x.name_;
  }

  return *this;
}

simulation_t::~simulation_t() {
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

::std::unique_ptr<::simulation_t> Simulation(const ::std::string &u, ::xml_schema::flags f,
                                             const ::xml_schema::properties &p) {
  ::xsd::cxx::xml::auto_initializer
      i((f & ::xml_schema::flags::dont_initialize) == 0, (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::tree::error_handler<char> h;

  ::xml_schema::dom::unique_ptr<::xercesc::DOMDocument> d(::xsd::cxx::xml::dom::parse<char>(u, h, p, f));

  h.throw_if_failed<::xsd::cxx::tree::parsing<char> >();

  return ::std::unique_ptr<::simulation_t>(::Simulation(std::move(d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr<::simulation_t> Simulation(const ::std::string &u, ::xml_schema::error_handler &h,
                                             ::xml_schema::flags f, const ::xml_schema::properties &p) {
  ::xsd::cxx::xml::auto_initializer
      i((f & ::xml_schema::flags::dont_initialize) == 0, (f & ::xml_schema::flags::keep_dom) == 0);

  ::xml_schema::dom::unique_ptr<::xercesc::DOMDocument> d(::xsd::cxx::xml::dom::parse<char>(u, h, p, f));

  if (!d.get())
    throw ::xsd::cxx::tree::parsing<char>();

  return ::std::unique_ptr<::simulation_t>(::Simulation(std::move(d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr<::simulation_t> Simulation(const ::std::string &u, ::xercesc::DOMErrorHandler &h,
                                             ::xml_schema::flags f, const ::xml_schema::properties &p) {
  ::xml_schema::dom::unique_ptr<::xercesc::DOMDocument> d(::xsd::cxx::xml::dom::parse<char>(u, h, p, f));

  if (!d.get())
    throw ::xsd::cxx::tree::parsing<char>();

  return ::std::unique_ptr<::simulation_t>(::Simulation(std::move(d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr<::simulation_t> Simulation(::std::istream &is, ::xml_schema::flags f,
                                             const ::xml_schema::properties &p) {
  ::xsd::cxx::xml::auto_initializer
      i((f & ::xml_schema::flags::dont_initialize) == 0, (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc(is);
  return ::Simulation(isrc, f, p);
}

::std::unique_ptr<::simulation_t> Simulation(::std::istream &is, ::xml_schema::error_handler &h, ::xml_schema::flags f,
                                             const ::xml_schema::properties &p) {
  ::xsd::cxx::xml::auto_initializer
      i((f & ::xml_schema::flags::dont_initialize) == 0, (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc(is);
  return ::Simulation(isrc, h, f, p);
}

::std::unique_ptr<::simulation_t> Simulation(::std::istream &is, ::xercesc::DOMErrorHandler &h, ::xml_schema::flags f,
                                             const ::xml_schema::properties &p) {
  ::xsd::cxx::xml::sax::std_input_source isrc(is);
  return ::Simulation(isrc, h, f, p);
}

::std::unique_ptr<::simulation_t> Simulation(::std::istream &is, const ::std::string &sid, ::xml_schema::flags f,
                                             const ::xml_schema::properties &p) {
  ::xsd::cxx::xml::auto_initializer
      i((f & ::xml_schema::flags::dont_initialize) == 0, (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc(is, sid);
  return ::Simulation(isrc, f, p);
}

::std::unique_ptr<::simulation_t> Simulation(::std::istream &is, const ::std::string &sid,
                                             ::xml_schema::error_handler &h, ::xml_schema::flags f,
                                             const ::xml_schema::properties &p) {
  ::xsd::cxx::xml::auto_initializer
      i((f & ::xml_schema::flags::dont_initialize) == 0, (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc(is, sid);
  return ::Simulation(isrc, h, f, p);
}

::std::unique_ptr<::simulation_t> Simulation(::std::istream &is, const ::std::string &sid,
                                             ::xercesc::DOMErrorHandler &h, ::xml_schema::flags f,
                                             const ::xml_schema::properties &p) {
  ::xsd::cxx::xml::sax::std_input_source isrc(is, sid);
  return ::Simulation(isrc, h, f, p);
}

::std::unique_ptr<::simulation_t> Simulation(::xercesc::InputSource &i, ::xml_schema::flags f,
                                             const ::xml_schema::properties &p) {
  ::xsd::cxx::tree::error_handler<char> h;

  ::xml_schema::dom::unique_ptr<::xercesc::DOMDocument> d(::xsd::cxx::xml::dom::parse<char>(i, h, p, f));

  h.throw_if_failed<::xsd::cxx::tree::parsing<char> >();

  return ::std::unique_ptr<::simulation_t>(::Simulation(std::move(d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr<::simulation_t> Simulation(::xercesc::InputSource &i, ::xml_schema::error_handler &h,
                                             ::xml_schema::flags f, const ::xml_schema::properties &p) {
  ::xml_schema::dom::unique_ptr<::xercesc::DOMDocument> d(::xsd::cxx::xml::dom::parse<char>(i, h, p, f));

  if (!d.get())
    throw ::xsd::cxx::tree::parsing<char>();

  return ::std::unique_ptr<::simulation_t>(::Simulation(std::move(d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr<::simulation_t> Simulation(::xercesc::InputSource &i, ::xercesc::DOMErrorHandler &h,
                                             ::xml_schema::flags f, const ::xml_schema::properties &p) {
  ::xml_schema::dom::unique_ptr<::xercesc::DOMDocument> d(::xsd::cxx::xml::dom::parse<char>(i, h, p, f));

  if (!d.get())
    throw ::xsd::cxx::tree::parsing<char>();

  return ::std::unique_ptr<::simulation_t>(::Simulation(std::move(d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr<::simulation_t> Simulation(const ::xercesc::DOMDocument &doc, ::xml_schema::flags f,
                                             const ::xml_schema::properties &p) {
  if (f & ::xml_schema::flags::keep_dom) {
    ::xml_schema::dom::unique_ptr<::xercesc::DOMDocument>
        d(static_cast< ::xercesc::DOMDocument * > (doc.cloneNode(true)));

    return ::std::unique_ptr<::simulation_t>(::Simulation(std::move(d), f | ::xml_schema::flags::own_dom, p));
  }

  const ::xercesc::DOMElement &e(*doc.getDocumentElement());
  const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(e));

  if (n.name() == "Simulation" && n.namespace_() == "") {
    ::std::unique_ptr<::simulation_t> r(::xsd::cxx::tree::traits<::simulation_t, char>::create(e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element<char>(n.name(), n.namespace_(), "Simulation", "");
}

::std::unique_ptr<::simulation_t> Simulation(::xml_schema::dom::unique_ptr<::xercesc::DOMDocument> d,
                                             ::xml_schema::flags f, const ::xml_schema::properties &) {
  ::xml_schema::dom::unique_ptr<::xercesc::DOMDocument> c
      (((f & ::xml_schema::flags::keep_dom) && !(f & ::xml_schema::flags::own_dom))
       ? static_cast< ::xercesc::DOMDocument * > (d->cloneNode(true)) : 0);

  ::xercesc::DOMDocument &doc(c.get() ? *c : *d);
  const ::xercesc::DOMElement &e(*doc.getDocumentElement());

  const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(e));

  if (f & ::xml_schema::flags::keep_dom)
    doc.setUserData(::xml_schema::dom::tree_node_key, (c.get() ? &c : &d), 0);

  if (n.name() == "Simulation" && n.namespace_() == "") {
    ::std::unique_ptr<::simulation_t> r(::xsd::cxx::tree::traits<::simulation_t, char>::create(e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element<char>(n.name(), n.namespace_(), "Simulation", "");
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

void operator<<(::xercesc::DOMElement &e, const cuboid_t &i) {
  e << static_cast< const ::xml_schema::type & > (i);

  // Position
  //
  {
    ::xercesc::DOMElement &s(::xsd::cxx::xml::dom::create_element("Position", e));

    s << i.Position();
  }

  // distance
  //
  {
    ::xercesc::DOMAttr &a(::xsd::cxx::xml::dom::create_attribute("distance", e));

    a << ::xml_schema::as_decimal(i.distance());
  }

  // mass
  //
  {
    ::xercesc::DOMAttr &a(::xsd::cxx::xml::dom::create_attribute("mass", e));

    a << ::xml_schema::as_decimal(i.mass());
  }

  // meanValue
  //
  {
    ::xercesc::DOMAttr &a(::xsd::cxx::xml::dom::create_attribute("meanValue", e));

    a << ::xml_schema::as_decimal(i.meanValue());
  }
}

void operator<<(::xercesc::DOMElement &e, const vector_t &i) {
  e << static_cast< const ::xml_schema::type & > (i);

  // x
  //
  {
    ::xercesc::DOMAttr &a(::xsd::cxx::xml::dom::create_attribute("x", e));

    a << ::xml_schema::as_decimal(i.x());
  }

  // y
  //
  {
    ::xercesc::DOMAttr &a(::xsd::cxx::xml::dom::create_attribute("y", e));

    a << ::xml_schema::as_decimal(i.y());
  }

  // z
  //
  {
    ::xercesc::DOMAttr &a(::xsd::cxx::xml::dom::create_attribute("z", e));

    a << ::xml_schema::as_decimal(i.z());
  }
}

void operator<<(::xercesc::DOMElement &e, const input_t &i) {
  e << static_cast< const ::xml_schema::type & > (i);

  // location
  //
  {
    ::xercesc::DOMAttr &a(::xsd::cxx::xml::dom::create_attribute("location", e));

    a << i.location();
  }
}

void operator<<(::xercesc::DOMElement &e, const simulation_t &i) {
  e << static_cast< const ::xml_schema::type & > (i);

  // Cuboid
  //
  for (simulation_t::Cuboid_const_iterator b(i.Cuboid().begin()), n(i.Cuboid().end()); b != n; ++b) {
    ::xercesc::DOMElement &s(::xsd::cxx::xml::dom::create_element("Cuboid", e));

    s << *b;
  }

  // Source
  //
  for (simulation_t::Source_const_iterator b(i.Source().begin()), n(i.Source().end()); b != n; ++b) {
    ::xercesc::DOMElement &s(::xsd::cxx::xml::dom::create_element("Source", e));

    s << *b;
  }

  // endTime
  //
  if (i.endTime()) {
    ::xercesc::DOMAttr &a(::xsd::cxx::xml::dom::create_attribute("endTime", e));

    a << ::xml_schema::as_decimal(*i.endTime());
  }

  // deltaT
  //
  if (i.deltaT()) {
    ::xercesc::DOMAttr &a(::xsd::cxx::xml::dom::create_attribute("deltaT", e));

    a << ::xml_schema::as_decimal(*i.deltaT());
  }

  // name
  //
  if (i.name()) {
    ::xercesc::DOMAttr &a(::xsd::cxx::xml::dom::create_attribute("name", e));

    a << *i.name();
  }
}

void Simulation(::std::ostream &o, const ::simulation_t &s, const ::xml_schema::namespace_infomap &m,
                const ::std::string &e, ::xml_schema::flags f) {
  ::xsd::cxx::xml::auto_initializer i((f & ::xml_schema::flags::dont_initialize) == 0);

  ::xml_schema::dom::unique_ptr<::xercesc::DOMDocument> d(::Simulation(s, m, f));

  ::xsd::cxx::tree::error_handler<char> h;

  ::xsd::cxx::xml::dom::ostream_format_target t(o);
  if (!::xsd::cxx::xml::dom::serialize(t, *d, e, h, f)) {
    h.throw_if_failed<::xsd::cxx::tree::serialization<char> >();
  }
}

void Simulation(::std::ostream &o, const ::simulation_t &s, ::xml_schema::error_handler &h,
                const ::xml_schema::namespace_infomap &m, const ::std::string &e, ::xml_schema::flags f) {
  ::xsd::cxx::xml::auto_initializer i((f & ::xml_schema::flags::dont_initialize) == 0);

  ::xml_schema::dom::unique_ptr<::xercesc::DOMDocument> d(::Simulation(s, m, f));
  ::xsd::cxx::xml::dom::ostream_format_target t(o);
  if (!::xsd::cxx::xml::dom::serialize(t, *d, e, h, f)) {
    throw ::xsd::cxx::tree::serialization<char>();
  }
}

void Simulation(::std::ostream &o, const ::simulation_t &s, ::xercesc::DOMErrorHandler &h,
                const ::xml_schema::namespace_infomap &m, const ::std::string &e, ::xml_schema::flags f) {
  ::xml_schema::dom::unique_ptr<::xercesc::DOMDocument> d(::Simulation(s, m, f));
  ::xsd::cxx::xml::dom::ostream_format_target t(o);
  if (!::xsd::cxx::xml::dom::serialize(t, *d, e, h, f)) {
    throw ::xsd::cxx::tree::serialization<char>();
  }
}

void Simulation(::xercesc::XMLFormatTarget &t, const ::simulation_t &s, const ::xml_schema::namespace_infomap &m,
                const ::std::string &e, ::xml_schema::flags f) {
  ::xml_schema::dom::unique_ptr<::xercesc::DOMDocument> d(::Simulation(s, m, f));

  ::xsd::cxx::tree::error_handler<char> h;

  if (!::xsd::cxx::xml::dom::serialize(t, *d, e, h, f)) {
    h.throw_if_failed<::xsd::cxx::tree::serialization<char> >();
  }
}

void Simulation(::xercesc::XMLFormatTarget &t, const ::simulation_t &s, ::xml_schema::error_handler &h,
                const ::xml_schema::namespace_infomap &m, const ::std::string &e, ::xml_schema::flags f) {
  ::xml_schema::dom::unique_ptr<::xercesc::DOMDocument> d(::Simulation(s, m, f));
  if (!::xsd::cxx::xml::dom::serialize(t, *d, e, h, f)) {
    throw ::xsd::cxx::tree::serialization<char>();
  }
}

void Simulation(::xercesc::XMLFormatTarget &t, const ::simulation_t &s, ::xercesc::DOMErrorHandler &h,
                const ::xml_schema::namespace_infomap &m, const ::std::string &e, ::xml_schema::flags f) {
  ::xml_schema::dom::unique_ptr<::xercesc::DOMDocument> d(::Simulation(s, m, f));
  if (!::xsd::cxx::xml::dom::serialize(t, *d, e, h, f)) {
    throw ::xsd::cxx::tree::serialization<char>();
  }
}

void Simulation(::xercesc::DOMDocument &d, const ::simulation_t &s, ::xml_schema::flags) {
  ::xercesc::DOMElement &e(*d.getDocumentElement());
  const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(e));

  if (n.name() == "Simulation" && n.namespace_() == "") {
    e << s;
  } else {
    throw ::xsd::cxx::tree::unexpected_element<char>(n.name(), n.namespace_(), "Simulation", "");
  }
}

::xml_schema::dom::unique_ptr<::xercesc::DOMDocument> Simulation(const ::simulation_t &s,
                                                                 const ::xml_schema::namespace_infomap &m,
                                                                 ::xml_schema::flags f) {
  ::xml_schema::dom::unique_ptr<::xercesc::DOMDocument>
      d(::xsd::cxx::xml::dom::serialize<char>("Simulation", "", m, f));

  ::Simulation(*d, s, f);
  return d;
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

