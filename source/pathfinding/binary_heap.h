//
// Created by fabio on 12/12/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_BINARY_HEAP_H
#define THE_LAIR_OF_THE_MINOTAUR_BINARY_HEAP_H

#include "comparator.h"
#include <stdexcept>
#include <vector>

namespace pathfinding
{
    template<typename T>
    class BinaryHeap
    {
    public :

        BinaryHeap(int size, Comparator<T>* comparator) : size_(size), comparator_(comparator)
        {
            this->heap_ = new T[this->size_ + 1]();
        }

        void Push(const T& item)
        {
            if (this->last_available_pos_ > this->size_)
            {
                throw std::length_error("Binary Heap is full.");
            }

            this->heap_[this->last_available_pos_] = item;

            this->PushAt(this->last_available_pos_);

            this->last_available_pos_++;
        }

        T Pop()
        {
            if (this->is_empty())
            {
                throw std::length_error("Binary Heap is empty.");
            }

            T item = this->heap_[1];

            this->heap_[1] = this->heap_[this->get_last_position()];

            this->heap_[this->get_last_position()] = T();

            this->last_available_pos_--;

            this->PopAt(1);

            return item;
        }

        T Remove(const T& obj)
        {
            if (this->is_empty())
            {
                throw std::length_error("Binary Heap is empty.");
            }

            for (int i = 1; i <= this->get_last_position(); i++)
            {
                if (this->comparator_->Compare(this->heap_[i], obj) == 0)
                {
                    T item = this->heap_[i];

                    this->heap_[i] = this->heap_[this->get_last_position()];

                    this->heap_[this->get_last_position()] = T();

                    this->last_available_pos_--;

                    this->PopAt(i);

                    return item;
                }
            }

            throw std::invalid_argument("Object not found.");
        }

        T Peek() const
        {
            if (this->is_empty())
            {
                return this->heap_[0];
            }

            return this->heap_[1];
        }

        const int& size() const
        {
            return this->size_;
        }

        std::vector<T> ToVector() const
        {
            return std::vector<T>(this->heap_ + 1, this->heap_ + this->size_ + 1);
        }

        const bool is_empty() const
        {
            return this->last_available_pos_ == 1;
        }

        ~BinaryHeap()
        {
            delete[] this->heap_;
        }

    private:

        T* heap_;

        int size_;

        int last_available_pos_ = 1;

        Comparator<T>* comparator_;

        void PopAt(const int& index)
        {
            int left_child_index = this->get_left_child_position(index);

            int right_child_index = this->get_right_child_position(index);

            T item = this->heap_[index];

            T left_child = T();
            T right_child = T();

            if (left_child_index <= this->size_)
            {
                left_child = this->heap_[left_child_index];
            }

            if (right_child_index <= this->size_)
            {
                right_child = this->heap_[right_child_index];
            }

            if ((this->comparator_->Compare(item, left_child) < 0 || left_child == T()) &&
                (this->comparator_->Compare(item, right_child) < 0 || right_child == T()))
            {
                return;
            }

            if ((this->comparator_->Compare(left_child, right_child) <= 0) || right_child == T())
            {
                this->heap_[index] = left_child;
                this->heap_[left_child_index] = item;

                this->PopAt(left_child_index);
            }
            else if (this->comparator_->Compare(right_child, left_child) < 0)
            {
                this->heap_[index] = right_child;
                this->heap_[right_child_index] = item;

                this->PopAt(right_child_index);
            }
        }

        void PushAt(const int& index)
        {
            T item = this->heap_[index];

            int parent_index = this->get_parent_position(index);

            T parent = this->heap_[parent_index];

            if (this->comparator_->Compare(item, parent) < 0)
            {
                this->heap_[index] = parent;
                this->heap_[parent_index] = item;

                this->PushAt(parent_index);
            }
        }

        const int get_right_child_position(const int& index) const
        {
            return (index * 2) + 1;
        }

        const int get_left_child_position(const int& index) const
        {
            return index * 2;
        }

        const int get_parent_position(const int& position) const
        {
            return position / 2;
        }

        const int get_last_position() const
        {
            return this->last_available_pos_ - 1;
        }
    };
}


#endif //THE_LAIR_OF_THE_MINOTAUR_BINARY_HEAP_H
