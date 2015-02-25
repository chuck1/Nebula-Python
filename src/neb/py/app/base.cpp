
#include <boost/python.hpp>

#include <neb/fnd/app/Base.hpp>
//#include <neb/fnd/app/__core.hpp>

#include <neb/py/core/scene/base.hpp>
#include <neb/py/app/base.hpp>
#include <neb/py/game/game/Base.hpp>
#include <neb/py/window/Base.hpp>
#include <neb/py/context/Base.hpp>
#include <neb/py/environ/Base.hpp>
#include <neb/py/gui/layout/Base.hpp>
//#include <neb/py/game/game/Base.hpp>

typedef neb::py::app::Base THIS;

THIS::Base()
{
}
THIS::Base(std::shared_ptr<neb::fnd::app::Base> app):
	_M_weak_app(app)
{
	assert(app);
}
boost::python::object			THIS::createWindow()
{
	//auto app = neb::fnd::app::Base::global();
	auto app = _M_weak_app.lock();

	auto window = app->createWindow();

	neb::py::window::Base pw(window);

	return boost::python::object(pw);
}
boost::python::object			THIS::createLayout(
		boost::python::object& window_obj,
		boost::python::object& environ_obj)
{
	//auto app = neb::fnd::app::Base::global();
	auto app = _M_weak_app.lock();

	// window
	auto window_ex = boost::python::extract<neb::py::window::Base&>(window_obj);
	assert(window_ex.check());
	auto window_py = window_ex();

	auto window = window_py.get_window();
	assert(window);

	// environ
	auto environ_ex = boost::python::extract<neb::py::environ::Base&>(environ_obj);
	assert(environ_ex.check());
	auto environ_py = environ_ex();

	auto environ = environ_py.environ_.lock();
	assert(environ);


	auto layout = app->createLayout(window, environ /*context*/);
	
	neb::py::gui::layout::Base layout_py(layout);

	return boost::python::object(layout_py);
}
boost::python::list			THIS::getScenes()
{
	boost::python::list l;

	//auto app = neb::fnd::app::Base::global();
	auto app = _M_weak_app.lock();
	
	neb::fnd::core::scene::util::parent & p = *app;
	
	for(auto it : p)
	{
		neb::py::core::scene::base ps(it.second.ptr_);
		//ps.scene_ = scene;
		l.append(ps);
	}
	
	return l;
}
boost::python::list			THIS::get_windows()
{
	boost::python::list l;

	//auto app = neb::fnd::app::Base::global();
	auto app = _M_weak_app.lock();
	
	neb::fnd::window::util::Parent & p = *app;
	
	for(auto it : p)
	{
		neb::py::window::Base ps(it.second.ptr_);
		//ps.scene_ = scene;
		l.append(ps);
	}
	
	return l;
}
boost::python::object			THIS::create_scene()
{
	//auto app = neb::fnd::app::Base::global();
	auto app = _M_weak_app.lock();
	
	auto scene = app->createScene();

	return bp::object(neb::py::core::scene::base(scene));
}
boost::python::object			THIS::createGame()
{
	//auto app = neb::fnd::app::Base::global();
	auto app = _M_weak_app.lock();
	
	auto game = app->createGame();
	
	//return bp::object();
	return boost::python::object(neb::py::game::game::Base(game));
}
void					THIS::export_class()
{
	auto c = boost::python::class_<THIS>("Base");
	
	c.def("createWindow",	&THIS::createWindow);
	c.def("createLayout",	&THIS::createLayout);
	c.def("createGame",	&THIS::createGame);
	c.def("create_scene",	&THIS::create_scene);
	c.def("getScenes",	&THIS::getScenes);
	c.def("get_windows",	&THIS::get_windows);

	//boost::python::class_<neb::py::app::base>("App");
	//	.def("createActorRigidStaticCube", &neb::py::core::scene::base::createActorRigidStaticCube);
	//        .def("greet", &World::greet)
	//       .def("set", &World::set)
	//    ;
}



