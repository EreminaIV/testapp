#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>

template <typename T>
class List
{
private:
    struct Node_;
    struct Iterator_;

public:
    typedef std::size_t size_type;
    typedef T value_type;
    typedef T &referebs;
    typedef T *pointer;
    typedef Iterator_ iterator;
    List() noexcept : size_(0), begin_(new Node_()), end_(new Node_()) // не возврашает ошибку
    {
    }
    ~List() noexcept
    {
    }
    size_type size() const noexcept
    {
        return this->size_;
    }
    bool empty() const noexcept
    {
        if (size_ == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    } //(this->begin_ == this->end_); }
    iterator begin() const noexcept { return this->begin_; }
    iterator end() const noexcept { return this->end_; }

    T &front() const
    {
        if (!this->empty())
        {
            return *this->begin();
        }
        else
        {
            throw std::out_of_range("this list empty");
        }
    }
    T &back() const
    {
        if (!this->empty())
        {
            return *this->end().operator--();
        }
        else
        {
            throw std::out_of_range("this list empty");
        }
    }
    void push_back(const T &varibal) noexcept(false)
    {
        if (this->empty())
        {
            begin_.node->value = varibal;
            Node_ *nod = new Node_;
            nod->prev = begin_.node;
            end_.node = nod;
        }
        else
        {
            end_.node->value = varibal;
            Node_ *nod = new Node_;
            nod->prev = end_.node;
            iterator itr = iterator(end_.node->prev);
           // iterator itr = end_--;
            itr.node->next = end_.node;
            end_.node = nod;
        }
        size_++;
    }
    void pop_back() noexcept(false)
    {
        if (this->empty())
        {
            throw std::out_of_range("list empty");
        }
        else
        {
            size_--;
            iterator itr = this->end().operator--();
            itr.node->prev->next = nullptr;
            end_.node = itr.node->prev;
            delete itr.node;
        }
    }
    void insert(const size_type &pozition, const T &varibal)
    {
        if (pozition < size_)
        {
            if (pozition != 0)
            {
                iterator itr = begin_;
                for (std::size_t i = 0; i < pozition; i++, itr++)
                {
                }
                Node_ *nod = new Node_;
                nod->value = varibal;
                nod->next = itr.node;
                nod->prev = itr.node->prev;
                itr.node->prev = nod;
                itr--.node->next = nod;
                // 1 - 2  3 - 4 - 5
                //      \\19//    
                //pozition = 3 => 1 2 >3< 4 5
                size_++;
            }
            else
            {
                
                Node_ *nod = new Node_;
                nod->value = varibal;
                nod->next = begin_.node;
                begin_.node->prev = nod;
                begin_.node = nod;
                size_++;
            }
        }
        else
        {
        }
    }

    void print_list()
    {
        iterator itr = this->begin();
        std::cout << "size_ = " << size_ << std::endl;
        for (int i = 0; i < size_ - 1; i++)
        {
            std::cout << "N" << i << ") " << *itr << " ";
            ++itr;
            //itr++;
            // itr = itr++;//.operator++();
        }
        std::cout << "N" << size_ - 1 << ") " << *itr << std::endl;
        //std::cout << *itr;
      //  std::cout << begin_.node->value << " " << begin_.node->next->value << " " << begin_.node->next->next->value  << " " << begin_.node->next->next->next->next->value << std::endl;
    }
    //добавляем спарва "_"
private:
    size_type size_;
    iterator begin_;
    iterator end_;
    struct Node_
    {
        Node_() : value(T()), next(nullptr), prev(nullptr) {}
        ~Node_() {}
        T value;
        Node_ *next;
        Node_ *prev;
    };
    //this свой не глобальный
    struct Iterator_
    {
        Iterator_() : node(nullptr) {}
        Iterator_(Node_ *const n) : node(n) {}
        Iterator_(const Iterator_ &iter) : node(iter.node) {}
        ~Iterator_() {}

        Node_ *node;

        bool operator!=(const iterator &iter) const noexcept
        {
            return this->node != iter.node;
        }

        bool operator==(const iterator &iter) const noexcept
        {
            return this->node == iter.node;
        }
        T &operator*() const noexcept { return this->node->value; }
        //для ++ написать push_back, pop_back
        //не работает -- 
        Iterator_ &operator--() noexcept(false)
        {
            auto &prev = this->node->prev;
            if (prev != nullptr)
            {
                this->node = prev;
                return *this;
            }
            else
            {
                throw std::out_of_range("the begin has been overcowe");
            }
        }
        Iterator_ operator--(int) noexcept(false)
        {
            auto &prev = this->node->prev;
            if (prev != nullptr)
            {
                const auto curv = *this;
                this->node = prev;
                return curv;
            }
            else
            {
                throw std::out_of_range("the begin has been overcowe");
            }
        }
        Iterator_ &operator++() noexcept(false)
        {
            auto &next = this->node->next;
            if (next != nullptr)
            {
                this->node = next;
                return *this;
            }
            else
            {
                throw std::out_of_range("the begin has been overcowe");
            }
        }
        Iterator_ operator++(int) noexcept(false)
        {
            auto &next = this->node->next;
            if (next != nullptr)
            {
                const auto curv = *this;
                this->node = next;
                return curv;
            }
            else
            {
                throw std::out_of_range("the begin has been overcowe");
            }
        }
    };
};