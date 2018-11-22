template <typename... Args>
std::vector<std::string> toStringVector(Args... args) {
	std::vector<std::string> result;
	auto initList = {args...};
	using T = typename decltype(initList)::value_type;
	std::vector<T> expanded{initList};
	result.resize(expanded.size());
	std::transform(expanded.begin(), expanded.end(), result.begin(), [](T value) { return std::to_string(value); });
	return result;
}
