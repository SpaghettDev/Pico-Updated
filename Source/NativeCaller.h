#pragma once

template <typename T>
static inline void nativePush(T val)
{
	UINT64 val64 = 0;
	if (sizeof(T) > sizeof(UINT64))
		throw "error, value size > 64 bit";

	*reinterpret_cast<T*>(&val64) = val; // &val + sizeof(dw) - sizeof(val)
	nativePush64(val64);
}

template <typename R>
static inline R invoke(UINT64 hash)
{
	nativeInit(hash);
	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1>
static inline R invoke(UINT64 hash, T1 P1)
{
	nativeInit(hash);

	nativePush(P1);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2>
static inline R invoke(UINT64 hash, T1 P1, T2 P2)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);
	nativePush(P19);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);
	nativePush(P19);
	nativePush(P20);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);
	nativePush(P19);
	nativePush(P20);
	nativePush(P21);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);
	nativePush(P19);
	nativePush(P20);
	nativePush(P21);
	nativePush(P22);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);
	nativePush(P19);
	nativePush(P20);
	nativePush(P21);
	nativePush(P22);
	nativePush(P23);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23, T24 P24)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);
	nativePush(P19);
	nativePush(P20);
	nativePush(P21);
	nativePush(P22);
	nativePush(P23);
	nativePush(P24);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23, T24 P24, T25 P25)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);
	nativePush(P19);
	nativePush(P20);
	nativePush(P21);
	nativePush(P22);
	nativePush(P23);
	nativePush(P24);
	nativePush(P25);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23, T24 P24, T25 P25, T26 P26)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);
	nativePush(P19);
	nativePush(P20);
	nativePush(P21);
	nativePush(P22);
	nativePush(P23);
	nativePush(P24);
	nativePush(P25);
	nativePush(P26);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23, T24 P24, T25 P25, T26 P26, T27 P27)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);
	nativePush(P19);
	nativePush(P20);
	nativePush(P21);
	nativePush(P22);
	nativePush(P23);
	nativePush(P24);
	nativePush(P25);
	nativePush(P26);
	nativePush(P27);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23, T24 P24, T25 P25, T26 P26, T27 P27, T28 P28)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);
	nativePush(P19);
	nativePush(P20);
	nativePush(P21);
	nativePush(P22);
	nativePush(P23);
	nativePush(P24);
	nativePush(P25);
	nativePush(P26);
	nativePush(P27);
	nativePush(P28);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23, T24 P24, T25 P25, T26 P26, T27 P27, T28 P28, T29 P29)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);
	nativePush(P19);
	nativePush(P20);
	nativePush(P21);
	nativePush(P22);
	nativePush(P23);
	nativePush(P24);
	nativePush(P25);
	nativePush(P26);
	nativePush(P27);
	nativePush(P28);
	nativePush(P29);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23, T24 P24, T25 P25, T26 P26, T27 P27, T28 P28, T29 P29, T30 P30)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);
	nativePush(P19);
	nativePush(P20);
	nativePush(P21);
	nativePush(P22);
	nativePush(P23);
	nativePush(P24);
	nativePush(P25);
	nativePush(P26);
	nativePush(P27);
	nativePush(P28);
	nativePush(P29);
	nativePush(P30);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23, T24 P24, T25 P25, T26 P26, T27 P27, T28 P28, T29 P29, T30 P30, T31 P31)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);
	nativePush(P19);
	nativePush(P20);
	nativePush(P21);
	nativePush(P22);
	nativePush(P23);
	nativePush(P24);
	nativePush(P25);
	nativePush(P26);
	nativePush(P27);
	nativePush(P28);
	nativePush(P29);
	nativePush(P30);
	nativePush(P31);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23, T24 P24, T25 P25, T26 P26, T27 P27, T28 P28, T29 P29, T30 P30, T31 P31, T32 P32)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);
	nativePush(P19);
	nativePush(P20);
	nativePush(P21);
	nativePush(P22);
	nativePush(P23);
	nativePush(P24);
	nativePush(P25);
	nativePush(P26);
	nativePush(P27);
	nativePush(P28);
	nativePush(P29);
	nativePush(P30);
	nativePush(P31);
	nativePush(P32);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31, typename T32, typename T33>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23, T24 P24, T25 P25, T26 P26, T27 P27, T28 P28, T29 P29, T30 P30, T31 P31, T32 P32, T33 P33)
{
	nativeInit(hash);

	nativePush(P1);
	nativePush(P2);
	nativePush(P3);
	nativePush(P4);
	nativePush(P5);
	nativePush(P6);
	nativePush(P7);
	nativePush(P8);
	nativePush(P9);
	nativePush(P10);
	nativePush(P11);
	nativePush(P12);
	nativePush(P13);
	nativePush(P14);
	nativePush(P15);
	nativePush(P16);
	nativePush(P17);
	nativePush(P18);
	nativePush(P19);
	nativePush(P20);
	nativePush(P21);
	nativePush(P22);
	nativePush(P23);
	nativePush(P24);
	nativePush(P25);
	nativePush(P26);
	nativePush(P27);
	nativePush(P28);
	nativePush(P29);
	nativePush(P30);
	nativePush(P31);
	nativePush(P32);
	nativePush(P33);

	if constexpr (!std::is_same_v<R, void>)
		return *reinterpret_cast<R*>(nativeCall());
}
