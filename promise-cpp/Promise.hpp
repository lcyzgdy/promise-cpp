#pragma once
#ifndef __PROMISE_HPP__
#define __PROMISE_HPP__

#include <functional>

namespace Promise
{
	enum class PromiseStatus
	{
		ePending,
		eFulfilled,
		eRejected,

		ePromiseStatusCount
	};

	template<typename _Ty>
	class Promise
	{
		using _ResolveFuncType = std::function<void(_Ty)>;

		PromiseStatus m_status;

		inline void DefaultResolve(_Ty&& value) { this->m_status = PromiseStatus::eFulfilled; }
		inline void DefaultReject(std::exception&& e) { this->m_status = PromiseStatus::eRejected; }

	public:
		Promise(std::function<void(_ResolveFuncType&&)>&& func)
		{
			func(std::bind(&DefaultResolve, this, std::placeholders::_1));
		}
		/*
		template<typename _ThenRet>
		Promise<_ThenRet>& Then(std::function<_ThenRet(_Ty)>&& func)
		{
		}
		*/
	};
}
#endif