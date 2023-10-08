#include "stdafx.hpp"

extern "C" void	_call_asm(void* context, void* function, void* ret);
static NativeManagerContext g_context;

static UINT64 g_hash;

void(*scrNativeCallContext::SetVectorResults)(scrNativeCallContext*) = nullptr;

void nativeInit(UINT64 hash)
{
	g_context.Reset();
	g_hash = hash;
}

void nativePush64(UINT64 value)
{
	g_context.Push(value);
}

uint64_t* nativeCall()
{
	auto fn = Hooking::get_native_handler(g_hash);

	auto log_ex = [](UINT64 hash, void* exaddr) -> void {
		LOG(ERROR) << "executing native " << std::format("{:#06x}", g_hash) << " at address " << exaddr;
	};

	if (fn != 0)
	{
		static void* exceptionAddress;

		__try
		{
			_call_asm(&g_context, fn, g_hooking.m_NativeSpoofer);
			scrNativeCallContext::SetVectorResults(&g_context);
		}
		__except (exceptionAddress = (GetExceptionInformation())->ExceptionRecord->ExceptionAddress, EXCEPTION_EXECUTE_HANDLER)
		{
			log_ex(g_hash, exceptionAddress);
		}
	}

	return reinterpret_cast<uint64_t*>(g_context.GetResultPointer());
}
