#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "iterator_traits.hpp"



namespace ft
{
	template <typename T>
	class Iterator
	{
        public :
            typedef             T				value_type;
            typedef             T                &reference;
            typedef             T                 *pointer;

		    typedef	std::random_access_iterator_tag			iterator_category;
            typedef    std::ptrdiff_t  difference_type; // on met ptrdiff_t carr dans iterator_trait c'est comme ca qu'on le définit
        // ptrdiff_t C'est un type capable de représenter le résultat de toute opération de soustraction de pointeur valide.

        

        // ON EST CENSE METTRE CA : typedef Category  iterator_category;
        // MAIS JE PENSE QUE C EST POUR PRECISER LA CATEGORIE DE L ITERATOR DONC LES FOWARD, BIDIRECTION
        // ETC .... DONC COMME ON FAIT TOUT D'UN COUP JE PENSE ON S'EN FOU
        private :

            pointer _ptr;

        public :


        // Où X est un type d'itérateur,
        // a et b sont des objets de ce type d'itérateur,
        // t est un objet du type pointé par le type d'itérateur 
        // n est un int
		//-------------CONSTRUCTORS-------------
            static const bool input_iterator = true;
            //contructors by default
            Iterator(void){};

            //contructors fill one
            Iterator(pointer ptr): _ptr(ptr){};

            template <class Ite>
			Iterator(Iterator<Ite> const &src): _ptr(src.base()) {};
			

            //Constructor by copy
            // Iterator(const Iterator &src)
            // {
            //     if (*this != src)
			// 		*this = src;
            // }
           
            // operator =
			Iterator& operator= (const Iterator& src)
            {
                _ptr = src.base();
                return (*this);
            }

            pointer	base() const
			{
				return (_ptr);
			}

            //destructeur
           virtual ~Iterator(){}; // virtual ou pas ?

            // template <class Ite>
			// friend Iterator<Ite> operator+(const int & lhs, const Iterator<Ite>& rhs);
			


        //-------------FONCTION INCREMENT DECREMENT-----------
            // ++a 
            Iterator &operator ++()
            {

                _ptr++;
                return (*this);
            }

            // a++ int
            // quand on fait ça on appel ++a, donc on doit enregistrer la position de base
            // retrouner la position de base pour apres faire appel à la fonction du dessus qui affichera la modification
            Iterator operator ++(int)
            {
                Iterator index; // on déclare un index qui prend la position de base
                index = *this;
                ++_ptr; // on incrrement _ptr (donc appel a la fonction du haut)
                return (index); // et on envoie l'index sans l'incrementation 
            };
            
            // --a
            Iterator &operator --()
            {
                _ptr--;
                return (*this);
            }

            // a-- int
            Iterator operator --(int)
            {
                Iterator index;
                index = *this;
                --_ptr;
                return (index);
            };
        
        //-------------SUPPORT ARITHETIC OPERATOR + AND - -----------
            // a + n ON DIT QUE N EST UN DIFFERENT TYPE DONC JE PEUX PAS METTRE INT JE PENSE
            Iterator operator+(difference_type n) const// on fait une copie car on ne l'assigne pas comme avec a += n 
            {
                Iterator tmp; //JE METS UN INT SINON J'AI DEUX FOIS LA MEME DECLA 129
                tmp = *this;
                tmp._ptr += n;
                return (tmp);
            };
            // n + a ? 

            // a - n
            Iterator operator-(difference_type n) const// on fait une copie car on ne l'assigne pas comme avec a += n 
            {
                Iterator tmp;
                tmp = *this;
                tmp._ptr -= n;
                return (tmp);
            };

            // // a + b donc deux iterator ?
            // int operator +(iterator b)
            // {
            //     return (_ptr + b._ptr);
            // };

            // // a - b
            // int operator -(iterator b)
            // {
            //     return (_ptr - b._ptr);
            // };

        //-------------SUPPORT COMPOUNF ASSIGNMENT OPERATION += AND -= -----------
            // a += n on fait pas de copie car on l'assigne directement à a
            Iterator &operator +=(difference_type n) 
            {
                _ptr += n;
                return (*this);
            };
            // a -= n
            Iterator &operator -=(difference_type n)
            {
                
                _ptr -= n;
                return (*this);
            };

            //-------------REFERENCE & POINTEUR -----------
            // a[n]
            reference operator[](difference_type n) const
            {
                return (_ptr[n]);
            }

            // *a
            reference operator* () const
            {
                return (*_ptr);
            };

            // ->
            pointer operator->() const
            {
                return (_ptr);
            };
    };

         //-------------BOOLEANS -----------
                     //==
	    template <class Ite>
        bool operator==(const Iterator<Ite> &lhs, const Iterator <Ite>& rhs)
        {
            return (lhs.base() == rhs.base());
        };

            //!=
        template  <class Ite>
        bool operator!= (const Iterator<Ite>& lhs, const Iterator<Ite>& rhs) 
        {
            return (lhs.base() != rhs.base());
        };

            // <
        template <class Ite>
        bool operator< (const Iterator<Ite>& lhs, const Iterator<Ite>& rhs) 
        {
            return !(lhs.base() < rhs.base());
        };

            // <=
        template <class Ite>
        bool operator<= (const Iterator<Ite>& lhs, const Iterator<Ite>& rhs)
        {
            return !(lhs.base() <= rhs.base());
        };

            // >
        template <class Ite>
        bool operator> (const Iterator<Ite>& lhs, const Iterator<Ite>& rhs) 
        {
            return (lhs.base() < rhs.base());
        };

            // >=
        template <class Ite>
        bool operator>= (const Iterator<Ite>& lhs, const Iterator<Ite>& rhs) 
        {
            return (lhs.base() < rhs.base());
        };

        template <typename T>
		ft::Iterator<T> operator+(typename ft::Iterator<T>::difference_type n, typename ft::Iterator<T> &rhs)
        {
            return (&(*rhs) + n);
        };

        template <class Ite>
		typename Iterator<Ite>::difference_type operator-(const Iterator<Ite>&lhs, const Iterator<Ite>& rhs)
        {

            return (lhs.base() - rhs.base());
        };
    
}


//-------------------------------------------------------------------------------------------------------------------------------------------------
//-------CONST_ITERATOR--------------
//     template <typename T>
// 	class const_iterator
// 	{
//         public :
//             typedef             T				value_type;
//             typedef             value_type      &const_reference;
//             typedef             value_type      *const_pointer;
//             typedef typename    std::ptrdiff_t  difference_type;
//             //typedef typename    std::ptrdiff_t  int; 

//         private :
//             const_pointer _ptr;

//         public :

// 		//-------------CONSTRUCTORS-------------
//             static const bool input_iterator = true;
            
//             //contructors by default
//             const_iterator(void){};

//             //contructors fill one
//             const_iterator(const_pointer ptr): _ptr(ptr){};

//             //constructor by iterator
// 	        const_iterator(iterator<T> const &src)
//             {
//                 _ptr = src.operator->();
//             };

//             //Constructor by copy
//             const_iterator(const const_iterator &src)
//             {
//                 if (*this != src)
// 					*this = src;
//             };
           
//             // operator =
// 			const_iterator& operator= (const const_iterator& src)
//             {
//                 _ptr = src.operator->();
//                 return (*this);
//             };

//             //destructeur
//             ~const_iterator(){}; // virtual ou pas ?

//         //-------------FONCTION INCREMENT DECREMENT-----------
//             // ++a 
//             const_iterator operator ++()
//             {
//                 _ptr++;
//                 return (*this);
//             };

//             // a++ int
//             const_iterator operator ++(int)
//             {
//                 const_iterator index; 
//                 index = *this;
//                 ++_ptr; 
//                 return (index); 
//             };
            
//             // --a
//             const_iterator operator --()
//             {
//                 _ptr--;
//                 return (*this);
//             };

//             // a-- int
//             const_iterator operator --(int)
//             {
//                 const_iterator index;
//                 index = *this;
//                 --_ptr;
//                 return (index);
//             };
        
//         //-------------SUPPORT ARITHETIC OPERATOR + AND - -----------
//             // a + n 
//             const_iterator operator +(int n)
//             {
//                 const_iterator tmp;
//                 tmp = *this;
//                 for (int i = 0; i < n; i++)
//                     tmp._ptr++;
//                 return (tmp);
//             };
//             // n + a ? 

//             // a - n
//             const_iterator operator -(int n)
//             {
//                 const_iterator tmp;
//                 tmp = *this;
//                 for (int i = 0; i < n; i++)
//                     tmp._ptr--;
//                 return (tmp);
//             };

//             // a + b donc deux iterator ?
//             int operator +(const_iterator b)
//             {
//                 return (_ptr + b._ptr);
//             };

//             // a - b
//             int operator -(const_iterator b)
//             {
//                 return (_ptr - b._ptr);
//             };

//         //-------------SUPPORT COMPOUNF ASSIGNMENT OPERATION += AND -= -----------
//             // a += n
//             const_iterator operator +=(int n)
//             {
//                 for (int i = 0; i < n; i++)
//                     _ptr++;
//                 return (*this);
//             };
//             // a -= n
//             const_iterator operator -=(int n)
//             {
//                 for (int i = 0; i < n; i++)
//                     _ptr--;
//                 return (*this);
//             };

//          //-------------BOOLEANS -----------
//             //==
//             bool operator== (const const_iterator& b) 
//             {
//                 return (_ptr == b._ptr);
//             };

//             //!=
//             bool operator!= (const const_iterator& b) 
//             {
//                 return (_ptr != b._ptr);
//             };

//             // <
//             bool operator< (const const_iterator& b) 
//             {
//                 return (_ptr < b._ptr);
//             };

//             // <=
//             bool operator<= (const const_iterator& b) 
//             {
//                 return (_ptr <= b._ptr);
//             };

//             // >
//             bool operator> (const const_iterator& b) 
//             {
//                 return (_ptr > b._ptr);
//             };

//             // >=
//             bool operator>= (const const_iterator& b) 
//             {
//                 return (_ptr >= b._ptr);
//             };

//         //-------------REFERENCE & POINTEUR -----------
//             // a[n]
//             const_reference operator[](difference_type n)
//             {
//                 const_iterator tmp = *this;
//                 if (n < 0)
//                     tmp -= n;
//                 else
//                     tmp += n;
//                 return (*tmp);
//             }

//             // *a
//             const_reference operator* ()
//             {
//                 return (*_ptr);
//             };

//             // ->
//             const_pointer operator->() const
//             {
//                 return (_ptr);
//             };
//     };

// //-------------------------------------------------------------------------------------------------------------------------------------------------
    //-------REVERSE_ITERATOR--------------
namespace ft
{
    template <class Iterator>
	class reverse_iterator
	{
        // public :
        //     typedef             T				value_type;
        //     typedef             value_type      &reverse_reference;
        //     typedef             value_type      *reverse_pointer;
        //     typedef typename    std::ptrdiff_t  difference_type;



            typedef Iterator  iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category  iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type         value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type    difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer            pointer;
			typedef typename ft::iterator_traits<Iterator>::reference          reference;
		
            //typedef typename    std::ptrdiff_t  int; 

        private :

            pointer _ptr;

        public :

		//-------------CONSTRUCTORS-------------
            static const bool input_iterator = true;
            
            //contructors by default
            reverse_iterator(void){};



            reverse_iterator(iterator_type iterator):_ptr(iterator){};
            
            //contructors fill one

			template <typename Ite>
            reverse_iterator(const reverse_iterator<Ite>& reverse_iterator): _ptr(reverse_iterator){};

            //constructor by iterator
	        // reverse_iterator(iterator<T> const &src)
            // {
            //     _ptr = src.operator->();
            // };

            //reverseructor by copy
            // reverse_iterator(const reverse_iterator &src)
            // {
            //     if (*this != src)
			// 		*this = src;
            // };
           
            // operator =
			template <class Iter>
			reverse_iterator& operator= (const reverse_iterator<Iter>& reverse_iterator)
            {
                _ptr = reverse_iterator.base();
                return (*this);
            };


            iterator_type base() const
			{
				return (this->_ptr);
			}
            //destructeur
           virtual ~reverse_iterator(){}; // virtual ou pas ?

        //-------------FONCTION INCREMENT DECREMENT-----------
            // ++a 
            reverse_iterator& operator ++()
            {
                _ptr--;
                return (*this);
            }

            // a++ int
            reverse_iterator operator ++(int)
            {
                reverse_iterator index; 
                index = *this;
                --_ptr; 
                return (index); 
            };
            
            // --a
            reverse_iterator& operator --()
            {
                _ptr++;
                return (*this);
            }

            // a-- int
            reverse_iterator operator --(int)
            {
                reverse_iterator index;
                index = *this;
                ++_ptr;
                return (index);
            };
        
        //-------------SUPPORT ARITHETIC OPERATOR + AND - -----------
            // a + n 
            reverse_iterator operator +(difference_type n) const
            {
                return (_ptr - n);
            };
            // n + a ? 

            // a - n
            reverse_iterator operator -(difference_type n) const
            {
               return (_ptr + n);
            };

            // // a + b donc deux iterator ?
            // int operator +(reverse_iterator b)
            // {
            //     return (_ptr - b._ptr);
            // };

            // // a - b
            // int operator -(reverse_iterator b)
            // {
            //     return (_ptr + b._ptr);
            // };

        //-------------SUPPORT COMPOUNF ASSIGNMENT OPERATION += AND -= -----------
            // a += n
            reverse_iterator& operator +=(difference_type n)
            {
                _ptr = _ptr - n;
                return (*this);
            };
            // a -= n
            reverse_iterator& operator -=(difference_type n)
            {
                 _ptr = _ptr + n;
                return (*this);
            };


              //-------------REFERENCE & POINTEUR -----------
            // a[n]
            reference operator[](difference_type n) const
            {
                return *(*this + n);
            }

            // *a
            reference operator* () const
            {
                return (*_ptr);
            };

            // ->
            pointer operator->() const
            {
                return (&(operator*()));
            };
    };
         //-------------BOOLEANS -----------
            //==
	        template <class Iterator>
            bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
            {
                return (lhs.base() == rhs.base());
            };

            //!=
           template <class Iterator>
            bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
            {
                return (lhs.base() != rhs.base());
            };

            // <
              template <class Iterator>
            bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
            {
               return (lhs.base() < rhs.base());
            };

            // <=
             template <class Iterator>
            bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
            {
               return (lhs.base() <= rhs.base());
            };

            // >
             template <class Iterator>
            bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
            {
                 return (lhs.base() > rhs.base());
            };

            // >=
             template <class Iterator>
            bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
            {
                 return (lhs.base() >= rhs.base());
            };

        template <class Iterator>
		reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& reverse_iterator)
        {
            return (n - &(*reverse_iterator));
        }

        template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>&lhs, const reverse_iterator<Iterator>& rhs)
        {
            return (lhs.base() + rhs.base());
        };


}

# endif
      

//     //-------------------------------------------------------------------------------------------------------------------------------------------------
//     //-------CONST_REVERSE_ITERATOR--------------
    
//     template <typename T>
// 	class const_reverse_iterator
// 	{
//         public :
//             typedef             T				value_type;
//             typedef             value_type      &const_reverse_reference;
//             typedef             value_type      *const_reverse_pointer;
//             typedef typename    std::ptrdiff_t  difference_type;
//             //typedef typename    std::ptrdiff_t  int; 

//         private :

//             const_reverse_pointer _ptr;

//         public :

// 		//-------------CONSTRUCTORS-------------
            
//             //contructors by default
//             const_reverse_iterator(void){};

//             //contructors fill one
//             //const_reverse_iterator(const_reverse_pointer ptr): _ptr(ptr){};

//             //constructor by reverse iterator
// 	        const_reverse_iterator(reverse_iterator<T> const &src)
//             {
//                 _ptr = src.operator->();
//             };

//             //constructor by const iterator
// 	        const_reverse_iterator(const_iterator<T> const &src)
//             {
//                 _ptr = src.operator->();
//             };

//             //const_reverseructor by copy
//             const_reverse_iterator(const const_reverse_iterator &src)
//             {
//                 if (*this != src)
// 					*this = src;
//             };
           
//             // operator =
// 			const_reverse_iterator& operator= (const const_reverse_iterator& src)
//             {
//                 _ptr = src.operator->();
//                 return (*this);
//             };

//             //destructeur
//             ~const_reverse_iterator(){}; // virtual ou pas ?

//         //-------------FONCTION INCREMENT DECREMENT-----------
//             // ++a 
//             const_reverse_iterator operator ++()
//             {
//                 _ptr--;
//                 return (*this);
//             };

//             // a++ int
//             const_reverse_iterator operator ++(int)
//             {
//                 const_reverse_iterator index; 
//                 index = *this;
//                 --_ptr; 
//                 return (index); 
//             };
            
//             // --a
//             const_reverse_iterator operator --()
//             {
//                 _ptr++;
//                 return (*this);
//             }

//             // a-- int
//             const_reverse_iterator operator --(int)
//             {
//                 const_reverse_iterator index;
//                 index = *this;
//                 ++_ptr;
//                 return (index);
//             };
        
//         //-------------SUPPORT ARITHETIC OPERATOR + AND - -----------
//             // a + n 
//             const_reverse_iterator operator +(int n)
//             {
//                 const_reverse_iterator tmp;
//                 tmp = *this;
//                 for (int i = 0; i < n; i++)
//                     tmp._ptr--;
//                 return (tmp);
//             };
//             // n + a ? 

//             // a - n
//             const_reverse_iterator operator -(int n)
//             {
//                 const_reverse_iterator tmp;
//                 tmp = *this;
//                 for (int i = 0; i < n; i++)
//                     tmp._ptr++;
//                 return (tmp);
//             };

//             // a + b donc deux iterator ?
//             int operator +(const_reverse_iterator b)
//             {
//                 return (_ptr - b._ptr);
//             };

//             // a - b
//             int operator -(const_reverse_iterator b)
//             {
//                 return (_ptr + b._ptr);
//             };

//         //-------------SUPPORT COMPOUNF ASSIGNMENT OPERATION += AND -= -----------
//             // a += n
//             const_reverse_iterator operator +=(int n)
//             {
//                 for (int i = 0; i < n; i++)
//                     _ptr--;
//                 return (*this);
//             };
//             // a -= n
//             const_reverse_iterator operator -=(int n)
//             {
//                 for (int i = 0; i < n; i++)
//                     _ptr++;
//                 return (*this);
//             };

//          //-------------BOOLEANS -----------
//             //==
//             bool operator== (const const_reverse_iterator& b) 
//             {
//                 return (_ptr == b._ptr);
//             };

//             //!=
//             bool operator!= (const const_reverse_iterator& b) 
//             {
//                 return (_ptr != b._ptr);
//             };

//             // <
//             bool operator< (const const_reverse_iterator& b) 
//             {
//                 return (_ptr < b._ptr);
//             };

//             // <=
//             bool operator<= (const const_reverse_iterator& b) 
//             {
//                 return (_ptr <= b._ptr);
//             };

//             // >
//             bool operator> (const const_reverse_iterator& b) 
//             {
//                 return (_ptr > b._ptr);
//             };

//             // >=
//             bool operator>= (const const_reverse_iterator& b) 
//             {
//                 return (_ptr >= b._ptr);
//             };

//         //-------------REFERENCE & POINTEUR -----------
//             // a[n]
//             const_reverse_reference operator[](difference_type n)
//             {
//                 const_reverse_iterator tmp = *this;
//                 if (n < 0)
//                     tmp -= n;
//                 else
//                     tmp += n;
//                 return (*tmp);
//             }

//             // *a
//             const_reverse_reference operator* ()
//             {
//                 return (*_ptr);
//             };

//             // ->
//             const_reverse_pointer operator->() const
//             {
//                 return (_ptr);
//             };
//     };
// }

// #endif
