#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_
#include "s21_list.h"
#include <algorithm>
#include <initializer_list>

namespace s21 {
/**
 * @brief Queue (очередь) - это контейнер с элементами, организованными по принцнипу FIFO (First-In, First-Out).
 * @details Так же как список, однако удаление производится строго из "головы",
 * а запись, то есть добавление новых элементов, строго в "хвост".
 * Реализован через список (s21::list)
 * 
 */
template<typename T>
    class queue {
        public:
            using value_type = T;
            using reference = T&;
            using const_reference = const T&;
            using size_type = std::size_t;

            /*---------------------------constructors and operators queue-----------------------------------*/

            /**
             * @brief Конструктор по умолчанию, создает пустую очередь
             * 
             */
            queue() : list_() {}

            /**
             * @brief Конструктор списка инициализаторов, создает очередь
             * 
             * @param items 
             */
            explicit queue(std::initializer_list<value_type> const &items) : list_(items) {}

            /**
             * @brief Конструктор копирования
             * 
             * @param q 
             */
            queue(const queue &q) : list_(q.list_) {}

            /**
             * @brief Конструктор перемещения
             * 
             * @param q 
             */
            queue(const queue &&q) : list_(std::move(q.list_)) {}

            /**
             * @brief Деструктор будет дефолдным
             * @details list_ сам себя почистит, у него есть свой деструктор
             * 
             */
            ~queue() = default;

            queue& operator=(queue &q) {
                this->list_ = q.list_;
                return *this;
            }

            queue& operator=(queue &&q) noexcept {
                this->list_ = std::move(q.list_);
                return *this;
            }

            /*----------------------------------------------------------------------------------*/

            /*---------------------------methods queue-----------------------------------*/

            /**
             * @brief Получить доступ к первому элементу
             * 
             * @return reference 
             */
            reference front() noexcept {
                return this->list_.front();
            }

            /**
             * @brief Получить доступ к первому элементу
             * @details Для конст обЪекта
             * 
             * @return const_reference 
             */
            const_reference front() const noexcept {
                return this->list_.front();
            }

            /**
             * @brief Получить доступ к последнему элементу
             * 
             * @return reference 
             */
            reference back() noexcept {
                return this->list_.back();
            }

            /**
             * @brief Получить доступ к последнему элементу
             * @details Для конст обЪекта
             * 
             * @return const_reference 
             */
            const_reference back() const noexcept {
                return this->list_.back();
            }

            /**
             * @brief Проверяет, пуст ли контейнер
             * 
             * @return true - контейнер пуст
             * @return false - контейнер не пуст
             */
            bool empty() const noexcept {
                return this->list_.empty();
            }

            size_type size() const noexcept {
                return this->list_.size();
            }

            /**
             * @brief Вставляет элемент в конце
             * 
             * @param value 
             */
            void push(const_reference value) {
                this->list_.push_back(value);
            }


            /**
             * @brief Удаляет первый элемент
             * 
             */
            void pop() noexcept {
                this->list_.pop_front();
            }

            /**
             * @brief Меняет содержимое
             * 
             * @param other 
             */
            void swap(queue& other) {
                std::swap(this->list_, other.list_);
            }

            /**
             * @brief Добавляет новые элементы в конец контейнера
             * 
             * @tparam Args 
             * @param args 
             */
            template<typename... Args>
            void emplace_back(Args&&... args) {
                this->list_.emplace_back(std::forward<Args>(args)...);
            }


            /*----------------------------------------------------------------------------*/


        private:
            s21::list<T> list_;
    }; // queue
} // s21

#endif // SRC_S21_QUEUE_H_