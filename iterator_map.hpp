#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP

namespace ft
{
    template <class iter, class T>
	class iterator_map
	{
		public:

			typedef iter         						value_type;
			typedef std::ptrdiff_t  					difference_type;
			typedef T*   								pointer;
			typedef T& 									reference;
			typedef std::bidirectional_iterator_tag		iterator_category;
		
		protected:

			value_type *_ptr;
		public:
		
            // ----------------CONSTRUCTEURS----------------------------

			iterator_map(): _ptr(nullptr){};

			iterator_map(const iterator_map &x)
			{
				*this = x;
			};

			iterator_map(value_type *x): _ptr(x){};

			~iterator_map(){};

			value_type *get_internal_pointer(void) const
			{
				return _ptr;
			};

			iterator_map &operator=(const iterator_map &x)
			{
				if (this != &x)
					_ptr = x._ptr;
				return (*this);
			};
           
            //-------------FONCTION INCREMENT DECREMENT-----------

            iterator_map &operator++()
			{
				_ptr = _ptr->next_node();
				return (*this);
			};

			iterator_map operator++(int)
			{
				iterator_map tmp(*this);
				_ptr = _ptr->next_node();
				return (tmp);
			};

			iterator_map &operator--()
			{
				_ptr = _ptr->previous_node();
				return *this;
			};

			iterator_map operator--(int)
			{
				iterator_map tmp(*this);
				_ptr = _ptr->previous_node();
				return tmp;
			};
         //-------------REFERENCE & POINTEUR -----------

			reference operator*() const
			{
				return (_ptr->value);
			};

			pointer operator->() const
			{
				return (&_ptr->value);
			};

            //-------------BOOLEANS -----------

			bool operator==(const iterator_map &x)
			{
				return (_ptr == x._ptr);
			};
	
			bool operator!=(const iterator_map &x)
			{
				return (_ptr != x._ptr);
			};
			
		};

	template <class iter, class T, class iterator_map>
	class const_iterator_map
	{
		public:
			typedef iter								value_type;
			typedef std::ptrdiff_t						difference_type;
			typedef T*									pointer;
			typedef T& 									reference;
			typedef std::bidirectional_iterator_tag		iterator_category;
			
		protected:
			value_type		*_ptr;


		public:

			// ----------------CONSTRUCTEURS----------------------------

			const_iterator_map(): _ptr(nullptr){};

			const_iterator_map(const const_iterator_map &x)
			{
				*this = x;
			};

			const_iterator_map(pointer x): _ptr(x)
			{

			};

			const_iterator_map(const iterator_map &other)
			{
				_ptr = other.get_internal_pointer();
			};

			~const_iterator_map(){};

			value_type *get_internal_pointer(void) const
			{
				return _ptr;
			};

			const_iterator_map &operator=(const const_iterator_map &x)
			{
				if (this != &x)
					_ptr = x._ptr;
				return (*this);
			};

			//-------------FONCTION INCREMENT DECREMENT-----------

			const_iterator_map &operator++()
			{
				_ptr = _ptr->next_node();
				return (*this);
			};

			const_iterator_map operator++(int)
			{
				const_iterator_map tmp(*this);
				_ptr = _ptr->next_node();
				return (tmp);
			};

			const_iterator_map &operator--()
			{
				_ptr = _ptr->previous_node();
				return *this;
			};

			const_iterator_map operator--(int)
			{
				const_iterator_map tmp(*this);
				_ptr = _ptr->previous_node();
				return tmp;
			};

			//-------------REFERENCE & POINTEUR -----------
			reference operator*() const
			{
				return (_ptr->value);
			};

			const pointer operator->() const
			{
				return (&_ptr->value);
			};

			//-------------BOOLEANS -----------

			bool operator==(const const_iterator_map &x) const
			{
				return (_ptr == x._ptr);
			};

			bool operator!=(const const_iterator_map &x) const
			{
				return (_ptr != x._ptr);
			};
	};
}

#endif