#ifndef ATA_SIGNAL_H
#define ATA_SIGNAL_H
#include "ATA/config.h"
#include <string>
#include <type_traits>
#include <unordered_map>
#include <functional>
#include <memory>
#include <vector>

namespace ata
{
	template<typename T>
	class Signal
	{
		public:
		
			Signal(size_t parameters = 0);
			
			Signal(const Signal& other);
			
			Signal(Signal&& other) noexcept = default;
			
			Signal& operator=(const Signal& other);
			
			Signal& operator=(Signal&& other) noexcept = default;
			
			virtual ~Signal() = default;
			
			template<typename Fn, typename ... BoundArgs>
			unsigned int operator()(const Fn& fn, BoundArgs&& ... args)
			{
				return connect(fn, std::forward<BoundArgs>(args)...);
			}
			
			template<typename Fn, typename ... BoundArgs, typename std::enable_if<
				std::is_convertible<Fn, std::function<void(const T*, BoundArgs&&...)>>::value>::type* = nullptr>
			unsigned int connect(const Fn& fn, BoundArgs&& ... args)
			{
				const auto id = ++lastSignalID;
				m_handlers[id] = [=]{invokeFn(fn, dereferenceParam<const T*>(0), std::forward<BoundArgs>(args)...);};
				return id;
			}
			
			bool disconnect(unsigned int id);
			
			void disconnectAll();
			
			void setEnable(bool enable)
			{
				m_enabled = enable;
			}
			
			bool isEnabled() const
			{
				return m_enabled;
			}
			
			bool emit(const T* object);
			
		private:
		
			static std::shared_ptr<T> getObject();
			
			template<typename Type>
			static const typename std::decay<Type>::type& dereferenceParam(size_t paramIndex)
			{
				return *static_cast<const typename std::decay<Type>::type*>(params[paramIndex]);
			}
			
			template<typename Fn, typename ... Args, typename std::enable_if<
				std::is_member_pointer<typename std::decay<Fn>::type>::value
			>::type* = nullptr>
			static void invokeFn(Fn&& fn, Args&& ... args)
			{
				(std::mem_fn(fn))(std::forward<Args>(args)...);
			}
			
			template<typename Fn, typename ... Args, typename std::enable_if<
				!std::is_member_pointer<typename std::decay<Fn>::type>::value
			>::type* = nullptr>
			static void invokeFn(Fn&& fn, Args&& ... args)
			{
				std::forward<Fn>(fn)(std::forward<Args>(args)...);
			}
			
		private:
		
			bool m_enabled = true;
			std::unordered_map<unsigned int, std::function<void()>> m_handlers;
			static unsigned int lastSignalID;
			static std::vector<const void*> params;
			
	};
	
#include "ATA/core/signal.inl"

}

#endif