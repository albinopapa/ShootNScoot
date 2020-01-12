#pragma once

namespace sns
{
	class Asteroid;
	class Ammo;
	class Boss;
	class Enemy;
	class Hero;
	class Shield;

	class AsteroidController;
	class AmmoController;
	class BossController;
	class EnemyController;
	class HeroController;
	class ShieldController;

	template<typename Model> struct controller;
	template<> struct controller<Asteroid> { using type = AsteroidController; };
	template<> struct controller<Ammo> { using type = AmmoController; };
	template<> struct controller<Boss> { using type = BossController; };
	template<> struct controller<Enemy> { using type = EnemyController; };
	template<> struct controller<Hero> { using type = HeroController; };
	template<> struct controller<Shield> { using type = ShieldController; };

	template<typename Model> using controller_t = typename controller<Model>::type;

	template<typename T> struct is_collidable;
	template<> struct is_collidable<Asteroid>
	{
		template<typename U> struct with :std::false_type {};
		template<> struct with<Asteroid> :std::true_type {};
		template<> struct with<Ammo> : std::true_type {};
		template<> struct with<Enemy> : std::true_type {};
		template<> struct with<Hero> : std::true_type {};
	};
	template<> struct is_collidable<Ammo>
	{
		template<typename U> struct with :std::false_type {};
		template<> struct with<Asteroid> :std::true_type {};
		template<> struct with<Boss> : std::true_type {};
		template<> struct with<Enemy> : std::true_type {};
		template<> struct with<Hero> : std::true_type {};

	};
	template<> struct is_collidable<Enemy>
	{
		template<typename U> struct with :std::false_type {};
		template<> struct with<Asteroid> :std::true_type {};
		template<> struct with<Ammo> :std::true_type {};
		template<> struct with<Hero> :std::true_type {};
	};
	template<> struct is_collidable<Hero>
	{
		template<typename U> struct with :std::false_type {};
		template<> struct with<Asteroid> :std::true_type {};
		template<> struct with<Ammo> :std::true_type {};
		template<> struct with<Boss> :std::true_type {};
		template<> struct with<Enemy> :std::true_type {};
	};

	template<typename T, typename U>
	constexpr auto is_collidable_with = is_collidable<T>::template with<U>::value;


}