#ifndef NEB_PY_CORE_GAME_GAME_BASE_HPP
#define NEB_PY_CORE_GAME_GAME_BASE_HPP

#include <boost/python.hpp>

#include <neb/core/game/game/util/decl.hpp>

//#include <neb/py/core/actor/Base.hpp>

namespace neb { namespace py { namespace game { namespace game {
	class Base
	{
		public:
			typedef neb::fnd::game::game::base CORE_TYPE;
			static void			export_class();
			Base();
			Base(std::weak_ptr<CORE_TYPE>);
			void				add_scene(boost::python::object& scene_object);
		protected:
			std::weak_ptr<CORE_TYPE>		_M_game;
	};
}}}}

#endif
