#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft
{
	template <typename T>
	class iterator
	{
        public :
            typedef             T				value_type;
            typedef             value_type      &reference;
            typedef             value_type      *pointer;
            typedef typename    std::ptrdiff_t  difference_type; // on met ptrdiff_t carr dans iterator_trait c'est comme ca qu'on le définit
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
            iterator(void){};

            //contructors fill one
            iterator(pointer ptr): _ptr(ptr){};

            //Constructor by copy
            iterator(const iterator &src)
            {
            //    std::cout << "copyyyyyy= " << std::endl;

                if (*this != src)
					*this = src;
            }
           
            // operator =
			iterator& operator= (iterator const &src)
            {
				

                _ptr = src._ptr;
            //   std::cout << "ap_ptr_lala= "<< *_ptr << std::endl;

                return (*this);
            }

            //destructeur
            ~iterator(){}; // virtual ou pas ?

        //-------------FONCTION INCREMENT DECREMENT-----------
            // ++a 
            iterator operator ++()
            {
                _ptr++;
             //   std::cout << "coucou" << std::endl;
                return (*this);
            }

            // a++ int
            // quand on fait ça on appel ++a, donc on doit enregistrer la position de base
            // retrouner la position de base pour apres faire appel à la fonction du dessus qui affichera la modification
            iterator operator ++(int)
            {
                iterator index; // on déclare un index qui prend la position de base
                index = *this;
                ++_ptr; // on incrrement _ptr (donc appel a la fonction du haut)
                return (index); // et on envoie l'index sans l'incrementation 
            };
            
            // --a
            iterator operator --()
            {
                _ptr--;
                std::cout << "ap_ptr= "<< *_ptr << std::endl;
                return (*this);
            }

            // a-- int
            iterator operator --(int)
            {
                iterator index;
                index = *this;
              //  std::cout << "coucou" << std::endl;
                --_ptr;
                return (index);
            };
        
        //-------------SUPPORT ARITHETIC OPERATOR + AND - -----------
            // a + n ON DIT QUE N EST UN DIFFERENT TYPE DONC JE PEUX PAS METTRE INT JE PENSE
            iterator operator+(int n) // on fait une copie car on ne l'assigne pas comme avec a += n 
            {
                iterator tmp; //JE METS UN INT SINON J'AI DEUX FOIS LA MEME DECLA 129
                tmp = *this;
                for (int i = 0; i < n; i++)
                    tmp._ptr++;
                return (tmp);
            };
            // n + a ? 

            // a - n
            iterator operator -(int n)
            {

                iterator tmp;
                tmp = *this;
                for (int i = 0; i < n; i++)
                    tmp._ptr--;
                return (tmp);
            };

            // a + b donc deux iterator ?
            int operator +(iterator b)
            {
                return (_ptr + b._ptr);
            };

            // a - b
            int operator -(iterator b)
            {

                return (_ptr - b._ptr);
            };

        //-------------SUPPORT COMPOUNF ASSIGNMENT OPERATION += AND -= -----------
            // a += n on fait pas de copie car on l'assigne directement à a
            iterator operator +=(int n)
            {
                for (int i = 0; i < n; i++)
                    _ptr++;
                return (*this);
            };
            // a -= n
             iterator operator -=(int n)
            {

                for (int i = 0; i < n; i++)
                    _ptr--;
                return (*this);
            };

         //-------------BOOLEANS -----------
            //==
            bool operator== (const iterator& b) 
            {

                return (_ptr == b._ptr);
            };

            //!=
            bool operator!= (const iterator& b) 
            {
                return (_ptr != b._ptr);
            };

            // <
            bool operator< (const iterator& b) 
            {

                return (_ptr < b._ptr);
            };

            // <=
            bool operator<= (const iterator& b) 
            {
                return (_ptr <= b._ptr);
            };

            // >
            bool operator> (const iterator& b) 
            {
                return (_ptr > b._ptr);
            };

            // >=
            bool operator>= (const iterator& b) 
            {
                return (_ptr >= b._ptr);
            };

        //-------------REFERENCE & POINTEUR -----------
            // a[n]
            reference operator[](difference_type n)
            {
                iterator tmp = *this;
                if (n < 0)
                    tmp -= n;
                else
                    tmp += n;
                return (*tmp);
            }
            

            // *a
            reference operator* ()
            {
         //     std::cout << "coucou" << std::endl;
                
                return (*_ptr);
            };


            // ->
            pointer operator->() const
            {

                return (_ptr);
            };
    };
//-------------------------------------------------------------------------------------------------------------------------------------------------
//-------CONST_ITERATOR--------------
    template <typename T>
	class const_iterator
	{
        public :
            typedef             T				value_type;
            typedef             value_type      &const_reference;
            typedef             value_type      *const_pointer;
            typedef typename    std::ptrdiff_t  difference_type; 

        private :
            const_pointer _ptr;

        public :

		//-------------CONSTRUCTORS-------------
            static const bool input_iterator = true;
            
            //contructors by default
            const_iterator(void){};

            //contructors fill one
            const_iterator(const_pointer ptr): _ptr(ptr){};

            //constructor by iterator
	        const_iterator(iterator<T> const &src)
            {
                _ptr = src.operator->();
            };

            //Constructor by copy
            const_iterator(const const_iterator &src)
            {
                if (*this != src)
					*this = src;
            };
           
            // operator =
			const_iterator& operator= (const const_iterator& src)
            {
                _ptr = src.operator->();
                return (*this);
            };

            //destructeur
            ~const_iterator(){}; // virtual ou pas ?

        //-------------FONCTION INCREMENT DECREMENT-----------
            // ++a 
            const_iterator operator ++()
            {
                _ptr++;
                return (*this);
            };

            // a++ int
            const_iterator operator ++(int)
            {
                const_iterator index; 
                index = *this;
                ++_ptr; 
                return (index); 
            };
            
            // --a
            const_iterator operator --()
            {
                _ptr--;
                return (*this);
            };

            // a-- int
            const_iterator operator --(int)
            {
                const_iterator index;
                index = *this;
                --_ptr;
                return (index);
            };
        
        //-------------SUPPORT ARITHETIC OPERATOR + AND - -----------
            // a + n 
            const_iterator operator +(int n)
            {
                const_iterator tmp;
                tmp = *this;
                for (int i = 0; i < n; i++)
                    tmp._ptr++;
                return (tmp);
            };
            // n + a ? 

            // a - n
            const_iterator operator -(int n)
            {
                const_iterator tmp;
                tmp = *this;
                for (int i = 0; i < n; i++)
                    tmp._ptr--;
                return (tmp);
            };

            // a + b donc deux iterator ?
            int operator +(const_iterator b)
            {
                return (_ptr + b._ptr);
            };

            // a - b
            int operator -(const_iterator b)
            {
                return (_ptr - b._ptr);
            };

        //-------------SUPPORT COMPOUNF ASSIGNMENT OPERATION += AND -= -----------
            // a += n
            const_iterator operator +=(int n)
            {
                for (int i = 0; i < n; i++)
                    _ptr++;
                return (*this);
            };
            // a -= n
            const_iterator operator -=(int n)
            {
                for (int i = 0; i < n; i++)
                    _ptr--;
                return (*this);
            };

         //-------------BOOLEANS -----------
            //==
            bool operator== (const const_iterator& b) 
            {
                return (_ptr == b._ptr);
            };

            //!=
            bool operator!= (const const_iterator& b) 
            {
                return (_ptr != b._ptr);
            };

            // <
            bool operator< (const const_iterator& b) 
            {
                return (_ptr < b._ptr);
            };

            // <=
            bool operator<= (const const_iterator& b) 
            {
                return (_ptr <= b._ptr);
            };

            // >
            bool operator> (const const_iterator& b) 
            {
                return (_ptr > b._ptr);
            };

            // >=
            bool operator>= (const const_iterator& b) 
            {
                return (_ptr >= b._ptr);
            };

        //-------------REFERENCE & POINTEUR -----------
            // a[n]
            const_reference operator[](difference_type n)
            {
                const_iterator tmp = *this;
                if (n < 0)
                    tmp -= n;
                else
                    tmp += n;
                return (*tmp);
            }

            // *a
            const_reference operator* ()
            {
                return (*_ptr);
            };

            // ->
            const_pointer operator->() const
            {
                return (_ptr);
            };
    };

//-------------------------------------------------------------------------------------------------------------------------------------------------
    //-------REVERSE_ITERATOR--------------
    template <typename T>
	class reverse_iterator
	{
        public :
            typedef             T				value_type;
            typedef             value_type      &reverse_reference;
            typedef             value_type      *reverse_pointer;
            typedef typename    std::ptrdiff_t  difference_type; 

        private :

            reverse_pointer _ptr;

        public :

		//-------------CONSTRUCTORS-------------

            static const bool input_iterator = true;
            
            //contructors by default
            reverse_iterator(void){};

            //contructors fill one
            reverse_iterator(reverse_pointer ptr): _ptr(ptr){};

            //constructor by iterator
	        reverse_iterator(iterator<T> const &src)
            {
                _ptr = src.operator->();
            };

            //reverseructor by copy
            reverse_iterator(const reverse_iterator &src)
            {
                if (*this != src)
					*this = src;
            };
           
            // operator =
			reverse_iterator& operator= (const reverse_iterator& src)
            {
                _ptr = src.operator->();
                return (*this);
            };

            //destructeur
            ~reverse_iterator(){}; // virtual ou pas ?

        //-------------FONCTION INCREMENT DECREMENT-----------
            // ++a 
            reverse_iterator operator ++()
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
            reverse_iterator operator --()
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
            reverse_iterator operator +(int n)
            {
                reverse_iterator tmp;
                tmp = *this;
                for (int i = 0; i < n; i++)
                    tmp._ptr--;
                return (tmp);
            };
            // n + a ? 

            // a - n
            reverse_iterator operator -(int n)
            {
                reverse_iterator tmp;
                tmp = *this;
                for (int i = 0; i < n; i++)
                    tmp._ptr++;
                return (tmp);
            };

            // a + b donc deux iterator ?
            int operator +(reverse_iterator b)
            {
                return (_ptr - b._ptr);
            };

            // a - b
            int operator -(reverse_iterator b)
            {
                return (_ptr + b._ptr);
            };

        //-------------SUPPORT COMPOUNF ASSIGNMENT OPERATION += AND -= -----------
            // a += n
            reverse_iterator operator +=(int n)
            {
                for (int i = 0; i < n; i++)
                    _ptr--;
                return (*this);
            };
            // a -= n
            reverse_iterator operator -=(int n)
            {
                for (int i = 0; i < n; i++)
                    _ptr++;
                return (*this);
            };

         //-------------BOOLEANS -----------
            //==
            bool operator== (const reverse_iterator& b) 
            {
                return (_ptr == b._ptr);
            };

            //!=
            bool operator!= (const reverse_iterator& b) 
            {
                return (_ptr != b._ptr);
            };

            // <
            bool operator< (const reverse_iterator& b) 
            {
                return (_ptr < b._ptr);
            };

            // <=
            bool operator<= (const reverse_iterator& b) 
            {
                return (_ptr <= b._ptr);
            };

            // >
            bool operator> (const reverse_iterator& b) 
            {
                return (_ptr > b._ptr);
            };

            // >=
            bool operator>= (const reverse_iterator& b) 
            {
                return (_ptr >= b._ptr);
            };

        //-------------REFERENCE & POINTEUR -----------
            // a[n]
            reverse_reference operator[](difference_type n)
            {
                reverse_iterator tmp = *this;
                if (n < 0)
                    tmp -= n;
                else
                    tmp += n;
                return (*tmp);
            }

            // *a
            reverse_reference operator* ()
            {
                return (*_ptr);
            };

            // ->
            reverse_pointer operator->() const 
            {
                return (_ptr);
            };
    };
    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //-------CONST_REVERSE_ITERATOR--------------
    
    template <typename T>
	class const_reverse_iterator
	{
        public :
            typedef             T				value_type;
            typedef             value_type      &const_reverse_reference;
            typedef             value_type      *const_reverse_pointer;
            typedef typename    std::ptrdiff_t  difference_type; 

        private :

            const_reverse_pointer _ptr;

        public :

		//-------------CONSTRUCTORS-------------
            
            //contructors by default
            const_reverse_iterator(void){};

            //contructors fill one
            //const_reverse_iterator(const_reverse_pointer ptr): _ptr(ptr){};

            //constructor by reverse iterator
	        const_reverse_iterator(reverse_iterator<T> const &src)
            {
                _ptr = src.operator->();
            };

            //constructor by const iterator
	        const_reverse_iterator(const_iterator<T> const &src)
            {
                _ptr = src.operator->();
            };

            //const_reverseructor by copy
            const_reverse_iterator(const const_reverse_iterator &src)
            {
                if (*this != src)
					*this = src;
            };
           
            // operator =
			const_reverse_iterator& operator= (const const_reverse_iterator& src)
            {
                _ptr = src.operator->();
                return (*this);
            };

            //destructeur
            ~const_reverse_iterator(){}; // virtual ou pas ?

        //-------------FONCTION INCREMENT DECREMENT-----------
            // ++a 
            const_reverse_iterator operator ++()
            {
                _ptr--;
                return (*this);
            };

            // a++ int
            const_reverse_iterator operator ++(int)
            {
                const_reverse_iterator index; 
                index = *this;
                --_ptr; 
                return (index); 
            };
            
            // --a
            const_reverse_iterator operator --()
            {
                _ptr++;
                return (*this);
            }

            // a-- int
            const_reverse_iterator operator --(int)
            {
                const_reverse_iterator index;
                index = *this;
                ++_ptr;
                return (index);
            };
        
        //-------------SUPPORT ARITHETIC OPERATOR + AND - -----------
            // a + n 
            const_reverse_iterator operator +(int n)
            {
                const_reverse_iterator tmp;
                tmp = *this;
                for (int i = 0; i < n; i++)
                    tmp._ptr--;
                return (tmp);
            };
            // n + a ? 

            // a - n
            const_reverse_iterator operator -(int n)
            {
                const_reverse_iterator tmp;
                tmp = *this;
                for (int i = 0; i < n; i++)
                    tmp._ptr++;
                return (tmp);
            };

            // a + b donc deux iterator ?
            int operator +(const_reverse_iterator b)
            {
                return (_ptr - b._ptr);
            };

            // a - b
            int operator -(const_reverse_iterator b)
            {
                return (_ptr + b._ptr);
            };

        //-------------SUPPORT COMPOUNF ASSIGNMENT OPERATION += AND -= -----------
            // a += n
            const_reverse_iterator operator +=(int n)
            {
                for (int i = 0; i < n; i++)
                    _ptr--;
                return (*this);
            };
            // a -= n
            const_reverse_iterator operator -=(int n)
            {
                for (int i = 0; i < n; i++)
                    _ptr++;
                return (*this);
            };

         //-------------BOOLEANS -----------
            //==
            bool operator== (const const_reverse_iterator& b) 
            {
                return (_ptr == b._ptr);
            };

            //!=
            bool operator!= (const const_reverse_iterator& b) 
            {
                return (_ptr != b._ptr);
            };

            // <
            bool operator< (const const_reverse_iterator& b) 
            {
                return (_ptr < b._ptr);
            };

            // <=
            bool operator<= (const const_reverse_iterator& b) 
            {
                return (_ptr <= b._ptr);
            };

            // >
            bool operator> (const const_reverse_iterator& b) 
            {
                return (_ptr > b._ptr);
            };

            // >=
            bool operator>= (const const_reverse_iterator& b) 
            {
                return (_ptr >= b._ptr);
            };

        //-------------REFERENCE & POINTEUR -----------
            // a[n]
            const_reverse_reference operator[](difference_type n)
            {
                const_reverse_iterator tmp = *this;
                if (n < 0)
                    tmp -= n;
                else
                    tmp += n;
                return (*tmp);
            }

            // *a
            const_reverse_reference operator* ()
            {
                return (*_ptr);
            };

            // ->
            const_reverse_pointer operator->() const
            {
                return (_ptr);
            };
    };
}

#endif
