#include "sequence1.h"
#include <cassert>

namespace main_savitch_3
{
    const sequence::size_type sequence::CAPACITY;
//Postcondition: The sequence has been initialized as an empty sequence, where the current index is set to 0.
    sequence::sequence(){
        m_used = 0;
        m_current_index = m_used;
    }
/*Precondition: the sequence is not empty. (Just to be safe)
 Postcondition: The first item in the sequence becomes the current item*/
    void sequence::start( ){
        assert(m_used >= 0);
        m_current_index = 0;
    }
/* Precondition: is_item is true.
Postcondition: If the current item was already the last item in the sequence, then there is no longer any current item. Otherwise, the new
current item is the next item in the sequence.*/

    void sequence::advance( ){
        assert(is_item());
        ++m_current_index;
    }
/*  Precondition: m_used did not reach the capacity of the array.
    Postcondition: A new copy of entry has been inserted in the sequence before the current item. If is_item is false,
    then the new entry has been inserted at the front of the sequence. Newly inserted item is now the current item */

    void sequence::insert(const value_type& entry){
        assert(m_used < CAPACITY);
        //If the sequence is empty, then entry becomes the first and only item.
        if(m_used == 0){
            m_data[0] = entry;
            m_current_index = 0;
            m_used++;
            return;
        }
        //If is_item is false, entry will inserted at the front of the sequence.
        if(!is_item()){
            m_current_index = 0;
        }
        //Makes space for entry
        size_type index = m_used;
        while(index > m_current_index){
            m_data[index] = m_data[index-1];
            --index;
        }
        m_data[m_current_index] = entry;
        m_used++;
}

/*  Precondition: m_used did not reach the capacity of the array.
    Postcondition: A new copy of entry has been inserted in the sequence after the current item. If is_item is flase, then the new entry has
    been attached to the end of the sequence. Newly inserted item is now the current item of the sequence. */

    void sequence::attach(const value_type& entry){
        assert(m_used < CAPACITY);
        //If the sequence is empty, then entry becomes the first and only item.
        if(m_used == 0){
            m_data[0] = entry;
            m_current_index = 0;
            m_used++;
            return;
        }
        //If is_item is false, or the current index is at the last item in the sequence, place entry at the end of the sequence.
        if(!is_item() || m_current_index == m_used-1){
            m_data[m_used] = entry;
            m_current_index = m_used;
            m_used++;
            return;
        }
        //Makes space for entry
        size_type index = m_used;
        while(index > m_current_index + 1){
            m_data[index] = m_data[index-1];
            --index;
        }
        m_current_index++;
        m_data[m_current_index] = entry;
        m_used++;
    }

/*   Precondition: is_item is true.
     Postcondition: The current item has been removed from the sequence, and the item after this is now the new current item.*/
    void sequence::remove_current( ){
        assert(is_item());
        //Case where current index is at the end of the sequence.
        if(m_current_index == m_used-1){
            m_used--;
            m_current_index = m_used;
            return;
        }
        //Shifts all items to fill the removed item.
        for(size_type i = m_current_index+1; i < m_used; ++i){
            m_data[i-1] = m_data[i];
        }
        m_used--;
    }

//Postcondition: The return number of items in the sequence.
    sequence::size_type sequence::size() const{
        return m_used;
    }

/*Postcondition: Returns true if there is a valid "current" item that may be retrieved by activating the current
member function. Returns false if there is no valid current item.*/

    bool sequence::is_item() const{
        return (m_current_index >= 0 && m_current_index < m_used);
    }
/*Precondition: is_item is true.
  Postcondition: Returns current item in the sequence.*/

    sequence::value_type sequence::current() const{
        assert(is_item());
        return m_data[m_current_index];
}


}
