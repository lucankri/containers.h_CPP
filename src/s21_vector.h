#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_
#include <iostream>
#include <initializer_list>
#include <limits>


namespace s21 {

    /**
     * @brief Вектор - это последовательный контейнер, не требующий ручного
     * контроля памяти.
     * @details  Динамическое изменение размера массива происходит не при каждом добавлении или
     * удалении элемента, а только в случае превышения размера заданного размера буфера
     * 
     * @tparam T 
     */
    template<typename T>
    class vector {
        public:
            using value_type = T;
            using reference = T&;
            using const_reference = const T&;
            using iterator = T*;
            using const_iterator = const T*;
            using size_type = std::size_t;
            /*---------------------------------constructors and operators vector-----------------------------------*/
            
            /**
             * @brief Конструктор по умолчанию, создает пустой вектор
             * 
             */
            vector() {
                this->size_ = 0;
                this->capacity_ = 0;
                this->buffer_ = nullptr;
            }

            /**
             * @brief Параметризованный конструктор, создает вектор размера n
             * 
             * @param n 
             */
            explicit vector(size_type n) {
                this->size_ = n;
                this->capacity_ = n;
                this->buffer_ = new value_type[this->capacity_];
            }

            /**
             * @brief Конструктор списка инициализаторов, создает вектор
             * инициализированный с помощью std::initializer_list
             * 
             * @param items 
             */
            vector(std::initializer_list<value_type> const &items) {
                this->size_ = items.size();
                this->capacity_ = items.size();
                this->buffer_ = new value_type[this->capacity_];
                std::copy(items.begin(), items.end(), this->buffer_);
            }

            /**
             * @brief Конструктор копирования
             * 
             * @param v 
             */
            vector(const vector& v) : vector() {
                *this = v;
            }

            /**
             * @brief Конструктор перемещения
             * 
             * @param v 
             */
            vector(vector&& v) : vector() {
                *this = std::move(v);
            }

            /**
             * @brief Деструктор
             * 
             */
            ~vector() {
                delete[] this->buffer_;
            }

            /**
             * @brief Перегрузка оператора присваивания копированием
             * 
             * @param v 
             * @return vector& 
             */
            vector& operator=(const vector& v) {
                if (this != &v) {
                    delete[] this->buffer_;
                    this->size_ = v.size_;
                    this->capacity_ = v.capacity_;
                    if (this->size_ > 0) {
                        this->buffer_ = new value_type[v.capacity_];
                        std::copy(v.begin(), v.end(), this->buffer_);
                    }

                }
                return *this;
            }

            /**
             * @brief Перегрузка оператора присваивания перемещением
             * 
             * @param v 
             * @return vector& 
             */
            vector& operator=(vector&& v) {
                if (this != &v) {
                    delete[] this->buffer_;
                    this->size_ = v.size_;
                    this->capacity_ = v.capacity_;
                    this->buffer_ = v.buffer_;
                    v.buffer_ = nullptr;
                    v.capacity_ = 0;
                    v.size_ = 0;
                }
                return *this;
            }

            /*----------------------------------------------------------------------------------------*/

            /*-----------------------------------------methods vector-----------------------------------------------*/
            
            /**
             * @brief Доступ к указанному элементу с проверкой границ
             * 
             * @param pos 
             * @return reference 
             */
            reference at(size_type pos) {
                if (pos >= size_)
                    throw std::out_of_range("s21::vector::at: The index is out of range");

                return this->buffer_[pos];
            }

            /**
             * @brief Доступ к указанному элементу с проверкой границ
             * @details Для конст объекта
             * 
             * @param pos 
             * @return const_reference 
             */
            const_reference at(size_type pos) const {
                if (pos >= size_)
                    throw std::out_of_range("s21::vector::at: The index is out of range");

                return this->buffer_[pos];
            }

            /**
             * @brief Доступ к указанному элементу
             * 
             * @param pos 
             * @return reference 
             */
            reference operator[](size_type pos) {
                return this->at(pos);
            }

            /**
             * @brief Доступ к указанному элементу
             * @details Для конст объекта
             * 
             * @param pos 
             * @return const_reference 
             */
            const_reference operator[](size_type pos) const {
                return this->at(pos);
            }

            /**
             * @brief Получить доступ к первому элементу
             * 
             * @return reference 
             */
            reference front() {
                if (this->size_ == 0)
                    throw std::out_of_range("s21::vector::front: Using methods on a zero sized container");

               return *this->begin();
            }

            /**
             * @brief Получить доступ к первому элементу
             * @details Для конст объекта
             * 
             * @return const_reference 
             */
            const_reference front() const {
                if (this->size_ == 0)
                    throw std::out_of_range("s21::vector::front: Using methods on a zero sized container");

               return *this->begin();
            }

            /**
             * @brief Получить доступ к последнему элементу
             * 
             * @return reference 
             */
            reference back() {
                if (this->size_ == 0)
                    throw std::out_of_range("s21::vector::front: Using methods on a zero sized container");

                return *(this->end() - 1);
            }

            /**
             * @brief Получить доступ к последнему элементу
             * @details Для конст объекта
             * 
             * @return const_reference 
             */
            const_reference back() const {
                if (this->size_ == 0)
                    throw std::out_of_range("s21::vector::front: Using methods on a zero sized container");

                return *(this->end() - 1);
            }

            /**
             * @brief Прямой доступ к базовому массиву
             * 
             * @return iterator 
             */
            iterator data() noexcept {
                return this->buffer_;
            }

            /**
             * @brief Прямой доступ к базовому массиву
             * @details Для конст объекта
             * 
             * @return const_iterator
             */
            const_iterator data() const noexcept {
                return this->buffer_;
            }

            /**
             * @brief Возвращает итератор в начало
             * 
             * @return iterator 
             */
            iterator begin() noexcept {
                return this->buffer_;
            }

            /**
             * @brief Возвращает итератор в начало
             * @details Для конст объекта
             * 
             * @return const_iterator 
             */
            const_iterator begin() const noexcept {
                return this->buffer_;
            }

            /**
             * @brief Возвращает итератор в конец
             * 
             * @return iterator 
             */
            iterator end() noexcept {
                return this->buffer_ + this->size_;
            }

            /**
             * @brief Возвращает итератор в конец
             * @details Для конст объекта
             * 
             * @return iterator 
             */
            const_iterator end() const noexcept {
                return this->buffer_ + this->size_;
            }

            /**
             * @brief Проверяет, пуст ли контейнер
             * 
             * @return true - контейнер пуст
             * @return false - контйнер не пуст
             */
            bool empty() const noexcept {
                return this->begin() == this->end();
            }

            /**
             * @brief Возвращает количество элементов
             * 
             * @return size_type 
             */
            size_type size() const noexcept{
                return this->size_;
            }

            /**
             * @brief Возвращает максимально возможное количество элементов
             * @details Инофрмация по алгоритму ищите в list и tree
             * 
             * @return size_type 
             */
            size_type max_size() const noexcept {
                return (std::numeric_limits<size_type>::max() / sizeof(value_type) / 2);
            }

            /**
             * @brief выделяет хранилище элементов размера size
             * и копирует текущие элементы массива в новый выделенный массив
             * 
             * @param size - размер хранилище
             */
            void reserve(size_type size) {
                if (size <= this->capacity_)
                    return;

                if (size > this->max_size())
                    throw std::out_of_range("s21::vector::reserve: Reserve capacity can't be larger than max_size!");

                this->reallocVector(size);                   
            }

            /**
             * @brief Возвращает количество элементов,
             * которые могут храниться в выделенной в данный момент памяти
             * 
             * @return size_type 
             */
            size_type capacity() const noexcept {
                return this->capacity_;
            }

            /**
             * @brief Уменьшает использование памяти, освобождая неиспользуемую память
             * 
             */
            void shrink_to_fit() {
                if (this->capacity_ == this->size_)
                    return;

                this->reallocVector(this->size_);
            }

            /**
             * @brief Очищает содержимое
             * @details 
             * 
             */
            void clear() noexcept {
                this->size_ = 0;
            }

            /**
             * @brief Вставляет элементы в конкретную позицию
             * и возвращает итератор, указывающий на новый элемент
             * @details если capacity_ == size_ то делаем реалок на 
             * size_ * 2, если контейнер пуст - выделяем память на 1 элемент
             * 
             */
            iterator insert(const_iterator pos, const_reference value) {
                size_type index = pos - this->begin();
                if (index > this->size_)
                    throw std::out_of_range("s21::vector::insert Unable to insert into a position out of range of begin to end");
                
                if (this->size_ == this->capacity_)
                    this->reallocVector(this->size_ ? this->size_ * 2 : 1);
                
                iterator it_begin = this->begin();
                std::copy(it_begin + index, this->end(), it_begin + index + 1);
                *(this->buffer_ + index) = value;
                this->size_++;
                return it_begin + index;
            }

            /**
             * @brief Аналогично insert только вставка перемещением
             * 
             * @param pos 
             * @param value 
             * @return iterator 
             */
            iterator insert(const_iterator pos, value_type &&value) {
                size_type index = pos - this->begin();
                if (index > this->size_)
                    throw std::out_of_range("s21::vector::insert Unable to insert into a position out of range of begin to end");
                
                if (this->size_ == this->capacity_)
                    this->reallocVector(this->size_ ? this->size_ * 2 : 1);
                
                iterator it_begin = this->begin();
                std::copy(it_begin + index, this->end(), it_begin + index + 1);
                *(this->buffer_ + index) = std::move(value);
                this->size_++;
                return it_begin + index;
            }

            /**
             * @brief Стирает элемент в позиции
             * 
             * @param pos 
             */
            void erase(const_iterator pos) {
                size_type index = pos - this->begin();
                if (index > this->size_)
                    throw std::out_of_range("s21::vector::insert Unable to insert into a position out of range of begin to end");

                std::copy(const_cast<iterator>(pos) + 1, this->end(), this->buffer_ + index);
                this->size_--;
            }

            /**
             * @brief Добавляет элемент в конец
             * 
             * @param value 
             */
            void push_back(const_reference value) {
                this->insert(this->end(), value);
            }

            /**
             * @brief Аналогично push_back только вставка перемещением
             * 
             * @param value 
             */
            void push_back(value_type &&value) {
                this->insert(this->end(), std::move(value));
            }

            /**
             * @brief Удаляет последний элемент
             * 
             */
            void pop_back() {
                if (this->size_ == 0)
                    throw std::out_of_range("s21::vector::pop_back: nothing to delete...");
                
                this->size_--;
            }

            /**
             * @brief Меняет содержимое
             * 
             * @param other 
             */
            void swap(vector& other) {
                std::swap(this->buffer_, other.buffer_);
                std::swap(this->size_, other.size_);
                std::swap(this->capacity_, other.capacity_);
            }

            /**
             * @brief Вставляет новые элементы в контейнер непосредственно перед pos
             * 
             * @tparam Args 
             * @param pos 
             * @param args 
             * @return iterator 
             */
            template<typename... Args>
            iterator emplace(const_iterator pos, Args&&... args) {
                auto index_pos = pos - this->begin();
                iterator it_res;
                // Чтоб insert постоянно не вызывал realloc, мы сразу
                // выделим то количество, которое нужно
                this->reserve(this->capacity_ + sizeof...(args));
                for (auto element : {std::forward<Args>(args)...}) {
                    it_res = this->insert(this->begin() + index_pos++, std::move(element));
                }
                return it_res;
            }

            /**
             * @brief Добавляет новые элементы в конец контейнера
             * 
             * @tparam Args 
             * @param args 
             */
            template<typename... Args>
            void emplace_back(Args&&... args) {
                for (auto element : {std::forward<Args>(args)...}) {
                    this->push_back(std::move(element));
                }
            }


        private:
            size_type size_;
            size_type capacity_;
            iterator buffer_;

            /**
             * @brief Приватная функция для переопределения памяти, копирования
             * в нову память и удаление старой памяти
             * 
             * @param new_capacity 
             */
            void reallocVector(size_type new_capacity) {
                iterator tmp = new value_type[new_capacity];
                for (size_type i = 0; i < this->size_; i++)
                    tmp[i] = std::move(this->buffer_[i]);

                delete[] this->buffer_;
                this->buffer_ = tmp;
                this->capacity_ = new_capacity;
            }
    };
}


#endif // SRC_S21_VECTOR_H_