template<typename T>
unsigned int Signal<T>::lastSignalID = 0;

template<typename T>
std::vector<const void*> Signal<T>::params(1);

template<typename T>
Signal<T>::Signal(size_t parameters) :
	m_enabled{true},
	m_handlers{}
{
	size_t paramCount = params.size() + parameters;
	if(paramCount > params.size())
	{
		params.reserve(paramCount);
	}
}

template<typename T>
Signal<T>::Signal(const Signal& other) :
	m_enabled{other.m_enabled},
	m_handlers{}
{
}

template<typename T>
Signal<T>& Signal<T>::operator=(const Signal& other)
{
	if(this != &other)
	{
		m_enabled = other.m_enabled;
		m_handlers.clear();
	}
	return *this;
}

template<typename T>
bool Signal<T>::disconnect(unsigned int id)
{
	return (m_handlers.erase(id) != 0);
}

template<typename T>
void Signal<T>::disconnectAll()
{
	m_handlers.clear();
}

template<typename T>
bool Signal<T>::emit(const T* object)
{
	if(m_handlers.empty() || !m_enabled)
		return false;
		
	params[0] = static_cast<const void*>(&object);
	
	auto handlers = m_handlers;
	for(const auto& handler : handlers)
		handler.second();
		
	return true;
}