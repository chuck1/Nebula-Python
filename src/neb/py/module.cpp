
#include <boost/version.hpp>

#include <neb/py/app/base.hpp>
#include <neb/py/window/Base.hpp>
#include <neb/py/context/Base.hpp>
#include <neb/py/environ/Scene.hpp>
#include <neb/py/core/pose.hpp>
#include <neb/py/core/scene/base.hpp>
#include <neb/py/core/shape/base.hpp>
#include <neb/py/core/shape/cuboid/Desc.hpp>
#include <neb/py/core/actor/rigiddynamic/base.hpp>
#include <neb/py/core/actor/control/rigidbody/Base.hpp>

#include <neb/py/net/server/Base.hpp>
#include <neb/py/net/client/Base.hpp>

#include <neb/py/game/game/Desc.hpp>
#include <neb/py/game/game/Base.hpp>

#include <neb/py/game/map/Base.hpp>
#include <neb/py/util/config.hpp>

/*
#if BOOST_VERSION==105500
#	warning 1_55
#elif BOOST_VERSION==104900
#	warning 1_49
#else
#	error
#endif
*/

class dummy_input {};
class dummy_scene {};
class dummy_shape {};
class dummy_shape_cuboid {};
class dummy_actor {};
class dummy_actor_rigidactor {};
class dummy_actor_rigiddynamic {};
class dummy_actor_control {};
class dummy_actor_control_rigidbody {};
class dummy_window {};
class dummy_context {};
class dummy_environ {};
class dummy_game {};
class dummy_game_game {};
class dummy_game_map {};

BOOST_PYTHON_MODULE(PY_LIB_NAME)
{
	export_pose();
	neb::py::app::Base::export_class();

	neb::py::net::server::Base::export_class();
	neb::py::net::client::Base::export_class();

	{
		// input
		bp::scope scope_input = bp::class_<dummy_input>("input");

		neb::py::input::js::export_class();
	}
	{
		// scene
		bp::scope scope_scene = bp::class_<dummy_scene>("scene");

		neb::py::core::scene::base::export_class();
	}
	{
		// actor
		bp::scope scope_actor = bp::class_<dummy_actor>("actor");

		neb::py::core::actor::Base::export_class();
		{
			// rigidactor
			bp::scope scope_actor_rigidactor = bp::class_<dummy_actor_rigidactor>("rigidactor");

			neb::py::core::actor::rigidactor::base::export_class();
		}
		{
			// rigiddynamic
			bp::scope scope_actor_rigiddynamic = bp::class_<dummy_actor_rigiddynamic>("rigiddynamic");

			neb::py::core::actor::rigiddynamic::base::export_class();
		}

		{
			// control
			bp::scope scope_actor_control = bp::class_<dummy_actor_control>("control");
			{
				// rigidbody
				bp::scope scope_actor_control_rigidbody = bp::class_<dummy_actor_control_rigidbody>("rigidbody");

				neb::py::core::actor::control::rigidbody::Base::export_class();
			}
		}
	}
	{
		// shape
		bp::scope scope_shape = bp::class_<dummy_shape>("shape");

		neb::py::core::shape::Base::export_class();

		bp::scope scope_shape_cuboid = bp::class_<dummy_shape_cuboid>("cuboid");

		neb::py::core::shape::cuboid::Desc::export_class();
	}
	{
		bp::scope scope_window = bp::class_<dummy_window>("window");

		neb::py::window::Base::export_class();
	}
	{
		bp::scope scope_context = bp::class_<dummy_context>("context");

		neb::py::context::Base::export_class();
	}
	{
		bp::scope scope_context = bp::class_<dummy_environ>("environ");

		neb::py::environ::Base::export_class();
		neb::py::environ::Three::export_class();
		neb::py::environ::Scene::export_class();
	}
	{
		// game
		bp::scope scope_game = bp::class_<dummy_game>("game");
		{
			// game
			bp::scope scope_game = bp::class_<dummy_game_game>("game");

			neb::py::game::game::Desc::export_class();
			neb::py::game::game::Base::export_class();
		}
		{
			// map
			bp::scope scope_game = bp::class_<dummy_game_map>("map");

			neb::py::game::map::Base::export_class();
		}
	}
}

