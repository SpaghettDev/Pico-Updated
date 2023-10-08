#pragma once

class script_global
{
public:
	constexpr explicit script_global(std::size_t index)
		: m_index(index)
	{}

	constexpr script_global add(std::ptrdiff_t index)
	{
		return script_global(m_index + index);
	}

	constexpr script_global at(std::ptrdiff_t index, std::size_t size)
	{
		return add(1 + (index * size));
	}

	template <typename T>
	std::enable_if_t<std::is_pointer<T>::value, T> as() const
	{
		return reinterpret_cast<T>(index_to_ptr(m_index));
	}

	template <typename T>
	std::enable_if_t<std::is_lvalue_reference<T>::value, T> as() const
	{
		return *reinterpret_cast<std::add_pointer_t<std::remove_reference_t<T>>>(index_to_ptr(m_index));
	}

	template <typename T>
	std::enable_if_t<std::is_same<T, std::uintptr_t>::value, T> as() const
	{
		return reinterpret_cast<std::uintptr_t>(as<void*>());
	}

	static void* index_to_ptr(std::size_t index)
	{
		return g_hooking.m_GlobalBase[index >> 0x12 & 0x3F] + (index & 0x3FFFF);
	}

private:
	std::uintptr_t m_index;
};
