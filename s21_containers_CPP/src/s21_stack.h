#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_
#include "s21_list.h"
#include <algorithm>
#include <initializer_list>

namespace s21 {
    /**
     * @brief Класс stack - последовательный контейнер
     * @details Stack реализован через список list
     * 
     */
    template<typename T>
    class stack {
        public:
            using value_type = T;
            using reference = T&;
            using const_reference = const T&;
            using size_type = std::size_t;

            /*---------------------------constructors and operators stack-----------------------------------*/

            /**
             * @brief Конструктор создает пустой список
             * 
             */
            stack() : list_() {}
            
            /**
             * @brief Конструктор создает список инициализируя кaждый узел элементами
             * 
             * @param items 
             */
            explicit stack(std::initializer_list<value_type> const &items) : list_(items) {}

            /**
             * @brief Конструктор создает список путем копирования из s
             * 
             * @param s 
             */
            stack(const stack &s) : list_(s.list_) {}

            /**
             * @brief Конструктор создает список путем перемещения из s в this
             * 
             * @param s
             */
            stack(stack &&s) : list_(std::move(s.list_)) {}

            /**
             * @brief Деструктор будет дефолдным
             * @details list_ сам себя почистит, у него есть свой деструктор
             * 
             */
            ~stack() = default;

            /**
             * @brief Оператор присваивания копированием
             * 
             */
            stack& operator=(const stack& s) {
                this->list_ = s.list_;
                return *this;
            }

            /**
             * @brief Оператор присваивания перемещением
             * 
             */
            stack& operator=(stack&& s) {
                this->list_ = std::move(s.list_);
                return *this;
            }


            /*------------------------------------------------------------------------------------------------*/

            /*---------------------------methods stack-----------------------------------*/

            /**
             * @brief Обращается к верхнему элементу
             * 
             * @return reference 
             */
            reference top() noexcept {
                return this->list_.back();
            }

            /**
             * @brief Обращается к верхнему элементу
             * @details Для конст объекта
             * 
             * @return const_reference 
             */
            const_reference top() const noexcept {
                return this->list_.back();
            }

            /**
             * @brief Проверяет, пуст ли контейнер
             * 
             * @return true - если пустой
             * @return false - если не пуст
             */
            bool empty() const noexcept {
                return this->list_.empty();
            }

            /**
             * @brief Возвращает количество элементов
             * 
             * @return size_type 
             */
            size_type size() const noexcept {
                return this->list_.size();
            }

            /**
             * @brief Вставляет элемент вверху
             * 
             * @param value 
             */
            void push(const_reference value) {
                this->list_.push_back(value);
            }

            /**
             * @brief Удаляет верхний элемент
             * 
             */
            void pop() {
                this->list_.pop_back();
            }

            /**
             * @brief Меняет содержимое
             * 
             * @param other 
             */
            void swap(stack& other) {
                std::swap(this->list_, other.list_);
            }

            /**
             * @brief Добавляет новые элементы в верхнюю часть контейнера
             * 
             * @tparam Args 
             * @param args 
             */
            template<typename... Args>
            void emplace_front(Args&&... args) {
                this->list_.emplace_back(std::forward<Args>(args)...);
            }


            /*---------------------------------------------------------------------------*/

        private:
            // Поле контейнера s21::list
            s21::list<T> list_;
    };
}


#endif // SRC_S21_STACK_H_