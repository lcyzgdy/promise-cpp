#pragma once
#ifndef __PROMISE_HPP__
#define __PROMISE_HPP__

#include <functional>
#include <iostream>

#include "PromiseLoop.h"

namespace Promise
{
	enum class PromiseStatus
	{
		ePending,
		eFulfilled,
		eRejected,

		ePromiseStatusCount
	};

	class PromiseLoop;

	template<typename _Ty>
	class Promise
	{
		friend class PromiseLoop;

		using _ResolveFuncType = std::function<void(_Ty)>;

		PromiseStatus m_status;

		inline void DefaultResolve(_Ty&& value) { this->m_status = PromiseStatus::eFulfilled; }
		inline void DefaultReject(std::exception&& e) { this->m_status = PromiseStatus::eRejected; }

	public:
		Promise(std::function<void(_ResolveFuncType&&)>&& func) :m_status(PromiseStatus::ePending)
		{
			func(std::bind(&DefaultResolve, this, std::placeholders::_1));
		}

		template<typename _ThenRet>
		Promise<_ThenRet>& Then(std::function<_ThenRet(_Ty)>&& func)
		{
		}
	};

	template<>
	class Promise<void>
	{
		using _ResolveFuncType = std::function<void()>;

		PromiseStatus m_status;
		std::vector<Promise<void>> m_resolveChain;
		std::vector<Promise<void>> m_rejectChain;
		std::function<void(_ResolveFuncType&&)> m_func;
		bool m_voidFlag;
		bool m_resolveFlag;
		bool m_rejectFlag;

		inline void _DefaultResolveVoid() { this->m_status = PromiseStatus::eFulfilled; std::cout << "OnResolve" << std::endl; }
		inline void _DefaultRejectVoid() { this->m_status = PromiseStatus::eRejected; }

		inline void _InternalInvoke()
		{
			m_func(std::bind(&Promise::_DefaultResolveVoid, this));
		}

	public:
		explicit Promise(std::function<void(_ResolveFuncType&&)>&& func) :m_status(PromiseStatus::ePending),
			m_func(func), m_resolveFlag(true)
		{

		}

		template<typename _ThenRet>
		Promise<_ThenRet>& Then(std::function<_ThenRet()>&& func)
		{
		}
	};
}
#endif // !__PROMISE_HPP__