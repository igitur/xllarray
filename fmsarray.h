// fmsarray.h - array functions
#pragma once
#include <exception>
#include <iterator>

#ifndef ensure
#define ensure(e) if (!e) { throw std::runtime_error{}; }
#endif // ensure

namespace fms {

	namespace sequence {
		// iterator with end
		template<class I, class E>
		class iterator : public I {
			E e;
		public:
			iterator(I i, E e)
				: I(i), e(e)
			{ }
			bool operator==(const iterator& i) const
			{
				return I::operator==(i) && e == i.end();
			}
			bool operator!=(const iterator& i) const
			{
				return !operator==(i);
			}
			// handy but a good idea?
			bool operator==(const I& i) const
			{
				return I::operator==(i);
			}
			bool operator!=(const I& i) const
			{
				return !operator==(i);
			}
			operator bool() const
			{
				return I::operator!=(e);
			}
			E end() const
			{
				return e;
			}
		};
		template<class I, class E>
		inline E end(const iterator<I,E>& i)
		{
			return i.end();
		}
		template<class I, class E>
		inline auto make_iterator(I i, E e)
		{
			return iterator<I,E>(i, e);
		}
		// poor man's range
		template<class C>
		inline auto make_iterator(const C& c)
		{
			return make_iterator(c.begin(), c.end());
		}
#ifdef _DEBUG
#include <vector>
		inline void iterator_test()
		{
			std::vector<int> v{1,2,3};
			{
				auto i = make_iterator(v.begin(), v.end());
				auto i2(i);
				i = i2;
				ensure (i == i2);
				ensure (*i == 1);
				ensure (*++i == 2);
				ensure (*i++ == 2);
				ensure (*i == 3);
				ensure (i);
				++i;
				ensure (!i);
				std::advance(i, -1);
				ensure (i);
				ensure (*i == 3);
			}
			{
				auto i = make_iterator(v);
				auto i2(i);
				i = i2;
				ensure (i == i2);
				ensure (*i == 1);
				ensure (*++i == 2);
				ensure (*i++ == 2);
				ensure (*i == 3);
				ensure (i);
				++i;
				ensure (!i);
				std::advance(i, -1);
				ensure (i);
				ensure (*i == 3);
			}
			{
				auto i = make_iterator(v.begin(), v.end());
				ensure (i == i);
				ensure (!(i != i));
				auto i_ = make_iterator(v.begin(), --v.end());
				ensure (i != i_);
				ensure (!( i == i_));
				ensure (i.end() == end(i));
				ensure (end(i) != i_.end());
			}
			{
				auto i = make_iterator(v);
				i += v.size();
				ensure (i == i.end());
			}
		}
#endif // _DEBUG

	template<class S>
	inline S end(S s)
	{
		ensure (*s);

		// if global end(S) or S.end() exists, call that
		while (*++s)
			;

		return s;
	}

	template<class S, class N = std::iterator_traits<S>::difference_type>
	inline S skip(N n, S s)
	{
		std::advance(s, n);

		return s;
	}

	template<class S, class N = std::iterator_traits<S>::difference_type>
	inline N size(S s)
	{
		// if global size(S) or S.size() exists, call that
		return std::distance(s, end(s));
	}
	
	// ++last == end
	template<class S>
	inline S last(S s)
	{
		ensure (*s)
		S s_(s);

		while (*++s) {
			++s_;
		}

		return s_;
	}

	template<class S, class N = std::iterator_traits<S>::difference_type, class T = std::iterator_traits<S>::value_type>
	class take {
		N n;
		S s;
	public:
		take(long n, S s)
			: n(n), s(s)
		{
			if (n < 0) {
				n = -n;
				s = skip(n, std::reverse(s));
			}
		}
		operator bool() const
		{
			return n != 0;
		}
		const T& operator*() const
		{
			return *s;
		}
		take& operator++()
		{
			if (n) {
				--n;
				++s;
			}

			return *this;
		}
	};

	template<class S, class T = std::iterator_traits<S>::value_type>
	class drop {
		long n;
		S s;
	public:
		drop(long n, S s)
			: n(n), s(s)
		{
			if (n > 0) {
				std::advance(s, n);
			}
			else if (n < 0) {
				n = size(s) + n;
			}
		}
		operator bool() const
		{
			return n != 0;
		}
		T operator*() const
		{
			return *s;
		}
		take& operator++()
		{
			if (n) {
				--n;
				++s;
			}

			return *this;
		}
	};

	}
} // namespace fms
