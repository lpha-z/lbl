// ------------------------------------------
// Copyright (c) 2018 lpha-z
// https://github.com/lpha-z/lbl
// Distributed under the MIT software license
// ------------------------------------------
#ifndef LBL_XINTNT_HPP
#define LBL_XINTNT_HPP
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <type_traits>

namespace lbl {

namespace /* (anonymous) */ { 

// or longer types
using int_t = int_least64_t;
using uint_t = uint_least64_t;
static constexpr std::size_t uint_t_bits = std::numeric_limits<uint_t>::digits;

// DO NOT use 'std::abs', which may cause undefined behavior (signed overflow)
constexpr uint_t safe_abs( int_t x ) {
	return x < 0 ? -static_cast<uint_t>(x) : static_cast<uint_t>(x);
}

// DO NOT use 'static_cast<int_t>' for 'bit_cast<int_t>'
// (Implementation-defined: 6.3.1.3.3 Signed and unsigned integers)
template<class S>
constexpr S bit_cast( std::make_unsigned_t<S> x ) {
	using U = std::make_unsigned_t<S>;
	constexpr S min = std::numeric_limits<S>::min();
	constexpr U bias = static_cast<U>(min); // 0x8000...
	return x < bias ? static_cast<S>(x) : static_cast<S>(x-bias) + min;
}

template<std::size_t N, bool IsSigned>
class xintN_t;

template<std::size_t N, bool IsSigned>
std::ostream& operator<<( std::ostream&, const xintN_t<N, IsSigned>& );

template<std::size_t N, bool IsSigned> constexpr bool operator< ( const xintN_t<N, IsSigned>&, const xintN_t<N, IsSigned>& ) noexcept;
template<std::size_t N, bool IsSigned> constexpr bool operator<=( const xintN_t<N, IsSigned>&, const xintN_t<N, IsSigned>& ) noexcept;
template<std::size_t N, bool IsSigned> constexpr bool operator> ( const xintN_t<N, IsSigned>&, const xintN_t<N, IsSigned>& ) noexcept;
template<std::size_t N, bool IsSigned> constexpr bool operator>=( const xintN_t<N, IsSigned>&, const xintN_t<N, IsSigned>& ) noexcept;
template<std::size_t N, bool IsSigned> constexpr bool operator==( const xintN_t<N, IsSigned>&, const xintN_t<N, IsSigned>& ) noexcept;
template<std::size_t N, bool IsSigned> constexpr bool operator!=( const xintN_t<N, IsSigned>&, const xintN_t<N, IsSigned>& ) noexcept;

template<std::size_t N, bool IsSigned> constexpr xintN_t<N, IsSigned> operator|( const xintN_t<N, IsSigned>&, const xintN_t<N, IsSigned>& ) noexcept;
template<std::size_t N, bool IsSigned> constexpr xintN_t<N, IsSigned> operator^( const xintN_t<N, IsSigned>&, const xintN_t<N, IsSigned>& ) noexcept;
template<std::size_t N, bool IsSigned> constexpr xintN_t<N, IsSigned> operator&( const xintN_t<N, IsSigned>&, const xintN_t<N, IsSigned>& ) noexcept;
template<std::size_t N, bool IsSigned> constexpr xintN_t<N, IsSigned> operator+( const xintN_t<N, IsSigned>&, const xintN_t<N, IsSigned>& ) noexcept;
template<std::size_t N, bool IsSigned> constexpr xintN_t<N, IsSigned> operator-( const xintN_t<N, IsSigned>&, const xintN_t<N, IsSigned>& ) noexcept;
template<std::size_t N, bool IsSigned> constexpr xintN_t<N, IsSigned> operator*( const xintN_t<N, IsSigned>&, const xintN_t<N, IsSigned>& ) noexcept;
template<std::size_t N, bool IsSigned> constexpr xintN_t<N, IsSigned> operator/( const xintN_t<N, IsSigned>&, const xintN_t<N, IsSigned>& ) noexcept;
template<std::size_t N, bool IsSigned> constexpr xintN_t<N, IsSigned> operator%( const xintN_t<N, IsSigned>&, const xintN_t<N, IsSigned>& ) noexcept;

template<std::size_t N, bool IsSigned>
class xintN_t {
	uint_t val;
	static constexpr std::size_t Offset = uint_t_bits - N;
	static_assert( Offset < uint_t_bits && N <= uint_t_bits, "cannot simulate" );

	friend std::ostream& operator<< <N>( std::ostream&, const xintN_t& );

	friend constexpr bool operator< <N>( const xintN_t&, const xintN_t& ) noexcept;
	friend constexpr bool operator<=<N>( const xintN_t&, const xintN_t& ) noexcept;
	friend constexpr bool operator> <N>( const xintN_t&, const xintN_t& ) noexcept;
	friend constexpr bool operator>=<N>( const xintN_t&, const xintN_t& ) noexcept;
	friend constexpr bool operator==<N>( const xintN_t&, const xintN_t& ) noexcept;
	friend constexpr bool operator!=<N>( const xintN_t&, const xintN_t& ) noexcept;

	friend constexpr xintN_t operator|<N>( const xintN_t&, const xintN_t& ) noexcept;
	friend constexpr xintN_t operator^<N>( const xintN_t&, const xintN_t& ) noexcept;
	friend constexpr xintN_t operator&<N>( const xintN_t&, const xintN_t& ) noexcept;
	friend constexpr xintN_t operator+<N>( const xintN_t&, const xintN_t& ) noexcept;
	friend constexpr xintN_t operator-<N>( const xintN_t&, const xintN_t& ) noexcept;
	friend constexpr xintN_t operator*<N>( const xintN_t&, const xintN_t& ) noexcept;
	friend constexpr xintN_t operator/<N>( const xintN_t&, const xintN_t& ) noexcept;
	friend constexpr xintN_t operator%<N>( const xintN_t&, const xintN_t& ) noexcept;
public:
	/* implicit */ constexpr xintN_t( uint_t x ) noexcept : val( x << Offset ) {}
	template<class T, std::enable_if_t<std::is_integral_v<T> && sizeof(T) <= sizeof(uint_t), std::nullptr_t> = nullptr>
	/* implicit */ constexpr xintN_t( T      x ) noexcept : xintN_t( static_cast<uint_t>(x) ) {}
	template<std::size_t M, bool IsSigned_M, std::enable_if_t<!((IsSigned && !IsSigned_M) || M < N), std::nullptr_t> = nullptr>
	/* implicit */ constexpr xintN_t( const xintN_t<M, IsSigned_M>& x ) noexcept : xintN_t( static_cast<uint_t>(x) ) {}
	template<std::size_t M, bool IsSigned_M, std::enable_if_t<((IsSigned && !IsSigned_M) || M < N), std::nullptr_t> = nullptr>
	explicit constexpr xintN_t( const xintN_t<M, IsSigned_M>& x ) noexcept : xintN_t( static_cast<uint_t>(x) ) {}
	constexpr xintN_t( const xintN_t&  ) noexcept = default;
	constexpr xintN_t(       xintN_t&& ) noexcept = default;
	constexpr xintN_t& operator=( const xintN_t&  ) & noexcept = default;
	constexpr xintN_t& operator=(       xintN_t&& ) & noexcept = default;

	/* implicit */ constexpr operator int_t()  const noexcept { return bit_cast<int_t>(val) < 0 ? bit_cast<int_t>( ~(~val >> Offset) ) : bit_cast<int_t>(val >> Offset); }

	constexpr xintN_t& operator|=( const xintN_t& rhs ) & noexcept { val |= rhs.val; return *this; }
	constexpr xintN_t& operator^=( const xintN_t& rhs ) & noexcept { val ^= rhs.val; return *this; }
	constexpr xintN_t& operator&=( const xintN_t& rhs ) & noexcept { val &= rhs.val; return *this; }
	constexpr xintN_t& operator+=( const xintN_t& rhs ) & noexcept { val += rhs.val; return *this; }
	constexpr xintN_t& operator-=( const xintN_t& rhs ) & noexcept { val -= rhs.val; return *this; }
	constexpr xintN_t& operator*=( const xintN_t& rhs ) & noexcept { val = ((val>>Offset) * (rhs.val>>Offset)) << Offset; return *this; }
	constexpr xintN_t& operator/=( const xintN_t& rhs ) & noexcept {
		if( IsSigned ) {
			bool result_sign = (bit_cast<int_t>(val) < 0) ^ (bit_cast<int_t>(rhs.val) < 0);
			uint_t abs_result = (safe_abs(bit_cast<int_t>(val))>>Offset) / (safe_abs(bit_cast<int_t>(rhs.val))>>Offset) << Offset;
			val = result_sign ? -abs_result : abs_result;
		} else {
			val = (val>>Offset) / (rhs.val>>Offset) << Offset;
		}
		return *this;
	}
	constexpr xintN_t& operator%=( const xintN_t& rhs ) & noexcept {
		if( IsSigned ) {
			bool result_sign = bit_cast<int_t>(val) < 0;
			uint_t abs_result = (safe_abs(bit_cast<int_t>(val))>>Offset) % (safe_abs(bit_cast<int_t>(rhs.val))>>Offset) << Offset;
			val = result_sign ? -abs_result : abs_result;
		} else {
			val = (val>>Offset) % (rhs.val>>Offset) << Offset;
		}
		return *this;
	}

	template<class T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
	constexpr xintN_t& operator<<=( T shamt ) & noexcept { val <<= shamt; return *this; }
	template<class T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
	constexpr xintN_t& operator>>=( T shamt ) & noexcept {
		if( IsSigned && bit_cast<int_t>(val) < 0 ) {
			val = ~(~val >> shamt);
		} else {
			val >>= shamt;
		}
		val >>= Offset; val <<= Offset; return *this;
	}

	constexpr bool operator!() const noexcept { return !static_cast<bool>(*this); }

	constexpr xintN_t& operator++()    noexcept { val += static_cast<uint_t>(1)<<Offset; return *this; }
	constexpr xintN_t& operator--()    noexcept { val -= static_cast<uint_t>(1)<<Offset; return *this; }
	constexpr xintN_t  operator++(int) noexcept { xintN_t ret = *this; val += static_cast<uint_t>(1)<<Offset; return ret; }
	constexpr xintN_t  operator--(int) noexcept { xintN_t ret = *this; val -= static_cast<uint_t>(1)<<Offset; return ret; }

	constexpr xintN_t operator+() const noexcept { return xintN_t { +(val>>Offset) }; }
	constexpr xintN_t operator-() const noexcept { return xintN_t { -(val>>Offset) }; }
	constexpr xintN_t operator~() const noexcept { return xintN_t { ~(val>>Offset) }; }

	template<class T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
	constexpr xintN_t operator<<( T shamt ) const noexcept { xintN_t ret = *this; return ret <<= shamt; }
	template<class T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
	constexpr xintN_t operator>>( T shamt ) const noexcept { xintN_t ret = *this; return ret >>= shamt; }
};

template<std::size_t N, bool IsSigned>
std::ostream& operator<<( std::ostream& ostr, const xintN_t<N, IsSigned>& rhs ) {
	return ostr << static_cast<uint_t>(rhs);
}

#define LBL_XINTNT_RELATIONAL_OPERATOR_DEF( op ) \
	template<std::size_t N, bool IsSigned> \
	constexpr bool operator op ( const xintN_t<N, IsSigned>& lhs, const xintN_t<N, IsSigned>& rhs ) noexcept { return IsSigned ? bit_cast<int_t>(lhs.val) op bit_cast<int_t>(rhs.val) : lhs.val op rhs.val; } \
	template<std::size_t N, bool IsSigned, class T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr> \
	constexpr bool operator op ( const xintN_t<N, IsSigned>& lhs, const T& rhs ) noexcept { return lhs op xintN_t<N, IsSigned>( rhs ); } \
	template<std::size_t N, bool IsSigned, class T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr> \
	constexpr bool operator op ( const T& lhs, const xintN_t<N, IsSigned>& rhs ) noexcept { return xintN_t<N, IsSigned>( lhs ) op rhs; }

LBL_XINTNT_RELATIONAL_OPERATOR_DEF( <  )
LBL_XINTNT_RELATIONAL_OPERATOR_DEF( <= )
LBL_XINTNT_RELATIONAL_OPERATOR_DEF( >  )
LBL_XINTNT_RELATIONAL_OPERATOR_DEF( >= )
LBL_XINTNT_RELATIONAL_OPERATOR_DEF( == )
LBL_XINTNT_RELATIONAL_OPERATOR_DEF( != )

#define LBL_XINTNT_BINARY_OPERATOR_DEF( op ) \
	template<std::size_t N, bool IsSigned, class T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr> \
	constexpr xintN_t<N, IsSigned>& operator op##=( xintN_t<N, IsSigned>& lhs, const T& rhs ) noexcept { return lhs op##= xintN_t<N, IsSigned>( rhs ); } \
	template<std::size_t N, bool IsSigned> \
	constexpr xintN_t<N, IsSigned> operator op ( const xintN_t<N, IsSigned>& lhs, const xintN_t<N, IsSigned>& rhs ) noexcept { xintN_t ret = lhs; return ret op##= rhs; } \
	template<std::size_t N, bool IsSigned, class T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr> \
	constexpr xintN_t<N, IsSigned> operator op ( const xintN_t<N, IsSigned>& lhs, const T& rhs ) noexcept { return lhs op xintN_t<N, IsSigned>( rhs ); } \
	template<std::size_t N, bool IsSigned, class T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr> \
	constexpr xintN_t<N, IsSigned> operator op ( const T& lhs, const xintN_t<N, IsSigned>& rhs ) noexcept { return xintN_t<N, IsSigned>( lhs ) op rhs; }

LBL_XINTNT_BINARY_OPERATOR_DEF( | )
LBL_XINTNT_BINARY_OPERATOR_DEF( ^ )
LBL_XINTNT_BINARY_OPERATOR_DEF( & )
LBL_XINTNT_BINARY_OPERATOR_DEF( + )
LBL_XINTNT_BINARY_OPERATOR_DEF( - )
LBL_XINTNT_BINARY_OPERATOR_DEF( * )
LBL_XINTNT_BINARY_OPERATOR_DEF( / )
LBL_XINTNT_BINARY_OPERATOR_DEF( % )

} // namespace (anonymous)

template<std::size_t N>
using uintN_t = xintN_t<N, false>;
template<std::size_t N>
using  intN_t = xintN_t<N, true>;

} // namespace lbl

#endif // LBL_XINTNT_HPP
