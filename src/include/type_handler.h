#pragma once

namespace kg
{
	/* Associative container check */
	template <typename T, typename = void>
	struct is_associative_container : std::false_type {};

	template <typename T>
	struct is_associative_container<T, std::void_t<typename T::key_type>> : std::true_type {};
	/* ----- */

	/* Map check by Container */
	template <typename T, typename = void>
	struct is_map : std::false_type {};

	template <typename T>
	struct is_map<T, std::void_t<typename T::key_type, typename T::mapped_type>> : std::true_type {};
	/* ----- */

	/* Map check by Iterator */
	template <typename>
	struct is_pair : std::false_type {};

	template <typename T, typename U>
	struct is_pair<std::pair<T, U>> : std::true_type {};
	/* ----- */
}
