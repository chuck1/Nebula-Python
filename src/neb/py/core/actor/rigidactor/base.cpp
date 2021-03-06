#include <neb/fnd/core/actor/rigidactor/Base.hpp>
#include <neb/fnd/core/shape/base.hpp>
#include <neb/fnd/window/Base.hpp>

#include <neb/py/core/actor/rigidactor/base.hpp>
#include <neb/py/core/shape/cuboid/Desc.hpp>
#include <neb/py/core/shape/base.hpp>
#include <neb/py/window/Base.hpp>

typedef neb::py::core::actor::Base BASE;
typedef neb::py::core::actor::rigidactor::base THIS;

THIS::base()
{
	assert(0);
}
THIS::base(std::weak_ptr<CORE_TYPE> p):
	BASE(p)
{
}
std::shared_ptr<THIS::CORE_TYPE>	THIS::get_rigidactor()
{
	auto a = _M_actor.lock();
	assert(a);

	auto ra = std::dynamic_pointer_cast<CORE_TYPE>(a);
	assert(ra);

	return ra;
}
bp::object			THIS::createShapeCuboid(
		boost::python::object& desc_obj)
{
	typedef neb::py::core::shape::cuboid::Desc T;

	auto desc = bp::extract<T&>(desc_obj);
	
	auto rigidactor = get_rigidactor();

	//typedef neb::fnd::core::shape::cuboid::base S;
	typedef neb::fnd::core::shape::base S;

	auto shape = std::dynamic_pointer_cast<S>(rigidactor->createShapeCuboid(desc).lock());
	
	neb::py::core::shape::Base py_shape(shape);

	return bp::object(py_shape);

}
bp::object		THIS::createWeaponSimpleProjectile(
		boost::python::object& src_obj,
		boost::python::object& size_obj,
		boost::python::object& damage_obj,
		boost::python::object& velocity_obj
		)
{
	auto rigidactor = get_rigidactor();

	// src
	auto src_ex = boost::python::extract<neb::py::window::Base&>(src_obj);
	assert(src_ex.check());
	auto src_py = src_ex();

	auto src = src_py.window_.lock();
	assert(src);

	// size
	boost::python::extract<double> size_ex(size_obj);
	assert(size_ex.check());
	auto size = size_ex();

	// damage
	boost::python::extract<double> damage_ex(damage_obj);
	assert(damage_ex.check());
	auto damage = damage_ex();

	// velocity
	boost::python::extract<double> velocity_ex(velocity_obj);
	assert(velocity_ex.check());

	auto velocity = velocity_ex();

	rigidactor->createWeaponSimpleProjectile(src, size, damage, velocity);

	return boost::python::object();
}
void			THIS::export_class()
{
	typedef neb::py::core::actor::Base BASE;
	auto c = boost::python::class_< THIS, boost::python::bases<BASE> >("Base");
}





