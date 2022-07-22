#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"
# include <iostream>


namespace ft
{
    template< typename T, typename Container = ft::vector<T> > // je pense qu'a la place de deque faut mettre vector
    class stack
    {
        public :

        //----------------DEFINE----------------
            typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

            container_type      _container;

        //---------------VALUES----------------


        public :

        //-------------CONSTRUCTORS-------------
        // doit on faire les constructeurs que vector a ? NON
            //contructors by default
            explicit stack (const container_type& ctnr = container_type()): _container(ctnr)
            {};

            // constructor by copy
	        stack(stack const &src) : _container(src._cont) 
            {};

			//destructeur
			~stack(){};

            //  on fait pas l'assignation ? 

        //-------------FONCTION-------------
            //empty
            bool empty() const
            {
                return(_container.empty());
            };

            //size
            size_type size() const
            {
                return(_container.size());
            };

            //top
            value_type& top()
            {
                return(_container.back()); // on fait appel a la fonction de vector back() qui renvoie le derier element
            };
            //const top
            const value_type& top() const
            {
                return(_container.back());
            };

            //push Insère un nouvel élément en haut de la pile, au-dessus de son élément supérieur actuel. Le contenu de ce nouvel élément est initialisé à une copie de val.
            void push (const value_type& val) // on utilise push_back
            {
                _container.push_back(val);
            };

            //pop  on fait appel a pop_back de vector
            void pop() // Supprime l'élément au-dessus de la pile, réduisant ainsi sa taille de un.
            {
                  _container.pop_back();
            }
    };

    //-------------NON-MEMBER FUNCTION OVERLOADS-------------

		    //relational operators ==
            template <class T, class Container>
               bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
                {
                    return (lhs._container == rhs._container);
                };

            //relational operators !=
            template <class T, class Container>
                bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
                {
				    return (!(lhs._container == rhs._container));
			    };

            //relational operators <
            template <class T, class Container>
                bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
                {
                     return (lhs._container < rhs._container);
                };
                
            //relational operators <=
            template <class T, class Container>
                bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
                {
                    return (lhs._container <= rhs._container);
			    };
		
            //relational operators >
            template <class T, class Container>
                bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
                {
				    return (lhs._container > rhs._container);
			    };
               
            //relational operators >=
            template <class T, class Container>
                bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
                {
				    return (lhs._container >= rhs._container);
			    };
}

#endif