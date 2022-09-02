#pragma once
// #include <iostream>
#include "../vector/vector.hpp"

namespace ft {
    template <class T, class Container = vector<T> >
    class stack
    {

        public:

        typedef Container 	container_type;
        typedef T			value_type;
        typedef size_t		size_type;

        protected:
            container_type c;

		public:

        explicit stack (const container_type& ctnr = container_type()){
            c = ctnr;
        }

		bool empty() const{
			return c.empty();
		}

		size_type size() const{
			return c.size();
		}

		value_type& top(){
			return c.back();
		}

		const value_type& top() const{
			return c.back();
		}

		void push (const value_type& val){
			c.push_back(val);
		}

		void pop(){
			c.pop_back();
		}


		template <class Tf, class Containerf>
		friend	bool operator== (const stack<Tf, Containerf>& lhs, const stack<Tf, Containerf>& rhs);
		template <class Tf, class Containerf>
  		friend	bool operator!= (const stack<Tf, Containerf>& lhs, const stack<Tf, Containerf>& rhs);
		template <class Tf, class Containerf>
		friend	bool operator<  (const stack<Tf, Containerf>& lhs, const stack<Tf, Containerf>& rhs);
		template <class Tf, class Containerf>
		friend	bool operator<= (const stack<Tf, Containerf>& lhs, const stack<Tf, Containerf>& rhs);
		template <class Tf, class Containerf>
		friend	bool operator>  (const stack<Tf, Containerf>& lhs, const stack<Tf, Containerf>& rhs);
		template <class Tf, class Containerf>
		friend	bool operator>= (const stack<Tf, Containerf>& lhs, const stack<Tf, Containerf>& rhs);


    }; //end of class stack


	//relational operators
	template <class T, class Container>
  	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
  		return lhs.c == rhs.c;
  	}

	template <class T, class Container>
  	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
  		return !(lhs == rhs);
  	}

	template <class T, class Container>
  	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
  		return lhs.c < rhs.c;
  	}
	
	template <class T, class Container>
  	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
  		return lhs.c <= rhs.c;
  	}
	
	template <class T, class Container>
  	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
  		return lhs.c > rhs.c;
  	}

	template <class T, class Container>
  	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
  		return lhs.c >= rhs.c;
  	}
};